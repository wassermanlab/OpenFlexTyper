#ifndef PROPERTIESCLASS_H
#define PROPERTIESCLASS_H

#include <climits>
#include <set>
#include <iostream>
#include <fstream>
#include <chrono>
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

const   std::string QUERYTYPE_REF  = "REF";
const   std::string QUERYTYPE_ALT  = "ALT";
const   std::string QUERYTYPE_CRO  = "CRO";

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
    /// Benchmark
    ////////////////////////////////////////////////////////////////////////
    class Benchmark {
    public:
        Benchmark(int indent): _indent(indent) {
           update();
        };
        virtual ~Benchmark() {};
        void update() {_start = std::chrono::steady_clock::now();};
        void now(const std::string tag) {
            _end = std::chrono::steady_clock::now();
            FTProp::Log << "Benchmark:";
            for(int i=0; i<_indent; i++)
                FTProp::Log << "**";
            FTProp::Log << tag << std::chrono::duration_cast<std::chrono::seconds>(_end - _start).count() << " in sec" << std::endl;
            _start = _end;
        };
    private:
        std::chrono::steady_clock::time_point _start;
        std::chrono::steady_clock::time_point _end;
        int _indent;
    };

    ////////////////////////////////////////////////////////////////////////
    /// \brief Init
    ////////////////////////////////////////////////////////////////////////
    void init(const fs::path& pathToQueryFile       ,
              uint kmerSize                         ,
              uint readLength                       ,
              const fs::path& indexPropsFile        ,
              const fs::path& outputFile            ,
              bool refOnly                          ,
              bool revCompSearch                    ,
              SearchType searchType                 ,
              bool multithread              = false ,
              uint overlap                  = 0     ,
              bool returnMatchesOnly        = false ,
              bool kmerCounts               = false ,
              uint stride                   = 10    ,
              uint maxOccurences            = 200   ,
              uint numOfThreads             = 1     ,
              bool flagOverCountedKmers     = false ,
              bool flagNonUniqueKmers       = false ,
              bool ignoreNonUniqueKmers     = true  ,
              bool countAsPairs             = false,
              bool crossover                = false ,
              bool printSearchTime          = false,
              uint maxKmers                 = UINT_MAX,
              uint totalKmers               = UINT_MAX,
              bool printInputs              = false,
              bool matchingReads            = false);

    void initFromQSettings(std::string configFile, bool printInputs);

    void setVerbose(bool verbose);
    ////////////////////////////////////////////////////////////////////////
    /// \brief Import Index Properties from INI
    ////////////////////////////////////////////////////////////////////////
    void loadIndexProps(const fs::path& _indexPropsFile, bool printInputs);
    void initIndexProps( const bool pairedReads,
                         const bool revComp,
                         fs::path buildDir,
                         fs::path indexDir,
                         std::string indexFileName,
                         std::string readSetName,
                         fs::path inputFastQ,
                         uint numOfReads,
                         uint numOfIndexes,
                         bool printInputs = false);

    void printToStdOut(const std::string outputString) const;
    ////////////////////////////////////////////////////////////////////////
    /// \brief malliable properties
    ////////////////////////////////////////////////////////////////////////
    std::map<fs::path, uint> _indexSet; //index path, index offset

    ////////////////////////////////////////////////////////////////////////
    /// \brief Parameter getters and setters
    ////////////////////////////////////////////////////////////////////////
    SearchType getSearchType() const;

    std::string getReadSetName()const ;
    std::string getIndexFileName()const ;

    uint getKmerSize() const;
    uint getOverlap() const;
    uint getStride() const;
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
    bool getNonUniqueFlag() const;
    bool getIgnoreNonUniqueKmersFlag() const;
    bool getCrossoverFlag() const;
    bool getPrintSearchTimeFlag() const;
    bool getPairedReadFlag() const;
    bool getCountAsPairsFlag() const;
    bool getRevCompSearchFlag() const;
    bool getIndexRevCompFlag() const;
    bool getMatchingReadsFlag() const;

    bool isVerbose() const;
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
    void setOutputFolder(const fs::path& outputFolder);

    static void OpenLog(const std::string& name);
    static void CloseLog();
    static std::fstream Log;

private:
    ////////////////////////////////////////////////////////////////////////
    /// \brief fixed properties
    ////////////////////////////////////////////////////////////////////////

    SearchType _searchType;
    std::string _readSetName;
    std::string _indexFileName;

    uint _numOfReads; // total individual reads, note: if countAsPairs, then equal to the number of Pairs of reads.
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
    uint _readLength;
    uint _maxOccurences ;
    uint _maxThreads;
    uint _maxKmersPerQuery;
    uint _maxTotalKmers;

    bool _kmerCounts;
    bool _multithread; //run search in parallel
    bool _refOnly; // single sequence for each query
    bool _matchesOnly; // only output positive hits
    bool _overcounted; //output a list of OCK
    bool _nonUnique; //output a list of NUK
    bool _ignoreNonUniqueKmers; //discount the NUK
    bool _crossover; //search for crossover counts
    bool _printSearchTime;
    bool _pairedReads; // paired reads
    bool _countAsPairs; // only count one hit per read pair
    bool _revCompSearch; //generate and search for _qkRCMap
    bool _indexRevComp; //do the index files contain the reverse complement
    bool _matchingReads; //create files that contain reads that match to each query
    bool _verbose; //print to std::cout

};

}

#endif // PROPERTIESCLASS_H
