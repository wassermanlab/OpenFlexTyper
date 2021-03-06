////////////////////////////////////////////////////////////////////////
/// \copyright Copyright (c) 2020, Wasserman lab
////////////////////////////////////////////////////////////////////////

#include <set>
#include <iostream>
#include <map>
#include "ftPropsClass.h"

namespace ft {

FTProp::FTProp()
{}

//=============== INIT ==============================

void FTProp::init(const fs::path &pathToQueryFile,
                  uint kmerSize,
                  uint readLength,
                  const fs::path &indexPropsFile,
                  const fs::path &outputFolder,
                  const fs::path &outputFile,
                  bool refOnly,
                  bool revCompSearch,
                  SearchType searchType,
                  bool multithread,
                  uint overlap,
                  bool returnMatchesOnly,
                  uint stride,
                  uint maxOccurences,
                  uint numOfThreads,
                  bool outputNonUniqueKmers,
                  bool outputOverCountedKmers,
                  bool ignoreNonUniqueKmers,
                  bool ignoreOverCountedKmers,
                  bool countAsPairs,
                  bool uniqueReads,
                  bool crossover,                  
                  uint maxKmersPerQuery,
                  uint maxTotalKmers,
                  bool printInputs,
                  bool matchingReads)
{
    _pathToQueryFile = pathToQueryFile;
    _kmerSize = kmerSize;
    _readLength = readLength;
    loadIndexProps(indexPropsFile, printInputs);
    setOutputFolder(outputFolder);
    _refOnly = refOnly;
    _revCompSearch = revCompSearch;
    _searchType = searchType;
    _multithread = multithread;
    _overlap = overlap;
    _matchesOnly = returnMatchesOnly;
    _stride = stride;
    _maxOccurences = maxOccurences;
    _maxThreads = numOfThreads;
    _countAsPairs = countAsPairs;
    _uniqueReads = uniqueReads;
    _crossover = crossover;
    _maxKmersPerQuery = maxKmersPerQuery;
    _maxTotalKmers = maxTotalKmers;
    _matchingReads = matchingReads;
    _outputFile = outputFile;
    _verbose = printInputs;

    if (outputOverCountedKmers){setFlagToOutput(ft::FlagType::OCK);}
    if (outputNonUniqueKmers){setFlagToOutput(ft::FlagType::NUK);}

    if (ignoreOverCountedKmers){setFlagToNotCount(ft::FlagType::OCK);}
    if (ignoreNonUniqueKmers){setFlagToNotCount(ft::FlagType::NUK);}

    if (_searchType == CENTERED && _overlap == 0){ LogClass::ThrowRuntimeError("overlap must be > 0 for centered search");}

    if (printInputs){
        std::cout << "pathToQueryFile               : " << pathToQueryFile <<  std::endl;
        std::cout << "kmerSize                      : " << kmerSize <<  std::endl;
        std::cout << "readLength                    : " << readLength <<  std::endl;
        std::cout << "indexPropsFile                : " << indexPropsFile <<  std::endl;
        std::cout << "outputFolder                  : " << outputFolder <<  std::endl;
        std::cout << "refOnly                       : " << refOnly <<  std::endl;
        std::cout << "revCompSearch                 : " << revCompSearch <<  std::endl;
        std::cout << "searchType                    : " << searchType <<  std::endl;
        std::cout << "multithread                   : " << multithread <<  std::endl;
        std::cout << "overlap                       : " << overlap <<  std::endl;
        std::cout << "return_only_positive_matches  : " << returnMatchesOnly <<  std::endl;
        std::cout << "stride                        : " << stride << std::endl;
        std::cout << "maxOccurences                 : " << maxOccurences << std::endl;
        std::cout << "numOfThreads                  : " << numOfThreads << std::endl;
        std::cout << "outputNonUniqueKmers          : " << outputNonUniqueKmers << std::endl;
        std::cout << "outputOverCountedKmers        : " << outputOverCountedKmers << std::endl;
        std::cout << "ignoreNonUniqueKmers          : " << ignoreNonUniqueKmers << std::endl;
        std::cout << "ignoreOverCountedkmers        : " << ignoreOverCountedKmers << std::endl;
        std::cout << "countAsPairs                  : " << countAsPairs << std::endl;
        std::cout << "uniqueReads                   : " << uniqueReads << std::endl;
        std::cout << "maxKmersPerQuery              : " << maxKmersPerQuery << std::endl;
        std::cout << "maxTotalKmers                 : " << maxTotalKmers << std::endl;
        std::cout << "matchingReads                 : " << matchingReads << std::endl;
        std::cout << "Query search results will be save in " << _outputFile << std::endl;
        std::cout << "FTProps Class verbose " << _verbose << std::endl;
    }
    if (LogClass::Log.is_open()){
        LogClass::Log << "======== Settings " << "======== " << std::endl;
        LogClass::Log << "pathToQueryFile               : " << pathToQueryFile <<  std::endl;
        LogClass::Log << "kmerSize                      : " << kmerSize <<  std::endl;
        LogClass::Log << "readLength                    : " << readLength <<  std::endl;
        LogClass::Log << "indexPropsFile                : " << indexPropsFile <<  std::endl;
        LogClass::Log << "outputFolder                  : " << outputFolder <<  std::endl;
        LogClass::Log << "refOnly                       : " << refOnly <<  std::endl;
        LogClass::Log << "revCompSearch                 : " << revCompSearch <<  std::endl;
        LogClass::Log << "searchType                    : " << searchType <<  std::endl;
        LogClass::Log << "multithread                   : " << multithread <<  std::endl;
        LogClass::Log << "overlap                       : " << overlap <<  std::endl;
        LogClass::Log << "return_only_positive_matches  : " << returnMatchesOnly <<  std::endl;
        LogClass::Log << "stride                        : " << stride << std::endl;
        LogClass::Log << "maxOccurences                 : " << maxOccurences << std::endl;
        LogClass::Log << "numOfThreads                  : " << numOfThreads << std::endl;
        LogClass::Log << "outputNonUniqueKmers          : " << outputNonUniqueKmers << std::endl;
        LogClass::Log << "outputOverCountedKmers        : " << outputOverCountedKmers << std::endl;
        LogClass::Log << "ignoreNonUniqueKmers          : " << ignoreNonUniqueKmers << std::endl;
        LogClass::Log << "ignoreOverCountedkmers        : " << ignoreOverCountedKmers << std::endl;
        LogClass::Log << "countAsPairs                  : " << countAsPairs << std::endl;
        LogClass::Log << "uniqueReads                   : " << uniqueReads << std::endl;
        LogClass::Log << "maxKmersPerQuery              : " << maxKmersPerQuery << std::endl;
        LogClass::Log << "maxTotalKmers                 : " << maxTotalKmers << std::endl;
        LogClass::Log << "matchingReads                 : " << matchingReads << std::endl;
        LogClass::Log << "Query search results will be save in " << _outputFile << std::endl;
    }
}

void FTProp::setVerbose(bool verbose)
{
    _verbose = verbose;
}
bool FTProp::isVerbose() const
{
    return _verbose;
}
//================= INIT From Q SETTINGS ========================
void FTProp::initFromQSettings (FTProp::CmdLineArg& arg){

    QString m_sSettingsFile(arg.iniFile.c_str());
    QSettings settings(m_sSettingsFile, QSettings::NativeFormat);

    fs::path       pathToQueryFile         = settings.value("queryFile").toString().toStdString();
    uint           kmerSize                = settings.value("kmerSize").toInt();
    uint           readLength              = settings.value("readLength").toInt();
    fs::path       indexPropsFile          = settings.value("indexPropsFile").toString().toStdString();
    fs::path       outputFolder            = settings.value("outputFolder").toString().toStdString();
    bool           refOnly                 = settings.value("refOnly").toBool();
    bool           revCompSearch           = settings.value("revCompSearch").toBool();
    ft::SearchType searchType              = static_cast<ft::SearchType>(settings.value("searchType").toString().toStdString()) ;
    bool           multithread             = settings.value("multithread").toBool();
    bool           matchingReads           = settings.value("matchingReads").toBool();
    uint           overlap                 = settings.value("overlap").toInt();
    bool           returnMatchesOnly       = settings.value("return_only_positive_matches").toBool();
    uint           stride                  = settings.value("stride").toInt();
    uint           maxOccurences           = settings.value("maxOccurences").toInt();
    uint           numOfThreads            = settings.value("numOfThreads").toInt();
    bool           outputOverCountedKmers    = settings.value("outputOverCountedKmers").toBool();
    bool           outputNonUniqueKmers      = settings.value("outputNonUniqueKmers").toBool();
    bool           ignoreNonUniqueKmers    = settings.value("ignoreNonUniqueKmers").toBool();
    bool           ignoreOverCountedKmers  = settings.value("ignoreOverCountedKmers").toBool();
    bool           countAsPairs            = settings.value("countAsPairs").toBool();
    bool           uniqueReads             = settings.value("uniqueReads").toBool();
    bool           crossover               = settings.value("crossover").toBool();
    uint           maxKmersPerQuery        = settings.value("maxKmersPerQuery").toInt();
    uint           maxTotalKmers           = settings.value("maxTotalKmers").toInt();

    fs::path queryOutputFile;
    if (arg.outputFile.empty()){
        queryOutputFile = _outputFolder;
        fs::path queryFileName = _pathToQueryFile.filename();
        queryFileName.replace_extension();
        queryOutputFile /= queryFileName+= std::string("_") += _readSetName += "_Results.tsv";
    }
    else {
        queryOutputFile = arg.outputFile;
    }
    if (arg.kmerSize)
        kmerSize = arg.kmerSize;
    if (arg.stride)
        stride = arg.stride;
    if (arg.maxOccurences)
        maxOccurences = arg.maxOccurences;
    if (arg.unique)
        ignoreNonUniqueKmers = arg.unique;

    init(pathToQueryFile, kmerSize, readLength,
         indexPropsFile, outputFolder, queryOutputFile, refOnly, revCompSearch,
         searchType, multithread, overlap,
         returnMatchesOnly, stride,
         maxOccurences, numOfThreads, outputNonUniqueKmers, outputOverCountedKmers,
         ignoreNonUniqueKmers, ignoreOverCountedKmers, countAsPairs, uniqueReads, crossover,
         maxKmersPerQuery, maxTotalKmers, arg.verbose, matchingReads);

}

void FTProp::printToStdOut(const std::string outputString) const {
    if (_verbose && LogClass::Log.is_open() ){
        LogClass::Log  << outputString << std::endl;
    }
}
//================= Load Index Props ========================
void FTProp::loadIndexProps(const fs::path &_indexPropsFile, bool printInputs){
    QSettings isettings(_indexPropsFile.string().c_str(), QSettings::IniFormat);

    _pairedReads = isettings.value("pairedReads").toBool();
    _indexRevComp = isettings.value("revComp").toBool();
    _buildDir = isettings.value("buildDirectory").toString().toStdString();
    _indexDir = isettings.value("indexDirectory").toString().toStdString();
    _readSetName = isettings.value("readSetName").toString().toStdString();
    _indexFileName = isettings.value("indexFileName").toString().toStdString();

    if (_pairedReads){
       _inputFastQ = isettings.value("R1").toString().toStdString();
       _R1 = isettings.value("R1").toString().toStdString();
       _R2 = isettings.value("R2").toString().toStdString();
    } else {
       _inputFastQ = isettings.value("R1").toString().toStdString();
    }

    _numOfReads = isettings.value("numOfReads").toUInt();
    _numOfIndexes = isettings.value("numOfIndexes").toUInt();

    std::map<fs::path, uint> indexSet;

    int size = isettings.beginReadArray("IndexFiles");
    for (int i = 0; i < size; ++i) {
        isettings.setArrayIndex(i);
        fs::path fileName = isettings.value("fileName").toString().toStdString();
        u_int offset = isettings.value("offset").toInt();
        printToStdOut("index fileName " + fileName.string());
        indexSet[fileName] = offset;
    }
    isettings.endArray();
    _indexSet = indexSet;

    if (printInputs){
        std::cout << "Properties loaded from Index File     " <<  std::endl;
        std::cout << "Paired Reads      : " << _pairedReads <<  std::endl;
        std::cout << "reverse Comp      : " << _indexRevComp <<  std::endl;
        std::cout << "build Directory   : " << _buildDir <<  std::endl;
        std::cout << "index Directory   : " << _indexDir <<  std::endl;
        std::cout << "Index File Name   : " << _indexFileName <<  std::endl;
        std::cout << "read Set Name     : " << _readSetName <<  std::endl;
        std::cout << "Read FQ           : " << _inputFastQ <<  std::endl;
        std::cout << "Number of Reads   : " << _numOfReads <<  std::endl;
        std::cout << "Number of Indexes : " << _numOfIndexes <<  std::endl;
    if (_pairedReads)
        {std::cout << "R1                : " << _R1 <<  std::endl;
         std::cout << "R2                : " << _R2 <<  std::endl;
        }
    for (auto index : _indexSet){
        std::cout << "Index File : " << index.first << " Offset: " << index.second <<  std::endl;
    }
    }
    if (LogClass::Log.is_open()){
        LogClass::Log << "Properties loaded from Index File     " <<  std::endl;
        LogClass::Log << "Paired Reads      : " << _pairedReads <<  std::endl;
        LogClass::Log << "reverse Comp      : " << _indexRevComp <<  std::endl;
        LogClass::Log << "build Directory   : " << _buildDir <<  std::endl;
        LogClass::Log << "index Directory   : " << _indexDir <<  std::endl;
        LogClass::Log << "Index File Name   : " << _indexFileName <<  std::endl;
        LogClass::Log << "read Set Name     : " << _readSetName <<  std::endl;
        LogClass::Log << "Read FQ           : " << _inputFastQ <<  std::endl;
        LogClass::Log << "Number of Reads   : " << _numOfReads <<  std::endl;
        LogClass::Log << "Number of Indexes : " << _numOfIndexes <<  std::endl;
    if (_pairedReads)
        {LogClass::Log << "R1                : " << _R1 <<  std::endl;
         LogClass::Log << "R2                : " << _R2 <<  std::endl;
        }
    for (auto index : _indexSet){
        LogClass::Log << "Index File : " << index.first << " Offset: " << index.second <<  std::endl;
    }
    }

}

//======================================================================
void FTProp::initIndexProps( const bool pairedReads,
                             const bool revComp,
                             fs::path buildDir,
                             fs::path indexDir,
                             std::string indexFileName,
                             std::string readSetName,
                             fs::path inputFastQ,
                             uint numOfReads,
                             uint numOfIndexes,
                             bool printInputs)
{
    _pairedReads = pairedReads;
    _indexRevComp = revComp;
    _buildDir = buildDir;
    _indexDir = indexDir;
    _indexFileName = indexFileName;
    _readSetName = readSetName;
    _inputFastQ = inputFastQ;
    _numOfReads = numOfReads;
    _numOfIndexes = numOfIndexes;

    if (_countAsPairs && !_pairedReads)
    {
        LogClass::ThrowRuntimeError("Error: Cannot count as pairs as input reads arent paired");
    }


    if (printInputs){
        std::cout << "Properties loaded from Index File     " <<  std::endl;
        std::cout << "Paired Reads      : " << _pairedReads <<  std::endl;
        std::cout << "reverse Comp      : " << _indexRevComp <<  std::endl;
        std::cout << "build Directory   : " << _buildDir <<  std::endl;
        std::cout << "index Directory   : " << _indexDir <<  std::endl;
        std::cout << "Index File Name   : " << _indexFileName <<  std::endl;
        std::cout << "read Set Name     : " << _readSetName <<  std::endl;
        std::cout << "Read FQ           : " << _inputFastQ <<  std::endl;
        std::cout << "Number of Reads   : " << _numOfReads <<  std::endl;
        std::cout << "Number of Indexes : " << _numOfIndexes <<  std::endl;
    if (_pairedReads)
        {std::cout << "R1                : " << _R1 <<  std::endl;
         std::cout << "R2                : " << _R2 <<  std::endl;
        }
    for (auto index : _indexSet){
        std::cout << "Index File : " << index.first << " Offset: " << index.second <<  std::endl;
    }
    }

    if (LogClass::Log.is_open()){
    LogClass::Log << "Properties loaded from Index File     " <<  std::endl;
    LogClass::Log << "Paired Reads      : " << _pairedReads <<  std::endl;
    LogClass::Log << "index contains reverse Comp      : " << _indexRevComp <<  std::endl;
    LogClass::Log << "build Directory   : " << _buildDir <<  std::endl;
    LogClass::Log << "index Directory   : " << _indexDir <<  std::endl;
    LogClass::Log << "read Set Name     : " << _readSetName <<  std::endl;
    LogClass::Log << "Read FQ           : " << _inputFastQ <<  std::endl;
    LogClass::Log << "Number of Reads   : " << _numOfReads <<  std::endl;
    LogClass::Log << "Number of Indexes : " << _numOfIndexes <<  std::endl;
    }
}

//======================================================================
void FTProp::addToIndexSet(const fs::path& index, u_int offset){
    LogClass::Log << "add index to set " << fs::absolute(index) << std::endl;

    if (_indexSet.count(index) == 0){
        _indexSet[index] = offset;
        _numOfIndexes = _indexSet.size();
    }
}

//================= PARAMETER GETTERS ========================
SearchType FTProp::getSearchType() const {return _searchType;}
std::string FTProp::getReadSetName() const{return _readSetName;}
std::string FTProp::getIndexFileName() const{return _indexFileName;}
uint FTProp::getKmerSize() const {return _kmerSize;}
uint FTProp::getOverlap() const {return _overlap;}
uint FTProp::getStride() const {return _stride;}
uint FTProp::getReadLength() const {return _readLength;}
uint FTProp::getMaxOcc() const {return _maxOccurences;}
uint FTProp::getMaxThreads() const {return _maxThreads;}
uint FTProp::getMaxKmersPerQuery() const {return _maxKmersPerQuery;}
uint FTProp::getMaxTotalKmers() const {return _maxTotalKmers;}
uint FTProp::getNumOfIndexes() const {return _numOfIndexes;}
uint FTProp::getNumOfReads() const {return _numOfReads;}

//====================== FLAG GETTERS ======================
bool FTProp::getMultithreadFlag() const {return _multithread;}
bool FTProp::getRefOnlyFlag() const {return _refOnly;}
bool FTProp::getMatchesOnlyFlag() const {return _matchesOnly;}
bool FTProp::getCrossoverFlag() const {return _crossover;}
bool FTProp::getPairedReadFlag() const {return _pairedReads;}
bool FTProp::getCountAsPairsFlag() const {return _countAsPairs;}
bool FTProp::getRevCompSearchFlag() const {return _revCompSearch;}
bool FTProp::getIndexRevCompFlag() const {return _indexRevComp;}
bool FTProp::getMatchingReadsFlag() const{return _matchingReads;}
bool FTProp::getUniqueReadsFlag() const {return _uniqueReads;}
const std::bitset<8>& FTProp::getFlagsToOutput() const {return _flagsToOutput;}
const std::bitset<8>& FTProp::getFlagsToNotCount() const {return _flagsToNotCount;}

//====================== FILE GETTERS ======================
const fs::path& FTProp::getPathToQueryFile() const {return _pathToQueryFile;}
const fs::path& FTProp::getIndexDir() const {return _indexDir;}
const fs::path& FTProp::getOutputFolder()const {return _outputFolder;}
const fs::path& FTProp::getOutputFile() const {return _outputFile;}
const fs::path& FTProp::getInputFastQ()const {return _inputFastQ;}
const std::map<fs::path, uint>& FTProp::getIndexSet() const {return _indexSet;}
const fs::path& FTProp::getBuildDir() const {return _buildDir;}
const fs::path& FTProp::getR1() const{return _R1;}
const fs::path& FTProp::getR2() const{return _R2;}

//====================== FILE GETTERS ======================
void FTProp::setTestProps(const uint numOfReads, const uint readLength, bool revComp, bool countAsPairs){
    _numOfReads = numOfReads;
    _readLength = readLength;
    _indexRevComp = revComp;
    _countAsPairs = countAsPairs;
}

void FTProp::setOutputFolder(const fs::path& outputFolder)
{
    fs::path outfolder;
    if (outputFolder == "" or outputFolder =="."){
        LogClass::Log << "no output folder set " << std::endl;
        outfolder = fs::current_path();
    } else if (outputFolder == "../"){
        LogClass::Log << "set as parent path  " + outputFolder.string() << std::endl;
        outfolder = fs::current_path().parent_path();
    } else {
        LogClass::Log << "set absolute path as output Folder " << outputFolder.string() << std::endl;
        outfolder = fs::absolute(outputFolder);
    }
    _outputFolder = outfolder;
    LogClass::Log << _outputFolder.string();

    if (!fs::exists(_outputFolder)){
     LogClass::Log << "creating output Folder " << outputFolder.string() << std::endl;
         try {
             fs::create_directory(outputFolder);
         } catch (std::exception& e ) {
             LogClass::ThrowRuntimeError("Cannot create output folder " + _outputFolder.string());
         }
    }

    if (!fs::exists(_outputFolder))
    {
        LogClass::ThrowRuntimeError("Cannot create output folder " + _outputFolder.string());
    }
}

void FTProp::setFlagToOutput(ft::FlagType flag)
{
    _flagsToOutput.set(flag);
}
void FTProp::setFlagToNotCount(ft::FlagType flag)
{
    _flagsToNotCount.set(flag);
}

bool FTProp::countFlag(ft::FlagType flag) const
{
    return !_flagsToNotCount.test(flag);
}
bool FTProp::outputFlag(ft::FlagType flag) const
{
    return _flagsToOutput.test(flag);
}


void FTProp::resetFlagToOutput(ft::FlagType flag)
{
    _flagsToOutput.reset(flag);
}
void FTProp::resetFlagToNotCount(ft::FlagType flag)
{
    _flagsToNotCount.reset(flag);
}


//====================== STATIC FUNCTIONS ======================

std::fstream LogClass::Log;


FTProp::~FTProp()
{
}


}
