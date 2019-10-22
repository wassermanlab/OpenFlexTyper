////////////////////////////////////////////////////////////////////////
///
/// Copyright (c) 2019, Wasserman lab
///
/// FILE        tst_queryextractor.cpp
///
/// DESCRIPTION This file contains tests for the query extractions
///
/// Initial version @ Godfrain Jacques Kounkou
///
////////////////////////////////////////////////////////////////////////

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
           tmpFile << "0\tTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT\t"
                         "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\t";
           tmpFile.close();
        }
    }

    virtual void TeadDown() {
    }

public:
    QueryExtractor _queryExtractor;
};

#define TEST_DESCRIPTION(desc) RecordProperty("description", desc)

//======================================================================
TEST_F(TestQueryExtractor, getInputQueriesRoutineTest_FileIndex_0)
{
    TEST_DESCRIPTION("This test tests the input queries generated");

    string refSequence("TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT");
    string altSequence("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");

    uint fileIndex = 0;
    set<Query> inputQueries;

    _queryExtractor.getInputQueriesRoutine(refSequence, altSequence, fileIndex, inputQueries);

    set<Query> expectedQueries {{ 1, "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT",
                                     "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
                                     "" }};

    EXPECT_EQ(expectedQueries, inputQueries);
    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();
}

//======================================================================
TEST_F(TestQueryExtractor, getInputQueriesRoutineTest_FileIndex_1)
{
    TEST_DESCRIPTION("This test tests the input queries generated");

    string refSequence("TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT");
    string altSequence("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");

    uint fileIndex = 1;
    set<Query> inputQueries;

    _queryExtractor.getInputQueriesRoutine(refSequence, altSequence, fileIndex, inputQueries);

    set<Query> expectedQueries {{ 2, "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT",
                                     "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
                                     "" }};

    EXPECT_EQ(expectedQueries, inputQueries);
    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();
}

//======================================================================
TEST_F(TestQueryExtractor, getStartAndEndPointSequencesTest)
{
    TEST_DESCRIPTION("This test tests the get start and endpoint sequence");

    string startPointRef("AATAAAACCGGTTA");
    string endPointRef("AATTTTTTTTTTTA");
    uint fileIndex = 1;
    set<Query> results;
    _queryExtractor.getStartAndEndPointSequences(startPointRef, endPointRef, fileIndex, results);
    set<Query> expectedResults {{ 2, "AATAAAACCGGTTA", "AATTTTTTTTTTTA", "AATAAAATTTTTTA" }};

    EXPECT_EQ(results, expectedResults);
    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();
}

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
