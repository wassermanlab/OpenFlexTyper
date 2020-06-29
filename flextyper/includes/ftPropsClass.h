#ifndef PROPERTIESCLASS_H
#define PROPERTIESCLASS_H

#include <climits>
#include <set>
#include <iostream>
#include <map>
#include <experimental/filesystem>
#include <QSettings>

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
    /// \brief FTProp
    ////////////////////////////////////////////////////////////////////////
    FTProp();

    ////////////////////////////////////////////////////////////////////////
    /// \brief ~FTProp
    ////////////////////////////////////////////////////////////////////////
    virtual ~FTProp();

    ////////////////////////////////////////////////////////////////////////
    /// \brief Init
    ////////////////////////////////////////////////////////////////////////
    void init(const fs::path& pathToQueryFile       ,
              uint kmerSize                         ,
              uint readLength                       ,
              const fs::path& indexLocation         ,
              const fs::path& outputFile            ,
              bool refOnly                          ,
              SearchType searchType                 ,
              bool multithread              = false ,
              const fs::path& inputFastQ    = ""    ,
              uint overlap                  = 0     ,
              bool returnMatchesOnly        = false ,
              bool kmerCounts               = false ,
              uint stride                   = 10    ,
              uint maxOccurences            = 200   ,
              uint maxThreads             = 1     ,
              bool flagOverCountedKmers     = false ,
              bool ignoreNonUniqueKmers     = true  ,
              bool crossover                = false ,
              bool printSearchTime          = false,
              uint maxKmers                 = UINT_MAX,
              uint totalKmers               = UINT_MAX,
              const fs::path& matchingReads = "");


    void initFromQSettings (std::string configFile, bool printInputs);

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
    uint _maxThreads;
    uint _maxKmersPerQuery;
    uint _maxTotalKmers;

    bool _kmerCounts;
    bool _multithread;
    bool _refOnly;
    bool _matchesOnly;
    bool _overcounted;
    bool _ignoreNonUniqueKmers;
    bool _crossover;
    bool _printSearchTime;

    fs::path _pathToQueryFile;
    fs::path _indexFileLocation;
    fs::path _outputFolder;
    fs::path _matchingReadFQ;
    fs::path _inputFastQ;
    fs::path _outputFile;
    std::set<fs::path> _indexSet;



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
    uint getMaxThreads();
    uint getMaxKmersPerQuery();
    uint getMaxTotalKmers();

    void setKmerSize(uint kmerSize);
    void setOverlap(uint overlap);
    void setStride(uint stride);
    void setMaxKmers(uint maxKmers);
    void setReadLength(uint readlength);
    void setMaxOcc(uint maxOcc);
    void setMaxThreads(uint maxThreads);
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

    ////////////////////////////////////////////////////////////////////////
    /// \brief File getters and setters
    ////////////////////////////////////////////////////////////////////////
    void setPathToQueryFile( fs::path pathToQueryFile);
    void setIndexFileLocation(fs::path indexFileLocation);
    void setOutputFolder(fs::path outputFolder);
    void setMatchingReadFQ(fs::path matchingReadFQ);
    void setInputFastQ(fs::path inputFastQ);
    void setOutputFile(fs::path outputFile);
    void setIndexSet(std::set<fs::path>);

    fs::path getPathToQueryFile();
    fs::path getIndexFileLocation();
    fs::path getOutputFolder();
    fs::path getMatchingReadFQ();
    fs::path getInputFastQ();
    fs::path getOutputFile();
    std::set<fs::path> getIndexSet();
};



}

#endif // PROPERTIESCLASS_H
