#include <gtest/gtest.h>
#include "kmergenerator.cpp"
#include "ftKPropsClass.cpp"
#include <climits>

using namespace std;

namespace ft {
class TestKmerGenerator : public ::testing::Test {
protected:
    virtual void SetUp() {

    }

    virtual void TearDown() {
    }

public:

};

#define TEST_DESCRIPTION(desc) RecordProperty("description", desc)

//======================================================================
TEST_F(TestKmerGenerator, genSlidingSearchStrings)
{
    TEST_DESCRIPTION("genSlidingSearchStrings");

    ft::KmerProperties* _kProps = new KmerProperties();
    uint _kmerSize = 5;
    bool _refOnly = true;
    SearchType _searchType = SLIDING;
    uint _overlap = 0;
    uint _stride = 1;
    bool _kmerCounts = false;
    uint _maxKmers  = 30;
    _kProps->setKmerSize(_kmerSize);
    _kProps->setRefOnly(_refOnly);
    _kProps->setSearchType(_searchType);
    _kProps->setStride(_stride);
    _kProps->setOverlap(_overlap);
    _kProps->setKmerCountsFlag(_kmerCounts);
    _kProps->setMaxKmers(_maxKmers);
    KmerGenerator _kmerGenerator(*_kProps);

    std::string queryString = "AAAAATCCCCC";

    std::set<std::string> expectedResult = {"AAAAA", "AAAAT", "AAATC", "AATCC", "ATCCC", "TCCCC", "CCCCC"};
    std::set<std::string> results = _kmerGenerator.genSlidingSearchStrings(queryString);

    EXPECT_EQ(results, expectedResult);
}

////======================================================================
//TEST_F(TestKmerGenerator, genCenteredSearchStrings)
//{
//    TEST_DESCRIPTION("genCenteredSearchStrings");

//    ft::FTProp ftprops;
//    ft::KmerProperties* _kProps = new KmerProperties(ftprops);
//    uint _kmerSize = 5;
//    bool _refOnly = true;
//    SearchType _searchType = CENTERED;
//    uint _overlap = 1;
//    uint _stride = 1;
//    bool _kmerCounts = false;
//    uint _maxKmers  = 30;
//    _kProps->setKmerSize(_kmerSize);
//    _kProps->setRefOnly(_refOnly);
//    _kProps->setSearchType(_searchType);
//    _kProps->setStride(_stride);
//    _kProps->setOverlap(_overlap);
//    _kProps->setKmerCountsFlag(_kmerCounts);
//    _kProps->setMaxKmers(_maxKmers);
//    KmerGenerator _kmerGenerator(*_kProps);


//    //input: const std::string& queryString, uint kmerSize, uint overlap, uint stride, bool kmerCounts, uint maxKmers
//    std::string queryString = "AAAAATCCCCC";

//    std::set<std::string> expectedResults = {"AAAAT", "AAATC", "AATCC", "ATCCC", "TCCCC"};
//    std::set<std::string> results = _kmerGenerator.genCenteredSearchStrings(queryString);
//;
//    EXPECT_EQ(results, expectedResults);
//}

////======================================================================
//TEST_F(TestKmerGenerator, genSearchKmers)
//{
//    TEST_DESCRIPTION("genSearchKmers");

//    //input: std::set<std::string> genSearchKmers(const ft::QueryClass& queryObj);
//    ft::FTProp ftprops;
//    ft::KmerProperties* _kProps = new KmerProperties(ftprops);
//    uint _kmerSize = 5;
//    bool _refOnly = true;
//    SearchType _searchType = CENTERED;
//    uint _overlap = 1;
//    uint _stride = 1;
//    bool _kmerCounts = false;
//    uint _maxKmers  = 30;
//    _kProps->setKmerSize(_kmerSize);
//    _kProps->setRefOnly(_refOnly);
//    _kProps->setSearchType(_searchType);
//    _kProps->setStride(_stride);
//    _kProps->setOverlap(_overlap);
//    _kProps->setKmerCountsFlag(_kmerCounts);
//    _kProps->setMaxKmers(_maxKmers);
//    KmerGenerator _kmerGenerator(*_kProps);

//    std::set<std::string> result;
//    std::set<std::string> expectedResult;

//    EXPECT_EQ(result, expectedResult);
//}


}
