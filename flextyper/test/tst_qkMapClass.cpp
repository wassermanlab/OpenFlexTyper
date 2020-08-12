#include <gtest/gtest.h>

#include "qkMapClass.cpp"
#include <set>
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
    std::set<ft::Kmer> kmerSet = {"AAAA","CCCC"};
    _qkMap._map[trueQuery->getQIdT()] = kmerSet;
    _qkMap._map[trueQuery2->getQIdT()] = kmerSet;

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

    ft::QKMap _qkMap;
    ft::QueryClass* query1 = new ft::QueryClass(1, ft::QueryType::REF);
    ft::QueryClass* query2 = new ft::QueryClass(1, ft::QueryType::ALT);
    ft::QueryClass* query3 = new ft::QueryClass(2, ft::QueryType::REF);
    ft::QueryClass* query4 = new ft::QueryClass(2, ft::QueryType::ALT);

    ft::KmerClass* kmer1 = new ft::KmerClass("AAAA");
    ft::KmerClass* kmer2 = new ft::KmerClass("CCCC");
    ft::KmerClass* kmer3 = new ft::KmerClass("GGGG");
    ft::KmerClass* kmer4 = new ft::KmerClass("TTTT");
    _qkMap._map[query1] = {kmer1, kmer2};
    _qkMap._map[query2] = {kmer2, kmer3};
    _qkMap._map[query3] = {kmer1, kmer3};
    _qkMap._map[query4] = {kmer4};
    set<ft::QueryClass*> expectedQueries1 = {query1, query3};
    set<ft::QueryClass*> expectedQueries2 = {query1, query2};
    set<ft::QueryClass*> expectedQueries3 = {query2, query3};
    set<ft::QueryClass*> expectedQueries4 = {query4};

    EXPECT_EQ(expectedQueries1, _qkMap.retrieveQueries(*kmer1));
    EXPECT_EQ(expectedQueries2, _qkMap.retrieveQueries(*kmer2));
    EXPECT_EQ(expectedQueries3, _qkMap.retrieveQueries(*kmer3));
    EXPECT_EQ(expectedQueries4, _qkMap.retrieveQueries(*kmer4));

}
//======================================================================
TEST_F(TestQKMap, TestRetrieveKmers)
{
    TEST_DESCRIPTION("retrieve Kmers");
    //std::set<ft::KmerClass*> retrieveKmers(ft::QueryClass *query);

    ft::QKMap _qkMap;
    ft::QueryClass* query1 = new ft::QueryClass(1, ft::QueryType::REF);
    ft::QueryClass* query2 = new ft::QueryClass(1, ft::QueryType::ALT);
    ft::QueryClass* query3 = new ft::QueryClass(2, ft::QueryType::REF);
    ft::QueryClass* query4 = new ft::QueryClass(2, ft::QueryType::ALT);

    ft::KmerClass* kmer1 = new ft::KmerClass("AAAA");
    ft::KmerClass* kmer2 = new ft::KmerClass("CCCC");
    ft::KmerClass* kmer3 = new ft::KmerClass("GGGG");
    ft::KmerClass* kmer4 = new ft::KmerClass("TTTT");
    _qkMap._map[query1] = {kmer1, kmer2};
    _qkMap._map[query2] = {kmer2, kmer3};
    _qkMap._map[query3] = {kmer1, kmer3};
    _qkMap._map[query4] = {kmer4};

    std::set<ft::KmerClass*> expectedKmers1 = {kmer1, kmer2};
    std::set<ft::KmerClass*> expectedKmers2 = {kmer2, kmer3};
    std::set<ft::KmerClass*> expectedKmers3 = {kmer1, kmer3};
    std::set<ft::KmerClass*> expectedKmers4 = {kmer4};

    EXPECT_EQ(expectedKmers1, _qkMap.retrieveKmers(query1));
    EXPECT_EQ(expectedKmers2, _qkMap.retrieveKmers(query2));
    EXPECT_EQ(expectedKmers3, _qkMap.retrieveKmers(query3));
    EXPECT_EQ(expectedKmers4, _qkMap.retrieveKmers(query4));

}
//======================================================================
TEST_F(TestQKMap, TestCheckForMatch)
{
    TEST_DESCRIPTION("check For Match ");
    //bool checkForMatch(const ft::QueryClass& query, const ft::KmerClass &kmer) const;
    ft::QKMap _qkMap;

    ft::QueryClass* query1 = new ft::QueryClass(1, ft::QueryType::REF);
    ft::QueryClass* query2 = new ft::QueryClass(1, ft::QueryType::ALT);
    ft::QueryClass* query3 = new ft::QueryClass(2, ft::QueryType::REF);
    ft::KmerClass* kmer1 = new ft::KmerClass("AAAA");
    ft::KmerClass* kmer2 = new ft::KmerClass("CCCC");
    ft::KmerClass* kmer3 = new ft::KmerClass("GGGG");
    std::set<KmerClass*> kmerSet = {kmer1, kmer2};
    _qkMap._map[query1] = kmerSet;
    _qkMap._map[query2] = kmerSet;
    _qkMap._map[query3] = kmerSet;

    EXPECT_TRUE(_qkMap.checkForMatch(*query1, *kmer1));
    EXPECT_TRUE(_qkMap.checkForMatch(*query1, *kmer2));
    EXPECT_FALSE(_qkMap.checkForMatch(*query1, *kmer3));

    EXPECT_TRUE(_qkMap.checkForMatch(*query2, *kmer1));
    EXPECT_TRUE(_qkMap.checkForMatch(*query2, *kmer2));
    EXPECT_FALSE(_qkMap.checkForMatch(*query2, *kmer3));

    EXPECT_TRUE(_qkMap.checkForMatch(*query3, *kmer1));
    EXPECT_TRUE(_qkMap.checkForMatch(*query3, *kmer2));
    EXPECT_FALSE(_qkMap.checkForMatch(*query3, *kmer3));

}
//======================================================================
TEST_F(TestQKMap, TestAddQKPair)
{
    TEST_DESCRIPTION("add QKPair");
    //void addQKPair(ft::QueryClass* query, ft::KmerClass* kmer);

    ft::QKMap _qkMap;

    ft::QueryClass* query1 = new ft::QueryClass(1, ft::QueryType::REF);
    ft::QueryClass* query2 = new ft::QueryClass(1, ft::QueryType::ALT);
    ft::QueryClass* query3 = new ft::QueryClass(2, ft::QueryType::REF);
    ft::KmerClass* kmer1 = new ft::KmerClass("AAAA");
    ft::KmerClass* kmer2 = new ft::KmerClass("CCCC");
    ft::KmerClass* kmer3 = new ft::KmerClass("GGGG");

    _qkMap.addQKPair(query1, kmer1);
    _qkMap.addQKPair(query1, kmer2);
    _qkMap.addQKPair(query2, kmer2);
    _qkMap.addQKPair(query3, kmer3);

    EXPECT_TRUE(_qkMap.checkForMatch(*query1, *kmer1));
    EXPECT_TRUE(_qkMap.checkForMatch(*query1, *kmer2));
    EXPECT_FALSE(_qkMap.checkForMatch(*query1, *kmer3));

    EXPECT_FALSE(_qkMap.checkForMatch(*query2, *kmer1));
    EXPECT_TRUE(_qkMap.checkForMatch(*query2, *kmer2));
    EXPECT_FALSE(_qkMap.checkForMatch(*query2, *kmer3));

    EXPECT_FALSE(_qkMap.checkForMatch(*query3, *kmer1));
    EXPECT_FALSE(_qkMap.checkForMatch(*query3, *kmer2));
    EXPECT_TRUE(_qkMap.checkForMatch(*query3, *kmer3));



}
//======================================================================
TEST_F(TestQKMap, TestAddQKSet_empty)
{
    TEST_DESCRIPTION("Add QKSet with 0 element2");
    //void addQKSet(ft::QueryClass* query, std::set<ft::KmerClass*> kmers);

    ft::QKMap _qkMap;
    ft::QueryClass* query1 = new ft::QueryClass(1, ft::QueryType::REF);
    ft::KmerClass* kmer1 = new ft::KmerClass("AAAA");
    ft::KmerClass* kmer2 = new ft::KmerClass("CCCC");

    // add a set with 0 elements
    _qkMap.addQKSet(query1, {});
    EXPECT_FALSE(_qkMap.checkForMatch(*query1, *kmer1));
    EXPECT_FALSE(_qkMap.checkForMatch(*query1, *kmer2));
    EXPECT_EQ(0, _qkMap.retrieveKmers(query1).size());

}

//======================================================================
TEST_F(TestQKMap, TestAddQKSet_1)
{
    TEST_DESCRIPTION("Add QKSet with 1 element");
    //void addQKSet(ft::QueryClass* query, std::set<ft::KmerClass*> kmers);

    ft::QKMap _qkMap;
    ft::QueryClass* query1 = new ft::QueryClass(1, ft::QueryType::REF);
    ft::KmerClass* kmer1 = new ft::KmerClass("AAAA");
    ft::KmerClass* kmer2 = new ft::KmerClass("CCCC");

    // add a set with 1 element
    _qkMap.addQKSet(query1, {kmer1});
    EXPECT_TRUE(_qkMap.checkForMatch(*query1, *kmer1));
    EXPECT_FALSE(_qkMap.checkForMatch(*query1, *kmer2));
    EXPECT_EQ(1, _qkMap.retrieveKmers(query1).size());

}

//======================================================================
TEST_F(TestQKMap, TestAddQKSet_2)
{
    TEST_DESCRIPTION("Add QKSet with 1 element");
    //void addQKSet(ft::QueryClass* query, std::set<ft::KmerClass*> kmers);

    ft::QKMap _qkMap;
    ft::QueryClass* query1 = new ft::QueryClass(1, ft::QueryType::REF);
    ft::KmerClass* kmer1 = new ft::KmerClass("AAAA");
    ft::KmerClass* kmer2 = new ft::KmerClass("CCCC");
    ft::KmerClass* kmer3 = new ft::KmerClass("GGGG");

    // add a set with 2 elements
    _qkMap.addQKSet(query1, {kmer1, kmer2});
    EXPECT_TRUE(_qkMap.checkForMatch(*query1, *kmer1));
    EXPECT_TRUE(_qkMap.checkForMatch(*query1, *kmer2));
    EXPECT_FALSE(_qkMap.checkForMatch(*query1, *kmer3));

    EXPECT_EQ(2, _qkMap.retrieveKmers(query1).size());

}
//======================================================================
TEST_F(TestQKMap, TestAddQKSet_ExistingQuery)
{
    TEST_DESCRIPTION("Add QKSet with 2 elements");
    //void addQKSet(ft::QueryClass* query, std::set<ft::KmerClass*> kmers);
    ft::QKMap _qkMap;
    ft::QueryClass* query1 = new ft::QueryClass(1, ft::QueryType::REF);
    ft::KmerClass* kmer1 = new ft::KmerClass("AAAA");
    ft::KmerClass* kmer2 = new ft::KmerClass("CCCC");
    ft::KmerClass* kmer3 = new ft::KmerClass("GGGG");
    ft::KmerClass* kmer4 = new ft::KmerClass("TTTT");

    _qkMap.addQKPair(query1, kmer1);
    EXPECT_TRUE(_qkMap.checkForMatch(*query1, *kmer1));
    EXPECT_FALSE(_qkMap.checkForMatch(*query1, *kmer2));
    EXPECT_FALSE(_qkMap.checkForMatch(*query1, *kmer3));
    EXPECT_FALSE(_qkMap.checkForMatch(*query1, *kmer4));
    EXPECT_EQ(1, _qkMap.retrieveKmers(query1).size());

    _qkMap.addQKSet(query1, {kmer2, kmer3});
    EXPECT_TRUE(_qkMap.checkForMatch(*query1, *kmer1));
    EXPECT_TRUE(_qkMap.checkForMatch(*query1, *kmer2));
    EXPECT_TRUE(_qkMap.checkForMatch(*query1, *kmer3));
    EXPECT_FALSE(_qkMap.checkForMatch(*query1, *kmer4));
    EXPECT_EQ(3, _qkMap.retrieveKmers(query1).size());


}
//======================================================================
TEST_F(TestQKMap, TestAddQKSet_ExistingQKPair)
{
    TEST_DESCRIPTION("Add QKPair that already exists");
    ft::QKMap _qkMap;
    ft::QueryClass* query1 = new ft::QueryClass(1, ft::QueryType::REF);
    ft::KmerClass* kmer1 = new ft::KmerClass("AAAA");
    ft::KmerClass* kmer2 = new ft::KmerClass("CCCC");
    ft::KmerClass* kmer3 = new ft::KmerClass("GGGG");
    _qkMap.addQKSet(query1, {kmer1, kmer2});

    EXPECT_TRUE(_qkMap.checkForMatch(*query1, *kmer1));
    EXPECT_TRUE(_qkMap.checkForMatch(*query1, *kmer2));
    EXPECT_FALSE(_qkMap.checkForMatch(*query1, *kmer3));
    EXPECT_EQ(2, _qkMap.retrieveKmers(query1).size());

    //There should be no change as the QKPair already exists in the Map
    _qkMap.addQKPair(query1, kmer1);

    EXPECT_TRUE(_qkMap.checkForMatch(*query1, *kmer1));
    EXPECT_TRUE(_qkMap.checkForMatch(*query1, *kmer2));
    EXPECT_FALSE(_qkMap.checkForMatch(*query1, *kmer3));
    EXPECT_EQ(2, _qkMap.retrieveKmers(query1).size());

}



}
