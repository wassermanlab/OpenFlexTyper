#include <set>
#include <iostream>
#include <map>
#include <math.h>
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
std::string KmerClass::getKmer() const{return this->_kmer;}
std::set<ft::QIdT> KmerClass::getQueryIDs(){return this->_queryIDs;}
std::set<ft::FlagType> KmerClass::getKFlags(){return this->_kFlags;}
std::set<size_t> KmerClass::getKPositions(){return this->_positions;}

//======================================================
void KmerClass::setQueryIDs(std::set<ft::QIdT> queries)
{
    for (auto qIDT : queries){addQuery(qIDT);}
}

//======================================================
void KmerClass::setKFlags( std::set<ft::FlagType> flags)
{
    for (auto kFlag : flags){addKFlag(kFlag);}
}
//======================================================
void KmerClass::setKPositions( std::set<size_t> kPositions, uint offset)
{
    for (auto kPosition : kPositions){addKPosition(kPosition, offset);}
}

//======================================================
void KmerClass::addQuery(ft::QIdT query){this->getQueryIDs().insert(query);}
void KmerClass::addKFlag(ft::FlagType flag){this->getKFlags().insert(flag);}

//======================================================
void KmerClass::addKPosition(size_t kPosition, uint offset)
{
    size_t kPos = kPosition + offset;
    std::set<size_t> positions = this->_positions;
    positions.insert(kPos);
}

//======================================================
uint KmerClass::getKmerMapSize(){return this->_kmer.size();}

//======================================================
bool KmerClass::isKmerEqual(KmerClass test) const {
    return _kmer == test.getKmer();
}

//======================================================
bool KmerClass::hasKmer(std::string test) const {
    return this->_kmer == test;
}

//======================================================
void KmerClass::convertPosToReadID(uint readLength)
{
    std::set<size_t> positions = this->_positions;
    for (auto pos : positions) {
        auto r = (size_t) std::ceil(pos / (readLength + 1));
    }
}

bool KmerClass::operator< (const ft::KmerClass &k) const {return _kmer < k._kmer;}
//======================================================
KmerClass::~KmerClass()
{
}

}
