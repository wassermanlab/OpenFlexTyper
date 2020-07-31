﻿#include <set>
#include <iostream>
#include <map>
#include <algorithm>
#include <queue>
#include "ftMapClass.h"

namespace ft {

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

    KmerGenerator  _kmerGenerator(_ftProps.getKmerSize(),
                                  _ftProps.getRefOnlyFlag(),
                                  _ftProps.getSearchType(),
                                  _ftProps.getOverlap(),
                                  _ftProps.getStride(),
                                  _ftProps.getKmerCountsFlag(),
                                  _ftProps.getMaxKmers());


    for (ft::QueryClass query : _querySet ){
        ft::QueryClass* queryPointer = findQuery(query.getQIdT());
        std::set<ft::KmerClass*> kmerObj;
        // generate fwd query kmers
        std::set<std::string> kmers = (_kmerGenerator.genSearchKmers(query));
        std::cout << "generated " << kmers.size() << " kmers " << std::endl;
        for (std::string kmer : kmers)
        {
            if (checkForKmer(kmer)){
                ft::KmerClass* nonuniqueKmer = findKmer(kmer);
                nonuniqueKmer->addKFlag(ft::FlagType::NUK);
                //std::cout << "add existing kmer " << kmer << std::endl;
            } else {
                //std::cout << "add new kmer " << kmer << std::endl;
                addKmer(kmer);
            }
            kmerObj.insert(findKmer(kmer));
        }
        std::cout << "number of fwd kmers " << kmerObj.size() << std::endl;


        if (_ftProps.getRevCompSearchFlag()){
            ft::Utils _utils;
            std::set<std::string> rckmers;
            for (std::string kmer : kmers)
            {
                std::string rckmer = _utils.reverseComplement(kmer);
                if (checkForKmer(rckmer)){
                    ft::KmerClass* nonuniqueKmer = findKmer(rckmer);
                    nonuniqueKmer->addKFlag(ft::FlagType::NUK);
                    //std::cout << "add existing RC kmer " << kmer << std::endl;
                } else {
                    //std::cout << "add new RC kmer " << kmer << std::endl;
                    addKmer(rckmer);
                }
                kmerObj.insert(findKmer(rckmer));
            }
        }
        std::cout << "number of fwd + rc kmers " << kmerObj.size() << std::endl;
        _qkMap.addQKSet(queryPointer, kmerObj);
    }
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
        //std::cout << "Query not added, query already exists" << std::endl;
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
        //std::cout << "Query not added, query already exists" << std::endl;
    }
}
#define QUERIESEND }
//=======================================================
//==================== INDEX ============================
//=======================================================
#define INDEXSTART {

void FTMap::addIndexResults(std::set<ft::KmerClass> indexResults)
{
    //for (ft::KmerClass result : indexResults)
    //{
        //std::cout<< " kmer " << result._kmer << " number of positions: " << result._positions.size() << std::endl;
    //}
    _searchResults.push_back(indexResults);
}

//======================================================
void FTMap::addKmerResults(const ft::KmerClass& kmerResult)
{
     //std::cout << "number of read IDs to add " << kmerResult.getReadIDs().size() << std::endl;
     KmerClass* kmer = findKmer(kmerResult.getKmer());

     if (kmer == NULL){
         std::cout << "kmer not found, creating new kmer entry" << std::endl;
         addKmer(kmerResult);
         kmer = findKmer(kmerResult.getKmer());
         if (!checkForKmer(kmer->getKmer())){
             std::cout << "Error: couldnt add new kmer to FTMap" << std::endl;
         }
     }

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
     for (auto flag : kmerResult.getKFlags())
     {
         //std::cout << "result Flag " << flag.first << std::endl;
         kmer->addKFlag(flag.first);
     }

}
//======================================================
void FTMap::processIndexResults(std::set<ft::KmerClass> indexResult)
{

    //std::cout << "Number of kmers for this index " << indexResult.size() << std::endl;
    for (ft::KmerClass kmerResult : indexResult){
        //std::cout << "kmer being added " << kmerResult._kmer << " positions " << kmerResult._positions.size()<< std::endl;

       kmerResult.convertPosToReadID(_ftProps.getReadLength(),
                                     _ftProps.getNumOfReads(),
                                     _ftProps.getPairedReadFlag(),
                                     _ftProps.getIndexRevCompFlag());
       addKmerResults(kmerResult);
    }

}

//======================================================
void FTMap::processResults()
{
    //std::cout << "number of index results to process " << _searchResults.size() << std::endl;
    for (std::set<ft::KmerClass> indexResult : _searchResults ){
       //std::cout << "Number of kmers for this index " << indexResult.size() << std::endl;
       processIndexResults(indexResult);
    }
    std::cout << "Number of queries to count " << _querySet.size() << std::endl;
    for (ft::QueryClass query : _querySet)
    {
        std::cout << "Query ID " << query.getqID() << std::endl;
        processQueryResults(query.getQIdT());

    }

}

//======================================================
void FTMap::processQueryResults(const ft::QIdT& queryIDT)
{
    ft::QueryClass* query = findQuery(queryIDT);

    // Add results from FWD Search
    std::set<ft::KmerClass*> fwdKmers = _qkMap.retrieveKmers(query);
    std::cout << "number of fwd Kmers " << fwdKmers.size() << std::endl;
    std::set<ft::ReadID> readIds;
    for (ft::KmerClass* fwdKmer : fwdKmers)
    {
        bool addToCount = true;

        if(fwdKmer->hasFlag(ft::FlagType::NUK)){
            std::cout << "Kmer is not unique " << std::endl;
            query->addFlag(ft::FlagType::NUK, fwdKmer->getKmer());
            if (_ftProps.getIgnoreNonUniqueKmersFlag()){addToCount = false;}
        }

        if (fwdKmer->hasFlag(ft::FlagType::OCK)){
            std::cout << "Kmer is overcounted " << std::endl;
            query->addFlag(ft::FlagType::OCK, fwdKmer->getKmer());
            if (_ftProps.getOverCountedFlag()){addToCount = false;}
        }

        std::set<ft::ReadID> fwdKmerReadIDs = fwdKmer->getReadIDs();
        //std::cout << "number of fwd ReadIDs " << fwdKmerReadIDs.size() << std::endl;
        if (addToCount){
            for ( ft::ReadID readID : fwdKmerReadIDs)
            {
                readIds.insert(readID);
            }
            //std::cout << "number of query ReadIDs " << readIds.size() << std::endl;
        }
    }

    //Add results from RC Search
    if (_ftProps.getRevCompSearchFlag()){
        std::set<ft::KmerClass*> rcKmers = _qkMap.retrieveKmers(query);
        std::cout << "number of rc Kmers " << rcKmers.size() << std::endl;
        for (ft::KmerClass* rcKmer : rcKmers)
        {
            bool addToCount = true;
            if(rcKmer->hasFlag(ft::FlagType::NUK)){
                query->addFlag(ft::FlagType::NUK, rcKmer->getKmer());
                if (_ftProps.getIgnoreNonUniqueKmersFlag()){addToCount = false;}
            }

            if (rcKmer->hasFlag(ft::FlagType::OCK)){
                query->addFlag(ft::FlagType::OCK, rcKmer->getKmer());
                if (_ftProps.getOverCountedFlag()){addToCount = false;}
            }

            std::set<ft::ReadID> rcKmerReadIDs = rcKmer->getReadIDs();
            //std::cout << "number of rc ReadIDs " << rcKmerReadIDs.size() << std::endl;
            if (addToCount){
                for ( ft::ReadID readID : rcKmerReadIDs)
                {
                    readIds.insert(readID);
                    //std::cout << "number of query ReadIDs " << readIds.size() << std::endl;
                }
            }
        }
    }

    query->setCount(readIds.size());
}

#define INDEXEND }

//======================================================
FTMap::~FTMap(){}

}
