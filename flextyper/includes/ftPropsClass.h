////////////////////////////////////////////////////////////////////////
/// \copyright Copyright (c) 2020, Wasserman lab
////////////////////////////////////////////////////////////////////////

#ifndef PROPERTIESCLASS_H
#define PROPERTIESCLASS_H

#include <climits>
#include <set>
#include <bitset>
#include <iostream>
#include <fstream>
#include <chrono>
#include <map>
#include <experimental/filesystem>
#include <QSettings>
#include <LogClass.h>

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

enum FlagType { ABK = 0x0001, OCK = 0x0002, NUK = 0x0003}; // abundant, overcounted, non-unique

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

    struct CmdLineArg {
        std::string outputFile;
        std::string iniFile;
        uint kmerSize;
        uint stride;
        uint maxOccurences;
        bool unique;
        bool verbose;
    };

    ////////////////////////////////////////////////////////////////////////
    /// \brief Init
    ////////////////////////////////////////////////////////////////////////
    void init(const fs::path& pathToQueryFile       ,
              uint kmerSize                         ,
              uint readLength                       ,
              const fs::path& indexPropsFile        ,
              const fs::path& outputFolder          ,
              const fs::path& outputFile            ,
              bool refOnly                          ,
              bool revCompSearch                    ,
              SearchType searchType                 ,
              bool multithread              = false ,
              uint overlap                  = 0     ,
              bool returnMatchesOnly        = false ,
              uint stride                   = 10    ,
              uint maxOccurences            = 200   ,
              uint numOfThreads             = 1     ,
              bool outputNonUniqueKmers       = false ,
              bool outputOverCountedKmers     = false ,
              bool ignoreNonUniqueKmers     = true  ,
              bool ignoreOverCountedKmers   = true  ,
              bool countAsPairs             = false ,
              bool crossover                = false ,
              bool printSearchTime          = false ,
              uint maxKmers                 = UINT_MAX,
              uint totalKmers               = UINT_MAX,
              bool printInputs              = false,
              bool matchingReads            = false);

    void initFromQSettings(FTProp::CmdLineArg& arg);

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

    const std::bitset<8>& getFlagsToOutput() const;
    const std::bitset<8>& getFlagsToNotCount() const;
    bool countFlag(ft::FlagType flag) const;
    bool outputFlag(ft::FlagType flag) const;
    void setFlagToOutput(ft::FlagType flag);
    void setFlagToNotCount(ft::FlagType flag);
    void resetFlagToOutput(ft::FlagType flag);
    void resetFlagToNotCount(ft::FlagType flag);

    ////////////////////////////////////////////////////////////////////////
    /// \brief Flag getters
    ////////////////////////////////////////////////////////////////////////
    bool getMultithreadFlag() const;
    bool getRefOnlyFlag() const;
    bool getMatchesOnlyFlag() const;
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

    void setTestProps(const uint numOfReads, const uint readLength, bool _revComp, bool countAsPairs = false);
    void setOutputFolder(const fs::path& outputFolder);

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

    std::bitset<8> _flagsToOutput;
    std::bitset<8> _flagsToNotCount;

    bool _multithread; //run search in parallel
    bool _refOnly; // single sequence for each query
    bool _matchesOnly; // only output positive hits
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
