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
#include "ftMapClass.h"

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
        ofstream tmpFile ("tempConfig.ini");
        if (tmpFile.is_open()) {
            tmpFile <<  "queryFile 		= path_query.txt"
                        "kmerSize 		= 30"
                        "overlap 		= 0"
                        "stride 			= 5"
                        "maxOccurences 		= 2000"
                        "threadNumber 		= 512"
                        "readLength 		= 150"
                        "indexFileLocation 	= ."
                        "outputFolder 		= ."
                        "refOnly 		= False"
                        "searchType 		= SLIDING"
                        "multithread 		= True"
                        "ignoreNonUniqueKmers 	= False"
                        "kmerCounts 		= False"
                        "matchingReads 		= MixedVirus_100.fasta";
            tmpFile.close();
        }
        _props->initFromQSettings("tempConfig.ini", false);
    }

    virtual void TearDown() {
    }

public:
    ft::FTProp* _props = new FTProp();
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

    ft::FTMap ftMap(*_props);
    _props->setMaxOcc(200);
    _props->setOverCountedFlag(false);
    ft::KmerClass kmer("ATATTATATAT");

    ftMap.addKmer(kmer);
    fs::path indexPath ("./test.fm9");
    std::string indexFileLocation ("test.fm9");
    bool printSearchTime = false;

    EXPECT_NO_THROW(_finder.sequentialSearch(ftMap, indexPath, 0));
}
}
