#include <gtest/gtest.h>
#include "kmergenerator.cpp"

#include <climits>

using namespace std;

namespace ft {
class TestKmerGenerator : public ::testing::Test {
protected:
    virtual void SetUp() {

    }

    virtual void TearDown() {
    }

public:

};

#define TEST_DESCRIPTION(desc) RecordProperty("description", desc)

//======================================================================
TEST_F(TestKmerGenerator, init)
{
    TEST_DESCRIPTION("genSlidingSearchStrings");


    uint _kmerSize = 5;
    bool _refOnly = true;
    SearchType _searchType = SLIDING;
    uint _overlap = 0;
    uint _stride = 1;
    uint _maxKmers  = 30;

    KmerGenerator _kgen(_kmerSize, _refOnly, _searchType, _overlap, _stride,  _maxKmers);

    EXPECT_EQ(_kmerSize, _kgen.getKmerSize());
    EXPECT_EQ(_refOnly, _kgen.getRefOnly());
    EXPECT_EQ(_searchType, _kgen.getSearchType());
    EXPECT_EQ(_overlap, _kgen.getOverlap());
    EXPECT_EQ(_stride, _kgen.getStride());
    EXPECT_EQ(_maxKmers, _kgen.getMaxKmers());

}

//======================================================================
TEST_F(TestKmerGenerator, genSlidingSearchStrings)
{
    TEST_DESCRIPTION("genSlidingSearchStrings");
    uint _kmerSize = 5;
    bool _refOnly = true;
    SearchType _searchType = SLIDING;
    uint _overlap = 0;
    uint _stride = 1;
    uint _maxKmers  = 30;
    KmerGenerator _kgen(_kmerSize, _refOnly, _searchType, _overlap, _stride, _maxKmers);

    std::string queryString = "AAAAATCCCCC";

    std::set<std::string> expectedResult = {"AAAAA", "AAAAT", "AAATC", "AATCC", "ATCCC", "TCCCC", "CCCCC"};
    std::set<std::string> results = _kgen.genSlidingSearchStrings(queryString);

    EXPECT_EQ(results, expectedResult);
}

//======================================================================
TEST_F(TestKmerGenerator, genCenteredSearchStrings)
{
    TEST_DESCRIPTION("genCenteredSearchStrings");


    uint _kmerSize = 5;
    bool _refOnly = true;
    SearchType _searchType = CENTERED;
    uint _overlap = 0;
    uint _stride = 1;
    uint _maxKmers  = 30;

    KmerGenerator _kgen(_kmerSize, _refOnly, _searchType, _overlap, _stride, _maxKmers);

    //input: const std::string& queryString, uint kmerSize, uint overlap, uint stride, bool kmerCounts, uint maxKmers
    std::string queryString = "AAAAATCCCCC";

    std::set<std::string> expectedResults = {"AAAAT", "AAATC", "AATCC", "ATCCC", "TCCCC"};
    std::set<std::string> results = _kgen.genCenteredSearchStrings(queryString);

    EXPECT_EQ(results, expectedResults);
}

}
