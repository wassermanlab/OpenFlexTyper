#include <gtest/gtest.h>
#include "kmergenerator.cpp"
#include "queryextractor.h"
#include <climits>

using namespace std;

namespace ft {
class TestKmerGenerator : public ::testing::Test {
protected:
    virtual void SetUp() {
    }

    virtual void TeadDown() {
    }

public:
    KmerGenerator _kmerGenerator;
};

#define TEST_DESCRIPTION(desc) RecordProperty("description", desc)

//======================================================================
TEST_F(TestKmerGenerator, genSlidingSearchStrings)
{
    TEST_DESCRIPTION("genSlidingSearchStrings");
    //input: const std::string& queryString, uint kmerSize, uint stride, bool kmerCounts, uint maxKmers
    std::set<std::string> result;
    std::set<std::string> expectedResult;

    EXPECT_EQ(result, expectedResult);
}

//======================================================================
TEST_F(TestKmerGenerator, genCenteredSearchStrings)
{
    TEST_DESCRIPTION("genCenteredSearchStrings");
    //input: const std::string& queryString, uint kmerSize, uint overlap, uint stride, bool kmerCounts, uint maxKmers
    std::set<std::string> result;
    std::set<std::string> expectedResult;

    EXPECT_EQ(result, expectedResult);
}
//======================================================================
TEST_F(TestKmerGenerator, genQueryClassKmers)
{
    TEST_DESCRIPTION("genQueryClassKmers");
    //input: QueryClass KmerGenerator::genQueryClassKmers(int queryID, std::string querystring, ft::QueryType queryType, SearchType searchType, uint kmerSize, uint overlap,
    //uint stride, bool kmerCounts, uint maxKmers)
    QueryClass result(1, ft::QueryType::REF);
    QueryClass expectedResult(1, ft::QueryType::REF);

    //EXPECT_EQ(result, expectedResult);
}
//======================================================================
TEST_F(TestKmerGenerator, genSearchKmers)
{
    TEST_DESCRIPTION("genSearchKmers");
    //input: std::set<QueryClass> KmerGenerator::genSearchKmers(std::set<Query>& inputQueries, ft::FTMap& ftMap)
    std::set<QueryClass> result;
    std::set<QueryClass> expectedResult;

    //EXPECT_EQ(result, expectedResult);
}

//======================================================================
TEST_F(TestKmerGenerator, addQueriestoKmerMap)
{
    TEST_DESCRIPTION("addQueriestoKmerMap");
    //KmerGenerator::addQueriestoKmerMap(ft::FTMap& ftMap, const std::set<QueryClass>& queryMap)

    std::set<QueryClass> result;
    std::set<QueryClass> expectedResult;

    //EXPECT_EQ(result, expectedResult);
}
//======================================================================
TEST_F(TestKmerGenerator, genKmerMap)
{
    TEST_DESCRIPTION("genKmerMap");
    //void KmerGenerator::genKmerMap(std::set<Query>& inputQueries, ft::FTMap& ftMap)

    std::set<QueryClass> result;
    std::set<QueryClass> expectedResult;

    //EXPECT_EQ(result, expectedResult);
}



////======================================================================
//TEST_F(TestKmerGenerator, TestCrossOver_0)
//{
//    TEST_DESCRIPTION("TestCrossoverSearch::TestCrossOverSequenceCreation_1"
//                     "This test checks that when we have Ref and Alt sequences, the "
//                     "crossover sequence are created");


//    std::set<Query> querySet{{ 2, "AATAAAACCGGTTA", "AATTTTTTTTTTTA", "AATAAAATTTTTTA" }};

//    uint        kmerSize  = 5;
//    bool         refOnly   = false;
//    SearchType   searchType = "CENTERED";
//    uint        overlap    = 1;
//    uint        stride     = 1;
//    bool         kmerCounts = false;

//    ft::KmerGenerator kmerGeneratorObj;
//    Query myQuery = *querySet.begin();

//    SearchKmers ret = kmerGeneratorObj.genQueryKmers(myQuery, kmerSize, refOnly, searchType, overlap, stride, crossover, kmerCounts, INT_MAX);

//    SearchKmers expectedRet {{{2, QueryType::REF}, { "AAACC", "AACCG" }},
//                             {{2, QueryType::ALT}, { "TTTTT" }},
//                             {{2, QueryType::CRO}, { "AAATT", "AATTT" }}};

//    EXPECT_EQ(ret, expectedRet);
//}

////======================================================================
//TEST_F(TestKmerGenerator, TestCrossOver_1)
//{
//    TEST_DESCRIPTION("TestCrossoverSearch::TestCrossOverSequenceCreation_1"
//                     "This test checks that when we have Ref and Alt sequences, the "
//                     "crossover sequence are created");

//    QueryExtractor obj;
//    std::string startPointRef = "AAAAAAAAAATTTTTTTTTTCCCCCCCCCCGGGGGGGGGG";
//    std::string endPointRef   = "TTTTTTTTTTCCCCCCCCCCGGGGGGGGGGAAAAAAAAAA";
//    bool crossover          = true;
//    uint fileIndex         = 1;
//    std::set<Query> results;
//    obj.getStartAndEndPointSequences(startPointRef, endPointRef, fileIndex, results);
//    std::set<Query> expectedResults {{ 2, "AAAAAAAAAATTTTTTTTTTCCCCCCCCCCGGGGGGGGGG",
//                                          "TTTTTTTTTTCCCCCCCCCCGGGGGGGGGGAAAAAAAAAA",
//                                          "AAAAAAAAAATTTTTTTTTTGGGGGGGGGGAAAAAAAAAA"
//                                     }};

//    EXPECT_EQ(results, expectedResults);

//    uint        kmerSize  = 10;
//    bool         refOnly   = false;
//    SearchType   searchType = "CENTERED";
//    uint        overlap    = 1;
//    uint        stride     = 1;
//    bool         kmerCounts = false;

//    ft::KmerGenerator kmerGeneratorObj;
//    Query myQuery = *results.begin();

//    SearchKmers ret = kmerGeneratorObj.genQueryKmers(myQuery, kmerSize, refOnly, searchType, overlap, stride, crossover, kmerCounts, INT_MAX);

//    SearchKmers expectedRet {{{2, QueryType::REF}, { "TTCCCCCCCC", "TTTCCCCCCC", "TTTTCCCCCC", "TTTTTCCCCC", "TTTTTTCCCC", "TTTTTTTCCC", "TTTTTTTTCC" }},
//                             {{2, QueryType::ALT}, { "CCCCCCCCGG", "CCCCCCCGGG", "CCCCCCGGGG", "CCCCCGGGGG", "CCCCGGGGGG", "CCCGGGGGGG", "CCGGGGGGGG" }},
//                             {{2, QueryType::CRO}, { "TTGGGGGGGG", "TTTGGGGGGG", "TTTTGGGGGG", "TTTTTGGGGG", "TTTTTTGGGG", "TTTTTTTGGG", "TTTTTTTTGG" }}};

//    EXPECT_EQ(ret, expectedRet);
//}

////======================================================================
//TEST_F(TestKmerGenerator, TestCrossOverBiggerStride)
//{
//    TEST_DESCRIPTION("TestCrossoverSearch::TestCrossOverSequenceCreation_1"
//                     "This test checks that when we have Ref and Alt sequences, the "
//                     "crossover sequence are created");

//    QueryExtractor obj;
//    std::string startPointRef = "AAAAAAAAAATTTTTTTTTTCCCCCCCCCCGGGGGGGGGG";
//    std::string endPointRef   = "TTTTTTTTTTCCCCCCCCCCGGGGGGGGGGAAAAAAAAAA";
//    bool crossover          = true;
//    uint fileIndex         = 1;
//    std::set<Query> results;
//    obj.getStartAndEndPointSequences(startPointRef, endPointRef, fileIndex, results);
//    std::set<Query> expectedResults {{ 2, "AAAAAAAAAATTTTTTTTTTCCCCCCCCCCGGGGGGGGGG",
//                                          "TTTTTTTTTTCCCCCCCCCCGGGGGGGGGGAAAAAAAAAA",
//                                          "AAAAAAAAAATTTTTTTTTTGGGGGGGGGGAAAAAAAAAA"
//                                     }};

//    EXPECT_EQ(results, expectedResults);

//    uint        kmerSize  = 10;
//    bool         refOnly   = false;
//    SearchType   searchType = "CENTERED";
//    uint        overlap    = 1;
//    uint        stride     = 3;
//    bool         kmerCounts = false;

//    ft::KmerGenerator kmerGeneratorObj;
//    Query myQuery = *results.begin();

//    SearchKmers ret = kmerGeneratorObj.genQueryKmers(myQuery, kmerSize, refOnly, searchType, overlap, stride, crossover, kmerCounts, INT_MAX);

//    SearchKmers expectedRet {{{2, QueryType::REF}, { "TTCCCCCCCC", "TTTTTCCCCC", "TTTTTTTTCC" }},
//                             {{2, QueryType::ALT}, { "CCCCCCCCGG", "CCCCCGGGGG", "CCGGGGGGGG" }},
//                             {{2, QueryType::CRO}, { "TTGGGGGGGG", "TTTTTGGGGG", "TTTTTTTTGG" }}};

//    EXPECT_EQ(ret, expectedRet);
//}

////======================================================================
//TEST_F(TestKmerGenerator, TestCrossOverBiggerOverlap_0)
//{
//    TEST_DESCRIPTION("TestCrossoverSearch::TestCrossOverSequenceCreation_1"
//                     "This test checks that when we have Ref and Alt sequences, the "
//                     "crossover sequence are created");

//    QueryExtractor obj;
//    std::string startPointRef = "AAAAAAAAAATTTTTTTTTTCCCCCCCCCCGGGGGGGGGG";
//    std::string endPointRef   = "TTTTTTTTTTCCCCCCCCCCGGGGGGGGGGAAAAAAAAAA";
//    bool crossover          = true;
//    uint fileIndex         = 1;
//    std::set<Query> results;
//    obj.getStartAndEndPointSequences(startPointRef, endPointRef, fileIndex, results);
//    std::set<Query> expectedResults {{ 2, "AAAAAAAAAATTTTTTTTTTCCCCCCCCCCGGGGGGGGGG",
//                                          "TTTTTTTTTTCCCCCCCCCCGGGGGGGGGGAAAAAAAAAA",
//                                          "AAAAAAAAAATTTTTTTTTTGGGGGGGGGGAAAAAAAAAA"
//                                     }};

//    EXPECT_EQ(results, expectedResults);

//    uint        kmerSize  = 10;
//    bool         refOnly   = false;
//    SearchType   searchType = "CENTERED";
//    uint        overlap    = 3;
//    uint        stride     = 1;
//    bool         kmerCounts = false;

//    ft::KmerGenerator kmerGeneratorObj;
//    Query myQuery = *results.begin();

//    SearchKmers ret = kmerGeneratorObj.genQueryKmers(myQuery, kmerSize, refOnly, searchType, overlap, stride, crossover, kmerCounts, INT_MAX);

//    SearchKmers expectedRet {{{2, QueryType::REF}, { "TTTTCCCCCC", "TTTTTCCCCC", "TTTTTTCCCC" }},
//                             {{2, QueryType::ALT}, { "CCCCCCGGGG", "CCCCCGGGGG", "CCCCGGGGGG" }},
//                             {{2, QueryType::CRO}, { "TTTTGGGGGG", "TTTTTGGGGG", "TTTTTTGGGG" }}};

//    EXPECT_EQ(ret, expectedRet);
//}

////======================================================================
//TEST_F(TestKmerGenerator, TestCrossOverBiggerOverlap_1)
//{
//    TEST_DESCRIPTION("TestCrossoverSearch::TestCrossOverSequenceCreation_1"
//                     "This test checks that when we have Ref and Alt sequences, the "
//                     "crossover sequence are created");

//    QueryExtractor obj;
//    std::string startPointRef = "AAAAAAAAAATTTTTTTTTTCCCCCCCCCCGGGGGGGGGG";
//    std::string endPointRef   = "TTTTTTTTTTCCCCCCCCCCGGGGGGGGGGAAAAAAAAAA";
//    bool crossover          = true;
//    uint fileIndex         = 1;
//    std::set<Query> results;
//    obj.getStartAndEndPointSequences(startPointRef, endPointRef, fileIndex, results);
//    std::set<Query> expectedResults {{ 2, "AAAAAAAAAATTTTTTTTTTCCCCCCCCCCGGGGGGGGGG",
//                                          "TTTTTTTTTTCCCCCCCCCCGGGGGGGGGGAAAAAAAAAA",
//                                          "AAAAAAAAAATTTTTTTTTTGGGGGGGGGGAAAAAAAAAA"
//                                     }};

//    EXPECT_EQ(results, expectedResults);

//    uint        kmerSize  = 10;
//    bool         refOnly   = false;
//    SearchType   searchType = "CENTERED";
//    uint        overlap    = 1;
//    uint        stride     = 1;
//    bool         kmerCounts = false;

//    ft::KmerGenerator kmerGeneratorObj;
//    Query myQuery = *results.begin();

//    SearchKmers ret = kmerGeneratorObj.genQueryKmers(myQuery, kmerSize, refOnly, searchType, overlap, stride, crossover, kmerCounts, INT_MAX);

//    SearchKmers expectedRet {{{2, QueryType::REF}, { "TTCCCCCCCC", "TTTCCCCCCC", "TTTTCCCCCC", "TTTTTCCCCC", "TTTTTTCCCC", "TTTTTTTCCC", "TTTTTTTTCC" }},
//                             {{2, QueryType::ALT}, { "CCCCCCCCGG", "CCCCCCCGGG", "CCCCCCGGGG", "CCCCCGGGGG", "CCCCGGGGGG", "CCCGGGGGGG", "CCGGGGGGGG" }},
//                             {{2, QueryType::CRO}, { "TTGGGGGGGG", "TTTGGGGGGG", "TTTTGGGGGG", "TTTTTGGGGG", "TTTTTTGGGG", "TTTTTTTGGG", "TTTTTTTTGG" }}};

//    EXPECT_EQ(ret, expectedRet);
//}

////======================================================================
//TEST_F(TestKmerGenerator, TestCrossOverSequenceCreation_0)
//{
//    TEST_DESCRIPTION("TestCrossoverSearch::TestCrossOverSequenceCreation_1"
//                     "This test checks that when we have Ref and Alt sequences, the "
//                     "crossover sequence are created");
//    QueryExtractor obj;
//    std::string startPointRef = "AAAAAAAA";
//    std::string endPointRef = "TTTTTTTT";
//    uint fileIndex         = 1;
//    std::set<Query> results;
//    obj.getStartAndEndPointSequences(startPointRef, endPointRef, fileIndex, results);
//    std::set<Query> expectedResults {{ 2, "AAAAAAAA", "TTTTTTTT", "AAAATTTT" }};

//    EXPECT_EQ(results, expectedResults);
//}

////======================================================================
//TEST_F(TestKmerGenerator, TestCrossOverSequenceCreation_1)
//{
//    TEST_DESCRIPTION("TestCrossoverSearch::TestCrossOverSequenceCreation_1"
//                     "This test checks that when we have Ref and Alt sequences, the "
//                     "crossover sequence are created");
//    QueryExtractor obj;
//    std::string startPointRef = "AAAAAAAA";
//    std::string endPointRef   = "CCCCCCCC";
//    uint fileIndex         = 1;
//    std::set<Query> results;
//    obj.getStartAndEndPointSequences(startPointRef, endPointRef, fileIndex, results);
//    std::set<Query> expectedResults {{ 2, "AAAAAAAA", "CCCCCCCC", "AAAACCCC" }};

//    EXPECT_EQ(results, expectedResults);
//}

////======================================================================
//TEST_F(TestKmerGenerator, TestGenCenteredSearchStrings_overlap_00) {
//    TEST_DESCRIPTION("TestFmSearch::TestGenCenteredSearchStrings"
//                     "This function test that the kmers match expected kmers"
//                     "The test will fail if return kmers are wrong");

//    ft::KmerGenerator obj;
//    string queryString ("AAAATCGGGG");
//    unsigned int kmerSize = 5;
//    unsigned int overlap  = 0;
//    unsigned int stride   = 1;
//    bool         kmerCounts = false;

//    auto result = obj.genCenteredSearchStrings(queryString, kmerSize, overlap, stride, kmerCounts, INT_MAX);
//    set<string> expectedResult { "AAATC",
//                                 "AATCG",
//                                 "ATCGG",
//                                 "TCGGG"
//                               };

//    EXPECT_EQ(result, expectedResult);
//}

////======================================================================
//TEST_F(TestKmerGenerator, TestGenCenteredSearchStrings_overlap_01) {
//    TEST_DESCRIPTION("TestFmSearch::TestGenCenteredSearchStrings"
//                     "This function test that the kmers match expected kmers"
//                     "The test will fail if return kmers are wrong");

//    ft::KmerGenerator obj;
//    string queryString ("AAAAATCCCCC");
//    unsigned int kmerSize = 5;
//    unsigned int overlap  = 0;
//    unsigned int stride   = 1;
//    bool         kmerCounts = false;

//    auto result = obj.genCenteredSearchStrings(queryString, kmerSize, overlap, stride, kmerCounts, INT_MAX);
//    set<string> expectedResult {
//                                 "AAAAT",
//                                 "AAATC",
//                                 "AATCC",
//                                 "ATCCC",
//                                 "TCCCC"
//                               };

//    EXPECT_EQ(result, expectedResult);
//}

////======================================================================
//TEST_F(TestKmerGenerator, TestGenCenteredSearchStrings_overlap_10) {
//    TEST_DESCRIPTION("TestFmSearch::TestGenCenteredSearchStrings"
//                     "This function test that the kmers match expected kmers"
//                     "The test will fail if return kmers are wrong");

//    ft::KmerGenerator obj;
//    string queryString ("AAAATCGGGG");
//    unsigned int kmerSize = 5;
//    unsigned int overlap  = 1;
//    unsigned int stride   = 1;
//    bool         kmerCounts = false;

//    auto result = obj.genCenteredSearchStrings(queryString, kmerSize, overlap, stride, kmerCounts, INT_MAX);
//    set<string> expectedResult { "AATCG",
//                                 "ATCGG"
//                               };

//    EXPECT_EQ(result, expectedResult);
//}

////======================================================================
//TEST_F(TestKmerGenerator, TestStartEndPositions ) {
//    TEST_DESCRIPTION("TestFmSearch::TestStartEndPositions"
//                     "This function test that the start and end positions"
//                     "The test will fail if they are wrong");

//    string queryString_1 ("AAAATGGGG");
//    string queryString_2 ("AAAATCGGGG");

//    size_t querylen_1 = queryString_1.length();
//    size_t varStart_1 = floor((double(querylen_1) - 1) / 2);
//    size_t varEnd_1   = ceil ((double(querylen_1) - 1) / 2);

//    size_t querylen_2 = queryString_2.length();
//    size_t varStart_2 = floor((double(querylen_2) - 1) / 2);
//    size_t varEnd_2   = ceil ((double(querylen_2) - 1) / 2);


//    vector<size_t> result { querylen_1, varStart_1, varEnd_1, querylen_2, varStart_2, varEnd_2
//                               };
//    vector<size_t> expectedResult {9, 4, 4, 10, 4 , 5 };


//    EXPECT_EQ(result, expectedResult);
//}

////======================================================================
//TEST_F(TestKmerGenerator, TestProbabilisticParamDisabled) {
//    TEST_DESCRIPTION("TestProbabilisticSearch::TestProbabilisticParamDisabled"
//                     "This test checks that when the 'ignore non unique Kmer option' is"
//                     "disabled, the repeated kmers ARE NOT deleted from the KmerMap");

//    std::set<Query> inputQueries {{1, "AAAAAT", ".", "." },
//                                  {2, "AAAAAC", ".", "." },
//                                  {3, "AAAAAG", ".", "." }};
//    uint kmerSize            = 6;
//    bool refOnly              = true;
//    SearchType searchType     = "SLIDING";
//    KmerMap kmerMap           = {};
//    uint overlap             = 0;
//    uint stride              = 1;
//    bool ignoreNonUniqueKmers = false;
//    bool crossover            = false;
//    bool         kmerCounts   = false;

//    KmerGenerator obj;
//    obj.genKmerMap(inputQueries, kmerSize, refOnly, searchType, kmerMap, overlap, stride, crossover, ignoreNonUniqueKmers, kmerCounts, INT_MAX, INT_MAX);

//    std::pair<std::set<ft::QIdT>,std::set<ft::FlagType>> result = {{{3, ft::QueryType::REF}}, {{}}};

//    KmerMap expectedKmerMap {{"AAAAAC", {{{2, ft::QueryType::REF}}, {{}}}},
//                             {"AAAAAG", {{{3, ft::QueryType::REF}}, {{}}}},
//                            {"AAAAAT", {{{1, ft::QueryType::REF}}, {{}}}}};
//    EXPECT_EQ(kmerMap, expectedKmerMap);
//}

////======================================================================
//TEST_F(TestKmerGenerator, TestProbabilisticParamEnabled) {
//    TEST_DESCRIPTION("TestProbabilisticSearch::TestProbabilisticParamEnabled"
//                     "This test checks that when the 'ignore non unique Kmer option' is"
//                     "enabled, the repeated kmers ARE deleted from the KmerMap");

//    std::set<Query> inputQueries {{1, "AAAAAAT", ".", "."},
//                                  {2, "AAAAAAC", ".", "."},
//                                  {3, "AAAAAAG", ".", "."}};
//    uint kmerSize            = 6;
//    bool refOnly              = true;
//    SearchType searchType     = "SLIDING";
//    KmerMap kmerMap           = {};
//    uint overlap             = 0;
//    uint stride              = 1;
//    bool ignoreNonUniqueKmers = true;
//    bool crossover            = false;
//    bool         kmerCounts   = false;

//    KmerGenerator obj;
//    obj.genKmerMap(inputQueries, kmerSize, refOnly, searchType, kmerMap, overlap, stride, crossover, ignoreNonUniqueKmers, kmerCounts, INT_MAX, INT_MAX);

//    KmerMap expectedKmerMap {{"AAAAAC", {{{2, ft::QueryType::REF}}, {{}}}},
//                             {"AAAAAG", {{{3, ft::QueryType::REF}}, {{}}}},
//                            {"AAAAAT", {{{1, ft::QueryType::REF}}, {{}}}}};
//    EXPECT_EQ(kmerMap, expectedKmerMap);
//}

////======================================================================
//TEST_F(TestKmerGenerator, TestProbabilisticParamEnabledLongQuery) {
//    TEST_DESCRIPTION("TestProbabilisticSearch::TestProbabilisticParamEnabled"
//                     "This test checks that when the 'ignore non unique Kmer option' is"
//                     "enabled, the repeated kmers ARE deleted from the KmerMap");

//    std::set<Query> inputQueries {{1, "CTAGCTGCATCGATCGATCGATCGTACGAAAAAATAAAAAACAAAAAATGGGGGCCCTTTTTACAAAAAATAAAAAACAAAAAATGGGGTTGTC", ".", "."}};
//    uint kmerSize            = 6;
//    bool refOnly              = true;
//    SearchType searchType     = "SLIDING";
//    KmerMap kmerMap           = {};
//    uint overlap             = 0;
//    uint stride              = 3;
//    bool ignoreNonUniqueKmers = true;
//    bool crossover            = false;
//    bool         kmerCounts   = false;

//    KmerGenerator obj;
//    obj.genKmerMap(inputQueries, kmerSize, refOnly, searchType, kmerMap, overlap, stride, crossover, ignoreNonUniqueKmers, kmerCounts, INT_MAX, INT_MAX);

//    // notice that kmers are appearing as they are created
//    // They are ordered lexicographycally.



//    KmerMap expectedKmerMap {{ {"AAAAAA", { {{1, ft::QueryType::REF}},{{}} } },
//                               {"AAAAAC", { {{1, ft::QueryType::REF}},{{}} } },
//                               {"AAAATA", { {{1, ft::QueryType::REF}},{{}} } },
//                               {"AAATGG", { {{1, ft::QueryType::REF}},{{}} } },
//                               {"AACAAA", { {{1, ft::QueryType::REF}},{{}} } },
//                               {"ATAAAA", { {{1, ft::QueryType::REF}},{{}} } },
//                               {"ATCGAT", { {{1, ft::QueryType::REF}},{{}} } },
//                               {"CAAAAA", { {{1, ft::QueryType::REF}},{{}} } },
//                               {"CCCTTT", { {{1, ft::QueryType::REF}},{{}} } },
//                               {"CGATCG", { {{1, ft::QueryType::REF}},{{}} } },
//                               {"CTAGCT", { {{1, ft::QueryType::REF}},{{}} } },
//                               {"GAAAAA", { {{1, ft::QueryType::REF}},{{}} } },
//                               {"GATCGA", { {{1, ft::QueryType::REF}},{{}} } },
//                               {"GCATCG", { {{1, ft::QueryType::REF}},{{}} } },
//                               {"GCTGCA", { {{1, ft::QueryType::REF}},{{}} } },
//                               {"GGGCCC", { {{1, ft::QueryType::REF}},{{}} } },
//                               {"GGTTGT", { {{1, ft::QueryType::REF}},{{}} } },
//                               {"TACGAA", { {{1, ft::QueryType::REF}},{{}} } },
//                               {"TCGATC", { {{1, ft::QueryType::REF}},{{}} } },
//                               {"TCGTAC", { {{1, ft::QueryType::REF}},{{}} } },
//                               {"TGGGGG", { {{1, ft::QueryType::REF}},{{}} } },
//                               {"TGGGGT", { {{1, ft::QueryType::REF}},{{}} } },
//                               {"TTACAA", { {{1, ft::QueryType::REF}},{{}} } },
//                               {"TTTTTA", { {{1, ft::QueryType::REF}},{{}} } }}};

//    EXPECT_EQ(kmerMap, expectedKmerMap);
//}
}
