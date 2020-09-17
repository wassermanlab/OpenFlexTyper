#include <gtest/gtest.h>
#include <climits>
#include "kmerClass.cpp"

using namespace std;

namespace ft {
class TestKmerClass : public ::testing::Test {
protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
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

    std::cout << "no flags" << std::endl;
    EXPECT_FALSE(testKmerClass->hasFlag(FlagType::NUK));
    EXPECT_FALSE(testKmerClass->hasFlag(FlagType::OCK));

    std::cout << "set NUK flag" << std::endl;
    testKmerClass->setKFlags({FlagType::NUK});
    EXPECT_TRUE(testKmerClass->hasFlag(FlagType::NUK));
    EXPECT_FALSE(testKmerClass->hasFlag(FlagType::OCK));

    std::cout << "add Flag" << std::endl;
    testKmerClass->addKFlag(FlagType::OCK);
    EXPECT_TRUE(testKmerClass->hasFlag(FlagType::OCK));
    EXPECT_FALSE(testKmerClass->hasFlag(FlagType::ABK));

    std::cout << "remove flag" << std::endl;
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
    ft::ReadID read1 = {1000, 1};
    ft::ReadID read2 = {2340, 1};
    ft::ReadID read3 = {666, 1};
    ft::ReadID read4 = {924357, 1};

    testKmerClass->setReadIDs({read1, read2});
    EXPECT_TRUE(testKmerClass->hasReadID(read1));
    EXPECT_FALSE(testKmerClass->hasReadID(read3));

    testKmerClass->addReadID(read3);
    EXPECT_TRUE(testKmerClass->hasReadID(read3));
    EXPECT_FALSE(testKmerClass->hasReadID(read4));

    testKmerClass->removeReadID(read2);
    EXPECT_FALSE(testKmerClass->hasReadID(read2));
    EXPECT_TRUE(testKmerClass->hasReadID(read1));
    EXPECT_TRUE(testKmerClass->hasReadID(read3));

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
TEST_F(TestKmerClass, convertPosToRead_NotPaired_NotReverseComp)
{
    TEST_DESCRIPTION("convert index positions to read ids ");

    ft::KmerClass* testKmerClass = new ft::KmerClass("AAAA");
    testKmerClass->setKPositions({50, 125, 251, 313, 449, 555, 654, 723});
    testKmerClass->convertPosToReadID(100,8,false, false);
    std::set<ft::ReadID> expectedReadIDs = {{1,1}, {2,1}, {3, 1}, {4, 1}, {5, 1}, {6, 1}, {7, 1}, {8, 1}};

    EXPECT_EQ(expectedReadIDs, testKmerClass->getReadIDs());
}
//======================================================================
TEST_F(TestKmerClass, sdotest)
{
    TEST_DESCRIPTION("convert index positions to read ids ");

    std::map<std::string, ft::KmerClass> indexResults;
    ft::KmerClass tmpResult = ft::KmerClass("AAAA");
    const std::string& resultkmer = tmpResult.getKmer();
    indexResults[resultkmer] = tmpResult;
    ft::KmerClass result = indexResults.find(resultkmer)->second;
    result.setKPositions({50, 125, 251, 313, 449, 555, 654, 723});
    indexResults.find(resultkmer)->second = result;
    ft::KmerClass result2 = indexResults.find(resultkmer)->second;
        for (long long pos : {50, 125, 251, 313, 449, 555, 654, 723})
        {
            //result.addKPosition(pos, offset);
            bool rc2 = result2.hasKPosition(pos);
            bool rc = result.hasKPosition(pos);
            //if(rc != rc2) {
                std::cout << "failed pos " << pos << " result " << rc << " result2 " << rc2 << std::endl;
            //}
        }
     std::cout << "sdotest done " << std::endl;
}

//======================================================================
TEST_F(TestKmerClass, convertPosToReadDirect)
{
    TEST_DESCRIPTION("convert index positions to read ids ");
    ft::KmerClass testKmerClass("AAAA");
    testKmerClass.setKPositions({50, 125, 251, 313, 449, 555, 654, 723});
    testKmerClass.convertPosToReadID(100,8,false,false);
    std::set<ft::ReadID> expectedReadIDs = {{1,1}, {2,1}, {3, 1}, {4, 1}, {5, 1}, {6, 1}, {7, 1}, {8, 1}};

    EXPECT_EQ(expectedReadIDs, testKmerClass.getReadIDs());
}


//======================================================================
TEST_F(TestKmerClass, convertPosToRead_Paired_NotReverseComp)
{
    TEST_DESCRIPTION("convert index positions to read ids ");
    ft::KmerClass* testKmerClass = new ft::KmerClass("AAAA");
    testKmerClass->setKPositions({50, 125, 251, 313, 449, 555, 654, 723});
    testKmerClass->convertPosToReadID(100,8,true,false);
    std::set<ft::ReadID> expectedReadIDs = {{1,1}, {2,1}, {3, 1}, {4, 1}, {1,2}, {2,2}, {3, 2}, {4, 2}};

    EXPECT_EQ(expectedReadIDs, testKmerClass->getReadIDs());
}
//======================================================================
TEST_F(TestKmerClass, convertPosToRead_NotPaired_ReverseComp)
{
    TEST_DESCRIPTION("convert index positions to read ids ");
    ft::KmerClass* testKmerClass = new ft::KmerClass("AAAA");
    testKmerClass->setKPositions({50, 125, 251, 313, 449, 555, 654, 723});
    testKmerClass->convertPosToReadID(100,4,false,true);
    std::set<ft::ReadID> expectedReadIDs = {{1,1}, {2,1}, {3, 1}, {4, 1}};

    EXPECT_EQ(expectedReadIDs, testKmerClass->getReadIDs());
}
//======================================================================
TEST_F(TestKmerClass, convertPosToRead_Paired_ReverseComp)
{
    TEST_DESCRIPTION("convert index positions to read ids ");
    ft::KmerClass* testKmerClass = new ft::KmerClass("AAAA");
    testKmerClass->setKPositions({50, 125, 251, 313, 449, 555, 654, 723});
    testKmerClass->convertPosToReadID(100,4, true,true);
    std::set<ft::ReadID> expectedReadIDs = {{1,1}, {2,1}, {1,2}, {2,2}};

    EXPECT_EQ(expectedReadIDs, testKmerClass->getReadIDs());
}
//======================================================================
TEST_F(TestKmerClass, matchingReadID)
{
    TEST_DESCRIPTION("check if readids match ");
    ft::KmerClass* testKmerClass = new ft::KmerClass("AAAA");
    ft::ReadID a = {1,1};
    ft::ReadID b = {1,2};
    ft::ReadID c = {2,1};
    ft::ReadID d = {2,2};
    ft::ReadID e = {1,1};
    EXPECT_TRUE(testKmerClass->matchingReadID(a,e));
    EXPECT_FALSE(testKmerClass->matchingReadID(a,b));
    EXPECT_FALSE(testKmerClass->matchingReadID(a,c));
    EXPECT_FALSE(testKmerClass->matchingReadID(a,d));

}

//======================================================================
TEST_F(TestKmerClass, hasReadID)
{
    TEST_DESCRIPTION("check if Kmer has ReadID ");
    ft::KmerClass* testKmerClass = new ft::KmerClass("AAAA");
    ft::ReadID a = {1,1};
    ft::ReadID b = {1,2};
    ft::ReadID c = {2,1};
    ft::ReadID d = {1,3};
    ft::ReadID e = {3,1};
    ft::ReadID f = {3,3};
    std::set<ft::ReadID> readIDs = {{1,1}, {2,1}, {1,2}, {2,2}};
    testKmerClass->setReadIDs(readIDs);
    EXPECT_TRUE(testKmerClass->hasReadID(a));
    EXPECT_TRUE(testKmerClass->hasReadID(b));
    EXPECT_TRUE(testKmerClass->hasReadID(c));

    EXPECT_FALSE(testKmerClass->hasReadID(d));
    EXPECT_FALSE(testKmerClass->hasReadID(e));
    EXPECT_FALSE(testKmerClass->hasReadID(f));

}
//======================================================================
TEST_F(TestKmerClass, testOverloadOperator)
{
    TEST_DESCRIPTION("check the overload operator ");
    ft::KmerClass* higherKmerClass = new ft::KmerClass("ATTT");
    ft::KmerClass* equalKmerClass = new ft::KmerClass("AATT");
    ft::KmerClass* testKmerClass = new ft::KmerClass("AATT");
    ft::KmerClass* lowerKmerClass = new ft::KmerClass("AAAA");
    EXPECT_TRUE(*lowerKmerClass < *testKmerClass);
    EXPECT_TRUE(*testKmerClass < *higherKmerClass);
    EXPECT_TRUE(*equalKmerClass == *testKmerClass);

}

}
