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
    this->setPathToQueryFile(pathToQueryFile);
    this->setKmerSize(kmerSize);
    this->setReadLength(readLength);
    this->setIndexFileLocation(indexLocation);
    this->setOutputFolder(outputFolder);
    this->setRefOnlyFlag(refOnly);
    this->setSearchType(searchType);
    this->setMultithreadFlag(multithread);
    this->setInputFastQ(inputFastQ);
    this->setOverlap(overlap);
    this->setMatchesOnlyFlag(returnMatchesOnly);
    this->setKmerCountsFlag(kmerCounts);
    this->setStride(stride);
    this->setMaxOcc(maxOccurences);
    this->setMaxThreads(maxThreads);
    this->setOverCountedFlag(flagOverCountedKmers);
    this->setIgnoreNonUniqueKmersFlag(ignoreNonUniqueKmers);
    this->setCrossoverFlag(crossover);
    this->setPrintSearchTimeFlag(printSearchTime);
    this->setMaxKmers(maxKmers);
    this->setMaxTotalKmers(totalKmers);
    this->setMatchingReadFQ(matchingReadFQ);

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
    bool           flagOverCountedKmers = settings.value("flagOverCountedKmers").toBool();
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
    this->init(pathToQueryFile, kmerSize, readLength,
               indexFileLocation, outputFolder, refOnly,
               searchType, multithread, inputFastQ, overlap,
               returnMatchesOnly, kmerCounts, stride,
               maxOccurences, threadNumber, flagOverCountedKmers,
               ignoreNonUniqueKmers, crossover, printSearchTime,
               maxKmersPerQuery, maxTotalKmers, matchingReads);

}

//================= PARAMETER GETTERS ========================
SearchType FTProp::getSearchType(){return this->_searchType;}

uint FTProp::getKmerSize(){return this->_kmerSize;}
uint FTProp::getOverlap(){return this->_overlap;}
uint FTProp::getStride(){return this->_stride;}
uint FTProp::getMaxKmers(){return this->_maxKmers;}
uint FTProp::getMaxTotalKmers(){return this->_maxTotalKmers;}
uint FTProp::getMaxOcc(){return this->_maxOccurences;}
uint FTProp::getReadLength(){return this->_readLength;}
uint FTProp::getMaxThreads(){return this->_maxThreads;}

//==================== PARAMETER SETTERS ===================
void FTProp::setKmerSize(uint kmerSize){if (kmerSize != this->getKmerSize()){_kmerSize = kmerSize;}}
void FTProp::setSearchType(ft::SearchType searchType){if (searchType != this->getSearchType()){_searchType = searchType;}}
void FTProp::setOverlap(uint overlap){if (overlap != this->getOverlap()){_overlap = overlap;}}
void FTProp::setStride(uint stride){if (stride != this->getStride()){_stride = stride;}}
void FTProp::setMaxKmers(uint maxKmers){if (maxKmers != this->getMaxKmers()){_maxKmers = maxKmers;}}
void FTProp::setMaxTotalKmers(uint maxTotalKmers){if (maxTotalKmers != this->getMaxTotalKmers()){_maxTotalKmers = maxTotalKmers;}}
void FTProp::setMaxOcc(uint maxOcc){if (maxOcc != this->getMaxOcc()){_maxOccurences = maxOcc;}}
void FTProp::setReadLength(uint readLength){if (readLength != this->getReadLength()){_readLength = readLength;}}
void FTProp::setMaxThreads(uint maxThreads){if (maxThreads != this->getMaxThreads()){_maxThreads = maxThreads;}}

//====================== FLAG GETTERS ======================
bool FTProp::getRefOnlyFlag(){return this->_refOnly;}
bool FTProp::getIgnoreNonUniqueKmersFlag(){return this->_ignoreNonUniqueKmers;}
bool FTProp::getKmerCountsFlag(){return this->_kmerCounts;}
bool FTProp::getCrossoverFlag(){return this->_crossover;}
bool FTProp::getOverCountedFlag(){return this->_overcounted;}
bool FTProp::getMatchesOnlyFlag(){return this->_matchesOnly;}
bool FTProp::getPrintSearchTimeFlag(){return this->_matchesOnly;}
bool FTProp::getMultithreadFlag(){return this->_multithread;}
//====================== FLAG SETTERS ======================
void FTProp::setRefOnlyFlag(bool refOnly){if (refOnly != this->getRefOnlyFlag()){ _refOnly = refOnly;}}
void FTProp::setIgnoreNonUniqueKmersFlag(bool ignoreNonUnique){if (ignoreNonUnique != this->getIgnoreNonUniqueKmersFlag()){ _ignoreNonUniqueKmers = ignoreNonUnique;}}
void FTProp::setKmerCountsFlag(bool kmerCounts){if (kmerCounts != this->getKmerCountsFlag()){ _kmerCounts = kmerCounts;}}
void FTProp::setCrossoverFlag(bool crossover){if (crossover != this->getCrossoverFlag()){ _crossover = crossover;}}
void FTProp::setOverCountedFlag(bool overcounted){if (overcounted != this->getOverCountedFlag()){ _overcounted = overcounted;}}
void FTProp::setMatchesOnlyFlag(bool matchesOnly){if (matchesOnly != this->getMatchesOnlyFlag()){ _matchesOnly = matchesOnly;}}
void FTProp::setPrintSearchTimeFlag(bool printSearchTime){if (printSearchTime != this->getPrintSearchTimeFlag()){ _printSearchTime = printSearchTime;}}
void FTProp::setMultithreadFlag(bool multithread){if (multithread!= this->getMultithreadFlag()){_multithread = multithread;}}

//====================== FILE GETTERS ======================
void FTProp::setPathToQueryFile(fs::path pathToQueryFile){
    if ( pathToQueryFile != this->getPathToQueryFile()){_pathToQueryFile = pathToQueryFile;}
}
void FTProp::setIndexFileLocation(fs::path indexFileLocation){
        if ( indexFileLocation != this->getIndexFileLocation()){_indexFileLocation = indexFileLocation;}
}
void FTProp::setOutputFolder(fs::path outputFolder){
    if (outputFolder != this->getOutputFolder()){_outputFolder = outputFolder;}
}
void FTProp::setMatchingReadFQ(fs::path matchingReadFQ){
    if (matchingReadFQ != this->getMatchingReadFQ()){_matchingReadFQ = matchingReadFQ;}
}
void FTProp::setInputFastQ(fs::path inputFastQ){
    if (inputFastQ != this->getInputFastQ()){_inputFastQ = inputFastQ;}
}
void FTProp::setOutputFile(fs::path outputFile){
    if (outputFile != this->getOutputFile()){_outputFile = outputFile;}
}
void FTProp::setIndexSet(std::set<fs::path> indexes){
    if (indexes != this->getIndexSet()){_indexSet = indexes;}
}

//====================== FILE SETTERS ======================
fs::path FTProp::getPathToQueryFile(){return this->_pathToQueryFile;}
fs::path FTProp::getIndexFileLocation(){return this->_indexFileLocation;}
fs::path FTProp::getOutputFolder(){return this->_outputFolder;}
fs::path FTProp::getMatchingReadFQ(){return this->_matchingReadFQ;}
fs::path FTProp::getInputFastQ(){return this->_inputFastQ;}
fs::path FTProp::getOutputFile(){return this->_outputFile;}
std::set<fs::path> FTProp::getIndexSet(){return this->_indexSet;}


FTProp::~FTProp()
{
}


}
