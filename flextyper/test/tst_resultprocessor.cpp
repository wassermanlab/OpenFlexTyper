////////////////////////////////////////////////////////////////////////
///
/// Copyright (c) 2019, Wasserman lab
///
/// FILE        tst_resultprocessor.cpp
///
/// DESCRIPTION This file contains tests for the result processor
///
/// Initial version @ Godfrain Jacques Kounkou
///
////////////////////////////////////////////////////////////////////////

#include <gtest/gtest.h>
#include "resultprocessor.cpp"

using namespace std;
using namespace ft;

namespace ft {
class TestResultProcessor : public ::testing::Test {
protected:
    virtual void SetUp() {
    }

    virtual void TeadDown() {
    }

public:
    ResultProcessor _resultProcessor;
};

#define TEST_DESCRIPTION(desc) RecordProperty("description", desc)

//======================================================================
TEST_F(TestResultProcessor, getIndexCounts)
{
    TEST_DESCRIPTION("This test tests the method getIndex counts");

    ResultsMap  inputs {{{1, QueryType::REF}, {1000, 5444, 421, 74, 1021}}};
    MapOfCounts expectedOutput {{{1, QueryType::REF}, 5}};

    MapOfCounts output = _resultProcessor.getIndexCounts(inputs);

    EXPECT_EQ(output, expectedOutput);
    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();
}

//======================================================================
TEST_F(TestResultProcessor, getIndexCountsRepeatedPosition)
{
    TEST_DESCRIPTION("This test tests the method getIndex counts");

    ResultsMap  inputs {{{1, QueryType::REF}, {1000, 5444, 1000, 74, 1021}}};
    MapOfCounts expectedOutput {{{1, QueryType::REF}, 4}};

    MapOfCounts output = _resultProcessor.getIndexCounts(inputs);

    EXPECT_EQ(output, expectedOutput);
    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();
}

//======================================================================
TEST_F(TestResultProcessor, processIndexPos)
{
    TEST_DESCRIPTION("This test tests the method process index pos");

    ResultsMap inputs {{{1, QueryType::REF}, {1000, 5444, 421, 74, 1021}}};
    uint readLen = 100;

    ResultsMap output = _resultProcessor.processIndexPos(inputs, readLen);
    ResultsMap expectedOutput {{{1, QueryType::REF}, {0, 4, 9, 10, 53}}};

    EXPECT_EQ(output, expectedOutput);
    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();
}

//======================================================================
TEST_F(TestResultProcessor, processIndexPosNoInput)
{
    TEST_DESCRIPTION("This test tests the method process index pos");

    ResultsMap inputs {{{1, QueryType::REF}, {}}};
    uint readLen = 100;

    ResultsMap output = _resultProcessor.processIndexPos(inputs, readLen);
    ResultsMap expectedOutput {{{1, QueryType::REF}, {}}};

    EXPECT_EQ(output, expectedOutput);
    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();
}

//======================================================================
TEST_F(TestResultProcessor, processResults)
{
    TEST_DESCRIPTION("This test tests the method processResults");

    ResultsMap indexPosResults {{{1, QueryType::REF}, {1, 4, 85, 441, 140, 54, 66}}};;
    uint readLen = 100;
    MapOfCounts expectedOutput {{{1, QueryType::REF}, 3}};

    MapOfCounts output = _resultProcessor.processResults(indexPosResults, readLen);

    EXPECT_EQ(output, expectedOutput);
    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();
}
}
