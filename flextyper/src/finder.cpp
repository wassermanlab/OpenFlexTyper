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
void Finder::searchMultipleIndexes(FTMap &ftMap, const std::set<fs::path> &indexPaths,
                                   long long offset)
{
    if (ftMap.getFTProps().getMultithreadFlag()) {
        multipleIndexesParallelSearch(ftMap, indexPaths, offset);
    } else {
        multipleIndexesSequentialSearch(ftMap, indexPaths, offset);
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
    std::cout << "running search in a multi thread" << std::endl;

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
            resultsFutures.push_back(std::async(std::launch::async, &algo::FmIndex::search,
                                                dynamic_cast<algo::FmIndex*>(_fmIndex),
                                                        kmer,
                                                        indexPath.stem().string(),
                                                        ftProps.getIndexFileLocation().string(),
                                                        ftProps.getMaxOcc(),
                                                        i++,
                                                        ftProps.getOverCountedFlag(),
                                                        ftProps.getPrintSearchTimeFlag()));
            kmerQueue.pop();
            j++;
            k--;
            continue;
        }

        while (1) {
            if (kmerQueue.size() > 0 && kmerQueue.size() < ftProps.getMaxThreads()) {
                ft::KmerClass kmer = kmerQueue.front();
                resultsFutures.push_back(std::async(std::launch::async, &algo::FmIndex::search, dynamic_cast<algo::FmIndex*>(_fmIndex),
                                        kmer,
                                        indexPath.stem().string(),
                                        ftProps.getIndexFileLocation().string(),
                                        ftProps.getMaxOcc(),
                                        i++,
                                        ftProps.getOverCountedFlag(),
                                        ftProps.getPrintSearchTimeFlag()));
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
    indexResults.clear();
    std::cout << "Finished\n";
}

//======================================================================
void Finder::multipleIndexesParallelSearch(FTMap &ftMap,
                                           const std::set<fs::path> &indexPath,  long long offset)
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
    long long curr = 0;

    for (auto index : indexPath) {
        std::cout << "searching : " << index << std::endl;
        parallelSearch(ftMap, index, curr * offset);
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
    _fmIndex->setKmerMapSize(kmerMap.size());

    std::set<ft::KmerClass> indexResults;

    try {
        _fmIndex->loadIndexFromFile(indexPath);
    } catch (std::exception& e) {
        std::cout << "Error ! " << indexPath << " " << e.what() << std::endl;
    }

    for (ft::KmerClass kmer : kmerMap) {
        ft::KmerClass tmpResult = _fmIndex->search(kmer,
                                                   indexPath.stem().string(),
                                                   ftProps.getIndexFileLocation(),
                                                   ftProps.getMaxOcc(),
                                                   i++,
                                                   ftProps.getOverCountedFlag(),
                                                   ftProps.getPrintSearchTimeFlag());
        addResultsFutures(indexResults,tmpResult, offset);
    }

    ftMap.addIndexResults(indexResults);

    indexResults.clear();

    std::cout << "Finished\n";
}

//======================================================================
void Finder::multipleIndexesSequentialSearch(FTMap &ftMap,
                                             const std::set<fs::path> &indexPaths, long long offset)
{
    std::cout << "Multi Indexes Sequential Search" << std::endl;

    // The application will take a set of paths to indexes
    // The idea is to also have a set of FmIndex objects to be created
    // We will then search inside the indexes one by one.
    // The search of kmers is done sequentially.

    int curr = 0;

    for (auto indexPath : indexPaths) {
        sequentialSearch(ftMap, indexPath, curr * offset);
        curr++;
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
