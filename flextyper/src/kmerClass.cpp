#include <set>
#include <iostream>
#include <map>
#include "typedefs.h"
#include "kmerClass.h"


namespace ft {

KmerClass::KmerClass(std::string kmer)
    : _kmer(kmer),
    _queryIDs(),
    _kFlags(),
    _positions()
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
std::set<size_t> KmerClass::getKPositions()
{
    return this->_positions;
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
void KmerClass::setKPositions( std::set<size_t> kPositions, uint offset)
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

//======================================================
void KmerClass::addKPosition(size_t kPosition, uint offset)
{

}


uint KmerClass::getKmerMapSize(){return this->_kmer.size();}
//======================================================
void convertPosToReadID(uint readlength)
{
    std::set<size_t> positions = this->_positions;

    for (auto pos : positions) {
        auto r = (size_t) std::ceil(indexPos / (readLength + 1));

}

KmerClass::~KmerClass()
{
}

}
