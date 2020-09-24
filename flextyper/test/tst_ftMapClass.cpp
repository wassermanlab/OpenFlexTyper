#include <gtest/gtest.h>

#include "ftMapClass.cpp"

#include <fstream>
#include <climits>

using namespace std;

namespace ft {
class TestFTMap : public ::testing::Test {
protected:
    virtual void SetUp() {}
    virtual void TearDown() {}

public:

};

#define TEST_DESCRIPTION(desc) RecordProperty("description", desc)
//ft::FTProp* TestFTMap::_ftProps = new ft::FTProp();

//======================================================================
TEST_F(TestFTMap, TestCheckKmer)
{
    TEST_DESCRIPTION("Check Kmer");
    ft::FTProp _ftProps;
    _ftProps.initFromQSettings("Test_Settings.ini", "output.tsv", false);
    ft::FTMap ftMap(_ftProps);

    ftMap.addKmer("AAAA");
    EXPECT_TRUE(ftMap.checkForKmer("AAAA"));
    EXPECT_FALSE(ftMap.checkForKmer("AAAC"));
}

//======================================================================
TEST_F(TestFTMap, TestCheckQIDT)
{
    TEST_DESCRIPTION("check QIdT");
    //bool checkQIDT(ft::QIdT testQueryObject);
    ft::FTProp _ftProps;
    _ftProps.initFromQSettings("Test_Settings.ini","output.tsv", false);
    ft::FTMap ftMap(_ftProps);

    ftMap.addQuery(1, ft::QueryType::REF);
    ftMap.addQuery(1, ft::QueryType::ALT);
    ftMap.addQuery(2, ft::QueryType::REF);

    ft::QIdT truetest = std::make_pair(1, ft::QueryType::REF);
    ft::QIdT truetest2 = std::make_pair(1, ft::QueryType::ALT);
    ft::QIdT truetest3 = std::make_pair(2, ft::QueryType::REF);
    ft::QIdT falsetest = std::make_pair(2, ft::QueryType::ALT);
    ft::QIdT falsetest2 = std::make_pair(3, ft::QueryType::REF);
    EXPECT_TRUE(ftMap.checkForQIDT(truetest));
    EXPECT_TRUE(ftMap.checkForQIDT(truetest2));
    EXPECT_TRUE(ftMap.checkForQIDT(truetest3));
    EXPECT_FALSE(ftMap.checkForQIDT(falsetest));
    EXPECT_FALSE(ftMap.checkForQIDT(falsetest2));
}





//======================================================================
TEST_F(TestFTMap, TestAddQuery)
{
    TEST_DESCRIPTION("Add Query");
    //void addQuery(ft::QueryClass query);
    ft::FTProp _ftProps;
    _ftProps.initFromQSettings("Test_Settings.ini","output.tsv", false);
    ft::FTMap ftMap(_ftProps);
    ftMap.addQuery(1, ft::QueryType::REF);
    ft::QIdT testGoodQIdT = std::make_pair(1, ft::QueryType::REF);
    ft::QIdT testBadQIdT = std::make_pair(6, ft::QueryType::REF);
    EXPECT_TRUE(ftMap.checkForQIDT(testGoodQIdT));
    EXPECT_FALSE(ftMap.checkForQIDT(testBadQIdT));
}


//====================== INDEX TESTS ===================================
//======================================================================
TEST_F(TestFTMap, TestAddKmerResults)
{
    TEST_DESCRIPTION("Add Kmer Results");
    //void FTMap::addKmerResults(ft::KmerClass kmerResult)
    ft::FTProp _ftProps;
    _ftProps.initFromQSettings("Test_Settings.ini","output.tsv", false);
    ft::FTMap ftMap(_ftProps);

    ft::KmerClass testKmer1("AAAA");
    testKmer1.addReadID(std::make_pair(1, 1));
    testKmer1.addKFlag(ft::FlagType::ABK);

    ftMap.addKmerResults(testKmer1);
    ft::ReadID testRID = std::make_pair(1, 1);
    ft::KmerClass kmer = ftMap.getKmer(testKmer1.getKmer());

    EXPECT_TRUE(kmer.hasFlag(ft::FlagType::ABK));
    EXPECT_TRUE(kmer.hasReadID(testRID));

}

//======================================================================
TEST_F(TestFTMap, TestAddIndexResults)
{
    TEST_DESCRIPTION("Add Index Results");
    //void addIndexResults(std::set<ft::KmerClass> indexResults);
    ft::FTProp _ftProps;
    _ftProps.initFromQSettings("Test_Settings.ini","output.tsv", false);
    ft::FTMap ftMap(_ftProps);

    ft::KmerClass testKmer1("AAAA");
    testKmer1.addKPosition(123);
    ft::KmerClass testKmer2("CCCC");
    testKmer2.addKPosition(345);
    std::map<std::string, ft::KmerClass> indexResults;
    indexResults["AAAA"]= testKmer1;
    indexResults["CCCC"] = testKmer2;

    ftMap.addIndexResults(indexResults);
    EXPECT_EQ(ftMap.getResults().size(), 1);
    //add a second set to make sure it doesnt override existing
    ftMap.addIndexResults(indexResults);
    EXPECT_EQ(ftMap.getResults().size(), 2);
}

//======================================================================
TEST_F(TestFTMap, TestProcessIndexResults)
{
    TEST_DESCRIPTION("Process Index Results");
    //void processIndexResults(std::set<ft::KmerClass> indexResults, uint readLength);
    ft::FTProp _ftProps;
    _ftProps.initFromQSettings("Test_Settings.ini","output.tsv", false);
    _ftProps.setTestProps(20, 100, false);
    ft::FTMap ftMap(_ftProps);

    ft::KmerClass testKmer1("AAAA");
    testKmer1.addKPosition(123);
    ft::KmerClass testKmer2("CCCC");
    testKmer2.addKPosition(345);
    std::map<std::string, ft::KmerClass> indexResults;
    indexResults["AAAA"]= testKmer1;
    indexResults["CCCC"] = testKmer2;

    ftMap.processIndexResults(indexResults);

    ft::KmerClass outputKmer = ftMap.getKmer("AAAA");
    ft::KmerClass outputKmer2 = ftMap.getKmer("CCCC");

    EXPECT_TRUE(ftMap.checkForKmer("AAAA"));
    EXPECT_TRUE(ftMap.checkForKmer("CCCC"));
    EXPECT_TRUE(outputKmer.hasReadID(std::make_pair(2, 1)));
    EXPECT_TRUE(outputKmer2.hasReadID(std::make_pair(4, 1)));
}

//======================================================================
TEST_F(TestFTMap, TestProcessIndexResults_multipleIndexes )
{
    TEST_DESCRIPTION("Process Index Results");
    //void processIndexResults(std::set<ft::KmerClass> indexResults, uint readLength);
    ft::FTProp _ftProps;
    _ftProps.initFromQSettings("Test_Settings.ini","output.tsv", false);
    _ftProps.setTestProps(20, 100, false);
    ft::FTMap ftMap(_ftProps);

    ft::KmerClass testKmer1("AAAA");
    testKmer1.addKPosition(123);
    ft::KmerClass testKmer2("CCCC");
    testKmer2.addKPosition(345);
    std::map<std::string, ft::KmerClass> indexResults;
    indexResults["AAAA"]= testKmer1;
    indexResults["CCCC"] = testKmer2;

    ftMap.processIndexResults(indexResults);

    ft::KmerClass outputKmer = ftMap.getKmer("AAAA");
    ft::KmerClass outputKmer2 = ftMap.getKmer("CCCC");

    EXPECT_TRUE(ftMap.checkForKmer("AAAA"));
    EXPECT_TRUE(ftMap.checkForKmer("CCCC"));
    EXPECT_TRUE(outputKmer.hasReadID(std::make_pair(2, 1)));
    EXPECT_TRUE(outputKmer2.hasReadID(std::make_pair(4, 1)));
}




//======================================================================
TEST_F(TestFTMap, TestaddKmersToQueryResults )
{
   TEST_DESCRIPTION("Process Query Results");
    // std::set<ft::ReadID> addKmersToQueryResults(ft::QueryClass query, std::set<std::string> kmers,  std::set<ft::ReadID> readIds);

   ft::FTProp _ftProps;
   _ftProps.initFromQSettings("Test_Settings.ini","output.tsv", false);
   _ftProps.setTestProps(20, 100, false);
   ft::FTMap ftMap(_ftProps);
   ft::QueryClass query1(1, ft::QueryType::REF);
   std::set<std::string> kmers = {"AAAA", "CCCC"};

   ft::KmerClass testKmer1("AAAA");
   ft::KmerClass testKmer2("CCCC");
   ft::ReadID a = {1,1};
   ft::ReadID b = {1,2};
   ft::ReadID c = {2,1};
   testKmer1.addReadID(a);
   testKmer1.addReadID(b);
   testKmer1.addReadID(c);
   testKmer2.addReadID(a);
   testKmer2.addReadID(b);
   testKmer2.addReadID(c);
   ftMap.addKmerResults(testKmer1);
   ftMap.addKmerResults(testKmer2);
   std::set<ft::ReadID> readIDs;
   std::set<ft::ReadID> expectedResult = {a,b,c};
   std::set<ft::ReadID> output = ftMap.addKmersToQueryResults(query1, kmers, readIDs);

   EXPECT_EQ(expectedResult, output);


}

//======================================================================
TEST_F(TestFTMap, TestcalculateQueryCount_singles )
{
    TEST_DESCRIPTION("Process Query Results");
    // int FTMap::calculateQueryCount(std::set<ft::ReadID> readIDs)

    ft::FTProp _ftProps;
    _ftProps.initFromQSettings("Test_Settings.ini","output.tsv", false);
    _ftProps.setTestProps(20, 100, false);
    ft::FTMap ftMap(_ftProps);

    ft::ReadID a = {1,1};
    ft::ReadID b = {1,2};
    ft::ReadID c = {2,1};

    std::set<ft::ReadID> readIDs = {a,b,c};
    int querycount = ftMap.calculateQueryCount(readIDs);
    int expectedcount = 3;
    EXPECT_EQ(querycount, expectedcount);


}

//======================================================================
TEST_F(TestFTMap, TestcalculateQueryCount_pairs )
{
    TEST_DESCRIPTION("Process Query Results");
    // int FTMap::calculateQueryCount(std::set<ft::ReadID> readIDs)

    ft::FTProp _ftProps;
    _ftProps.initFromQSettings("Test_Settings.ini","output.tsv", false);
    _ftProps.setTestProps(20, 100, false, true);
    ft::FTMap ftMap(_ftProps);

    ft::ReadID a = {1,1};
    ft::ReadID b = {1,2};
    ft::ReadID c = {2,1};

    std::set<ft::ReadID> readIDs = {a,b,c};
    int querycount = ftMap.calculateQueryCount(readIDs);
    int expectedcount = 2;
    EXPECT_EQ(querycount, expectedcount);


}
//======================================================================
TEST_F(TestFTMap, TestAddingReadIDToSet )
{
    TEST_DESCRIPTION("Process Query Results");
    // int FTMap::calculateQueryCount(std::set<ft::ReadID> readIDs)


    ft::ReadID a = {1,1};
    ft::ReadID b = {1,2};
    ft::ReadID c = {2,1};

    std::set<ft::ReadID> readIDs;

    readIDs.insert(a);
    std::cout << readIDs.size() << std::endl;
    EXPECT_EQ(readIDs.size(), 1);
    readIDs.insert(b);
    std::cout << readIDs.size() << std::endl;
    EXPECT_EQ(readIDs.size(), 2);
    readIDs.insert(c);
    std::cout << readIDs.size() << std::endl;
    EXPECT_EQ(readIDs.size(), 3);
    readIDs.insert(a);
    std::cout << readIDs.size() << std::endl;
    EXPECT_EQ(readIDs.size(), 3);


}

}
