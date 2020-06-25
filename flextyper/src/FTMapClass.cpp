#include <set>
#include <iostream>
#include <map>
#include <algorithm>
#include "FTMapClass.h"

namespace ft {

FTMap::FTMap()
    : _kmerSet(),
      _querySet(),
      _qkMap(),
      _searchResults()
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

KmerProperties FTMap::getKmerProperties(){
    KmerProperties kmerProperties;
    kmerProperties.setKmerSize(this->getKmerSize());
    kmerProperties.setRefOnly(this->getRefOnlyFlag());
    kmerProperties.setSearchType(this->getSearchType());
    kmerProperties.setOverlap(this->getOverlap());
    kmerProperties.setStride(this->getStride());
    kmerProperties.setKmerCountsFlag(this->getKmerCountsFlag());
    kmerProperties.setMaxKmers(this->getMaxKmers());
    return kmerProperties;
}

//======================================================
void FTMap::addInputQueries(std::set<Query> inputQueries){
    for (auto inputQuery : inputQueries) {
        std::string refString = std::get<1>(inputQuery);
        int qID = std::get<0>(inputQuery);

        //Create Ref Query
        ft::QueryClass tmpRefQuery(qID, ft::QueryType::REF);
        tmpRefQuery.setQueryString(refString);
        this->addQuery(tmpRefQuery);

        // Create Alt Query
        if (!this->getRefOnlyFlag()) {
            std::string altString = std::get<2>(inputQuery);
            ft::QueryClass tmpAltQuery(qID, ft::QueryType::ALT);
            tmpAltQuery.setQueryString(altString);
            this->addQuery(tmpAltQuery);
        }

        // Create Crossover Query
        if (this->getCrossoverFlag() && !tmpRefQuery.getQueryString().empty() && !std::get<2>(inputQuery).empty()) {
            std::string croString = std::get<3>(inputQuery);
            ft::QueryClass tmpCroQuery(qID, ft::QueryType::CRO);
            tmpCroQuery.setQueryString(croString);
            this->addQuery(tmpCroQuery);
        }
    }
}

//======================================================
void FTMap::genQKMap(std::set<ft::QueryClass> queries){

    for (ft::QueryClass query : queries){
        std::set<std::string> kmers = (_kmerGenerator->genSearchKmers(query, this->getKmerProperties()));

        //std::set<ft::KmerClass> kmerObjs = getKmerObjFromKmerString(kmers);
        //this->addQKSet(query, kmerObjs);
    }
}

//=============== GETTERS ==============================
std::set<ft::KmerClass> FTMap::getKmerSet(){return this->_kmerSet;}
std::set<ft::QueryClass> FTMap::getQuerySet(){return this->_querySet;}
std::map<ft::QueryClass, std::set<KmerClass>> FTMap::getQKMap(){return this->_qkMap;}
std::vector<std::set<ft::KmerClass>> FTMap::getResults(){return this->_searchResults;}
SearchType FTMap::getSearchType(){return this->_searchType;}
uint FTMap::getKmerSize(){return this->_kmerSize;}
uint FTMap::getOverlap(){return this->_overlap;}
uint FTMap::getStride(){return this->_stride;}
uint FTMap::getMaxKmers(){return this->_maxKmers;}
uint FTMap::getMaxTotalKmers(){return this->_maxTotalKmers;}
uint FTMap::getMaxOcc(){return this->_maxOcc;}
uint FTMap::getReadLength(){return this->_readLen;}

//=============== SETTERS ==============================
void FTMap::setKmers(std::set<ft::KmerClass> kmerSet){if (this->getKmerSet().empty()){_kmerSet = kmerSet;}}
void FTMap::setQueries(std::set<ft::QueryClass> querySet){if (this->getQuerySet().empty()){_querySet = querySet;}}
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
bool FTMap::checkForKmer(ft::KmerClass testKmerObject)
{
    std::set<ft::KmerClass> kmerMap = this->getKmerSet();
    bool result;
    auto it = std::find_if(std::begin(kmerMap), std::end(kmerMap),
        [&] (ft::KmerClass k) {return k.isKmerEqual(testKmerObject);});
    if (it != kmerMap.end())
    {
        result = true;
    } else {
        result = false;
    }
    return result;
}

//======================================================
bool FTMap::checkForQIDT(ft::QIdT testQIDTObject)
{
    std::set<ft::QueryClass> queryMap = this->getQuerySet();
    bool result;
    auto it = std::find_if(std::begin(queryMap), std::end(queryMap),
        [&] (ft::QueryClass k) {return k.isQIdTEqual(testQIDTObject);});
    if (it != queryMap.end())
    {
        result = true;
    } else {
        result = false;
    }
    return result;
}

//======================================================
ft::KmerClass FTMap::findKmer(std::string testkmer)
{
    std::set<ft::KmerClass> kmerMap = this->getKmerSet();
    auto it = std::find_if(std::begin(kmerMap), std::end(kmerMap),
        [&] (ft::KmerClass k) {return k.hasKmer(testkmer);});
    return (*it);
}
//======================================================
ft::KmerClass FTMap::getKmer(ft::KmerClass kmerObject)
{
    std::set<ft::KmerClass> _kmerSet = this->getKmerSet();

    auto it = std::find_if(std::begin(_kmerSet), std::end(_kmerSet),
        [&] (ft::KmerClass k) {return k.isKmerEqual(kmerObject);});
    return (*it);
}

//======================================================
ft::QueryClass FTMap::getQuery(ft::QIdT qIDT)
{
    std::set<ft::QueryClass> queryMap = this->getQuerySet();

    auto it = std::find_if(std::begin(queryMap), std::end(queryMap),
        [&] (ft::QueryClass k) {return k.isQIdTEqual(qIDT);});
    return (*it);
}

//======================================================
void FTMap::addKmer(ft::KmerClass kmer)
{
    if (checkForKmer(kmer)){
        this->_kmerSet.insert(kmer);
    } else {
        std::cout << "Kmer not added, kmer already exists" << std::endl;
    }
}

//======================================================
void FTMap::addQuery(ft::QueryClass query)
{
    ft::QIdT testQIDT = query.getQIdT();
    if (checkForQIDT(testQIDT)==false){
        this->_querySet.insert(query);
    } else {
        std::cout << "Query not added, query already exists" << std::endl;
    }
}

//======================================================
void FTMap::addQIDtoKmer(std::string kmer, int queryID, ft::QueryType queryIDType)
{
    ft::KmerClass _kmer(kmer);
    ft::QIdT qIDT = std::make_pair(queryID, queryIDType);

}

//==================== QKMAP ============================
std::set<ft::QueryClass> FTMap::retrieveQueries(ft::KmerClass){
     std::set<ft::QueryClass> _matchingQueries;
     return _matchingQueries;
}
std::set<ft::KmerClass> FTMap::retrieveKmers(ft::QueryClass){
    std::set<ft::KmerClass> _matchingKmers;
    return _matchingKmers;
}
bool FTMap::checkForMatch(ft::KmerClass, ft::QueryClass){
    return false;
}

void FTMap::addQKPair(ft::QueryClass query, ft::KmerClass kmer){

}

void FTMap::addQKSet(ft::QueryClass query, std::set<ft::KmerClass> kmers){

}


//======================================================
void FTMap::addIndexResults(std::set<ft::KmerClass> indexResults)
{
    this->getResults().push_back(indexResults);
}

//======================================================
void FTMap::processIndexResults(std::set<ft::KmerClass> indexResult, uint readLength)
{
    for (ft::KmerClass kmerResult : indexResult){
       kmerResult.convertPosToReadID(readLength);
    }
    // iterate over results from a single index
    for (ft::KmerClass kmerResult : indexResult){
        std::set<ft::FlagType> kFlags = kmerResult.getKFlags();

//        for (ft::QIdT qIDT : kmerResult.getQueryIDs()){
//            ft::QueryClass query = this->getQuery(qIDT);
//            query.addReadIDs(kmerResult.getReadIDs());
//            for (ft::FlagType flag : kFlags)
//            {
//                query.addFlag(flag, {kmerResult.getKmer()});
//            }
//        }

    }


}

FTMap::~FTMap()
{
}


}
