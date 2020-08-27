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
        revCompSearch = false;
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
        countAsPairs             = false ;
        crossover                = false ;
        pairedReads = false;
        revComp = false;
        buildDir = "";
        indexDir = "testOutput";
        indexFileName = "Index";
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
    bool revCompSearch;
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
    bool countAsPairs;
    bool crossover;
    bool pairedReads;
    bool revComp;
    fs::path buildDir;
    fs::path indexDir;
    std::string indexFileName;
    std::string readSetName;
    fs::path inputFastQ;
    uint numOfReads;
    uint numOfIndexes;
    bool printInputs;

public:
    void CreateIndex(bool saveini = false){
        algo::IndexProps _indexProp(true);
        algo::FmIndex _fmindex;
        std::ofstream("testFiles/test.fq.gz");
        _indexProp.setR1("testFiles/test.fq.gz");
        _indexProp.setBuildDir(fs::current_path());
        _indexProp.setOutputFolder("testOutput");
        _indexProp.setReadFileType(algo::FileType::GZ);

        _indexProp.setReadSetName("Test");
        fs::path pPF = fs::current_path() /= "testFiles/Index_Test.fasta";

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
TEST_F(TestFinder, addResultsFutures)
{
    TEST_DESCRIPTION("Add results futures");
    //void addResultsFutures(std::set<ft::KmerClass> &indexResults, ft::KmerClass &tmpResult, uint offset);

    Finder _finder;
    ft::FTProp _ftProps;

    _ftProps.init(pathToQueryFile,kmerSize,readLength,
                  indexPropsFile,outputFolder,refOnly, revCompSearch,
                  searchType, multithread, overlap,
                  returnMatchesOnly, kmerCounts, stride,
                  maxOccurences, maxThreads, flagOverCountedKmers,
                  ignoreNonUniqueKmers, crossover);
    _ftProps.initIndexProps( pairedReads, revComp,buildDir,indexDir,indexFileName, readSetName,
                             inputFastQ, numOfReads,numOfIndexes);

    ft::FTMap _ftMap(_ftProps);


    _ftMap.addKmer("AATTACTGTGATATTTCTCATGTTCATCTTGGGCCTTATCTATTCCATCTAAAAATAGTACTTTCCTGATTCCAG");
    _ftMap.addKmer("AAT");
    _ftMap.addKmer("ATATT");


}



//======================================================================
TEST_F(TestFinder, sequentialSearch)
{
    TEST_DESCRIPTION("This test checks that the function searchSequentially");
    //void Finder::sequentialSearch(ft::FTMap &ftMap, const fs::path &indexPath, long long offset)
    CreateIndex();
    Finder _finder;
    ft::FTProp _ftProps;

    _ftProps.init(pathToQueryFile,kmerSize,readLength,
                  indexPropsFile,outputFolder,refOnly, revCompSearch,
                  searchType, multithread, overlap,
                  returnMatchesOnly, kmerCounts, stride,
                  maxOccurences, maxThreads, flagOverCountedKmers,
                  ignoreNonUniqueKmers, crossover);
    _ftProps.initIndexProps( pairedReads, revComp,buildDir,indexDir,indexFileName, readSetName,
                             inputFastQ, numOfReads,numOfIndexes);
    _ftProps.addToIndexSet("testOutput/Index_Test.fm9", 0);

    ft::FTMap _ftMap(_ftProps);

    std::map<fs::path, uint> _indexSet = _ftProps._indexSet;
    _indexPath = _indexSet.begin()->first;

    std::string kmer = "AATTACTGTGATATTTCTCATGTTCATCTTGGGCCTTATCTATTCCATCTAAAAATAGTACTTTCCTGATTCCAG";
    std::string kmer2 = "AAT";
    std::string kmer3 = "ATATT";
    _ftMap.addKmer(kmer);
    _ftMap.addKmer(kmer2);
    _ftMap.addKmer(kmer3);

    EXPECT_NO_THROW(_finder.sequentialSearch(_ftMap, _indexPath, offset));

    std::vector<std::map<std::string, ft::KmerClass>> results = _ftMap.getResults();
    EXPECT_EQ(results.size(), _ftProps.getNumOfIndexes());
    std::map<std::string, ft::KmerClass> result = results.front();
    EXPECT_EQ(result.size(), 3);


    uint roccs = result[kmer].getKPositions().size();
    uint roccs2 = result[kmer2].getKPositions().size();
    uint roccs3 = result[kmer3].getKPositions().size();


    csa_wt<wt_huff<rrr_vector<256>>, 512, 1024> _testindex;
    sdsl::load_from_file(_testindex, "testOutput/Index_Test.fm9");
    auto occs = sdsl::count(_testindex, kmer.begin(), kmer.end());
    auto occs2 = sdsl::count(_testindex, kmer2.begin(), kmer2.end());
    auto occs3 = sdsl::count(_testindex, kmer3.begin(), kmer3.end());

    EXPECT_EQ(occs, roccs);
    EXPECT_EQ(occs2, roccs2);
    EXPECT_EQ(occs3, roccs3);

}
//======================================================================
TEST_F(TestFinder, sequentialSearchLocations)
{
    TEST_DESCRIPTION("This test checks that the function searchSequentially");
    //void Finder::sequentialSearch(ft::FTMap &ftMap, const fs::path &indexPath, long long offset)
    CreateIndex();
    Finder _finder;
    ft::FTProp _ftProps;

    _ftProps.init(pathToQueryFile,kmerSize,readLength,
                  indexPropsFile,outputFolder,refOnly, revCompSearch,
                  searchType, multithread, overlap,
                  returnMatchesOnly, kmerCounts, stride,
                  maxOccurences, maxThreads, flagOverCountedKmers,
                  ignoreNonUniqueKmers, crossover);
    _ftProps.initIndexProps( pairedReads, revComp,buildDir,indexDir,indexFileName, readSetName,
                             inputFastQ, numOfReads,numOfIndexes);
    _ftProps.addToIndexSet("testOutput/Index_Test.fm9", 0);

    ft::FTMap _ftMap(_ftProps);

    std::map<fs::path, uint> _indexSet = _ftProps._indexSet;
    _indexPath = _indexSet.begin()->first;

    std::string kmer = "AATTACTGTGATATTTCTCATGTTCATCTTGGGCCTTATCTATTCCATCTAAAAATAGTACTTTCCTGATTCCAG";
    std::string kmer2 = "AAT";
    std::string kmer3 = "ATATT";
    _ftMap.addKmer(kmer);
    _ftMap.addKmer(kmer2);
    _ftMap.addKmer(kmer3);

    EXPECT_NO_THROW(_finder.sequentialSearch(_ftMap, _indexPath, offset));

    std::vector<std::map<std::string, ft::KmerClass>> results = _ftMap.getResults();
    EXPECT_EQ(results.size(), _ftProps.getNumOfIndexes());
    std::map<std::string, ft::KmerClass> result = results.front();
    EXPECT_EQ(result.size(), 3);


    uint roccs = result[kmer].getKPositions().size();
    uint roccs2 = result[kmer2].getKPositions().size();
    uint roccs3 = result[kmer3].getKPositions().size();


    csa_wt<wt_huff<rrr_vector<256>>, 512, 1024> _testindex;
    std::cout << fs::current_path() << std::endl;
    sdsl::load_from_file(_testindex, "testOutput/Index_Test.fm9");

    auto occs2 = sdsl::count(_testindex, kmer2.begin(), kmer2.end());
    std::cout << "occs2 " << occs2 << std::endl;
    auto locs2 = sdsl::locate(_testindex, kmer2.begin(), kmer2.end());

    auto occs = sdsl::count(_testindex, kmer.begin(), kmer.end());
    auto locs = sdsl::locate(_testindex, kmer.begin(), kmer.end());
    auto occs3 = sdsl::count(_testindex, kmer3.begin(), kmer3.end());
    auto locs3 = sdsl::locate(_testindex, kmer3.begin(), kmer3.end());

    EXPECT_EQ(occs, locs.size());
    EXPECT_EQ(occs2, locs2.size());
    EXPECT_EQ(occs3, locs3.size());
    EXPECT_EQ(occs, roccs);
    EXPECT_EQ(occs2, roccs2);
    EXPECT_EQ(occs3, roccs3);

}

//======================================================================
TEST_F(TestFinder, sequentialSearchFromIndexProps)
{
    TEST_DESCRIPTION("This test checks that the function searchSequentially");
    //void Finder::sequentialSearch(ft::FTMap &ftMap, const fs::path &indexPath, long long offset)
    CreateIndex();
    Finder _finder;
    ft::FTProp _ftProps;
    indexPropsFile = "testFiles/Test.ini";
    _ftProps.init(pathToQueryFile,kmerSize,readLength,
                  indexPropsFile,outputFolder,refOnly, revCompSearch,
                  searchType, multithread, overlap,
                  returnMatchesOnly, kmerCounts, stride,
                  maxOccurences, maxThreads, flagOverCountedKmers,
                  ignoreNonUniqueKmers, crossover, false, 3000, 3000000000, true);

    _ftProps.addToIndexSet("testOutput/Index_Test.fm9", 0);

    ft::FTMap _ftMap(_ftProps);

    std::map<fs::path, uint> _indexSet = _ftProps._indexSet;
    _indexPath = _indexSet.begin()->first;

    std::string kmer = "AATTACTGTGATATTTCTCATGTTCATCTTGGGCCTTATCTATTCCATCTAAAAATAGTACTTTCCTGATTCCAG";
    std::string kmer2 = "AAT";
    std::string kmer3 = "ATATT";
    _ftMap.addKmer(kmer);
    _ftMap.addKmer(kmer2);
    _ftMap.addKmer(kmer3);


    EXPECT_NO_THROW(_finder.sequentialSearch(_ftMap, _indexPath, offset));

    std::vector<std::map<std::string, ft::KmerClass>> results = _ftMap.getResults();
    EXPECT_EQ(results.size(), _ftProps.getNumOfIndexes());
    std::map<std::string, ft::KmerClass> result = results.front();
    EXPECT_EQ(result.size(), 3);
    uint roccs = result[kmer].getKPositions().size();
    uint roccs2 = result[kmer2].getKPositions().size();
    uint roccs3 = result[kmer3].getKPositions().size();

    csa_wt<wt_huff<rrr_vector<256>>, 512, 1024> _testindex;
    sdsl::load_from_file(_testindex, "testOutput/Index_Test.fm9");
    auto occs = sdsl::count(_testindex, kmer.begin(), kmer.end());
    auto occs2 = sdsl::count(_testindex, kmer2.begin(), kmer2.end());
    auto occs3 = sdsl::count(_testindex, kmer3.begin(), kmer3.end());

    EXPECT_EQ(occs, roccs);
    EXPECT_EQ(occs2, roccs2);
    EXPECT_EQ(occs3, roccs3);

}



//======================================================================
TEST_F(TestFinder, parallelSearch1)
{
    TEST_DESCRIPTION("parallel search single index, num kmers > max threads");
    //void parallelSearch(FTMap &ftMap,const fs::path &indexPath, long long offset);
    CreateIndex(true);

    Finder _finder;
    ft::FTProp _ftProps;
    maxThreads = 2;
    indexPropsFile = "testOutput/Index_Test.ini";
    _ftProps.init(pathToQueryFile,kmerSize,readLength,
                  indexPropsFile,outputFolder,refOnly, revCompSearch,
                  searchType, multithread, overlap,
                  returnMatchesOnly, kmerCounts, stride,
                  maxOccurences, maxThreads, flagOverCountedKmers,
                  ignoreNonUniqueKmers, crossover);

    fs::path index = "testOutput/Index_Test.fm9";
    _ftProps.addToIndexSet(index, 0);


    std::map<fs::path, uint> _indexSet = _ftProps._indexSet;
    for (auto index : _indexSet)
    {
        std::cout << "index " << index.first << std::endl;
    }
    std::cout << "number of indexes in indexSet " << _indexSet.size() << std::endl;
    std::cout << "number of indexes in ftProps  " << _ftProps.getNumOfIndexes() << std::endl;
    _indexPath = _indexSet.begin()->first;
    std::cout << "index loaded " << _indexPath << std::endl;
    ft::FTMap _ftMap(_ftProps);

    std::string kmer = "AATTACTGTGATATTTCTCATGTTCATCTTGGGCCTTATCTATTCCATCTAAAAATAGTACTTTCCTGATTCCAG";
    std::string kmer2 = "TTG";
    std::string kmer3 = "ATATT";
    _ftMap.addKmer(kmer);
    _ftMap.addKmer(kmer2);
    _ftMap.addKmer(kmer3);

    _finder.parallelSearch(_ftMap, _indexPath, offset);


    std::vector<std::map<std::string, ft::KmerClass>> results = _ftMap.getResults();
    EXPECT_EQ(results.size(), _ftProps.getNumOfIndexes());
    std::map<std::string, ft::KmerClass> result = results.front();
    EXPECT_EQ(result.size(), 3);
    uint roccs = result[kmer].getKPositions().size();
    uint roccs2 = result[kmer2].getKPositions().size();
    uint roccs3 = result[kmer3].getKPositions().size();

    csa_wt<wt_huff<rrr_vector<256>>, 512, 1024> _testindex;
    sdsl::load_from_file(_testindex, "testOutput/Index_Test.fm9");
    auto occs = sdsl::count(_testindex, kmer.begin(), kmer.end());
    auto occs2 = sdsl::count(_testindex, kmer2.begin(), kmer2.end());
    auto occs3 = sdsl::count(_testindex, kmer3.begin(), kmer3.end());
    EXPECT_EQ(occs, roccs);
    EXPECT_EQ(occs2, roccs2);
    EXPECT_EQ(occs3, roccs3);

}
//======================================================================
TEST_F(TestFinder, parallelSearch2)
{
    TEST_DESCRIPTION("parallel search single index, num kmers <= max threads ");
    //void parallelSearch(FTMap &ftMap,const fs::path &indexPath, long long offset);

    CreateIndex();
    Finder _finder;
    ft::FTProp _ftProps;
    maxThreads = 3;
    indexPropsFile = "testFiles/Test.ini";
    _ftProps.init(pathToQueryFile,kmerSize,readLength,
                  indexPropsFile,outputFolder,refOnly, revCompSearch,
                  searchType, multithread, overlap,
                  returnMatchesOnly, kmerCounts, stride,
                  maxOccurences, maxThreads, flagOverCountedKmers,
                  ignoreNonUniqueKmers, crossover);

    _ftProps.addToIndexSet("testOutput/Index_Test.fm9", 0);


    std::map<fs::path, uint> _indexSet = _ftProps._indexSet;
    std::cout << "number of indexes " << _indexSet.size() << std::endl;
    _indexPath = _indexSet.begin()->first;
    std::cout << "index loaded " << _indexPath << std::endl;
    ft::FTMap _ftMap(_ftProps);

    std::string kmer = "AATTACTGTGATATTTCTCATGTTCATCTTGGGCCTTATCTATTCCATCTAAAAATAGTACTTTCCTGATTCCAG";
    std::string kmer2 = "TTG";
    std::string kmer3 = "ATATT";
    _ftMap.addKmer(kmer);
    _ftMap.addKmer(kmer2);
    _ftMap.addKmer(kmer3);

    _finder.parallelSearch(_ftMap, _indexPath, offset);

    std::vector<std::map<std::string, ft::KmerClass>> results = _ftMap.getResults();
    EXPECT_EQ(results.size(), _ftProps.getNumOfIndexes());
    std::map<std::string, ft::KmerClass> result = results.front();
    EXPECT_EQ(result.size(), 3);
    uint roccs = result[kmer].getKPositions().size();
    uint roccs2 = result[kmer2].getKPositions().size();
    uint roccs3 = result[kmer3].getKPositions().size();

    csa_wt<wt_huff<rrr_vector<256>>, 512, 1024> _testindex;
    sdsl::load_from_file(_testindex, "testOutput/Index_Test.fm9");
    auto occs = sdsl::count(_testindex, kmer.begin(), kmer.end());
    auto occs2 = sdsl::count(_testindex, kmer2.begin(), kmer2.end());
    auto occs3 = sdsl::count(_testindex, kmer3.begin(), kmer3.end());
    EXPECT_EQ(occs, roccs);
    EXPECT_EQ(occs2, roccs2);
    EXPECT_EQ(occs3, roccs3);

}

//======================================================================
TEST_F(TestFinder, testIndex)
{
    //test the index can be loaded correctly
    CreateIndex();
    fs::path indexPath3 = fs::current_path() /= "testOutput/Index_Test.fm9";
    Finder _finder;
    ft::FTProp ftProps;


    fs::path indexPath1 = "/home/tixii/Git/OpenFlexTyper/build/testFiles/Test.fm9";
    fs::path indexPath2 = fs::absolute("testFiles/Test.fm9");

    std::string testkmer = "AAT";
    ftProps.printToStdOut("test kmer " + testkmer);

    csa_wt<wt_huff<rrr_vector<256>>, 512, 1024> _testindex1;
    sdsl::load_from_file(_testindex1, indexPath1);
    csa_wt<wt_huff<rrr_vector<256>>, 512, 1024> _testindex2;
    sdsl::load_from_file(_testindex2, indexPath2);
    csa_wt<wt_huff<rrr_vector<256>>, 512, 1024> _testindex3;
    sdsl::load_from_file(_testindex3, indexPath3);

    std::cout << "index 1 " << fs::absolute(indexPath1) << std::endl;
    std::cout << "index 2 " << fs::absolute(indexPath2) << std::endl;
    std::cout << "index 3 " << fs::absolute(indexPath3) << std::endl;

    size_t occ1 = sdsl::count(_testindex1, testkmer.begin(), testkmer.end());
    std::cout << "occs 1 count complete" << std::endl;
    size_t occ2 = sdsl::count(_testindex2, testkmer.begin(), testkmer.end());
    std::cout << "occs 2 count complete" << std::endl;
    size_t occ3 = sdsl::count(_testindex3, testkmer.begin(), testkmer.end());

    std::cout << "testkmer count ooc1 " << occ1 << " occ2 " << occ2 <<" occ3 " << occ3 << std::endl;

    auto locs2 = sdsl::locate(_testindex2, testkmer.begin(), testkmer.begin()+testkmer.length());
    std::cout << "locs 2 locate complete" << std::endl;
    auto locs3 = sdsl::locate(_testindex3, testkmer.begin(), testkmer.begin()+testkmer.length());
    std::cout << "locs 3 locate complete" << std::endl;
    auto locs1 = sdsl::locate(_testindex1, testkmer.begin(), testkmer.begin()+testkmer.length());
    std::cout << "testkmer locations locs1 " << locs1.size() << " locs2 " << locs2.size() << " locs3 " << locs3.size()<< std::endl;


};



}
