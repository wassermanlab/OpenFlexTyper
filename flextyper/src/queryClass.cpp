#include <set>
#include <iostream>
#include <map>

#include "queryClass.h"
#include "typedefs.h"

namespace ft {

QueryClass::QueryClass(int queryID, ft::QueryType queryType)
    : _qID(queryID),
      _qType(queryType)
{
}
//======================================================
int QueryClass::getqID(){ return _qID;}
QueryType QueryClass::getqType(){return _qType;}
std::string QueryClass::getQueryString(){return _string;}
std::set<std::string> QueryClass::getKmers(){return _kmers;}
std::set<int> QueryClass::getReadIDs(){return _readIDs;}
int QueryClass::getCount(){return _count;}
std::map<ft::FlagType, std::set<std::string>> QueryClass::getQFlags(){return _qFlags;}

ft::QIdT QueryClass::getQIdT(){return std::make_pair(_qID, _qType);}

//======================================================
void QueryClass::setqID(int qID){
    if (qID != this->getqID()) {
        _qID = qID;
    }
}
void QueryClass::setqType(QueryType queryType){
    if (queryType != this->getqType()) {
        _qType = queryType;
    }
}
void QueryClass::setQueryString(std::string queryString){
    if (queryString != this->getQueryString()) {
        _string = queryString;
    }
}
void QueryClass::setCount(int count){
    if (count != this->getCount()) {
        _count = count;
    }
}
void QueryClass::setKmers(std::set<std::string> kmers){
    if (kmers != this->getKmers()) {
        _kmers = kmers;
    }
}
void QueryClass::setFlags(std::map<ft::FlagType, std::set<std::string>> flags){
    if (flags != this->getQFlags()) {
        _qFlags = flags;
    }
}
//======================================================
void QueryClass::addKmer(std::string kmer){
    this->getKmers().insert(kmer);
}
void QueryClass::addReadID(int readID){
    this->getReadIDs().insert(readID);
}
void QueryClass::addFlag(ft::FlagType flagType, std::set<std::string> kmers){
    std::map<ft::FlagType, std::set<std::string>> queryFlags = this->getQFlags();
    for (auto kmer :kmers){
        queryFlags[flagType].insert(kmer);
    }
}

//======================================================
bool QueryClass::isQIdTEqual(ft::QIdT test){
    return this->getQIdT() == test;
}

//======================================================
std::set<std::string> QueryClass::getFlagKmers(ft::FlagType flag){
    return this->getQFlags()[flag];
}

//======================================================
bool QueryClass::operator< (const ft::QueryClass &q){return this->getQIdT() < std::make_pair(q._qID, q._qType); }


}
