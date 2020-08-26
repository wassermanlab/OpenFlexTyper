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
    std::set<std::string> kmerSet = {"AAAA","CCCC"};
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
    ft::QIdT query1 = std::make_pair(1, ft::QueryType::REF);
    ft::QIdT query2 = std::make_pair(1, ft::QueryType::ALT);
    ft::QIdT query3 = std::make_pair(2, ft::QueryType::REF);
    ft::QIdT query4 = std::make_pair(2, ft::QueryType::ALT);

    std::string kmer1 ="AAAA";
    std::string kmer2 = "CCCC";
    std::string kmer3 = "GGGG";
    std::string kmer4 = "TTTT";
    _qkMap._map[query1] = {kmer1, kmer2};
    _qkMap._map[query2] = {kmer2, kmer3};
    _qkMap._map[query3] = {kmer1, kmer3};
    _qkMap._map[query4] = {kmer4};
    set<ft::QIdT> expectedQueries1 = {query1, query3};
    set<ft::QIdT> expectedQueries2 = {query1, query2};
    set<ft::QIdT> expectedQueries3 = {query2, query3};
    set<ft::QIdT> expectedQueries4 = {query4};

    EXPECT_EQ(expectedQueries1, _qkMap.retrieveQueries(kmer1));
    EXPECT_EQ(expectedQueries2, _qkMap.retrieveQueries(kmer2));
    EXPECT_EQ(expectedQueries3, _qkMap.retrieveQueries(kmer3));
    EXPECT_EQ(expectedQueries4, _qkMap.retrieveQueries(kmer4));

}
//======================================================================
TEST_F(TestQKMap, TestRetrieveKmers)
{
    TEST_DESCRIPTION("retrieve Kmers");
    //std::set<ft::KmerClass*> retrieveKmers(ft::QueryClass *query);

    ft::QKMap _qkMap;
    ft::QIdT query1 = std::make_pair(1, ft::QueryType::REF);
    ft::QIdT query2 = std::make_pair(1, ft::QueryType::ALT);
    ft::QIdT query3 = std::make_pair(2, ft::QueryType::REF);
    ft::QIdT query4 = std::make_pair(2, ft::QueryType::ALT);

    std::string kmer1 ="AAAA";
    std::string kmer2 = "CCCC";
    std::string kmer3 = "GGGG";
    std::string kmer4 = "TTTT";
    _qkMap._map[query1] = {kmer1, kmer2};
    _qkMap._map[query2] = {kmer2, kmer3};
    _qkMap._map[query3] = {kmer1, kmer3};
    _qkMap._map[query4] = {kmer4};

    std::set<std::string> expectedKmers1 = {kmer1, kmer2};
    std::set<std::string> expectedKmers2 = {kmer2, kmer3};
    std::set<std::string> expectedKmers3 = {kmer1, kmer3};
    std::set<std::string> expectedKmers4 = {kmer4};

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

    ft::QIdT q1 = std::make_pair(1, ft::QueryType::REF);
    ft::QIdT q2 = std::make_pair(1, ft::QueryType::ALT);
    ft::QIdT q3 = std::make_pair(2, ft::QueryType::REF);
    ft::QueryClass* query1 = new ft::QueryClass(1, ft::QueryType::REF);
    ft::QueryClass* query2 = new ft::QueryClass(1, ft::QueryType::ALT);
    ft::QueryClass* query3 = new ft::QueryClass(2, ft::QueryType::REF);
    std::string k1 ="AAAA";
    std::string k2 = "CCCC";
    std::string k3 = "GGGG";
    ft::KmerClass* kmer1 = new ft::KmerClass("AAAA");
    ft::KmerClass* kmer2 = new ft::KmerClass("CCCC");
    ft::KmerClass* kmer3 = new ft::KmerClass("GGGG");
    std::set<std::string> kmerSet = {k1, k2};
    _qkMap._map[q1] = kmerSet;
    _qkMap._map[q2] = kmerSet;
    _qkMap._map[q3] = kmerSet;

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

    ft::QIdT q1 = std::make_pair(1, ft::QueryType::REF);
    ft::QIdT q2 = std::make_pair(1, ft::QueryType::ALT);
    ft::QIdT q3 = std::make_pair(2, ft::QueryType::REF);
    ft::QueryClass* query1 = new ft::QueryClass(1, ft::QueryType::REF);
    ft::QueryClass* query2 = new ft::QueryClass(1, ft::QueryType::ALT);
    ft::QueryClass* query3 = new ft::QueryClass(2, ft::QueryType::REF);
    std::string k1 ="AAAA";
    std::string k2 = "CCCC";
    std::string k3 = "GGGG";
    ft::KmerClass* kmer1 = new ft::KmerClass("AAAA");
    ft::KmerClass* kmer2 = new ft::KmerClass("CCCC");
    ft::KmerClass* kmer3 = new ft::KmerClass("GGGG");

    _qkMap.addQKPair(q1, k1);
    _qkMap.addQKPair(q1, k2);
    _qkMap.addQKPair(q2, k2);
    _qkMap.addQKPair(q3, k3);

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
TEST_F(TestQKMap, TestAddQKSet_ExistingQKPair)
{
    TEST_DESCRIPTION("Add QKPair that already exists");
    ft::QKMap _qkMap;
    ft::QueryClass* query1 = new ft::QueryClass(1, ft::QueryType::REF);
    ft::KmerClass* kmer1 = new ft::KmerClass("AAAA");
    ft::KmerClass* kmer2 = new ft::KmerClass("CCCC");
    ft::KmerClass* kmer3 = new ft::KmerClass("GGGG");
    _qkMap.addQKPair(query1->getQIdT(), kmer1->getKmer());
    _qkMap.addQKPair(query1->getQIdT(), kmer2->getKmer());

    EXPECT_TRUE(_qkMap.checkForMatch(*query1, *kmer1));
    EXPECT_TRUE(_qkMap.checkForMatch(*query1, *kmer2));
    EXPECT_FALSE(_qkMap.checkForMatch(*query1, *kmer3));
    EXPECT_EQ(2, _qkMap.retrieveKmers(query1->getQIdT()).size());

    //There should be no change as the QKPair already exists in the Map
    _qkMap.addQKPair(query1->getQIdT(), kmer1->getKmer());

    EXPECT_TRUE(_qkMap.checkForMatch(*query1, *kmer1));
    EXPECT_TRUE(_qkMap.checkForMatch(*query1, *kmer2));
    EXPECT_FALSE(_qkMap.checkForMatch(*query1, *kmer3));
    EXPECT_EQ(2, _qkMap.retrieveKmers(query1->getQIdT()).size());

}



}
