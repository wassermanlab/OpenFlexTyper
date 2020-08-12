#include <set>
#include <iostream>
#include <unordered_map>
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
        addNewQuery(qID, ft::QueryType::REF, refString);

        // Create Alt Query
        if (!_ftProps.getRefOnlyFlag()) {
            std::string altString = std::get<2>(inputQuery);
            addNewQuery(qID, ft::QueryType::ALT, altString);
        }

        // Create Crossover Query
        if (_ftProps.getCrossoverFlag() && !std::get<1>(inputQuery).empty() && !std::get<2>(inputQuery).empty()) {
            std::string croString = std::get<3>(inputQuery);
            addNewQuery(qID, ft::QueryType::CRO, croString);
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

    std::map<ft::QIdT, ft::QueryClass>::iterator it = _querySet.begin();
    ft::Utils _utils;
    while (it != _querySet.end()){
        ft::QueryClass query = it->second;
        // generate fwd query kmers
        std::set<ft::Kmer> kmers = (_kmerGenerator.genSearchKmers(query));
        //std::cout << "generated " << kmers.size() << " kmers " << std::endl;

        for (ft::Kmer kmer : kmers)
        {
            if (_kmerSet.count(kmer)>0){
                findKmer(kmer)->addKFlag(ft::FlagType::NUK);
                //std::cout << "add existing kmer " << kmer << std::endl;
            } else {
                createKmer(kmer);
                //std::cout << "add new kmer " << kmer << std::endl;
            }
            _qkMap.addQKPair(it->first, kmer);
        }

        //std::cout << "number of fwd kmers " << kmerObj.size() << std::endl;

        if (_ftProps.getRevCompSearchFlag()){
            std::set<ft::Kmer> rckmers;

            for (ft::Kmer kmer : kmers)
            {
                ft::Kmer rckmer = _utils.reverseComplement(kmer);
                if (_kmerSet.count(rckmer) > 0){
                    findKmer(rckmer)->addKFlag(ft::FlagType::NUK);
                    //std::cout << "add existing RC kmer " << kmer << std::endl;
                } else {
                    //std::cout << "add new RC kmer " << kmer << std::endl;
                    createKmer(rckmer);
                }
                _qkRCMap.addQKPair(it->first, rckmer);
            }       
        }
        //std::cout << "number of fwd + rc kmers " << kmerObj.size() << std::endl;
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
bool FTMap::checkForKmer(const ft::Kmer &testKmer) const
{
    if (_kmerSet.count(testKmer)>0) {return true;}
    else {return false;}
}

//======================================================
ft::KmerClass* FTMap::findKmer(const std::string& testKmer)
{
    std::unordered_map<ft::Kmer, ft::KmerClass>::iterator it = _kmerSet.find(testKmer);
    if (it != _kmerSet.end()) {
        return  &((*it).second);
    } else {return NULL;}
}

//======================================================
const ft::KmerClass& FTMap::getKmer(const ft::Kmer& kmerString) const
{

    if (_kmerSet.count(kmerString)>0) {
        return  _kmerSet.find(kmerString)->second;
    } else {
        std::cout << "Kmer Doesnt Exist" << std::endl;
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
    if (_querySet.count(testQIDTObject)>0) {return true;}
    else {return false;}
}
//======================================================
ft::QueryClass* FTMap::findQuery(const ft::QIdT& qIDT)
{
    std::map<ft::QIdT, ft::QueryClass>::iterator it = _querySet.find(qIDT);
    if (it != _querySet.end()) {
        return  &((*it).second);
    } else {return NULL;}
}

//======================================================
const ft::QueryClass& FTMap::getQuery(const ft::QIdT& qIDT) const
{
    if (_querySet.count(qIDT)>0) {
        return  _querySet.find(qIDT)->second;
    } else {
        std::cout << "Query Doesnt Exist" << std::endl;
 }
}

//======================================================
void FTMap::addNewQuery(int queryID, ft::QueryType queryType, std::string queryString)
{
    ft::QIdT testQIDT = std::make_pair(queryID, queryType);
    ft::QueryClass newquery(queryID, queryType);
    newquery.setQueryString(queryString);
    _querySet[testQIDT] = newquery;
}

//======================================================
void FTMap::createQuery(int queryID, ft::QueryType queryType)
{
    ft::QIdT testQIDT = std::make_pair(queryID, queryType);
    ft::QueryClass newquery(queryID, queryType);
    _querySet[testQIDT] = newquery;
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
    //std::cout << "Number of queries to count " << _querySet.size() << std::endl;
    for (auto query : _querySet)
    {
        ft::QIdT qIDT = query.first;
        //std::cout << "Query ID " << qIDT << std::endl;
        processQueryResults(qIDT);

    }

}

//======================================================
void FTMap::processQueryResults(const ft::QIdT& queryIDT)
{
    ft::QueryClass* query = findQuery(queryIDT);

    // Add results from FWD Search
    std::set<ft::Kmer> fwdKmers = _qkMap.retrieveKmers(queryIDT);
    //std::cout << "number of fwd Kmers " << fwdKmers.size() << std::endl;
    std::set<ft::ReadID> readIds;
    for ( ft::Kmer kmerString : fwdKmers)
    {
        bool addToCount = true;
        ft::KmerClass* fwdKmer = findKmer(kmerString);
        if(fwdKmer->hasFlag(ft::FlagType::NUK)){
            //std::cout << "Kmer is not unique " << std::endl;
            query->addFlag(ft::FlagType::NUK, fwdKmer->getKmer());
            if (_ftProps.getIgnoreNonUniqueKmersFlag()){addToCount = false;}
        }

        if (fwdKmer->hasFlag(ft::FlagType::OCK)){
            //std::cout << "Kmer is overcounted " << std::endl;
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
        std::set<ft::Kmer> rcKmers = _qkMap.retrieveKmers(queryIDT);
        //std::cout << "number of rc Kmers " << rcKmers.size() << std::endl;
        for (ft::Kmer kmerString : rcKmers)
        {
            ft::KmerClass* rcKmer = findKmer(kmerString);
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
