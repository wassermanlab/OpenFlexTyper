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
    bool revCompSearch;
    SearchType searchType;
    bool multithread;
    uint overlap;
    bool returnMatchesOnly;
    bool kmerCounts;
    uint stride;
    uint maxOccurences;
    uint maxThreads;
    bool flagOverCountedKmers;
    bool flagNonUniqueKmers;
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

};


#define TEST_DESCRIPTION(desc) RecordProperty("description", desc)

//======================================================================
TEST_F(TestWriterBridge, setOutputOptions)
{
     TEST_DESCRIPTION("Tests whether a string is join correctly ");
    //void setOutputOptions(const ft::FTMap& ftMap);
    ft::FTProp _ftProps;
    _ftProps.init(pathToQueryFile,kmerSize,readLength,
                  indexPropsFile,outputFolder,refOnly, revCompSearch,
                  searchType, multithread, overlap,
                  returnMatchesOnly, kmerCounts, stride,
                  maxOccurences, maxThreads, flagOverCountedKmers, flagNonUniqueKmers,
                  ignoreNonUniqueKmers, crossover);
    ft::FTMap _ftMap(_ftProps);
    WriterBridge _writerBridge;
    _writerBridge.setOutputOptions(_ftMap);
    EXPECT_TRUE(_writerBridge.getRefData());
    EXPECT_TRUE(_writerBridge.getAltData());
    EXPECT_FALSE(_writerBridge.getCroData());
    EXPECT_FALSE(_writerBridge.getOCKFlag());
    EXPECT_FALSE(_writerBridge.getNUKFlag());
    EXPECT_FALSE(_writerBridge.getMatchesOnlyFlag());
}
////////////////////////////////////////////////////////////////////////
/// createHeader()
////////////////////////////////////////////////////////////////////////
#define HeaderTesting {

//======================================================================
TEST_F(TestWriterBridge, createHeaderRef1)
{
     TEST_DESCRIPTION("Ref Only header, no flags");
    ft::FTProp _ftProps;
    refOnly = true;
    flagOverCountedKmers = false;
    flagNonUniqueKmers = false;
    ignoreNonUniqueKmers = false;
    _ftProps.init(pathToQueryFile,kmerSize,readLength,
                  indexPropsFile,outputFolder,refOnly,revCompSearch,
                  searchType, multithread, overlap,
                  returnMatchesOnly, kmerCounts, stride,
                  maxOccurences, maxThreads, flagOverCountedKmers, flagNonUniqueKmers,
                  ignoreNonUniqueKmers, crossover);
    ft::FTMap _ftMap(_ftProps);
    WriterBridge _writerBridge;
    _writerBridge.setOutputOptions(_ftMap);
    EXPECT_TRUE(_writerBridge.getRefData());
    EXPECT_FALSE(_writerBridge.getAltData());
    EXPECT_FALSE(_writerBridge.getCroData());
    EXPECT_FALSE(_writerBridge.getOCKFlag());
    EXPECT_FALSE(_writerBridge.getNUKFlag());
    EXPECT_FALSE(_writerBridge.getMatchesOnlyFlag());
    std::string expectedHeader = '\t' + std::string("Ref_Count") +'\n';
    std::string outputHeader = _writerBridge.createHeader();
    std::cout<< "Expected Header" << expectedHeader << std::endl;
    std::cout<< "Output Header" << outputHeader << std::endl;
    EXPECT_EQ(outputHeader, expectedHeader);
}
//======================================================================
TEST_F(TestWriterBridge, createHeaderRef2)
{
     TEST_DESCRIPTION("Ref Only header, OCK flag");
    ft::FTProp _ftProps;
    refOnly = true;
    flagOverCountedKmers = true;
    flagNonUniqueKmers = false;
    ignoreNonUniqueKmers = false;
    _ftProps.init(pathToQueryFile,kmerSize,readLength,
                  indexPropsFile,outputFolder,refOnly, revCompSearch,
                  searchType, multithread, overlap,
                  returnMatchesOnly, kmerCounts, stride,
                  maxOccurences, maxThreads, flagOverCountedKmers, flagNonUniqueKmers,
                  ignoreNonUniqueKmers, crossover);
    ft::FTMap _ftMap(_ftProps);
    WriterBridge _writerBridge;
    _writerBridge.setOutputOptions(_ftMap);
    EXPECT_TRUE(_writerBridge.getRefData());
    EXPECT_FALSE(_writerBridge.getAltData());
    EXPECT_FALSE(_writerBridge.getCroData());
    EXPECT_TRUE(_writerBridge.getOCKFlag());
    EXPECT_FALSE(_writerBridge.getNUKFlag());
    EXPECT_FALSE(_writerBridge.getMatchesOnlyFlag());
    std::string expectedHeader = '\t' + std::string("Ref_Count") +'\t' + std::string("Ref_Over_Counted_Kmers") +'\n';
    std::string outputHeader = _writerBridge.createHeader();
    std::cout<< "Expected Header" << expectedHeader << std::endl;
    std::cout<< "Output Header" << outputHeader << std::endl;
    EXPECT_EQ(outputHeader, expectedHeader);
}
//======================================================================
TEST_F(TestWriterBridge, createHeaderRef3)
{
     TEST_DESCRIPTION("Ref Only header, NUK flag");
    ft::FTProp _ftProps;
    refOnly = true;
    flagOverCountedKmers = false;
    flagNonUniqueKmers = true;
    ignoreNonUniqueKmers = true;
    _ftProps.init(pathToQueryFile,kmerSize,readLength,
                  indexPropsFile,outputFolder,refOnly, revCompSearch,
                  searchType, multithread, overlap,
                  returnMatchesOnly, kmerCounts, stride,
                  maxOccurences, maxThreads, flagOverCountedKmers, flagNonUniqueKmers,
                  ignoreNonUniqueKmers, crossover);
    ft::FTMap _ftMap(_ftProps);
    WriterBridge _writerBridge;
    _writerBridge.setOutputOptions(_ftMap);
    EXPECT_TRUE(_writerBridge.getRefData());
    EXPECT_FALSE(_writerBridge.getAltData());
    EXPECT_FALSE(_writerBridge.getCroData());
    EXPECT_FALSE(_writerBridge.getOCKFlag());
    EXPECT_TRUE(_writerBridge.getNUKFlag());
    EXPECT_FALSE(_writerBridge.getMatchesOnlyFlag());
    std::string expectedHeader = '\t' + std::string("Ref_Count") +'\t' + std::string("Ref_Non_Unique_Kmers") +'\n';
    std::string outputHeader = _writerBridge.createHeader();
    std::cout<< "Expected Header" << expectedHeader << std::endl;
    std::cout<< "Output Header" << outputHeader << std::endl;
    EXPECT_EQ(outputHeader, expectedHeader);
}
//======================================================================
TEST_F(TestWriterBridge, createHeaderRef4)
{
     TEST_DESCRIPTION("Ref Only header, OCK and NUK flag");
    ft::FTProp _ftProps;
    refOnly = true;
    flagOverCountedKmers = true;
    flagNonUniqueKmers = true;
    ignoreNonUniqueKmers = true;
    _ftProps.init(pathToQueryFile,kmerSize,readLength,
                  indexPropsFile,outputFolder,refOnly,revCompSearch,
                  searchType, multithread, overlap,
                  returnMatchesOnly, kmerCounts, stride,
                  maxOccurences, maxThreads, flagOverCountedKmers, flagNonUniqueKmers,
                  ignoreNonUniqueKmers, crossover);
    ft::FTMap _ftMap(_ftProps);
    WriterBridge _writerBridge;
    _writerBridge.setOutputOptions(_ftMap);
    std::string expectedHeader = '\t' + std::string("Ref_Count") + '\t' + std::string("Ref_Non_Unique_Kmers") +'\t' + std::string("Ref_Over_Counted_Kmers") +'\n';
    std::string outputHeader = _writerBridge.createHeader();
    //std::cout<< "Expected Header" << expectedHeader << std::endl;
    //std::cout<< "Output Header" << outputHeader << std::endl;
    EXPECT_EQ(outputHeader, expectedHeader);
}
//======================================================================
TEST_F(TestWriterBridge, createHeaderRA1)
{
     TEST_DESCRIPTION("Ref and Alt header, no flags");
    ft::FTProp _ftProps;
    refOnly = false;
    flagOverCountedKmers = false;
    flagNonUniqueKmers = false;
    ignoreNonUniqueKmers = false;
    _ftProps.init(pathToQueryFile,kmerSize,readLength,
                  indexPropsFile,outputFolder,refOnly,revCompSearch,
                  searchType, multithread, overlap,
                  returnMatchesOnly, kmerCounts, stride,
                  maxOccurences, maxThreads, flagOverCountedKmers, flagNonUniqueKmers,
                  ignoreNonUniqueKmers, crossover);
    ft::FTMap _ftMap(_ftProps);
    WriterBridge _writerBridge;
    _writerBridge.setOutputOptions(_ftMap);
    EXPECT_TRUE(_writerBridge.getRefData());
    EXPECT_TRUE(_writerBridge.getAltData());
    EXPECT_FALSE(_writerBridge.getCroData());
    EXPECT_FALSE(_writerBridge.getOCKFlag());
    EXPECT_FALSE(_writerBridge.getNUKFlag());
    EXPECT_FALSE(_writerBridge.getMatchesOnlyFlag());
    std::string expectedHeader = '\t' + std::string("Ref_Count") + '\t' + std::string("Alt_Count") + "\n" ;
    std::string outputHeader = _writerBridge.createHeader();
    //std::cout<< "Expected Header" << expectedHeader << std::endl;
    //std::cout<< "Output Header" << outputHeader << std::endl;
    EXPECT_EQ(outputHeader, expectedHeader);
}
//======================================================================
TEST_F(TestWriterBridge, createHeaderRA2)
{
     TEST_DESCRIPTION("Ref and Alt header, OCK flags");
    ft::FTProp _ftProps;
    refOnly = false;
    flagOverCountedKmers = true;
    flagNonUniqueKmers = false;
    ignoreNonUniqueKmers = false;
    _ftProps.init(pathToQueryFile,kmerSize,readLength,
                  indexPropsFile,outputFolder,refOnly, revCompSearch,
                  searchType, multithread, overlap,
                  returnMatchesOnly, kmerCounts, stride,
                  maxOccurences, maxThreads, flagOverCountedKmers, flagNonUniqueKmers,
                  ignoreNonUniqueKmers, crossover);
    ft::FTMap _ftMap(_ftProps);
    WriterBridge _writerBridge;
    _writerBridge.setOutputOptions(_ftMap);
    EXPECT_TRUE(_writerBridge.getRefData());
    EXPECT_TRUE(_writerBridge.getAltData());
    EXPECT_FALSE(_writerBridge.getCroData());
    EXPECT_TRUE(_writerBridge.getOCKFlag());
    EXPECT_FALSE(_writerBridge.getNUKFlag());
    EXPECT_FALSE(_writerBridge.getMatchesOnlyFlag());
    std::string expectedHeader = '\t' + std::string("Ref_Count") + '\t' + std::string("Alt_Count")
            + '\t' + std::string("Ref_Over_Counted_Kmers") + '\t' + std::string("Alt_Over_Counted_Kmers") + "\n";
    std::string outputHeader = _writerBridge.createHeader();
    EXPECT_EQ(outputHeader, expectedHeader);
}
//======================================================================
TEST_F(TestWriterBridge, createHeaderRA3)
{
     TEST_DESCRIPTION("Ref and Alt header, NUK flags");
    ft::FTProp _ftProps;
    refOnly = false;
    flagOverCountedKmers = false;
    flagNonUniqueKmers = true;
    ignoreNonUniqueKmers = true;
    _ftProps.init(pathToQueryFile,kmerSize,readLength,
                  indexPropsFile,outputFolder,refOnly,revCompSearch,
                  searchType, multithread, overlap,
                  returnMatchesOnly, kmerCounts, stride,
                  maxOccurences, maxThreads, flagOverCountedKmers, flagNonUniqueKmers,
                  ignoreNonUniqueKmers, crossover);
    ft::FTMap _ftMap(_ftProps);
    WriterBridge _writerBridge;
    _writerBridge.setOutputOptions(_ftMap);
    EXPECT_TRUE(_writerBridge.getRefData());
    EXPECT_TRUE(_writerBridge.getAltData());
    EXPECT_FALSE(_writerBridge.getCroData());
    EXPECT_FALSE(_writerBridge.getOCKFlag());
    EXPECT_TRUE(_writerBridge.getNUKFlag());
    EXPECT_FALSE(_writerBridge.getMatchesOnlyFlag());
    std::string expectedHeader = '\t' + std::string("Ref_Count") + '\t' + std::string("Alt_Count")
            +'\t' + std::string("Ref_Non_Unique_Kmers") + '\t' + std::string("Alt_Non_Unique_Kmers") + "\n";
    std::string outputHeader = _writerBridge.createHeader();
    EXPECT_EQ(outputHeader, expectedHeader);
}
//======================================================================
TEST_F(TestWriterBridge, createHeaderRA4)
{
     TEST_DESCRIPTION("Ref and Alt header, OCK and NUK flags");
    ft::FTProp _ftProps;
    refOnly = false;
    flagOverCountedKmers = true;
    flagNonUniqueKmers = true;
    ignoreNonUniqueKmers = true;
    _ftProps.init(pathToQueryFile,kmerSize,readLength,
                  indexPropsFile,outputFolder,refOnly,revCompSearch,
                  searchType, multithread, overlap,
                  returnMatchesOnly, kmerCounts, stride,
                  maxOccurences, maxThreads, flagOverCountedKmers, flagNonUniqueKmers,
                  ignoreNonUniqueKmers, crossover);
    ft::FTMap _ftMap(_ftProps);
    WriterBridge _writerBridge;
    _writerBridge.setOutputOptions(_ftMap);
    EXPECT_TRUE(_writerBridge.getRefData());
    EXPECT_TRUE(_writerBridge.getAltData());
    EXPECT_FALSE(_writerBridge.getCroData());
    EXPECT_TRUE(_writerBridge.getOCKFlag());
    EXPECT_TRUE(_writerBridge.getNUKFlag());
    EXPECT_FALSE(_writerBridge.getMatchesOnlyFlag());
    std::string expectedHeader = '\t' + std::string("Ref_Count") + '\t' + std::string("Alt_Count")
            + '\t' + std::string("Ref_Non_Unique_Kmers") + '\t' + std::string("Alt_Non_Unique_Kmers")
            + '\t' + std::string("Ref_Over_Counted_Kmers") + '\t' + std::string("Alt_Over_Counted_Kmers") + "\n";
    std::string outputHeader = _writerBridge.createHeader();
    EXPECT_EQ(outputHeader, expectedHeader);
}
//======================================================================
TEST_F(TestWriterBridge, createHeaderCRO1)
{
     TEST_DESCRIPTION("Ref,Alt and Cro header, no flags");
    ft::FTProp _ftProps;
    refOnly = false;
    crossover = true;
    flagOverCountedKmers = false;
    flagNonUniqueKmers = false;
    ignoreNonUniqueKmers = false;
    _ftProps.init(pathToQueryFile,kmerSize,readLength,
                  indexPropsFile,outputFolder,refOnly,revCompSearch,
                  searchType, multithread, overlap,
                  returnMatchesOnly, kmerCounts, stride,
                  maxOccurences, maxThreads, flagOverCountedKmers, flagNonUniqueKmers,
                  ignoreNonUniqueKmers, crossover);
    ft::FTMap _ftMap(_ftProps);
        WriterBridge _writerBridge;
        _writerBridge.setOutputOptions(_ftMap);
    EXPECT_TRUE(_writerBridge.getRefData());
    EXPECT_TRUE(_writerBridge.getAltData());
    EXPECT_TRUE(_writerBridge.getCroData());
    EXPECT_FALSE(_writerBridge.getOCKFlag());
    EXPECT_FALSE(_writerBridge.getNUKFlag());
    EXPECT_FALSE(_writerBridge.getMatchesOnlyFlag());
    std::string expectedHeader = '\t' + std::string("Start_Count") + '\t' + std::string("Crossover_Count") + '\t' + std::string("End_Count")+ "\n";
    std::string outputHeader = _writerBridge.createHeader();
    EXPECT_EQ(outputHeader, expectedHeader);
}
//======================================================================
TEST_F(TestWriterBridge, createHeaderCRO2)
{
     TEST_DESCRIPTION("Ref,Alt and Cro header, OCK flags");
    ft::FTProp _ftProps;
    refOnly = false;
    crossover = true;
    flagOverCountedKmers = true;
    flagNonUniqueKmers = false;
    ignoreNonUniqueKmers = false;
    _ftProps.init(pathToQueryFile,kmerSize,readLength,
                  indexPropsFile,outputFolder,refOnly,revCompSearch,
                  searchType, multithread, overlap,
                  returnMatchesOnly, kmerCounts, stride,
                  maxOccurences, maxThreads, flagOverCountedKmers, flagNonUniqueKmers,
                  ignoreNonUniqueKmers, crossover);
    ft::FTMap _ftMap(_ftProps);
    WriterBridge _writerBridge;

    _writerBridge.setOutputOptions(_ftMap);
    EXPECT_TRUE(_writerBridge.getRefData());
    EXPECT_TRUE(_writerBridge.getAltData());
    EXPECT_TRUE(_writerBridge.getCroData());
    EXPECT_TRUE(_writerBridge.getOCKFlag());
    EXPECT_FALSE(_writerBridge.getNUKFlag());
    EXPECT_FALSE(_writerBridge.getMatchesOnlyFlag());
    std::string expectedHeader = '\t' + std::string("Start_Count") + '\t' + std::string("Crossover_Count") + '\t' + std::string("End_Count")
             + '\t' + std::string("Start_Over_Counted_Kmers") + '\t' + std::string("Crossover_Over_Counted_Kmers") + '\t' + std::string("End_Over_Counted_Kmers") + "\n";
    std::string outputHeader = _writerBridge.createHeader();
    EXPECT_EQ(outputHeader, expectedHeader);
}
//======================================================================
TEST_F(TestWriterBridge, createHeaderCRO3)
{
     TEST_DESCRIPTION("Ref,Alt and Cro header, NUK flags");
    //std::string createHeader();
    ft::FTProp _ftProps;
    refOnly = false;
    crossover = true;
    flagOverCountedKmers = false;
    flagNonUniqueKmers = true;
    ignoreNonUniqueKmers = true;
    _ftProps.init(pathToQueryFile,kmerSize,readLength,
                  indexPropsFile,outputFolder,refOnly,revCompSearch,
                  searchType, multithread, overlap,
                  returnMatchesOnly, kmerCounts, stride,
                  maxOccurences, maxThreads, flagOverCountedKmers, flagNonUniqueKmers,
                  ignoreNonUniqueKmers, crossover);
    ft::FTMap _ftMap(_ftProps);
    WriterBridge _writerBridge;
    _writerBridge.setOutputOptions(_ftMap);
    EXPECT_TRUE(_writerBridge.getRefData());
    EXPECT_TRUE(_writerBridge.getAltData());
    EXPECT_TRUE(_writerBridge.getCroData());
    EXPECT_FALSE(_writerBridge.getOCKFlag());
    EXPECT_TRUE(_writerBridge.getNUKFlag());
    EXPECT_FALSE(_writerBridge.getMatchesOnlyFlag());
    std::string expectedHeader = '\t' + std::string("Start_Count") + '\t' + std::string("Crossover_Count") + '\t' + std::string("End_Count")
            + '\t' + std::string("Start_Non_Unique_Kmers") + '\t' + std::string("Crossover_Non_Unique_Kmers") + '\t' + std::string("End_Non_Unique_Kmers") + "\n";
    std::string outputHeader= _writerBridge.createHeader();
    EXPECT_EQ(outputHeader, expectedHeader);

}
//======================================================================
TEST_F(TestWriterBridge, createHeaderCRO4)
{
     TEST_DESCRIPTION("Ref,Alt and Cro header, OCK and NUK flags");
    //std::string createHeader();
    ft::FTProp _ftProps;
    refOnly = false;
    crossover = true;
    flagOverCountedKmers = true;
    flagNonUniqueKmers = true;
    ignoreNonUniqueKmers = true;
    _ftProps.init(pathToQueryFile,kmerSize,readLength,
                  indexPropsFile,outputFolder,refOnly, revCompSearch,
                  searchType, multithread, overlap,
                  returnMatchesOnly, kmerCounts, stride,
                  maxOccurences, maxThreads, flagOverCountedKmers, flagNonUniqueKmers,
                  ignoreNonUniqueKmers, crossover);
    ft::FTMap _ftMap(_ftProps);
    WriterBridge _writerBridge;
    _writerBridge.setOutputOptions(_ftMap);
    EXPECT_TRUE(_writerBridge.getRefData());
    EXPECT_TRUE(_writerBridge.getAltData());
    EXPECT_TRUE(_writerBridge.getCroData());
    EXPECT_TRUE(_writerBridge.getOCKFlag());
    EXPECT_TRUE(_writerBridge.getNUKFlag());
    EXPECT_FALSE(_writerBridge.getMatchesOnlyFlag());
    std::string expectedHeader = '\t' + std::string("Start_Count") + '\t' + std::string("Crossover_Count") + '\t' + std::string("End_Count")
            + '\t' + std::string("Start_Non_Unique_Kmers") + '\t' + std::string("Crossover_Non_Unique_Kmers") + '\t' + std::string("End_Non_Unique_Kmers")
             + '\t' + std::string("Start_Over_Counted_Kmers") + '\t' + std::string("Crossover_Over_Counted_Kmers") + '\t' + std::string("End_Over_Counted_Kmers") + "\n";
    std::string outputHeader = _writerBridge.createHeader();
    EXPECT_EQ(outputHeader, expectedHeader);


}

#define EndHeaderTest }

////////////////////////////////////////////////////////////////////////
///  getFlagKmers(const ft::QueryClass& query, const ft::FlagType flag)
////////////////////////////////////////////////////////////////////////
#define flagTesting {

//======================================================================
TEST_F(TestWriterBridge, getFlagKmers)
{
     TEST_DESCRIPTION("Ref, count 12, no flags");
    ft::FTProp _ftProps;
    refOnly = true;
    flagOverCountedKmers = true;
    ignoreNonUniqueKmers = false;
    _ftProps.init(pathToQueryFile,kmerSize,readLength,
                  indexPropsFile,outputFolder,refOnly, revCompSearch,
                  searchType, multithread, overlap,
                  returnMatchesOnly, kmerCounts, stride,
                  maxOccurences, maxThreads, flagOverCountedKmers,
                  ignoreNonUniqueKmers, crossover);
    ft::FTMap _ftMap(_ftProps);
    WriterBridge _writerBridge;
    _writerBridge.setOutputOptions(_ftMap);
    ft::QueryClass refQuery(1, ft::QueryType::REF);
    std::set<std::string > flagKmers = {"AAAA", "CCCC"};
    refQuery.addFlags(ft::FlagType::OCK, flagKmers );
    std::string outputFlags = _writerBridge.getFlagKmers(refQuery, ft::FlagType::OCK);
    std::string expectedFlags = "AAAA, CCCC";
    EXPECT_EQ(outputFlags, expectedFlags);

}
//======================================================================
TEST_F(TestWriterBridge, getFlagKmers2)
{
     TEST_DESCRIPTION("Alt, count 13456, NUK flags");
    ft::FTProp _ftProps;
    refOnly = true;
    flagOverCountedKmers = false;
    ignoreNonUniqueKmers = true;
    _ftProps.init(pathToQueryFile,kmerSize,readLength,
                  indexPropsFile,outputFolder,refOnly, revCompSearch,
                  searchType, multithread, overlap,
                  returnMatchesOnly, kmerCounts, stride,
                  maxOccurences, maxThreads, flagOverCountedKmers,
                  ignoreNonUniqueKmers, crossover);
    ft::FTMap _ftMap(_ftProps);
    WriterBridge _writerBridge;
    _writerBridge.setOutputOptions(_ftMap);
    ft::QueryClass altQuery(1, ft::QueryType::ALT);
    altQuery.setCount(13456);
    std::set<std::string > flagKmers = {"AAAA", "CCCC"};
    altQuery.addFlags(ft::FlagType::NUK, flagKmers );

    std::string outputFlags = _writerBridge.getFlagKmers(altQuery, ft::FlagType::NUK);
    std::string expectedFlags = "AAAA, CCCC";

    EXPECT_EQ(outputFlags, expectedFlags);
}

//======================================================================
TEST_F(TestWriterBridge, getFlagKmers3)
{
     TEST_DESCRIPTION("No flag Kmers");
    ft::FTProp _ftProps;
    refOnly = true;
    flagOverCountedKmers = false;
    ignoreNonUniqueKmers = true;
    _ftProps.init(pathToQueryFile,kmerSize,readLength,
                  indexPropsFile,outputFolder,refOnly, revCompSearch,
                  searchType, multithread, overlap,
                  returnMatchesOnly, kmerCounts, stride,
                  maxOccurences, maxThreads, flagOverCountedKmers,
                  ignoreNonUniqueKmers, crossover);
    ft::FTMap _ftMap(_ftProps);
    WriterBridge _writerBridge;
    _writerBridge.setOutputOptions(_ftMap);
    ft::QueryClass refQuery(1, ft::QueryType::REF);
    std::string outputFlags = _writerBridge.getFlagKmers(refQuery, ft::FlagType::NUK);
    std::string expectedFlags = "";

    EXPECT_EQ(outputFlags, expectedFlags);
}


#define flagTestingEnd }


////////////////////////////////////////////////////////////////////////
///  addQueryToOutput();
////////////////////////////////////////////////////////////////////////
#define addQueryTesting {

//======================================================================
TEST_F(TestWriterBridge, addQueryToOutput1)
{
     TEST_DESCRIPTION("Ref, count 12, no flags");
    ft::FTProp _ftProps;
    refOnly = true;
    flagOverCountedKmers = false;
    ignoreNonUniqueKmers = false;
    _ftProps.init(pathToQueryFile,kmerSize,readLength,
                  indexPropsFile,outputFolder,refOnly, revCompSearch,
                  searchType, multithread, overlap,
                  returnMatchesOnly, kmerCounts, stride,
                  maxOccurences, maxThreads, flagOverCountedKmers,
                  ignoreNonUniqueKmers, crossover);
    ft::FTMap _ftMap(_ftProps);
    WriterBridge _writerBridge;
    _writerBridge.setOutputOptions(_ftMap);
    ft::QueryClass refQuery(1, ft::QueryType::REF);
    refQuery.setCount(12);
    _writerBridge.addQueryToOutput(refQuery, "ref");
    std::map<std::string, std::string> outputMap = _writerBridge.getOutputMap();

    EXPECT_EQ(outputMap["refMatches"], "true");
    EXPECT_EQ(outputMap["refCount"], std::to_string(12));
    EXPECT_EQ(outputMap["refOCK"], "");
    EXPECT_EQ(outputMap["refNUK"], "");

}
//======================================================================
TEST_F(TestWriterBridge, addQueryToOutput2)
{
     TEST_DESCRIPTION("Alt, count 13456, OCK flags");
    ft::FTProp _ftProps;
    refOnly = true;
    flagOverCountedKmers = true;
    ignoreNonUniqueKmers = false;
    _ftProps.init(pathToQueryFile,kmerSize,readLength,
                  indexPropsFile,outputFolder,refOnly,revCompSearch ,
                  searchType, multithread, overlap,
                  returnMatchesOnly, kmerCounts, stride,
                  maxOccurences, maxThreads, flagOverCountedKmers,
                  ignoreNonUniqueKmers, crossover);
    ft::FTMap _ftMap(_ftProps);
    WriterBridge _writerBridge;
    _writerBridge.setOutputOptions(_ftMap);
    ft::QueryClass altQuery(1, ft::QueryType::REF);
    altQuery.setCount(13456);
    std::set<std::string > flagKmers = {"AAAA", "CCCC"};
    altQuery.addFlags(ft::FlagType::OCK, flagKmers );
    _writerBridge.addQueryToOutput(altQuery, "alt");
    std::map<std::string, std::string> outputMap = _writerBridge.getOutputMap();

    EXPECT_EQ(outputMap["altMatches"], "true");
    EXPECT_EQ(outputMap["altCount"], std::to_string(13456));
    EXPECT_EQ(outputMap["altOCK"], "AAAA, CCCC");
    EXPECT_EQ(outputMap["altNUK"], "");

}


#define formatOutputTestingEnd }

////////////////////////////////////////////////////////////////////////
///  formatOutputMap();
////////////////////////////////////////////////////////////////////////
#define formatOutputTesting {

//======================================================================
TEST_F(TestWriterBridge, formatOutputMap1)
{
     TEST_DESCRIPTION("Ref only, count 12, no flags");
    ft::FTProp _ftProps;
    refOnly = true;
    flagOverCountedKmers = false;
    flagNonUniqueKmers = false;
    ignoreNonUniqueKmers = false;
    _ftProps.init(pathToQueryFile,kmerSize,readLength,
                  indexPropsFile,outputFolder,refOnly, revCompSearch,
                  searchType, multithread, overlap,
                  returnMatchesOnly, kmerCounts, stride,
                  maxOccurences, maxThreads, flagOverCountedKmers, flagNonUniqueKmers,
                  ignoreNonUniqueKmers, crossover);
    ft::FTMap _ftMap(_ftProps);
    WriterBridge _writerBridge;
    _writerBridge.setOutputOptions(_ftMap);
    ft::QueryClass refQuery(1, ft::QueryType::REF);
    refQuery.setCount(12);
    _writerBridge.addQueryToOutput(refQuery, "ref");
    std::string expected = '\t' + std::string("12");
    std::string output = _writerBridge.formatOutputMap();
    EXPECT_EQ(expected, output);
}
//======================================================================
TEST_F(TestWriterBridge, formatOutputMap2)
{
     TEST_DESCRIPTION("Ref And Alt, count R=12, A=34, no flags");
    ft::FTProp _ftProps;
    refOnly = false;
    flagOverCountedKmers = false;
    flagNonUniqueKmers = false;
    ignoreNonUniqueKmers = false;
    _ftProps.init(pathToQueryFile,kmerSize,readLength,
                  indexPropsFile,outputFolder,refOnly, revCompSearch,
                  searchType, multithread, overlap,
                  returnMatchesOnly, kmerCounts, stride,
                  maxOccurences, maxThreads, flagOverCountedKmers, flagNonUniqueKmers,
                  ignoreNonUniqueKmers, crossover);
    ft::FTMap _ftMap(_ftProps);
    WriterBridge _writerBridge;
    _writerBridge.setOutputOptions(_ftMap);
    ft::QueryClass refQuery(1, ft::QueryType::REF);
    refQuery.setCount(12);
    _writerBridge.addQueryToOutput(refQuery, "ref");
    ft::QueryClass altQuery(1, ft::QueryType::ALT);
    altQuery.setCount(34);
    _writerBridge.addQueryToOutput(altQuery, "alt");
    std::string expected = '\t' + std::string("12") + '\t' + std::string("34");
    std::string output = _writerBridge.formatOutputMap();
    EXPECT_EQ(expected, output);
}
//======================================================================
TEST_F(TestWriterBridge, formatOutputMap3)
{
     TEST_DESCRIPTION("Ref, Alt and Cro, R=12, A=34, C= 56, no flags");
    ft::FTProp _ftProps;
    refOnly = false;
    crossover = true;
    flagOverCountedKmers = false;
    flagNonUniqueKmers = false;
    ignoreNonUniqueKmers = false;
    _ftProps.init(pathToQueryFile,kmerSize,readLength,
                  indexPropsFile,outputFolder,refOnly, revCompSearch,
                  searchType, multithread, overlap,
                  returnMatchesOnly, kmerCounts, stride,
                  maxOccurences, maxThreads, flagOverCountedKmers, flagNonUniqueKmers,
                  ignoreNonUniqueKmers, crossover);
    ft::FTMap _ftMap(_ftProps);
    WriterBridge _writerBridge;
    _writerBridge.setOutputOptions(_ftMap);
    ft::QueryClass refQuery(1, ft::QueryType::REF);
    refQuery.setCount(12);
    _writerBridge.addQueryToOutput(refQuery, "ref");
    ft::QueryClass altQuery(1, ft::QueryType::ALT);
    altQuery.setCount(34);
    _writerBridge.addQueryToOutput(altQuery, "alt");
    ft::QueryClass croQuery(1, ft::QueryType::CRO);
    croQuery.setCount(56);
    _writerBridge.addQueryToOutput(croQuery, "cro");
    std::string expected = '\t' + std::string("12") + '\t' + std::string("56") + '\t' + std::string("34");
    std::string output = _writerBridge.formatOutputMap();
    EXPECT_EQ(expected, output);
}
//======================================================================
TEST_F(TestWriterBridge, formatOutputMap4)
{
     TEST_DESCRIPTION("Ref only, count 12, OCK Flags");
    ft::FTProp _ftProps;
    refOnly = true;
    flagOverCountedKmers = true;
    flagNonUniqueKmers = false;
    ignoreNonUniqueKmers = false;
    _ftProps.init(pathToQueryFile,kmerSize,readLength,
                  indexPropsFile,outputFolder,refOnly, revCompSearch,
                  searchType, multithread, overlap,
                  returnMatchesOnly, kmerCounts, stride,
                  maxOccurences, maxThreads, flagOverCountedKmers, flagNonUniqueKmers,
                  ignoreNonUniqueKmers, crossover);
    ft::FTMap _ftMap(_ftProps);
    WriterBridge _writerBridge;
    _writerBridge.setOutputOptions(_ftMap);
    ft::QueryClass refQuery(1, ft::QueryType::REF);
    refQuery.setCount(12);
    std::set<std::string > flagKmers = {"AAAA", "CCCC"};
    refQuery.addFlags(ft::FlagType::OCK, flagKmers );
    _writerBridge.addQueryToOutput(refQuery, "ref");
    std::string expected = '\t' + std::string("12") + '\t' + std::string("AAAA, CCCC");
    std::string output = _writerBridge.formatOutputMap();
    EXPECT_EQ(expected, output);
}
//======================================================================
TEST_F(TestWriterBridge, formatOutputMap5)
{
     TEST_DESCRIPTION("Ref only, count 12, NUK Flags");
    ft::FTProp _ftProps;
    refOnly = true;
    flagOverCountedKmers = false;
    flagNonUniqueKmers = true;
    ignoreNonUniqueKmers = true;
    _ftProps.init(pathToQueryFile,kmerSize,readLength,
                  indexPropsFile,outputFolder,refOnly, revCompSearch,
                  searchType, multithread, overlap,
                  returnMatchesOnly, kmerCounts, stride,
                  maxOccurences, maxThreads, flagOverCountedKmers, flagNonUniqueKmers,
                  ignoreNonUniqueKmers, crossover);
    ft::FTMap _ftMap(_ftProps);
    WriterBridge _writerBridge;
    _writerBridge.setOutputOptions(_ftMap);
    ft::QueryClass refQuery(1, ft::QueryType::REF);
    refQuery.setCount(12);
    std::set<std::string > flagKmers = {"GGGG", "TTTT"};
    refQuery.addFlags(ft::FlagType::NUK, flagKmers );
    _writerBridge.addQueryToOutput(refQuery, "ref");
    std::string expected = '\t' + std::string("12") + '\t' + std::string("GGGG, TTTT");
    std::string output = _writerBridge.formatOutputMap();
    EXPECT_EQ(expected, output);
}
//======================================================================
TEST_F(TestWriterBridge, formatOutputMap6)
{
     TEST_DESCRIPTION("Ref only, count 12, OCK and NUK Flags");
    ft::FTProp _ftProps;
    refOnly = true;
    flagOverCountedKmers = true;
    flagNonUniqueKmers = true;
    ignoreNonUniqueKmers = true;
    _ftProps.init(pathToQueryFile,kmerSize,readLength,
                  indexPropsFile,outputFolder,refOnly, revCompSearch,
                  searchType, multithread, overlap,
                  returnMatchesOnly, kmerCounts, stride,
                  maxOccurences, maxThreads, flagOverCountedKmers, flagNonUniqueKmers,
                  ignoreNonUniqueKmers, crossover);
    ft::FTMap _ftMap(_ftProps);
    WriterBridge _writerBridge;
    _writerBridge.setOutputOptions(_ftMap);
    ft::QueryClass refQuery(1, ft::QueryType::REF);
    refQuery.setCount(12);
    std::set<std::string > flagKmers = {"AAAA", "CCCC"};
    refQuery.addFlags(ft::FlagType::OCK, flagKmers );
    std::set<std::string > flagKmers2 = {"GGGG", "TTTT"};
    refQuery.addFlags(ft::FlagType::NUK, flagKmers2 );
    _writerBridge.addQueryToOutput(refQuery, "ref");
    std::string expected = '\t' + std::string("12") + '\t' + std::string("GGGG, TTTT") + '\t' + std::string("AAAA, CCCC");
    std::string output = _writerBridge.formatOutputMap();
    EXPECT_EQ(expected, output);
}
//======================================================================
TEST_F(TestWriterBridge, formatOutputMap7)
{
     TEST_DESCRIPTION("Ref and Alt, R=12, A=34, OCK and NUK Flags");
    ft::FTProp _ftProps;
    refOnly = false;
    flagOverCountedKmers = true;
    flagNonUniqueKmers = true;
    ignoreNonUniqueKmers = true;
    _ftProps.init(pathToQueryFile,kmerSize,readLength,
                  indexPropsFile,outputFolder,refOnly, revCompSearch,
                  searchType, multithread, overlap,
                  returnMatchesOnly, kmerCounts, stride,
                  maxOccurences, maxThreads, flagOverCountedKmers, flagNonUniqueKmers,
                  ignoreNonUniqueKmers, crossover);
    ft::FTMap _ftMap(_ftProps);
    WriterBridge _writerBridge;
    _writerBridge.setOutputOptions(_ftMap);
    ft::QueryClass refQuery(1, ft::QueryType::REF);
    refQuery.setCount(12);
    std::set<std::string > flagKmers = {"AAAA", "CCCC"};
    refQuery.addFlags(ft::FlagType::OCK, flagKmers );
    std::set<std::string > flagKmers2 = {"GGGG", "TTTT"};
    refQuery.addFlags(ft::FlagType::NUK, flagKmers2 );
    _writerBridge.addQueryToOutput(refQuery, "ref");
    ft::QueryClass altQuery(1, ft::QueryType::ALT);
    altQuery.setCount(34);
    std::set<std::string > flagKmers3 = {"AACC", "CCAA"};
    altQuery.addFlags(ft::FlagType::OCK, flagKmers3 );
    std::set<std::string > flagKmers4 = {"GGTT", "TTGG"};
    altQuery.addFlags(ft::FlagType::NUK, flagKmers4 );
    _writerBridge.addQueryToOutput(altQuery, "alt");
    std::string expected = '\t' + std::string("12") + '\t' + std::string("34") +'\t' + std::string("GGGG, TTTT") + '\t' + std::string("GGTT, TTGG") +'\t' + std::string("AAAA, CCCC") + '\t' + std::string("AACC, CCAA");
    std::string output = _writerBridge.formatOutputMap();
    EXPECT_EQ(expected, output);
}


#define formatOutputTestingEnd }





}
