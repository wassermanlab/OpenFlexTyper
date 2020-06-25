#ifndef PROPERTIESCLASS_H
#define PROPERTIESCLASS_H


#include <set>
#include <iostream>
#include <map>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

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
    SearchType _searchType;

    uint _kmerSize;
    uint _overlap;
    uint _stride;
    uint _maxKmers;
    uint _readLength;
    uint _maxOccurences ;
    uint _threadNumber;
    uint _maxKmersPerQuery;
    uint _maxTotalKmers;

    bool _kmerCounts;
    bool _multithread;
    bool _refOnly;
    bool _returnMatchesOnly;
    bool _overcounted;
    bool _ignoreNonUniqueKmers;
    bool _crossover;
    bool _printSearchTime;

    fs::path _pathToQueryFile;
    fs::path _indexFileLocation;
    fs::path _outputFolder;
    fs::path _matchingReads;
    fs::path _inputFastQ;

    ////////////////////////////////////////////////////////////////////////
    /// \brief Parameter getters and setters
    ////////////////////////////////////////////////////////////////////////
    SearchType getSearchType();
    void setSearchType(ft::SearchType searchType);

    uint getKmerSize();
    uint getOverlap();
    uint getStride();
    uint getMaxKmers();
    uint getReadLength();
    uint getMaxOcc();
    uint getThreadNumber();
    uint getMaxKmersPerQuery();
    uint getMaxTotalKmers();

    void setKmerSize(uint kmerSize);
    void setOverlap(uint overlap);
    void setStride(uint stride);
    void setMaxKmers(uint maxKmers);
    void setReadLength(uint readlength);
    void setMaxOcc(uint maxOcc);
    void setThreadNumber(uint threadNumber);
    void setMaxKmersPerQuery(uint maxKmersPerQ);
    void setMaxTotalKmers(uint maxTotalKmers);

    ////////////////////////////////////////////////////////////////////////
    /// \brief Flag getters and setters
    ////////////////////////////////////////////////////////////////////////
    bool getKmerCountsFlag();
    bool getMultithreadFlag();
    bool getRefOnlyFlag();
    bool getMatchesOnlyFlag();
    bool getOverCountedFlag();
    bool getIgnoreNonUniqueKmersFlag();
    bool getCrossoverFlag();
    bool getPrintSearchTimeFlag();

    void setKmerCountsFlag(bool kmerCounts);
    void setMultithreadFlag(bool multithread);
    void setRefOnlyFlag(bool refOnly);
    void setMatchesOnlyFlag(bool matchesOnly);
    void setOverCountedFlag(bool overcounted);
    void setIgnoreNonUniqueKmersFlag(bool ignoreNonUnique);
    void setCrossoverFlag(bool crossover);
    void setPrintSearchTimeFlag(bool printSearchTime);


};

}





#endif // PROPERTIESCLASS_H
