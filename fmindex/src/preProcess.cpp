#include "preProcess.h"

namespace algo {

PreProcess::PreProcess(const algo::IndexProps& indexProps)
    :_indexProps(indexProps)
{
}

PreProcess::~PreProcess()
{}

//======================================================================
void PreProcess::gunzipPairedFQ(){
    // Unzip FQGZ

        std::string unzipCMD = "gunzip -c " + _indexProps.getR1().string() + " > " + _indexProps.getReadFQ().string();
        system(unzipCMD.c_str());

        std::string unzip2CMD = "gunzip -c " + _indexProps.getR2().string()  + " >> " + _indexProps.getReadFQ().string();;
        system(unzipCMD.c_str());

}

//======================================================================
void PreProcess::combineFasta(const fs::path& file1, const fs::path& file2, const fs::path& output)
{
    std::string merge = "cat " + file1.string() + " " + file2.string() + " > " + output.string();
    system(merge.c_str());
}

//======================================================================
fs::path PreProcess::createFWDFasta(){
    // create forward fasta

    std::string seqFwdFa = "seqtk seq -A -C -U $" + _indexProps.getReadFQ().string()+ " | egrep -v '[>]' > " + _indexProps.getPreProcessedFasta().string();
    system(seqFwdFa.c_str());
    return _indexProps.getPreProcessedFasta();
}

//======================================================================
fs::path PreProcess::createRevFasta(){
    // create rev fasta
    fs::path outputfile = _indexProps.getPreProcessedFasta();
    outputfile.stem() += "_rev";
    std::string seqRevFa = "seqtk seq -A -C -U -r $" + _indexProps.getReadFQ().string()+ " | egrep -v '[>]' > " + outputfile.string();
    system(seqRevFa.c_str());
    return outputfile;
}

//======================================================================
void PreProcess::addR1R2()
{   fs::path readFiles = fs::current_path();
    readFiles.replace_filename(_indexProps.getReadSetName());

    //set R1 file
    fs::path r1 = readFiles;
    r1.stem()+= "_R1";

    //check for R1 File
     if (!fs::exists(r1)) {std::cout << "ERROR: File " << readFiles << " does not exist. Exit." << std::endl;}

    //set R2 file
    fs::path r2 = readFiles;
    r1.stem() += "_R2";

    //check for R2 file
     if (!fs::exists(r2)) {std::cout << "ERROR: File " << readFiles << " does not exist. Exit." << std::endl;}
}

//======================================================================
void PreProcess::preProcessFQ()
{
    // create fwd fasta
    fs::path fwdfasta = createFWDFasta();

    // create rev fasta
    if (_indexProps.getRevCompFlag()){
        fs::path revfasta = createRevFasta();
        combineFasta(fwdfasta, revfasta, _indexProps.getPreProcessedFasta());
    } else {
        _indexProps.setPreProcessedFasta(fwdfasta);
    }

}

//======================================================================
fs::path PreProcess::createPreProcessFasta(){
    fs::path preprocessfasta = _indexProps.getOutputFolder();
    preprocessfasta/=_indexProps.getReadSetName();
    preprocessfasta.replace_extension(".fa");
    return preprocessfasta;
}

//======================================================================
void PreProcess::processPairedReadFiles()
{
    fs::path preprocessfasta = createPreProcessFasta();
    _indexProps.setPreProcessedFasta(preprocessfasta);
    //add both read files
    addR1R2();

    if (_indexProps.getReadFileType() == algo::FileType::GZ)
    {
        gunzipPairedFQ();
    }

    preProcessFQ();



}

//======================================================================
void PreProcess::processReadFile()
{
    fs::path preprocessfasta = createPreProcessFasta();
    _indexProps.setPreProcessedFasta(preprocessfasta);

    fs::path readFiles = fs::current_path();
    readFiles.replace_filename(_indexProps.getReadSetName());
    readFiles.replace_extension(".fq");
    _indexProps.setReadFQ(readFiles);

    if (_indexProps.getReadFileType() == algo::FileType::GZ)
    {
        fs::path zippedReads = readFiles.replace_extension(".fq.gz");
        if (!fs::exists(zippedReads)) {std::cout << "ERROR: File " << zippedReads << " does not exist. Exit." << std::endl;}
        else {
        std::string unzipCMD = "gunzip -c " + zippedReads.string() + " > " + _indexProps.getReadFQ().string();
        system(unzipCMD.c_str());
        }
       }

    std::cout << "Read File: " << readFiles << std::endl;

    //check for Read File
    if (!fs::exists(_indexProps.getReadFQ())) {std::cout << "ERROR: File " << readFiles << " does not exist. Exit." << std::endl;}

    else {
        preProcessFQ();
    }

}

}
