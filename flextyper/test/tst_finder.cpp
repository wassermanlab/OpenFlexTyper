#include <gtest/gtest.h>
#include "finder.cpp"
#include "fmindex.cpp"
#include "mock/mock_fmindex.cpp"
#include "ifmindex.h"
#include "ftMapClass.h"
#include "ftPropsClass.h"

using namespace std;
using namespace ft;
using ::testing::AtLeast;

namespace ft {
class TestFinder : public ::testing::Test {
protected:

        ft::FTProp* _ftProps;

        virtual void SetUp() {
            _ftProps = new FTProp();
            fs::path pathToQueryFile = "path_query.tsv";
            uint kmerSize = 30;
            uint readLength =150;
            fs::path indexLocation;
            fs::path outputFolder;
            bool refOnly;
            SearchType searchType;
            bool multithread;
            fs::path inputFastQ;
            uint overlap;
            bool returnMatchesOnly;
            bool kmerCounts;
            uint stride;
            uint maxOccurences;
            uint maxThreads;
            bool flagOverCountedKmers;
            bool ignoreNonUniqueKmers;
            bool crossover;
            bool printSearchTime;
            uint maxKmers;
            uint totalKmers;
            fs::path matchingReadFQ;

            _ftProps->init(pathToQueryFile,  kmerSize,readLength,indexLocation,outputFolder,refOnly,searchType,
                           multithread,inputFastQ,overlap, returnMatchesOnly,kmerCounts, stride,maxOccurences,
                           maxThreads,flagOverCountedKmers, ignoreNonUniqueKmers,crossover, printSearchTime,
                           maxKmers, totalKmers, matchingReadFQ);
        }

    virtual void TearDown() {
    }

public:
    //ft::FTProp* _props = new FTProp();
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

    ft::FTMap ftMap(*_ftProps);
    _ftProps->setMaxOcc(200);
    _ftProps->setOverCountedFlag(false);
    ft::KmerClass kmer("ATATTATATAT");

    ftMap.addKmer(kmer);
    fs::path indexPath ("./test.fm9");
    std::string indexFileLocation ("test.fm9");
    bool printSearchTime = false;

    EXPECT_NO_THROW(_finder.sequentialSearch(ftMap, indexPath, 0));
}

}
