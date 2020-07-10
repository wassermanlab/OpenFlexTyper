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
                  bool refOnly,
                  SearchType searchType,
                  bool multithread,
                  uint overlap,
                  bool returnMatchesOnly,
                  bool kmerCounts,
                  uint stride,
                  uint maxOccurences,
                  uint maxThreads,
                  bool flagOverCountedKmers,
                  bool ignoreNonUniqueKmers,
                  bool crossover,
                  bool printSearchTime,
                  uint maxKmers,
                  uint totalKmers,
                  bool printInputs)
{
    setPathToQueryFile(pathToQueryFile);
    setKmerSize(kmerSize);
    setReadLength(readLength);
    loadIndexProps(indexPropsFile, printInputs);
    setOutputFolder(outputFolder);
    setRefOnlyFlag(refOnly);
    setSearchType(searchType);
    setMultithreadFlag(multithread);
    setOverlap(overlap);
    setMatchesOnlyFlag(returnMatchesOnly);
    setKmerCountsFlag(kmerCounts);
    setStride(stride);
    setMaxOcc(maxOccurences);
    setMaxThreads(maxThreads);
    setOverCountedFlag(flagOverCountedKmers);
    setIgnoreNonUniqueKmersFlag(ignoreNonUniqueKmers);
    setCrossoverFlag(crossover);
    setPrintSearchTimeFlag(printSearchTime);
    setMaxKmers(maxKmers);
    setMaxTotalKmers(totalKmers);

    fs::path outputFile = _outputFolder;
    outputFile /= _readSetName += _pathToQueryFile;
    std::cout << "Query search results will be save in " << outputFile << std::endl;
    setOutputFile(outputFile);

}

//================= INIT From Q SETTINGS ========================
void FTProp::initFromQSettings (std::string configFile, bool printInputs){

    QString m_sSettingsFile(configFile.c_str());
    QSettings settings(m_sSettingsFile, QSettings::NativeFormat);

    fs::path       pathToQueryFile         = settings.value("queryFile").toString().toStdString();
    uint           kmerSize                = settings.value("kmerSize").toInt();
    uint           readLength              = settings.value("readLength").toInt();
    fs::path       indexPropsFile          = settings.value("indexPropsFile").toString().toStdString();
    fs::path       outputFolder            = settings.value("outputFolder").toString().toStdString();
    bool           refOnly                 = settings.value("refOnly").toBool();
    ft::SearchType searchType              = static_cast<ft::SearchType>(settings.value("searchType").toString().toStdString()) ;
    bool           multithread             = settings.value("multithread").toBool();
    bool           matchingReads           = settings.value("matchingReads").toBool();
    uint           overlap                 = settings.value("overlap").toInt();
    bool           returnMatchesOnly       = settings.value("return_only_positive_matches").toBool();
    bool           kmerCounts              = settings.value("kmerCounts").toBool();
    uint           stride                  = settings.value("stride").toInt();
    uint           maxOccurences           = settings.value("maxOccurences").toInt();
    uint           numOfThreads            = settings.value("numOfThreads").toInt();
    bool           flagOverCountedKmers    = settings.value("flagOverCountedKmers").toBool();
    bool           ignoreNonUniqueKmers    = settings.value("ignoreNonUniqueKmers").toBool();
    bool           crossover               = settings.value("crossover").toBool();
    bool           printSearchTime         = settings.value("printSearchTime").toBool();
    uint           maxKmersPerQuery        = settings.value("maxKmersPerQuery").toInt();
    uint           maxTotalKmers           = settings.value("maxTotalKmers").toInt();

    if (printInputs){
    std::cout << "pathToQueryFile               : " << pathToQueryFile <<  std::endl;
    std::cout << "kmerSize                      : " << kmerSize <<  std::endl;
    std::cout << "readLength                    : " << readLength <<  std::endl;
    std::cout << "indexPropsFile                : " << indexPropsFile <<  std::endl;
    std::cout << "outputFolder                  : " << outputFolder <<  std::endl;
    std::cout << "refOnly                       : " << refOnly <<  std::endl;
    std::cout << "searchType                    : " << searchType <<  std::endl;
    std::cout << "multithread                   : " << multithread <<  std::endl;
    std::cout << "overlap                       : " << overlap <<  std::endl;
    std::cout << "return_only_positive_matches  : " << returnMatchesOnly <<  std::endl;
    std::cout << "kmerCounts                    : " << kmerCounts << std::endl;
    std::cout << "stride                        : " << stride << std::endl;
    std::cout << "maxOccurences                 : " << maxOccurences << std::endl;
    std::cout << "numOfThreads                  : " << numOfThreads << std::endl;
    std::cout << "flagOverCountedKmers          : " << flagOverCountedKmers << std::endl;
    std::cout << "ignoreNonUniqueKmers          : " << ignoreNonUniqueKmers << std::endl;
    std::cout << "printSearchTime               : " << printSearchTime << std::endl;
    std::cout << "maxKmersPerQuery              : " << maxKmersPerQuery << std::endl;
    std::cout << "maxTotalKmers                 : " << maxTotalKmers << std::endl;
    std::cout << "matchingReads                 : " << matchingReads << std::endl;
    }
    init(pathToQueryFile, kmerSize, readLength,
         indexPropsFile, outputFolder, refOnly,
         searchType, multithread, overlap,
         returnMatchesOnly, kmerCounts, stride,
         maxOccurences, numOfThreads, flagOverCountedKmers,
         ignoreNonUniqueKmers, crossover, printSearchTime,
         maxKmersPerQuery, maxTotalKmers, printInputs);
}

//================= Load Index Props ========================
void FTProp::loadIndexProps(const fs::path &_indexPropsFile, bool printInputs){
    QSettings isettings(_indexPropsFile.string().c_str(), QSettings::IniFormat);

    setPairedReadsFlag(isettings.value("pairedReads").toBool());
    setRevCompFlag(isettings.value("revComp").toBool());
    setBuildDir(isettings.value("buildDirectory").toString().toStdString());
    setIndexDir(isettings.value("indexDirectory").toString().toStdString());
    setReadSetName(isettings.value("readSetName").toString().toStdString());

    if (_pairedReads){
       setInputFastQ(isettings.value("R1").toString().toStdString());
       setR1(isettings.value("R1").toString().toStdString());
       setR2(isettings.value("R2").toString().toStdString());
    } else {
       setInputFastQ(isettings.value("readFQ").toString().toStdString());
    }

    setNumOfReads(isettings.value("numOfReads").toUInt());
    setNumOfIndexes(isettings.value("numOfIndexes").toUInt());

    std::map<fs::path, uint> indexSet;

    int size = isettings.beginReadArray("IndexFiles");
    for (int i = 0; i < size; ++i) {
        isettings.setArrayIndex(i);
        std::string fileName = isettings.value("fileName").toString().toStdString();
        u_int offset = isettings.value("offset").toInt();
        indexSet[fileName] = offset;
    }
    isettings.endArray();
    setIndexSet(indexSet);

    if (printInputs){
    std::cout << "Properties loaded from Index File     " <<  std::endl;
    std::cout << "Paired Reads      : " << _pairedReads <<  std::endl;
    std::cout << "reverse Comp      : " << _revComp <<  std::endl;
    std::cout << "build Directory   : " << _buildDir <<  std::endl;
    std::cout << "index Directory   : " << _indexDir <<  std::endl;
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

}

//================= PARAMETER GETTERS ========================
SearchType FTProp::getSearchType(){return _searchType;}
std::string FTProp::getReadSetName(){return _readSetName;}
uint FTProp::getKmerSize() const {return _kmerSize;}
uint FTProp::getOverlap() const {return _overlap;}
uint FTProp::getStride() const {return _stride;}
uint FTProp::getMaxKmers() const {return _maxKmers;}
uint FTProp::getReadLength() const {return _readLength;}
uint FTProp::getMaxOcc() const {return _maxOccurences;}
uint FTProp::getMaxThreads() const {return _maxThreads;}
uint FTProp::getMaxKmersPerQuery() const {return _maxKmersPerQuery;}
uint FTProp::getMaxTotalKmers() const {return _maxTotalKmers;}
uint FTProp::getNumOfIndexes() const {return _numOfIndexes;}
uint FTProp::getNumOfReads() const {return _numOfReads;}

//==================== PARAMETER SETTERS ===================
void FTProp::setSearchType(ft::SearchType searchType) {_searchType = searchType;}
void FTProp::setReadSetName(std::string readSetName){_readSetName = readSetName;}
void FTProp::setKmerSize(uint kmerSize) {_kmerSize = kmerSize;}
void FTProp::setOverlap(uint overlap) {_overlap = overlap;}
void FTProp::setStride(uint stride) {_stride = stride;}
void FTProp::setMaxKmers(uint maxKmers) {_maxKmers = maxKmers;}
void FTProp::setReadLength(uint readLength) {_readLength = readLength;}
void FTProp::setMaxOcc(uint maxOcc) {_maxOccurences = maxOcc;}
void FTProp::setMaxThreads(uint maxThreads) {_maxThreads = maxThreads;}
void FTProp::setMaxKmersPerQuery(uint maxKmersPerQ) {_maxKmersPerQuery = maxKmersPerQ;}
void FTProp::setMaxTotalKmers(uint maxTotalKmers) {_maxTotalKmers = maxTotalKmers;}
void FTProp::setNumOfIndexes(uint numOfIndexes) {_numOfIndexes = numOfIndexes;}
void FTProp::setNumOfReads(uint numOfReads) {_numOfReads = numOfReads;}

//====================== FLAG GETTERS ======================
bool FTProp::getKmerCountsFlag() const {return _kmerCounts;}
bool FTProp::getMultithreadFlag() const {return _multithread;}
bool FTProp::getRefOnlyFlag() const {return _refOnly;}
bool FTProp::getMatchesOnlyFlag() const {return _matchesOnly;}
bool FTProp::getOverCountedFlag() const {return _overcounted;}
bool FTProp::getIgnoreNonUniqueKmersFlag() const {return _ignoreNonUniqueKmers;}
bool FTProp::getCrossoverFlag() const {return _crossover;}
bool FTProp::getPrintSearchTimeFlag() const {return _matchesOnly;}
bool FTProp::getPairedReadFlag() const {return _pairedReads;}
bool FTProp::getRevCompFlag() const {return _revComp;}
bool FTProp::getMatchingReadsFlag() const{return _matchingReads;}

//====================== FLAG SETTERS ======================
void FTProp::setKmerCountsFlag(bool kmerCounts){ _kmerCounts = kmerCounts;}
void FTProp::setMultithreadFlag(bool multithread){_multithread = multithread;}
void FTProp::setRefOnlyFlag(bool refOnly){ _refOnly = refOnly;}
void FTProp::setMatchesOnlyFlag(bool matchesOnly){ _matchesOnly = matchesOnly;}
void FTProp::setOverCountedFlag(bool overcounted){ _overcounted = overcounted;}
void FTProp::setIgnoreNonUniqueKmersFlag(bool ignoreNonUnique){ _ignoreNonUniqueKmers = ignoreNonUnique;}
void FTProp::setCrossoverFlag(bool crossover){ _crossover = crossover;}
void FTProp::setPrintSearchTimeFlag(bool printSearchTime){ _printSearchTime = printSearchTime;}
void FTProp::setPairedReadsFlag(bool pairedReads) {_pairedReads = pairedReads;}
void FTProp::setRevCompFlag(bool revComp){ _revComp = revComp;}
void FTProp::setMatchingReadsFlag(bool matchingReads){_matchingReads = matchingReads;}
//====================== FILE SETTERS ======================
void FTProp::setPathToQueryFile(const fs::path& pathToQueryFile){_pathToQueryFile = pathToQueryFile; }
void FTProp::setIndexDir(const fs::path& indexDirectory){ _indexDir = indexDirectory;}
void FTProp::setOutputFolder(const fs::path& outputFolder){ _outputFolder = outputFolder;}
void FTProp::setOutputFile(const fs::path& outputFile){ _outputFile = outputFile;}
void FTProp::setInputFastQ(const fs::path& inputFastQ){_inputFastQ = inputFastQ;}
void FTProp::setIndexSet(std::map<fs::path, uint>& indexes){_indexSet = indexes;}
void FTProp::setBuildDir(const fs::path& buildDirectory){_buildDir = buildDirectory;}
void FTProp::setR1(const fs::path& _read1){ _R1 = _read1;}
void FTProp::setR2(const fs::path& _read2){ _R2 = _read2;}

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

FTProp::~FTProp()
{
}


}
