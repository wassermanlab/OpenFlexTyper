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
    virtual void SetUp() {

    }
    virtual void TearDown() {}

public:
    void CreateIndex(bool saveini = false){
        algo::IndexProps _indexProp(true);
        algo::FmIndex _fmindex;
        std::ofstream("testFiles/test.fq.gz");
        _indexProp.setReadFQ("testFiles/test.fq.gz");
        _indexProp.setR1("testFiles/test.fq.gz");
        _indexProp.setBuildDir(fs::current_path());
        _indexProp.setOutputFolder("testOutput");
        _indexProp.setReadFileType(algo::FileType::GZ);
        _indexProp.setIndexFileName("Index");
        fs::path pPF = fs::current_path() /= "testFiles/Test.fasta";

        if (fs::exists(fs::current_path() /= "testOutput/Index_Test.fm9"))
        {
            fs::remove(fs::current_path() /= "testOutput/Index_Test.fm9");
        }
         fs::path output = _fmindex.createFMIndex(_indexProp, pPF );
        _indexProp.addToIndexSet(output, 0);
         if (saveini){
             fs::path ini = fs::current_path() /= "testOutput/Index_Test.ini";
             if (fs::exists(ini))
            {
             fs::remove(ini);
             }
            _indexProp.saveIndexProps(ini);
        }

    }

};

#define TEST_DESCRIPTION(desc) RecordProperty("description", desc)


//======================================================================
TEST_F(TestFMIndex, createFMIndex)
{
    TEST_DESCRIPTION("This test checks createFMIndex");
    fs::path testIndex = fs::absolute(fs::current_path() /= "testOutput/Index_Test.fm9");
    std::cout << "test index " << testIndex.string() << std::endl;
    if (fs::exists(testIndex)){ fs::remove(testIndex); }

    algo::IndexProps _indexProp(true);
    algo::FmIndex _fmindex;
    std::ofstream("test.fq.gz");
    _indexProp.setR1("test.fq.gz");
    _indexProp.setBuildDir(fs::current_path().parent_path() /= "build");
    _indexProp.setOutputFolder(fs::absolute(fs::current_path() /= "testOutput"));

    _indexProp.setReadFileType(algo::FileType::GZ);
    _indexProp.setReadSetName("Test");
    _indexProp.setOutputFile();
    fs::path pPF = fs::absolute(fs::current_path() /= "testFiles/Index_Test.fasta");

    fs::path output = _fmindex.createFMIndex(_indexProp, pPF );
    csa_wt<wt_huff<rrr_vector<256>>, 512, 1024> _testindex;

    std::string kmer = "AAAATAGTACTTTCCTGATTCCAGCACTGACTAATTTATCTACTTGTTCA";

    sdsl::load_from_file(_testindex, testIndex);
    auto occs = sdsl::count(_testindex, kmer.begin(), kmer.end());
    fs::remove(output);
    EXPECT_EQ(occs, 1);
    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();

}
//======================================================================
TEST_F(TestFMIndex, createParallelFMIndex)
{
    TEST_DESCRIPTION("create parallel FMIndex");
    fs::path testIndex = fs::current_path() /= "testOutput/Index_Test.fm9";
    fs::path testIndex2 = fs::current_path() /= "testOutput/Index_Test2.fm9";
    std::cout << "test index " << testIndex.string() << std::endl;
    if (fs::exists(testIndex)){ fs::remove(testIndex); }
    if (fs::exists(testIndex2)){ fs::remove(testIndex2); }
    algo::IndexProps _indexProp(true);
    algo::FmIndex _fmindex;
    std::ofstream("test.fq.gz");
    _indexProp.setR1("test.fq.gz");

    _indexProp.setOutputFolder(fs::current_path() /= "testOutput");
    _indexProp.setReadSetName("Test");
    _indexProp.setNumOfIndexes(2);
    _indexProp.setReadFileType(algo::FileType::GZ);
    _indexProp.setOutputFile();
    std::map<fs::path, std::pair<u_int, uint>> pPFS;

    fs::path index1 = fs::absolute(fs::current_path() /="testFiles/Test.fasta");

    pPFS[index1]= std::make_pair(0, 10);
     fs::path index2 = fs::absolute(fs::current_path() /="testFiles/Test2.fasta");

    pPFS[index2]= std::make_pair(11, 20);
    _indexProp.setPreProcessedFastas(pPFS);
    _fmindex.parallelFmIndex(_indexProp);


    fs::path index1 = fs::absolute(fs::current_path() /="testFiles/Index_Test.fasta");

    _indexProp.addPPF(index1, 0, 10);
     fs::path index2 = fs::absolute(fs::current_path() /="testFiles/Index_Test2.fasta");

    _indexProp.addPPF(index2, 11, 20);

    _fmindex.parallelFmIndex(_indexProp);
     std::map<fs::path, uint> _indexSet = _indexProp.getIndexSet();
     std::string kmer = "AAAATAGTACTTTCCTGATTCCAGCACTGACTAATTTATCTACTTGTTCA";
    for (auto index : _indexSet)
    {
        std::cout << "Checking in " << index.first << std::endl;
        csa_wt<wt_huff<rrr_vector<256>>, 512, 1024> _testindex;
        sdsl::load_from_file(_testindex, fs::absolute(index.first));
        auto occs = sdsl::count(_testindex, kmer.begin(), kmer.end());
        EXPECT_EQ(occs, 1);
        fs::remove(index.first);
    }

    csa_wt<wt_huff<rrr_vector<256>>, 512, 1024> _testindex2;
    sdsl::load_from_file(_testindex, "testOutput/Index_Test2.fm9");
    auto occs2 = sdsl::count(_testindex, kmer.begin(), kmer.end());

    EXPECT_EQ(occs, 1);
    EXPECT_EQ(occs2, 1);
    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();
    fs::remove("testOutput/Index_Test.fm9");
    fs::remove("testOutput/Index_Test2.fm9");
}

//======================================================================
TEST_F(TestFMIndex, loadFMIndex)
{
    TEST_DESCRIPTION("This test checks loadFMIndex");
    CreateIndex();
    algo::FmIndex _fmindex;
    fs::path index = fs::current_path() /= "testFiles/Test.fm9";

    _fmindex.loadIndexFromFile(index);

    std::string kmer = "CCCTGCATGCACTGGATGCACTCTATCCCATTCTGCAGCTTCCTCATTGATGGTCTCTTTTAACATTTGCATGGCTGCTTGATGTCCCCCCAC";
    csa_wt<wt_huff<rrr_vector<256>>, 512, 1024> _testindex;
    sdsl::load_from_file(_testindex, "testFiles/Index_Test.fm9");
    auto occs = sdsl::count(_testindex, kmer.begin(), kmer.end());
    std::cout << "occs " << occs << std::endl;
    EXPECT_EQ(occs, 1);
    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();
}
//======================================================================
TEST_F(TestFMIndex, searchFMIndexDirect)
{
    TEST_DESCRIPTION("Search FMIndex");
    CreateIndex();
    algo::FmIndex _fmindex;
    fs::path index = fs::current_path() /= "testOutput/Index_Test.fm9";
    _fmindex.loadIndexFromFile(index);
    std::string kmer = "AAAAC";
    KmerClass testKmer(kmer);
    KmerClass resultsKmer = _fmindex.search(kmer);
    uint count = resultsKmer.getKPositions().size();

    csa_wt<wt_huff<rrr_vector<256>>, 512, 1024> _testindex;
    sdsl::load_from_file(_testindex, "testOutput/Index_Test.fm9");
    auto occs = sdsl::count(_testindex, kmer.begin(), kmer.end());
    std::cout << "count " << count << " occs " << occs << std::endl;
    EXPECT_EQ(count, occs);
    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();

}
//======================================================================
TEST_F(TestFMIndex, locateInFMIndexDirect)
{
    TEST_DESCRIPTION("Locate kmer in FMIndex");
    CreateIndex();
    algo::FmIndex _fmindex;
    fs::path index = fs::current_path() /= "testOutput/Index_Test.fm9";
    _fmindex.loadIndexFromFile(index);
    std::string kmer = "AAAAC";
    KmerClass testKmer(kmer);
    KmerClass resultsKmer = _fmindex.search(kmer);

    csa_wt<wt_huff<rrr_vector<256>>, 512, 1024> _testindex;
    sdsl::load_from_file(_testindex, "testOutput/Index_Test.fm9");
    auto occs = sdsl::count(_testindex, kmer.begin(), kmer.end());
    std::cout << "count for Test.fm9  " << occs << std::endl;

    auto locations = sdsl::locate(_fmindex.getIndex(), kmer.begin(), kmer.end());

    EXPECT_EQ(occs, locations.size());
    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();

}

//======================================================================
TEST_F(TestFMIndex, locateInIndexUsingPointers)
{
    TEST_DESCRIPTION("Locate kmer in Index");
    fs::path testIndex = fs::current_path() /= "testOutput/Index_Test.fm9";
    if (fs::exists(testIndex)){ fs::remove(testIndex); }
    algo::IndexProps _indexProp;
    algo::FmIndex* _fmindex = new algo::FmIndex;
    std::ofstream("test.fq.gz");
    _indexProp.setR1("test.fq.gz");
    _indexProp.setOutputFolder("testOutput");
    _indexProp.setReadSetName("Test");
    _indexProp.setOutputFile();
    _indexProp.setReadFileType(algo::FileType::GZ);
    fs::path pPF = fs::current_path() /="testFiles/Index_Test.fasta";
    std::cout << pPF.string() << std::endl;
    fs::path output = _fmindex->createFMIndex(_indexProp, pPF );
    std::cout << "index output " << output << std::endl;
    std::string kmer = "AA";
    _fmindex->loadIndexFromFile(output);
    auto occs = sdsl::count(_fmindex->getIndex(), kmer.begin(), kmer.end());
    auto locations = sdsl::locate(_fmindex->getIndex(), kmer.begin(), kmer.end());
    fs::remove(output);
    EXPECT_EQ(occs, locations.size());
    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();

}

//======================================================================
TEST_F(TestFMIndex, searchFMIndexUsingPointer)
{
    TEST_DESCRIPTION("search kmer in Index");
    fs::path testIndex = fs::current_path() /= "testOutput/Index_Test.fm9";
    if (fs::exists(testIndex)){ fs::remove(testIndex); }
    algo::IndexProps _indexProp;
    algo::FmIndex* _fmindex = new algo::FmIndex;
    _indexProp.setR1("test.fq.gz");

    _indexProp.setOutputFolder("testOutput");
    _indexProp.setReadSetName("Test");
    _indexProp.setOutputFile();
    _indexProp.setReadFileType(algo::FileType::GZ);
    fs::path pPF = "testFiles/Index_Test.fasta";
    fs::path output = _fmindex->createFMIndex(_indexProp, pPF );
    std::string kmer = "AA";
    std::cout << "index output " << output << std::endl;
    _fmindex->loadIndexFromFile(output);
    auto locations = sdsl::locate(_fmindex->getIndex(), kmer.begin(), kmer.end());
    ft::KmerClass outputKmer = _fmindex->search(kmer, 10000, true);
    EXPECT_EQ(outputKmer.getKPositions().size(), locations.size());
    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();

}


//======================================================================
TEST_F(TestFMIndex, searchUsingSettingsIni)
{
    TEST_DESCRIPTION("search kmer in Index");
    CreateIndex(true);
    algo::IndexProps _indexProp;
    algo::FmIndex* _fmindex = new algo::FmIndex;


    fs::path testSettings = fs::current_path() /= "testOutput/Index_Test.ini";
    _indexProp.loadFromIni(testSettings);


    fs::path index = _indexProp.getIndexSet().begin()->first;
    std::cout << "index path " << index << std::endl;
    std::string kmer = "CCCTGCATGCACTGGATGCACTCTATCCCATTCTGCAGCTTCCTCATTGATGGTCTCTTTTAACATTTGCATGGCTGCTTGATGTCCCCCCAC";
    _fmindex->loadIndexFromFile(index);
    auto locations = sdsl::locate(_fmindex->getIndex(), kmer.begin(), kmer.end());
    ft::KmerClass outputKmer = _fmindex->search(kmer, 10000, true);
    EXPECT_TRUE(locations.size()>0);
    EXPECT_EQ(outputKmer.getKPositions().size(), locations.size());
    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();

}

}
