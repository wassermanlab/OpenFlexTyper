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
    TEST_DESCRIPTION("This test checks createFMIndex");
    algo::IndexProps _indexProp;
    algo::FmIndex _fmindex;
    _indexProp.setR1("test.fq.gz");
    _indexProp.setOutputFile("Test");
    _indexProp.setOutputFolder("testOutput");
    _indexProp.setReadFileType(algo::FileType::GZ);
    fs::path pPF = "testFiles/Test.fasta";
    fs::path output = _fmindex.createFMIndex(_indexProp, pPF );
    csa_wt<wt_huff<rrr_vector<256>>, 512, 1024> _testindex;

    std::string kmer = "AAAATAGTACTTTCCTGATTCCAGCACTGACTAATTTATCTACTTGTTCA";

    sdsl::load_from_file(_testindex, "testOutput/Test.fm9");
    auto occs = sdsl::count(_testindex, kmer.begin(), kmer.end());
    EXPECT_EQ(occs, 1);
    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();

}
//======================================================================
TEST_F(TestFMIndex, createParallelFMIndex)
{
    TEST_DESCRIPTION("create parallel FMIndex");
    algo::IndexProps _indexProp;
    algo::FmIndex _fmindex;
    _indexProp.setR1("test.fq.gz");
    _indexProp.setOutputFile("Test");
    _indexProp.setOutputFolder("testOutput");
    _indexProp.setNumOfIndexes(2);
    _indexProp.setReadFileType(algo::FileType::GZ);
    std::map<fs::path, std::pair<u_int, uint>> pPFS;
    pPFS["testFiles/Test.fasta"]= std::make_pair(0, 10);
    pPFS["testFiles/Test2.fasta"]= std::make_pair(11, 20);
    _indexProp.setPreProcessedFastas(pPFS);
    _fmindex.parallelFmIndex(_indexProp);

    csa_wt<wt_huff<rrr_vector<256>>, 512, 1024> _testindex;

    std::string kmer = "AAAATAGTACTTTCCTGATTCCAGCACTGACTAATTTATCTACTTGTTCA";


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
    TEST_DESCRIPTION("This test checks loadFMIndex");

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
TEST_F(TestFMIndex, searchFMIndexDirect)
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
//======================================================================
TEST_F(TestFMIndex, locateInFMIndexDirect)
{
    TEST_DESCRIPTION("Locate kmer in FMIndex");

    algo::FmIndex _fmindex;
    _fmindex.loadIndexFromFile("testOutput/Test.fm9");
    std::string kmer = "CCTT";
    KmerClass testKmer(kmer);
    KmerClass resultsKmer = _fmindex.search(testKmer);

    csa_wt<wt_huff<rrr_vector<256>>, 512, 1024> _testindex;
    sdsl::load_from_file(_testindex, "testOutput/Test.fm9");
    auto occs = sdsl::count(_testindex, kmer.begin(), kmer.end());
    auto locations = sdsl::locate(_fmindex.getIndex(), kmer.begin(), kmer.end());

    EXPECT_EQ(occs, locations.size());
    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();

}

//======================================================================
TEST_F(TestFMIndex, locateInIndexUsingPointers)
{
    TEST_DESCRIPTION("Locate kmer in Index");
    algo::IndexProps _indexProp;
    algo::FmIndex* _fmindex = new algo::FmIndex;
    _indexProp.setR1("test.fq.gz");
    _indexProp.setOutputFile("Test");
    _indexProp.setOutputFolder("testOutput");
    _indexProp.setReadFileType(algo::FileType::GZ);
    fs::path pPF = "testFiles/Test.fasta";
    fs::path output = _fmindex->createFMIndex(_indexProp, pPF );
    std::string kmer = "AA";
    _fmindex->loadIndexFromFile(output);
    auto occs = sdsl::count(_fmindex->getIndex(), kmer.begin(), kmer.end());
    auto locations = sdsl::locate(_fmindex->getIndex(), kmer.begin(), kmer.end());

    EXPECT_EQ(occs, locations.size());
    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();

}

//======================================================================
TEST_F(TestFMIndex, searchFMIndexUsingPointer)
{
    TEST_DESCRIPTION("search kmer in Index");
    algo::IndexProps _indexProp;
    algo::FmIndex* _fmindex = new algo::FmIndex;
    _indexProp.setR1("test.fq.gz");
    _indexProp.setOutputFile("Test");
    _indexProp.setOutputFolder("testOutput");
    _indexProp.setReadFileType(algo::FileType::GZ);
    fs::path pPF = "testFiles/Test.fasta";
    fs::path output = _fmindex->createFMIndex(_indexProp, pPF );
    std::string kmer = "AA";
    _fmindex->loadIndexFromFile(output);
    auto locations = sdsl::locate(_fmindex->getIndex(), kmer.begin(), kmer.end());
    ft::KmerClass outputKmer = _fmindex->search(ft::KmerClass(kmer), 10000, true);
    EXPECT_EQ(outputKmer.getKPositions().size(), locations.size());
    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();

}


//======================================================================
TEST_F(TestFMIndex, DISABLED_searchUsingSettingsIni)
{
    TEST_DESCRIPTION("search kmer in Index");
    algo::IndexProps _indexProp;
    algo::FmIndex* _fmindex = new algo::FmIndex;


    fs::path testSettings = fs::current_path() /= "testFiles/Test.ini";
    std::cout << "test settings " << testSettings << std::endl;
    QSettings isettings(testSettings.string().c_str(), QSettings::IniFormat);

    bool _pairedReads = isettings.value("pairedReads").toBool();
    bool _indexRevComp = isettings.value("revComp").toBool();
    fs::path _buildDir = isettings.value("buildDirectory").toString().toStdString();
    fs::path _indexDir = isettings.value("indexDirectory").toString().toStdString();
    std::string _readSetName = isettings.value("readSetName").toString().toStdString();
    fs::path _inputFastQ;
    fs::path _R1;
    fs::path _R2;
    if (_pairedReads){
       _inputFastQ = isettings.value("R1").toString().toStdString();
       _R1 = isettings.value("R1").toString().toStdString();
       _R2 = isettings.value("R2").toString().toStdString();
    } else {
       _inputFastQ = isettings.value("readFQ").toString().toStdString();
    }

    u_int _numOfReads = isettings.value("numOfReads").toUInt();
    u_int _numOfIndexes = isettings.value("numOfIndexes").toUInt();

    std::map<fs::path, uint> indexSet;

    int size = isettings.beginReadArray("IndexFiles");
    for (int i = 0; i < size; ++i) {
        isettings.setArrayIndex(i);
        std::string fileName = isettings.value("fileName").toString().toStdString();
        u_int offset = isettings.value("offset").toInt();
        indexSet[fileName] = offset;
    }
    isettings.endArray();


    std::cout << "Properties loaded from Index File     " <<  std::endl;
    std::cout << "Paired Reads      : " << _pairedReads <<  std::endl;
    std::cout << "reverse Comp      : " << _indexRevComp <<  std::endl;
    std::cout << "build Directory   : " << _buildDir <<  std::endl;
    std::cout << "index Directory   : " << _indexDir <<  std::endl;
    std::cout << "read Set Name     : " << _readSetName <<  std::endl;
    std::cout << "Read FQ           : " << _inputFastQ <<  std::endl;
    std::cout << "Number of Reads   : " << _numOfReads <<  std::endl;
    std::cout << "Number of Indexes : " << _numOfIndexes <<  std::endl;
    if (_pairedReads)
        {std::cout << "R1                : " << _R1 <<  std::endl;
         std::cout << "R2                : " << _R2 <<  std::endl;
        }
    for (auto index : indexSet){
        std::cout << "Index File : " << index.first << " Offset: " << index.second <<  std::endl;
    }

    _indexProp.setR1(_R1);
    _indexProp.setR2(_R2);
    _indexProp.setReadFQ(_inputFastQ);
    _indexProp.setBuildDir(_buildDir);
    _indexProp.setNumOfReads(_numOfReads);
    _indexProp.setNumOfIndexes(_numOfIndexes);
    _indexProp.setIndexSet(indexSet);
    _indexProp.setReadSetName(_readSetName);
    _indexProp.setOutputFolder(_indexDir);
    fs::path index = _indexProp.getIndexSet().begin()->first;
    std::cout << "index path " << index << std::endl;
    std::string kmer = "CCCTGCATGCACTGGATGCACTCTATCCCATTCTGCAGCTTCCTCATTGATGGTCTCTTTTAACATTTGCATGGCTGCTTGATGTCCCCCCAC";
    _fmindex->loadIndexFromFile(index);
    auto locations = sdsl::locate(_fmindex->getIndex(), kmer.begin(), kmer.end());
    ft::KmerClass outputKmer = _fmindex->search(ft::KmerClass(kmer), 10000, true);
    EXPECT_EQ(outputKmer.getKPositions().size(), locations.size());
    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();

}

}
