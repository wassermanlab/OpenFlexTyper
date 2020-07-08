﻿#include "indexPropsClass.h"

namespace algo {

IndexProps::IndexProps()
{}

std::string IndexProps::createBash(){
    std::string bashargs = "bash preprocess.sh";
    bashargs += " -r " + _R1.string();
    bashargs += " -o " + _outputFolder.string();
    bashargs += " -f " + _outputFile.string();
    fs::path pathToUtils = _buildDir;
    pathToUtils  /= "bin/";
    bashargs += " -u " + pathToUtils.string();
    if (_readFileType == algo::FileType::GZ) {bashargs += " -z 1"; }
    if (_pairedReads) {bashargs += " -p " + _R2.string() ;}
    if (_revComp){bashargs += " -c 1";}

    return bashargs;
}
//================= PARAMETER GETTERS ========================
uint IndexProps::getNumOfReads() const {return _numOfReads;}

bool IndexProps::getDelFQFlag() const {return _delFQ;}
bool IndexProps::getDelFastaFlag() const {return _delFasta;}
bool IndexProps::getRevCompFlag() const {return _revComp;}
bool IndexProps::getPairedReadsFlag() const {return _pairedReads;}

const std::string& IndexProps::getReadSetName() const {return _readSetName;}
const algo::FileType& IndexProps::getReadFileType()const {return _readFileType;}

//==================== PARAMETER SETTERS ===================
void IndexProps::setNumOfReads(uint numOfReads) {_numOfReads = numOfReads;}

void IndexProps::setDelFQFlag(bool delFQ){ _delFQ = delFQ;}
void IndexProps::setDelFastaFlag(bool delFasta){ _delFasta = delFasta;}
void IndexProps::setRevCompFlag(bool revComp){ _revComp = revComp;}
void IndexProps::setPairedReadsFlag(bool pairedReads){ _pairedReads = pairedReads;}

void IndexProps::setReadSetName(const std::string readSetName){_readSetName = readSetName;}
void IndexProps::setReadFileType(const algo::FileType& readFileType){_readFileType = readFileType;}

//====================== FILE GETTERS ======================
const fs::path& IndexProps::getBuildDir() const {return _buildDir;}
const fs::path& IndexProps::getOutputFile() const {return _outputFile;}
const fs::path& IndexProps::getOutputFolder()const {return _outputFolder;}

const fs::path& IndexProps::getReadFQ()const {return _readFQ;}
const fs::path& IndexProps::getR1()const {return _R1;}
const fs::path& IndexProps::getR2()const {return _R2;}

const fs::path& IndexProps::getPreProcessedFasta()const {return _preProcessedFasta;}
const std::set<fs::path>& IndexProps::getIndexSet() const {return _indexSet;}

//====================== FILE SETTERS ======================
void IndexProps::setReadFQ(const fs::path& readFile)
{       _readFQ = readFile;   }
void IndexProps::setR1(const fs::path& readFile)
{       _R1 = readFile;   }
void IndexProps::setR2(const fs::path& readFile)
{       _R2 = readFile;   }


void IndexProps::delR1(){
    fs::remove(_R1);
}
void IndexProps::delR2(){
    fs::remove(_R2);
}
void IndexProps::delReadFQ(){
    fs::remove(_readFQ);
}
void IndexProps::delReadFasta(){
    fs::remove(_preProcessedFasta);
}
void IndexProps::setBuildDir(const fs::path &buildDir)
{        _buildDir = buildDir;   }
void IndexProps::setOutputFile(const fs::path& outputFile)
{        _outputFile = outputFile;   }
void IndexProps::setOutputFolder(const fs::path& outputFolder)
{        _outputFolder = outputFolder;    }

void IndexProps::setPreProcessedFasta(const fs::path& preProcessedFasta)
{       _preProcessedFasta = preProcessedFasta; }
void IndexProps::setIndexSet(std::set<fs::path>& indexes)
{        _indexSet = indexes;   }
void IndexProps::addToIndexSet(const fs::path& index){
    _indexSet.insert(index);
}

IndexProps::~IndexProps()
{}
}