#ifndef PROPERTIESCLASS_H
#define PROPERTIESCLASS_H


#include <set>
#include <iostream>
#include <map>

namespace ft {


enum QueryType {
    REF = 1, ALT, CRO
};

typedef std::string     SearchType;             // SearchType declaration
const   std::string     CENTERED = "CENTERED";  // search type centered approach
const   std::string     SLIDING  = "SLIDING";   // search type sliding approach

typedef std::pair<int, QueryType>  QIdT; // int is the query ID
typedef std::tuple<uint, std::string, std::string, std::string>  Query;

enum FlagType {
    ABK = 1, OCK, NUK // abundant, overcounted, non-unique
};

class FTProp {
public:
    ////////////////////////////////////////////////////////////////////////
    /// \brief QueryClass
    ////////////////////////////////////////////////////////////////////////
    FTProp();

    ////////////////////////////////////////////////////////////////////////
    /// \brief ~QueryClass
    ////////////////////////////////////////////////////////////////////////
    virtual ~FTProp();

    ////////////////////////////////////////////////////////////////////////
    /// \brief properties
    ////////////////////////////////////////////////////////////////////////
    uint _kmerSize;
    bool _refOnly;
    SearchType _searchType;
    uint _overlap;
    uint _stride;
    bool _kmerCounts;
    uint _maxKmers;

    ////////////////////////////////////////////////////////////////////////
    /// \brief getters
    ////////////////////////////////////////////////////////////////////////
    SearchType getSearchType();
    uint getKmerSize();
    uint getOverlap();
    uint getStride();
    uint getMaxKmers();
    uint getMaxTotalKmers();
    uint getMaxOcc();
    uint getReadLength();

    ////////////////////////////////////////////////////////////////////////
    /// \brief setters
    ////////////////////////////////////////////////////////////////////////
    void setKmerSize(uint kmerSize);
    void setSearchType(ft::SearchType searchType);
    void setOverlap(uint overlap);
    void setStride(uint stride);
    void setMaxKmers(uint maxKmers);
    void setMaxTotalKmers(uint maxTotalKmers);
    void setMaxOcc(uint maxOcc);
    void setReadLength(uint readlength);


    ////////////////////////////////////////////////////////////////////////
    /// \brief Flag getters and setters
    ////////////////////////////////////////////////////////////////////////
    bool getRefOnlyFlag();
    bool getIgnoreNonUniqueKmersFlag();
    bool getKmerCountsFlag();
    bool getCrossoverFlag();
    bool getOverCountedFlag();
    bool getMatchesOnlyFlag();

    void setRefOnlyFlag(bool refOnly);
    void setIgnoreNonUniqueKmersFlag(bool ignoreNonUnique);
    void setKmerCountsFlag(bool kmerCounts);
    void setCrossoverFlag(bool crossover);
    void setOverCountedFlag(bool overcounted);
    void setMatchesOnlyFlag(bool matchesOnly);


};

}





#endif // PROPERTIESCLASS_H
