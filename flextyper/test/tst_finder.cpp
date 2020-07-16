#include <gtest/gtest.h>
#include "finder.cpp"

#include "ftMapClass.cpp"
#include "mock/mock_fmindex.cpp"


using namespace std;
using namespace ft;
using ::testing::AtLeast;

namespace ft {
class TestFinder : public ::testing::Test {
protected:
    virtual void SetUp() {}
    virtual void TearDown() {}

public:

};

#define TEST_DESCRIPTION(desc) RecordProperty("description", desc)

//======================================================================
TEST_F(TestFinder, DISABLED_searchSequentially)
{
//    TEST_DESCRIPTION("This test checks that the function searchSequentially");

//    std::shared_ptr<MockFmIndex> fmIndex = std::make_shared<MockFmIndex>();
//    EXPECT_CALL(*fmIndex, loadIndexFromFile("./test.fm9"))
//            .Times(AtLeast(1));
//    EXPECT_CALL(*fmIndex, setKmerMapSize(1))
//            .Times(AtLeast(1));
//    Finder _finder;

//    ft::FTProp _ftProps;
//    fs::path pathToQueryFile = "TestQuery.txt";
//    uint kmerSize = 30;
//    uint readLength =150;
//    fs::path indexPropsFile;
//    fs::path outputFolder;
//    bool refOnly = false;
//    SearchType searchType;

//    _ftProps.init(pathToQueryFile,kmerSize,readLength,indexPropsFile,outputFolder,refOnly,searchType);
//    _finder.overrideFmIndex(fmIndex);

//    ft::FTMap ftMap(_ftProps);
//    _ftProps.setMaxOcc(200);
//    _ftProps.setOverCountedFlag(false);
//    ft::KmerClass kmer("ATATTATATAT");

//    ftMap.addKmer(kmer);
//    fs::path indexPath ("./test.fm9");
//    std::string indexFileLocation ("test.fm9");


//    EXPECT_NO_THROW(_finder.sequentialSearch(ftMap, indexPath, 0));
}

}
