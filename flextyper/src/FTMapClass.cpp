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
                          uint maxTotalKmers)
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
void FTMap::setKmers(std::set<ft::KmerClass>){}
void FTMap::setQueries(std::set<ft::QueryClass>){}
void FTMap::setKmerSize(uint kmerSize){}
void FTMap::setSearchType(ft::SearchType searchType){}
void FTMap::setOverlap(uint overlap){}
void FTMap::setStride(uint stride){}
void FTMap::setMaxKmers(uint maxKmers){}
void FTMap::setMaxTotalKmers(uint maxTotalKmers){}
void FTMap::setMaxOcc(uint maxOcc){}
void FTMap::setReadLength(uint readLength){}

//=============== FLAGS ==============================
bool FTMap::getRefOnlyFlag(){return this->_refOnly;}
bool FTMap::getIgnoreNonUniqueKmersFlag(){return this->_ignoreNonUniqueKmers;}
bool FTMap::getKmerCountsFlag(){return this->_kmerCounts;}
bool FTMap::getCrossoverFlag(){return this->_crossover;}
bool FTMap::getOverCountedFlag(){return this->_overcounted;}

void FTMap::setRefOnlyFlag(bool refOnly){}
void FTMap::setIgnoreNonUniqueKmersFlag(bool ignoreNonUnique){}
void FTMap::setKmerCountsFlag(bool kmerCounts){}
void FTMap::setCrossoverFlag(bool crossover){}
void FTMap::setOverCountedFlag(bool overcounted){}


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
