#include <gtest/gtest.h>
#include <climits>
#include "indexPropsClass.cpp"
using namespace std;

namespace algo {

class TestIndexProp : public ::testing::Test {
protected:
    virtual void SetUp() {    }
    virtual void TearDown() {
     if (fs::exists("testOutput")){fs::remove_all("testOutput");}
     if (fs::exists("outputFolder")){fs::remove_all("outputFolder");}
    }

public:

};
#define TEST_DESCRIPTION(desc) RecordProperty("description", desc)
////======================================================================
//TEST_F(TestIndexProp, setOutputFile1)
//{
//    TEST_DESCRIPTION("test default outputfile: ${pwd}/Index.fm9");

//    algo::IndexProps* _indexProp = new algo::IndexProps(true);
//    _indexProp->setOutputFile();

//    fs::path expectedOutputFile = fs::current_path() /= "Index.fm9";
//    std::string outputFile = _indexProp->getOutputFile();

//    EXPECT_EQ(expectedOutputFile.string(), outputFile);

//}
////======================================================================
//TEST_F(TestIndexProp, setOutputFile2)
//{
//    TEST_DESCRIPTION("test setOutputFolder: /tmp/outputFile/Index.fm9");

//    algo::IndexProps* _indexProp = new algo::IndexProps(true);

//    fs::path expectedOutputFile = "/tmp/outputFile/Index.fm9";
//    _indexProp->setOutputFolder(expectedOutputFile.string());
//    _indexProp->setOutputFile();
//    std::string outputFile = _indexProp->getOutputFile();

//    bool exist = fs::exists(_indexProp->getOutputFolder());

//    EXPECT_EQ(expectedOutputFile.string(), outputFile);
//    EXPECT_EQ(true, exist);

//    //remove folder /tmp/outputFile
//    fs::remove(_indexProp->getOutputFolder());
//}
////======================================================================
//TEST_F(TestIndexProp, setOutputFile3)
//{
//    TEST_DESCRIPTION("test setOutputFolder: outputFile/Index.fm9");

//    algo::IndexProps* _indexProp = new algo::IndexProps(true);

//    fs::path expectedOutputFile = fs::current_path() /= "outputFile/Index.fm9";
//    _indexProp->setOutputFolder(expectedOutputFile.string());
//    _indexProp->setOutputFile();
//    std::string outputFile = _indexProp->getOutputFile();

//    bool exist = fs::exists(_indexProp->getOutputFolder());

//    EXPECT_EQ(expectedOutputFile.string(), outputFile);
//    EXPECT_EQ(true, exist);

//    //remove folder /tmp/outputFile
//    fs::remove(_indexProp->getOutputFolder());
//}
////======================================================================
//TEST_F(TestIndexProp, setOutputFile4)
//{
//    TEST_DESCRIPTION("test setOutputFolder & outputfile: ../Index.fm9");

//    algo::IndexProps* _indexProp = new algo::IndexProps(true);

//    _indexProp->setOutputFolder("../Index.fm9");
//    _indexProp->setOutputFile();
//    std::string outputFile = _indexProp->getOutputFile();
//    fs::path expectedOutputFile = fs::current_path() /= "../Index.fm9";

//    bool exist = fs::exists(_indexProp->getOutputFolder());

//    EXPECT_EQ(expectedOutputFile.string(), outputFile);
//    EXPECT_EQ(true, exist);
//}
////======================================================================
//TEST_F(TestIndexProp, setOutputFile5)
//{
//    TEST_DESCRIPTION("test setIndexFileName: Test.fm9");

//    algo::IndexProps* _indexProp = new algo::IndexProps(true);

//    _indexProp->setIndexFileName("Test");

//    _indexProp->setOutputFile();
//    fs::path expectedOutputFile = fs::current_path() /= "Test.fm9";
//    std::string outputFile = _indexProp->getOutputFile();

//    EXPECT_EQ(expectedOutputFile.string(), outputFile);
//}

////======================================================================
//TEST_F(TestIndexProp, setOutputFile6)
//{
//    TEST_DESCRIPTION("test RecordProperty: Index_Reads.fm9");

//    algo::IndexProps* _indexProp = new algo::IndexProps(true);
//    _indexProp->setReadSetName("Reads");

//    _indexProp->setOutputFile();
//    fs::path expectedOutputFile = fs::current_path() /= "Index_Reads.fm9";
//    std::string outputFile = _indexProp->getOutputFile();

//    EXPECT_EQ(expectedOutputFile.string(), outputFile);
//}
////======================================================================
//TEST_F(TestIndexProp, setOutputFile7)
//{
//    TEST_DESCRIPTION("test setReadSetName & setOutputFolder: /tmp/outputFile2/Index_Reads.fm9");

//    algo::IndexProps* _indexProp = new algo::IndexProps(true);

//    fs::path expectedOutputFile = "/tmp/outputFile2/Index_Reads.fm9";

//    _indexProp->setReadSetName("Reads");
//    _indexProp->setOutputFolder(expectedOutputFile.string());
//    _indexProp->setOutputFile();

//    std::string outputFile = _indexProp->getOutputFile();
//    bool exist = fs::exists(_indexProp->getOutputFolder());

//    EXPECT_EQ(expectedOutputFile.string(), outputFile);
//    EXPECT_EQ(true, exist);

//    //remove folder /tmp/outputFile2
//    fs::remove(_indexProp->getOutputFolder());
//}
////======================================================================
//TEST_F(TestIndexProp, setOutputFile8)
//{
//    TEST_DESCRIPTION("test setReadSetName & setIndexFileName: ${pwd}/Test_Reads.fm9");

//    algo::IndexProps* _indexProp = new algo::IndexProps(true);

//    _indexProp->setReadSetName("Reads");
//    _indexProp->setIndexFileName("Test");
//    _indexProp->setOutputFile();

//    fs::path expectedOutputFile = fs::current_path() /= "Test_Reads.fm9";
//    std::string outputFile = _indexProp->getOutputFile();

//    EXPECT_EQ(expectedOutputFile, outputFile);
//}
//======================================================================
TEST_F(TestIndexProp, setR1)
{
    TEST_DESCRIPTION("test setR1");

    algo::IndexProps* _indexProp = new algo::IndexProps(true);

    fs::create_directory("reads");
    std::ofstream("reads/test.fq");
    bool rc1 = _indexProp->setR1("reads/test.fq");  //found and return true

    _indexProp->delR1();    //removed
    bool rc2 = _indexProp->setR1("reads/test.fq");  //not found and return false

    EXPECT_EQ(true, rc1);
    EXPECT_EQ(false, rc2);

    //cleanup
    fs::remove_all("reads");
}
//======================================================================
TEST_F(TestIndexProp, setR2)
{
    TEST_DESCRIPTION("test setR2");

    algo::IndexProps* _indexProp = new algo::IndexProps(true);

    fs::create_directory("reads");
    std::ofstream("reads/test.fq");
    bool rc1 = _indexProp->setR2("reads/test.fq");  //found and return true

    _indexProp->delR2();    //removed
    bool rc2 = _indexProp->setR2("reads/test.fq");  //not found and return false

    EXPECT_EQ(true, rc1);
    EXPECT_EQ(false, rc2);

    //cleanup
    fs::remove_all("reads");
}
//======================================================================
TEST_F(TestIndexProp, createBash1)
{
    TEST_DESCRIPTION("test create bash function: set:[R1, build dir] not set:[outputFolder, Index Filename, Read Filename, R2]");

    algo::IndexProps* _indexProp = new algo::IndexProps(true);

    fs::create_directory("reads");
    std::ofstream("reads/test.fq");
    _indexProp->setR1("reads/test.fq");
    _indexProp->setReadSetName("test");
    _indexProp->setBuildDir("build");

    std::string outputBash = _indexProp->createBash();

    char _r[800], _o[800], _f[800], _u[800];
    //"bash .../preprocess.sh -r <r> -o <o> -f <f> -u <u> "
    std::sscanf(outputBash.c_str(), "%*s %*s %*2s %s %*2s %s %*2s %s %*2s %s", _r, _o, _f, _u);
    std::string r(_r), o(_o), f(_f), u(_u);

    std::string expected_r = _indexProp->getR1();
    std::string expected_o = _indexProp->getppfFolder();
    std::string expected_f = _indexProp->getReadSetName();
    std::string expected_u = _indexProp->getBuildDir().string() + "/bin/";

    EXPECT_EQ(r, expected_r);
    EXPECT_EQ(o, expected_o);
    EXPECT_EQ(f, expected_f);
    EXPECT_EQ(u, expected_u);

    //cleanup
    fs::remove_all("reads");
}
//======================================================================
TEST_F(TestIndexProp, createBash2)
{
    TEST_DESCRIPTION("test create bash function: set:[R1, R2, outputFolder, build dir, Index Filename, Read Filename] not set:[outputFolder, Index Filename]");

    algo::IndexProps* _indexProp = new algo::IndexProps(true);

    fs::create_directory("reads");
    std::ofstream("reads/test_1.fq");
    std::ofstream("reads/test_2.fq");

    _indexProp->setR1("reads/test_1.fq");
    _indexProp->setR2("reads/test_2.fq");
    _indexProp->setPairedReadsFlag(true);
    _indexProp->setReadSetName("PatientX");
    _indexProp->setIndexName("ITest");
    _indexProp->setOutputFolder("outputFolder");

    _indexProp->setBuildDir("build");
    std::string outputBash = _indexProp->createBash();

    char _r[800], _o[800], _f[800], _u[800], _p[800];
    //"bash .../preprocess.sh -r <r> -o <o> -f <f> -u <u>  -p <p>"
    std::sscanf(outputBash.c_str(), "%*s %*s %*2s %s %*2s %s %*2s %s %*2s %s %*2s %s", _r, _o, _f, _u, _p);
    std::string r(_r), o(_o), f(_f), u(_u), p(_p);

    std::string expected_r = _indexProp->getR1();
    std::string expected_o = _indexProp->getppfFolder();
    std::string expected_f = _indexProp->getReadSetName();
    std::string expected_u = _indexProp->getBuildDir().string() + "/bin/";
    std::string expected_p = _indexProp->getR2();

    EXPECT_EQ(r, expected_r);
    EXPECT_EQ(o, expected_o);
    EXPECT_EQ(f, expected_f);
    EXPECT_EQ(u, expected_u);
    EXPECT_EQ(p, expected_p);

    //cleanup
    _indexProp->delR2();
    fs::remove_all("reads");


}
//======================================================================
TEST_F(TestIndexProp, createBash_withUnzip)
{
    TEST_DESCRIPTION("test create bash function:");

    algo::IndexProps* _indexProp = new algo::IndexProps(true);

    std::ofstream("test.fq.gz");
    _indexProp->setR1("test.fq.gz");
    _indexProp->setBuildDir("build");
    _indexProp->setReadSetName("test");
    _indexProp->setReadFileType(algo::FileType::GZ);
    std::string outputBash = _indexProp->createBash();

    char _r[800], _o[800], _f[800], _u[800];
    int z;
    //"bash .../preprocess.sh -r <r> -o <o> -f <f> -u <u>  -z <z>"
    std::sscanf(outputBash.c_str(), "%*s %*s %*2s %s %*2s %s %*2s %s %*2s %s %*2s %d", _r, _o, _f, _u, &z);
    std::string r(_r), o(_o), f(_f), u(_u);

    std::string expected_r = _indexProp->getR1();
    std::string expected_o = _indexProp->getppfFolder();
    std::string expected_f = _indexProp->getReadSetName();
    std::string expected_u = _indexProp->getBuildDir().string() + "/bin/";

    EXPECT_EQ(r, expected_r);
    EXPECT_EQ(o, expected_o);
    EXPECT_EQ(f, expected_f);
    EXPECT_EQ(u, expected_u);
    EXPECT_EQ(1, z);

    //cleanup
    _indexProp->delR1();


}

//======================================================================
TEST_F(TestIndexProp, createBash_withRevComp)
{
    TEST_DESCRIPTION("test create bash function");

    algo::IndexProps* _indexProp = new algo::IndexProps(true);

    std::ofstream("test.fq");
    _indexProp->setR1("test.fq");
    _indexProp->setBuildDir("build");
    _indexProp->setReadSetName("test");
    _indexProp->setRevCompFlag(true);
    std::string outputBash = _indexProp->createBash();

    char _r[800], _o[800], _f[800], _u[800];
    int c;
    //"bash .../preprocess.sh -r <r> -o <o> -f <f> -u <u>  -c <c>"
    std::sscanf(outputBash.c_str(), "%*s %*s %*2s %s %*2s %s %*2s %s %*2s %s %*2s %d", _r, _o, _f, _u, &c);
    std::string r(_r), o(_o), f(_f), u(_u);

    std::string expected_r = _indexProp->getR1();
    std::string expected_o = _indexProp->getppfFolder();
    std::string expected_f = _indexProp->getReadSetName();
    std::string expected_u = _indexProp->getBuildDir().string() + "/bin/";

    EXPECT_EQ(r, expected_r);
    EXPECT_EQ(o, expected_o);
    EXPECT_EQ(f, expected_f);
    EXPECT_EQ(u, expected_u);
    EXPECT_EQ(1, c);

    //cleanup
    _indexProp->delR1();
}
//======================================================================
TEST_F(TestIndexProp, createBash_withUnzipPairedRevComp)
{
    TEST_DESCRIPTION("test create bash function");

    algo::IndexProps* _indexProp = new algo::IndexProps(true);

    fs::create_directory("reads");
    std::ofstream("reads/test_1.fq.gz");
    std::ofstream("reads/test_2.fq.gz");

    _indexProp->setR1("reads/test_1.fq.gz");
    _indexProp->setR2("reads/test_2.fq.gz");
    _indexProp->setPairedReadsFlag(true);
    _indexProp->setReadFileType(algo::FileType::GZ);
    _indexProp->setRevCompFlag(true);
    _indexProp->setReadSetName("test");
    _indexProp->setBuildDir("build");
    std::string outputBash = _indexProp->createBash();

    char _r[800], _o[800], _f[800], _u[800], _p[800];
    int z, c;
    //"bash .../preprocess.sh -r <r> -o <o> -f <f> -u <u> -z <z> -p <p> -c <c>"
    std::sscanf(outputBash.c_str(), "%*s %*s %*2s %s %*2s %s %*2s %s %*2s %s %*2s %d %*2s %s %*2s %d",
                _r, _o, _f, _u, &z, _p, &c);
    std::string r(_r), o(_o), f(_f), u(_u), p(_p);

    std::string expected_r = _indexProp->getR1();
    std::string expected_o = _indexProp->getppfFolder();
    std::string expected_f = _indexProp->getReadSetName();
    std::string expected_u = _indexProp->getBuildDir().string() + "/bin/";
    std::string expected_p = _indexProp->getR2();

    EXPECT_EQ(r, expected_r);
    EXPECT_EQ(o, expected_o);
    EXPECT_EQ(f, expected_f);
    EXPECT_EQ(u, expected_u);
    EXPECT_EQ(p, expected_p);
    EXPECT_EQ(1, z);
    EXPECT_EQ(1, c);

    //cleanup
    _indexProp->delR1();
    _indexProp->delR2();
    fs::remove_all("reads");
}

//======================================================================
TEST_F(TestIndexProp, createBash_withMultipleIndexes)
{
    TEST_DESCRIPTION("test create bash function");

    algo::IndexProps* _indexProp = new algo::IndexProps(true);

    std::ofstream("test_R1.fq.gz");
    _indexProp->setR1("test_R1.fq.gz");
    _indexProp->setReadSetName("test");
    _indexProp->setOutputFolder("outputFolder");
    _indexProp->setBuildDir("build");
    _indexProp->setNumOfIndexes(5);
    //_indexProp->setOutputFile();
    std::string outputBash = _indexProp->createBash();

    char _r[800], _o[800], _f[800], _u[800], _p[800];
    int n;
    //"bash .../preprocess.sh -r <r> -o <o> -f <f> -u <u> -n <n>"
    std::sscanf(outputBash.c_str(), "%*s %*s %*2s %s %*2s %s %*2s %s %*2s %s %*2s %d",
                _r, _o, _f, _u, &n);
    std::string r(_r), o(_o), f(_f), u(_u);

    std::string expected_r = _indexProp->getR1();
    std::string expected_o = _indexProp->getppfFolder();
    std::string expected_f = _indexProp->getReadSetName();
    std::string expected_u = _indexProp->getBuildDir().string() + "/bin/";

    EXPECT_EQ(r, expected_r);
    EXPECT_EQ(o, expected_o);
    EXPECT_EQ(f, expected_f);
    EXPECT_EQ(u, expected_u);
    EXPECT_EQ(5, n);

    //cleanup
    _indexProp->delR1();
}
//======================================================================
TEST_F(TestIndexProp, createPPFSet1)
{
    algo::IndexProps* _indexProp = new algo::IndexProps(true);
    fs::create_directory("outputFolder");
    fs::create_directory("outputFolder/tmp_ppf");
    std::ofstream("outputFolder/tmp_ppf/test.fasta");
    std::ofstream("test.fq.gz");

    _indexProp->setR1("test.fq.gz");
    _indexProp->setOutputFolder("outputFolder");
    _indexProp->setppfFolder("outputFolder/tmp_ppf");

    _indexProp->setBuildDir("/build");
    _indexProp->setNumOfIndexes(1);
    _indexProp->setReadSetName("test");
    _indexProp->createPPFSet();
    std::string expectedPPFN1 =  "outputFolder/tmp_ppf/test.fasta";
    std::map<fs::path, std::pair<u_int, u_int>> outputPPFNs = _indexProp->getPreProcessedFastas();
    std::string outputPPFN1 = outputPPFNs.begin()->first.string() ;
    fs::remove(_indexProp->getR1());
    fs::remove_all(_indexProp->getOutputFolder());

    EXPECT_EQ(expectedPPFN1, outputPPFN1);

    //cleanup
    _indexProp->delR1();
    fs::remove(_indexProp->getOutputFolder());
}
//======================================================================
TEST_F(TestIndexProp, createPPFSet2)
{
    algo::IndexProps* _indexProp = new algo::IndexProps(true);
    std::ofstream("test.fq.gz");
    fs::create_directories("outputFolder/tmp_ppf");
    std::ofstream("outputFolder/tmp_ppf/reads.fasta");
    _indexProp->setR1("test.fq.gz");
    _indexProp->setOutputFolder("outputFolder");
    _indexProp->setppfFolder("outputFolder/tmp_ppf");
    _indexProp->setBuildDir("../build");
    _indexProp->setNumOfIndexes(1);
    _indexProp->setReadSetName("reads");


    _indexProp->createPPFSet();
    std::string expectedPPFN1 =  "outputFolder/tmp_ppf/reads.fasta";
    std::map<fs::path, std::pair<u_int, u_int>> outputPPFNs = _indexProp->getPreProcessedFastas();
    std::string outputPPFN1 = outputPPFNs.begin()->first.string() ;

    std::cout << "createPPFSet2 : " << outputPPFN1 << " " << expectedPPFN1 <<  std::endl;

    EXPECT_EQ(expectedPPFN1, outputPPFN1);

    //cleanup
    _indexProp->delR1();
    fs::remove_all(_indexProp->getOutputFolder());
}
//======================================================================
TEST_F(TestIndexProp, createPPFSet3)
{
    algo::IndexProps* _indexProp = new algo::IndexProps(true);
    std::ofstream("test.fq.gz");
    fs::create_directories("outputFolder/tmp_ppf");
    std::ofstream("outputFolder/tmp_ppf/test_1.fasta");
    std::ofstream("outputFolder/tmp_ppf/test_2.fasta");
    _indexProp->setR1("test.fq.gz");
    _indexProp->setReadSetName("test");
    _indexProp->setOutputFolder("outputFolder");
    _indexProp->setBuildDir("../build");
    _indexProp->setNumOfIndexes(2);

    _indexProp->createPPFSet();
    std::string expectedPPFN1 =  "outputFolder/tmp_ppf/test_1.fasta";
    std::string expectedPPFN2 =  "outputFolder/tmp_ppf/test_2.fasta";

    std::map<fs::path, std::pair<u_int, u_int>> outputPPFNs = _indexProp->getPreProcessedFastas();

    std::map<fs::path, std::pair<u_int, u_int>>::iterator it = outputPPFNs.begin();
    std::string outputPPFN1 = it->first.string();
    it++;
    std::string outputPPFN2 = it->first.string();


    EXPECT_EQ(expectedPPFN1, outputPPFN1);
    EXPECT_EQ(expectedPPFN2, outputPPFN2);

    //cleanup
    _indexProp->delR1();
    fs::remove_all(_indexProp->getOutputFolder());
}
//======================================================================
TEST_F(TestIndexProp, createPPFSet4)
{
    algo::IndexProps* _indexProp = new algo::IndexProps(true);
    std::ofstream("test.fq.gz");
    fs::create_directories("outputFolder/tmp_ppf");
    std::ofstream("outputFolder/tmp_ppf/reads_0.fasta");
    std::ofstream("outputFolder/tmp_ppf/reads_1.fasta");
    _indexProp->setR1("test.fq.gz");
    _indexProp->setOutputFolder("outputFolder");
    _indexProp->setppfFolder("outputFolder/tmp_ppf");
    _indexProp->setBuildDir("../build");
    _indexProp->setNumOfIndexes(2);
    _indexProp->setReadSetName("reads");

    _indexProp->createPPFSet();
    std::string expectedPPFN1 =  "outputFolder/tmp_ppf/reads_0.fasta";
    std::string expectedPPFN2 =  "outputFolder/tmp_ppf/reads_1.fasta";

    std::map<fs::path, std::pair<u_int, u_int>> outputPPFNs = _indexProp->getPreProcessedFastas();

    std::map<fs::path, std::pair<u_int, u_int>>::iterator it = outputPPFNs.begin();
    std::string outputPPFN1 = it->first.string();
    it++;
    std::string outputPPFN2 = it->first.string();

    EXPECT_EQ(expectedPPFN1, outputPPFN1);
    EXPECT_EQ(expectedPPFN2, outputPPFN2);

    //cleanup
    _indexProp->delR1();
    fs::remove_all(_indexProp->getOutputFolder());
}


//======================================================================
TEST_F(TestIndexProp, createIndexINI)
{
    algo::IndexProps* _indexProp = new algo::IndexProps(true);
    std::ofstream("test.fq.gz");
    _indexProp->setR1("test.fq.gz");
    _indexProp->setNumOfReads(10);
    _indexProp->setOutputFolder("outputFolder");
    _indexProp->setppfFolder("outputFolder/tmp_ppf");
    _indexProp->setBuildDir("../build");
    _indexProp->setNumOfIndexes(2);
    _indexProp->setIndexName("output");

    _indexProp->saveIndexProps("indexProps.ini");
    EXPECT_TRUE(fs::exists("indexProps.ini"));

    //cleanup
    _indexProp->delR1();
    fs::remove_all(_indexProp->getOutputFolder());
    fs::remove_all("indexProps.ini");
}

//======================================================================
TEST_F(TestIndexProp, countReads)
{
    //algo::IndexProps* _indexProp = new algo::IndexProps(true);
    //countNumOfReads();



}





}
