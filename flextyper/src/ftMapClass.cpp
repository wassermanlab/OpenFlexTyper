#include <set>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include "ftMapClass.h"


namespace ft {

const std::string empty = std::string();

FTMap::FTMap(const FTProp& ftProps)
    : _ftProps(ftProps),
      _kmerSet(),
      _querySet(),
      _qkMap(),
      _qkRCMap(),
      _searchResults()
{
}
//======================================================
//================== INIT ==============================
//======================================================
#define INITSTART {
void FTMap::addInputQueries(const std::set<Query> &inputQueries){

    LogClass::Benchmark benchmark;

    for (auto inputQuery : inputQueries) {
        std::string refString = std::get<1>(inputQuery);
        int qID = std::get<0>(inputQuery);

        //Create Ref Query
        addQuery(qID, ft::QueryType::REF, refString);

        // Create Alt Query
        if (!_ftProps.getRefOnlyFlag()) {
            std::string altString = std::get<2>(inputQuery);
            addQuery(qID, ft::QueryType::ALT, altString);
        }

        // Create Crossover Query
        if (_ftProps.getCrossoverFlag() && !std::get<1>(inputQuery).empty() && !std::get<2>(inputQuery).empty()) {
            std::string croString = std::get<3>(inputQuery);
            addQuery(qID, ft::QueryType::CRO, croString);
        }
    }
    benchmark.now("Retrieve Input Queries " + _ftProps.getPathToQueryFile().string() + " DONE ");
}
//======================================================
void FTMap::genQKMap()
{
    LogClass::Benchmark benchmark;

    KmerGenerator  _kmerGenerator(_ftProps.getKmerSize(),
                                  _ftProps.getRefOnlyFlag(),
                                  _ftProps.getSearchType(),
                                  _ftProps.getOverlap(),
                                  _ftProps.getStride(),
                                  //_ftProps.getKmerCountsFlag(),
                                  _ftProps.getMaxKmersPerQuery(),
                                  _ftProps.isVerbose());

    std::map<ft::QIdT, ft::QueryClass>::iterator it = _querySet.begin();
    ft::Utils _utils;
    while (it != _querySet.end()){
        ft::QueryClass query = it->second;
        std::set<std::string> kmers = (_kmerGenerator.genSearchKmers(query));

        _ftProps.printToStdOut( "generated " + std::to_string(kmers.size()) + " kmers " );

        for (std::string kmer : kmers)
        {
            if (_kmerSet.count(kmer)>0){
                findKmer(kmer)->addKFlag(ft::FlagType::NUK);
            } else {
                createKmer(kmer);
            }
            _qkMap.addQKPair(it->first, kmer);
        }

        if (_ftProps.getRevCompSearchFlag()){
            std::set<std::string> rckmers;
            for (std::string kmer : kmers)
            {
                std::string rckmer = _utils.reverseComplement(kmer);
                if (_kmerSet.count(rckmer) > 0){
                    findKmer(rckmer)->addKFlag(ft::FlagType::NUK);
                } else {
                    createKmer(rckmer);
                }
                _qkRCMap.addQKPair(it->first, rckmer);
            }       
        }
        it++;
    }
    benchmark.now("Generate QKMap DONE ");
}

#define INITEND }
//======================================================
//=============== GETTERS & SETTERS ====================
//======================================================
const std::vector<std::map<std::string, ft::KmerClass>>& FTMap::getResults(){return _searchResults;}
const FTProp& FTMap::getFTProps() const {return _ftProps;}
const std::unordered_map<std::string, ft::KmerClass>& FTMap::getKmerSet() const {return _kmerSet;}

//======================================================
//================= KMERS ==============================
//======================================================
#define KMERSTART {
bool FTMap::checkForKmer(const std::string &testKmer) const
{
    return (_kmerSet.count(testKmer) > 0);
}

//======================================================
ft::KmerClass* FTMap::findKmer(const std::string& testKmer)
{
    std::unordered_map<std::string, ft::KmerClass>::iterator it = _kmerSet.find(testKmer);
    if (it != _kmerSet.end()) {
        return  &((*it).second);
    } else {return NULL;}
}

//======================================================
const ft::KmerClass& FTMap::getKmer(const std::string& kmerString) const
{
    if (_kmerSet.count(kmerString) == 0) {
        LogClass::ThrowRuntimeError("Kmer Doesnt Exist");
    }
    return  _kmerSet.find(kmerString)->second;
}
//======================================================
void FTMap::addKmer(const std::string &kmer)
{
    if(!checkForKmer(kmer)){
        createKmer(kmer);
    }
}

//======================================================
void FTMap::createKmer(const std::string &kmer)
{
    ft::KmerClass newkmer(kmer);
    _kmerSet[kmer] = newkmer;
}

#define KMERSEND }
//======================================================
//================= QUERIES ============================
//======================================================
#define QUERIESSTART {
bool FTMap::checkForQIDT(const ft::QIdT& testQIDTObject) const
{
    return (_querySet.count(testQIDTObject) > 0);
}

//======================================================
const ft::QueryClass& FTMap::getQuery(const ft::QIdT& qIDT) const {

    if(_querySet.count(qIDT) == 0){
        LogClass::ThrowRuntimeError( "FTMap::getQuery can't find (" + 
                         std::to_string(qIDT.first) + ", " + ft::QueryClass::queryTypeToString(qIDT.second) + ")");
    }
    return _querySet.find(qIDT)->second;
}
//======================================================
void FTMap::addQuery(int queryID, ft::QueryType queryType, const std::string& queryString = empty)
{
    ft::QIdT testQIDT = std::make_pair(queryID, queryType);
    if(checkForQIDT(testQIDT)){
        LogClass::ThrowRuntimeError( "FTMap::addQuery already had entry (" + 
                         std::to_string(queryID) + ", " + ft::QueryClass::queryTypeToString(queryType) + ")");
    }
    ft::QueryClass newquery(queryID, queryType);
    newquery.setQueryString(queryString);
    _querySet[testQIDT] = newquery;
}
#define QUERIESEND }
//=======================================================
//==================== INDEX ============================
//=======================================================
#define INDEXSTART {

void FTMap::addIndexResults(const std::map<std::string, ft::KmerClass>& indexResults)
{
    _searchResults.push_back(indexResults);
}

//======================================================
void FTMap::addKmerResults(const ft::KmerClass& kmerResult)
{
     if (!checkForKmer(kmerResult.getKmer())){
         createKmer(kmerResult.getKmer());
     }

     KmerClass* kmer = findKmer(kmerResult.getKmer());

     // add read IDs
     for (ft::ReadID resultID : kmerResult.getReadIDs())
     {
         kmer->addReadID(resultID);
         if (!kmer->hasReadID(resultID))
         {
             std::cout << "Error: couldnt add readID to Kmer" << std::endl;
         }
     }

     // add flags
     for (std::size_t i = 0; i < 8; ++i) {
         if ( kmerResult.getKFlags().test(i) ) {
             kmer->addKFlag(ft::FlagType(i));
         }
     }
}
//======================================================
void FTMap::processIndexResults(const std::map<std::string, ft::KmerClass>& indexResult)
{
    std::map<std::string, ft::KmerClass>::const_iterator it = indexResult.begin();
    while (it != indexResult.end()){
       ft::KmerClass kmerResult = it->second;
       kmerResult.convertPosToReadID(_ftProps.getReadLength(),
                                     _ftProps.getNumOfReads(),
                                     _ftProps.getPairedReadFlag(),
                                     _ftProps.getIndexRevCompFlag());
       addKmerResults(kmerResult);
       it++;
    }
}

//======================================================
void FTMap::processResults()
{
    LogClass::Benchmark benchmark;

    for (std::map<std::string, ft::KmerClass> indexResult : _searchResults )
    {
       processIndexResults(indexResult);
    }

    for (auto query : _querySet)
    {
        ft::QIdT qIDT = query.first;
        processQueryResults(qIDT);
    }

    benchmark.now("ProcessResults DONE ");
}

//======================================================
void FTMap::processQueryResults(const ft::QIdT& qIDT)
{
    ft::QueryClass query = _querySet.find(qIDT)->second;
    // Add results from FWD Search
    std::set<std::string> fwdKmers = _qkMap.retrieveKmers(qIDT);
    std::set<ft::ReadID> readIds;
    readIds = addKmersToQueryResults(query, fwdKmers,  readIds);

    //Add results from RC Search

    if (_ftProps.getRevCompSearchFlag()){
        std::set<std::string> rcKmers = _qkRCMap.retrieveKmers(qIDT);
        readIds = addKmersToQueryResults(query, rcKmers, readIds);
    }

    int queryCount = calculateQueryCount(readIds);
    query.setCount(queryCount);
    _querySet.find(qIDT)->second = query;
}

//======================================================
int FTMap::calculateQueryCount(std::set<ft::ReadID> readIDs)
{
    int querycount = 0;
    if (_ftProps.getCountAsPairsFlag()){
        std::set<int> pairIDs;
        for (ft::ReadID readID : readIDs){
            pairIDs.insert(readID.first);
        }
        querycount = pairIDs.size();
    } else {
        querycount = readIDs.size();
    }
    return querycount;
}


//======================================================
std::set<ft::ReadID> FTMap::addKmersToQueryResults(ft::QueryClass& query, std::set<std::string> kmers,  std::set<ft::ReadID> readIds )
{
    for ( std::string kmerString : kmers)
    {
        bool addToCount = true;
        ft::KmerClass* fwdKmer = findKmer(kmerString);
        if (fwdKmer->hasFlag(ft::FlagType::OCK)){
            query.addFlag(ft::FlagType::OCK, fwdKmer->getKmer());
            if (! _ftProps.countFlag(ft::FlagType::OCK)){addToCount = false;}
        }

        if(fwdKmer->hasFlag(ft::FlagType::NUK)){
            query.addFlag(ft::FlagType::NUK, fwdKmer->getKmer());
            if (! _ftProps.countFlag(ft::FlagType::NUK)){addToCount = false;}
        }

        if (addToCount == true){
            for ( ft::ReadID readID : fwdKmer->getReadIDs())
            {
                readIds.insert(readID);
            }
        }
    }
    return readIds;
}


#define INDEXEND }
bool FTMap::operator()(const ft::QIdT& a, const ft::QIdT& b) const {
    if (a.first != b.first){
        return a.first < b.first;
    } else {
        return a.second < b.second;
    }
}

//======================================================
FTMap::~FTMap(){}

}
