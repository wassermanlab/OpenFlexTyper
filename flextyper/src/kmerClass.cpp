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
KmerClass::KmerClass(){}

//=================== GETTERS =========================
const std::string& KmerClass::getKmer() const{return _kmer;}
const std::bitset<8>& KmerClass::getKFlags() const {return _kFlags;}
const std::set<long long>& KmerClass::getKPositions() const {return _positions;}
const std::set<ft::ReadID>& KmerClass::getReadIDs() const {return _readIDs;}

//================== SETTERS ===========================
void KmerClass::setKFlags( std::set<ft::FlagType> flags)
{
    for (auto flag: flags){
        _kFlags.set(flag);
    }
}
void KmerClass::setKPositions(const std::set<long long>& kPositions)
{
    _positions = kPositions;
}
void KmerClass::setReadIDs(std::set<ft::ReadID> readIDs)
{
        _readIDs = readIDs;
}

void KmerClass::adjustPosForOffset(uint offset)
{
    std::set < long long > positions ;
    std::set < long long > kPositions = getKPositions();
    for (long long kPosition : kPositions){
        long long kPos = kPosition + offset;
        positions.insert(kPos);
       }
    setKPositions(positions);
}

//===================== ADDERS ==========================
void KmerClass::addKFlag(const ft::FlagType& flag)
{
    _kFlags.set(flag);
}
void KmerClass::addKPosition(const size_t& kPosition, const uint& offset)
{
    size_t kPos = kPosition + offset;
    _positions.insert(kPos);
}
void KmerClass::addReadID(const ft::ReadID& readID)
{
    if (!hasReadID(readID)){
        _readIDs.insert(readID);
    }else {
        //std::cout << "ReadID already added" << std::endl;
    }
}

//===================== REMOVERS =======================+
void KmerClass::removeKFlag(ft::FlagType flag){
    _kFlags.reset(flag);
}
void KmerClass::removeKPosition(size_t kPosition, uint offset)
{
    size_t kPos = kPosition + offset;
    _positions.erase(kPos);
}
void KmerClass::removeReadID(ft::ReadID readID){_readIDs.erase(readID);}

//==================== CHECKERS =========================
bool KmerClass::isKmerEqual(const KmerClass& test) const {
    return _kmer == test.getKmer();
}
bool KmerClass::hasKmer(const std::string& test) const {
    return _kmer == test;
}
bool KmerClass::hasFlag(const ft::FlagType& flag) {
    return _kFlags.test(flag);
}
bool KmerClass::hasKPosition(const size_t& kPosition) const{
    const bool is_in = _positions.find(kPosition) != _positions.end();
    return is_in;
}

bool KmerClass::matchingReadID(const ft::ReadID &a, const ft::ReadID &b) const
{
    return (a.first == b.first && a.second == b.second);
}

bool KmerClass::hasReadID(const ft::ReadID& read ) const {

    bool is_in = false;
    for (ft::ReadID rID : getReadIDs())
    {
       if (matchingReadID(rID, read) == true)
        {
            is_in = true;
            continue;
        }
    }
    return is_in;
}

//====================== CONVERT ========================
void KmerClass::convertPosToReadID(uint readLength, uint numOfReads, bool pairedReads, bool indexRevComp)
{
    if (readLength == 0)
    {
        std::cout << "ERROR: Read Length not set " << std::endl;
    }
    if (numOfReads == 0)
    {
        std::cout << "ERROR: Num of Reads not set " << std::endl;
    }
    if (pairedReads)
    {
        numOfReads = numOfReads/2;
    }

    for (auto pos : _positions) {
        u_int r = std::ceil(pos / (readLength + 1)) ;
        int rID = r%numOfReads;
        rID +=1;
        u_int readType = std::ceil((r+1)/float(numOfReads));

        if (indexRevComp){readType = ceil((readType+1)/2);}

        addReadID(std::make_pair(rID, readType));
    }

}

//===================== OVERLOAD ========================
bool KmerClass::operator< (const ft::KmerClass &k) const {
    int output = _kmer.compare(k._kmer);

    // lower.compare(higher) < 0 => true
    if (output <0 )
    {
        return true;
    }
    else return false;
}
bool KmerClass::operator== (const ft::KmerClass &k) const {return _kmer == k._kmer;}

KmerClass::~KmerClass()
{
}

}
