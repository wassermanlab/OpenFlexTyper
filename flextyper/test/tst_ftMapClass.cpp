#include <gtest/gtest.h>

#include "ftMapClass.cpp"

#include "ftPropsClass.cpp"
#include "kmergenerator.cpp"
#include "ftKPropsClass.cpp"
#include "stats.cpp"

#include <fstream>
#include <climits>

using namespace std;

namespace ft {
class TestFTMap : public ::testing::Test {
protected:
//    static void SetUpTestSuite()
//    {
//        //ft::FTProp* _ftProps;
//        ofstream tmpFile("tempConfig.ini");
//        if (tmpFile.is_open()) {
//            tmpFile <<  "queryFile 		= path_query.txt"
//                        "kmerSize 		= 30"
//                        "overlap 		= 0"
//                        "stride 			= 5"
//                        "maxOccurences 		= 2000"
//                        "threadNumber 		= 512"
//                        "readLength 		= 150"
//                        "indexFileLocation 	= ."
//                        "outputFolder 		= ."
//                        "refOnly 		= False"
//                        "searchType 		= SLIDING"
//                        "multithread 		= True"
//                        "ignoreNonUniqueKmers 	= False"
//                        "kmerCounts 		= False"
//                        "matchingReads 		= MixedVirus_100.fasta";
//            tmpFile.close();
//        }
        //_ftProps->initFromQSettings("tempConfig.ini", false);

//    };
//    static void TearDownTestSuite() {
//         // _ftProps= nullptr;
//    }

    virtual void SetUp() {

    }

    virtual void TearDown() {
    }

public:

//static ft::FTProp* _ftProps;

};

#define TEST_DESCRIPTION(desc) RecordProperty("description", desc)
//ft::FTProp* TestFTMap::_ftProps = new ft::FTProp();
/*
//======================================================================
TEST_F(TestFTMap, TestCheckKmer)
{
    TEST_DESCRIPTION("Check Kmer");
    ft::FTMap ftMap(*_ftProps);
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
    ft::FTMap ftMap(*_ftProps);
    ft::QueryClass testQuery1Ref =  ft::QueryClass(1, ft::QueryType::REF);
    ft::QueryClass testQuery1Alt =  ft::QueryClass(1, ft::QueryType::ALT);
    ft::QueryClass testQuery2Ref =  ft::QueryClass(2, ft::QueryType::REF);

    ftMap.setQueries({testQuery1Alt, testQuery1Ref, testQuery2Ref});
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

    ft::FTMap ftMap(*_ftProps);
    ftMap.setKmers({ft::KmerClass("AAAA"),ft::KmerClass("TTTT")});

    EXPECT_EQ("AAAA", ftMap.findKmer("AAAA")->getKmer());
    EXPECT_EQ("TTTT", ftMap.findKmer("TTTT")->getKmer());
}
//======================================================================
TEST_F(TestFTMap, TestGetQuery)
{
    TEST_DESCRIPTION("Get Query");
    //ft::QueryClass getQuery(ft::QIdT qIDT);

    ft::FTMap ftMap(*_ftProps);
    ft::QueryClass* testQuery1Ref =  new ft::QueryClass(1, ft::QueryType::REF);
    ft::QueryClass* testQuery1Alt = new ft::QueryClass(1, ft::QueryType::ALT);
    ft::QueryClass* testQuery2Ref = new ft::QueryClass(2, ft::QueryType::REF);
    ftMap.addQuery(*testQuery1Ref);
    ftMap.addQuery(*testQuery1Alt);
    ftMap.addQuery(*testQuery2Ref);

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
    ft::FTMap ftMap(*_ftProps);
    ft::KmerClass testGoodKmer("AAAA");
    ft::KmerClass testBadKmer("AAAC");
    ftMap.addKmer(testGoodKmer);
    EXPECT_TRUE(ftMap.checkForKmer(testGoodKmer.getKmer()));
    EXPECT_FALSE(ftMap.checkForKmer(testBadKmer.getKmer()));
}
//======================================================================
TEST_F(TestFTMap, TestAddQuery)
{
    TEST_DESCRIPTION("Add Query");
    //void addQuery(ft::QueryClass query);
    ft::FTMap ftMap(*_ftProps);
    ftMap.addQuery(ft::QueryClass(1, ft::QueryType::REF));
    ft::QIdT testGoodQIdT = std::make_pair(1, ft::QueryType::REF);
    ft::QIdT testBadQIdT = std::make_pair(6, ft::QueryType::REF);
    EXPECT_TRUE(ftMap.checkForQIDT(testGoodQIdT));
    EXPECT_FALSE(ftMap.checkForQIDT(testBadQIdT));
}

//======================================================================
TEST_F(TestFTMap, TestAddQIDtoKmer)
{
    TEST_DESCRIPTION("Add QID to Kmer");
    //void addQIDtoKmer(std::string kmer, int queryID, ft::QueryType queryIDType);

}
//======================================================================
TEST_F(TestFTMap, TestAddIndexResults)
{
    TEST_DESCRIPTION("Add Index Results");
    //void addIndexResults(std::set<ft::KmerClass> indexResults);
    std::string result;
    std::string expectedResult;

    EXPECT_EQ(result, expectedResult);
}

//======================================================================
TEST_F(TestFTMap, TestProcessIndexResults)
{
    TEST_DESCRIPTION("Process Index Results");
    //void processIndexResults(std::set<ft::KmerClass> indexResults, uint readLength);
    std::string result;
    std::string expectedResult;

    EXPECT_EQ(result, expectedResult);
}
*/
}
