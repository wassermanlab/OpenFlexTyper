#include <gtest/gtest.h>
#include <sdsl/suffix_arrays.hpp>
#include "fmindex.cpp"


using namespace std;
using namespace ft;
using namespace algo;
using namespace sdsl;
namespace ft {
class TestFMIndex : public ::testing::Test {
protected:
    virtual void SetUp() {}
    virtual void TearDown() {}

public:

};

#define TEST_DESCRIPTION(desc) RecordProperty("description", desc)

//======================================================================
TEST_F(TestFMIndex, createFMIndex)
{
    TEST_DESCRIPTION("This test checks that the function searchSequentially");
    algo::IndexProps _indexProp;
    algo::FmIndex _fmindex;
    _indexProp.setR1("test.fq.gz");
    _indexProp.setOutputFile("Test");
    _indexProp.setOutputFolder("testOutput");
    _indexProp.setReadFileType(algo::FileType::GZ);
    fs::path pPF = "Test.fasta";
    fs::path output = _fmindex.createFMIndex(_indexProp, pPF );
    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();

}
//======================================================================
TEST_F(TestFMIndex, DISABLED_createParalleFMIndex)
{
    TEST_DESCRIPTION("This test checks that the function searchSequentially");
    algo::IndexProps _indexProp;
    algo::FmIndex _fmindex;
    _indexProp.setR1("test.fq.gz");
    _indexProp.setOutputFile("Test");
    _indexProp.setOutputFolder("testOutput");
    _indexProp.setNumOfIndexes(2);
    _indexProp.setReadFileType(algo::FileType::GZ);
    std::map<fs::path, std::pair<u_int, uint>> pPFS;
    pPFS["Test.fasta"]= std::make_pair(0, 10);
    pPFS["Test2.fasta"]= std::make_pair(11, 20);
    _indexProp.setPreProcessedFastas(pPFS);
    _fmindex.parallelFmIndex(_indexProp);

    csa_wt<wt_huff<rrr_vector<256>>, 512, 1024> _testindex;

    std::string kmer = "CCCTGCATGCACTGGATGCACTCTATCCCATTCTGCAGCTTCCTCATTGATGGTCTCTTTTAACATTTGCATGGCTGCTTGATGTCCCCCCAC";


    sdsl::load_from_file(_testindex, "testOutput/Test.fm9");
    auto occs = sdsl::count(_testindex, kmer.begin(), kmer.end());

    csa_wt<wt_huff<rrr_vector<256>>, 512, 1024> _testindex2;
    sdsl::load_from_file(_testindex, "testOutput/Test2.fm9");
    auto occs2 = sdsl::count(_testindex, kmer.begin(), kmer.end());

    EXPECT_EQ(occs, 1);
    EXPECT_EQ(occs2, 1);
    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();

}


//======================================================================
TEST_F(TestFMIndex, loadFMIndex)
{
    TEST_DESCRIPTION("This test checks that the function searchSequentially");

    algo::FmIndex _fmindex;
    _fmindex.loadIndexFromFile("testOutput/Test.fm9");

    std::string kmer = "CCCTGCATGCACTGGATGCACTCTATCCCATTCTGCAGCTTCCTCATTGATGGTCTCTTTTAACATTTGCATGGCTGCTTGATGTCCCCCCAC";
    csa_wt<wt_huff<rrr_vector<256>>, 512, 1024> _testindex;
    auto occs = sdsl::count(_testindex, kmer.begin(), kmer.end());
    std::cout << "occs " << occs << std::endl;

    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();
}
//======================================================================
TEST_F(TestFMIndex, searchFMIndex)
{
    TEST_DESCRIPTION("Search FMIndex");

    algo::FmIndex _fmindex;
    _fmindex.loadIndexFromFile("testOutput/Test.fm9");

    std::string kmer = "CCTT";
    KmerClass testKmer(kmer);
    KmerClass resultsKmer = _fmindex.search(testKmer);
    uint count = resultsKmer.getKPositions().size();
    csa_wt<wt_huff<rrr_vector<256>>, 512, 1024> _testindex;
    sdsl::load_from_file(_testindex, "testOutput/Test.fm9");
    auto occs = sdsl::count(_testindex, kmer.begin(), kmer.end());
    std::cout << "occs " << occs << std::endl;
    EXPECT_EQ(count, occs);
    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();

}

}
