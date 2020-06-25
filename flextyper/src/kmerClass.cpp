#include <set>
#include <iostream>
#include <map>
#include <math.h>
#include "kmerClass.h"


namespace ft {

KmerClass::KmerClass(std::string kmer)
    : _kmer(kmer),
    _queryIDs(),
    _kFlags(),
    _positions(),
    _readIDs()
{
}

//=================== GETTERS =========================
std::string KmerClass::getKmer() const{return this->_kmer;}
std::set<ft::QIdT> KmerClass::getQueryIDs(){return this->_queryIDs;}
std::set<ft::FlagType> KmerClass::getKFlags(){return this->_kFlags;}
std::set<size_t> KmerClass::getKPositions(){return this->_positions;}
uint KmerClass::getKmerMapSize(){return this->_kmer.size();}
std::set<int> KmerClass::getReadIDs(){return this->_readIDs;}

//================== SETTERS ===========================
void KmerClass::setQueryIDs(std::set<ft::QIdT> queries)
{
    for (auto qIDT : queries){addQuery(qIDT);}
}
void KmerClass::setKFlags( std::set<ft::FlagType> flags)
{
    for (auto kFlag : flags){addKFlag(kFlag);}
}
void KmerClass::setKPositions( std::set<size_t> kPositions, uint offset)
{
    for (auto kPosition : kPositions){addKPosition(kPosition, offset);}
}
void KmerClass::setReadIDs(std::set<int> readIDs)
{
    for (auto readID : readIDs){addReadID(readID);}
}

//===================== ADDERS ==========================
void KmerClass::addQuery(ft::QIdT query){this->getQueryIDs().insert(query);}
void KmerClass::addKFlag(ft::FlagType flag){this->getKFlags().insert(flag);}
void KmerClass::addKPosition(size_t kPosition, uint offset)
{
    size_t kPos = kPosition + offset;
    std::set<size_t> positions = this->_positions;
    positions.insert(kPos);
}
void KmerClass::addReadID(int readID){this->getReadIDs().insert(readID);}

//===================== REMOVERS =======================+
void KmerClass::removeQuery(ft::QIdT query){this->getQueryIDs().erase(query);}
void KmerClass::removeKFlag(ft::FlagType flag){this->getKFlags().erase(flag);}
void KmerClass::removeKPosition(size_t kPosition, uint offset)
{
    size_t kPos = kPosition + offset;
    std::set<size_t> positions = this->_positions;
    positions.erase(kPos);
}
void KmerClass::removeReadID(int readID){this->getReadIDs().erase(readID);}

//==================== CHECKERS =========================
bool KmerClass::isKmerEqual(KmerClass test) const {
    return _kmer == test.getKmer();
}
bool KmerClass::hasKmer(std::string test) const {
    return this->_kmer == test;
}
bool KmerClass::hasQuery(ft::QIdT query) const {
    std::set<ft::QIdT> queries = this->_queryIDs;
    const bool is_in = queries.find(query) != queries.end();
    return is_in;
}
bool KmerClass::hasFlag(ft::FlagType flag) const{
    std::set<ft::FlagType> flags = this->_kFlags;
    const bool is_in = flags.find(flag) != flags.end();
    return is_in;
}
bool KmerClass::hasKPosition(size_t kPosition) const{
    std::set<size_t> kPositions = this->_positions;
    const bool is_in = kPositions.find(kPosition) != kPositions.end();
    return is_in;
}
bool KmerClass::hasReadID(int read) const {
    std::set<int> reads = this->_readIDs;
    const bool is_in = reads.find(read) != reads.end();
    return is_in;
}

//====================== CONVERT ========================
void KmerClass::convertPosToReadID(uint readLength)
{
    std::set<size_t> positions = this->_positions;
    for (auto pos : positions) {
        auto r = (size_t) std::ceil(pos / (readLength + 1));
        this->addReadID(r);
    }
}

//===================== OVERLOAD ========================
bool KmerClass::operator< (const ft::KmerClass &k) const {return _kmer < k._kmer;}

KmerClass::~KmerClass()
{
}

}
