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

    void createR1R2(const std::string& readSetName)
    {
        fs::path r1 = readSetName + "_R1.fq";
        std::ofstream ofs1(r1);
        ofs1 << "this is some text in the new file\n";
        ofs1.close();
        std::cout << "CREATE R1 : " << r1 << std::endl;

        fs::path r2 = readSetName + "_R2.fq";
        std::ofstream ofs2(r2);
        ofs2 << "this is some text in the new file\n";
        ofs2.close();
        std::cout << "CREATE R2 : " << r2 << std::endl;
    }



public:

};

#define TEST_DESCRIPTION(desc) RecordProperty("description", desc)

//======================================================================
TEST_F(TestPreProcess, testGunZipFQ)
{
    TEST_DESCRIPTION("gunzip FQ");


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
    _props->setReadSetName("test");
    fs::path readFiles = fs::current_path();
    readFiles /= (_props->getReadSetName());
    fs::path r1 = readFiles += "_R1.fq";
    fs::path r2 = readFiles += "_R2.fq";

    createR1R2(_props->getReadSetName());

    algo::PreProcess _preprocess(*_props);
    _preprocess.addR1R2();

    std::cout << "R1 : " << _props->getR1() << std::endl;
    std::cout << "R2 : " << _props->getR2() << std::endl;

    EXPECT_EQ(r1.string(), _props->getR1().string());
    EXPECT_EQ(r2.string(), _props->getR2().string());
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
    TEST_DESCRIPTION("process paired read files");

}

//======================================================================
TEST_F(TestPreProcess, testProcessReadFile)
{
    TEST_DESCRIPTION("process read file");

}


}
