#include <set>
#include <iostream>
#include <map>
#include <algorithm>
#include "ftMapClass.h"

namespace ft {

FTMap::FTMap(FTProp& ftProps)
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
#define INITSTART {
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
    std::cout << "create kmer generator" << std::endl;
    KmerGenerator  _kmerGenerator(_ftProps.getKmerSize(),
                                  _ftProps.getRefOnlyFlag(),
                                  _ftProps.getSearchType(),
                                  _ftProps.getOverlap(),
                                  _ftProps.getStride(),
                                  _ftProps.getKmerCountsFlag(),
                                  _ftProps.getMaxKmers());

    for (ft::QueryClass query : _querySet ){
        std::set<ft::KmerClass*> kmerObj;
        std::set<std::string> kmers = (_kmerGenerator.genSearchKmers(query));
        std::cout << "generated " << kmers.size() << " kmers " << std::endl;
        for (auto kmer : kmers)
        {
            //std::cout << "add kmer " << kmer << std::endl;
            addKmer(kmer);
            kmerObj.insert(findKmer(kmer));
        }
        ft::QueryClass* queryPointer = findQuery(query.getQIdT());
        _qkMap.addQKSet(queryPointer, kmerObj);
        std::cout << "size of kmer map " << _kmerSet.size() << std::endl;
    }
}

#define INITEND }
//======================================================
//=============== GETTERS & SETTERS ====================
//======================================================
const std::vector<std::set<ft::KmerClass>>& FTMap::getResults(){return _searchResults;}
const FTProp& FTMap::getFTProps(){return _ftProps;}

//======================================================
//================= KMERS ==============================
//======================================================
#define KMERSTART {
bool FTMap::checkForKmer(const std::string &testKmer) const
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
    if ( it != _kmerSet.end())
    {
        return (ft::KmerClass *) &(*it);
    } else {
        return NULL;
    }
}

//======================================================
ft::KmerClass& FTMap::getKmer(const ft::KmerClass& kmerObject)
{
    auto it = std::find_if(std::begin(_kmerSet), std::end(_kmerSet),
        [&] (ft::KmerClass k) {return k.isKmerEqual(kmerObject);});
    return (ft::KmerClass &) (*it);
}

//======================================================
void FTMap::createKmer(const std::string &kmer)
{
    if(!checkForKmer(kmer)){
        ft::KmerClass newkmer(kmer);
        _kmerSet.insert(kmer);
    } else {
        //std::cout << "Kmer not added, kmer already exists" << std::endl;
    }
}


//======================================================
void FTMap::addKmer(const ft::KmerClass& kmer)
{
    if (!checkForKmer(kmer.getKmer())){
        _kmerSet.insert(kmer);
    } else {
        //std::cout << "Kmer not added, kmer already exists" << std::endl;
    }
}

#define KMERSEND }
//======================================================
//================= QUERIES ============================
//======================================================
#define QUERIESSTART {
bool FTMap::checkForQIDT(const ft::QIdT& testQIDTObject) const
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
ft::QueryClass& FTMap::getQuery(const ft::QIdT& qIDT) const
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

//======================================================
void FTMap::createQuery(int queryID, ft::QueryType queryType)
{
    ft::QIdT testQIDT = std::make_pair(queryID, queryType);
    if (checkForQIDT(testQIDT)==false){
        ft::QueryClass newquery(queryID, queryType);
        _querySet.insert(newquery);
    } else {
        std::cout << "Query not added, query already exists" << std::endl;
    }
}
#define QUERIESEND }
//=======================================================
//==================== INDEX ============================
//=======================================================
#define INDEXSTART {

void FTMap::addIndexResults(std::set<ft::KmerClass> indexResults)
{
    _searchResults.push_back(indexResults);
}

void FTMap::addKmerResults(const ft::KmerClass& kmerResult)
{
     //std::cout << "number of read IDs to add " << kmerResult.getReadIDs().size() << std::endl;
     KmerClass* kmer = findKmer(kmerResult.getKmer());

     if (kmer == NULL){
         std::cout << "kmer not found, creating new kmer entry" << std::endl;
         addKmer(kmerResult);

         if (!checkForKmer(kmerResult.getKmer())){
             std::cout << "Error: couldnt add new kmer to FTMap" << std::endl;
         }
     }

     kmer = findKmer(kmerResult.getKmer());
     //std::cout << "number of existing read IDs " << kmer->getReadIDs().size() << std::endl;

     // add read IDs
     for (ft::ReadID resultID : kmerResult.getReadIDs())
     {
         //std::cout << "result ID " << resultID.first << std::endl;
         kmer->addReadID(resultID);
     }

     // add flags
     for (auto flag : kmerResult.getKFlags())
     {
         //std::cout << "result Flag " << flag.first << std::endl;
         kmer->addKFlag(flag.first);
     }

}

void FTMap::processIndexResults(std::set<ft::KmerClass> indexResult)
{
    for (ft::KmerClass kmerResult : indexResult){
       kmerResult.convertPosToReadID(_ftProps.getReadLength(),
                                     _ftProps.getNumOfReads(),
                                     _ftProps.getRevCompFlag());
       addKmerResults(kmerResult);
    }
}
#define INDEXEND }

//======================================================
FTMap::~FTMap(){}

}
