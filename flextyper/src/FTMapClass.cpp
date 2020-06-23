#include <set>
#include <iostream>
#include <map>
#include <algorithm>
#include "FTMapClass.h"
#include "kmerClass.h"
#include "queryClass.h"

namespace ft {

FTMap::FTMap()
    : _kmerMap(),
      _queryMap()
{
}

//======================================================
void FTMap::setProperties(uint kmerSize,
                          bool refOnly,
                          SearchType searchType,
                          uint overlap,
                          uint stride,
                          bool crossover,
                          bool ignoreNonUniqueKmers,
                          bool kmerCounts,
                          uint maxKmers,
                          uint maxTotalKmers,
                          bool returnMatchesOnly)
{
    FTMap::setKmerSize(kmerSize);
    FTMap::setSearchType(searchType);
    FTMap::setOverlap(overlap);
    FTMap::setStride(stride);
    FTMap::setMaxKmers(maxKmers);
    FTMap::setMaxTotalKmers(maxTotalKmers);
    FTMap::setRefOnlyFlag(refOnly);
    FTMap::setIgnoreNonUniqueKmersFlag(ignoreNonUniqueKmers);
    FTMap::setKmerCountsFlag(kmerCounts);
    FTMap::setCrossoverFlag(crossover);
    FTMap::setMatchesOnlyFlag(returnMatchesOnly);
}

//=============== GETTERS ==============================
std::set<ft::KmerClass> FTMap::getKmerMap(){return this->_kmerMap;}
std::set<ft::QueryClass> FTMap::getQueryMap(){return this->_queryMap;}
uint FTMap::getKmerSize(){return this->_kmerSize;}
SearchType FTMap::getSearchType(){return this->_searchType;}
uint FTMap::getOverlap(){return this->_overlap;}
uint FTMap::getStride(){return this->_stride;}
uint FTMap::getMaxKmers(){return this->_maxKmers;}
uint FTMap::getMaxTotalKmers(){return this->_maxTotalKmers;}
uint FTMap::getMaxOcc(){return this->_maxOcc;}
uint FTMap::getReadLength(){return this->_readLen;}

//=============== SETTERS ==============================
void FTMap::setKmers(std::set<ft::KmerClass> kmerMap){if (this->getKmerMap().empty()){_kmerMap = kmerMap;}}
void FTMap::setQueries(std::set<ft::QueryClass> queryMap){if (this->getQueryMap().empty()){_queryMap = queryMap;}}
void FTMap::setKmerSize(uint kmerSize){if (kmerSize != this->getKmerSize()){_kmerSize = kmerSize;}}
void FTMap::setSearchType(ft::SearchType searchType){if (searchType != this->getSearchType()){_searchType = searchType;}}
void FTMap::setOverlap(uint overlap){if (overlap != this->getOverlap()){_overlap = overlap;}}
void FTMap::setStride(uint stride){if (stride != this->getStride()){_stride = stride;}}
void FTMap::setMaxKmers(uint maxKmers){if (maxKmers != this->getMaxKmers()){_maxKmers = maxKmers;}}
void FTMap::setMaxTotalKmers(uint maxTotalKmers){if (maxTotalKmers != this->getMaxTotalKmers()){_maxTotalKmers = maxTotalKmers;}}
void FTMap::setMaxOcc(uint maxOcc){if (maxOcc != this->getMaxOcc()){_maxOcc = maxOcc;}}
void FTMap::setReadLength(uint readLength){if (readLength != this->getReadLength()){_readLen = readLength;}}

//=============== FLAGS ==============================
bool FTMap::getRefOnlyFlag(){return this->_refOnly;}
bool FTMap::getIgnoreNonUniqueKmersFlag(){return this->_ignoreNonUniqueKmers;}
bool FTMap::getKmerCountsFlag(){return this->_kmerCounts;}
bool FTMap::getCrossoverFlag(){return this->_crossover;}
bool FTMap::getOverCountedFlag(){return this->_overcounted;}
bool FTMap::getMatchesOnlyFlag(){return this->_matchesOnly;}
void FTMap::setRefOnlyFlag(bool refOnly){if (refOnly != this->getRefOnlyFlag()){ _refOnly = refOnly;}}
void FTMap::setIgnoreNonUniqueKmersFlag(bool ignoreNonUnique){if (ignoreNonUnique != this->getIgnoreNonUniqueKmersFlag()){ _ignoreNonUniqueKmers = ignoreNonUnique;}}
void FTMap::setKmerCountsFlag(bool kmerCounts){if (kmerCounts != this->getKmerCountsFlag()){ _kmerCounts = kmerCounts;}}
void FTMap::setCrossoverFlag(bool crossover){if (crossover != this->getCrossoverFlag()){ _crossover = crossover;}}
void FTMap::setOverCountedFlag(bool overcounted){if (overcounted != this->getOverCountedFlag()){ _overcounted = overcounted;}}
void FTMap::setMatchesOnlyFlag(bool matchesOnly){if (matchesOnly != this->getMatchesOnlyFlag()){ _matchesOnly = matchesOnly;}}


//======================================================
bool FTMap::checkKmer(ft::KmerClass testKmerObject)
{
    std::set<ft::KmerClass> kmerMap = this->getKmerMap();

    auto it = std::find_if(std::begin(kmerMap), std::end(kmerMap),
        [&] (ft::KmerClass k) {return k.isKmerEqual(testKmerObject);});
    if (it != kmerMap.end())
    {
        return true;
    } else {
        return false;
    }
}

//======================================================
bool FTMap::checkQIDT(ft::QIdT testQIDTObject)
{
    std::set<ft::QueryClass> queryMap = this->getQueryMap();

    auto it = std::find_if(std::begin(queryMap), std::end(queryMap),
        [&] (ft::QueryClass k) {return k.isQIdTEqual(testQIDTObject);});
    if (it != queryMap.end())
    {
        return true;
    } else {
        return false;
    }
}

//======================================================
auto FTMap::findKmer(std::string testkmer)
{
    std::set<ft::KmerClass> kmerMap = this->getKmerMap();
    auto it = std::find_if(std::begin(kmerMap), std::end(kmerMap),
        [&] (ft::KmerClass k) {return k.hasKmer(testkmer);});
    return it;
}

//======================================================
ft::QueryClass FTMap::getQuery(ft::QIdT qIDT)
{
    std::set<ft::QueryClass> queryMap = this->getQueryMap();

    auto it = std::find_if(std::begin(queryMap), std::end(queryMap),
        [&] (ft::QueryClass k) {return k.isQIdTEqual(qIDT);});
    return (*it);
}

//======================================================
void FTMap::addKmer(ft::KmerClass kmer)
{
    if (!checkKmer(kmer)){
        this->_kmerMap.insert(kmer);
    } else {
        std::cout << "Kmer not added, kmer already exists" << std::endl;
    }
}

//======================================================
void FTMap::addQuery(ft::QueryClass query)
{
    ft::QIdT testQIDT = query.getQIdT();
    if (!checkQIDT(testQIDT)){
        this->_queryMap.insert(query);
    } else {
        std::cout << "Query not added, query already exists" << std::endl;
    }
}

//======================================================
void FTMap::addQIDtoKmer(std::string kmer, int queryID, ft::QueryType queryIDType)
{
    ft::KmerClass _kmer(kmer);
    ft::QIdT qIDT = std::make_pair(queryID, queryIDType);
    if (checkKmer(_kmer)){
        auto k = findKmer(kmer);
        (*k).addQuery(qIDT);
    } else {
        _kmer.addQuery(qIDT);
        this->addKmer(_kmer);
    }

}

//======================================================
void FTMap::addIndexResults(std::set<ft::KmerClass> indexResults)
{
    // std::map<std::string, std::set<readID>>
// convert index positions to read ids
//    auto r = (size_t) std::ceil(indexPos / (readLength + 1));
// add read ids to queryMap

}

//======================================================
void FTMap::processIndexResults(std::set<ft::KmerClass> indexResult, uint readLength)
{
    for (ft::KmerClass kmerResult : indexResult){
       kmerResult.convertPosToReadID(readLength);
    }

    for (ft::KmerClass kmerResult : indexResult){

    }


}
//    for (auto queryID_Type : queryID_Types) {
//        for (auto position : tmpResult.first) {
//            indexResults.addIndexResults()  (position + offset);
//            indexResults[queryID_Type].second.insert(tmpResult.second.begin(), tmpResult.second.end());
//        }
//    }






FTMap::~FTMap()
{
}


}
