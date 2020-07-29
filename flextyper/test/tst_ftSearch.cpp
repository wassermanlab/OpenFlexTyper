#include <gtest/gtest.h>
#include <sdsl/suffix_arrays.hpp>
#include "ftSearch.cpp"


using namespace std;
using namespace ft;
using namespace algo;
using namespace sdsl;

namespace ft {
class TestFTSearch : public ::testing::Test {
protected:
    virtual void SetUp() {}
    virtual void TearDown() {}

public:

};

#define TEST_DESCRIPTION(desc) RecordProperty("description", desc)


//======================================================================
TEST_F(TestFTSearch, ftSearchEntirePipeline)
{
    TEST_DESCRIPTION("This test checks createFMIndex");
    ft::FTProp props;
    props.initFromQSettings("testFiles/Test_Settings.ini", true);
    ft::FTSearch *ftSearch = new ft::FTSearch();
    ftSearch->init(props);

    EXPECT_NO_THROW();

}

}
