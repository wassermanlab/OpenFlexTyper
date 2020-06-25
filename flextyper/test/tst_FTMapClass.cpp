#include <gtest/gtest.h>
#include "kmergenerator.cpp"
#include "queryextractor.h"
#include <climits>

using namespace std;

namespace ft {
class TestFTMap : public ::testing::Test {
protected:
    virtual void SetUp() {

    }

    virtual void TeadDown() {
    }

public:

};

#define TEST_DESCRIPTION(desc) RecordProperty("description", desc)

//======================================================================
TEST_F(TestFTMap, setProperties)
{
    TEST_DESCRIPTION("set Properties");
    ft::FTMap ftMap;
    uint kmerSize;
    bool refOnly;
    SearchType searchType;
    uint overlap;
    uint stride;
    bool crossover;
    bool ignoreNonUniqueKmers;
    bool kmerCounts;
    uint maxKmers;
    uint maxTotalKmers;
    bool returnMatchesOnly;

    ftMap.setProperties(kmerSize, refOnly, searchType, overlap, stride, crossover, ignoreNonUniqueKmers, kmerCounts, maxKmers, maxTotalKmers, returnMatchesOnly);

    EXPECT_EQ(kmerSize, ftMap.getKmerSize());
    EXPECT_EQ(refOnly, ftMap.getRefOnlyFlag());
    EXPECT_EQ(searchType, ftMap.getSearchType());
    EXPECT_EQ(overlap, ftMap.getOverlap());
    EXPECT_EQ(stride, ftMap.getStride());
    EXPECT_EQ(crossover, ftMap.getCrossoverFlag());
    EXPECT_EQ(ignoreNonUniqueKmers, ftMap.getIgnoreNonUniqueKmersFlag());
    EXPECT_EQ(kmerCounts, ftMap.getKmerCountsFlag());
    EXPECT_EQ(maxKmers, ftMap.getMaxKmers());
    EXPECT_EQ(maxTotalKmers, ftMap.getMaxTotalKmers());
    EXPECT_EQ(returnMatchesOnly, ftMap.getMatchesOnlyFlag());
}

//======================================================================
TEST_F(TestFTMap, TestCheckKmer)
{
    TEST_DESCRIPTION("Check Kmer");
    ft::FTMap ftMap;
    ftMap.setKmers({ft::KmerClass("AAAA"),ft::KmerClass("TTTT")});

    EXPECT_TRUE(ftMap.checkForKmer(ft::KmerClass("AAAA")));
    EXPECT_FALSE(ftMap.checkForKmer(ft::KmerClass("AAAC")));
}

//======================================================================
TEST_F(TestFTMap, TestCheckQIDT)
{
    TEST_DESCRIPTION("check QIdT");
    //bool checkQIDT(ft::QIdT testQueryObject);
    ft::FTMap ftMap;
    ftMap.setQueries({ft::QueryClass(1, ft::QueryType::REF),ft::QueryClass(1, ft::QueryType::ALT), ft::QueryClass(2, ft::QueryType::REF)});
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
    ft::FTMap ftMap;
    ftMap.setKmers({ft::KmerClass("AAAA"),ft::KmerClass("TTTT")});

    EXPECT_EQ("AAAA", ftMap.findKmer("AAAA").getKmer());
    EXPECT_EQ("TTTT", ftMap.findKmer("TTTT").getKmer());
}
//======================================================================
TEST_F(TestFTMap, TestGetQuery)
{
    TEST_DESCRIPTION("Get Query");
    //ft::QueryClass getQuery(ft::QIdT qIDT);
    ft::FTMap ftMap;
    ftMap.setQueries({ft::QueryClass(1, ft::QueryType::REF),ft::QueryClass(1, ft::QueryType::ALT), ft::QueryClass(2, ft::QueryType::REF)});

    ft::QIdT truetest = std::make_pair(1, ft::QueryType::REF);
    ft::QIdT truetest2 = std::make_pair(1, ft::QueryType::ALT);
    ft::QIdT truetest3 = std::make_pair(2, ft::QueryType::REF);
    EXPECT_EQ(truetest, ftMap.getQuery(truetest).getQIdT());
    EXPECT_EQ(truetest2, ftMap.getQuery(truetest2).getQIdT());
    EXPECT_EQ(truetest3, ftMap.getQuery(truetest3).getQIdT());
}

//======================================================================
TEST_F(TestFTMap, TestAddKmer)
{
    TEST_DESCRIPTION("Add Kmer");
    //void addKmer(ft::KmerClass kmer);
    ft::FTMap ftMap;
    ft::KmerClass testGoodKmer("AAAA");
    ft::KmerClass testBadKmer("AAAC");
    ftMap.addKmer(testGoodKmer);
    EXPECT_TRUE(ftMap.checkForKmer(testGoodKmer));
    EXPECT_FALSE(ftMap.checkForKmer(testBadKmer));
}
//======================================================================
TEST_F(TestFTMap, TestAddQuery)
{
    TEST_DESCRIPTION("Add Query");
    //void addQuery(ft::QueryClass query);
    ft::FTMap ftMap;
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

}
