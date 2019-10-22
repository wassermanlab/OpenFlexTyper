////////////////////////////////////////////////////////////////////////
///
/// Copyright (c) 2019, Wasserman lab
///
/// FILE        finder.cpp
///
/// DESCRIPTION This file contains the definition of finder class. It contains
///             functions used to search for kmers inside the FmIndex
///
/// Initial version @ Godfrain Jacques Kounkou
///
////////////////////////////////////////////////////////////////////////

#include "finder.h"
#include <future>

namespace ft {
//======================================================================
Finder::Finder()
    : _fmIndex(&_ownedFmIndex)
    , _flag(false)
{
}

//======================================================================
void Finder::searchMonoIndex(ResultsMap& indexPosResults, const KmerMap &kmerMap, const fs::path& indexPath,
                             const std::string& indexFileLocation, uint maxOccurences, bool parallel, uint threadNumber,
                             bool printSearchTime)
{
    if (parallel) {
        parallelSearch(indexPosResults, indexFileLocation, kmerMap, indexPath, maxOccurences, threadNumber, printSearchTime);
    } else {
        sequentialSearch(indexPosResults, indexFileLocation, kmerMap, indexPath, maxOccurences, printSearchTime);
    }
}

//======================================================================
void Finder::searchMultipleIndexes(ResultsMap& indexPosResults, const KmerMap &kmerMap, const std::set<fs::path>& indexPaths,
                                   const std::string& indexFileLocation, uint maxOccurences, bool parallel, uint threadNumber,
                                   bool printSearchTime)
{
    if (parallel) {
        multipleIndexesParallelSearch(indexPosResults, indexFileLocation, kmerMap, indexPaths, maxOccurences, threadNumber,
                                      printSearchTime);
    } else {
        multipleIndexesSequentialSearch(indexPosResults, indexFileLocation, kmerMap, indexPaths, maxOccurences,
                                        printSearchTime);
    }
}

//======================================================================
void Finder::parallelSearch(ResultsMap& indexPosResults, const fs::path& indexFileLocation, const KmerMap& kmerMap,
                            fs::path indexPath, uint maxOcc, uint threadNumber,
                            bool printSearchTime)
{
    std::cout << "running search in a multi thread" << std::endl;

    size_t i = 1;
    std::cout << "working on : " << indexPath << std::endl;

    _fmIndex->setKmerMapSize(kmerMap.size());

    if (!_flag) {
        try {
            _fmIndex->loadIndexFromFile(indexPath);
        } catch (std::exception& e) {
            std::cout << "Error ! " << indexPath << " " << e.what() << std::endl;
        }
        _flag = true;
    }

    // create a vector of futures
    std::vector<std::future<std::tuple<std::set<size_t>, std::set<std::pair<int, QueryType>>>>> op;
    size_t j = 0;
    size_t k = kmerMap.size();

    // using a queue to easily control the flow of kmers
    std::queue<std::pair<std::string, std::set<std::pair<int, QueryType>>>> q;
    for (auto& kmers : kmerMap) {
        q.push(kmers);
    }

    std::atomic<int> elts;
    elts = 0;

    while (!q.empty()) {
        if (j < threadNumber) {
            const auto& kmers = q.front();
            op.push_back(std::async(std::launch::async, &algo::FmIndex::search, dynamic_cast<algo::FmIndex*>(_fmIndex),
                                    kmers.first,
                                    kmers.second,
                                    indexPath.stem().string(),
                                    indexFileLocation.string(),
                                    maxOcc,
                                    i++,
                                    printSearchTime));
            q.pop();
            j++;
            k--;
            continue;
        }

        while (1) {
            if (q.size() > 0 && q.size() < threadNumber) {
                const auto& kmers = q.front();
                op.push_back(std::async(std::launch::async, &algo::FmIndex::search, dynamic_cast<algo::FmIndex*>(_fmIndex),
                                        kmers.first,
                                        kmers.second,
                                        indexPath.stem().string(),
                                        indexFileLocation,
                                        maxOcc,
                                        i++,
                                        printSearchTime));
                q.pop();
            } else {
                break;
            }
        }

        for (auto& e : op) {
            e.wait();
        }

        for (auto& e : op) {
            auto tmpResult = e.get();
            elts++;
            for (auto e : std::get<1>(tmpResult)) {
                for (auto f : std::get<0>(tmpResult)) {
                    indexPosResults[e].insert(f);
                }
            }
        }

        j = 0;
        op.clear();
    }


    std::cout << "Finished\n";
}

//======================================================================
void Finder::multipleIndexesParallelSearch(ResultsMap &indexPosResults, const fs::path& indexFileLocation, const KmerMap& kmerMap,
                                           const std::set<fs::path>& indexPath, uint maxOcc, uint threadNumber,
                                           bool printSearchTime)
{
    std::cout << "Multi Indexes Parallel Search" << std::endl;

    /*
     * The application will take a set of paths to indexes
     * The idea is to also have a set of FmIndex objects to be created
     * We will then search inside the indexes one by one.
     * The search of kmers is done in parallel.
     */

    ResultsMap tmpResult;

    for (auto e : indexPath) {
        parallelSearch(tmpResult, indexFileLocation, kmerMap, e, maxOcc, threadNumber, printSearchTime);

        for (auto& f : tmpResult) { // or kmers.second
            indexPosResults.insert(f);
        }
    }
}

//======================================================================
void Finder::sequentialSearch(ResultsMap& indexPosResults, const fs::path& indexFileLocation, const KmerMap& kmerMap,
                              fs::path indexPath, uint maxOcc, bool printSearchTime)
{
    std::cout << "running search in a single thread" << std::endl;

    // performs the kmer search for a single index file
    // returns indexPosResults for a single index
    // std::thread::id this_id = std::this_thread::get_id();

    // ResultsMap indexPosResults;
    size_t i = 0;
    std::cout << "working on : " << indexPath << std::endl;
    _fmIndex->setKmerMapSize(kmerMap.size());

    // std::cout << "elements to be processed : " << kmerMap.size() << std::endl;

    if (!_flag) {
        try {
            _fmIndex->loadIndexFromFile(indexPath);
            // std::cout << "index " << indexPath << " loaded" << std::endl;
        } catch (std::exception& e) {
            std::cout << "Error ! " << indexPath << " " << e.what() << std::endl;
        }
        _flag = true;
    }

    for (auto kmers : kmerMap) {
        auto tmpResult = _fmIndex->search(kmers.first,
                                          kmers.second,
                                          indexPath.stem().string(),
                                          indexFileLocation,
                                          maxOcc,
                                          i++,
                                          printSearchTime);

        for (auto e : kmers.second) {
            for (auto f : std::get<0>(tmpResult)) {
                indexPosResults[e].insert(f);
            }
        }
    }

    std::cout << "Finished\n";
}

//======================================================================
void Finder::multipleIndexesSequentialSearch(ResultsMap& indexPosResults, const fs::path& indexFileLocation, const KmerMap& kmerMap,
                                             std::set<fs::path> indexPath, uint maxOcc, bool printSearchTime)
{
    std::cout << "Multi Indexes Sequential Search" << std::endl;

    // The application will take a set of paths to indexes
    // The idea is to also have a set of FmIndex objects to be created
    // We will then search inside the indexes one by one.
    // The search of kmers is done sequentially.

    ResultsMap tmpResult;

    for (auto e : indexPath) {
        sequentialSearch(tmpResult, indexFileLocation, kmerMap, e, maxOcc, printSearchTime);

        for (auto& f : tmpResult) { // or kmers.second
            indexPosResults.insert(f);
        }
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
