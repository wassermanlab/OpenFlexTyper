#include <set>
#include <iostream>
#include <map>
#include "FTMapClass.h"
#include "kmerClass.h"
#include "queryClass.h"
#include "resultsClass.h"

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
ft::KmerClass FTMap::getKmer(std::string kmer)
{

}

//======================================================
ft::QueryClass FTMap::getQuery(ft::QIdT qIDT)
{

}

//======================================================
void FTMap::addKmer(ft::KmerClass kmer)
{

}

//======================================================
void FTMap::addQuery(ft::QueryClass query)
{

}

//======================================================
void FTMap::addQIDtoKmer(std::string kmer, int queryID, ft::QueryType queryIDType)
{

}

//void FTMap::addtmpResults(ft::FTResults tmpResults, uint offset){

//    for (auto queryID_Type : queryID_Types) {
//        for (auto position : tmpResult.first) {
//            indexResults.addIndexResults()  (position + offset);
//            indexResults[queryID_Type].second.insert(tmpResult.second.begin(), tmpResult.second.end());
//        }
//    }

//}

//======================================================
void FTMap::addResults(std::map<ft::QueryClass, std::set<KmerClass>> tmpResults)
{

}



FTMap::~FTMap()
{
}


}
