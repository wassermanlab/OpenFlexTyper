#include "kmergenerator.h"
#include <cmath>

namespace ft {
//======================================================================
KmerGenerator::KmerGenerator(const uint& kmerSize ,
                             const bool& refOnly ,
                             const SearchType& searchType ,
                             const uint& overlap ,
                             const uint& stride,
                             //const bool& kmerCounts,
                             const uint& maxKmers,
                             const bool &verbose)
    : _kmerSize(kmerSize) ,
    _refOnly(refOnly),
    _searchType(searchType),
    _overlap(overlap),
    _stride(stride),
    //_kmerCounts(kmerCounts),
    _maxKmers(maxKmers),
    _verbose(verbose)
{
}

//================= PARAMETER GETTERS ========================
uint KmerGenerator::getKmerSize() const {return _kmerSize;}
bool KmerGenerator::getRefOnly() const {return _refOnly;}
SearchType KmerGenerator::getSearchType() const {return _searchType;}
uint KmerGenerator::getOverlap() const {return _overlap;}
uint KmerGenerator::getStride() const {return _stride;}
//bool KmerGenerator::getKmerCountsFlag() const {return _kmerCounts;}
uint KmerGenerator::getMaxKmers() const {return _maxKmers;}

//======================================================================
std::set<std::string> KmerGenerator::genSlidingSearchStrings(const std::string& queryString)
{


    std::set<std::string> searchStrings;
    if (queryString.length() < _kmerSize)
        return searchStrings;

    uint count = 0;

    for (uint i = 0; i <= queryString.length() - _kmerSize; i += _stride) {
        if (_maxKmers > 0 && count >= _maxKmers)
            break;
        if (queryString == ".") continue;
        std::string searchString = queryString.substr(i, _kmerSize);

        if (!searchString.empty()) {
            _counter[searchString]++;
            searchStrings.insert(searchString);
        }
        count++;
    }
    return searchStrings;
}

//======================================================================
std::set<std::string> KmerGenerator::genCenteredSearchStrings(const std::string& queryString)
{
    std::set<std::string> searchStrings;

    uint count = 0;

    if (queryString.length() < _kmerSize)
        return searchStrings;

    size_t querylen = queryString.length();
    size_t varStart = floor((double(querylen - 1)) / 2);
    size_t varEnd   = ceil ((double(querylen - 1)) / 2);
    size_t start    = varEnd + _overlap - _kmerSize + 1;
    size_t end      = varStart - _overlap;

    if (queryString.empty() || queryString == ".")
        return searchStrings;

    for (size_t i = start; i <= end; i += _stride) {
        if (_maxKmers > 0 && count >= _maxKmers)
            break;
        if (i + _kmerSize < queryString.size()) {
            std::string searchString = queryString.substr(i, _kmerSize);
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
    if (_verbose){
            std::cout << "  " << std::endl;
            std::cout << "  " << std::endl;
            std::cout << "Query String " << queryObj._qstring.substr(0,10) <<std::endl;
            std::cout << "Kmer Size " << _kmerSize << std::endl;
            std::cout << "Ref Only Flag " << _refOnly << std::endl;
            std::cout << "Search Type " << _searchType << std::endl;
            std::cout << "Overlap  " << _overlap << std::endl;
            std::cout << "Stride " << _stride << std::endl;
            //std::cout << "kmer Counts " << _kmerCounts << std::endl;
            std::cout << "MaxKmers  " << _maxKmers << std::endl;

    }


    // generate search queries

    if (_searchType == CENTERED) {
        searchKmers = genCenteredSearchStrings(queryObj._qstring);
    } else if (_searchType == SLIDING) {
        searchKmers = genSlidingSearchStrings(queryObj._qstring);
    } else {
        throw std::runtime_error("Search Type not recognised");
    }
    if (_verbose)
    {
        std::cout << "length of searchKmers " << searchKmers.size() << std::endl;
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
