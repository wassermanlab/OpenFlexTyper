#include "finder.h"
#include <future>

namespace ft {
//======================================================================
Finder::Finder()
    : _fmIndex(&_ownedFmIndex)
{
}

//======================================================================
void Finder::searchMonoIndex(FTMap& ftMap, const fs::path& indexPath,
                             const std::string& indexFileLocation, bool parallel, uint threadNumber,
                             bool printSearchTime, long long offset)
{
    if (parallel) {
        parallelSearch(ftMap, indexFileLocation, indexPath, threadNumber, printSearchTime, offset);
    } else {
        sequentialSearch(ftMap, indexFileLocation, indexPath, printSearchTime, offset);
    }
}

//======================================================================
void Finder::searchMultipleIndexes(FTMap& ftMap, const std::set<fs::path>& indexPaths,
                                   const std::string& indexFileLocation, bool parallel, uint threadNumber,
                                   bool printSearchTime, long long offset)
{
    if (parallel) {
        multipleIndexesParallelSearch(ftMap, indexFileLocation, indexPaths, threadNumber, printSearchTime, offset);
    } else {
        multipleIndexesSequentialSearch(ftMap, indexFileLocation, indexPaths, printSearchTime, offset);
    }
}

//======================================================================

void Finder::addResultsFutures(std::set<ft::KmerClass>& indexResults, ft::KmerClass& tmpResult, uint offset)
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
void Finder::parallelSearch(FTMap& ftMap, const fs::path& indexFileLocation,
                            fs::path indexPath, uint threadNumber,
                            bool printSearchTime, long long offset)
{
    std::cout << "running search in a multi thread" << std::endl;
    uint maxOcc = ftMap.getMaxOcc();
    bool flagOverCountedKmers= ftMap.getOverCountedFlag();
    std::set<ft::KmerClass> kmerMap = ftMap.getKmerMap();
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
        if (j < threadNumber) {
            const auto& kmer = kmerQueue.front();
            resultsFutures.push_back(std::async(std::launch::async, &algo::FmIndex::search, dynamic_cast<algo::FmIndex*>(_fmIndex),
                                    kmer,
                                    indexPath.stem().string(),
                                    indexFileLocation.string(),
                                    maxOcc,
                                    i++,
                                    flagOverCountedKmers,
                                    printSearchTime));
            kmerQueue.pop();
            j++;
            k--;
            continue;
        }

        while (1) {
            if (kmerQueue.size() > 0 && kmerQueue.size() < threadNumber) {
                const auto& kmers = kmerQueue.front();
                resultsFutures.push_back(std::async(std::launch::async, &algo::FmIndex::search, dynamic_cast<algo::FmIndex*>(_fmIndex),
                                        kmers,
                                        indexPath.stem().string(),
                                        indexFileLocation,
                                        maxOcc,
                                        i++,
                                        flagOverCountedKmers,
                                        printSearchTime));
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
void Finder::multipleIndexesParallelSearch(FTMap& ftMap, const fs::path& indexFileLocation,
                                           const std::set<fs::path>& indexPath, uint threadNumber,
                                           bool printSearchTime, long long offset)
{
    std::cout << "Multi Indexes Parallel Search" << std::endl;

    /*
     * The application will take a set of paths to indexes
     * The idea is to also have a set of FmIndex objects to be created
     * We will then search inside the indexes one by one.
     * The search of kmers is done in parallel.
     */
    uint maxOcc = ftMap.getMaxOcc();
    bool flagOverCountedKmers= ftMap.getOverCountedFlag();
    std::set<ft::KmerClass> kmerMap = ftMap.getKmerMap();

    long long curr = 0;

    for (auto index : indexPath) {

        std::cout << "searching : " << index << std::endl;

        parallelSearch(ftMap, indexFileLocation, index, threadNumber, printSearchTime, curr * offset);
        curr++;
    }
}


//======================================================================
void Finder::sequentialSearch(ft::FTMap& ftMap,
                              const fs::path& indexFileLocation,
                              fs::path indexPath, bool printSearchTime, long long offset)
{
    std::cout << "running search in a single thread" << std::endl;

    // performs the kmer search for a single index file
    // returns indexPosResults for a single index
    // std::thread::id this_id = std::this_thread::get_id();

    uint maxOcc = ftMap.getMaxOcc();
    bool flagOverCountedKmers= ftMap.getOverCountedFlag();
    std::set<ft::KmerClass> kmerMap = ftMap.getKmerMap();
    size_t i = 0;
    std::cout << "working on : " << indexPath << std::endl;
    _fmIndex->setKmerMapSize(kmerMap.size());

    std::set<ft::KmerClass> indexResults;

    // std::cout << "elements to be processed : " << kmerMap.size() << std::endl;

    try {
        _fmIndex->loadIndexFromFile(indexPath);
        // std::cout << "index " << indexPath << " loaded" << std::endl;
    } catch (std::exception& e) {
        std::cout << "Error ! " << indexPath << " " << e.what() << std::endl;
    }

    for (ft::KmerClass kmer : kmerMap) {
        ft::KmerClass tmpResult = _fmIndex->search(kmer, indexPath.stem().string(),
                                          indexFileLocation, maxOcc, i++,
                                          flagOverCountedKmers, printSearchTime);
        addResultsFutures(indexResults,tmpResult, offset);
    }

    ftMap.addIndexResults(indexResults);

    indexResults.clear();

    std::cout << "Finished\n";
}

//======================================================================
void Finder::multipleIndexesSequentialSearch(FTMap& ftMap, const fs::path& indexFileLocation,
                                             std::set<fs::path> indexPaths, bool printSearchTime, long long offset)
{
    std::cout << "Multi Indexes Sequential Search" << std::endl;

    // The application will take a set of paths to indexes
    // The idea is to also have a set of FmIndex objects to be created
    // We will then search inside the indexes one by one.
    // The search of kmers is done sequentially.

    int curr = 0;

    for (auto indexPath : indexPaths) {
        sequentialSearch(ftMap, indexFileLocation, indexPath, printSearchTime, curr * offset);
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
    // dtor
}
}
