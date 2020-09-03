#include "finder.h"
#include <future>

namespace ft {
//======================================================================
Finder::Finder()
    : _fmIndex(&_ownedFmIndex)
{
}

//======================================================================
void Finder::testIndex(const FTProp& ftProps, const fs::path &indexPath, std::string& testkmer2 )
{
    //test the index can be loaded correctly
    std::string testkmer = testkmer2;

    csa_wt<wt_huff<rrr_vector<256>>, 512, 1024> _testindex;
    sdsl::load_from_file(_testindex, indexPath);
    auto locs2 = sdsl::locate(_testindex, testkmer.begin(), testkmer.begin()+testkmer.length());

    ft::KmerClass tmpResult = _fmIndex->search(testkmer,
                                                ftProps.getMaxOcc(),
                                                ftProps.getOverCountedFlag());
    if (tmpResult.getKPositions().size() != locs2.size()) {
        FTProp::Log << "test kmer: " << testkmer << std::endl;
        FTProp::Log << " ==> Error: Result Positions=" << tmpResult.getKPositions().size() << " not match locations=" << locs2.size() << std::endl;
    }

}
//======================================================================
void Finder::searchIndexes(ft::FTMap &ftMap)
{
    int numOfIndexes = ftMap.getFTProps().getNumOfIndexes();
    std::cout << "number of indexes " << numOfIndexes << std::endl;

    if (ftMap.getFTProps().getMultithreadFlag()) {
        std::cout << "Parallel Search " << std::endl;
        indexParallelSearch(ftMap);
    } else {
        indexSequentialSearch(ftMap);
    }

}

//======================================================================
void Finder::indexSequentialSearch(FTMap &ftMap)
{
    std::map<fs::path, uint> indexes = ftMap.getFTProps().getIndexSet();
    FTProp::Log << "Sequential Search on " << indexes.size() << " indexes" << std::endl;
    for (std::pair<fs::path, u_int> item : indexes){
        fs::path indexPath = item.first;
        u_int offset = item.second;
        sequentialSearch(ftMap, indexPath, offset);
    }

}

//======================================================================
void Finder::indexParallelSearch(FTMap &ftMap)
{
    std::map<fs::path, uint> indexes = ftMap.getFTProps().getIndexSet();
    std::map<fs::path, uint>::iterator it = indexes.begin();
    while ( it != indexes.end()) {
        fs::path indexPath = it->first;
        uint offset = it->second;
        parallelSearch(ftMap, indexPath, offset);
        it++;
    }
}

//======================================================================
void Finder::addResultsFutures(std::map<std::string, ft::KmerClass> & indexResults, ft::KmerClass &tmpResult, uint offset)
{
    const std::string& resultkmer = tmpResult.getKmer();
    //std::cout << "results kmer " << resultkmer << std::endl;
    //std::cout << "number of result kmer positions " << tmpResult.getKPositions().size() << std::endl;
    if (indexResults.count(resultkmer) > 0)
    {
        ft::KmerClass result = indexResults.find(resultkmer)->second;
        const std::set<long long>& positions = tmpResult.getKPositions();
        result.setKPositions(positions, offset);
        indexResults.find(resultkmer)->second = result;
    } else {
        indexResults[resultkmer] = tmpResult;
    }
   //std::cout << "number of index results " << indexResults.size() << std::endl;
}

//======================================================================
void Finder::parallelSearch(FTMap &ftMap, const fs::path &indexPath,
                            long long offset)
{
    const FTProp& ftProps = ftMap.getFTProps();
    FTProp::Log << "parallelSearch: index Path " << indexPath.string() << std::endl;

    algo::FmIndex* _fmIndex = new algo::FmIndex(ftProps.isVerbose());
    const std::unordered_map<std::string, ft::KmerClass>& kmerMap = ftMap.getKmerSet();


    std::map<std::string, ft::KmerClass>  indexResults;

    try {
        _fmIndex->loadIndexFromFile(indexPath);
    } catch (std::exception& e) {
        FTProp::Log << "Error! " << e.what() << std::endl;
    }
    std::string testKmer = "AAT";
    testIndex(ftProps, indexPath, testKmer);

    // create a vector of futures
    std::vector<std::future<ft::KmerClass>> resultsFutures;
    size_t j = 0;
    size_t k = kmerMap.size();

    // using a queue to easily control the flow of kmers
    std::queue<std::string> kmerQueue;
    std::unordered_map<std::string, ft::KmerClass>::const_iterator it = kmerMap.begin();
    while (it != kmerMap.end())
    {
        FTProp::Log << "INFO" "kmer add to queue " << it->first << std::endl;
        kmerQueue.push(it->first);
        it++;
    }
    if (kmerMap.size() != kmerQueue.size()){
        std::cout << "Error: Kmers not added to queue correctly " << std::endl;
        std::cout << "Number of kmers in kmer map: " << kmerMap.size() << std::endl;
        std::cout << "Number of kmers in kmerQueue: " << kmerQueue.size() << std::endl;
    }

    std::cout << "kmer queue created " << std::endl;
    std::atomic<int> elts;
    elts = 0;

    while (!kmerQueue.empty()) {
        if (j < ftProps.getMaxThreads()) {

            std::string kmer = kmerQueue.front();
            //std::cout << "add kmer to ResultsFuture " << kmer << std::endl;
            resultsFutures.push_back(std::async(std::launch::async, &algo::FmIndex::search,
                                                dynamic_cast<algo::FmIndex*>(_fmIndex),
                                                        kmer,
                                                        ftProps.getMaxOcc(),
                                                        ftProps.getOverCountedFlag()));
            kmerQueue.pop();
            j++;
            k--;
            //std::cout << "Kmer Queue size " << kmerQueue.size() << " j " << j << std::endl;
            continue;
        }


        while (kmerQueue.size() > 0) {
            //std::cout << "Kmer queue is greater than 0" << std::endl;
            if ( kmerQueue.size() < ftProps.getMaxThreads()) {
                std::string kmer = kmerQueue.front();
                //std::cout << "kmer added to resultsFutures  " << kmer << std::endl;
                resultsFutures.push_back(std::async(std::launch::async, &algo::FmIndex::search,
                                                    dynamic_cast<algo::FmIndex*>(_fmIndex),
                                                    kmer,
                                                    ftProps.getMaxOcc(),
                                                    ftProps.getOverCountedFlag()));
                kmerQueue.pop();
            } else {
                break;
            }
        }

        for (auto& e : resultsFutures) {
            //std::cout << "waiting for results future " << std::endl;
            e.wait();
        }

        for (auto& e : resultsFutures) {
            ft::KmerClass tmpResult = e.get();
            elts++;
            //std::cout << "getting results future " << std::endl;

            if (tmpResult.getKPositions().size() > 0)
            {
                addResultsFutures(indexResults,tmpResult, offset);
            }
        }

        j = 0;
        resultsFutures.clear();

        //std::cout << "Kmer Queue size (end) " << kmerQueue.size() << " j " << j << std::endl;
    }
    for (auto& e : resultsFutures) {
        //std::cout << "waiting for results future " << std::endl;
        e.wait();
    }

    for (auto& e : resultsFutures) {
        ft::KmerClass tmpResult = e.get();
        elts++;
        //std::cout << "getting results future " << std::endl;

        if (tmpResult.getKPositions().size() > 0)
        {
            addResultsFutures(indexResults,tmpResult, offset);
        }
    }

    ftMap.addIndexResults(indexResults);

    std::cout << "Finished\n";
}

//======================================================================
void Finder::sequentialSearch(ft::FTMap &ftMap,
                              const fs::path &indexPath, long long offset)
{
    // performs the kmer search for a single index file
    // returns indexPosResults for a single index
    // std::thread::id this_id = std::this_thread::get_id();
    const FTProp& ftProps = ftMap.getFTProps();

    const std::unordered_map<std::string, ft::KmerClass>& kmerMap = ftMap.getKmerSet();

    FTProp::Log  << "working on : " << indexPath.string() << std::endl;
    FTProp::Log  << "kmer Map Size " << kmerMap.size() << std::endl;
    algo::FmIndex _fmIndex;

    std::map<std::string, ft::KmerClass> indexResults;

    try {
        _fmIndex.loadIndexFromFile(fs::absolute(indexPath));
    } catch (std::exception& e) {
        FTProp::Log  << "Error ! " << e.what() << std::endl;
    }
    FTProp::Log  << "index loaded " << _fmIndex.indexCount() << std::endl;
#if 0
    std::string testKmer = "AAT";
    testIndex(ftProps, indexPath, testKmer);
    benchmark.now("SequentialSearch TestIndex DONE ");
#endif

    std::unordered_map<std::string, ft::KmerClass>::const_iterator it = kmerMap.begin();
    while (it != kmerMap.end())
    {
       std::string kmer = it->first;
       //FTProp::Log  << " searching for kmer " << kmer << std::endl;
       ft::KmerClass tmpResult = _fmIndex.search(kmer,
                                                   ftProps.getMaxOcc(),
                                                   ftProps.getOverCountedFlag());
       if (tmpResult.getKPositions().size() > 0)
       {
           addResultsFutures(indexResults,tmpResult, offset);
       }
       //FTProp::Log  << "  number of positions " << tmpResult.getKPositions().size();
       //FTProp::Log  << ", number of kmer hits  " << tmpResult.getKPositions().size() << std::endl;

       it++;
    }

    ftMap.addIndexResults(indexResults);
    FTProp::Log  << "number of indexes processed " << indexResults.size() << std::endl;

    indexResults.clear();
}

//======================================================================
void Finder::overrideFmIndex(std::shared_ptr<algo::IFmIndex> fmIndex)
{
    _fmIndex = fmIndex.get();
}


//======================================================================
Finder::~Finder()
{
}
}
