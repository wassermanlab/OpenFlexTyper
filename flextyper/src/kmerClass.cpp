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
std::set<ft::QIdT> KmerClass::getQueryIDs()
{
    return _queryIDs;
}

//======================================================
std::set<ft::FlagType> KmerClass::getKFlags()
{
    return _kFlags;
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

KmerClass::~KmerClass()
{
}

}
