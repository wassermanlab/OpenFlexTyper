#include <gtest/gtest.h>
#include <climits>
#include "queryClass.h"

using namespace std;

namespace ft {
class TestQueryClass : public ::testing::Test {
protected:
    virtual void SetUp() {

    }

    virtual void TeadDown() {
    }

public:

};

#define TEST_DESCRIPTION(desc) RecordProperty("description", desc)

//======================================================================
TEST_F(TestQueryClass, setProperties)
{
    TEST_DESCRIPTION("set Properties");

}

//======================================================================
TEST_F(TestQueryClass, Flags)
{
    TEST_DESCRIPTION("Add a flag to a query");
    ft::QueryClass testQueryClass(1, QueryType::REF);
    std::map<ft::FlagType, std::set<std::string>> flags;
    flags[FlagType::NUK]={"AAAA", "AATT"};

    testQueryClass.setFlags(flags);
    EXPECT_TRUE(testQueryClass.hasKmerFlag(FlagType::NUK, "AAAA"));
    EXPECT_FALSE(testQueryClass.hasKmerFlag(FlagType::NUK, "TTTT"));
    EXPECT_FALSE(testQueryClass.hasKmerFlag(FlagType::OCK, "AAAA"));

    testQueryClass.addFlag(FlagType::OCK, {"AAAA", "CCTT"});
    EXPECT_TRUE(testQueryClass.hasKmerFlag(FlagType::NUK, "AAAA"));
    EXPECT_FALSE(testQueryClass.hasKmerFlag(FlagType::NUK, "TTTT"));
    EXPECT_FALSE(testQueryClass.hasKmerFlag(FlagType::NUK, "CCTT"));
    EXPECT_TRUE(testQueryClass.hasKmerFlag(FlagType::OCK, "AAAA"));
    EXPECT_FALSE(testQueryClass.hasKmerFlag(FlagType::OCK, "TTTT"));
    EXPECT_TRUE(testQueryClass.hasKmerFlag(FlagType::OCK, "CCTT"));

    testQueryClass.removeKmerFlag(FlagType::OCK, "AAAA");
    EXPECT_TRUE(testQueryClass.hasKmerFlag(FlagType::NUK, "AAAA"));
    EXPECT_FALSE(testQueryClass.hasKmerFlag(FlagType::NUK, "TTTT"));
    EXPECT_FALSE(testQueryClass.hasKmerFlag(FlagType::NUK, "CCTT"));
    EXPECT_FALSE(testQueryClass.hasKmerFlag(FlagType::OCK, "AAAA"));
    EXPECT_FALSE(testQueryClass.hasKmerFlag(FlagType::OCK, "TTTT"));
    EXPECT_TRUE(testQueryClass.hasKmerFlag(FlagType::OCK, "CCTT"));

    testQueryClass.removeFlag(FlagType::OCK);
    EXPECT_TRUE(testQueryClass.hasKmerFlag(FlagType::NUK, "AAAA"));
    EXPECT_FALSE(testQueryClass.hasKmerFlag(FlagType::NUK, "TTTT"));
    EXPECT_FALSE(testQueryClass.hasKmerFlag(FlagType::NUK, "CCTT"));
    EXPECT_FALSE(testQueryClass.hasKmerFlag(FlagType::OCK, "AAAA"));
    EXPECT_FALSE(testQueryClass.hasKmerFlag(FlagType::OCK, "TTTT"));
    EXPECT_FALSE(testQueryClass.hasKmerFlag(FlagType::OCK, "CCTT"));


}
}
