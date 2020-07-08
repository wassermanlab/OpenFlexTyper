#include <gtest/gtest.h>
#include <climits>
#include "indexPropsClass.h"


using namespace std;

namespace algo {

class TestIndexProp : public ::testing::Test {
protected:
    virtual void SetUp() {

    }

    virtual void TearDown() {
    }

public:

};
#define TEST_DESCRIPTION(desc) RecordProperty("description", desc)

//======================================================================
TEST_F(TestIndexProp, createBash1)
{
    TEST_DESCRIPTION("test create bash function");

    algo::IndexProps* _indexProp = new algo::IndexProps();
    _indexProp->setR1("test.fq");
    _indexProp->setOutputFile("output");
    _indexProp->setOutputFolder(".");
    _indexProp->setBuildDir("../build");

    std::string expectedBash = "bash preprocess.sh -r test.fq -o . -f output -u ../build/bin/";
    std::string outputBash = _indexProp->createBash();

    EXPECT_EQ(expectedBash, outputBash);

}



}
