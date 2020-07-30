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
        multipleIndexesParallelSearch(ftMap);
    } else {
        std::cout << "Sequential Search " << std::endl;
        multipleIndexesSequentialSearch(ftMap);
    }
}

//======================================================================
void Finder::multipleIndexesSequentialSearch(FTMap &ftMap)
{
    std::map<fs::path, uint> indexes = ftMap._ftProps.getIndexSet();
    for (auto [indexPath, offset] : indexes) {
        std::cout << "sequential search : " << indexPath << std::endl;
        sequentialSearch(ftMap, indexPath, offset);
    }
}

//======================================================================
void Finder::multipleIndexesParallelSearch(FTMap &ftMap)
{
    std::map<fs::path, uint> indexes = ftMap._ftProps.getIndexSet();
    for (auto [indexPath, offset] : indexes) {
        std::cout << "parallel search : " << indexPath << std::endl;
        parallelSearch(ftMap, indexPath, offset);
    }
}

//======================================================================
void Finder::addResultsFutures(std::set<ft::KmerClass> &indexResults, ft::KmerClass &tmpResult, uint offset)
{

    std::string resultkmer = tmpResult.getKmer();
    //std::cout << "results kmer " << resultkmer << std::endl;
    //std::cout << "number of result kmer positions " << tmpResult.getKPositions().size() << std::endl;

    auto it = std::find_if(std::begin(indexResults), std::end(indexResults),
        [&] (const ft::KmerClass& k) {return k.hasKmer(resultkmer);});
    if (it != indexResults.end()) {
        //std::cout << "Kmer found" << std::endl;
        for (auto pos = tmpResult.getKPositions().begin(); pos !=tmpResult.getKPositions().end();)
        {
           //std::cout << "Add to existing result" << std::endl;
            ft::KmerClass result = (*it);
            result.addKPosition((*pos), offset);
        }
    }
    else {
        //std::cout << "Kmer not found in Index " << std::endl;
        indexResults.insert(tmpResult);
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
    std::set<ft::KmerClass> kmerMap = ftMap._kmerSet;


    std::cout << "working on : " << indexPath << std::endl;
    std::set<ft::KmerClass> indexResults;

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
    std::queue<ft::KmerClass> kmerQueue;
    for (ft::KmerClass kmer : kmerMap) {
        //std::cout << "kmers " << kmer._kmer << std::endl;
        kmerQueue.push(kmer);
    }

    std::atomic<int> elts;
    elts = 0;

    while (!kmerQueue.empty()) {
        if (j < ftProps.getMaxThreads()) {
            ft::KmerClass kmer = kmerQueue.front();
            resultsFutures.push_back(std::async(std::launch::async, &algo::FmIndex::search,
                                                dynamic_cast<algo::FmIndex*>(_fmIndex),
                                                        kmer,                                                        
                                                        ftProps.getMaxOcc(),
                                                        ftProps.getOverCountedFlag()));
            kmerQueue.pop();
            j++;
            k--;
            continue;
        }
        while (kmerQueue.size() > 0) {
            if (kmerQueue.size() < ftProps.getMaxThreads()) {
                ft::KmerClass kmer = kmerQueue.front();
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
            e.wait();
        }

        for (auto& e : resultsFutures) {
            ft::KmerClass tmpResult = e.get();

            elts++;
            if (tmpResult._positions.size() > 0)
            {
                addResultsFutures(indexResults,tmpResult, offset);
            }
            elts++;
            }
        j = 0;
    }
    resultsFutures.clear();
    ftMap.addIndexResults(indexResults);
    indexResults.clear();
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

    std::set<ft::KmerClass> kmerMap = ftMap._kmerSet;
    size_t i = 0;
    //std::cout << "working on : " << indexPath << std::endl;
    //std::cout << "kmer Map Size " << kmerMap.size() << std::endl;
    algo::FmIndex _fmIndex;

    std::set<ft::KmerClass> indexResults;
    try {
        _fmIndex.loadIndexFromFile(indexPath);
    } catch (std::exception& e) {
        std::cout << "Error ! " << indexPath << " " << e.what() << std::endl;
    }

    for (ft::KmerClass kmer : kmerMap) {
       ft::KmerClass tmpResult = _fmIndex.search(kmer,
                                                   ftProps.getMaxOcc(),
                                                   ftProps.getOverCountedFlag());
       if (tmpResult._positions.size() > 0)
       {
           //std::cout << "number of kmer hits  " << tmpResult._positions.size() << std::endl;
           addResultsFutures(indexResults,tmpResult, offset);
       }
    }

    ftMap.addIndexResults(indexResults);
    //std::cout << "number of indexes processed " << indexResults.size() << std::endl;
    indexResults.clear();
    //std::cout << "Finished\n";
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
