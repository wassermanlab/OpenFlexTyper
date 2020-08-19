#include <gtest/gtest.h>
#include <climits>
#include "indexPropsClass.cpp"
using namespace std;

namespace algo {

class TestIndexProp : public ::testing::Test {
protected:
    virtual void SetUp() {    }
    virtual void TearDown() {    }

public:

};
#define TEST_DESCRIPTION(desc) RecordProperty("description", desc)

//======================================================================
TEST_F(TestIndexProp, setOutputFolder1)
{
    TEST_DESCRIPTION("test set outputFolder, no folder given ");

    algo::IndexProps* _indexProp = new algo::IndexProps(true);
    _indexProp->setOutputFolder("");

    std::string expectedOutputFolder = fs::current_path().string();
    std::string outputFolder = _indexProp->getOutputFolder();
    if (fs::is_empty(_indexProp->getOutputFolder())){
        fs::remove(_indexProp->getOutputFolder());
    }
    EXPECT_EQ(expectedOutputFolder, outputFolder);

}
//======================================================================
TEST_F(TestIndexProp, setOutputFolder2)
{
    TEST_DESCRIPTION("test set outputFolder, relative path given ");

    algo::IndexProps* _indexProp = new algo::IndexProps(true);
    _indexProp->setOutputFolder("outputfolder/");

    std::string expectedOutputFolder = fs::current_path().string()+ "/outputfolder/";
    std::string outputFolder = _indexProp->getOutputFolder();
    if (fs::is_empty(_indexProp->getOutputFolder())){
        fs::remove(_indexProp->getOutputFolder());
    }
    EXPECT_EQ(expectedOutputFolder, outputFolder);

}
//======================================================================
TEST_F(TestIndexProp, setOutputFolder3)
{
    TEST_DESCRIPTION("test set outputFolder, ../ given  ");

    algo::IndexProps* _indexProp = new algo::IndexProps(true);
    _indexProp->setOutputFolder("../");

    std::string expectedOutputFolder = fs::current_path().parent_path().string();
    std::string outputFolder = _indexProp->getOutputFolder();
    if (fs::is_empty(_indexProp->getOutputFolder())){
        fs::remove(_indexProp->getOutputFolder());
    }
    EXPECT_EQ(expectedOutputFolder, outputFolder);

}
//======================================================================
TEST_F(TestIndexProp, setOutputFolder4)
{
    TEST_DESCRIPTION("test set outputFolder, current folder given using . ");

    algo::IndexProps* _indexProp = new algo::IndexProps(true);
    _indexProp->setOutputFolder(".");

    std::string expectedOutputFolder = fs::current_path().string();
    std::string outputFolder = _indexProp->getOutputFolder();
    if (fs::is_empty(_indexProp->getOutputFolder())){
        fs::remove(_indexProp->getOutputFolder());
    }
    EXPECT_EQ(expectedOutputFolder, outputFolder);

}

//======================================================================
TEST_F(TestIndexProp, setOutputFile1)
{
    TEST_DESCRIPTION("test set outputfile");

    algo::IndexProps* _indexProp = new algo::IndexProps(true);
    _indexProp->setOutputFolder("");
    _indexProp->setOutputFile("test.tsv");
    fs::path outputfile = fs::current_path() /= "test.tsv";
    std::string expectedOutputFile = outputfile.string();
    std::string outputFile = _indexProp->getOutputFile();
    if (fs::is_empty(_indexProp->getOutputFolder())){
        fs::remove(_indexProp->getOutputFolder());
    }
    EXPECT_EQ(expectedOutputFile, outputFile);

}

//======================================================================
TEST_F(TestIndexProp, setOutputFile2)
{
    TEST_DESCRIPTION("test set outputfile, with different output directory");

    algo::IndexProps* _indexProp = new algo::IndexProps(true);

    _indexProp->setOutputFolder(fs::current_path().parent_path());
    _indexProp->setOutputFile("test.tsv");
    fs::path outputfile = fs::current_path().parent_path() /= "test.tsv";
    std::string expectedOutputFile = outputfile.string();
    std::string outputFile = _indexProp->getOutputFile();
    if (fs::is_empty(_indexProp->getOutputFolder())){
        fs::remove(_indexProp->getOutputFolder());
    }
    EXPECT_EQ(expectedOutputFile, outputFile);

}
//======================================================================
TEST_F(TestIndexProp, setOutputFile3)
{
    TEST_DESCRIPTION("test set outputfile");

    algo::IndexProps* _indexProp = new algo::IndexProps(true);
    _indexProp->setOutputFolder("");
    _indexProp->setOutputFile("test.tsv");
    fs::path outputfile = fs::current_path() /= "test.tsv";
    std::string expectedOutputFile = outputfile.string();
    std::string outputFile = _indexProp->getOutputFile();
    if (fs::is_empty(_indexProp->getOutputFolder())){
        fs::remove(_indexProp->getOutputFolder());
    }
    EXPECT_EQ(expectedOutputFile, outputFile);
}


//======================================================================
TEST_F(TestIndexProp, createBash1)
{
    TEST_DESCRIPTION("test create bash function");

    algo::IndexProps* _indexProp = new algo::IndexProps(true);
    std::ofstream("test.fq");
    _indexProp->setR1("test.fq");
    _indexProp->setOutputFolder("outputfolder/");
    _indexProp->setBuildDir("../build");
    _indexProp->setOutputFile("output");
    std::string expectedBash = "bash preprocess.sh -r "
            + fs::current_path().string()+ "/test.fq -o "
            + fs::current_path().string() + "/outputfolder/ -f "
            + fs::current_path().string() + "/outputfolder/output -u ../build/bin/";
    std::string outputBash = _indexProp->createBash();
    fs::remove(_indexProp->getOutputFile());
    if (fs::is_empty(_indexProp->getOutputFolder())){
        fs::remove(_indexProp->getOutputFolder());
    }

    EXPECT_EQ(expectedBash, outputBash);

}
//======================================================================
TEST_F(TestIndexProp, createBash2)
{
    TEST_DESCRIPTION("test create bash function");

    algo::IndexProps* _indexProp = new algo::IndexProps(true);
    fs::path folder = fs::current_path();
    folder /= "reads";
    fs::create_directory(folder);
    folder /= "test.fq";

    std::ofstream(folder.string());
    _indexProp->setR1("/reads/test.fq");
    _indexProp->setOutputFolder("../");
    _indexProp->setOutputFile("output");
    _indexProp->setBuildDir("../build");
    std::string expectedBash = "bash preprocess.sh -r "
            + fs::current_path().string()+ "/reads/test.fq -o "
            + fs::current_path().parent_path().string() + " -f "
            + fs::current_path().parent_path().string() + "/output -u ../build/bin/";
    std::string outputBash = _indexProp->createBash();
    fs::remove(_indexProp->getR1());

    EXPECT_EQ(expectedBash, outputBash);

}
//======================================================================
TEST_F(TestIndexProp, createBash_withUnzip)
{
    TEST_DESCRIPTION("test create bash function");

    algo::IndexProps* _indexProp = new algo::IndexProps(true);
        std::ofstream("test.fq.gz");
    _indexProp->setR1("test.fq.gz");
    _indexProp->setOutputFolder("outputfolder/");
    _indexProp->setOutputFile("output");
    _indexProp->setBuildDir("../build");
    _indexProp->setReadFileType(algo::FileType::GZ);

    std::string expectedBash = "bash preprocess.sh -r "
            +  fs::current_path().string()+ "/test.fq.gz -o "
             + fs::current_path().string()+ "/outputfolder/ -f "
            + fs::current_path().string() + "/outputfolder/output -u ../build/bin/ -z 1" ;
    std::string outputBash = _indexProp->createBash();
    fs::remove(_indexProp->getR1());
    if (fs::is_empty(_indexProp->getOutputFolder())){
        fs::remove(_indexProp->getOutputFolder());
    }
    EXPECT_EQ(expectedBash, outputBash);

}
//======================================================================
TEST_F(TestIndexProp, createBash_withPair)
{
    TEST_DESCRIPTION("test create bash function");

    algo::IndexProps* _indexProp = new algo::IndexProps(true);
    std::ofstream("test_R1.fq");
    std::ofstream("test_R2.fq");

    _indexProp->setR1("test_R1.fq");
    _indexProp->setR2("test_R2.fq");
    _indexProp->setPairedReadsFlag(true);

    _indexProp->setOutputFolder("outputfolder/");
    _indexProp->setBuildDir("../build");
    _indexProp->setOutputFile("output");
    std::string expectedBash = "bash preprocess.sh -r "
             + fs::current_path().string()+ "/test_R1.fq -o "
             + fs::current_path().string()+ "/outputfolder/ -f "
            + fs::current_path().string() + "/outputfolder/output -u ../build/bin/ -p "
             + fs::current_path().string()+ "/test_R2.fq";
    std::string outputBash = _indexProp->createBash();

    fs::remove(_indexProp->getR1());
    fs::remove(_indexProp->getR2());
    if (fs::is_empty(_indexProp->getOutputFolder())){
        fs::remove(_indexProp->getOutputFolder());
    }
    EXPECT_EQ(expectedBash, outputBash);

}
//======================================================================
TEST_F(TestIndexProp, createBash_withRevComp)
{
    TEST_DESCRIPTION("test create bash function");

    algo::IndexProps* _indexProp = new algo::IndexProps(true);
    std::ofstream("test.fq");

    _indexProp->setR1("test.fq");

    _indexProp->setOutputFolder("outputfolder/");
    _indexProp->setBuildDir("../build");
    _indexProp->setRevCompFlag(true);
    _indexProp->setOutputFile("output");
    std::string expectedBash = "bash preprocess.sh -r "
             + fs::current_path().string()+ "/test.fq -o "
             + fs::current_path().string()+ "/outputfolder/ -f "
            + fs::current_path().string() + "/outputfolder/output -u ../build/bin/ -c 1";
    std::string outputBash = _indexProp->createBash();
    fs::remove(_indexProp->getR1());

    if (fs::is_empty(_indexProp->getOutputFolder())){
        fs::remove(_indexProp->getOutputFolder());
    }
    EXPECT_EQ(expectedBash, outputBash);

}
//======================================================================
TEST_F(TestIndexProp, createBash_withUnzipPairedRevComp)
{
    TEST_DESCRIPTION("test create bash function");

    algo::IndexProps* _indexProp = new algo::IndexProps(true);
    std::ofstream("test_R1.fq.gz");
    std::ofstream("test_R2.fq.gz");
    _indexProp->setR1("test_R1.fq.gz");
    _indexProp->setR2("test_R2.fq.gz");
    _indexProp->setPairedReadsFlag(true);

    _indexProp->setOutputFolder("outputfolder/");
    _indexProp->setBuildDir("../build");
    _indexProp->setRevCompFlag(true);
    _indexProp->setReadFileType(algo::FileType::GZ);
    _indexProp->setOutputFile("output");

    std::string expectedBash = "bash preprocess.sh -r "
             + fs::current_path().string()+ "/test_R1.fq.gz -o "
             + fs::current_path().string()+ "/outputfolder/ -f "
            + fs::current_path().string() + "/outputfolder/output -u ../build/bin/ -z 1 -p "
             + fs::current_path().string()+ "/test_R2.fq.gz -c 1";
    std::string outputBash = _indexProp->createBash();
    fs::remove(_indexProp->getR1());
    fs::remove(_indexProp->getR2());
    if (fs::is_empty(_indexProp->getOutputFolder())){
        fs::remove(_indexProp->getOutputFolder());
    }
    EXPECT_EQ(expectedBash, outputBash);

}

//======================================================================
TEST_F(TestIndexProp, createBash_withMultipleIndexes)
{
    TEST_DESCRIPTION("test create bash function");

    algo::IndexProps* _indexProp = new algo::IndexProps(true);
    std::ofstream("test_R1.fq.gz");
    _indexProp->setR1("test_R1.fq.gz");

    _indexProp->setOutputFolder("outputfolder/");
    _indexProp->setBuildDir("../build");
    _indexProp->setNumOfIndexes(5);
    _indexProp->setOutputFile("output");

    std::string expectedBash = "bash preprocess.sh -r "
             + fs::current_path().string()+ "/test_R1.fq.gz -o "
             + fs::current_path().string()+ "/outputfolder/ -f "
            + fs::current_path().string() + "/outputfolder/output -u ../build/bin/ -n 5";
    std::string outputBash = _indexProp->createBash();
    fs::remove(_indexProp->getR1());

    if (fs::is_empty(_indexProp->getOutputFolder())){
        fs::remove(_indexProp->getOutputFolder());
    }
    EXPECT_EQ(expectedBash, outputBash);

}
//======================================================================
TEST_F(TestIndexProp, createPPFSet1)
{
    algo::IndexProps* _indexProp = new algo::IndexProps(true);
    std::ofstream("test.fq.gz");

    _indexProp->setR1("test.fq.gz");
    _indexProp->setOutputFolder("outputfolder/");
    _indexProp->setBuildDir("../build");
    _indexProp->setNumOfIndexes(1);
    _indexProp->setOutputFile("output");

    _indexProp->createPPFSet();
    std::string expectedPPFN1 =  fs::current_path().string() + "/outputfolder/output.fasta";
    std::map<fs::path, std::pair<u_int, u_int>> outputPPFNs = _indexProp->getPreProcessedFastas();
    std::string outputPPFN1 = outputPPFNs.begin()->first.string() ;
    fs::remove(_indexProp->getR1());

    if (fs::is_empty(_indexProp->getOutputFolder())){
        fs::remove(_indexProp->getOutputFolder());
    }
    EXPECT_EQ(expectedPPFN1, outputPPFN1);


}
//======================================================================
TEST_F(TestIndexProp, createPPFSet)
{
    algo::IndexProps* _indexProp = new algo::IndexProps(true);
    std::ofstream("test.fq.gz");
    _indexProp->setR1("test.fq.gz");
    _indexProp->setOutputFolder("outputfolder/");
    _indexProp->setBuildDir("../build");
    _indexProp->setNumOfIndexes(2);
    _indexProp->setOutputFile("output");
    _indexProp->createPPFSet();
    std::string expectedPPFN1 =  fs::current_path().string() +  "/outputfolder/output_0.fasta";
    std::string expectedPPFN2 =  fs::current_path().string() + "/outputfolder/output_1.fasta";

    std::map<fs::path, std::pair<u_int, u_int>> outputPPFNs = _indexProp->getPreProcessedFastas();

    std::map<fs::path, std::pair<u_int, u_int>>::iterator it = outputPPFNs.begin();
    std::string outputPPFN1 = it->first.string();
    it++;
    std::string outputPPFN2 = it->first.string();
    fs::remove(_indexProp->getR1());

    if (fs::is_empty(_indexProp->getOutputFolder())){
        fs::remove(_indexProp->getOutputFolder());
    }
    EXPECT_EQ(expectedPPFN1, outputPPFN1);
    EXPECT_EQ(expectedPPFN2, outputPPFN2);

}


//======================================================================
TEST_F(TestIndexProp, createIndexINI)
{
    algo::IndexProps* _indexProp = new algo::IndexProps(true);
    std::ofstream("test.fq.gz");
    _indexProp->setR1("test.fq.gz");

    _indexProp->setOutputFolder("outputfolder/");
    _indexProp->setBuildDir("../build");
    _indexProp->setNumOfIndexes(2);
    _indexProp->setOutputFile("output");
    _indexProp->saveIndexProps("indexProps.ini");
    EXPECT_TRUE(fs::exists("indexProps.ini"));
    fs::remove(_indexProp->getR1());

    if (fs::is_empty(_indexProp->getOutputFolder())){
        fs::remove(_indexProp->getOutputFolder());
    }
}






}
