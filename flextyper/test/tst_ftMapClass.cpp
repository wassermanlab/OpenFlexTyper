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
    _ftProps.initFromQSettings("Test_Settings.ini", false);
    ft::FTMap ftMap(_ftProps);
    ft::KmerClass testKmer1("AAAA");
    ftMap.addKmer(testKmer1);
    EXPECT_TRUE(ftMap.checkForKmer("AAAA"));
    EXPECT_FALSE(ftMap.checkForKmer("AAAC"));
}

//======================================================================
TEST_F(TestFTMap, TestCheckQIDT)
{
    TEST_DESCRIPTION("check QIdT");
    //bool checkQIDT(ft::QIdT testQueryObject);
    ft::FTProp _ftProps;
    _ftProps.initFromQSettings("Test_Settings.ini", false);
    ft::FTMap ftMap(_ftProps);
    ft::QueryClass testQuery1Ref =  ft::QueryClass(1, ft::QueryType::REF);
    ft::QueryClass testQuery1Alt =  ft::QueryClass(1, ft::QueryType::ALT);
    ft::QueryClass testQuery2Ref =  ft::QueryClass(2, ft::QueryType::REF);
    ftMap.addQuery(testQuery1Alt);
    ftMap.addQuery(testQuery1Ref);
    ftMap.addQuery(testQuery2Ref);

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
TEST_F(TestFTMap, TestFindKmer)
{
    TEST_DESCRIPTION("Find Kmer");
    //ft::KmerClass findKmer(std::string kmer);
    ft::FTProp _ftProps;
    _ftProps.initFromQSettings("Test_Settings.ini", false);
    ft::FTMap ftMap(_ftProps);
    ftMap.addKmer(ft::KmerClass("AAAA"));

    EXPECT_EQ("AAAA", ftMap.findKmer("AAAA")->getKmer());
}
//======================================================================
TEST_F(TestFTMap, TestGetQuery)
{
    TEST_DESCRIPTION("Get Query");
    //ft::QueryClass getQuery(ft::QIdT qIDT);
    ft::FTProp _ftProps;
    _ftProps.initFromQSettings("Test_Settings.ini", false);
    ft::FTMap ftMap(_ftProps);
    ft::QueryClass testQuery1Ref =  ft::QueryClass(1, ft::QueryType::REF);
    ft::QueryClass testQuery1Alt = ft::QueryClass(1, ft::QueryType::ALT);
    ft::QueryClass testQuery2Ref = ft::QueryClass(2, ft::QueryType::REF);
    ftMap.addQuery(testQuery1Ref);
    ftMap.addQuery(testQuery1Alt);
    ftMap.addQuery(testQuery2Ref);

    ft::QIdT truetest = std::make_pair(1, ft::QueryType::REF);
    ft::QIdT truetest2 = std::make_pair(1, ft::QueryType::ALT);
    ft::QIdT truetest3 = std::make_pair(2, ft::QueryType::REF);

    EXPECT_EQ(testQuery1Ref, ftMap.getQuery(truetest));
    EXPECT_EQ(testQuery1Alt, ftMap.getQuery(truetest2));
    EXPECT_EQ(testQuery2Ref, ftMap.getQuery(truetest3));
}

//======================================================================
TEST_F(TestFTMap, TestAddKmer)
{
    TEST_DESCRIPTION("Add Kmer");
    //void addKmer(ft::KmerClass kmer);
    ft::FTProp _ftProps;
    _ftProps.initFromQSettings("Test_Settings.ini", false);
    ft::FTMap ftMap(_ftProps);
    ft::KmerClass testGoodKmer("AAAA");
    ft::KmerClass testBadKmer("AAAC");
    ftMap.addKmer(testGoodKmer);
    EXPECT_TRUE(ftMap.checkForKmer(testGoodKmer.getKmer()));
    EXPECT_FALSE(ftMap.checkForKmer(testBadKmer.getKmer()));
}
//======================================================================
TEST_F(TestFTMap, TestCreateKmer)
{
    TEST_DESCRIPTION("Add Kmer");
    //void addKmer(ft::KmerClass kmer);
    ft::FTProp _ftProps;
    _ftProps.initFromQSettings("Test_Settings.ini", false);
    ft::FTMap ftMap(_ftProps);
    ftMap.createKmer("AAAA");
    EXPECT_TRUE(ftMap.checkForKmer("AAAA"));
    EXPECT_FALSE(ftMap.checkForKmer("AAAC"));
}

//======================================================================
TEST_F(TestFTMap, TestAddQuery)
{
    TEST_DESCRIPTION("Add Query");
    //void addQuery(ft::QueryClass query);
    ft::FTProp _ftProps;
    _ftProps.initFromQSettings("Test_Settings.ini", false);
    ft::FTMap ftMap(_ftProps);
    ftMap.addQuery(ft::QueryClass(1, ft::QueryType::REF));
    ft::QIdT testGoodQIdT = std::make_pair(1, ft::QueryType::REF);
    ft::QIdT testBadQIdT = std::make_pair(6, ft::QueryType::REF);
    EXPECT_TRUE(ftMap.checkForQIDT(testGoodQIdT));
    EXPECT_FALSE(ftMap.checkForQIDT(testBadQIdT));
}

//======================================================================
TEST_F(TestFTMap, TestCreateQuery)
{
    TEST_DESCRIPTION("Create Query");
    //void addQuery(ft::QueryClass query);
    ft::FTProp _ftProps;
    _ftProps.initFromQSettings("Test_Settings.ini", false);
    ft::FTMap ftMap(_ftProps);
    ftMap.createQuery(1, ft::QueryType::REF);
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
    _ftProps.initFromQSettings("Test_Settings.ini", false);
    ft::FTMap ftMap(_ftProps);

    ft::KmerClass testKmer1("AAAA");
    testKmer1.addReadID(std::make_pair(1, 1));
    testKmer1.addKFlag(ft::FlagType::ABK);

    ftMap.addKmerResults(testKmer1);
    ft::ReadID testRID = std::make_pair(1, 1);
    ft::KmerClass* kmer = ftMap.findKmer(testKmer1._kmer);

    EXPECT_TRUE(kmer->hasFlag(ft::FlagType::ABK));
    EXPECT_TRUE(kmer->hasReadID(testRID));

}

//======================================================================
TEST_F(TestFTMap, TestAddIndexResults)
{
    TEST_DESCRIPTION("Add Index Results");
    //void addIndexResults(std::set<ft::KmerClass> indexResults);
    ft::FTProp _ftProps;
    _ftProps.initFromQSettings("Test_Settings.ini", false);
    ft::FTMap ftMap(_ftProps);

    ft::KmerClass testKmer1("AAAA");
    testKmer1.addKPosition(123);
    ft::KmerClass testKmer2("CCCC");
    testKmer2.addKPosition(345);
    std::set<ft::KmerClass> indexResults = {testKmer1, testKmer2};

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
    _ftProps.initFromQSettings("Test_Settings.ini", false);
    ft::FTMap ftMap(_ftProps);
    ftMap._ftProps._numOfReads = 20;
    ftMap._ftProps._revComp = false;
    ftMap._ftProps._readLength = 100;
    ft::KmerClass testKmer1("AAAA");
    testKmer1.addKPosition(123);
    ft::KmerClass testKmer2("CCCC");
    testKmer2.addKPosition(345);
    std::set<ft::KmerClass> indexResults = {testKmer1, testKmer2};

    ftMap.processIndexResults(indexResults);

    ft::KmerClass* outputKmer = ftMap.findKmer("AAAA");
    ft::KmerClass* outputKmer2 = ftMap.findKmer("CCCC");

    EXPECT_TRUE(ftMap.checkForKmer("AAAA"));
    EXPECT_TRUE(ftMap.checkForKmer("CCCC"));
    EXPECT_TRUE(outputKmer->hasReadID(std::make_pair(2, 1)));
    EXPECT_TRUE(outputKmer2->hasReadID(std::make_pair(4, 1)));
}

}
