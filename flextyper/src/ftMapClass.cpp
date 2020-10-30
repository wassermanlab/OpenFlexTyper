////////////////////////////////////////////////////////////////////////
/// \copyright Copyright (c) 2020, Wasserman lab
////////////////////////////////////////////////////////////////////////

#include <set>
#include <iostream>
#include <iomanip>
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

        //_ftProps.printToStdOut( "generated " + std::to_string(kmers.size()) + " kmers " );

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

     // add overcounted flag if combined maxOcc is too high
     if (kmer->getReadIDs().size() > _ftProps.getMaxOcc()){
         kmer->addKFlag(ft::FlagType::OCK);
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

    showResources();
    for (std::map<std::string, ft::KmerClass>& indexResult : _searchResults )
    {
       processIndexResults(indexResult);
       indexResult.clear(); //free up memory
    }

    for (auto query : _querySet)
    {
        ft::QIdT qIDT = query.first;
        processQueryResults(qIDT);
    }
    _kmerSet.clear(); //free up memory

    showResources();
    if (_ftProps.getUniqueReadsFlag()){
        if (_ftProps.getCountAsPairsFlag())
        {
            removeMultiHitsAsPairs();
        } else {
            removeMultiHits();
        }
    }
    for (auto query : _querySet)
    {
        std::cout << "count " << query.second.getCount() << " readIds " << query.second._reads.size() << std::endl;
    }

    benchmark.now("ProcessResults DONE ");
}

//======================================================
void FTMap::processQueryResults(const ft::QIdT& qIDT)
{
    ft::QueryClass& query = _querySet.find(qIDT)->second;
    // Add results from FWD Search
    std::set<std::string> fwdKmers = _qkMap.retrieveKmers(qIDT);
    std::set<ft::ReadID> readIds;
    addKmersToQueryResults(query, fwdKmers,  readIds);

    //Add results from RC Search

    if (_ftProps.getRevCompSearchFlag()){
        std::set<std::string> rcKmers = _qkRCMap.retrieveKmers(qIDT);
        addKmersToQueryResults(query, rcKmers, readIds);
    }

    int queryCount = calculateQueryCount(readIds);
    query.setCount(queryCount);
}

//======================================================
int FTMap::calculateQueryCount(const std::set<ft::ReadID>& readIDs)
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
void FTMap::addKmersToQueryResults(ft::QueryClass& query, std::set<std::string>& kmers,  std::set<ft::ReadID>& readIds )
{
    for (const std::string& kmerString : kmers)
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
                //std::cout << "Read ID to add " << readID.first << std::endl;
                query.addReadID(readID);
                readIds.insert(readID);
            }
        }
    }
}
//======================================================
void FTMap::addReadIDsToQuery(ft::QIdT qIDT, std::set<ft::ReadID>& readIds)
{
    ft::QueryClass& query = _querySet.find(qIDT)->second;
    for (const ft::ReadID& readID : readIds)
    {
        query.addReadID(readID);
    }
}

//======================================================
void FTMap::removeMultiHits()
{
    LogClass::Log << "Remove multi hits";
    std::map<ft::ReadID, std::pair<ft::QIdT, bool>> _observedReads; ///< bool = whether its added to adjustment (gets added when its seen for the second time)
    std::map<ft::QIdT, std::set<ft::ReadID>> _queriesToAdjust; /// query to adjust, amount to adjust count by
    for (auto querypair : _querySet) /// iterate through and compile a list of multihits
    {
        ft::QIdT qIDT = querypair.first;
        ft::QueryClass& query = _querySet.find(qIDT)->second;
        std::set<ft::ReadID> newReadIDs;
        for (auto readID : query.getReadIDs())
        {
            auto search = _observedReads.find(readID);
            if (search == _observedReads.end()){ /// if read hasnt been observed
                _observedReads[readID] = std::make_pair(qIDT, false); /// add to observed Reads
                newReadIDs.insert(readID); /// add to new reads
            } else {
                if (!search->second.second){ /// if query isnt marked for adjustment
                    ft::QIdT qIDTAdjust =  search->second.first;
                    search->second.second = true;
                    //_observedReads[readID] = std::make_pair(qIDTAdjust, true); /// mark query for adjustment
                    _queriesToAdjust[qIDTAdjust].insert(readID); /// add to list of queries to adjust
                }
            }
        }

        query._reads = newReadIDs;
        int queryCount = calculateQueryCount(newReadIDs);
        query.setCount(queryCount);
    }

    for (auto qIDT : _queriesToAdjust){ ///< iterate through and remove multi hit reads, adjust query counts
        ft::QueryClass& query = _querySet.find(qIDT.first)->second;
        for (auto readID : _queriesToAdjust[qIDT.first]){
            query.removeReadID(readID);
        }
        int queryCount = calculateQueryCount(query.getReadIDs());
        query.setCount(queryCount);
    }
}
//======================================================
void FTMap::removeMultiHitsAsPairs()
{
    LogClass::Log << "Remove multi hits as pairs";
    std::map<int, std::tuple<ft::ReadID, ft::QIdT, bool>> _observedReads; /// < int = Read ID (ignoring pair)
    std::map<ft::QIdT, std::set<ft::ReadID>> _queriesToAdjust; /// query to adjust, amount to adjust count by
    for (auto querypair : _querySet) /// iterate through and compile a list of multihits
    {
        ft::QIdT qIDT = querypair.first;
        ft::QueryClass& query = _querySet.find(qIDT)->second;
        std::set<ft::ReadID> newReadIDs;
        for (auto readID : query.getReadIDs())
        {
            int rID = readID.first;
            auto search = _observedReads.find(rID);
            if (search == _observedReads.end()){ /// if read hasnt been observed
                _observedReads[rID] = std::make_tuple(readID, qIDT, false); /// add to observed Reads
                newReadIDs.insert(readID); /// add to new reads
            } else {
                if (!std::get<2>(search->second)){ /// if query isnt marked for adjustment
                    ft::ReadID readIDAdjust= std::get<0>(search->second);
                    ft::QIdT qIDTAdjust = std::get<1>(search->second);
                    if (!(qIDTAdjust == qIDT)){
                    _observedReads[rID] = std::make_tuple(readIDAdjust, qIDTAdjust, true); /// mark query for adjustment
                    _queriesToAdjust[qIDTAdjust].insert(readIDAdjust); /// add to list of queries to adjust
                    } else {
                         newReadIDs.insert(readID);
                    }
                }
            }
        }
        query._reads = newReadIDs;
        int queryCount = calculateQueryCount(newReadIDs);
        query.setCount(queryCount);
    }

   for (auto qIDT : _queriesToAdjust){ ///< iterate through and remove multi hit reads, adjust query counts
        ft::QueryClass& query = _querySet.find(qIDT.first)->second;
        for (auto readID : _queriesToAdjust[qIDT.first]){
            query.removeReadID(readID);
        }
        int queryCount = calculateQueryCount(query.getReadIDs());
        query.setCount(queryCount);
    }
}

//======================================================
#define INDEXEND }

bool FTMap::operator()(const ft::QIdT& a, const ft::QIdT& b) const {
    if (a.first != b.first){
        return a.first < b.first;
    } else {
        return a.second < b.second;
    }
}

void FTMap::showResources() const {
    LogClass::Log << "========== Show FTMap Resources ==========" << std::endl;
    LogClass::Log << "==========================================" << std::endl;

    int kmer_count = 0, kmer_positions = 0, kmer_readIDs = 0;
    for (auto& it : _kmerSet) {
        kmer_count++;
        kmer_positions += it.second.getKPositions().size();
        kmer_readIDs += it.second.getReadIDs().size();
    }
    LogClass::Log << "=== FTMap._kmer[total " << kmer_count << "] ====" << std::endl; 
    LogClass::Log << "\tnum_entries\tentry_size\ttotal(kB)\ttype" << std::endl;
    LogClass::Log << "\t"
                  << kmer_positions << std::setw(12) 
                  << sizeof(long long) << std::setw(12) 
                  << (kmer_positions * sizeof(long long))/1000 << std::setw(12)
                  << "all FTMap._kmerSet::_positions" << std::endl;
    LogClass::Log << "\t"
                  << kmer_readIDs << std::setw(12)
                  << sizeof(ft::ReadID) << std::setw(12)
                  << (kmer_readIDs * sizeof(ft::ReadID))/1000 << std::setw(12)
                  << "all FTMap._kmerSet::_readIDs" << std::endl;

    LogClass::Log << "=== FTMap._querySet ====" << std::endl; 
    LogClass::Log << "\tnum_entries\tentry_size\ttotal(kB)\ttype" << std::endl;
    for (auto& it : _querySet) {
        LogClass::Log << "\t"
                      << it.second.getReadIDs().size() << std::setw(12) 
                      << sizeof(ft::ReadID) << std::setw(12)
                      << (it.second.getReadIDs().size() * sizeof(ft::ReadID))/1000 << std::setw(12)
                      << "FTMap._querySet::_readIDs for type " 
                      << ft::QueryClass::queryTypeToString(it.second.getqType())  << std::endl;
    }

    for (auto& indexResult : _searchResults) {
        int kmer_count = 0; kmer_positions = 0; kmer_readIDs = 0;
        for (auto& it2 : indexResult) {
            kmer_count++;
            kmer_positions += it2.second.getKPositions().size();
            kmer_readIDs += it2.second.getReadIDs().size();
        }
        LogClass::Log << "=== FTMap._searchResults[][total " << kmer_count << "] ====" << std::endl; 
        LogClass::Log << "\tnum_entries\tentry_size\ttotal(kB)\ttype" << std::endl;
        LogClass::Log << "\t"
                  << kmer_positions << std::setw(12) 
                  << sizeof(long long) << std::setw(12) 
                  << (kmer_positions * sizeof(long long))/1000 << std::setw(12)
                  << "all FTMap._kmer::_positions" << std::endl;
        LogClass::Log << "\t"
                  << kmer_readIDs << std::setw(12)
                  << sizeof(ft::ReadID) << std::setw(12)
                  << (kmer_readIDs * sizeof(ft::ReadID))/1000 << std::setw(12)
                  << "all FTMap._kmer::_readIDs" << std::endl;
    }

}

//======================================================
FTMap::~FTMap(){}

}
