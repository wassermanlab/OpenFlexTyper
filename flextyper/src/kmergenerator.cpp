
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
std::set<std::string> KmerGenerator::genQueryClassKmers(ft::QueryClass queryObj, SearchType searchType, uint kmerSize, uint overlap,
                                             uint stride, bool kmerCounts, uint maxKmers)
{    
    // generate search queries
    std::set<std::string> searchStrings;
    if (searchType == CENTERED) {
        searchStrings = genCenteredSearchStrings(queryObj.getQueryString(), kmerSize, overlap, stride, kmerCounts, maxKmers);
    } else {
        searchStrings = genSlidingSearchStrings(queryObj.getQueryString(), kmerSize, stride, kmerCounts, maxKmers);
    }

    if (searchStrings.empty()) {
        std::cout << "Error during the ID creation !" << std::endl;
    }
    return searchStrings;
}

//======================================================================
void KmerGenerator::genSearchKmers(std::set<Query>& inputQueries, ft::FTMap& ftMap)
{
    uint kmerSize = ftMap.getKmerSize();
    bool refOnly = ftMap.getRefOnlyFlag();
    ft::SearchType searchType = ftMap.getSearchType();
    uint overlap = ftMap.getOverlap();
    uint stride = ftMap.getStride();
    bool kmerCounts = ftMap.getKmerCountsFlag();
    uint maxKmers = ftMap.getMaxKmers();

    QKMAP _qkMap = ftMap.getQKMap();






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
std::set<std::string> KmerGenerator::genKmers(std::set<ft::QueryClass>& inputQueries, ft::FTMap& ftMap)
{

    ftMap.

    std::set<QueryClass> queryMap = genSearchKmers(inputQueries, ftMap);


    addQueriestoKmerMap(ftMap, queryMap);
    uint maxTotalKmers = ftMap.getMaxTotalKmers();
    std::set<ft::KmerClass> kmerMap = ftMap.getKmerSet();

    if (maxTotalKmers > 0 && kmerMap.size() > maxTotalKmers) {
        kmerMap.clear();
        std::cout << "Error: Too many kmers generated" << std::endl;
    }

    if (ftMap.getIgnoreNonUniqueKmersFlag()) {
        std::cout << "initial size : " << kmerMap.size() << std::endl;
        for (auto it = kmerMap.begin(); it != kmerMap.end();) {
            if ((*it)._queryIDs.size() > 1){
                kmerMap.erase(it++);
            } else {
                ++it;
            }
        }
        std::cout << "final size : " << kmerMap.size() << std::endl;
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
