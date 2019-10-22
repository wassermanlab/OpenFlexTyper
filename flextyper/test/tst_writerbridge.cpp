////////////////////////////////////////////////////////////////////////
///
/// Copyright (c) 2019, Wasserman lab
///
/// FILE        tst_writebridge.cpp
///
/// DESCRIPTION This file contains tests for the writer bridge
///
/// Initial version @ Godfrain Jacques Kounkou
///
////////////////////////////////////////////////////////////////////////

#include <gtest/gtest.h>
#include "writerbridge.cpp"

using namespace std;
using namespace ft;

namespace ft {
class TestWriterBridge : public ::testing::Test {
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
    WriterBridge _writerBridge;
};

#define TEST_DESCRIPTION(desc) RecordProperty("description", desc)

//======================================================================
TEST_F(TestWriterBridge, saveQueryOutput)
{
    MapOfCounts allCounts {};
    bool returnMatchesOnly = false;
    bool crossover = false;
    const fs::path inputQueryFile ("temp.tsv");
    const fs::path outputQueryFile("output_result.tsv");

    _writerBridge.saveQueryOutput(allCounts, returnMatchesOnly, crossover, inputQueryFile, outputQueryFile);

    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();
}
}
