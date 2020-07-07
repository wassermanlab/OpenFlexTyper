#include <gtest/gtest.h>
#include <climits>
#include "preProcess.cpp"
#include "indexPropsClass.cpp"
using namespace std;

namespace algo {
class TestPreProcess : public ::testing::Test {
protected:
    algo::IndexProps* _props;
    virtual void SetUp() {
        _props = new algo::IndexProps();
    }

    virtual void TearDown() {
    }

public:

};

#define TEST_DESCRIPTION(desc) RecordProperty("description", desc)

//======================================================================
TEST_F(TestPreProcess, testGunZipFQ)
{
    TEST_DESCRIPTION("addR1R2");

}
//======================================================================
TEST_F(TestPreProcess, testCombineFasta)
{
    TEST_DESCRIPTION("combine Fasta");
        //void combineFasta(const fs::path& file1, const fs::path& file2, const fs::path& output);

}
//======================================================================
TEST_F(TestPreProcess, testCreateFWDFasta)
{
    TEST_DESCRIPTION("Create FWD Fasta");

    //    fs::path createFWDFasta();

}
//======================================================================
TEST_F(TestPreProcess, testCreateRevFasta)
{
    TEST_DESCRIPTION("Create Rev Fasta");

    //    fs::path createRevFasta();

}
//======================================================================
TEST_F(TestPreProcess, testCreatePreProcessFasta)
{
    TEST_DESCRIPTION("Create Pre Process Fasta");
    //    fs::path createPreProcessFasta();

}
//======================================================================
TEST_F(TestPreProcess, testAddR1R2)
{
    TEST_DESCRIPTION("add R1 R2");

}
//======================================================================
TEST_F(TestPreProcess, testPreProcessFQGZ)
{
    TEST_DESCRIPTION("Pre process FQ.gz");

}
//======================================================================
TEST_F(TestPreProcess, testPreProcessFQ)
{
    TEST_DESCRIPTION("pre process fq");

}
//======================================================================
TEST_F(TestPreProcess, testProcessPairedReadFiles)
{
    TEST_DESCRIPTION("process read file");

}

//======================================================================
TEST_F(TestPreProcess, testProcessReadFile)
{
    TEST_DESCRIPTION("process read file");

}


}
