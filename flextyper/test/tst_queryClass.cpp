#include <gtest/gtest.h>
#include <climits>
#include "queryClass.cpp"

using namespace std;

namespace ft {
class TestQueryClass : public ::testing::Test {
protected:
    virtual void SetUp() {

    }

    virtual void TearDown() {
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
TEST_F(TestQueryClass, OverloadOperators)
{
    TEST_DESCRIPTION("Test the overload operators ");

    ft::QueryClass* testQuery1Ref = new ft::QueryClass(1, ft::QueryType::REF);
    ft::QueryClass* testQuery1Alt = new ft::QueryClass(1, ft::QueryType::ALT);
    ft::QueryClass* testQuery2Ref = new ft::QueryClass(2, ft::QueryType::REF);

    EXPECT_TRUE(testQuery1Alt < testQuery2Ref);
    EXPECT_TRUE(testQuery1Ref < testQuery1Alt);
    EXPECT_TRUE(testQuery2Ref == testQuery2Ref);
    EXPECT_FALSE(testQuery1Ref == testQuery1Alt);
    EXPECT_FALSE(testQuery2Ref < testQuery1Alt);

}

//======================================================================
TEST_F(TestQueryClass, DISABLED_Flags)
{
    TEST_DESCRIPTION("Add a flag to a query");
    ft::QueryClass* testQuery1Ref = new ft::QueryClass(1, ft::QueryType::REF);
    std::map<ft::FlagType, std::set<std::string>> flags;
    flags[FlagType::NUK]={"AAAA", "AATT"};

    testQuery1Ref->setFlags(flags);
    EXPECT_TRUE(testQuery1Ref->hasKmerFlag(FlagType::NUK, "AAAA"));
    EXPECT_FALSE(testQuery1Ref->hasKmerFlag(FlagType::NUK, "TTTT"));
    EXPECT_FALSE(testQuery1Ref->hasKmerFlag(FlagType::OCK, "AAAA"));

    testQuery1Ref->addFlag(FlagType::OCK, {"AAAA", "CCTT"});
    EXPECT_TRUE(testQuery1Ref->hasKmerFlag(FlagType::NUK, "AAAA"));
    EXPECT_FALSE(testQuery1Ref->hasKmerFlag(FlagType::NUK, "TTTT"));
    EXPECT_FALSE(testQuery1Ref->hasKmerFlag(FlagType::NUK, "CCTT"));
    EXPECT_TRUE(testQuery1Ref->hasKmerFlag(FlagType::OCK, "AAAA"));
    EXPECT_FALSE(testQuery1Ref->hasKmerFlag(FlagType::OCK, "TTTT"));
    EXPECT_TRUE(testQuery1Ref->hasKmerFlag(FlagType::OCK, "CCTT"));

    testQuery1Ref->removeKmerFlag(FlagType::OCK, "AAAA");
    EXPECT_TRUE(testQuery1Ref->hasKmerFlag(FlagType::NUK, "AAAA"));
    EXPECT_FALSE(testQuery1Ref->hasKmerFlag(FlagType::NUK, "TTTT"));
    EXPECT_FALSE(testQuery1Ref->hasKmerFlag(FlagType::NUK, "CCTT"));
    EXPECT_FALSE(testQuery1Ref->hasKmerFlag(FlagType::OCK, "AAAA"));
    EXPECT_FALSE(testQuery1Ref->hasKmerFlag(FlagType::OCK, "TTTT"));
    EXPECT_TRUE(testQuery1Ref->hasKmerFlag(FlagType::OCK, "CCTT"));

    testQuery1Ref->removeFlag(FlagType::OCK);
    EXPECT_TRUE(testQuery1Ref->hasKmerFlag(FlagType::NUK, "AAAA"));
    EXPECT_FALSE(testQuery1Ref->hasKmerFlag(FlagType::NUK, "TTTT"));
    EXPECT_FALSE(testQuery1Ref->hasKmerFlag(FlagType::NUK, "CCTT"));
    EXPECT_FALSE(testQuery1Ref->hasKmerFlag(FlagType::OCK, "AAAA"));
    EXPECT_FALSE(testQuery1Ref->hasKmerFlag(FlagType::OCK, "TTTT"));
    EXPECT_FALSE(testQuery1Ref->hasKmerFlag(FlagType::OCK, "CCTT"));

}

}
