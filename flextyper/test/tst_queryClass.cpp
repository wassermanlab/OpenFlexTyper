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
TEST_F(TestQueryClass, getQFlags)
{
    TEST_DESCRIPTION("get QFlags");
    //std::map<ft::FlagType, std::set<std::string>> getQFlags() const;
}
//======================================================================
TEST_F(TestQueryClass, getQIdT)
{
    TEST_DESCRIPTION("get QIdT");
    //ft::QIdT getQIdT() const;
    ft::QueryClass testQuery(1, ft::QueryType::REF);
    EXPECT_EQ(1, testQuery.getQIdT().first);
    EXPECT_EQ(ft::QueryType::REF, testQuery.getQIdT().second);

}
//======================================================================
TEST_F(TestQueryClass, getFlagKmers)
{
    TEST_DESCRIPTION("get Flag Kmers ");
    //const std::set<std::string> getFlagKmers(const ft::FlagType flag) const;
    ft::QueryClass* testQuery = new ft::QueryClass(1, ft::QueryType::REF);
    testQuery->_qFlags[FlagType::NUK]={"AAAA", "AATT"};
    std::set<std::string> expected = {"AAAA", "AATT"};
    std::set<std::string> output = testQuery->getFlagKmers(FlagType::NUK);
    std::set<std::string> output2 = testQuery->getFlagKmers(FlagType::OCK);
    std::set<std::string> expected2 = {};
    EXPECT_EQ(expected, output);
    EXPECT_EQ(output2, expected2);

}
//======================================================================
TEST_F(TestQueryClass, setFlags)
{
    TEST_DESCRIPTION("set Flags");
    //void setFlags(const std::map<ft::FlagType, std::set<std::string>>& qFlags);
    ft::QueryClass* testQuery = new ft::QueryClass(1, ft::QueryType::REF);
    std::map<ft::FlagType, std::set<std::string>> flags;
    flags[FlagType::NUK]={"AAAA", "AATT"};
    std::set<std::string> expected = {"AAAA", "AATT"};
    testQuery->setFlags(flags);
    EXPECT_TRUE(testQuery->hasFlag(FlagType::NUK));
    EXPECT_FALSE(testQuery->hasFlag(FlagType::OCK));
    EXPECT_EQ(testQuery->getFlagKmers(FlagType::NUK),expected);

}

//======================================================================
TEST_F(TestQueryClass, addFlag)
{
    TEST_DESCRIPTION("add Flag ");
    //void addFlag(const ft::FlagType& flagType, const std::string& kmers);
    ft::QueryClass* testQuery = new ft::QueryClass(1, ft::QueryType::REF);
    std::string kmer = "AAAA";
    testQuery->addFlag(FlagType::NUK, kmer);
    EXPECT_EQ(1, testQuery->_qFlags.size());
    EXPECT_TRUE(testQuery->hasKmerFlag(FlagType::NUK, kmer));

}
//======================================================================
TEST_F(TestQueryClass, removeFlag)
{
    TEST_DESCRIPTION("remove Flag");
    //void removeFlag(ft::FlagType flagType);
    ft::QueryClass* testQuery = new ft::QueryClass(1, ft::QueryType::REF);
    testQuery->_qFlags[FlagType::NUK] = {"AAAA", "CCCC"};
    testQuery->_qFlags[FlagType::OCK] = {"AAAA", "CCCC"};
    EXPECT_EQ(2, testQuery->_qFlags.size());
    EXPECT_TRUE(testQuery->hasFlag(FlagType::NUK));
    EXPECT_TRUE(testQuery->hasFlag(FlagType::OCK));

    testQuery->removeFlag(FlagType::OCK);
    EXPECT_EQ(1, testQuery->_qFlags.size());
    EXPECT_TRUE(testQuery->hasFlag(FlagType::NUK));
    EXPECT_FALSE(testQuery->hasFlag(FlagType::OCK));
    testQuery->removeFlag(FlagType::NUK);
    EXPECT_EQ(0, testQuery->_qFlags.size());
    EXPECT_FALSE(testQuery->hasFlag(FlagType::NUK));
    EXPECT_FALSE(testQuery->hasFlag(FlagType::OCK));

}
//======================================================================
TEST_F(TestQueryClass, removeKmerFlag)
{
    TEST_DESCRIPTION("remove Kmer Flag ");
    //void removeKmerFlag(const ft::FlagType& flagTyper, const std::string& kmers);
    ft::QueryClass* testQuery = new ft::QueryClass(1, ft::QueryType::REF);
    testQuery->_qFlags[FlagType::NUK] = {"AAAA", "CCCC"};
    testQuery->_qFlags[FlagType::OCK] = {"AAAA", "CCCC"};
    EXPECT_EQ(2, testQuery->_qFlags[FlagType::NUK].size());
    EXPECT_EQ(2, testQuery->_qFlags[FlagType::OCK].size());
    EXPECT_TRUE(testQuery->hasFlag(FlagType::NUK));
    EXPECT_TRUE(testQuery->hasFlag(FlagType::OCK));

    testQuery->removeKmerFlag(FlagType::OCK, "CCCC");
    EXPECT_EQ(2, testQuery->_qFlags[FlagType::NUK].size());
    EXPECT_EQ(1, testQuery->_qFlags[FlagType::OCK].size());
    EXPECT_TRUE(testQuery->hasKmerFlag(FlagType::NUK, "AAAA"));
    EXPECT_FALSE(testQuery->hasKmerFlag(FlagType::OCK, "CCCC"));

}
//======================================================================
TEST_F(TestQueryClass, removeCount)
{
    TEST_DESCRIPTION("remove Count");
    //void removeCount();
    ft::QueryClass* testQuery = new ft::QueryClass(1, ft::QueryType::REF);
    testQuery->setCount(20);
    EXPECT_EQ(20, testQuery->_count);
    testQuery->removeCount();
    EXPECT_EQ(0, testQuery->_count);

}
//======================================================================
TEST_F(TestQueryClass, isQIdTEqual)
{
    TEST_DESCRIPTION("is QIdT Equal");
    //bool isQIdTEqual(const ft::QIdT& test) const;
    ft::QueryClass* testQuery = new ft::QueryClass(1, ft::QueryType::REF);
    ft::QIdT trueqidt = std::make_pair(1, ft::QueryType::REF);
    ft::QIdT falseqidt1 = std::make_pair(1, ft::QueryType::ALT);
    ft::QIdT falseqidt2 = std::make_pair(2, ft::QueryType::REF);

    EXPECT_TRUE(testQuery->isQIdTEqual(trueqidt));
    EXPECT_FALSE(testQuery->isQIdTEqual(falseqidt1));
    EXPECT_FALSE(testQuery->isQIdTEqual(falseqidt2));

}
//======================================================================
TEST_F(TestQueryClass, hasQueryID)
{
    TEST_DESCRIPTION("has Query ID ");
    //bool hasQueryID(const int& qid) const;
    ft::QueryClass* testQuery = new ft::QueryClass(1, ft::QueryType::REF);
    EXPECT_TRUE(testQuery->hasQueryID(1));
    EXPECT_FALSE(testQuery->hasQueryID(2));

}
//======================================================================
TEST_F(TestQueryClass, hasQueryType)
{
    TEST_DESCRIPTION("has Query Type");
    //bool hasQueryType(const ft::QueryType& qType) const;

    ft::QueryClass* testQuery = new ft::QueryClass(1, ft::QueryType::REF);
    EXPECT_TRUE(testQuery->hasQueryType(ft::QueryType::REF));
    EXPECT_FALSE(testQuery->hasQueryType(ft::QueryType::ALT));

}
//======================================================================
TEST_F(TestQueryClass, hasKmerFlag)
{
    TEST_DESCRIPTION("has Kme rFlag");
    //bool hasKmerFlag(const ft::FlagType& flag, const std::string& kmer) const;
    ft::QueryClass* testQuery = new ft::QueryClass(1, ft::QueryType::REF);
    testQuery->_qFlags[FlagType::NUK] = {"AAAA", "CCCC"};

    EXPECT_TRUE(testQuery->hasKmerFlag(ft::FlagType::NUK, "AAAA"));
    EXPECT_TRUE(testQuery->hasKmerFlag(ft::FlagType::NUK, "CCCC"));
    EXPECT_FALSE(testQuery->hasKmerFlag(ft::FlagType::OCK, "AAAA")); //wrong flag type
    EXPECT_FALSE(testQuery->hasKmerFlag(ft::FlagType::NUK, "TTTT")); //kmer doesnt exist

}
//======================================================================
TEST_F(TestQueryClass, hasNonZeroCount)
{
    TEST_DESCRIPTION("has Non Zero Count ");
    //bool hasNonZeroCount() const;
    ft::QueryClass* testQuery = new ft::QueryClass(1, ft::QueryType::REF);
    testQuery->_count =32;
    EXPECT_TRUE(testQuery->hasNonZeroCount());

}
//======================================================================
TEST_F(TestQueryClass, OverloadOperators)
{
    TEST_DESCRIPTION("Test the overload operators ");

    ft::QueryClass* testQuery2Ref = new ft::QueryClass(2, ft::QueryType::REF);
    ft::QueryClass* testQuery1Ref = new ft::QueryClass(1, ft::QueryType::REF);
    ft::QueryClass* testQuery1Alt = new ft::QueryClass(1, ft::QueryType::ALT);
    EXPECT_TRUE(*testQuery1Alt < *testQuery2Ref);
    EXPECT_TRUE(*testQuery1Ref < *testQuery1Alt);
    EXPECT_TRUE(*testQuery2Ref == *testQuery2Ref);
    EXPECT_FALSE(*testQuery1Ref == *testQuery1Alt);
    EXPECT_FALSE(*testQuery2Ref < *testQuery1Alt);

}


}
