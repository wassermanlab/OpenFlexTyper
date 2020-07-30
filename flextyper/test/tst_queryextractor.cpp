#include <gtest/gtest.h>
#include "queryextractor.cpp"


using namespace std;
using namespace ft;

namespace ft {
class TestQueryExtractor : public ::testing::Test {
protected:
    virtual void SetUp() {
        ofstream tmpFile ("temp.tsv");

        if (tmpFile.is_open()) {
           tmpFile << "# header\n";
           tmpFile << "1\tTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT\t"
                         "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\t";
           tmpFile.close();
        }
    }

    virtual void TearDown() {
    }

public:
    QueryExtractor _queryExtractor;
};

#define TEST_DESCRIPTION(desc) RecordProperty("description", desc)





//======================================================================
TEST_F(TestQueryExtractor, getInputQueriesTestRefOnly)
{
    TEST_DESCRIPTION("This test tests the get input queries method");

    bool refOnly  = true;
    bool crossover = false;
    const fs::path& pathToQueryFile("temp.tsv");

    set<Query> results;
    results = _queryExtractor.getInputQueries(refOnly, crossover, pathToQueryFile);

    set<Query> expectedResults {{ 1, "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT",
                                     "",
                                     "" }};

    EXPECT_EQ(results, expectedResults);
    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();
}

//======================================================================
TEST_F(TestQueryExtractor, getInputQueriesTestRefAndAlt)
{
    TEST_DESCRIPTION("This test tests the get input queries method");

    bool refOnly  = false;
    bool crossover = false;
    const fs::path& pathToQueryFile("temp.tsv");

    set<Query> results;
    results = _queryExtractor.getInputQueries(refOnly, crossover, pathToQueryFile);

    set<Query> expectedResults {{ 1, "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT",
                                     "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
                                     "" }};

    EXPECT_EQ(results, expectedResults);
    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();
}

//======================================================================
TEST_F(TestQueryExtractor, getInputQueriesTestCrossover)
{
    TEST_DESCRIPTION("This test tests the get input queries method");

    bool refOnly  = false;
    bool crossover = true;
    const fs::path& pathToQueryFile("temp.tsv");

    set<Query> results;
    results = _queryExtractor.getInputQueries(refOnly, crossover, pathToQueryFile);

    set<Query> expectedResults {{ 1, "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT",
                                     "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
                                     "TTTTTTTTTTTTTTTTTTTTTTTTTTTTAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" }};

    EXPECT_EQ(results, expectedResults);
    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();
}

}
