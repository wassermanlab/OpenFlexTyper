#include <gtest/gtest.h>
#include "utils.cpp"
#include <experimental/filesystem>

using namespace std;
using namespace ft;
namespace fs = experimental::filesystem;

namespace ft {
class TestUtils : public ::testing::Test {
protected:
    virtual void SetUp() {
        ofstream indexes("indices.txt");

        if (indexes.is_open()) {
            indexes << "test_index_1.fm9\n";
            indexes << "test_index_2.fm9\n";
        }
        indexes.close();
    }

    virtual void TearDown() {
    }

public:
    Utils _utils;
};

#define TEST_DESCRIPTION(desc) RecordProperty("description", desc)

//======================================================================
TEST_F(TestUtils, joinStringWithDelimiter)
{
    TEST_DESCRIPTION("Tests whether a string is join correctly ");
    std::set<std::string> inputSetOfStr= {"A", "B", "C"};
    std::string inputDelimeter = "+";
    std::string expectedOutput ("A+B+C");
    string output = _utils.joinString(inputSetOfStr, inputDelimeter);
    EXPECT_EQ(output, expectedOutput);
}
//======================================================================
TEST_F(TestUtils, joinStringNoDelimiter)
{
    TEST_DESCRIPTION("Tests whether a string is join correctly ");
    std::set<std::string> inputSetOfStr= {"A", "B", "C"};
    std::string expectedOutput ("A, B, C");
    string output = _utils.joinString(inputSetOfStr);
    EXPECT_EQ(output, expectedOutput);
}

//======================================================================
TEST_F(TestUtils, split)
{
    TEST_DESCRIPTION("Tests whether a string is split correctly");
    char delimiter = '+';
    string input ("A+B+C");
    std::vector<std::string> expectedOutput ={"A", "B", "C"};
    std::vector<std::string> output = _utils.split(input, delimiter);
    EXPECT_EQ(output, expectedOutput);
}
//======================================================================
TEST_F(TestUtils, splitWrongDelimiter)
{
    TEST_DESCRIPTION("Tests whether a string is split correctly");
    char delimiter = ',';
    string input ("A+B+C");
    std::vector<std::string> expectedOutput ={"A+B+C"};
    std::vector<std::string> output = _utils.split(input, delimiter);
    EXPECT_EQ(output, expectedOutput);
}

//======================================================================
TEST_F(TestUtils, reverseCompliment)
{
    TEST_DESCRIPTION("Tests the capacity to find the reverse compliment"
                     "The result was checked with : "
                     "https://www.bioinformatics.org/sms/rev_comp.html");

    string input ("ATTTTTTTTTTTGGGGGGGGGGGGGGGGGG");
    string expectedOutput ("CCCCCCCCCCCCCCCCCCAAAAAAAAAAAT");
    string output = _utils.reverseComplement(input);

    EXPECT_EQ(output, expectedOutput);
}

//======================================================================
TEST_F(TestUtils, reverseComplimentWithBadNucleotide)
{
    TEST_DESCRIPTION("Tests the capacity to find the reverse compliment"
                     "The result was checked with : "
                     "https://www.bioinformatics.org/sms/rev_comp.html");

    string input ("ATTTTTTTTTTTGGGGGGGGGGGGGGGGGGB");
    string expectedOutput ("");
    string output = _utils.reverseComplement(input);

    EXPECT_EQ(output, expectedOutput);
}

}
