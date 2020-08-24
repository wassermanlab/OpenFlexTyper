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
    TEST_DESCRIPTION("test set outputfile: set:[] not set:[outputfolder,index file name,read set]");

    algo::IndexProps* _indexProp = new algo::IndexProps(true);
    _indexProp->setOutputFile();
    fs::path outputfile = fs::current_path() /= "Index.fm9";
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
    TEST_DESCRIPTION("test set outputfile: set:[outputfolder] not set:[index file name,read set]");

    algo::IndexProps* _indexProp = new algo::IndexProps(true);

    _indexProp->setOutputFolder(fs::current_path().parent_path());
    _indexProp->setOutputFile();
    fs::path outputfile = fs::current_path().parent_path() /= "Index.fm9";
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
    TEST_DESCRIPTION("test set outputfile: set:[index file name] not set:[outputfolder,read set]");

    algo::IndexProps* _indexProp = new algo::IndexProps(true);

    _indexProp->setIndexFileName("Test");

    _indexProp->setOutputFile();
    fs::path outputfile = fs::current_path() /= "Test.fm9";
    std::string expectedOutputFile = outputfile.string();
    std::string outputFile = _indexProp->getOutputFile();
    if (fs::is_empty(_indexProp->getOutputFolder())){
        fs::remove(_indexProp->getOutputFolder());
    }
    EXPECT_EQ(expectedOutputFile, outputFile);
}

//======================================================================
TEST_F(TestIndexProp, setOutputFile4)
{
    TEST_DESCRIPTION("test set outputfile: set:[read set] not set:[outputfolder,index file name]");

    algo::IndexProps* _indexProp = new algo::IndexProps(true);
    _indexProp->setReadSetName("Reads");


    _indexProp->setOutputFile();
    fs::path outputfile = fs::current_path() /= "Index_Reads.fm9";
    std::string expectedOutputFile = outputfile.string();
    std::string outputFile = _indexProp->getOutputFile();
    if (fs::is_empty(_indexProp->getOutputFolder())){
        fs::remove(_indexProp->getOutputFolder());
    }
    EXPECT_EQ(expectedOutputFile, outputFile);
}

//======================================================================
TEST_F(TestIndexProp, setOutputFile5)
{
    TEST_DESCRIPTION("test set outputfile: set:[outputfolder,index file name] not set:[read set]");

    algo::IndexProps* _indexProp = new algo::IndexProps(true);

    _indexProp->setIndexFileName("Test");
    _indexProp->setOutputFolder(fs::current_path().parent_path());
    _indexProp->setOutputFile();
    fs::path outputfile = fs::current_path().parent_path() /= "Test.fm9";
    std::string expectedOutputFile = outputfile.string();
    std::string outputFile = _indexProp->getOutputFile();
    if (fs::is_empty(_indexProp->getOutputFolder())){
        fs::remove(_indexProp->getOutputFolder());
    }
    EXPECT_EQ(expectedOutputFile, outputFile);
}

//======================================================================
TEST_F(TestIndexProp, setOutputFile6)
{
    TEST_DESCRIPTION("test set outputfile: set:[outputfolder,read set] not set:[index file name,]");

    algo::IndexProps* _indexProp = new algo::IndexProps(true);
    _indexProp->setReadSetName("Reads");

    _indexProp->setOutputFolder(fs::current_path().parent_path());
    _indexProp->setOutputFile();
    fs::path outputfile = fs::current_path().parent_path() /= "Index_Reads.fm9";
    std::string expectedOutputFile = outputfile.string();
    std::string outputFile = _indexProp->getOutputFile();
    if (fs::is_empty(_indexProp->getOutputFolder())){
        fs::remove(_indexProp->getOutputFolder());
    }
    EXPECT_EQ(expectedOutputFile, outputFile);
}
//======================================================================
TEST_F(TestIndexProp, setOutputFile7)
{
    TEST_DESCRIPTION("test set outputfile: set:[index file name,read set] not set:[outputfolder]");

    algo::IndexProps* _indexProp = new algo::IndexProps(true);
    _indexProp->setReadSetName("Reads");
    _indexProp->setIndexFileName("Test");

    _indexProp->setOutputFile();
    fs::path outputfile = fs::current_path() /= "Test_Reads.fm9";
    std::string expectedOutputFile = outputfile.string();
    std::string outputFile = _indexProp->getOutputFile();
    if (fs::is_empty(_indexProp->getOutputFolder())){
        fs::remove(_indexProp->getOutputFolder());
    }
    EXPECT_EQ(expectedOutputFile, outputFile);
}
//======================================================================
TEST_F(TestIndexProp, setOutputFile8)
{
    TEST_DESCRIPTION("test set outputfile: set:[outputfolder,index file name,read set] not set:[]");

    algo::IndexProps* _indexProp = new algo::IndexProps(true);
    _indexProp->setReadSetName("Reads");
    _indexProp->setIndexFileName("Test");
    _indexProp->setOutputFolder(fs::current_path().parent_path());
    _indexProp->setOutputFile();
    fs::path outputfile = fs::current_path().parent_path() /= "Test_Reads.fm9";
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
    TEST_DESCRIPTION("test create bash function: set:[R1, build dir] not set:[outputFolder, Index Filename, Read Filename, R2]");

    algo::IndexProps* _indexProp = new algo::IndexProps(true);
    std::ofstream("test.fq");
    _indexProp->setR1("test.fq");
    _indexProp->setBuildDir("../build");
    _indexProp->setOutputFile();
    std::string expectedBash = "bash "
            + _indexProp->getBuildDir().string() + "/preprocess.sh -r "
            + fs::current_path().string()+ "/test.fq -o "
            + fs::current_path().string() + " -f Index -u ../build/bin/";
    std::string outputBash = _indexProp->createBash();
    fs::remove(_indexProp->getOutputFile());
    if (fs::is_empty(_indexProp->getOutputFolder())){
        fs::remove(_indexProp->getOutputFolder());
    }
    fs::remove(_indexProp->getR1());

    EXPECT_EQ(expectedBash, outputBash);

}
//======================================================================
TEST_F(TestIndexProp, createBash2)
{
    TEST_DESCRIPTION("test create bash function: set:[R1, R2, build dir] not set:[outputFolder, Index Filename, Read Filename]");

    algo::IndexProps* _indexProp = new algo::IndexProps(true);
    fs::path folder = fs::current_path();
    folder /= "reads";
    fs::create_directory(folder);
    fs::path read1 = folder;
    fs::path read2 = folder;
    read1 /= "test_1.fq";
    std::ofstream(read1.string());
    read2 /= "test_2.fq";
    std::ofstream(read2.string());

    _indexProp->setR1("/reads/test_1.fq");
    _indexProp->setR2("/reads/test_2.fq");
    _indexProp->setPairedReadsFlag(true);
    _indexProp->setOutputFile();
    _indexProp->setBuildDir("../build");
    std::string expectedBash = "bash "
            + _indexProp->getBuildDir().string() + "/preprocess.sh -r "
            + fs::current_path().string()+ "/reads/test_1.fq -o "
            + fs::current_path().string() + " -f Index -u ../build/bin/ -p "
            + fs::current_path().string()+ "/reads/test_2.fq";
    std::string outputBash = _indexProp->createBash();
    fs::remove(_indexProp->getR1());
    fs::remove(_indexProp->getR2());
    EXPECT_EQ(expectedBash, outputBash);

}
//======================================================================
TEST_F(TestIndexProp, createBash3)
{
    TEST_DESCRIPTION("test create bash function: set:[R1, build dir, Read Filename] not set:[outputFolder, Index Filename, R2]");

    algo::IndexProps* _indexProp = new algo::IndexProps(true);
    fs::path folder = fs::current_path();
    folder /= "reads";
    fs::create_directory(folder);
    fs::path read1 = folder /= "test_1.fq";
    std::ofstream(read1.string());


    _indexProp->setR1("/reads/test_1.fq");

    _indexProp->setReadSetName("PatientX");
    _indexProp->setOutputFolder("../");
    _indexProp->setOutputFile();
    _indexProp->setBuildDir("../build");
    std::string expectedBash = "bash "
            + _indexProp->getBuildDir().string() + "/preprocess.sh -r "
            + fs::current_path().string()+ "/reads/test_1.fq -o "
            + fs::current_path().parent_path().string() + " -f Index_PatientX -u ../build/bin/";
    std::string outputBash = _indexProp->createBash();
    fs::remove(_indexProp->getR1());

    EXPECT_EQ(expectedBash, outputBash);

}
//======================================================================
TEST_F(TestIndexProp, createBash4)
{
    TEST_DESCRIPTION("test create bash function: set:[R1, Index Filename, build dir] not set:[outputFolder, Read Filename, R2]");

    algo::IndexProps* _indexProp = new algo::IndexProps(true);
    fs::path folder = fs::current_path();
    folder /= "reads";
    fs::create_directory(folder);
    fs::path read1 = folder /= "test_1.fq";
    std::ofstream(read1.string());

    _indexProp->setR1("/reads/test_1.fq");
    _indexProp->setIndexFileName("Test");
    _indexProp->setOutputFile();
    _indexProp->setBuildDir("../build");
    std::string expectedBash = "bash "
                        + _indexProp->getBuildDir().string() + "/preprocess.sh -r "
            + fs::current_path().string()+ "/reads/test_1.fq -o "
            + fs::current_path().string() + " -f Test -u ../build/bin/";
    std::string outputBash = _indexProp->createBash();
    fs::remove(_indexProp->getR1());

    EXPECT_EQ(expectedBash, outputBash);

}
//======================================================================
TEST_F(TestIndexProp, createBash5)
{
    TEST_DESCRIPTION("test create bash function: set:[R1,outputFolder, build dir] not set:[Index Filename,Read Filename, R2]");

    algo::IndexProps* _indexProp = new algo::IndexProps(true);
    fs::path folder = fs::current_path();
    folder /= "reads";
    fs::create_directory(folder);
    fs::path read1 = folder /= "test_1.fq";
    std::ofstream(read1.string());

    _indexProp->setR1("/reads/test_1.fq");
    _indexProp->setOutputFolder("outputFolder");
    _indexProp->setOutputFile();
    _indexProp->setBuildDir("../build");
    std::string expectedBash = "bash "
                        + _indexProp->getBuildDir().string() + "/preprocess.sh -r "
            + fs::current_path().string()+ "/reads/test_1.fq -o "
            + fs::current_path().string() + "/outputFolder -f Index -u ../build/bin/";
    std::string outputBash = _indexProp->createBash();
    fs::remove(_indexProp->getR1());

    EXPECT_EQ(expectedBash, outputBash);

}
//======================================================================
TEST_F(TestIndexProp, createBash_withUnzip)
{
    TEST_DESCRIPTION("test create bash function:");
    algo::IndexProps* _indexProp = new algo::IndexProps(true);
    std::ofstream("test.fq");
    _indexProp->setR1("test.fq.gz");
    _indexProp->setBuildDir("../build");
    _indexProp->setOutputFile();
    _indexProp->setReadFileType(algo::FileType::GZ);
    std::string expectedBash = "bash "
                        + _indexProp->getBuildDir().string() + "/preprocess.sh -r "
            + fs::current_path().string()+ "/test.fq.gz -o "
            + fs::current_path().string() + " -f Index -u ../build/bin/ -z 1";
    std::string outputBash = _indexProp->createBash();
    fs::remove(_indexProp->getOutputFile());
    if (fs::is_empty(_indexProp->getOutputFolder())){
        fs::remove(_indexProp->getOutputFolder());
    }
    fs::remove(_indexProp->getR1());

    EXPECT_EQ(expectedBash, outputBash);


}

//======================================================================
TEST_F(TestIndexProp, createBash_withRevComp)
{
    TEST_DESCRIPTION("test create bash function");

    algo::IndexProps* _indexProp = new algo::IndexProps(true);
    std::ofstream("test.fq");
    _indexProp->setR1("test.fq");
    _indexProp->setBuildDir("../build");
    _indexProp->setOutputFile();
    _indexProp->setRevCompFlag(true);
    std::string expectedBash = "bash "
            + _indexProp->getBuildDir().string() + "/preprocess.sh -r "
            + fs::current_path().string()+ "/test.fq -o "
            + fs::current_path().string() + " -f Index -u ../build/bin/ -c 1";
    std::string outputBash = _indexProp->createBash();
    fs::remove(_indexProp->getOutputFile());
    if (fs::is_empty(_indexProp->getOutputFolder())){
        fs::remove(_indexProp->getOutputFolder());
    }
    fs::remove(_indexProp->getR1());

    EXPECT_EQ(expectedBash, outputBash);

}
//======================================================================
TEST_F(TestIndexProp, createBash_withUnzipPairedRevComp)
{
    TEST_DESCRIPTION("test create bash function");
    algo::IndexProps* _indexProp = new algo::IndexProps(true);
    fs::path folder = fs::current_path();
    folder /= "reads";
    fs::create_directory(folder);
    fs::path read1 = folder;
    fs::path read2 = folder;
    read1 /= "test_1.fq.gz";
    std::ofstream(read1.string());
    read2 /= "test_2.fq.gz";
    std::ofstream(read2.string());

    _indexProp->setR1("/reads/test_1.fq.gz");
    _indexProp->setR2("/reads/test_2.fq.gz");
    _indexProp->setPairedReadsFlag(true);
    _indexProp->setReadFileType(algo::FileType::GZ);
    _indexProp->setRevCompFlag(true);
    _indexProp->setOutputFile();
    _indexProp->setBuildDir("../build");
    std::string expectedBash = "bash "
            + _indexProp->getBuildDir().string() + "/preprocess.sh -r "
            + fs::current_path().string()+ "/reads/test_1.fq.gz -o "
            + fs::current_path().string() + " -f Index -u ../build/bin/ -z 1 -p "
            + fs::current_path().string()+ "/reads/test_2.fq.gz -c 1";
    std::string outputBash = _indexProp->createBash();
    fs::remove(_indexProp->getR1());
    fs::remove(_indexProp->getR2());
    EXPECT_EQ(expectedBash, outputBash);

}

//======================================================================
TEST_F(TestIndexProp, createBash_withMultipleIndexes)
{
    TEST_DESCRIPTION("test create bash function");

    algo::IndexProps* _indexProp = new algo::IndexProps(true);

    std::ofstream("test_R1.fq.gz");
    _indexProp->setR1("test_R1.fq.gz");
    _indexProp->setOutputFolder("outputfolder");
    _indexProp->setBuildDir("../build");
    _indexProp->setNumOfIndexes(5);
    _indexProp->setOutputFile();

    std::string expectedBash = "bash "
             + _indexProp->getBuildDir().string() + "/preprocess.sh -r "
             + fs::current_path().string()+ "/test_R1.fq.gz -o "
             + fs::current_path().string()+ "/outputfolder -f Index -u ../build/bin/ -n 5";
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
    _indexProp->setOutputFile();

    _indexProp->createPPFSet();
    std::string expectedPPFN1 =  fs::current_path().string() + "/outputfolder/Index.fasta";
    std::map<fs::path, std::pair<u_int, u_int>> outputPPFNs = _indexProp->getPreProcessedFastas();
    std::string outputPPFN1 = outputPPFNs.begin()->first.string() ;
    fs::remove(_indexProp->getR1());

    if (fs::is_empty(_indexProp->getOutputFolder())){
        fs::remove(_indexProp->getOutputFolder());
    }
    EXPECT_EQ(expectedPPFN1, outputPPFN1);
}
//======================================================================
TEST_F(TestIndexProp, createPPFSet2)
{
    algo::IndexProps* _indexProp = new algo::IndexProps(true);
    std::ofstream("test.fq.gz");

    _indexProp->setR1("test.fq.gz");
    _indexProp->setOutputFolder("outputfolder/");
    _indexProp->setBuildDir("../build");
    _indexProp->setNumOfIndexes(1);
    _indexProp->setReadSetName("reads");
    _indexProp->setOutputFile();

    _indexProp->createPPFSet();
    std::string expectedPPFN1 =  fs::current_path().string() + "/outputfolder/Index_reads.fasta";
    std::map<fs::path, std::pair<u_int, u_int>> outputPPFNs = _indexProp->getPreProcessedFastas();
    std::string outputPPFN1 = outputPPFNs.begin()->first.string() ;
    fs::remove(_indexProp->getR1());

    if (fs::is_empty(_indexProp->getOutputFolder())){
        fs::remove(_indexProp->getOutputFolder());
    }


    EXPECT_EQ(expectedPPFN1, outputPPFN1);
}
//======================================================================
TEST_F(TestIndexProp, createPPFSet3)
{
    algo::IndexProps* _indexProp = new algo::IndexProps(true);
    std::ofstream("test.fq.gz");
    _indexProp->setR1("test.fq.gz");
    _indexProp->setOutputFolder("outputfolder/");
    _indexProp->setBuildDir("../build");
    _indexProp->setNumOfIndexes(2);
    _indexProp->setOutputFile();
    _indexProp->createPPFSet();
    std::string expectedPPFN1 =  fs::current_path().string() +  "/outputfolder/Index_0.fasta";
    std::string expectedPPFN2 =  fs::current_path().string() + "/outputfolder/Index_1.fasta";

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
TEST_F(TestIndexProp, createPPFSet4)
{
    algo::IndexProps* _indexProp = new algo::IndexProps(true);
    std::ofstream("test.fq.gz");
    _indexProp->setR1("test.fq.gz");
    _indexProp->setOutputFolder("outputfolder/");
    _indexProp->setBuildDir("../build");
    _indexProp->setNumOfIndexes(2);
    _indexProp->setReadSetName("reads");
    _indexProp->setOutputFile();
    _indexProp->createPPFSet();
    std::string expectedPPFN1 =  fs::current_path().string() +  "/outputfolder/Index_reads_0.fasta";
    std::string expectedPPFN2 =  fs::current_path().string() + "/outputfolder/Index_reads_1.fasta";

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
    _indexProp->setNumOfReads(10);
    _indexProp->setOutputFolder("outputfolder/");
    _indexProp->setBuildDir("../build");
    _indexProp->setNumOfIndexes(2);
    _indexProp->setIndexFileName("output");
    _indexProp->setOutputFile();
    _indexProp->saveIndexProps("indexProps.ini");
    EXPECT_TRUE(fs::exists("indexProps.ini"));
    fs::remove(_indexProp->getR1());

    if (fs::is_empty(_indexProp->getOutputFolder())){
        fs::remove(_indexProp->getOutputFolder());
    }
}

//======================================================================
TEST_F(TestIndexProp, countReads)
{
    //algo::IndexProps* _indexProp = new algo::IndexProps(true);
    //countNumOfReads();



}





}
