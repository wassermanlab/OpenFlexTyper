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
    if (fs::exists("testOutput")){fs::remove_all("testOutput");}
    }
    virtual void TearDown() {}

public:
    void CreateIndex(bool saveini = false){
        algo::IndexProps _indexProp(true);
        algo::FmIndex _fmindex;
        std::ofstream("testFiles/test.fq.gz");

        _indexProp.setR1("testFiles/test.fq.gz");
        _indexProp.setBuildDir(fs::current_path());
        _indexProp.setOutputFolder("testOutput");
        _indexProp.setReadFileType(algo::FileType::GZ);
        _indexProp.setIndexName("Index");
        _indexProp.setNumOfReads(10);
        fs::path pPF = fs::current_path() /= "testFiles/Test.fasta";

        if (fs::exists(fs::current_path() /= "testOutput/Index_Test.fm9"))
        {
            fs::remove(fs::current_path() /= "testOutput/Index_Test.fm9");
        }
         fs::path output = _fmindex.createFMIndex(_indexProp, pPF ).first;
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
    _indexProp.setBuildDir("build");
    _indexProp.setOutputFolder("testOutput");

    _indexProp.setReadFileType(algo::FileType::GZ);
    _indexProp.setReadSetName("Test");

    fs::path pPF = fs::absolute("testFiles/Test.fasta");
    fs::path output = _fmindex.createFMIndex(_indexProp, pPF ).first;
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
    std::string indexName = "Index_" + _indexProp.getReadSetName();
    _indexProp.setIndexName(indexName);


    fs::path index1 = fs::absolute(fs::current_path() /="testFiles/Test.fasta");

    _indexProp.addPPF(index1, 0, 10);
     fs::path index2 = fs::absolute(fs::current_path() /="testFiles/Test2.fasta");

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

    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();

}

//======================================================================
TEST_F(TestFMIndex, loadFMIndex)
{
    TEST_DESCRIPTION("This test checks loadFMIndex");
    CreateIndex();
    algo::FmIndex _fmindex;
    fs::path index = fs::current_path() /= "testOutput/Index_Test.fm9";

    _fmindex.loadIndexFromFile(index);

    std::string kmer = "CCCTGCATGCACTGGATGCACTCTATCCCATTCTGCAGCTTCCTCATTGATGGTCTCTTTTAACATTTGCATGGCTGCTTGATGTCCCCCCAC";
    csa_wt<wt_huff<rrr_vector<256>>, 512, 1024> _testindex;
    sdsl::load_from_file(_testindex, "testOutput/Index_Test.fm9");
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
    EXPECT_TRUE(occs > 0);
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
    KmerClass resultsKmer = _fmindex.search(kmer);

    csa_wt<wt_huff<rrr_vector<256>>, 512, 1024> _testindex;
    sdsl::load_from_file(_testindex, "testOutput/Index_Test.fm9");
    auto occs = sdsl::count(_testindex, kmer.begin(), kmer.end());
    std::cout << "count for Test.fm9  " << occs << std::endl;

    EXPECT_TRUE(occs > 0);
    EXPECT_EQ(occs, resultsKmer.getOCC());
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
    algo::FmIndex _fmindex;
    std::ofstream("test.fq.gz");
    _indexProp.setR1("test.fq.gz");
    _indexProp.setOutputFolder("testOutput");
    _indexProp.setReadSetName("Test");

    _indexProp.setReadFileType(algo::FileType::GZ);
    fs::path pPF = fs::current_path() /="testFiles/Test.fasta";
    std::cout << pPF.string() << std::endl;
    fs::path output = _fmindex.createFMIndex(_indexProp, pPF ).first;
    std::cout << "index output " << output << std::endl;
    std::string kmer = "AA";
    _fmindex.loadIndexFromFile(output);
    KmerClass resultsKmer = _fmindex.search(kmer);
    uint occs = resultsKmer.getOCC();
    fs::remove(output);

    EXPECT_TRUE(occs > 0);
    EXPECT_TRUE(resultsKmer.getKPositions().size() > 0);
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
    algo::FmIndex _fmindex;
    _indexProp.setR1("test.fq.gz");

    _indexProp.setOutputFolder("testOutput");
    _indexProp.setReadSetName("Test");

    _indexProp.setReadFileType(algo::FileType::GZ);
    fs::path pPF = "testFiles/Test.fasta";
    fs::path output = _fmindex.createFMIndex(_indexProp, pPF ).first;
    std::string kmer = "AA";
    std::cout << "index output " << output << std::endl;
    _fmindex.loadIndexFromFile(output);
    KmerClass resultsKmer = _fmindex.search(kmer, 10000);
    fs::remove(output);

    EXPECT_TRUE(resultsKmer.getKPositions().size() > 0);
    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();

}


//======================================================================
TEST_F(TestFMIndex, searchUsingSettingsIni)
{
    TEST_DESCRIPTION("search kmer in Index");
    CreateIndex(true);
    algo::IndexProps _indexProp;
    algo::FmIndex _fmindex;

    fs::path testSettings = fs::current_path() /= "testOutput/Index_Test.ini";
    _indexProp.loadFromIni(testSettings);


    fs::path index = _indexProp.getIndexSet().begin()->first;
    std::cout << "index path " << index << std::endl;
    std::string kmer = "CCCTGCATGCACTGGATGCACTCTATCCCATTCTGCAGCTTCCTCATTGATGGTCTCTTTTAACATTTGCATGGCTGCTTGATGTCCCCCCAC";
    _fmindex.loadIndexFromFile(index);
    ft::KmerClass outputKmer = _fmindex.search(kmer, 10000);
    EXPECT_TRUE(outputKmer.getKPositions().size()>0);
    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();

}

}
