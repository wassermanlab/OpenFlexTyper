#include <gtest/gtest.h>
#include <climits>
#include "kmerClass.cpp"

using namespace std;

namespace ft {
class TestKmerClass : public ::testing::Test {
protected:
    virtual void SetUp() {

    }

    virtual void TearDown() {
    }

public:

};

#define TEST_DESCRIPTION(desc) RecordProperty("description", desc)

//======================================================================
TEST_F(TestKmerClass, getKmer)
{
    TEST_DESCRIPTION("get Kmer string");
    std::string kmer = "AAAA";
    ft::KmerClass testKmerClass(kmer);
    std::string resultkmer = testKmerClass.getKmer();
    EXPECT_EQ(resultkmer, kmer);


}


//======================================================================
TEST_F(TestKmerClass, KFlag)
{
    TEST_DESCRIPTION("Add single flag to kmer class");
    ft::KmerClass* testKmerClass = new ft::KmerClass("AAAA");

    testKmerClass->setKFlags({FlagType::NUK});
    EXPECT_TRUE(testKmerClass->hasFlag(FlagType::NUK));
    EXPECT_FALSE(testKmerClass->hasFlag(FlagType::OCK));

    testKmerClass->addKFlag(FlagType::OCK);
    EXPECT_TRUE(testKmerClass->hasFlag(FlagType::OCK));
    EXPECT_FALSE(testKmerClass->hasFlag(FlagType::ABK));

    testKmerClass->removeKFlag(FlagType::NUK);
    EXPECT_FALSE(testKmerClass->hasFlag(FlagType::NUK));
    EXPECT_TRUE(testKmerClass->hasFlag(FlagType::OCK));

}

//======================================================================
TEST_F(TestKmerClass, KPosition)
{
    TEST_DESCRIPTION("Add single position to kmer class");
    ft::KmerClass* testKmerClass = new ft::KmerClass("AAAA");

    testKmerClass->setKPositions({1000, 2340});
    EXPECT_TRUE(testKmerClass->hasKPosition(1000));
    EXPECT_FALSE(testKmerClass->hasKPosition(666));

    testKmerClass->addKPosition(666);
    EXPECT_TRUE(testKmerClass->hasKPosition(666));
    EXPECT_FALSE(testKmerClass->hasKPosition(924357));

    testKmerClass->removeKPosition(2340);
    EXPECT_FALSE(testKmerClass->hasKPosition(2340));
    EXPECT_TRUE(testKmerClass->hasKPosition(1000));
    EXPECT_TRUE(testKmerClass->hasKPosition(666));
}

//======================================================================
TEST_F(TestKmerClass,  ReadID)
{
    TEST_DESCRIPTION("add and remove single Read ID");
    ft::KmerClass* testKmerClass = new ft::KmerClass("AAAA");

    testKmerClass->setReadIDs({1000, 2340});
    EXPECT_TRUE(testKmerClass->hasReadID(1000));
    EXPECT_FALSE(testKmerClass->hasReadID(666));

    testKmerClass->addReadID(666);
    EXPECT_TRUE(testKmerClass->hasReadID(666));
    EXPECT_FALSE(testKmerClass->hasReadID(924357));

    testKmerClass->removeReadID(2340);
    EXPECT_FALSE(testKmerClass->hasReadID(2340));
    EXPECT_TRUE(testKmerClass->hasReadID(1000));
    EXPECT_TRUE(testKmerClass->hasReadID(666));

}

//======================================================================
TEST_F(TestKmerClass, hasKmer)
{
    TEST_DESCRIPTION("see if a kmer class has the same kmer ");

    ft::KmerClass* testKmerClass = new ft::KmerClass("AAAA");

    EXPECT_TRUE(testKmerClass->hasKmer("AAAA"));
    EXPECT_FALSE(testKmerClass->hasKmer("AAA"));
    EXPECT_FALSE(testKmerClass->hasKmer("TTTT"));
}

//======================================================================
TEST_F(TestKmerClass, isKmerEqual)
{
    TEST_DESCRIPTION("see if a kmer class has a specific kmer");
    ft::KmerClass* goodTestKmer = new ft::KmerClass("AAAA");
    ft::KmerClass* badTestKmer = new ft::KmerClass("AAA");
    ft::KmerClass* badTestKmer2 = new ft::KmerClass("TTTT");
    ft::KmerClass* testKmerClass = new ft::KmerClass("AAAA");


    EXPECT_TRUE(testKmerClass->isKmerEqual(*goodTestKmer));
    EXPECT_FALSE(testKmerClass->isKmerEqual(*badTestKmer));
    EXPECT_FALSE(testKmerClass->isKmerEqual(*badTestKmer2));
}

//======================================================================
TEST_F(TestKmerClass,  convertPosToReadIDNoOffset)
{
    TEST_DESCRIPTION("see if a kmer class has a specific QIdT ");
    ft::KmerClass* testKmerClass = new ft::KmerClass("AAAA");
    testKmerClass->setKPositions({100, 200, 251});
    testKmerClass->convertPosToReadID(100);
    std::set<int> expectedReadIDs = {1, 2};

    EXPECT_EQ(expectedReadIDs, testKmerClass->getReadIDs());
}

//======================================================================
TEST_F(TestKmerClass, DISABLED_convertPosToReadIDWithOffset)
{
    TEST_DESCRIPTION("see if a kmer class has a specific QIdT ");
    ft::KmerClass testKmerClass("AAAA");
    testKmerClass.setKPositions({100, 200, 251}, 10);
    testKmerClass.convertPosToReadID(100);
    std::set<int> expectedReadIDs = {1, 2};

    EXPECT_EQ(expectedReadIDs, testKmerClass.getReadIDs());
}


//======================================================================
TEST_F(TestKmerClass, testOverloadOperator)
{
    TEST_DESCRIPTION("check the overload operator ");
    ft::KmerClass* testKmerClass = new ft::KmerClass("AATT");
    ft::KmerClass* higherKmerClass = new ft::KmerClass("ATTT");
    ft::KmerClass* equalKmerClass = new ft::KmerClass("AATT");
    ft::KmerClass* lowerKmerClass = new ft::KmerClass("AAAA");


}

}
