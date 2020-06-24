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
TEST_F(TestFTMap, genSlidingSearchStrings)
{
    TEST_DESCRIPTION("genSlidingSearchStrings");
    //input: const std::string& queryString, uint kmerSize, uint stride, bool kmerCounts, uint maxKmers
    std::set<std::string> result;
    std::set<std::string> expectedResult;

    EXPECT_EQ(result, expectedResult);
}
}
