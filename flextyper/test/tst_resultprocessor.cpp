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
#include <fstream>
#include <iostream>

using namespace std;
using namespace ft;

namespace ft {
class TestResultProcessor : public ::testing::Test {
protected:
    virtual void SetUp() {
    }

    virtual void TeadDown() {
    }

    bool areFileIdentical(const string& f1, const string& f2) {
        ifstream fin1(f1);
        string str1;
        string line;
        if (fin1.is_open()) {
            while (getline(fin1, line)) {
                str1 += line;
            }
            fin1.close();
        }

        ifstream fin2(f2);
        string str2;
        if (fin2.is_open()) {
            while (getline(fin2, line)) {
                str2 += line;
            }
            fin2.close();
        }

        return str1 == str2;
    }

public:
    ResultProcessor _resultProcessor;
};

#define TEST_DESCRIPTION(desc) RecordProperty("description", desc)

//======================================================================
TEST_F(TestResultProcessor, getIndexCounts)
{
    TEST_DESCRIPTION("This test tests the method getIndex counts");

    ReaIDsMap  inputs {{{1, QueryType::REF}, {1000, 5444, 421, 74, 1021}}};
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

    ReaIDsMap  inputs {{{1, QueryType::REF}, {1000, 5444, 1000, 74, 1021}}};
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

    ReaIDsMap output = _resultProcessor.processIndexPos(inputs, readLen);
    ReaIDsMap expectedOutput {{{1, QueryType::REF}, {0, 4, 9, 10, 53}}};

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

    ReaIDsMap output = _resultProcessor.processIndexPos(inputs, readLen);
    ReaIDsMap expectedOutput {{{1, QueryType::REF}, {}}};

    EXPECT_EQ(output, expectedOutput);
    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();
}

//======================================================================
TEST_F(TestResultProcessor, processResults)
{
    TEST_DESCRIPTION("This test tests the method processResults");

    ResultsMap indexPosResults {{{1, QueryType::REF}, {1, 4, 85, 395, 140, 54, 66}}};;
    uint readLen = 100;
    MapOfCounts expectedOutput {{{1, QueryType::REF}, 2}};

    MapOfCounts output = _resultProcessor.processResults(indexPosResults, readLen, 4, "index.fa");

    EXPECT_EQ(output, expectedOutput);
    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();
}

//======================================================================
TEST_F(TestResultProcessor, processResults_extract_matching_reads_0)
{
    TEST_DESCRIPTION("This test tests the method processResults with extract matching reads activated");

    std::remove("extracted_reads.fa");
    ResultsMap indexPosResults {{{1, QueryType::REF}, {60}}};
    uint readLen = 59;
    ofstream outputFile("index.fa");
    if (outputFile.is_open()) {
        outputFile << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAATAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"; // 0 -> 59
        outputFile << "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTATTTTTTTTTTTTTTTTTTTTTTTTTTTT\n";
        outputFile << "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCGCCCCCCCCCCCCCCCCCCCCCCCCCCCC\n";
        outputFile << "GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCGGGGGGGGGGGGGGGGGGGGGGGGGGGG\n";
    }
    outputFile.close();
    _resultProcessor.processResults(indexPosResults, readLen, 4, "index.fa");

    // expected output
    ofstream expectedFile("expectedFile.fa");
    if (expectedFile.is_open()) {
        expectedFile << "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTATTTTTTTTTTTTTTTTTTTTTTTTTTTT\n";
    }
    expectedFile.close();

    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();
    EXPECT_EQ(areFileIdentical("expectedFile.fa", "extracted_reads.fa"), true);
}

//======================================================================
TEST_F(TestResultProcessor, processResults_extract_matching_reads_1)
{
    TEST_DESCRIPTION("This test tests the method processResults with extract matching reads activated");

    std::remove("extracted_reads.fa");
    ResultsMap indexPosResults {{{1, QueryType::REF}, {60, 61, 62}}};
    uint readLen = 59;
    ofstream outputFile("index.fa");
    if (outputFile.is_open()) {
        outputFile << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAATAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"; // 0 -> 59
        outputFile << "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTATTTTTTTTTTTTTTTTTTTTTTTTTTTT\n";
        outputFile << "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCGCCCCCCCCCCCCCCCCCCCCCCCCCCCC\n";
        outputFile << "GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCGGGGGGGGGGGGGGGGGGGGGGGGGGGG\n";
    }
    outputFile.close();
    _resultProcessor.processResults(indexPosResults, readLen, 4, "index.fa");

    // expected output
    ofstream expectedFile("expectedFile.fa");
    if (expectedFile.is_open()) {
        expectedFile << "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTATTTTTTTTTTTTTTTTTTTTTTTTTTTT\n";
    }
    expectedFile.close();

    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();
    EXPECT_EQ(areFileIdentical("expectedFile.fa", "extracted_reads.fa"), true);
}

//======================================================================
TEST_F(TestResultProcessor, processResults_extract_matching_reads_2)
{
    TEST_DESCRIPTION("This test tests the method processResults with extract matching reads activated");

    std::remove("extracted_reads.fa");
    ResultsMap indexPosResults {{{1, QueryType::REF}, {68, 61, 62, 206, 209}}};
    uint readLen = 59;
    ofstream outputFile("index.fa");
    if (outputFile.is_open()) {
        outputFile << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAATAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"; // 0 -> 58
        outputFile << "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTATTTTTTTTTTTTTTTTTTTTTTTTTTTT\n";
        outputFile << "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCGCCCCCCCCCCCCCCCCCCCCCCCCCCCC\n";
        outputFile << "GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCGGGGGGGGGGGGGGGGGGGGGGGGGGGG\n";
    }
    outputFile.close();
    _resultProcessor.processResults(indexPosResults, readLen, 4, "index.fa");

    // expected output
    ofstream expectedFile("expectedFile.fa");
    if (expectedFile.is_open()) {
        expectedFile << "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTATTTTTTTTTTTTTTTTTTTTTTTTTTTT\n";
    }
    expectedFile.close();

    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();
    EXPECT_EQ(areFileIdentical("expectedFile.fa", "extracted_reads.fa"), true);
}

//======================================================================
TEST_F(TestResultProcessor, processResults_extract_matching_reads_3)
{
    TEST_DESCRIPTION("This test tests the method processResults with extract matching reads activated");

    std::remove("extracted_reads.fa");
    ResultsMap indexPosResults {{{1, QueryType::REF}, {}}};
    uint readLen = 59;
    ofstream outputFile("index.fa");
    if (outputFile.is_open()) {
        outputFile << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAATAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"; // 0 -> 59
        outputFile << "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTATTTTTTTTTTTTTTTTTTTTTTTTTTTT\n";
        outputFile << "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCGCCCCCCCCCCCCCCCCCCCCCCCCCCCC\n";
        outputFile << "GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCGGGGGGGGGGGGGGGGGGGGGGGGGGGG\n";
    }
    outputFile.close();
    _resultProcessor.processResults(indexPosResults, readLen, 4, "index.fa");

    // expected output
    ofstream expectedFile("expectedFile.fa");
    if (expectedFile.is_open()) {
    }
    expectedFile.close();

    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();
    EXPECT_EQ(areFileIdentical("expectedFile.fa", "extracted_reads.fa"), true);
}

//======================================================================
TEST_F(TestResultProcessor, processResults_extract_matching_reads_4)
{
    TEST_DESCRIPTION("This test tests the method processResults with extract matching reads activated");

    std::remove("extracted_reads.fa");
    ResultsMap indexPosResults {{{1, QueryType::REF}, {10000, 349320}}};
    uint readLen = 59;
    ofstream outputFile("index.fa");
    if (outputFile.is_open()) {
        outputFile << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAATAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"; // 0 -> 59
        outputFile << "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTATTTTTTTTTTTTTTTTTTTTTTTTTTTT\n";
        outputFile << "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCGCCCCCCCCCCCCCCCCCCCCCCCCCCCC\n";
        outputFile << "GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCGGGGGGGGGGGGGGGGGGGGGGGGGGGG\n";
    }
    outputFile.close();
    _resultProcessor.processResults(indexPosResults, readLen, 4, "index.fa");

    // expected output
    ofstream expectedFile("expectedFile.fa");
    if (expectedFile.is_open()) {
    }
    expectedFile.close();

    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();
    EXPECT_EQ(areFileIdentical("expectedFile.fa", "extracted_reads.fa"), true);
}

//======================================================================
TEST_F(TestResultProcessor, processResults_extract_matching_reads_5)
{
    TEST_DESCRIPTION("This test tests the method processResults with extract matching reads activated");

    std::remove("extracted_reads.fa");
    ResultsMap indexPosResults {{{1, QueryType::REF}, {6}}};
    uint readLen = 59;
    ofstream outputFile("index.fa");
    if (outputFile.is_open()) {
        outputFile << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAATAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"; // 0 -> 59
        outputFile << "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTATTTTTTTTTTTTTTTTTTTTTTTTTTTT\n";
        outputFile << "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCGCCCCCCCCCCCCCCCCCCCCCCCCCCCC\n";
        outputFile << "GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCGGGGGGGGGGGGGGGGGGGGGGGGGGGG\n";
    }
    outputFile.close();
    _resultProcessor.processResults(indexPosResults, readLen, 4, "index.fa");

    // expected output
    ofstream expectedFile("expectedFile.fa");
    if (expectedFile.is_open()) {
        expectedFile << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAATAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n";
    }
    expectedFile.close();

    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();
    EXPECT_EQ(areFileIdentical("expectedFile.fa", "extracted_reads.fa"), true);
}

//======================================================================
TEST_F(TestResultProcessor, processResults_extract_matching_reads_6)
{
    TEST_DESCRIPTION("This test tests the method processResults with extract matching reads activated");

    std::remove("extracted_reads.fa");
    ResultsMap indexPosResults {{{1, QueryType::REF}, {6, 150}}};
    uint readLen = 59;
    ofstream outputFile("index.fa");
    if (outputFile.is_open()) {
        outputFile << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAATAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"; // 0 -> 58
        outputFile << "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTATTTTTTTTTTTTTTTTTTTTTTTTTTTT\n";
        outputFile << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAATAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n";
        outputFile << "GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCGGGGGGGGGGGGGGGGGGGGGGGGGGGG\n";
    }
    outputFile.close();
    _resultProcessor.processResults(indexPosResults, readLen, 4, "index.fa");

    // expected output
    ofstream expectedFile("expectedFile.fa");
    if (expectedFile.is_open()) {
        expectedFile << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAATAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n";
    }
    expectedFile.close();

    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();
    EXPECT_EQ(areFileIdentical("expectedFile.fa", "extracted_reads.fa"), true);
}

//======================================================================
TEST_F(TestResultProcessor, processResults_extract_matching_reads_7)
{
    TEST_DESCRIPTION("This test tests the method processResults with extract matching reads activated");

    std::remove("extracted_reads.fa");
    ResultsMap indexPosResults {{{1, QueryType::REF}, {6, 200}}};
    uint readLen = 59;
    ofstream outputFile("index.fa");
    if (outputFile.is_open()) {
        outputFile << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAATAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"; // 0 -> 58
        outputFile << "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTATTTTTTTTTTTTTTTTTTTTTTTTTTTT\n";
        outputFile << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAATAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n";
        outputFile << "GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCGGGGGGGGGGGGGGGGGGGGGGGGGGGG\n";
    }
    outputFile.close();
    _resultProcessor.processResults(indexPosResults, readLen, 4, "index.fa");

    // expected output
    ofstream expectedFile("expectedFile.fa");
    if (expectedFile.is_open()) {
        expectedFile << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAATAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n";
        expectedFile << "GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCGGGGGGGGGGGGGGGGGGGGGGGGGGGG\n";
    }
    expectedFile.close();

    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();
    EXPECT_EQ(areFileIdentical("expectedFile.fa", "extracted_reads.fa"), true);
}

//======================================================================
TEST_F(TestResultProcessor, processResults_extract_matching_reads_8)
{
    TEST_DESCRIPTION("This test tests the method processResults with extract matching reads activated");

    std::remove("extracted_reads.fa");
    ResultsMap indexPosResults {{{1, QueryType::REF}, {68, 120}}};
    uint readLen = 59;
    ofstream outputFile("index.fa");
    if (outputFile.is_open()) {
        outputFile << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAATAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"; // 0 -> 58
        outputFile << "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTATTTTTTTTTTTTTTTTTTTTTTTTTTTT\n";
        outputFile << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAATAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n";
        outputFile << "GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCGGGGGGGGGGGGGGGGGGGGGGGGGGGG\n";
    }
    outputFile.close();
    _resultProcessor.processResults(indexPosResults, readLen, 4, "index.fa");

    // expected output
    ofstream expectedFile("expectedFile.fa");
    if (expectedFile.is_open()) {
        expectedFile << "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTATTTTTTTTTTTTTTTTTTTTTTTTTTTT\n";
        expectedFile << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAATAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n";
    }
    expectedFile.close();

    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();
    EXPECT_EQ(areFileIdentical("expectedFile.fa", "extracted_reads.fa"), true);
}
}
