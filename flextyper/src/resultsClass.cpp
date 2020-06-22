#include <set>
#include <iostream>
#include <map>
#include "typedefs.h"
#include "kmerClass.h"
#include "resultsClass.h"


namespace ft {

FTResults::FTResults(std::string kmer)
    : _searchKmer(kmer)
{
}
//======================================================
ft::KmerClass FTResults::getSearchKmer(){return this->_searchKmer;}
std::set<size_t> FTResults::getPositions(){return this->_positions;}
std::set<FlagType> FTResults::getFlags(){return this->_flags;}

//======================================================
void setSearchKmer(ft::KmerClass searchKmer){

}
void setPositions(std::set<size_t>){

}
void setFlags(std::set<FlagType>){

}

//======================================================
void addPositions(std::set<size_t>){

}
void addPosition(size_t){

}

//======================================================
void addFlags(std::set<FlagType>){

}
void addFlag(FlagType){

}


}
