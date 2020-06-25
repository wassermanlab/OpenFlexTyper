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
std::set<std::string> KmerGenerator::genSearchKmers(ft::QueryClass queryObj)
{

    SearchType searchType = kmerProperties.getSearchType();
    uint kmerSize = kmerProperties.getKmerSize();
    uint overlap = kmerProperties.getOverlap();
    uint stride = kmerProperties.getStride();
    bool kmerCounts = kmerProperties.getKmerCountsFlag();
    uint maxKmers = kmerProperties.getMaxKmers();

    std::set<std::string> searchKmers = genQueryClassKmers(queryObj, searchType, kmerSize, overlap,
                                                 stride, kmerCounts, maxKmers);
//    if (maxTotalKmers > 0 && kmerMap.size() > maxTotalKmers) {
//        kmerMap.clear();
//        std::cout << "Error: Too many kmers generated" << std::endl;
//    }

//    if (ftMap.getIgnoreNonUniqueKmersFlag()) {
//        std::cout << "initial size : " << kmerMap.size() << std::endl;
//        for (auto it = kmerMap.begin(); it != kmerMap.end();) {
//            if ((*it)._queryIDs.size() > 1){
//                kmerMap.erase(it++);
//            } else {
//                ++it;
//            }
//        }
//        std::cout << "final size : " << kmerMap.size() << std::endl;
//    }
    return searchKmers;
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
