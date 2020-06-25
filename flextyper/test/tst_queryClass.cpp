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
TEST_F(TestQueryClass, Kmer)
{
    TEST_DESCRIPTION("set Properties");
    ft::QueryClass testQueryClass(1, QueryType::REF);

    testQueryClass.setKmers({"AAAA", "AATT"});
    EXPECT_TRUE(testQueryClass.hasKmer("AAAA"));
    EXPECT_TRUE(testQueryClass.hasKmer("AATT"));
    EXPECT_FALSE(testQueryClass.hasKmer("CCCC"));

    testQueryClass.addKmer("TTTT");
    EXPECT_TRUE(testQueryClass.hasKmer("AAAA"));
    EXPECT_TRUE(testQueryClass.hasKmer("AATT"));
    EXPECT_TRUE(testQueryClass.hasKmer("TTTT"));
    EXPECT_FALSE(testQueryClass.hasKmer("CCCC"));

    testQueryClass.removeKmer("AATT");
    EXPECT_TRUE(testQueryClass.hasKmer("AAAA"));
    EXPECT_FALSE(testQueryClass.hasKmer("AATT"));
    EXPECT_TRUE(testQueryClass.hasKmer("TTTT"));
    EXPECT_FALSE(testQueryClass.hasKmer("CCCC"));
}

//======================================================================
TEST_F(TestQueryClass, ReadIDs)
{
    TEST_DESCRIPTION("set Properties");
    ft::QueryClass testQueryClass(1, QueryType::REF);

    testQueryClass.addReadIDs({1000, 2340});
    EXPECT_TRUE(testQueryClass.hasReadID(1000));
    EXPECT_TRUE(testQueryClass.hasReadID(2340));
    EXPECT_FALSE(testQueryClass.hasReadID(666));
    EXPECT_FALSE(testQueryClass.hasReadID(924357));

    testQueryClass.addReadID(666);
    EXPECT_TRUE(testQueryClass.hasReadID(1000));
    EXPECT_TRUE(testQueryClass.hasReadID(2340));
    EXPECT_TRUE(testQueryClass.hasReadID(666));
    EXPECT_FALSE(testQueryClass.hasReadID(924357));

    testQueryClass.removeReadID(2340);
    EXPECT_TRUE(testQueryClass.hasReadID(1000));
    EXPECT_FALSE(testQueryClass.hasReadID(2340));
    EXPECT_TRUE(testQueryClass.hasReadID(666));
    EXPECT_FALSE(testQueryClass.hasReadID(924357));

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
