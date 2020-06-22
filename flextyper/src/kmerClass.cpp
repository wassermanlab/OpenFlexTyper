#include <set>
#include <iostream>
#include <map>
#include "typedefs.h"
#include "kmerClass.h"


namespace ft {

KmerClass::KmerClass(std::string kmer)
    : _kmer(kmer),
    _queryIDs(),
    _kFlags()
{
}

//======================================================
std::string KmerClass::getKmer()
{
    return this->_kmer;
}

//======================================================
std::set<ft::QIdT> KmerClass::getQueryIDs()
{
    return this->_queryIDs;
}

//======================================================
std::set<ft::FlagType> KmerClass::getKFlags()
{
    return this->_kFlags;
}

//======================================================
void KmerClass::setQueryIDs(std::set<ft::QIdT> queries)
{

}

//======================================================
void KmerClass::setKFlags( std::set<ft::FlagType> flags)
{

}

//======================================================
void KmerClass::addQuery(ft::QIdT query)
{

}

//======================================================
void KmerClass::addKFlag(ft::FlagType flag)
{

}

uint KmerClass::getKmerMapSize(){return this->_kmer.size();}

KmerClass::~KmerClass()
{
}

}
