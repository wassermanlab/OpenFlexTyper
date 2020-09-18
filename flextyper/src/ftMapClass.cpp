﻿#include <set>
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

    FTProp::Benchmark benchmark = FTProp::Benchmark(0);

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
    FTProp::Benchmark benchmark = FTProp::Benchmark(0);

    KmerGenerator  _kmerGenerator(_ftProps.getKmerSize(),
                                  _ftProps.getRefOnlyFlag(),
                                  _ftProps.getSearchType(),
                                  _ftProps.getOverlap(),
                                  _ftProps.getStride(),
                                  _ftProps.getKmerCountsFlag(),
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
            //std::cout << "fwd kmer " << kmer << std::endl;
            if (_kmerSet.count(kmer)>0){
                findKmer(kmer)->addKFlag(ft::FlagType::NUK);
                //std::cout << "add existing kmer " << kmer << std::endl;
            } else {
                createKmer(kmer);
                //std::cout << "add new kmer " << kmer << std::endl;
            }
            _qkMap.addQKPair(it->first, kmer);
        }
        //std::cout<< "size of _qkMap " << _qkMap._map.size() << std::endl;
        // generate rc query kmers
        if (_ftProps.getRevCompSearchFlag()){
            std::set<std::string> rckmers;
            for (std::string kmer : kmers)
            {
                std::string rckmer = _utils.reverseComplement(kmer);
                //std::cout << "rc kmer " << rckmer << std::endl;
                if (_kmerSet.count(rckmer) > 0){
                    findKmer(rckmer)->addKFlag(ft::FlagType::NUK);
                    //std::cout << "add existing RC kmer " << kmer << std::endl;
                } else {
                    //std::cout << "add new RC kmer " << kmer << std::endl;
                    createKmer(rckmer);
                }
                _qkRCMap.addQKPair(it->first, rckmer);
            }       
        //std::cout<< "size of _qkRCMap " << _qkRCMap._map.size() << std::endl;
        }

        it++;
    }

    benchmark.now("Generate QKMap DONE ");
}

////======================================================================
//void FTMap::classifyQueryKmers(ft::QueryClass* queryPointer, std::set<std::string> inputkmers)
//{
//    std::set<ft::KmerClass*> newKmers;
//    std::set<ft::KmerClass*> nukKmers;

//    // create a vector of futures
//    std::vector< std::pair<std::string, std::future<ft::KmerClass*>>> classifiedKmerFutures;
//    size_t j = 0;
//    size_t k = inputkmers.size();

//    // using a queue to easily control the flow of kmers
//    std::queue<std::string> kmerQueue;
//    for (std::string kmer : inputkmers) {
//        //std::cout << "kmers " << kmer._kmer << std::endl;
//        kmerQueue.push(kmer);
//    }

//    std::atomic<int> elts;
//    elts = 0;

//    while (!kmerQueue.empty()) {
//        if (j < _ftProps.getMaxThreads()) {
//            std::string kmer = kmerQueue.front();
//            classifiedKmerFutures.push_back(std::make_pair(kmer,std::async(std::launch::async,
//                                                       &ft::FTMap::findKmer,
//                                                       dynamic_cast<ft::FTMap*>(this),
//                                                       kmer)));
//            kmerQueue.pop();
//            j++;
//            k--;
//            continue;
//        }
//        while (kmerQueue.size() > 0) {
//            if (kmerQueue.size() < _ftProps.getMaxThreads()) {
//                std::string kmer = kmerQueue.front();
//                classifiedKmerFutures.push_back(std::make_pair(kmer, std::async(std::launch::async,
//                                                 &ft::FTMap::findKmer,
//                                                 dynamic_cast<ft::FTMap*>(this),
//                                                 kmer)));
//                kmerQueue.pop();
//            } else {
//                break;
//            }
//        }

//        for (auto& e : classifiedKmerFutures) {
//            e.second.wait();
//        }

//        for (auto& e : classifiedKmerFutures) {
//            if (!e.second.get()){

//            }
//            ft::KmerClass *exists = e.second.get();
//            std::string kmer = e.first;
//            elts++;
//            if (exists)
//            {
//                ft::KmerClass* nonuniqueKmer = findKmer(kmer);
//                nonuniqueKmer->addKFlag(ft::FlagType::NUK);
//                //std::cout << "add existing kmer " << kmer << std::endl;
//            } else {
//                //std::cout << "add new kmer " << kmer << std::endl;
//                addKmer(kmer);
//            elts++;
//            }
//        j = 0;
//    }
//    std::cout << "Finished\n";
//}





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

    if (_kmerSet.count(kmerString)>0) {
        return  _kmerSet.find(kmerString)->second;
    } else {
        std::cout << "Kmer Doesnt Exist" << std::endl;
 }
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

    if(_querySet.count(qIDT)>0){
        return _querySet.find(qIDT)->second;
    }
    else {
        throw std::runtime_error( "FTMap::getQuery can't find (" + 
                         std::to_string(qIDT.first) + ", " + ft::QueryClass::queryTypeToString(qIDT.second) + ")");
    }
}
//======================================================
void FTMap::addQuery(int queryID, ft::QueryType queryType, const std::string& queryString = empty)
{
#if 0
    ft::QIdT testQIDT = std::make_pair(queryID, queryType);
    ft::QueryClass newquery(queryID, queryType);
    newquery.setQueryString(queryString);
    _querySet[testQIDT] = newquery;
#else
    //TODO: will there be duplicate added entries? The map will override the previous entry.
    ft::QIdT testQIDT = std::make_pair(queryID, queryType);
    if(!checkForQIDT(testQIDT)){
        ft::QueryClass newquery(queryID, queryType);
        newquery.setQueryString(queryString);
        _querySet[testQIDT] = newquery;
    }
    else {
        throw std::runtime_error( "FTMap::addQuery already had entry (" + 
                         std::to_string(queryID) + ", " + ft::QueryClass::queryTypeToString(queryType) + ")");
    }
#endif
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
     //std::cout << "number of read IDs to add " << kmerResult.getReadIDs().size() << std::endl;


     if (!checkForKmer(kmerResult.getKmer())){
         //std::cout << "kmer not found, creating new kmer entry" << std::endl;
         createKmer(kmerResult.getKmer());
     }

     KmerClass* kmer = findKmer(kmerResult.getKmer());

     // add read IDs
     for (ft::ReadID resultID : kmerResult.getReadIDs())
     {
         //std::cout << "result ID " << resultID.first << std::endl;
         kmer->addReadID(resultID);
         if (!kmer->hasReadID(resultID))
         {
             std::cout << "Error: couldnt add readID to Kmer" << std::endl;
         }
     }

     // add flags

     for (std::size_t i = 0; i < 8; ++i) {
         if ( kmerResult.getKFlags().test(i) ) {
             //std::cout << "addKmerResults: result Flag " << ft::FlagType(i) << std::endl;
             kmer->addKFlag(ft::FlagType(i));
         }
     }
}
//======================================================
void FTMap::processIndexResults(const std::map<std::string, ft::KmerClass>& indexResult)
{
    std::map<std::string, ft::KmerClass>::const_iterator it = indexResult.begin();
    //std::cout << "Number of kmers for this index " << indexResult.size() << std::endl;
    while (it != indexResult.end()){
        //std::cout << "kmer being added " << kmerResult._kmer << " positions " << kmerResult._positions.size()<< std::endl;
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
    FTProp::Benchmark benchmark = FTProp::Benchmark(0);

    //std::cout << "number of index results to process " << _searchResults.size() << std::endl;
    for (std::map<std::string, ft::KmerClass> indexResult : _searchResults ){
       //std::cout << "Number of kmers for this index " << indexResult.size() << std::endl;
       processIndexResults(indexResult);
    }
    //std::cout << "Number of queries to count " << _querySet.size() << std::endl;
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
    FTProp::Benchmark benchmark = FTProp::Benchmark(0);

    // Add results from FWD Search
    std::set<std::string> fwdKmers = _qkMap.retrieveKmers(qIDT);
    //std::cout << "number of fwd Kmers " << fwdKmers.size() << std::endl;
    std::set<ft::ReadID> readIds;
    readIds = addKmersToQueryResults(query, fwdKmers,  readIds);

    //std::cout << "query count after fwd kmers added " << readIds.size() << std::endl;
    //Add results from RC Search


    if (_ftProps.getRevCompSearchFlag()){
        std::set<std::string> rcKmers = _qkRCMap.retrieveKmers(qIDT);
        readIds = addKmersToQueryResults(query, rcKmers, readIds);
    }

    //std::cout << "query count after rc kmers added " << readIds.size() << std::endl;
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
std::set<ft::ReadID> FTMap::addKmersToQueryResults(ft::QueryClass query, std::set<std::string> kmers,  std::set<ft::ReadID> readIds )
{
    for ( std::string kmerString : kmers)
    {
        bool addToCount = true;
        ft::KmerClass* fwdKmer = findKmer(kmerString);

        //std::cout << "kmer found " << fwdKmer->getKmer() << " with count " << fwdKmer->getOCC()<<  std::endl;
        //std::cout << "over counted " << fwdKmer->hasFlag(ft::FlagType::OCK) << std::endl;
        //std::cout << "abundant " << fwdKmer->hasFlag(ft::FlagType::ABK) << std::endl;
        //std::cout << "NUK " << fwdKmer->hasFlag(ft::FlagType::NUK)  << std::endl;
        if (fwdKmer->hasFlag(ft::FlagType::OCK)){
            //std::cout << "Kmer is overcounted " << std::endl;
            query.addFlag(ft::FlagType::OCK, fwdKmer->getKmer());
            if (_ftProps.getOverCountedFlag()){addToCount = false;}
            //std::cout << "OCK add to count " << addToCount << std::endl;
        }

        if(fwdKmer->hasFlag(ft::FlagType::NUK)){
            //std::cout << "Kmer is not unique " << std::endl;
            query.addFlag(ft::FlagType::NUK, fwdKmer->getKmer());
            if (_ftProps.getIgnoreNonUniqueKmersFlag()){addToCount = false;}
        }

        //std::cout << "number of fwd ReadIDs " << readIds.size() << std::endl;
        if (addToCount == true){

            //std::cout << "count kmer " << fwdKmer->getKmer() << " with count " << fwdKmer->getOCC() << " with " << fwdKmer->getReadIDs().size() << " OCC FLAG " << fwdKmer->hasFlag(ft::FlagType::OCK) << std::endl;
            for ( ft::ReadID readID : fwdKmer->getReadIDs())
            {
                readIds.insert(readID);
            }

        }
    }
    //std::cout << "number of query ReadIDs " << readIds.size() << std::endl;
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
