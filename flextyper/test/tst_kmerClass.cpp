#include <gtest/gtest.h>
#include <climits>
#include "kmerClass.h"

using namespace std;

namespace ft {
class TestKmerClass : public ::testing::Test {
protected:
    virtual void SetUp() {

    }

    virtual void TeadDown() {
    }

public:

};

#define TEST_DESCRIPTION(desc) RecordProperty("description", desc)

//======================================================================
TEST_F(TestKmerClass, getKmer)
{
    TEST_DESCRIPTION("get Kmer string");
    ft::KmerClass testKmerClass("AAAA")

    EXPECT_EQ(testKmerClass.getKmer(), "AAAA");
}

//======================================================================
TEST_F(TestKmerClass, hasQuery)
{
    TEST_DESCRIPTION("see if a kmer class has a specific QIdT ");
    ft::KmerClass testKmerClass("AAAA");

    ft::QIdT goodQueryIDT = std::make_pair(1, ft::QueryType::REF);
    ft::QIdT badQueryIDT = std::make_pair(1, ft::QueryType::ALT);
    ft::QIdT badQueryIDT2 = std::make_pair(6, ft::QueryType::REF);

    testKmerClass.setQueryIDs({goodQueryIDT});

    EXPECT_TRUE(testKmerClass.hasQuery(goodQueryIDT));
    EXPECT_FALSE(testKmerClass.hasQuery(badQueryIDT)); // mismatch query type
    EXPECT_FALSE(testKmerClass.hasQuery(badQueryIDT2));// mismatch query id

}

//======================================================================
TEST_F(TestKmerClass, addQueryDifferentID)
{
    TEST_DESCRIPTION("Add single query to kmer class with a different ID");

    ft::KmerClass testKmerClass("AAAA");

    ft::QIdT goodQueryIDT = std::make_pair(1, ft::QueryType::REF);
    ft::QIdT newQueryIDT = std::make_pair(6, ft::QueryType::REF);
    ft::QIdT badQueryIDT = std::make_pair(1, ft::QueryType::ALT);
    ft::QIdT badQueryIDT2 = std::make_pair(6, ft::QueryType::ALT);
    testKmerClass.setQueryIDs({goodQueryIDT});
    testKmerClass.addQuery(newQueryIDT);

    EXPECT_TRUE(testKmerClass.hasQuery(goodQueryIDT));
    EXPECT_TRUE(testKmerClass.hasQuery(newQueryIDT));
    EXPECT_FALSE(testKmerClass.hasQuery(badQueryIDT)); // mismatch query type
    EXPECT_FALSE(testKmerClass.hasQuery(badQueryIDT2));// mismatch query id

}

//======================================================================
TEST_F(TestKmerClass, addQueryDifferentType)
{
    TEST_DESCRIPTION("Add single query to kmer class with a different type");

    ft::KmerClass testKmerClass("AAAA");

    ft::QIdT goodQueryIDT = std::make_pair(1, ft::QueryType::REF);
    ft::QIdT newQueryIDT = std::make_pair(1, ft::QueryType::ALT);
    ft::QIdT badQueryIDT = std::make_pair(2, ft::QueryType::REF);
    ft::QIdT badQueryIDT2 = std::make_pair(2, ft::QueryType::ALT);
    testKmerClass.setQueryIDs({goodQueryIDT});
    testKmerClass.addQuery(newQueryIDT);

    EXPECT_TRUE(testKmerClass.hasQuery(goodQueryIDT));
    EXPECT_TRUE(testKmerClass.hasQuery(newQueryIDT));
    EXPECT_FALSE(testKmerClass.hasQuery(badQueryIDT)); // mismatch query type
    EXPECT_FALSE(testKmerClass.hasQuery(badQueryIDT2));// mismatch query id
}

//======================================================================
TEST_F(TestKmerClass, addQueryDifferentIDandType)
{
    TEST_DESCRIPTION("Add single query to kmer class with a different type");

    ft::KmerClass testKmerClass("AAAA");

    ft::QIdT goodQueryIDT = std::make_pair(1, ft::QueryType::REF);
    ft::QIdT newQueryIDT = std::make_pair(2, ft::QueryType::ALT);
    ft::QIdT badQueryIDT = std::make_pair(2, ft::QueryType::REF);
    ft::QIdT badQueryIDT2 = std::make_pair(1, ft::QueryType::ALT);
    testKmerClass.setQueryIDs({goodQueryIDT});
    testKmerClass.addQuery(newQueryIDT);

    EXPECT_TRUE(testKmerClass.hasQuery(goodQueryIDT));
    EXPECT_TRUE(testKmerClass.hasQuery(newQueryIDT));
    EXPECT_FALSE(testKmerClass.hasQuery(badQueryIDT)); // mismatch query type
    EXPECT_FALSE(testKmerClass.hasQuery(badQueryIDT2));// mismatch query id
}

//======================================================================
TEST_F(TestKmerClass, KFlag)
{
    TEST_DESCRIPTION("Add single flag to kmer class");
    ft::KmerClass testKmerClass("AAAA");

    testKmerClass.setKFlags({FlagType::NUK});
    EXPECT_TRUE(testKmerClass.hasFlag(FlagType::NUK));
    EXPECT_FALSE(testKmerClass.hasFlag(FlagType::OCK));

    testKmerClass.addKFlag(FlagType::OCK);
    EXPECT_TRUE(testKmerClass.hasFlag(FlagType::OCK));
    EXPECT_FALSE(testKmerClass.hasFlag(FlagType::ABK));

    testKmerClass.removeKFlag(FlagType::NUK);
    EXPECT_FALSE(testKmerClass.hasFlag(FlagType::NUK));
    EXPECT_TRUE(testKmerClass.hasFlag(FlagType::OCK));

}

//======================================================================
TEST_F(TestKmerClass, KPosition)
{
    TEST_DESCRIPTION("Add single position to kmer class");
    ft::KmerClass testKmerClass("AAAA");

    testKmerClass.setKPositions({1000, 2340});
    EXPECT_TRUE(testKmerClass.hasKPosition(1000));
    EXPECT_FALSE(testKmerClass.hasKPosition(666));

    testKmerClass.addKPosition(666);
    EXPECT_TRUE(testKmerClass.hasKPosition(666));
    EXPECT_FALSE(testKmerClass.hasKPosition(924357));

    testKmerClass.removeKPosition(2340);
    EXPECT_FALSE(testKmerClass.hasKPosition(2340));
    EXPECT_TRUE(testKmerClass.hasKPosition(1000));
    EXPECT_TRUE(testKmerClass.hasKPosition(666));
}

//======================================================================
TEST_F(TestKmerClass, ReadID)
{
    TEST_DESCRIPTION("add and remove single Read ID");
    ft::KmerClass testKmerClass("AAAA");


    testKmerClass.setReadIDs(){1000, 2340});
    EXPECT_TRUE(testKmerClass.hasReadID(1000));
    EXPECT_FALSE(testKmerClass.hasReadID(666));

    testKmerClass.addReadID(666);
    EXPECT_TRUE(testKmerClass.hasReadID(666));
    EXPECT_FALSE(testKmerClass.hasReadID(924357));

    testKmerClass.removeReadID(2340);
    EXPECT_FALSE(testKmerClass.hasReadID(2340));
    EXPECT_TRUE(testKmerClass.hasReadID(1000));
    EXPECT_TRUE(testKmerClass.hasReadID(666));

}

//======================================================================
TEST_F(TestKmerClass, hasKmer)
{
    TEST_DESCRIPTION("see if a kmer class has the same kmer ");

    ft::KmerClass testKmerClass("AAAA");

    EXPECT_TRUE(testKmerClass.hasKmer("AAAA"));
    EXPECT_FALSE(testKmerClass.hasKmer("AAA"));
    EXPECT_FALSE(testKmerClass.hasKmer("TTTT"));
}

//======================================================================
TEST_F(TestKmerClass, isKmerEqual)
{
    TEST_DESCRIPTION("see if a kmer class has a specific kmer");

    ft::KmerClass goodtestKmer("AAAA");
    ft::KmerClass badtestKmer("AAA");
    ft::KmerClass badtestKmer2("TTTT");
    ft::KmerClass testkmerClass("AAAA");
    EXPECT_TRUE(testkmerClass.isKmerEqual(goodtestKmer));
    EXPECT_FALSE(testkmerClass.isKmerEqual(badtestKmer));
    EXPECT_FALSE(testkmerClass.isKmerEqual(badtestKmer2));
}

//======================================================================
TEST_F(TestKmerClass, convertPosToReadID)
{
    TEST_DESCRIPTION("see if a kmer class has a specific QIdT ");
    ft::KmerClass testKmerClass("AAAA");

    EXPECT_EQ(testKmer.getKmer(), "AAAA")
}

//======================================================================
TEST_F(TestKmerClass, testOverloadOperator)
{
    TEST_DESCRIPTION("check the overload operator ");

    ft::KmerClass testKmer("AAAA");
    EXPECT_EQ(testKmer.getKmer(), "AAAA")
}

}
