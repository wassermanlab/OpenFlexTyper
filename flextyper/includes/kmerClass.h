#ifndef KMERCLASS_H
#define KMERCLASS_H

#include <set>
#include <iostream>
#include <map>
#include "typedefs.h"


namespace ft {


class KmerClass
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// \brief KmerClass
    ////////////////////////////////////////////////////////////////////////
    KmerClass(std::string kmer);

    ////////////////////////////////////////////////////////////////////////
    /// \brief ~KmerClass
    ////////////////////////////////////////////////////////////////////////
    virtual ~KmerClass();

    ////////////////////////////////////////////////////////////////////////
    /// \brief getters
    ////////////////////////////////////////////////////////////////////////
    std::string getKmer() const;
    std::set<ft::QIdT> getQueryIDs();
    std::set<ft::FlagType> getKFlags();
    std::set<size_t> getKPositions();
    std::set<uint> getReadIDs();

    ////////////////////////////////////////////////////////////////////////
    /// \brief setters
    ////////////////////////////////////////////////////////////////////////
    void setQueryIDs(std::set<ft::QIdT> queries);
    void setKFlags(std::set<ft::FlagType> kFlags);
    void setKPositions(std::set<size_t> kPositions, uint offset = 0);
    void setReadIDs(std::set<uint> readIDs);

    void addQuery(ft::QIdT query);
    void addKFlag(ft::FlagType kFlag);
    void addKPosition(size_t kPosition, uint offset = 0);
    void addReadID(uint readID);

    bool isKmerEqual(KmerClass test) const;
    bool hasKmer(std::string test) const;
    uint getKmerMapSize();
    void convertPosToReadID(uint readlength);

    ////////////////////////////////////////////////////////////////////////
    /// \brief properties
    ////////////////////////////////////////////////////////////////////////
    std::string _kmer;
    std::set<ft::QIdT> _queryIDs;
    std::set<ft::FlagType> _kFlags;
    std::set<size_t> _positions;
    std::set<uint> _readIDs;

    bool operator< (const ft::KmerClass &k) const;

private:



};
}


#endif // KMERCLASS_H
