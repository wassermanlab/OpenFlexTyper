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
    std::map<fs::path, uint>::iterator it = indexes.begin();
    while ( it != indexes.end()) {
        fs::path indexPath = it->first;
        uint offset = it->second;
        std::cout << "sequential search : " << indexPath << std::endl;
        sequentialSearch(ftMap, indexPath, offset);
        it++;
    }
}

//======================================================================
void Finder::multipleIndexesParallelSearch(FTMap &ftMap)
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
void Finder::addResultsFutures(std::set<ft::KmerClass> &indexResults, ft::KmerClass &tmpResult, uint offset)
{
    std::string resultkmer = tmpResult.getKmer();
    std::cout << "results kmer " << resultkmer << std::endl;
    std::cout << "number of result kmer positions " << tmpResult.getKPositions().size() << std::endl;

    auto it = std::find_if(std::begin(indexResults), std::end(indexResults),
        [&] (const ft::KmerClass& k) {return k.hasKmer(resultkmer);});
    if (it != indexResults.end()) {
        std::cout << "Kmer found" << std::endl;

        for (auto pos : tmpResult.getKPositions())
        {
           //std::cout << "Add to existing result" << std::endl;
            ft::KmerClass result = (*it);
            result.addKPosition(pos, offset);
        }
    }
    else {
        std::cout << "Kmer not found in Index " << std::endl;
        indexResults.insert(tmpResult);
    }
   std::cout << "number of index results " << indexResults.size() << std::endl;
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
    std::queue<ft::Kmer> kmerQueue;
    std::unordered_map<ft::Kmer, ft::KmerClass>::iterator it = kmerMap.begin();
    while (it != kmerMap.end())
    {
        std::cout << "kmer add to queue " << it->first << std::endl;
        kmerQueue.push(it->first);
        it++;
    }

    std::cout << "kmer queue created " << std::endl;
    std::atomic<int> elts;
    elts = 0;

    while (!kmerQueue.empty()) {
        if (j < ftProps.getMaxThreads()) {

            ft::Kmer kmer = kmerQueue.front();
            std::cout << "add kmer future " << kmer << std::endl;
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
                ft::Kmer kmer = kmerQueue.front();
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

    std::unordered_map<ft::Kmer, ft::KmerClass> kmerMap = ftMap._kmerSet;
    //size_t i = 0;
    std::cout << "working on : " << indexPath << std::endl;
    std::cout << "kmer Map Size " << kmerMap.size() << std::endl;
    algo::FmIndex _fmIndex;

    std::set<ft::KmerClass> indexResults;
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
