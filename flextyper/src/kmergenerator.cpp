#include "kmergenerator.h"
#include <cmath>

namespace ft {
//======================================================================
KmerGenerator::KmerGenerator()
    : _stats(&_ownedStats)
{
}

//======================================================================
std::set<std::string> KmerGenerator::genSlidingSearchStrings(const std::string& queryString, uint kmerSize, uint stride, bool kmerCounts, uint maxKmers)
{
    std::set<std::string> searchStrings;

    if (queryString.length() < kmerSize)
        return searchStrings;

    uint count = 0;

    for (uint i = 0; i <= queryString.length() - kmerSize; i += stride) {
        if (maxKmers > 0 && count >= maxKmers)
            break;
        if (queryString == ".") continue;
        std::string searchString = queryString.substr(i, kmerSize);
        if (!searchString.empty()) {
            _counter[searchString]++;
            searchStrings.insert(searchString);
        }
        count++;
        // std::cout << "Nominal : Trying : " << queryString << ".substr(" << start << ", " << kmerSize << ");" << std::endl;
    }

    if (kmerCounts) {
        _stats->printKmerCountToFile("kmerCount.log", _counter);
    }

    return searchStrings;
}

//======================================================================
std::set<std::string> KmerGenerator::genCenteredSearchStrings(const std::string& queryString, uint kmerSize, uint overlap, uint stride, bool kmerCounts, uint maxKmers)
{
    std::set<std::string> searchStrings;

    uint count = 0;

    if (queryString.length() < kmerSize)
        return searchStrings;

    size_t querylen = queryString.length();
    size_t varStart = floor((double(querylen - 1)) / 2);
    size_t varEnd   = ceil ((double(querylen - 1)) / 2);
    size_t start    = varEnd + overlap - kmerSize + 1;
    size_t end      = varStart - overlap;

    if (queryString.empty() || queryString == ".")
        return searchStrings;

    for (size_t i = start; i <= end; i += stride) {
        if (maxKmers > 0 && count >= maxKmers)
            break;
        if (i + kmerSize < queryString.size()) {
            std::string searchString = queryString.substr(i, kmerSize);
            _counter[searchString]++;
            searchStrings.insert(searchString);
        }
        count++;
    }

    if (kmerCounts) {
        _stats->printKmerCountToFile("kmerCount.log", _counter);
    }

    return searchStrings;
}

//======================================================================
SearchKmers KmerGenerator::genSearchKmers(std::set<Query> inputQueries, uint kmerSize, bool refOnly, SearchType searchType, uint overlap,
                                          uint stride, bool kmerCounts, uint maxKmers)
{
    SearchKmers results;
    for (auto inputQuery : inputQueries) {

        int queryID                = std::get<0>(inputQuery);
        std::string refQueryString = std::get<1>(inputQuery);
        //std::cout << "ref Query String " << refQueryString << std::endl;

        // generate ref search queries
        std::set<std::string> refSearchStrings;
        if (searchType == CENTERED) {
            refSearchStrings = genCenteredSearchStrings(refQueryString, kmerSize, overlap, stride, kmerCounts, maxKmers);
        } else {
            refSearchStrings = genSlidingSearchStrings(refQueryString, kmerSize, stride, kmerCounts, maxKmers);
        }

        // add ref search queries to searchKmers map
        if (!refSearchStrings.empty()) {
            results[{QueryType::REF, queryID}] = refSearchStrings;
        } else {
            std::cout << "Error during the ID creation !" << std::endl;
        }

        // if refOnly = false, gen alt search queries
        if (!refOnly) {
            std::string altQueryString = std::get<2>(inputQuery);
            //std::cout << "alt Query String " << altQueryString << std::endl;
            std::set<std::string> altSearchStrings;
            if (searchType == CENTERED) {
                altSearchStrings = genCenteredSearchStrings(altQueryString, kmerSize, overlap, stride, kmerCounts, maxKmers);
            } else {
                altSearchStrings = genSlidingSearchStrings(altQueryString, kmerSize, stride, kmerCounts, maxKmers);
            }

            // add alt search queries to searchKmers map
            if (!altSearchStrings.empty()) {
                results[{QueryType::ALT, queryID}] = altSearchStrings;
            } else {
                std::cout << "Error during the ID creation !" << std::endl;
            }
        }
    }

    return results;
}

//======================================================================
SearchKmers KmerGenerator::genQueryKmers(Query inputQuery, uint kmerSize, bool refOnly, SearchType searchType, uint overlap, uint stride, bool crossover, bool kmerCounts, uint maxKmers)
{
    SearchKmers results;

    int queryID                = std::get<0>(inputQuery);
    // std::cout << "QueryID : " << queryID << std::endl;
    std::string refQueryString = std::get<1>(inputQuery);
    //std::cout << "ref Query String " << refQueryString << std::endl;

    /*
    std::cout << "QueryId : " << queryID << std::endl;
    std::cout << "ref     : " << std::get<1>(inputQuery) << std::endl;
    std::cout << "alt     : " << std::get<2>(inputQuery) << std::endl;
    std::cout << "crO     : " << std::get<3>(inputQuery) << std::endl;
    */

    // generate ref search queries
    std::set<std::string> refSearchStrings;
    if (searchType == CENTERED && !refQueryString.empty()) {
        refSearchStrings = genCenteredSearchStrings(refQueryString, kmerSize, overlap, stride, kmerCounts, maxKmers);
    } else if (searchType == SLIDING && !refQueryString.empty()) {
        refSearchStrings = genSlidingSearchStrings(refQueryString, kmerSize, stride, kmerCounts, maxKmers);
    }

    // std::cout << "queryID : " << queryID << std::endl;

    // add ref search queries to searchKmers map
    if (!refSearchStrings.empty()) {
        results[{QueryType::REF, queryID}] = refSearchStrings;
    } else {
        std::cerr << "no ref kmers generated" << std::endl;
    }

    // if refOnly = false, gen alt search queries
    if (!refOnly) {
        std::string altQueryString = std::get<2>(inputQuery);
        // std::cout << "alt Query String " << altQueryString << std::endl;
        std::set<std::string> altSearchStrings;
        if (searchType == CENTERED) {
            altSearchStrings = genCenteredSearchStrings(altQueryString, kmerSize, overlap, stride, kmerCounts, maxKmers);
        } else {
            altSearchStrings = genSlidingSearchStrings(altQueryString, kmerSize, stride, kmerCounts, maxKmers);
        }

        // add alt search queries to searchKmers map
        if (!altSearchStrings.empty()) {
            results[{QueryType::ALT, queryID}] = altSearchStrings;
        } else {
            std::cerr << "no alt kmers generated" << std::endl;
        }

        // if crossover is enabled, then generates crossover data
        std::set<std::string> crossoverStrings;
        if (crossover && !refSearchStrings.empty() && !altSearchStrings.empty()) {
            std::string crossoverQueryString = std::get<3>(inputQuery);
            if (searchType == CENTERED) {
                crossoverStrings = genCenteredSearchStrings(crossoverQueryString, kmerSize, overlap, stride, kmerCounts, maxKmers);
            } else {
                std::cout << "Crossover feature only works with CENTERED search" << std::endl;
                throw 1;
            }

            results[{QueryType::CRO, queryID}] = crossoverStrings;
        }
    }

    /*
    for (auto e : results) {
        std::cout << e.first << std::endl;
        for (auto f : e.second) {
            std::cout << f << std::endl;
        }
    }
    */

    return results;
}

//======================================================================
void KmerGenerator::addtoKmerMap(KmerMap& kmerMap, const SearchKmers& queryKmers)
{
    for (auto query : queryKmers) {
        QueryType queryType = query.first.first;
        int queryID = query.first.second;
        std::set<std::string> kmers = query.second;
        for (auto kmer : kmers) {
            kmerMap[kmer].insert({queryID, queryType});
        }
    }
}

//======================================================================
void KmerGenerator::genKmerMap(std::set<Query>& inputQueries, uint kmerSize, bool refOnly, const SearchType& searchType, KmerMap& kmerMap, uint overlap, uint stride,
                               bool crossover, bool ignoreNonUniqueKmers, bool kmerCounts, uint maxKmers, uint maxTotalKmers)
{
    for (auto query : inputQueries) {
        SearchKmers query_kmers = genQueryKmers(query, kmerSize, refOnly, searchType, overlap, stride, crossover, kmerCounts, maxKmers);
        // std::cout << "kmermap ::: " <<  kmerMap.size() << std::endl;
        addtoKmerMap(kmerMap, query_kmers);
    }

    if (maxTotalKmers > 0 && kmerMap.size() > maxTotalKmers) {
        KmerMap tmp = kmerMap;
        kmerMap.clear();
        uint l = 0;
        for (auto e : tmp) {
            if (l == maxTotalKmers)
                break;
            kmerMap.insert(e);
            l++;
        }
    }

    if (ignoreNonUniqueKmers) {
        std::cout << "probabilistic search" << std::endl;
        std::cout << "initial size : " << kmerMap.size() << std::endl;
        for (auto it = kmerMap.begin(); it != kmerMap.end();) {
            if (kmerMap[(*it).first].size() > 1) {
                // std::cout << "removing  " << (*it).first << std::endl;
                kmerMap.erase(it++);
            } else {
                ++it;
            }
        }
        std::cout << "final   size : " << kmerMap.size() << std::endl;
    }
}

//======================================================================
void KmerGenerator::overrideStats(std::shared_ptr<IStats> stats)
{
    _stats = stats.get();
}

//======================================================================
KmerGenerator::~KmerGenerator()
{
}
}
