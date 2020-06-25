#include <gtest/gtest.h>
#include "kmergenerator.cpp"
#include "queryextractor.h"
#include <climits>

using namespace std;

namespace ft {
class TestKmerGenerator : public ::testing::Test {
protected:
    virtual void SetUp() {
    }

    virtual void TeadDown() {
    }

public:
    KmerGenerator _kmerGenerator;
};

#define TEST_DESCRIPTION(desc) RecordProperty("description", desc)

//======================================================================
TEST_F(TestKmerGenerator, genSlidingSearchStrings)
{
    TEST_DESCRIPTION("genSlidingSearchStrings");

    std::string queryString = "AAAAATCCCCC";
    uint kmerSize = 5;
    uint stride = 1;
    bool kmerCounts = false;
    uint maxKmers = 30;
    std::set<std::string> expectedResult = {"AAAAA", "AAAAT", "AAATC", "AATCC", "ATCCC", "TCCCC", "CCCCC"};
    std::set<std::string> results = _kmerGenerator.genSlidingSearchStrings(queryString, kmerSize, stride, kmerCounts, maxKmers);

    EXPECT_EQ(results, expectedResult);
}

//======================================================================
TEST_F(TestKmerGenerator, genCenteredSearchStrings)
{
    TEST_DESCRIPTION("genCenteredSearchStrings");

    //input: const std::string& queryString, uint kmerSize, uint overlap, uint stride, bool kmerCounts, uint maxKmers
    std::string queryString = "AAAAATCCCCC";
    uint kmerSize = 5;
    uint overlap = 1;
    uint stride = 1;
    bool kmerCounts = false;
    uint maxKmers = 30;
    std::set<std::string> expectedResults = {"AAAAT", "AAATC", "AATCC", "ATCCC", "TCCCC"};
    std::set<std::string> results = _kmerGenerator.genCenteredSearchStrings(queryString, kmerSize, overlap, stride, kmerCounts, maxKmers);
;
    EXPECT_EQ(results, expectedResults);
}
//======================================================================
TEST_F(TestKmerGenerator, genQueryClassKmersCentered)
{
    TEST_DESCRIPTION("genQueryClassKmers");

    //input: QueryClass KmerGenerator::genQueryClassKmers(
    int queryID;
    std::string querystring = "AAAAATCCCCC";
    ft::QueryType queryType = ft::QueryType::REF;
    SearchType searchType = CENTERED;
    uint kmerSize = 5;
    uint overlap = 0;
    uint stride = 1;
    bool kmerCounts = false;
    uint maxKmers = 30;
    QueryClass expectedResult(1, ft::QueryType::REF);
    expectedResult.setQueryString(querystring);
    expectedResult.setKmers({"AAAAA", "AAAAT", "AAATC", "AATCC", "ATCCC", "TCCCC", "CCCCC"});

    QueryClass result = _kmerGenerator.genQueryClassKmers(queryID, querystring, queryType, searchType, kmerSize, overlap, stride, kmerCounts, maxKmers);

    //EXPECT_EQ(result, expectedResult);
}
//======================================================================
TEST_F(TestKmerGenerator, genQueryClassKmersSliding)
{
    TEST_DESCRIPTION("genQueryClassKmers");

    //input: QueryClass KmerGenerator::genQueryClassKmers(
    int queryID;
    std::string querystring = "AAAAATCCCCC";
    ft::QueryType queryType = ft::QueryType::REF;
    SearchType searchType = SLIDING;
    uint kmerSize = 5;
    uint overlap = 2;
    uint stride = 1;
    bool kmerCounts = false;
    uint maxKmers = 30;
    QueryClass expectedResult(1, ft::QueryType::REF);
    expectedResult.setQueryString(querystring);
    expectedResult.setKmers({"AAAAA", "AAAAT", "AAATC", "AATCC", "ATCCC", "TCCCC", "CCCCC"});

    QueryClass result = _kmerGenerator.genQueryClassKmers(queryID, querystring, queryType, searchType, kmerSize, overlap, stride, kmerCounts, maxKmers);

    //EXPECT_EQ(result, expectedResult);
}
//======================================================================
TEST_F(TestKmerGenerator, genSearchKmers)
{
    TEST_DESCRIPTION("genSearchKmers");

    //input: std::set<QueryClass> KmerGenerator::genSearchKmers(std::set<Query>& inputQueries, ft::FTMap& ftMap)
    std::set<QueryClass> result;
    std::set<QueryClass> expectedResult;

    //EXPECT_EQ(result, expectedResult);
}


//======================================================================
TEST_F(TestKmerGenerator, genKmerMap)
{
    TEST_DESCRIPTION("genKmerMap");

    //void KmerGenerator::genKmerMap(std::set<Query>& inputQueries, ft::FTMap& ftMap)

    std::set<QueryClass> result;
    std::set<QueryClass> expectedResult;

    //EXPECT_EQ(result, expectedResult);
}



}
