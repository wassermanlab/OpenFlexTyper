#include <set>
#include <iostream>
#include <map>
#include <math.h>
#include "kmerClass.h"


namespace ft {

KmerClass::KmerClass(std::string kmer)
    : _kmer(kmer),
    _kFlags(),
    _positions(),
    _readIDs()
{
}

//=================== GETTERS =========================
std::string KmerClass::getKmer() const{return this->_kmer;}
std::map<ft::FlagType, bool> KmerClass::getKFlags() const {return this->_kFlags;}
std::set<size_t> KmerClass::getKPositions() const {return this->_positions;}
uint KmerClass::getKmerMapSize() const {return this->_kmer.size();}
std::set<ft::ReadID> KmerClass::getReadIDs() const {return this->_readIDs;}

//================== SETTERS ===========================
void KmerClass::setKFlags( std::set<ft::FlagType> flags)
{
    for (auto flag: flags){
        _kFlags[flag] = true;
    }
}
void KmerClass::setKPositions( std::set<size_t> kPositions, uint offset)
{
    for (auto kPosition : kPositions){
        size_t kPos = kPosition + offset;
        _positions.insert(kPos);
       }
}
void KmerClass::setReadIDs(std::set<ft::ReadID> readIDs)
{
        _readIDs = readIDs;
}

//===================== ADDERS ==========================
void KmerClass::addKFlag(const ft::FlagType& flag)
{
    _kFlags[flag] = true;
}
void KmerClass::addKPosition(const size_t& kPosition, const uint& offset)
{
    size_t kPos = kPosition + offset;
    _positions.insert(kPos);
}
void KmerClass::addReadID(const ft::ReadID& readID)
{    _readIDs.insert(readID);}

//===================== REMOVERS =======================+
void KmerClass::removeKFlag(ft::FlagType flag){
    this->_kFlags[flag] = false;
    }
void KmerClass::removeKPosition(size_t kPosition, uint offset)
{
    size_t kPos = kPosition + offset;
    _positions.erase(kPos);
}
void KmerClass::removeReadID(ft::ReadID readID){_readIDs.erase(readID);}

//==================== CHECKERS =========================
bool KmerClass::isKmerEqual(KmerClass test) const {
    return _kmer == test.getKmer();
}
bool KmerClass::hasKmer(std::string test) const {
    return _kmer == test;
}
bool KmerClass::hasFlag(ft::FlagType flag) const{
    return this->getKFlags()[flag];
}
bool KmerClass::hasKPosition(size_t kPosition) const{
    const bool is_in = _positions.find(kPosition) != _positions.end();
    return is_in;
}
bool KmerClass::hasReadID(ft::ReadID read ) const {

    const bool is_in = _readIDs.find(read) != _readIDs.end();
    return is_in;
}

//====================== CONVERT ========================
void KmerClass::convertPosToReadID(uint readLength, uint numOfReads, bool revComp)
{
//    std::cout << "read Length " << readLength << std::endl;
//    std::cout << "num of Reads " << numOfReads << std::endl;
//    std::cout << " rev comp " << revComp << std::endl;

    if (readLength == 0)
    {
        std::cout << "ERROR: Read Length not set " << std::endl;
    }
    if (numOfReads == 0)
    {
        std::cout << "ERROR: Num of Reads not set " << std::endl;
    }

    for (auto pos : _positions) {
        u_int r = std::ceil(pos / (readLength + 1)) ;
        int rID = r%numOfReads;
        rID +=1;
        u_int readType = std::ceil((r+1)/float(numOfReads));
        //std::cout << "r " << float(r) << " num of Reads "<< float(numOfReads) << std::endl;
        //std::cout << "read Type " << readType << std::endl;
        if (revComp){readType = ceil((readType+1)/2);}
        //std::cout <<"read ID " << rID <<  " read Type " << readType << std::endl;
        addReadID(std::make_pair(rID, readType));
    }
}

//===================== OVERLOAD ========================
bool KmerClass::operator< (const ft::KmerClass &k) const {return _kmer < k._kmer;}


KmerClass::~KmerClass()
{
}

}
