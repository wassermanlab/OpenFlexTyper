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

    ft::FTMap ftMap;
    ftMap.setMaxOcc(200);
    ftMap.setOverCountedFlag(false);
    ft::KmerClass kmer("ATATTATATAT");
    kmer.addQuery(std::make_pair(1, ft::QueryType::REF));
    ftMap.addKmer(kmer);
    fs::path indexPath ("./test.fm9");
    std::string indexFileLocation ("test.fm9");
    uint maxOccurrences = 200;
    bool flagOverCountedKmers = false;
    bool printSearchTime = false;

//    void Finder::sequentialSearch(ft::FTMap& ftMap,
//                                  const fs::path& indexFileLocation,
//                                  fs::path indexPath, bool printSearchTime, long long offset)


    EXPECT_NO_THROW(_finder.sequentialSearch(ftMap, indexFileLocation, indexPath, printSearchTime, 0));
}
}
