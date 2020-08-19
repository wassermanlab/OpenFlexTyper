#include "finder.h"
#include <future>

namespace ft {
//======================================================================
Finder::Finder()
    : _fmIndex(&_ownedFmIndex)
{
}
//======================================================================
void Finder::searchIndexes(ft::FTMap &ftMap)
{

    int numOfIndexes = ftMap._ftProps.getNumOfIndexes();
    std::cout << "number of indexes " << numOfIndexes << std::endl;

    if (ftMap.getFTProps().getMultithreadFlag()) {
        std::cout << "Parallel Search " << std::endl;
        indexParallelSearch(ftMap);
    } else {
        std::cout << "Sequential Search " << std::endl;
        indexSequentialSearch(ftMap);
    }
}

//======================================================================
void Finder::indexSequentialSearch(FTMap &ftMap)
{
    std::map<fs::path, uint> indexes = ftMap._ftProps.getIndexSet();
    for (std::pair<fs::path, u_int> item : indexes){
        fs::path indexPath = item.first;
        u_int offset = item.second;
        sequentialSearch(ftMap, indexPath, offset);
    }

}

//======================================================================
void Finder::indexParallelSearch(FTMap &ftMap)
{
    std::map<fs::path, uint> indexes = ftMap._ftProps.getIndexSet();
    std::map<fs::path, uint>::iterator it = indexes.begin();
    while ( it != indexes.end()) {
        fs::path indexPath = it->first;
        uint offset = it->second;
        std::cout << "parallel search : " << indexPath << std::endl;
        parallelSearch(ftMap, indexPath, offset);
        it++;
    }
}

//======================================================================
void Finder::addResultsFutures(std::map<ft::Kmer, ft::KmerClass> & indexResults, ft::KmerClass &tmpResult, uint offset)
{
    std::string resultkmer = tmpResult.getKmer();
    //std::cout << "results kmer " << resultkmer << std::endl;
    //std::cout << "number of result kmer positions " << tmpResult.getKPositions().size() << std::endl;
    if (indexResults.count(resultkmer) > 0)
    {
        //std::cout << "Kmer found" << std::endl;

        for (long long pos : tmpResult.getKPositions())
        {
           //std::cout << "Add to existing result" << std::endl;
            ft::KmerClass result = indexResults.find(resultkmer)->second;
            result.addKPosition(pos, offset);
        }
    } else {
        std::cout << "Kmer not found in Index " << std::endl;
        indexResults[resultkmer] = tmpResult;
    }
   //std::cout << "number of index results " << indexResults.size() << std::endl;
}

//======================================================================
void Finder::parallelSearch(FTMap &ftMap, const fs::path &indexPath,
                            long long offset)
{
    FTProp ftProps = ftMap.getFTProps();
    std::cout << "Parallel search of single index" << std::endl;
    algo::FmIndex* _fmIndex = new algo::FmIndex;
    std::unordered_map<ft::Kmer, ft::KmerClass> kmerMap = ftMap._kmerSet;


    std::cout << "working on : " << indexPath << std::endl;
    std::map<ft::Kmer, ft::KmerClass>  indexResults;

    try {
        _fmIndex->loadIndexFromFile(indexPath);
    } catch (std::exception& e) {
        std::cout << "Error ! " << indexPath << " " << e.what() << std::endl;
    }

    // create a vector of futures
    std::vector<std::future<ft::KmerClass>> resultsFutures;
    size_t j = 0;
    size_t k = kmerMap.size();

    // using a queue to easily control the flow of kmers
    std::queue<ft::Kmer> kmerQueue;
    std::unordered_map<ft::Kmer, ft::KmerClass>::iterator it = kmerMap.begin();
    while (it != kmerMap.end())
    {
        std::cout << "kmer add to queue " << it->first << std::endl;
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



    ft::Kmer kmer2 = "AAT";
    csa_wt<wt_huff<rrr_vector<256>>, 512, 1024> _testindex;
    std::cout << fs::current_path() << std::endl;
    sdsl::load_from_file(_testindex, "testOutput/Test.fm9");

    auto occ2 = sdsl::count(_testindex, kmer2.begin(), kmer2.end());
    std::cout << "kmer3 count " << occ2 << std::endl;
    auto locs2 = sdsl::locate(_testindex, kmer2.begin(), kmer2.end());
    std::cout << "kmer3 " << locs2.size() << std::endl;


    while (!kmerQueue.empty()) {
        if (j < ftProps.getMaxThreads()) {

            ft::Kmer kmer = kmerQueue.front();
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
                ft::Kmer kmer = kmerQueue.front();
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

            if (tmpResult._positions.size() > 0)
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

        if (tmpResult._positions.size() > 0)
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
    std::cout << "running sequential search" << std::endl;

    // performs the kmer search for a single index file
    // returns indexPosResults for a single index
    // std::thread::id this_id = std::this_thread::get_id();
    FTProp ftProps = ftMap.getFTProps();

    std::unordered_map<ft::Kmer, ft::KmerClass> kmerMap = ftMap._kmerSet;
    //size_t i = 0;
    std::cout << "working on : " << indexPath << std::endl;
    std::cout << "kmer Map Size " << kmerMap.size() << std::endl;
    algo::FmIndex _fmIndex;

    std::map<ft::Kmer, ft::KmerClass> indexResults;
    try {
        _fmIndex.loadIndexFromFile(indexPath);
    } catch (std::exception& e) {
        std::cout << "Error ! " << indexPath << " " << e.what() << std::endl;
    }

    std::unordered_map<ft::Kmer, ft::KmerClass>::iterator it = kmerMap.begin();
    while (it != kmerMap.end())
    {
       ft::Kmer kmer = it->first;
       std::cout << "searching for kmer " << kmer << std::endl;
       ft::KmerClass tmpResult = _fmIndex.search(kmer,
                                                   ftProps.getMaxOcc(),
                                                   ftProps.getOverCountedFlag());

       std::cout << "number of positions " << tmpResult._positions.size() << std::endl;
       if (tmpResult._positions.size() > 0)
       {
           std::cout << "number of kmer hits  " << tmpResult._positions.size() << std::endl;
           addResultsFutures(indexResults,tmpResult, offset);
       }

       it++;
    }

    ftMap.addIndexResults(indexResults);
    std::cout << "number of indexes processed " << indexResults.size() << std::endl;
    indexResults.clear();
    std::cout << "Finished\n";
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
