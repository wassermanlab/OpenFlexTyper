#ifndef KMERCLASS_H
#define KMERCLASS_H

#include <set>
#include <bitset>
#include <iostream>
#include <map>
#include "ftPropsClass.h"

namespace ft {

////////////////////////////////////////////////////////////////////////
/// \class Kmer Class
/// \brief A class that contains information for a single Kmer
////////////////////////////////////////////////////////////////////////

class KmerClass
{
public:
    /// Constructor
    /// \param string Kmer
    KmerClass(std::string kmer);
    KmerClass();

    /// Class Destructor
    virtual ~KmerClass();

    /// @name Getters
    /// Constant functions to return properties of the Kmer
    /// @{
    /// \public
    /// \fn
    const std::string& getKmer() const;
    const std::bitset<8>& getKFlags()const;
    const std::set<long long>& getKPositions()const;
    const std::set<ft::ReadID>& getReadIDs()const;
    uint getOCC()const {return _occ;};
    //uint getKmerMapSize()const;
    /// @}

    /// \name Setters
    /// Non-constant functions to update properties of the kmer class
    /// @{
    /// \public
    void setKFlags(std::set<ft::FlagType> kFlags);
    void setKPositions(const std::set<long long>& kPositions);
    void adjustPosForOffset(uint offset = 0);
    void setReadIDs(std::set<ft::ReadID> readIDs);
    void setOCC(uint occ) {_occ=occ;};
    /// @}

    /// \name Adders
    /// Non-constant functions to add properties to the kmer class
    /// @{
    void addKFlag(const ft::FlagType& kFlag);
    void addKPosition(const size_t& kPosition, const uint& offset = 0);
    void addReadID(const ft::ReadID& readID);
    /// @}

    /// \name Removers
    /// Non-constant functions to remove properties from the kmer class
    /// @{
    void removeKFlag(ft::FlagType kFlag);
    void removeKPosition(size_t kPosition, uint offset = 0);
    void removeReadID(ft::ReadID readID);
    /// @}

    /// \name Checkers
    /// Constant functions to check the properties of the kmer class
    /// @{
    bool isKmerEqual(const KmerClass& test) const;
    bool hasKmer(const std::string& test) const;
    bool hasFlag(const ft::FlagType& flag);
    bool hasKPosition(const size_t& position) const;
    bool hasReadID(const ft::ReadID& readID) const;
    /// @}

    /// \name Manipulation
    /// Functions to convert between index positions, and read IDs
    /// @{
    void convertPosToReadID(uint readLength, uint numOfReads, bool pairedReads, bool indexRevComp = false);
    bool matchingReadID(const ft::ReadID &a, const ft::ReadID &b) const;
    void adjustPositionsWithOffset(uint offset);
    /// @}

    /// \name Overloaded Operators
    /// @{
    bool operator< (const ft::KmerClass &k) const;
    bool operator== (const ft::KmerClass &k) const;
    /// @}

private:
    /// @name Properties
    /// @{
    /// \private
    /// \var
    std::string _kmer;
    std::bitset<8> _kFlags;
    std::set<long long> _positions;
    std::set<ft::ReadID> _readIDs;
    uint _occ; //from sdsl::count(_index, _kmer)
    bool _isOffsetAdjusted;
    /// @}

};
}

#endif // KMERCLASS_H
