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
TEST_F(TestFinder, searchSequentially)
{
    TEST_DESCRIPTION("This test checks that the function searchSequentially");
    //void Finder::sequentialSearch(ft::FTMap &ftMap, const fs::path &indexPath, long long offset)


    Finder _finder;

    fs::path _indexPath = "/home/tixii/Git/OpenFlexTyper/build/Test.fm9";
    u_int offset = 0;

    ft::FTProp _ftProps;
    fs::path pathToQueryFile = "TestQuery.txt";
    uint kmerSize = 30;
    uint readLength =150;
    fs::path indexPropsFile = "Test.ini";
    fs::path outputFolder;
    bool refOnly = false;
    SearchType searchType;

    _ftProps.init(pathToQueryFile,kmerSize,readLength,indexPropsFile,outputFolder,refOnly,searchType);
    ft::FTMap _ftMap(_ftProps);
    _ftProps.setMaxOcc(200);
    _ftProps.setOverCountedFlag(false);

    ft::KmerClass kmer("CCTT");
    ft::KmerClass kmer2("AAT");
    ft::KmerClass kmer3("ATATT");
    _ftMap.addKmer(kmer);
    _ftMap.addKmer(kmer2);
    _ftMap.addKmer(kmer3);


    csa_wt<wt_huff<rrr_vector<256>>, 512, 1024> _testindex;
    sdsl::load_from_file(_testindex, "testOutput/Test2.fm9");
    auto occs = sdsl::count(_testindex, kmer._kmer.begin(), kmer._kmer.end());
    std::cout << "kmer CCTT occs " << occs << std::endl;
    auto occs2 = sdsl::count(_testindex, kmer2._kmer.begin(), kmer2._kmer.end());
    std::cout << "kmer AAT occs " << occs2 << std::endl;
    auto occs3 = sdsl::count(_testindex, kmer3._kmer.begin(), kmer3._kmer.end());
    std::cout << "kmer AAT occs " << occs3 << std::endl;


    EXPECT_NO_THROW(_finder.sequentialSearch(_ftMap, _indexPath, 0));
}

}
