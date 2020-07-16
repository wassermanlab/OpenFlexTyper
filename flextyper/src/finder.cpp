#include "finder.h"
#include <future>

namespace ft {
//======================================================================
Finder::Finder()
    : _fmIndex(&_ownedFmIndex)
{
}

//======================================================================
void Finder::searchMonoIndex(FTMap &ftMap, const fs::path &indexPath,
                             long long offset)
{
    if (ftMap.getFTProps().getMultithreadFlag()) {
        parallelSearch(ftMap, indexPath, offset);
    } else {
        sequentialSearch(ftMap, indexPath, offset);
    }
}

//======================================================================
void Finder::searchMultipleIndexes(FTMap &ftMap)
{
    if (ftMap.getFTProps().getMultithreadFlag()) {
        multipleIndexesParallelSearch(ftMap);
    } else {
        multipleIndexesSequentialSearch(ftMap);
    }
}

//======================================================================
void Finder::addResultsFutures(std::set<ft::KmerClass> &indexResults, ft::KmerClass &tmpResult, uint offset)
{
    for (auto it = indexResults.begin(); it != indexResults.end();)
    {
        std::string indexkmer = (*it)._kmer;
        std::string resultkmer = tmpResult.getKmer();
        if ( indexkmer.compare(resultkmer)) {
            for (auto pos = tmpResult.getKPositions().begin(); pos !=tmpResult.getKPositions().end();)
            {
                ft::KmerClass result = (*it);
                result.addKPosition((*pos), offset);
            }
        }
    }
}

//======================================================================
void Finder::parallelSearch(FTMap &ftMap, const fs::path &indexPath,
                            long long offset)
{
    FTProp ftProps = ftMap.getFTProps();
    std::cout << "Parallel search of single index" << std::endl;

    std::set<ft::KmerClass> kmerMap = ftMap.getKmerSet();

    size_t i = 1;
    std::cout << "working on : " << indexPath << std::endl;
    std::set<ft::KmerClass> indexResults;

    _fmIndex->setKmerMapSize(kmerMap.size());

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
        kmerQueue.push(kmer);
    }

    std::atomic<int> elts;
    elts = 0;

    while (!kmerQueue.empty()) {
        if (j < ftProps.getMaxThreads()) {
            ft::KmerClass kmer = kmerQueue.front();
            std::cout << "Kmer search launch ! " << kmer._kmer << " j " << j << " k " << k <<" i " << i << std::endl;

            resultsFutures.push_back(std::async(std::launch::async, &algo::FmIndex::search,
                                                dynamic_cast<algo::FmIndex*>(_fmIndex),
                                                        kmer,                                                        
                                                        ftProps.getMaxOcc(),
                                                        i++,
                                                        ftProps.getOverCountedFlag()));
            kmerQueue.pop();
            j++;
            k--;
            continue;
        }

        while (1) {
            if (kmerQueue.size() > 0 && kmerQueue.size() < ftProps.getMaxThreads()) {
                ft::KmerClass kmer = kmerQueue.front();
                resultsFutures.push_back(std::async(std::launch::async, &algo::FmIndex::search,
                                                    dynamic_cast<algo::FmIndex*>(_fmIndex),
                                                    kmer,
                                                    ftProps.getMaxOcc(),
                                                    i++,
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
            addResultsFutures(indexResults,tmpResult, offset);
            elts++;
            }
        j = 0;
    }
        resultsFutures.clear();

    ftMap.addIndexResults(indexResults);
    std::cout << "number of index results " << indexResults.size() << std::endl;
    indexResults.clear();
    std::cout << "Finished\n";
}

//======================================================================
void Finder::multipleIndexesParallelSearch(FTMap &ftMap)
{
    std::cout << "Multi Indexes Parallel Search" << std::endl;
    FTProp ftProps = ftMap.getFTProps();
    /*
     * The application will take a set of paths to indexes
     * The idea is to also have a set of FmIndex objects to be created
     * We will then search inside the indexes one by one.
     * The search of kmers is done in parallel.
     */
    std::set<ft::KmerClass> kmerMap = ftMap.getKmerSet();
    std::map<fs::path, uint> indexes = ftProps.getIndexSet();
    long long curr = 0;

    for (auto [indexPath, offset] : indexes) {
        std::cout << "searching : " << indexPath << std::endl;
        parallelSearch(ftMap, indexPath, offset);
        curr++;
    }
}

//======================================================================
void Finder::sequentialSearch(ft::FTMap &ftMap,
                              const fs::path &indexPath, long long offset)
{
    std::cout << "running search in a single thread" << std::endl;

    // performs the kmer search for a single index file
    // returns indexPosResults for a single index
    // std::thread::id this_id = std::this_thread::get_id();
    FTProp ftProps = ftMap.getFTProps();

    std::set<ft::KmerClass> kmerMap = ftMap.getKmerSet();
    size_t i = 0;
    std::cout << "working on : " << indexPath << std::endl;
    std::cout << "kmer Map Size " << kmerMap.size() << std::endl;
    algo::FmIndex _fmIndex;
    _fmIndex.setKmerMapSize(kmerMap.size());

    std::set<ft::KmerClass> indexResults;


    try {
        _fmIndex.loadIndexFromFile(indexPath);
    } catch (std::exception& e) {
        std::cout << "Error ! " << indexPath << " " << e.what() << std::endl;
    }

    for (ft::KmerClass kmer : kmerMap) {
        std::cout << "searching for kmer " << kmer._kmer << "  i  " << i << std::endl;
        ft::KmerClass tmpResult = _fmIndex.search(kmer,
                                                   ftProps.getMaxOcc(),
                                                   i++,
                                                   ftProps.getOverCountedFlag());

        std::cout << "index search results " << tmpResult._positions.size() << std::endl;

        addResultsFutures(indexResults,tmpResult, offset);
    }

    ftMap.addIndexResults(indexResults);
    std::cout << "number of index results " << indexResults.size() << std::endl;
    indexResults.clear();

    std::cout << "Finished\n";
}

//======================================================================
void Finder::multipleIndexesSequentialSearch(FTMap &ftMap)
{
    std::cout << "Multi Indexes Sequential Search" << std::endl;

    // The application will take a set of paths to indexes
    // The idea is to also have a set of FmIndex objects to be created
    // We will then search inside the indexes one by one.
    // The search of kmers is done sequentially.

    FTProp ftProps = ftMap.getFTProps();
    std::set<ft::KmerClass> kmerMap = ftMap.getKmerSet();
    std::map<fs::path, uint> indexes = ftProps.getIndexSet();
    for (auto [indexPath, offset] : indexes) {
        std::cout << "searching : " << indexPath << std::endl;
        sequentialSearch(ftMap, indexPath, offset);
    }
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
