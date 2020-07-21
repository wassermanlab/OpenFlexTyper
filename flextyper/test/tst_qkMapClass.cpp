#include <gtest/gtest.h>

#include "qkMapClass.cpp"

#include <fstream>
#include <climits>

using namespace std;

namespace ft {
class TestQKMap : public ::testing::Test {

protected:
    virtual void SetUp() {}
    virtual void TearDown() {}

public:

};


#define TEST_DESCRIPTION(desc) RecordProperty("description", desc)

//======================================================================
TEST_F(TestQKMap, TestCheckForQuery)
{
    TEST_DESCRIPTION("check For Query");
    //bool checkForQuery(const ft::QueryClass& query) const;
    ft::QKMap _qkMap;
    ft::QueryClass* trueQuery = new ft::QueryClass(1, ft::QueryType::REF);
    ft::QueryClass* falseQuery = new ft::QueryClass(1, ft::QueryType::ALT);
    ft::QueryClass* trueQuery2 = new ft::QueryClass(2, ft::QueryType::ALT);
    ft::QueryClass* falseQuery2 = new ft::QueryClass(2, ft::QueryType::REF);
    std::set<KmerClass*> kmerSet = {new ft::KmerClass("AAAA"), new ft::KmerClass("CCCC")};
    _qkMap._map[trueQuery] = kmerSet;
    _qkMap._map[trueQuery2] = kmerSet;

    EXPECT_TRUE(_qkMap.checkForQuery(*trueQuery));
    EXPECT_TRUE(_qkMap.checkForQuery(*trueQuery2));
    EXPECT_FALSE(_qkMap.checkForQuery(*falseQuery));
    EXPECT_FALSE(_qkMap.checkForQuery(*falseQuery2));

}
//======================================================================
TEST_F(TestQKMap, TestGetQueryPointer)
{
    TEST_DESCRIPTION("get Query Pointer");
    //ft::QueryClass* getQueryPointer(const ft::QueryClass& query);


}
//======================================================================
TEST_F(TestQKMap, TestRetrieveQueries)
{
    TEST_DESCRIPTION("retrieve Queries");
    //std::set<ft::QueryClass*> retrieveQueries(const ft::KmerClass& kmer);




}
//======================================================================
TEST_F(TestQKMap, TestRetrieveKmers)
{
    TEST_DESCRIPTION("retrieve Kmers");
    //std::set<ft::KmerClass*> retrieveKmers(ft::QueryClass *query);

}
//======================================================================
TEST_F(TestQKMap, TestCheckForMatch)
{
    TEST_DESCRIPTION("check For Match ");
    //bool checkForMatch(const ft::QueryClass& query, const ft::KmerClass &kmer) const;
    ft::QKMap _qkMap;

    ft::QueryClass* query = new ft::QueryClass(1, ft::QueryType::REF);
    ft::QueryClass* query2 = new ft::QueryClass(1, ft::QueryType::ALT);
    ft::QueryClass* query3 = new ft::QueryClass(2, ft::QueryType::REF);
    ft::KmerClass* kmer = new ft::KmerClass("AAAA");
    ft::KmerClass* kmer2 = new ft::KmerClass("CCCC");
    ft::KmerClass* kmer3 = new ft::KmerClass("GGGG");
    std::set<KmerClass*> kmerSet = {kmer, kmer2};
    _qkMap._map[query] = kmerSet;
    _qkMap._map[query2] = kmerSet;
    _qkMap._map[query3] = kmerSet;

    EXPECT_TRUE(_qkMap.checkForMatch(*query, *kmer));
    EXPECT_TRUE(_qkMap.checkForMatch(*query, *kmer2));
    EXPECT_FALSE(_qkMap.checkForMatch(*query, *kmer3));
    EXPECT_TRUE(_qkMap.checkForMatch(*query2, *kmer));
    EXPECT_TRUE(_qkMap.checkForMatch(*query2, *kmer2));
    EXPECT_FALSE(_qkMap.checkForMatch(*query2, *kmer3));
    EXPECT_TRUE(_qkMap.checkForMatch(*query3, *kmer));
    EXPECT_TRUE(_qkMap.checkForMatch(*query3, *kmer2));
    EXPECT_FALSE(_qkMap.checkForMatch(*query3, *kmer3));

}
//======================================================================
TEST_F(TestQKMap, TestAddQKPair)
{
    TEST_DESCRIPTION("add QKPair");
    //void addQKPair(ft::QueryClass* query, ft::KmerClass* kmer);

}
//======================================================================
TEST_F(TestQKMap, TestAddQKSet)
{
    TEST_DESCRIPTION("Add QKSet");
    //void addQKSet(ft::QueryClass* query, std::set<ft::KmerClass*> kmers);

}



}
