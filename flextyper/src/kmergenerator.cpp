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
    QueryClass tmpQuery(queryID, queryType);
    tmpQuery.setQueryString(querystring);

    // generate search queries
    std::set<std::string> searchStrings;
    if (searchType == CENTERED) {
        searchStrings = genCenteredSearchStrings(tmpQuery.getQueryString(), kmerSize, overlap, stride, kmerCounts, maxKmers);
    } else {
        searchStrings = genSlidingSearchStrings(tmpQuery.getQueryString(), kmerSize, stride, kmerCounts, maxKmers);
    }

    if (!searchStrings.empty()) {
        tmpQuery.setKmers(searchStrings);
    } else {
        std::cout << "Error during the ID creation !" << std::endl;
    }
    return tmpQuery;
}

//======================================================================
std::set<QueryClass> KmerGenerator::genSearchKmers(std::set<Query>& inputQueries, ft::FTMap& ftMap)
{
    uint kmerSize = ftMap.getKmerSize();
    bool refOnly = ftMap.getRefOnlyFlag();
    ft::SearchType searchType = ftMap.getSearchType();
    uint overlap = ftMap.getOverlap();
    uint stride = ftMap.getStride();
    bool kmerCounts = ftMap.getKmerCountsFlag();
    uint maxKmers = ftMap.getMaxKmers();

    std::set<ft::QueryClass> results;

    for (auto inputQuery : inputQueries) {
        std::string refString = std::get<1>(inputQuery);
        int qID = std::get<0>(inputQuery);

        //Create Ref Query
        ft::QueryClass tmpRefQuery = genQueryClassKmers(qID, refString, ft::QueryType::REF, searchType, kmerSize, overlap,
                                                     stride, kmerCounts, maxKmers);
        results.insert(tmpRefQuery);

        // Create Alt Query
        if (!refOnly) {
            std::string altString = std::get<2>(inputQuery);
            QueryClass tmpAltQuery = genQueryClassKmers(qID, altString, ft::QueryType::ALT, searchType, kmerSize, overlap,
                                                         stride, kmerCounts, maxKmers);
            results.insert(tmpAltQuery);
        }

        // Create Crossover Query
        if (ftMap.getCrossoverFlag() && !tmpRefQuery.getQueryString().empty() && !std::get<2>(inputQuery).empty()) {
            std::string croString = std::get<3>(inputQuery);
            if (searchType == CENTERED){
                QueryClass tmpCroQuery = genQueryClassKmers(qID, croString, ft::QueryType::CRO, searchType, kmerSize, overlap,
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
void KmerGenerator::addQueriestoKmerMap(ft::FTMap& ftMap, const std::set<QueryClass>& queryMap)
{
    for (auto query : queryMap) {
        std::set<std::string> kmers = query.getKmers();
        for (auto kmer : kmers) {
            ftMap.addQIDtoKmer(kmer, query.getqID(), query.getqType());
        }
    }
}

//======================================================================
void KmerGenerator::genKmerMap(std::set<Query>& inputQueries, ft::FTMap& ftMap)
{

    std::set<QueryClass> queryMap = genSearchKmers(inputQueries, ftMap);
    addQueriestoKmerMap(ftMap, queryMap);
    uint maxTotalKmers = ftMap.getMaxTotalKmers();
    std::set<ft::KmerClass> kmerMap = ftMap.getKmerMap();

    if (maxTotalKmers > 0 && kmerMap.size() > maxTotalKmers) {
        kmerMap.clear();
        std::cout << "Error: Too many kmers generated" << std::endl;
//        KmerMap tmp = kmerMap;
//        kmerMap.clear();
//        uint l = 0;
//        for (auto e : tmp) {
//            if (l == maxTotalKmers)
//                break;
//            kmerMap.insert(e);
//            l++;
//        }
    }

    if (ftMap.getIgnoreNonUniqueKmersFlag()) {
        std::cout << "probabilistic search" << std::endl;
        std::cout << "initial size : " << kmerMap.size() << std::endl;
        for (auto it = kmerMap.begin(); it != kmerMap.end();) {
            if ((*it)._queryIDs.size() > 1){
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
