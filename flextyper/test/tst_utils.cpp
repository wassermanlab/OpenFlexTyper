////////////////////////////////////////////////////////////////////////
///
/// Copyright (c) 2019, Wasserman lab
///
/// FILE        tst_utils.cpp
///
/// DESCRIPTION This file contains tests for the utils class
///
/// Initial version @ Godfrain Jacques Kounkou
///
////////////////////////////////////////////////////////////////////////

#include <gtest/gtest.h>
#include "utils.cpp"
#include <experimental/filesystem>

using namespace std;
using namespace ft;
namespace fs = experimental::filesystem;

namespace ft {
class TestUtils : public ::testing::Test {
protected:
    virtual void SetUp() {
        ofstream indexes("indices.txt");

        if (indexes.is_open()) {
            indexes << "test_index_1.fm9\n";
            indexes << "test_index_2.fm9\n";
        }
        indexes.close();
    }

    virtual void TeadDown() {
    }

public:
    Utils _utils;
};

#define TEST_DESCRIPTION(desc) RecordProperty("description", desc)

//======================================================================
TEST_F(TestUtils, split)
{
    TEST_DESCRIPTION("This test tests the capacity to split the given string,"
                     "The result was checked with : "
                     "https://www.bioinformatics.org/sms/rev_comp.html");

    string input ("ATTTTTTTTTTTGGGGGGGGGGGGGGGGGG");
    string expectedOutput ("CCCCCCCCCCCCCCCCCCAAAAAAAAAAAT");
    string output = _utils.reverseComplement(input);

    EXPECT_EQ(output, expectedOutput);
}

//======================================================================
TEST_F(TestUtils, splitWithWeirdNucleotide)
{
    TEST_DESCRIPTION("This test tests the capacity to split the given string,"
                     "The result was checked with : "
                     "https://www.bioinformatics.org/sms/rev_comp.html");

    string input ("ATTTTTTTTTTTGGGGGGGGGGGGGGGGGGB");
    string expectedOutput ("");
    string output = _utils.reverseComplement(input);

    EXPECT_EQ(output, expectedOutput);
}

//======================================================================
TEST_F(TestUtils, getSetOfIndexes)
{
    TEST_DESCRIPTION("This test tests the capacity to get the set of indexes");

    fs::path input ("indices.txt");
    set<fs::path> expectedPaths { "test_index_1.fm9",
                                  "test_index_2.fm9"};

    set<fs::path> output = _utils.getSetOfIndexes(input);

    EXPECT_EQ(output, expectedPaths);
}

//======================================================================
TEST_F(TestUtils, convertIndexPositionsToReadIDs)
{
    TEST_DESCRIPTION("This test tests the capacity to convert Index position to readID");

    set<long long> input {1, 2, 878, 55465, 5456, 56654};
    uint readLen = 100;
    set<size_t> expectedPositions {0, 8, 54, 549, 560};

    set<size_t> output = _utils.convertIndexPositionsToReadIDs(input, readLen);

    EXPECT_EQ(output, expectedPositions);
}

//======================================================================
TEST_F(TestUtils, convertIndexPositionsToReadIDsWithRepeatedPositions)
{
    TEST_DESCRIPTION("This test tests the capacity to convert Index position to readID");

    set<long long> input {1, 2, 878, 55465, 5456, 56654, 56654, 56654};
    uint readLen = 100;
    set<size_t> expectedPositions {0, 8, 54, 549, 560};

    set<size_t> output = _utils.convertIndexPositionsToReadIDs(input, readLen);

    EXPECT_EQ(output, expectedPositions);
}

//======================================================================
TEST_F(TestUtils, fileIndexToQueryIndex)
{
    TEST_DESCRIPTION("This test test that the method findIndexToQueryIndex translates the index");

    vector<int> input {1, 5, 2, 6, 3, 1, 4, 2, 1};
    vector<int> expectedOutputVector {2, 6, 3, 7, 4, 2, 5, 3, 2};

    vector<int> output;
    for (auto e : input) {
        output.push_back(_utils.fileIndexToQueryIndex(e));
    }

    EXPECT_EQ(output, expectedOutputVector);
}

//======================================================================
TEST_F(TestUtils, fileIndexToQueryIndexWithWeirdCases)
{
    TEST_DESCRIPTION("This test test that in case of weird cases, the program exits correctly");

    int input = -15;

    EXPECT_EXIT(_utils.fileIndexToQueryIndex(input), ::testing::ExitedWithCode(1), "");
}

//======================================================================
TEST_F(TestUtils, fileIndexToQueryIndexWithAnotherWeirdCases)
{
    TEST_DESCRIPTION("This test test that in case of weird cases, the program exits correctly");

    int input = -1;

    EXPECT_EXIT(_utils.fileIndexToQueryIndex(input), ::testing::ExitedWithCode(1), "");
}

//======================================================================
TEST_F(TestUtils, trimmedReadFileName)
{
    TEST_DESCRIPTION("This test trimmes the read filename");

    fs::path input ("Indexes_ERR123456.fasta");
    string expectedOutput("ERR123456.fasta");
    string output = _utils.trimmedReadFileName(input);

    EXPECT_EQ(output, expectedOutput);
}

//======================================================================
TEST_F(TestUtils, trimmedReadFileNameWithoutNeedToRoRemovePattern)
{
    TEST_DESCRIPTION("This test makes sure the readname is not changes if there is no need to trim");

    fs::path input ("ERR123456.fasta");
    string expectedOutput("ERR123456.fasta");
    string output = _utils.trimmedReadFileName(input);

    EXPECT_EQ(output, expectedOutput);
}
}
