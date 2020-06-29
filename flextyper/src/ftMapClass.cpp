#include <set>
#include <iostream>
#include <map>
#include <algorithm>
#include "ftMapClass.h"

namespace ft {

FTMap::FTMap(FTProp ftProps)
    : _ftProps(ftProps),
      _kmerSet(),
      _querySet(),
      _qkMap(),
      _searchResults()
{
}

//======================================================
KmerProperties* FTMap::genKProps(){
    ft::KmerProperties* _kProps = new KmerProperties();
    _kProps->setKmerSize(_ftProps.getKmerSize());
    _kProps->setRefOnly(_ftProps.getRefOnlyFlag());
    _kProps->setSearchType(_ftProps.getSearchType());
    _kProps->setOverlap(_ftProps.getOverlap());
    _kProps->setKmerCountsFlag(_ftProps.getKmerCountsFlag());
    _kProps->setMaxKmers(_ftProps.getMaxKmers());
    return _kProps;
}

//======================================================
void FTMap::addInputQueries(const std::set<Query> &inputQueries){

    for (auto inputQuery : inputQueries) {
        std::string refString = std::get<1>(inputQuery);
        int qID = std::get<0>(inputQuery);

        //Create Ref Query
        ft::QueryClass *tmpRefQuery = new ft::QueryClass(qID, ft::QueryType::REF);
        tmpRefQuery->setQueryString(refString);
        this->addQuery(*tmpRefQuery);

        // Create Alt Query
        if (!_ftProps.getRefOnlyFlag()) {
            std::string altString = std::get<2>(inputQuery);
            ft::QueryClass *tmpAltQuery = new ft::QueryClass(qID, ft::QueryType::ALT);
            tmpAltQuery->setQueryString(altString);
            this->addQuery(*tmpAltQuery);
        }

        // Create Crossover Query
        if (_ftProps.getCrossoverFlag() && !tmpRefQuery->getQueryString().empty() && !std::get<2>(inputQuery).empty()) {
            std::string croString = std::get<3>(inputQuery);
            ft::QueryClass *tmpCroQuery= new ft::QueryClass(qID, ft::QueryType::CRO);
            tmpCroQuery->setQueryString(croString);
            this->addQuery(*tmpCroQuery);
        }
    }
}

//======================================================
void FTMap::genQKMap(const std::set<ft::QueryClass>& queries){

    KmerProperties* _kProps = genKProps();
    KmerGenerator  _kmerGenerator(*_kProps);
    for (const ft::QueryClass& query : queries){
        std::set<std::string> kmers = (_kmerGenerator.genSearchKmers(query));

        //std::set<ft::KmerClass> kmerObjs = getKmerObjFromKmerString(kmers);
        //this->addQKSet(query, kmerObjs);
    }
}

//=============== GETTERS ==============================
std::set<ft::KmerClass>* FTMap::getKmerSet(){return &(this->_kmerSet);}
std::set<ft::QueryClass>* FTMap::getQuerySet(){return &(this->_querySet);}
std::map<ft::QueryClass*, std::set<KmerClass*>> FTMap::getQKMap(){return this->_qkMap;}
std::vector<std::set<ft::KmerClass>> FTMap::getResults(){return this->_searchResults;}
FTProp FTMap::getFTProps(){return this->_ftProps;}

//=============== SETTERS ==============================
void FTMap::setKmers(std::set<ft::KmerClass> kmerSet){if (this->_kmerSet.empty()){_kmerSet = kmerSet;}}
void FTMap::setQueries(std::set<ft::QueryClass> querySet){if (this->_querySet.empty()){_querySet = querySet;}}

//======================================================
bool FTMap::checkForKmer(ft::KmerClass testKmerObject)
{
    std::set<ft::KmerClass> *kmerSet = this->getKmerSet();
    bool result;
    auto it = std::find_if(std::begin(*kmerSet), std::end(*kmerSet),
        [&] (ft::KmerClass k) {return k.isKmerEqual(testKmerObject);});
    if (it != kmerSet->end())
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
    std::set<ft::QueryClass> *querySet = this->getQuerySet();
    bool result;
    auto it = std::find_if(std::begin(*querySet ), std::end(*querySet ),
        [&] (ft::QueryClass k) {return k.isQIdTEqual(testQIDTObject);});
    if (it != querySet->end())
    {
        result = true;
    } else {
        result = false;
    }
    return result;
}

//======================================================
ft::KmerClass* FTMap::findKmer(std::string testkmer)
{
    std::set<ft::KmerClass>* kmerSet = this->getKmerSet();
    auto it = std::find_if(std::begin(*kmerSet), std::end(*kmerSet),
        [&] (ft::KmerClass k) {return k.hasKmer(testkmer);});
    return &(*it);
}

//======================================================
ft::KmerClass* FTMap::getKmer(ft::KmerClass kmerObject)
{
    std::set<ft::KmerClass>* _kmerSet = this->getKmerSet();

    auto it = std::find_if(std::begin(*_kmerSet), std::end(*_kmerSet),
        [&] (ft::KmerClass k) {return k.isKmerEqual(kmerObject);});
    return it;
}

//======================================================
ft::QueryClass* FTMap::getQuery(ft::QIdT qIDT)
{
    std::set<ft::QueryClass>* querySet = this->getQuerySet();

    std::set<ft::QueryClass>::iterator it = std::find_if(std::begin(*querySet), std::end(*querySet),
        [&] (ft::QueryClass q) {return q.isQIdTEqual(qIDT);});

    return &(*it);
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
    ft::QIdT testQIDT = std::make_pair(query._qID, query._qType);
    if (this->checkForQIDT(testQIDT)==false){
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
std::set<ft::QueryClass>* FTMap::retrieveQueries(ft::KmerClass *kmer){
     std::set<ft::QueryClass>* _matchingQueries;
     return _matchingQueries;
}
std::set<ft::KmerClass>* FTMap::retrieveKmers(ft::QueryClass *query){
    std::set<ft::KmerClass>* _matchingKmers;
    return _matchingKmers;
}
bool FTMap::checkForMatch(ft::KmerClass *kmer, ft::QueryClass *query){
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

//======================================================
FTMap::~FTMap()
{
}

}
