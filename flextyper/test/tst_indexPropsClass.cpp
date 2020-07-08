#include <gtest/gtest.h>
#include <climits>
#include "indexPropsClass.cpp"
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
//======================================================================
TEST_F(TestIndexProp, createBash2)
{
    TEST_DESCRIPTION("test create bash function");

    algo::IndexProps* _indexProp = new algo::IndexProps();
    _indexProp->setR1("/reads/test.fq");
    _indexProp->setOutputFile("output");
    _indexProp->setOutputFolder("../");
    _indexProp->setBuildDir("../build");

    std::string expectedBash = "bash preprocess.sh -r /reads/test.fq -o ../ -f output -u ../build/bin/";
    std::string outputBash = _indexProp->createBash();

    EXPECT_EQ(expectedBash, outputBash);

}
//======================================================================
TEST_F(TestIndexProp, createBash_withUnzip)
{
    TEST_DESCRIPTION("test create bash function");

    algo::IndexProps* _indexProp = new algo::IndexProps();
    _indexProp->setR1("test.fq.gz");
    _indexProp->setOutputFile("output");
    _indexProp->setOutputFolder(".");
    _indexProp->setBuildDir("../build");
    _indexProp->setReadFileType(algo::FileType::GZ);

    std::string expectedBash = "bash preprocess.sh -r test.fq.gz -o . -f output -u ../build/bin/ -z 1" ;
    std::string outputBash = _indexProp->createBash();

    EXPECT_EQ(expectedBash, outputBash);

}
//======================================================================
TEST_F(TestIndexProp, createBash_withPair)
{
    TEST_DESCRIPTION("test create bash function");

    algo::IndexProps* _indexProp = new algo::IndexProps();
    _indexProp->setR1("test_R1.fq");
    _indexProp->setR2("test_R2.fq");
    _indexProp->setPairedReadsFlag(true);
    _indexProp->setOutputFile("output");
    _indexProp->setOutputFolder(".");
    _indexProp->setBuildDir("../build");

    std::string expectedBash = "bash preprocess.sh -r test_R1.fq -o . -f output -u ../build/bin/ -p test_R2.fq";
    std::string outputBash = _indexProp->createBash();

    EXPECT_EQ(expectedBash, outputBash);

}
//======================================================================
TEST_F(TestIndexProp, createBash_withRevComp)
{
    TEST_DESCRIPTION("test create bash function");

    algo::IndexProps* _indexProp = new algo::IndexProps();
    _indexProp->setR1("test.fq");
    _indexProp->setOutputFile("output");
    _indexProp->setOutputFolder(".");
    _indexProp->setBuildDir("../build");
    _indexProp->setRevCompFlag(true);

    std::string expectedBash = "bash preprocess.sh -r test.fq -o . -f output -u ../build/bin/ -c 1";
    std::string outputBash = _indexProp->createBash();

    EXPECT_EQ(expectedBash, outputBash);

}
//======================================================================
TEST_F(TestIndexProp, createBash_withUnzipPairedRevComp)
{
    TEST_DESCRIPTION("test create bash function");

    algo::IndexProps* _indexProp = new algo::IndexProps();
    _indexProp->setR1("test_R1.fq.gz");
    _indexProp->setR2("test_R2.fq.gz");
    _indexProp->setPairedReadsFlag(true);
    _indexProp->setOutputFile("output");
    _indexProp->setOutputFolder(".");
    _indexProp->setBuildDir("../build");
    _indexProp->setRevCompFlag(true);
    _indexProp->setReadFileType(algo::FileType::GZ);


    std::string expectedBash = "bash preprocess.sh -r test_R1.fq.gz -o . -f output -u ../build/bin/ -z 1 -p test_R2.fq.gz -c 1";
    std::string outputBash = _indexProp->createBash();

    EXPECT_EQ(expectedBash, outputBash);

}






}
