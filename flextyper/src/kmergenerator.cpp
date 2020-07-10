#include "kmergenerator.h"
#include <cmath>

namespace ft {
//======================================================================
KmerGenerator::KmerGenerator(const KmerProperties& _kProperties)
    : _kProps(_kProperties)
{
}

//======================================================================
std::set<std::string> KmerGenerator::genSlidingSearchStrings(const std::string& queryString)
{

    uint kmerSize = _kProps._kmerSize;
    uint stride = _kProps._stride;
    bool kmerCounts = _kProps._kmerCounts;
    uint maxKmers = _kProps._maxKmers;
    std::set<std::string> searchStrings;
    if (queryString.length() < kmerSize)
        return searchStrings;

    uint count = 0;

    for (uint i = 0; i <= queryString.length() - kmerSize; i += stride) {
        if (maxKmers > 0 && count >= maxKmers)
            break;
        if (queryString == ".") continue;
        std::string searchString = queryString.substr(i, kmerSize);
        std::cout << "kmer string  " << searchString << std::endl;
        if (!searchString.empty()) {
            _counter[searchString]++;
            searchStrings.insert(searchString);
        }
        count++;
        // std::cout << "Nominal : Trying : " << queryString << ".substr(" << start << ", " << kmerSize << ");" << std::endl;
    }

    return searchStrings;
}

//======================================================================
std::set<std::string> KmerGenerator::genCenteredSearchStrings(const std::string& queryString)
{
    std::set<std::string> searchStrings;
    uint kmerSize = _kProps._kmerSize;
    uint stride = _kProps._stride;
    bool kmerCounts = _kProps._kmerCounts;
    uint maxKmers = _kProps._maxKmers;
    uint overlap = _kProps._overlap;
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

    return searchStrings;
}


//======================================================================
std::set<std::string> KmerGenerator::genSearchKmers(const ft::QueryClass& queryObj)
{
    std::set<std::string> searchKmers;
    // generate search queries

    if (_kProps._searchType == CENTERED) {
        searchKmers = genCenteredSearchStrings(queryObj._qstring);
    } else {
        searchKmers = genSlidingSearchStrings(queryObj._qstring);
    }

    if (searchKmers.empty()) {
        std::cout << "Error during the ID creation !" << std::endl;
    }

    return searchKmers;
}


//======================================================================
KmerGenerator::~KmerGenerator()
{
}
}
