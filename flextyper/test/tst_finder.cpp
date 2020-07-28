#include <gtest/gtest.h>
#include "finder.cpp"
#include "mock/mock_fmindex.cpp"


using namespace std;
using namespace ft;
using ::testing::AtLeast;

namespace ft {
class TestFinder : public ::testing::Test {
protected:
    virtual void SetUp() {
        //_indexPath = "testOutput/Test.fm9";
        offset = 0;
        pathToQueryFile = "TestQuery.txt";
        kmerSize = 30;
        readLength =150;
        indexPropsFile = "Test.ini";
        outputFolder = "testOutput";
        refOnly = false;
        searchType = CENTERED;
        multithread              = false ;
        overlap                  = 0     ;
        returnMatchesOnly        = false ;
        kmerCounts               = false ;
        stride                   = 10    ;
        maxOccurences            = 200   ;
        maxThreads               = 1     ;
        flagOverCountedKmers     = false ;
        ignoreNonUniqueKmers     = true  ;
        crossover                = false ;
        pairedReads = false;
        revComp = false;
        buildDir = "";
        indexDir = "testOutput";
        readSetName = "test";
        inputFastQ = "testFiles/test.fq";
        numOfReads = 10;
        numOfIndexes =1 ;
        printInputs = true;

    }
    virtual void TearDown() {}

    fs::path _indexPath ;
    u_int offset = 0;
    fs::path pathToQueryFile;
    uint kmerSize ;
    uint readLength;
    fs::path indexPropsFile ;
    fs::path outputFolder;
    bool refOnly ;
    SearchType searchType;
    bool multithread;
    uint overlap;
    bool returnMatchesOnly;
    bool kmerCounts;
    uint stride;
    uint maxOccurences;
    uint maxThreads;
    bool flagOverCountedKmers;
    bool ignoreNonUniqueKmers;
    bool crossover;
    bool pairedReads;
    bool revComp;
    fs::path buildDir;
    fs::path indexDir;
    std::string readSetName;
    fs::path inputFastQ;
    uint numOfReads;
    uint numOfIndexes;
    bool printInputs;

public:

};

#define TEST_DESCRIPTION(desc) RecordProperty("description", desc)


//======================================================================
TEST_F(TestFinder, addResultsFutures)
{
    TEST_DESCRIPTION("Add results futures");
    //void addResultsFutures(std::set<ft::KmerClass> &indexResults, ft::KmerClass &tmpResult, uint offset);

    Finder _finder;
    ft::FTProp _ftProps;

    _ftProps.init(pathToQueryFile,kmerSize,readLength,
                  indexPropsFile,outputFolder,refOnly,
                  searchType, multithread, overlap,
                  returnMatchesOnly, kmerCounts, stride,
                  maxOccurences, maxThreads, flagOverCountedKmers,
                  ignoreNonUniqueKmers, crossover);
    _ftProps.initIndexProps( pairedReads, revComp,buildDir,indexDir,readSetName,
                             inputFastQ, numOfReads,numOfIndexes);

    ft::FTMap _ftMap(_ftProps);

    ft::KmerClass kmer("AATTACTGTGATATTTCTCATGTTCATCTTGGGCCTTATCTATTCCATCTAAAAATAGTACTTTCCTGATTCCAG");
    ft::KmerClass kmer2("AAT");
    ft::KmerClass kmer3("ATATT");
    _ftMap.addKmer(kmer);
    _ftMap.addKmer(kmer2);
    _ftMap.addKmer(kmer3);


}




//======================================================================
TEST_F(TestFinder, sequentialSearch)
{
    TEST_DESCRIPTION("This test checks that the function searchSequentially");
    //void Finder::sequentialSearch(ft::FTMap &ftMap, const fs::path &indexPath, long long offset)

    Finder _finder;
    ft::FTProp _ftProps;

    _ftProps.init(pathToQueryFile,kmerSize,readLength,
                  indexPropsFile,outputFolder,refOnly,
                  searchType, multithread, overlap,
                  returnMatchesOnly, kmerCounts, stride,
                  maxOccurences, maxThreads, flagOverCountedKmers,
                  ignoreNonUniqueKmers, crossover);
    _ftProps.initIndexProps( pairedReads, revComp,buildDir,indexDir,readSetName,
                             inputFastQ, numOfReads,numOfIndexes);
    _ftProps.addToIndexSet("testOutput/Test.fm9", 0);

    ft::FTMap _ftMap(_ftProps);

    std::map<fs::path, uint> _indexSet = _ftProps._indexSet;
    _indexPath = _indexSet.begin()->first;

    ft::KmerClass kmer("AATTACTGTGATATTTCTCATGTTCATCTTGGGCCTTATCTATTCCATCTAAAAATAGTACTTTCCTGATTCCAG");
    ft::KmerClass kmer2("AAT");
    ft::KmerClass kmer3("ATATT");
    _ftMap.addKmer(kmer);
    _ftMap.addKmer(kmer2);
    _ftMap.addKmer(kmer3);

    EXPECT_NO_THROW(_finder.sequentialSearch(_ftMap, _indexPath, offset));

    std::vector<std::set<ft::KmerClass>> results = _ftMap.getResults();
    EXPECT_EQ(results.size(), _ftProps.getNumOfIndexes());
    std::set<ft::KmerClass> result = results.front();
    EXPECT_EQ(result.size(), 3);
    auto roccsIT = result.begin();
    uint roccs = roccsIT->getKPositions().size();
    roccsIT++;
    uint roccs2 = roccsIT->getKPositions().size();
    roccsIT++;
    uint roccs3 = roccsIT->getKPositions().size();

    csa_wt<wt_huff<rrr_vector<256>>, 512, 1024> _testindex;
    sdsl::load_from_file(_testindex, "testOutput/Test.fm9");
    auto occs3 = sdsl::count(_testindex, kmer._kmer.begin(), kmer._kmer.end());
    auto occs = sdsl::count(_testindex, kmer2._kmer.begin(), kmer2._kmer.end());
    auto occs2 = sdsl::count(_testindex, kmer3._kmer.begin(), kmer3._kmer.end());

    EXPECT_EQ(occs, roccs);
    EXPECT_EQ(occs2, roccs2);
    EXPECT_EQ(occs3, roccs3);

}

//======================================================================
TEST_F(TestFinder, sequentialSearchFromIndexProps)
{
    TEST_DESCRIPTION("This test checks that the function searchSequentially");
    //void Finder::sequentialSearch(ft::FTMap &ftMap, const fs::path &indexPath, long long offset)

    Finder _finder;
    ft::FTProp _ftProps;
    indexPropsFile = "testFiles/Test.ini";
    _ftProps.init(pathToQueryFile,kmerSize,readLength,
                  indexPropsFile,outputFolder,refOnly,
                  searchType, multithread, overlap,
                  returnMatchesOnly, kmerCounts, stride,
                  maxOccurences, maxThreads, flagOverCountedKmers,
                  ignoreNonUniqueKmers, crossover, false, 3000, 3000000000, true);

    _ftProps.addToIndexSet("testOutput/Test.fm9", 0);

    ft::FTMap _ftMap(_ftProps);

    std::map<fs::path, uint> _indexSet = _ftProps._indexSet;
    _indexPath = _indexSet.begin()->first;

    ft::KmerClass kmer("AATTACTGTGATATTTCTCATGTTCATCTTGGGCCTTATCTATTCCATCTAAAAATAGTACTTTCCTGATTCCAG");
    ft::KmerClass kmer2("AAT");
    ft::KmerClass kmer3("ATATT");
    _ftMap.addKmer(kmer);
    _ftMap.addKmer(kmer2);
    _ftMap.addKmer(kmer3);

    EXPECT_NO_THROW(_finder.sequentialSearch(_ftMap, _indexPath, offset));

    std::vector<std::set<ft::KmerClass>> results = _ftMap.getResults();
    EXPECT_EQ(results.size(), _ftProps.getNumOfIndexes());
    std::set<ft::KmerClass> result = results.front();
    EXPECT_EQ(result.size(), 3);
    auto roccsIT = result.begin();
    uint roccs = roccsIT->getKPositions().size();
    roccsIT++;
    uint roccs2 = roccsIT->getKPositions().size();
    roccsIT++;
    uint roccs3 = roccsIT->getKPositions().size();

    csa_wt<wt_huff<rrr_vector<256>>, 512, 1024> _testindex;
    sdsl::load_from_file(_testindex, "testOutput/Test.fm9");
    auto occs3 = sdsl::count(_testindex, kmer._kmer.begin(), kmer._kmer.end());
    auto occs = sdsl::count(_testindex, kmer2._kmer.begin(), kmer2._kmer.end());
    auto occs2 = sdsl::count(_testindex, kmer3._kmer.begin(), kmer3._kmer.end());

    EXPECT_EQ(occs, roccs);
    EXPECT_EQ(occs2, roccs2);
    EXPECT_EQ(occs3, roccs3);

}



//======================================================================
TEST_F(TestFinder, DISABLED_parallelSearch)
{
    TEST_DESCRIPTION("parallel search");
    //void parallelSearch(FTMap &ftMap,const fs::path &indexPath, long long offset);


    Finder _finder;
    ft::FTProp _ftProps;
    maxThreads = 30;
    _ftProps.init(pathToQueryFile,kmerSize,readLength,
                  indexPropsFile,outputFolder,refOnly,
                  searchType, multithread, overlap,
                  returnMatchesOnly, kmerCounts, stride,
                  maxOccurences, maxThreads, flagOverCountedKmers,
                  ignoreNonUniqueKmers, crossover);
    _ftProps.initIndexProps( pairedReads, revComp,buildDir,indexDir,readSetName,
                             inputFastQ, numOfReads,numOfIndexes);

    ft::FTMap _ftMap(_ftProps);

    ft::KmerClass kmer("AATTACTGTGATATTTCTCATGTTCATCTTGGGCCTTATCTATTCCATCTAAAAATAGTACTTTCCTGATTCCAG");
    ft::KmerClass kmer2("AAT");
    ft::KmerClass kmer3("ATATT");
    _ftMap.addKmer(kmer);
    _ftMap.addKmer(kmer2);
    _ftMap.addKmer(kmer3);

    csa_wt<wt_huff<rrr_vector<256>>, 512, 1024> _testindex;
    sdsl::load_from_file(_testindex, "testOutput/Test.fm9");
    auto occs3 = sdsl::count(_testindex, kmer._kmer.begin(), kmer._kmer.end());
    auto occs = sdsl::count(_testindex, kmer2._kmer.begin(), kmer2._kmer.end());
    auto occs2 = sdsl::count(_testindex, kmer3._kmer.begin(), kmer3._kmer.end());

    _finder.parallelSearch(_ftMap, _indexPath, offset);

    std::vector<std::set<ft::KmerClass>> results = _ftMap.getResults();
    EXPECT_EQ(results.size(), _ftProps.getNumOfIndexes());
    std::set<ft::KmerClass> result = results.front();
    std::cout<< "result size " << result.size() << std::endl;
    auto roccsIT = result.begin();
    uint roccs = roccsIT->getKPositions().size();
    roccsIT++;
    uint roccs2 = roccsIT->getKPositions().size();
    roccsIT++;
    uint roccs3 = roccsIT->getKPositions().size();
    EXPECT_EQ(occs, roccs);
    EXPECT_EQ(occs2, roccs2);
    EXPECT_EQ(occs3, roccs3);

}










}
