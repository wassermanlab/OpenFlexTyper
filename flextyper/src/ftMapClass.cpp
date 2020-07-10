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
//================== INIT ==============================
//======================================================
void FTMap::addInputQueries(const std::set<Query> &inputQueries){
    for (auto inputQuery : inputQueries) {
        std::string refString = std::get<1>(inputQuery);
        int qID = std::get<0>(inputQuery);

        //Create Ref Query
        ft::QueryClass *tmpRefQuery = new ft::QueryClass(qID, ft::QueryType::REF);
        tmpRefQuery->setQueryString(refString);
        addQuery(*tmpRefQuery);

        // Create Alt Query
        if (!_ftProps.getRefOnlyFlag()) {
            std::string altString = std::get<2>(inputQuery);
            ft::QueryClass *tmpAltQuery = new ft::QueryClass(qID, ft::QueryType::ALT);
            tmpAltQuery->setQueryString(altString);
            addQuery(*tmpAltQuery);
        }

        // Create Crossover Query
        if (_ftProps.getCrossoverFlag() && !tmpRefQuery->getQueryString().empty() && !std::get<2>(inputQuery).empty()) {
            std::string croString = std::get<3>(inputQuery);
            ft::QueryClass *tmpCroQuery= new ft::QueryClass(qID, ft::QueryType::CRO);
            tmpCroQuery->setQueryString(croString);
            addQuery(*tmpCroQuery);
        }
    }
}
//======================================================
void FTMap::genQKMap()
{
    std::cout << "generate QK Map" << std::endl;
    // causes a seg fault when trying to create KProps
    KmerProperties _kProps(_ftProps);
    std::cout << "create kmer generator" << std::endl;
    KmerGenerator  _kmerGenerator(_kProps);
    for (const ft::QueryClass& query : _querySet ){
        std::set<ft::KmerClass*> kmerObj;
        std::set<std::string> kmers = (_kmerGenerator.genSearchKmers(query));
        for (auto kmer : kmers)
        {
            std::cout << "add kmer " << kmer << std::endl;
            //addKmer(kmer);
            //kmerObj.insert(findKmer(kmer));
        }
        //addQKSet(query, kmerObj);
    }
}

//======================================================
//=============== GETTERS ==============================
//======================================================
const std::set<ft::KmerClass>& FTMap::getKmerSet(){return _kmerSet;}
const std::set<ft::QueryClass>& FTMap::getQuerySet(){return _querySet;}
const std::map<ft::QueryClass*, std::set<KmerClass*>>& FTMap::getQKMap(){return _qkMap;}
const std::vector<std::set<ft::KmerClass>>& FTMap::getResults(){return _searchResults;}
const FTProp& FTMap::getFTProps(){return _ftProps;}

//======================================================
//=============== SETTERS ==============================
//======================================================
void FTMap::setKmers(std::set<ft::KmerClass> kmerSet){if (_kmerSet.empty()){_kmerSet = kmerSet;}}
void FTMap::setQueries(std::set<ft::QueryClass> querySet){if (_querySet.empty()){_querySet = querySet;}}

//======================================================
//================= KMERS ==============================
//======================================================
bool FTMap::checkForKmer(const std::string &testKmer)
{
    auto it = std::find_if(std::begin(_kmerSet), std::end(_kmerSet),
        [&] (const ft::KmerClass& k) {return k.hasKmer(testKmer);});
    if (it != _kmerSet.end()) {
        //std::cout << "Kmer found" << std::endl;
        return true;
    }
    else {
        //std::cout << "Kmer not found" << std::endl;
        return false;
    }
}

//======================================================
ft::KmerClass* FTMap::findKmer(const std::string& testkmer)
{
    auto it = std::find_if(std::begin(_kmerSet), std::end(_kmerSet),
        [&] (ft::KmerClass k) {return k.hasKmer(testkmer);});
    return (ft::KmerClass *) &(*it);
}

//======================================================
ft::KmerClass& FTMap::getKmer(const ft::KmerClass& kmerObject)
{
    auto it = std::find_if(std::begin(_kmerSet), std::end(_kmerSet),
        [&] (ft::KmerClass k) {return k.isKmerEqual(kmerObject);});
    return (ft::KmerClass &) (*it);
}

//======================================================
void FTMap::addKmer(const ft::KmerClass& kmer)
{
    if (!checkForKmer(kmer.getKmer())){
        _kmerSet.insert(kmer);
    } else {
        std::cout << "Kmer not added, kmer already exists" << std::endl;
    }
}

//======================================================
//================= QUERIES ============================
//======================================================
bool FTMap::checkForQIDT(const ft::QIdT& testQIDTObject)
{
    auto it = std::find_if(std::begin(_querySet ), std::end(_querySet ),
        [&] (ft::QueryClass k) {return k.isQIdTEqual(testQIDTObject);});
    if (it != _querySet.end()){ return true;}
    else { return false; }
}
//======================================================
ft::QueryClass* FTMap::findQuery(const ft::QIdT& qIDT)
{
    std::set<ft::QueryClass>::iterator it = std::find_if(std::begin(_querySet), std::end(_querySet),
      [&] (ft::QueryClass q) {return q.isQIdTEqual(qIDT);});
    return (ft::QueryClass *) &(*it);
}
//======================================================
ft::QueryClass& FTMap::getQuery(const ft::QIdT& qIDT)
{
    std::set<ft::QueryClass>::iterator it = std::find_if(std::begin(_querySet), std::end(_querySet),
      [&] (ft::QueryClass q) {return q.isQIdTEqual(qIDT);});
    return (ft::QueryClass &) (*it);
}
//======================================================
void FTMap::addQuery(const ft::QueryClass& query)
{
    ft::QIdT testQIDT = std::make_pair(query._qID, query._qType);
    if (checkForQIDT(testQIDT)==false){
        _querySet.insert(query);
    } else {
        std::cout << "Query not added, query already exists" << std::endl;
    }
}

//=======================================================
//==================== QKMAP ============================
//=======================================================
std::set<ft::QueryClass*> FTMap::retrieveQueries(const ft::KmerClass& kmer)
{
    std::set<ft::QueryClass*> _matchingQueries;
     for (auto qk : _qkMap){
         auto it = std::find_if(std::begin(qk.second), std::end(qk.second),
             [&] (const ft::KmerClass* k) {return k->isKmerEqual(kmer);});
         if (it != qk.second.end()) {_matchingQueries.insert(qk.first);}
     }
     return _matchingQueries;
}
//=======================================================
std::set<ft::KmerClass*> FTMap::retrieveKmers(ft::QueryClass* query){
    return _qkMap[query];
}
//=======================================================
bool FTMap::checkForMatch(ft::QueryClass *query, const ft::KmerClass& kmer){

    auto it = std::find_if(std::begin(_qkMap[query]), std::end(_qkMap[query]),
        [&] (const ft::KmerClass* k) {return k->isKmerEqual(kmer);});
    if (it != _qkMap[query].end()) {return true;}
    else {return false;}
}
//=======================================================
void FTMap::addQKPair(ft::QueryClass* query, ft::KmerClass* kmer){
    _qkMap[query].insert(kmer);

}
//=======================================================
void FTMap::addQKSet(ft::QueryClass* query, std::set<ft::KmerClass*> kmers){

    for (auto kmer: kmers){
        _qkMap[query].insert(kmer);
    }

}

//=======================================================
//==================== INDEX ============================
//=======================================================
void FTMap::addIndexResults(std::set<ft::KmerClass> indexResults)
{    _searchResults.push_back(indexResults); }

void FTMap::processIndexResults(std::set<ft::KmerClass> indexResult, uint readLength)
{
    for (ft::KmerClass kmerResult : indexResult){
       kmerResult.convertPosToReadID(readLength);
    }
    // iterate over results from a single index
    for (ft::KmerClass kmerResult : indexResult){
       // add positions and flags from each Kmer to the QKMAP
    }
}

//======================================================
FTMap::~FTMap(){}

}
