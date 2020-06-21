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
QueryClass KmerGenerator::genQueryClassKmers(int queryID, std::string querystring, ft::QueryType queryType, SearchType searchType, uint kmerSize, uint overlap,
                                             uint stride, bool kmerCounts, uint maxKmers)
{
    QueryClass tmpQuery;
    tmpQuery._ID = queryID;
    tmpQuery._String = querystring;
    tmpQuery._Type = queryType;

    // generate search queries
    std::set<std::string> searchStrings;
    if (searchType == CENTERED) {
        searchStrings = genCenteredSearchStrings(tmpQuery._String, kmerSize, overlap, stride, kmerCounts, maxKmers);
    } else {

        searchStrings = genSlidingSearchStrings(tmpQuery._String, kmerSize, stride, kmerCounts, maxKmers);
    }

    // add ref search queries to searchKmers map
    if (!searchStrings.empty()) {
        tmpQuery._kmers = searchStrings;
    } else {
        std::cout << "Error during the ID creation !" << std::endl;
    }

    return tmpQuery;
}





//======================================================================
std::set<QueryClass> KmerGenerator::genSearchKmers(std::set<Query> inputQueries, uint kmerSize, bool refOnly, SearchType searchType, uint overlap,
                                          uint stride, bool crossover, bool kmerCounts, uint maxKmers)
{
    std::set<QueryClass> results;
    for (auto inputQuery : inputQueries) {

        //Create Ref Query
        QueryClass tmpRefQuery = genQueryClassKmers(std::get<0>(inputQuery), std::get<1>(inputQuery), ft::QueryType::REF, searchType, kmerSize, overlap,
                                                     stride, kmerCounts, maxKmers);

        //std::cout << "ref Query String " << tmpRefQuery._String << std::endl;

        results.insert(tmpRefQuery);

        // Create Alt Query
        if (!refOnly) {
            QueryClass tmpAltQuery = genQueryClassKmers(std::get<0>(inputQuery), std::get<2>(inputQuery), ft::QueryType::ALT, searchType, kmerSize, overlap,
                                                         stride, kmerCounts, maxKmers);
            //std::cout << "alt Query String " << tmpAltQuery._String << std::endl;
            results.insert(tmpAltQuery);
        }

        // Create Crossover Query
        if (crossover && !tmpRefQuery._String.empty() && !std::get<2>(inputQuery).empty()) {
            if (searchType == CENTERED){
                QueryClass tmpCroQuery = genQueryClassKmers(std::get<0>(inputQuery), std::get<3>(inputQuery), ft::QueryType::CRO, searchType, kmerSize, overlap,
                                                         stride, kmerCounts, maxKmers);
                results.insert(tmpCroQuery);
            } else {
                std::cout << "Crossover feature only works with CENTERED search" << std::endl;
                throw 1;
            }


        }
    }

    return results;
}


//======================================================================
void KmerGenerator::addtoKmerMap(std::set<KmerClass>& kmerMap, const std::set<QueryClass>& queryKmers)
{
    for (auto query : queryKmers) {
        ft::QIdT queryIDT = std::make_pair(query._ID, query._Type);
        std::set<std::string> kmers = query._kmers;
        for (auto kmer : kmers) {
            kmerMap.first.insert(queryIDT);
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
            if (kmerMap[(*it).first].first.size() > 1) {
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
