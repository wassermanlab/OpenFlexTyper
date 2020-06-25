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

//=================== GETTERS =============================
int QueryClass::getqID(){return _qID;}
QueryType QueryClass::getqType(){return _qType;}
std::string QueryClass::getQueryString(){return _qstring;}
int QueryClass::getCount(){return _count;}
std::map<ft::FlagType, std::set<std::string>> QueryClass::getQFlags(){return _qFlags;}
ft::QIdT QueryClass::getQIdT(){return std::make_pair(_qID, _qType);}
std::set<std::string> QueryClass::getFlagKmers(ft::FlagType flag){
    return this->getQFlags()[flag];
}

//================== SETTERS ===========================
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
        _qstring = queryString;
    }
}
void QueryClass::setCount(int count){
    if (count != this->getCount()) {
        _count = count;
    }
}
void QueryClass::setFlags(std::map<ft::FlagType, std::set<std::string>> flags){
    if (flags != this->getQFlags()) {
        _qFlags = flags;
    }
}

//===================== ADDERS ==========================
void QueryClass::addFlag(ft::FlagType flagType, std::set<std::string> kmers){
    std::map<ft::FlagType, std::set<std::string>> queryFlags = this->getQFlags();
    for (auto kmer :kmers){
        queryFlags[flagType].insert(kmer);
    }
}

//===================== REMOVERS ==========================
void QueryClass::removeFlag(ft::FlagType flagType){
    this->getQFlags().erase(flagType);
}
void QueryClass::removeKmerFlag(ft::FlagType flagType, std::string kmers){
    _qFlags[flagType].erase(kmers);
}
void QueryClass::removeCount(){
     this->setCount(0);
}

//==================== CHECKERS =========================
bool QueryClass::isQIdTEqual(ft::QIdT test){
    return this->getQIdT() == test;
}
bool QueryClass::hasQueryID(int qid) const {
    return _qID == qid;
}
bool QueryClass::hasQueryType(ft::QueryType qType) const{
    return this->_qType == qType;
}
bool QueryClass::hasKmerFlag(ft::FlagType flag, std::string kmer) {
    std::set<std::string> flagKmers = this->getFlagKmers(flag);
    const bool is_in = flagKmers.find(kmer) != flagKmers.end();
    return is_in;
}
bool QueryClass::hasNonZeroCount() {

    return this->getCount()>0;
}

//===================== OVERLOAD ========================
bool QueryClass::operator< (const ft::QueryClass &q) const {
    return std::make_pair(_qID, _qType) < std::make_pair(q._qID, q._qType); }


}
