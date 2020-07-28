#include <gtest/gtest.h>

#include "ftPropsClass.cpp"

#include <fstream>
#include <climits>

using namespace std;

namespace ft {
class TestFTProps : public ::testing::Test {
protected:
    virtual void SetUp() {}
    virtual void TearDown() {}

public:

};
#define TEST_DESCRIPTION(desc) RecordProperty("description", desc)
//ft::FTProp* TestFTMap::_ftProps = new ft::FTProp();

//======================================================================
TEST_F(TestFTProps, TestCheckKmer)
{
    TEST_DESCRIPTION("Check Kmer");



}

}
