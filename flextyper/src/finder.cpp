#include "finder.h"
#include <future>

namespace ft {
//======================================================================
Finder::Finder()
    : _fmIndex(&_ownedFmIndex)
{
}

//======================================================================
void Finder::searchMonoIndex(ResultsMap& indexPosResults, const KmerMap &kmerMap, const fs::path& indexPath,
                             const std::string& indexFileLocation, uint maxOccurences, bool parallel, uint threadNumber,
                             bool flagOverCountedKmers, bool printSearchTime)
{
    if (parallel) {
        parallelSearch(indexPosResults, indexFileLocation, kmerMap, indexPath, maxOccurences, threadNumber, flagOverCountedKmers, printSearchTime, 0);
    } else {
        sequentialSearch(indexPosResults, indexFileLocation, kmerMap, indexPath, maxOccurences, flagOverCountedKmers, printSearchTime, 0);
    }
}

//======================================================================
void Finder::searchMultipleIndexes(ResultsMap& indexPosResults, const KmerMap &kmerMap, const std::set<fs::path>& indexPaths,
                                   const std::string& indexFileLocation, uint maxOccurences, bool parallel, uint threadNumber,
                                   bool flagOverCountedKmers, bool printSearchTime, long long offset)
{
    if (parallel) {
        multipleIndexesParallelSearch(indexPosResults, indexFileLocation, kmerMap, indexPaths, maxOccurences, threadNumber, flagOverCountedKmers,
                                      printSearchTime, offset);
    } else {
        multipleIndexesSequentialSearch(indexPosResults, indexFileLocation, kmerMap, indexPaths, maxOccurences, flagOverCountedKmers,
                                        printSearchTime, offset);
    }
}

//======================================================================
void Finder::parallelSearch(ResultsMap& indexPosResults, const fs::path& indexFileLocation, const KmerMap& kmerMap,
                            fs::path indexPath, uint maxOcc, uint threadNumber, bool flagOverCountedKmers,
                            bool printSearchTime, long long offset)
{
    std::cout << "running search in a multi thread" << std::endl;

    size_t i = 1;
    std::cout << "working on : " << indexPath << std::endl;

    _fmIndex->setKmerMapSize(kmerMap.size());

        try {
            _fmIndex->loadIndexFromFile(indexPath);
        } catch (std::exception& e) {
            std::cout << "Error ! " << indexPath << " " << e.what() << std::endl;
        }

    // create a vector of futures
    std::vector<std::future<std::tuple<ResultsFuture, std::set<QIdT>>>> op;
    size_t j = 0;
    size_t k = kmerMap.size();

    // using a queue to easily control the flow of kmers
    std::queue<std::pair<std::string, std::set<QIdT>>> q;
    for (auto& kmer : kmerMap) {
        std::pair<std::string, std::set<QIdT>> kmers = std::make_pair(kmer.first, kmer.second.first);
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
                                    flagOverCountedKmers,
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
                                        flagOverCountedKmers,
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

            auto tmpResultMap = e.get();
            std::set<QIdT> queryID_Types = std::get<1>(tmpResultMap);
            ft::ResultsFuture tmpResult = std::get<0>(tmpResultMap);

            elts++;
            for (auto queryID_Type : queryID_Types) {
                for (auto position : tmpResult.first) {
                    indexPosResults[queryID_Type].first.insert(position + offset);
                    indexPosResults[queryID_Type].second.insert(tmpResult.second.begin(), tmpResult.second.end());

                }
            }
        }

        j = 0;
        op.clear();
    }

    std::cout << "Finished\n";
}

//======================================================================
void Finder::multipleIndexesParallelSearch(ResultsMap& indexPosResults, const fs::path& indexFileLocation, const KmerMap& kmerMap,
                                           const std::set<fs::path>& indexPath, uint maxOcc, uint threadNumber, bool flagOverCountedKmers,
                                           bool printSearchTime, long long offset)
{
    std::cout << "Multi Indexes Parallel Search" << std::endl;

    /*
     * The application will take a set of paths to indexes
     * The idea is to also have a set of FmIndex objects to be created
     * We will then search inside the indexes one by one.
     * The search of kmers is done in parallel.
     */

    ResultsMap tmpResultMap;

    long long curr = 0;

    for (auto e : indexPath) {

        std::cout << "searching : " << e << std::endl;

        parallelSearch(tmpResultMap, indexFileLocation, kmerMap, e, maxOcc, threadNumber, flagOverCountedKmers, printSearchTime, curr * offset);

        /*
        for (auto f : tmpResult) {
            std::cout << "tmpResults " << f.first.first << " " << f.second.size() << " " << std::endl;
            int c = 0;
            for (auto g : f.second) {
                std::cout << g << " ";
                c++;
                if (c == 2)
                    break;
            }
            std::cout << "\n";

        }
        */


        for (auto& queryResults : tmpResultMap) { // or kmers.second

            ft::QIdT queryID_Type = std::get<0>(queryResults);
            Results tmpQueryResult = std::get<1>(queryResults);

            std::set< long long> tmppositions = tmpQueryResult.first;
            std::set<ft::FlagType> tmpflags = tmpQueryResult.second;
            if (indexPosResults.find(queryID_Type) != indexPosResults.end()) {
                for (auto pos : tmppositions) {
                    indexPosResults[queryID_Type].first.insert(pos);
				}
			} else {
                indexPosResults.insert(queryResults);
            }
            indexPosResults[queryID_Type].second.insert(tmpflags.begin(), tmpflags.end());

        }

        /*
        for (auto& g : indexPosResults) {
            std::cout << g.first.first << " : " << g.second.size() << std::endl;
        }
        */
        tmpResultMap.clear();

        curr++;
    }
}

//======================================================================
void Finder::sequentialSearch(ResultsMap& indexPosResults, const fs::path& indexFileLocation, const KmerMap& kmerMap,
                              fs::path indexPath, uint maxOcc, bool flagOverCountedKmers, bool printSearchTime, long long offset)
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

        try {
            _fmIndex->loadIndexFromFile(indexPath);
            // std::cout << "index " << indexPath << " loaded" << std::endl;
        } catch (std::exception& e) {
            std::cout << "Error ! " << indexPath << " " << e.what() << std::endl;
        }

    for (auto kmer : kmerMap) {
        std::pair<std::string, std::set<QIdT>> kmers = std::make_pair(kmer.first, kmer.second.first);

        // tmpResultMap std::tuple<ft::ResultsFuture, std::set<std::pair<int, ft::QueryType>>>
        auto tmpResultMap = _fmIndex->search(kmers.first,
                                          kmers.second,
                                          indexPath.stem().string(),
                                          indexFileLocation,
                                          maxOcc,
                                          i++,
                                          flagOverCountedKmers,
                                          printSearchTime);



        std::set<QIdT> queryID_Types = std::get<1>(tmpResultMap);
        ft::ResultsFuture tmpResult = std::get<0>(tmpResultMap);

        for (auto queryID_Type : queryID_Types) {
            for (auto position : tmpResult.first) {
                indexPosResults[queryID_Type].first.insert(position + offset);
                indexPosResults[queryID_Type].second.insert(tmpResult.second.begin(), tmpResult.second.end());
            }
        }
    }

    std::cout << "Finished\n";
}

//======================================================================
void Finder::multipleIndexesSequentialSearch(ResultsMap& indexPosResults, const fs::path& indexFileLocation, const KmerMap& kmerMap,
                                             std::set<fs::path> indexPath, uint maxOcc, bool flagOverCountedKmers, bool printSearchTime, long long offset)
{
    std::cout << "Multi Indexes Sequential Search" << std::endl;

    // The application will take a set of paths to indexes
    // The idea is to also have a set of FmIndex objects to be created
    // We will then search inside the indexes one by one.
    // The search of kmers is done sequentially.

    ResultsMap tmpResult;
    int curr = 0;

    for (auto e : indexPath) {
        sequentialSearch(tmpResult, indexFileLocation, kmerMap, e, maxOcc, flagOverCountedKmers, printSearchTime, curr * offset);

        for (auto& f : tmpResult) { // or kmers.second
            indexPosResults.insert(f);
        }
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
