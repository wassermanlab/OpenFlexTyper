#include <set>
#include <iostream>
#include <map>
#include "queryClass.h"

namespace ft {

QueryClass::QueryClass(int queryID, ft::QueryType queryType)
    : _qID(queryID),
      _qType(queryType)
{
}

//=================== GETTERS =============================
int QueryClass::getqID()const {return _qID;}
QueryType QueryClass::getqType() const {return _qType;}
std::string QueryClass::getQueryString() const {return _qstring;}
int QueryClass::getCount() const {return _count;}
std::map<ft::FlagType, std::set<std::string>> QueryClass::getQFlags()const {return _qFlags;}
ft::QIdT QueryClass::getQIdT()const {return std::make_pair(_qID, _qType);}
const std::set<std::string> QueryClass::getFlagKmers(const ft::FlagType flag) const {
return _qFlags.find(flag)->second;}

//================== SETTERS ===========================
void QueryClass::setqID(int qID){
        _qID = qID;  
}
void QueryClass::setqType(QueryType queryType){
        _qType = queryType;
}
void QueryClass::setQueryString(std::string queryString){
        _qstring = queryString;
}
void QueryClass::setCount(int count){
        _count = count;
}
void QueryClass::setFlags(const std::map<ft::FlagType, std::set<std::string>>& flags){
    _qFlags = flags;
}

//===================== ADDERS ==========================
void QueryClass::addFlag(const ft::FlagType& flagType, const std::set<std::string>& kmers){
    for (auto kmer :kmers){
        _qFlags[flagType].insert(kmer);
    }
}

//===================== REMOVERS ==========================
void QueryClass::removeFlag(ft::FlagType flagType){
    _qFlags.erase(flagType);
}
void QueryClass::removeKmerFlag(const ft::FlagType& flagType, const std::string& kmers){
    _qFlags[flagType].erase(kmers);
}
void QueryClass::removeCount(){
     setCount(0);
}

//==================== CHECKERS =========================
bool QueryClass::isQIdTEqual(const ft::QIdT& test) const{
    return getQIdT() == test;
}
bool QueryClass::hasQueryID(const int &qid) const {
    return _qID == qid;
}
bool QueryClass::hasQueryType(const ft::QueryType& qType) const{
    return _qType == qType;
}
bool QueryClass::hasKmerFlag(const ft::FlagType& flag, const std::string& kmer) const{
    //std::set<std::string> flagKmers = _qFlags[flag];
    //const bool is_in = flagKmers.find(kmer) != flagKmers.end();
    //return is_in;
    return true;
}
bool QueryClass::hasNonZeroCount() const{

    return this->getCount()>0;
}

//===================== OVERLOAD ========================
bool QueryClass::operator< (const ft::QueryClass &q) const {
    if (_qID != q._qID){
        return _qID < q._qID;
    } else {
        return _qType < q._qType;
    }
}

bool QueryClass::operator== (const ft::QueryClass &q) const {
    return (_qID == q._qID && _qType == q._qType); }



QueryClass::~QueryClass()
{
}
}
