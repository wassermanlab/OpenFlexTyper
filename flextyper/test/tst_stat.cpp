////////////////////////////////////////////////////////////////////////
///
/// Copyright (c) 2019, Wasserman lab
///
/// FILE        tst_stats.cpp
///
/// DESCRIPTION This file contains tests for the stats class
///
/// Initial version @ Godfrain Jacques Kounkou
///
////////////////////////////////////////////////////////////////////////

#include <gtest/gtest.h>
#include "stats.cpp"
#include <experimental/filesystem>

using namespace std;
using namespace ft;
namespace fs = experimental::filesystem;

namespace ft {
class TestStats : public ::testing::Test {
protected:
    virtual void SetUp() {
        ofstream output_expected("output_expected.log");

        if (output_expected.is_open()) {
            output_expected << "ATTATCTATCTACTACTTCTATCTACTCTA : 3\n";
            output_expected << "CTAGCATCGATCGATCGATCGATCGACTGC : 5\n";
            output_expected << "CTTTTTTTTATCTACTTACTATCTTTTTTT : 1\n";
            output_expected << "GGGGCTGACTACGTAGCTACGATCGATCGT : 4\n";
        }

        output_expected.close();
    }

    virtual void TeadDown() {
        // std::remove("output_expected.log");
    }

public:
    bool compareFiles(const string& file1, const string& file2) {
        ifstream f1(file1), f2(file2);
        string content1, content2;

        string line;
        if (f1.is_open()) {
            while (getline(f1, line))
            content1 += line;
        }
        f1.close();

        line.clear();

        if (f2.is_open()) {
            while (getline(f2, line))
            content2 += line;
        }
        f2.close();

        return content1 == content2;
    }

public:
    Stats _stats;
};

#define TEST_DESCRIPTION(desc) RecordProperty("description", desc)

//======================================================================
TEST_F(TestStats, printKmerCountToFile)
{
    TEST_DESCRIPTION("This test will chech that the function creates an ouput file");

    map<string, uint> counter {{ "ATTATCTATCTACTACTTCTATCTACTCTA", 3},
                               { "GGGGCTGACTACGTAGCTACGATCGATCGT", 4},
                               { "CTTTTTTTTATCTACTTACTATCTTTTTTT", 1},
                               { "CTAGCATCGATCGATCGATCGATCGACTGC", 5}};

    fs::path output ("output.log");

    _stats.printKmerCountToFile(output, counter);

    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();
    EXPECT_TRUE(fs::exists(output));
}

//======================================================================
TEST_F(TestStats, printKmerCountToFileEmpty)
{
    TEST_DESCRIPTION("This test will chech that the function creates an ouput file");

    map<string, uint> counter {};

    fs::path output ("output.log");

    _stats.printKmerCountToFile(output, counter);

    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();
    EXPECT_FALSE(fs::exists(output));
}

//======================================================================
TEST_F(TestStats, printKmerCountToFileCompareContent)
{
    TEST_DESCRIPTION("This test will chech that the function creates an ouput file");

    map<string, uint> counter {{ "ATTATCTATCTACTACTTCTATCTACTCTA", 3},
                               { "GGGGCTGACTACGTAGCTACGATCGATCGT", 4},
                               { "CTTTTTTTTATCTACTTACTATCTTTTTTT", 1},
                               { "CTAGCATCGATCGATCGATCGATCGACTGC", 5}};

    fs::path output ("output.log");
    fs::path expectedOutpt ("output_expected.log");

    _stats.printKmerCountToFile(output, counter);

    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();
    EXPECT_TRUE(compareFiles(output, expectedOutpt));
}
}
