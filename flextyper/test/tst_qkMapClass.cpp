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
    TEST_DESCRIPTION("Check Kmer");
    //bool checkForQuery(const ft::QueryClass& query) const;
}
//======================================================================
TEST_F(TestQKMap, TestGetQueryPointer)
{
    TEST_DESCRIPTION("Check Kmer");
    //ft::QueryClass* getQueryPointer(const ft::QueryClass& query);
}
//======================================================================
TEST_F(TestQKMap, TestRetrieveQueries)
{
    TEST_DESCRIPTION("Check Kmer");
    //std::set<ft::QueryClass*> retrieveQueries(const ft::KmerClass& kmer);

}
//======================================================================
TEST_F(TestQKMap, TestRetrieveKmers)
{
    TEST_DESCRIPTION("Check Kmer");
    //std::set<ft::KmerClass*> retrieveKmers(ft::QueryClass *query);

}
//======================================================================
TEST_F(TestQKMap, TestCheckForMatch)
{
    TEST_DESCRIPTION("Check Kmer");
    //bool checkForMatch(const ft::QueryClass& query, const ft::KmerClass &kmer) const;
}
//======================================================================
TEST_F(TestQKMap, TestAddQKPair)
{
    TEST_DESCRIPTION("Check Kmer");
    //void addQKPair(ft::QueryClass* query, ft::KmerClass* kmer);

}
//======================================================================
TEST_F(TestQKMap, TestAddQKSet)
{
    TEST_DESCRIPTION("Check Kmer");
    //void addQKSet(ft::QueryClass* query, std::set<ft::KmerClass*> kmers);

}



}
