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

//======================================================
void setqID(int qID){

}
void setqType(QueryType queryType){

}
void setQueryString(std::string queryString){

}
void setCount(int count){

}
void setKmers(std::set<std::string> kmers){

}
void setFlags(std::map<ft::FlagType, std::set<std::string>> flags){

}
//======================================================
void addKmer(std::string kmer){

}
void addFlag(ft::FlagType flagType, std::set<std::string> kmers){

}
}
