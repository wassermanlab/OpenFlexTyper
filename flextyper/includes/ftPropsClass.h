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

enum QueryType {REF = 1, ALT, CRO};
enum Orientation {FWD = 1, REV};
typedef std::string     SearchType;             // SearchType declaration
const   std::string     CENTERED = "CENTERED";  // search type centered approach
const   std::string     SLIDING  = "SLIDING";   // search type sliding approach

typedef std::pair<int, QueryType>  QIdT; // int is the query ID
typedef std::pair<int, int> ReadID; // pair (id, pair 1 or pair 2)
typedef std::tuple<uint, std::string, std::string, std::string>  Query;

enum FlagType { ABK = 1, OCK, NUK}; // abundant, overcounted, non-unique

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
              const fs::path& indexPropsFile        ,
              const fs::path& outputFile            ,
              bool refOnly                          ,
              SearchType searchType                 ,
              bool multithread              = false ,
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
              bool printInputs              = false);

    void initFromQSettings(std::string configFile, bool printInputs);


    ////////////////////////////////////////////////////////////////////////
    /// \brief Import Index Properties from INI
    ////////////////////////////////////////////////////////////////////////
    void loadIndexProps(const fs::path& _indexPropsFile, bool printInputs);
    void initIndexProps( const bool pairedReads,
                         const bool revComp,
                         fs::path buildDir,
                         fs::path indexDir,
                         std::string readSetName,
                         fs::path inputFastQ,
                         uint numOfReads,
                         uint numOfIndexes,
                         bool printInputs = false);

    ////////////////////////////////////////////////////////////////////////
    /// \brief malliable properties
    ////////////////////////////////////////////////////////////////////////
    std::map<fs::path, uint> _indexSet; //index path, index offset

    ////////////////////////////////////////////////////////////////////////
    /// \brief Parameter getters and setters
    ////////////////////////////////////////////////////////////////////////
    SearchType getSearchType() const;

    std::string getReadSetName()const ;

    uint getKmerSize() const;
    uint getOverlap() const;
    uint getStride() const;
    uint getMaxKmers() const;
    uint getReadLength() const;
    uint getMaxOcc() const;
    uint getMaxThreads() const;
    uint getMaxKmersPerQuery() const;
    uint getMaxTotalKmers() const;
    uint getNumOfIndexes() const;
    uint getNumOfReads() const;

    ////////////////////////////////////////////////////////////////////////
    /// \brief Flag getters
    ////////////////////////////////////////////////////////////////////////
    bool getKmerCountsFlag() const;
    bool getMultithreadFlag() const;
    bool getRefOnlyFlag() const;
    bool getMatchesOnlyFlag() const;
    bool getOverCountedFlag() const;
    bool getIgnoreNonUniqueKmersFlag() const;
    bool getCrossoverFlag() const;
    bool getPrintSearchTimeFlag() const;
    bool getPairedReadFlag() const;
    bool getRevCompSearchFlag() const;
    bool getIndexRevCompFlag() const;
    bool getMatchingReadsFlag() const;

    ////////////////////////////////////////////////////////////////////////
    /// \brief File getters
    ////////////////////////////////////////////////////////////////////////

    const fs::path& getPathToQueryFile() const;
    const fs::path& getIndexDir() const;
    const fs::path& getOutputFolder() const;
    const fs::path& getMatchingReadFQ() const;
    const fs::path& getInputFastQ() const;
    const fs::path& getOutputFile() const;
    const std::map<fs::path, uint>& getIndexSet() const;
    const fs::path& getBuildDir() const;
    const fs::path& getR1() const;
    const fs::path& getR2() const;

    void addToIndexSet(const fs::path& index, u_int offset);

    void setTestProps(const uint numOfReads, const uint readLength, bool _revComp);

private:
    ////////////////////////////////////////////////////////////////////////
    /// \brief fixed properties
    ////////////////////////////////////////////////////////////////////////

    SearchType _searchType;
    std::string _readSetName;

    uint _numOfReads;
    uint _numOfIndexes;

    fs::path _pathToQueryFile;

    fs::path _buildDir;
    fs::path _indexDir;

    fs::path _R1;
    fs::path _R2;
    fs::path _inputFastQ;

    fs::path _outputFolder;
    fs::path _outputFile;

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
    bool _pairedReads;
    bool _revCompSearch; //generate and search for _qkRCMap
    bool _indexRevComp; //do the index files contain the reverse complement
    bool _matchingReads; //create files that contain reads that match to each query
};

}

#endif // PROPERTIESCLASS_H
