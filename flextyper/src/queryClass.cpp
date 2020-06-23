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

}
void QueryClass::setqType(QueryType queryType){

}
void QueryClass::setQueryString(std::string queryString){

}
void QueryClass::setCount(int count){

}
void QueryClass::setKmers(std::set<std::string> kmers){

}
void QueryClass::setFlags(std::map<ft::FlagType, std::set<std::string>> flags){

}
//======================================================
void QueryClass::addKmer(std::string kmer){

}
void QueryClass::addReadID(int readID){

}
void QueryClass::addFlag(ft::FlagType flagType, std::set<std::string> kmers){

}

bool QueryClass::isQIdTEqual(ft::QIdT test){
    return this->getQIdT() == test;
}

std::set<std::string> QueryClass::getFlagKmers(ft::FlagType flag){
    return this->getQFlags()[flag];
}

}
