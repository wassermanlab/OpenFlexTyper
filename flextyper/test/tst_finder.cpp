////////////////////////////////////////////////////////////////////////
///
/// Copyright (c) 2019, Wasserman lab
///
/// FILE        tst_finder.cpp
///
/// DESCRIPTION This file contains tests for the finder class
///
/// Initial version @ Godfrain Jacques Kounkou
///
////////////////////////////////////////////////////////////////////////

#include <gtest/gtest.h>
#include "finder.cpp"
#include "fmindex.cpp"
#include "mock/mock_fmindex.cpp"
#include "ifmindex.h"

using namespace std;
using namespace ft;
using ::testing::AtLeast;

namespace ft {
class TestFinder : public ::testing::Test {
protected:
    virtual void SetUp() {
        ofstream index("test.fm9");
        if (index.is_open()) {}
        index.close();
    }

    virtual void TeadDown() {
    }

public:
};

#define TEST_DESCRIPTION(desc) RecordProperty("description", desc)

//======================================================================
TEST_F(TestFinder, searchSequentially)
{
    TEST_DESCRIPTION("This test checks that the function searchSequentially");

    std::shared_ptr<MockFmIndex> fmIndex = std::make_shared<MockFmIndex>();
    EXPECT_CALL(*fmIndex, loadIndexFromFile("./test.fm9"))
            .Times(AtLeast(1));
    EXPECT_CALL(*fmIndex, setKmerMapSize(1))
            .Times(AtLeast(1));
    Finder _finder;
    _finder.overrideFmIndex(fmIndex);

    ResultsMap indexPosResults;
    KmerMap kmerMap {{"ATATTATATAT", {{1, QueryType::REF}}}};
    fs::path indexPath ("./test.fm9");
    std::string indexFileLocation ("test.fm9");
    uint maxOccurrences = 200;
    bool printSearchTime = false;

    EXPECT_NO_THROW(_finder.sequentialSearch(indexPosResults, indexFileLocation, kmerMap, indexPath, maxOccurrences, printSearchTime, 0));
}
}
