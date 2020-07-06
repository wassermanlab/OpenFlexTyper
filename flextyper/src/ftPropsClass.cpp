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
                  const fs::path &indexLocation,
                  const fs::path &outputFolder,
                  bool refOnly,
                  SearchType searchType,
                  bool multithread,
                  const fs::path &inputFastQ,
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
                  const fs::path &matchingReadFQ)
{
    setPathToQueryFile(pathToQueryFile);
    setKmerSize(kmerSize);
    setReadLength(readLength);
    setIndexFileLocation(indexLocation);
    setOutputFolder(outputFolder);
    setRefOnlyFlag(refOnly);
    setSearchType(searchType);
    setMultithreadFlag(multithread);
    setInputFastQ(inputFastQ);
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
    setMatchingReadFQ(matchingReadFQ);

}

//================= INIT From Q SETTINGS ========================
void FTProp::initFromQSettings (std::string configFile, bool printInputs){

    QString m_sSettingsFile(configFile.c_str());
    QSettings settings(m_sSettingsFile, QSettings::NativeFormat);

    fs::path       pathToQueryFile         = settings.value("queryFile").toString().toStdString();
    uint           kmerSize                = settings.value("kmerSize").toInt();
    uint           readLength              = settings.value("readLength").toInt();
    fs::path       indexFileLocation       = settings.value("indexFileLocation").toString().toStdString();
    fs::path       outputFolder            = settings.value("outputFolder").toString().toStdString();
    bool           refOnly                 = settings.value("refOnly").toBool();
    ft::SearchType searchType              = static_cast<ft::SearchType>(settings.value("searchType").toString().toStdString()) ;
    bool           multithread             = settings.value("multithread").toBool();
    fs::path       matchingReads           = settings.value("matchingReads").toString().toStdString();
    fs::path       inputFastQ              = settings.value("inputFastQ").toString().toStdString();
    uint           overlap                 = settings.value("overlap").toInt();
    bool           returnMatchesOnly       = settings.value("return_only_positive_matches").toBool();
    bool           kmerCounts              = settings.value("kmerCounts").toBool();
    uint           stride                  = settings.value("stride").toInt();
    uint           maxOccurences           = settings.value("maxOccurences").toInt();
    uint           threadNumber            = settings.value("threadNumber").toInt();
    bool           flagOverCountedKmers    = settings.value("flagOverCountedKmers").toBool();
    bool           ignoreNonUniqueKmers    = settings.value("ignoreNonUniqueKmers").toBool();
    bool           crossover               = settings.value("crossover").toBool();
    bool           printSearchTime         = settings.value("printSearchTime").toBool();
    uint           maxKmersPerQuery        = settings.value("maxKmersPerQuery").toInt();
    uint           maxTotalKmers           = settings.value("maxTotalKmers").toInt();

    if (printInputs){
    std::cout << "pathToQueryFile               : " << pathToQueryFile.string() <<  std::endl;
    std::cout << "kmerSize                      : " << kmerSize <<  std::endl;
    std::cout << "readLength                    : " << readLength <<  std::endl;
    std::cout << "indexFileLocation             : " << indexFileLocation.string() <<  std::endl;
    std::cout << "outputFolder                  : " << outputFolder.string() <<  std::endl;
    std::cout << "refOnly                       : " << refOnly <<  std::endl;
    std::cout << "searchType                    : " << searchType <<  std::endl;
    std::cout << "multithread                   : " << multithread <<  std::endl;
    std::cout << "overlap                       : " << overlap <<  std::endl;
    std::cout << "return_only_positive_matches  : " << returnMatchesOnly <<  std::endl;
    std::cout << "kmerCounts                    : " << kmerCounts << std::endl;
    std::cout << "stride                        : " << stride << std::endl;
    std::cout << "maxOccurences                 : " << maxOccurences << std::endl;
    std::cout << "threadNumber                  : " << threadNumber << std::endl;
    std::cout << "flagOverCountedKmers          : " << flagOverCountedKmers << std::endl;
    std::cout << "ignoreNonUniqueKmers          : " << ignoreNonUniqueKmers << std::endl;
    std::cout << "printSearchTime               : " << printSearchTime << std::endl;
    std::cout << "maxKmersPerQuery              : " << maxKmersPerQuery << std::endl;
    std::cout << "maxTotalKmers                 : " << maxTotalKmers << std::endl;
    std::cout << "matchinReads                  : " << matchingReads << std::endl;
    }
    init(pathToQueryFile, kmerSize, readLength,
         indexFileLocation, outputFolder, refOnly,
         searchType, multithread, inputFastQ, overlap,
         returnMatchesOnly, kmerCounts, stride,
         maxOccurences, threadNumber, flagOverCountedKmers,
         ignoreNonUniqueKmers, crossover, printSearchTime,
         maxKmersPerQuery, maxTotalKmers, matchingReads);

}

//================= PARAMETER GETTERS ========================
SearchType FTProp::getSearchType(){return _searchType;}

uint FTProp::getKmerSize() const {return _kmerSize;}
uint FTProp::getOverlap() const {return _overlap;}
uint FTProp::getStride() const {return _stride;}
uint FTProp::getMaxKmers() const {return _maxKmers;}
uint FTProp::getMaxTotalKmers() const {return _maxTotalKmers;}
uint FTProp::getMaxOcc() const {return _maxOccurences;}
uint FTProp::getReadLength() const {return _readLength;}
uint FTProp::getMaxThreads() const {return _maxThreads;}

//==================== PARAMETER SETTERS ===================
void FTProp::setKmerSize(uint kmerSize) {_kmerSize = kmerSize;}
void FTProp::setSearchType(ft::SearchType searchType) {_searchType = searchType;}
void FTProp::setOverlap(uint overlap) {_overlap = overlap;}
void FTProp::setStride(uint stride) {_stride = stride;}
void FTProp::setMaxKmers(uint maxKmers) {_maxKmers = maxKmers;}
void FTProp::setMaxTotalKmers(uint maxTotalKmers) {_maxTotalKmers = maxTotalKmers;}
void FTProp::setMaxOcc(uint maxOcc) {_maxOccurences = maxOcc;}
void FTProp::setReadLength(uint readLength) {_readLength = readLength;}
void FTProp::setMaxThreads(uint maxThreads) {_maxThreads = maxThreads;}

//====================== FLAG GETTERS ======================
bool FTProp::getRefOnlyFlag() const {return _refOnly;}
bool FTProp::getIgnoreNonUniqueKmersFlag() const {return _ignoreNonUniqueKmers;}
bool FTProp::getKmerCountsFlag() const {return _kmerCounts;}
bool FTProp::getCrossoverFlag() const {return _crossover;}
bool FTProp::getOverCountedFlag() const {return _overcounted;}
bool FTProp::getMatchesOnlyFlag() const {return _matchesOnly;}
bool FTProp::getPrintSearchTimeFlag() const {return _matchesOnly;}
bool FTProp::getMultithreadFlag() const {return _multithread;}
//====================== FLAG SETTERS ======================
void FTProp::setRefOnlyFlag(bool refOnly){if (refOnly != getRefOnlyFlag()){ _refOnly = refOnly;}}
void FTProp::setIgnoreNonUniqueKmersFlag(bool ignoreNonUnique){if (ignoreNonUnique != getIgnoreNonUniqueKmersFlag()){ _ignoreNonUniqueKmers = ignoreNonUnique;}}
void FTProp::setKmerCountsFlag(bool kmerCounts){if (kmerCounts != getKmerCountsFlag()){ _kmerCounts = kmerCounts;}}
void FTProp::setCrossoverFlag(bool crossover){if (crossover != getCrossoverFlag()){ _crossover = crossover;}}
void FTProp::setOverCountedFlag(bool overcounted){if (overcounted != getOverCountedFlag()){ _overcounted = overcounted;}}
void FTProp::setMatchesOnlyFlag(bool matchesOnly){if (matchesOnly != getMatchesOnlyFlag()){ _matchesOnly = matchesOnly;}}
void FTProp::setPrintSearchTimeFlag(bool printSearchTime){if (printSearchTime != getPrintSearchTimeFlag()){ _printSearchTime = printSearchTime;}}
void FTProp::setMultithreadFlag(bool multithread){if (multithread!= getMultithreadFlag()){_multithread = multithread;}}

//====================== FILE SETTERS ======================
void FTProp::setPathToQueryFile(const fs::path& pathToQueryFile)
{
    if ( pathToQueryFile != getPathToQueryFile())
    {
        _pathToQueryFile = pathToQueryFile;
    }
}
void FTProp::setIndexFileLocation(const fs::path& indexFileLocation)
{
    if ( indexFileLocation != getIndexFileLocation())
    {
        _indexFileLocation = indexFileLocation;
    }
}
void FTProp::setOutputFolder(const fs::path& outputFolder)
{
    if (outputFolder != getOutputFolder())
    {
        _outputFolder = outputFolder;
    }
}
void FTProp::setMatchingReadFQ(const fs::path& matchingReadFQ)
{
    if (matchingReadFQ != getMatchingReadFQ())
    {
        _matchingReadFQ = matchingReadFQ;
    }
}
void FTProp::setInputFastQ(const fs::path& inputFastQ)
{
    if (inputFastQ != getInputFastQ())
    {
        _inputFastQ = inputFastQ;
    }
}
void FTProp::setOutputFile(const fs::path& outputFile)
{
    if (outputFile != getOutputFile())
    {
        _outputFile = outputFile;
    }
}
void FTProp::setIndexSet(std::set<fs::path>& indexes)
{
    if (indexes != getIndexSet())
    {
        _indexSet = indexes;
    }
}

//====================== FILE GETTERS ======================
const fs::path& FTProp::getPathToQueryFile() const {return _pathToQueryFile;}
const fs::path& FTProp::getIndexFileLocation()const {return _indexFileLocation;}
const fs::path& FTProp::getOutputFolder()const {return _outputFolder;}
const fs::path& FTProp::getMatchingReadFQ() const {return _matchingReadFQ;}
const fs::path& FTProp::getInputFastQ()const {return _inputFastQ;}
const fs::path& FTProp::getOutputFile() const {return _outputFile;}
const std::set<fs::path>& FTProp::getIndexSet() const {return _indexSet;}


FTProp::~FTProp()
{
}


}
