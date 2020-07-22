#include <gtest/gtest.h>
#include "writerbridge.cpp"

using namespace std;
using namespace ft;

namespace ft {
class TestWriterBridge : public ::testing::Test {
protected:
    virtual void SetUp() {
        _indexPath = "testOutput/Test.fm9";
        offset = 0;
        pathToQueryFile = "testFiles/TestQuery.txt";
        kmerSize = 30;
        readLength =150;
        indexPropsFile = "testOutput/indexProps.ini";
        outputFolder = "testOutput";
        refOnly = false;
        searchType = CENTERED;
        multithread              = false ;
        overlap                  = 0     ;
        returnMatchesOnly        = false ;
        kmerCounts               = false ;
        stride                   = 10    ;
        maxOccurences            = 200   ;
        maxThreads               = 1     ;
        flagOverCountedKmers     = false ;
        ignoreNonUniqueKmers     = true  ;
        crossover                = false ;
        pairedReads = false;
        revComp = false;
        buildDir = "";
        indexDir = "testOutput";
        readSetName = "test";
        inputFastQ = "testFiles/test.fq";
        numOfReads = 10;
        numOfIndexes =1 ;
        printInputs = false;

    }
    virtual void TearDown() {}

    fs::path _indexPath ;
    u_int offset = 0;
    fs::path pathToQueryFile;
    uint kmerSize ;
    uint readLength;
    fs::path indexPropsFile ;
    fs::path outputFolder;
    bool refOnly ;
    SearchType searchType;
    bool multithread;
    uint overlap;
    bool returnMatchesOnly;
    bool kmerCounts;
    uint stride;
    uint maxOccurences;
    uint maxThreads;
    bool flagOverCountedKmers;
    bool ignoreNonUniqueKmers;
    bool crossover;
    bool pairedReads;
    bool revComp;
    fs::path buildDir;
    fs::path indexDir;
    std::string readSetName;
    fs::path inputFastQ;
    uint numOfReads;
    uint numOfIndexes;
    bool printInputs;


public:
    WriterBridge _writerBridge;
};

//void setOutputOptions(const ft::FTMap& ftMap);
//std::string createHeader();
//std::string formatOutputMap();
//std::string getFlagKmers(const ft::QueryClass& query, const ft::FlagType flag);
//void addQueryToOutput(const ft::QueryClass& query, const std::string prefix);
//void saveOutput(const ft::FTMap& ftMap);


#define TEST_DESCRIPTION(desc) RecordPro perty("description", desc)

//======================================================================
TEST_F(TestWriterBridge, saveQueryOutput)
{

    ft::FTProp _ftProps;
    _ftProps.init(pathToQueryFile,kmerSize,readLength,
                  indexPropsFile,outputFolder,refOnly,
                  searchType, multithread, overlap,
                  returnMatchesOnly, kmerCounts, stride,
                  maxOccurences, maxThreads, flagOverCountedKmers,
                  ignoreNonUniqueKmers, crossover);
    ft::FTMap _ftMap(_ftProps);

    std::cout << "Matches Flag " << _ftProps.getIgnoreNonUniqueKmersFlag() << std::endl;

    _writerBridge.setOutputOptions(_ftMap);
    EXPECT_TRUE(_writerBridge.getRefData());
    EXPECT_TRUE(_writerBridge.getAltData());
    EXPECT_FALSE(_writerBridge.getCroData());
    EXPECT_FALSE(_writerBridge.getOCKFlag());
    EXPECT_TRUE(_writerBridge.getNUKFlag());
    EXPECT_FALSE(_writerBridge.getMatchesOnlyFlag());

}
}
