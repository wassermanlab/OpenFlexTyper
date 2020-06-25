#include <set>
#include <iostream>
#include <map>
#include "propertiesClass.h"

namespace ft {

FTProp::FTProp()
{}

void FTProp::setKmerSize(uint kmerSize){if (kmerSize != this->getKmerSize()){_kmerSize = kmerSize;}}
void FTProp::setSearchType(ft::SearchType searchType){if (searchType != this->getSearchType()){_searchType = searchType;}}
void FTProp::setOverlap(uint overlap){if (overlap != this->getOverlap()){_overlap = overlap;}}
void FTProp::setStride(uint stride){if (stride != this->getStride()){_stride = stride;}}
void FTProp::setMaxKmers(uint maxKmers){if (maxKmers != this->getMaxKmers()){_maxKmers = maxKmers;}}
void FTProp::setMaxTotalKmers(uint maxTotalKmers){if (maxTotalKmers != this->getMaxTotalKmers()){_maxTotalKmers = maxTotalKmers;}}
void FTProp::setMaxOcc(uint maxOcc){if (maxOcc != this->getMaxOcc()){_maxOccurences = maxOcc;}}
void FTProp::setReadLength(uint readLength){if (readLength != this->getReadLength()){_readLength = readLength;}}

SearchType FTProp::getSearchType(){return this->_searchType;}

std::set<fs::path> FTProp::getSetOfIndexes(){return this->_IndexesSet;}

uint FTProp::getKmerSize(){return this->_kmerSize;}
uint FTProp::getOverlap(){return this->_overlap;}
uint FTProp::getStride(){return this->_stride;}
uint FTProp::getMaxKmers(){return this->_maxKmers;}
uint FTProp::getMaxTotalKmers(){return this->_maxTotalKmers;}
uint FTProp::getMaxOcc(){return this->_maxOccurences;}
uint FTProp::getReadLength(){return this->_readLength;}

//=============== FLAGS ==============================
bool FTProp::getRefOnlyFlag(){return this->_refOnly;}
bool FTProp::getIgnoreNonUniqueKmersFlag(){return this->_ignoreNonUniqueKmers;}
bool FTProp::getKmerCountsFlag(){return this->_kmerCounts;}
bool FTProp::getCrossoverFlag(){return this->_crossover;}
bool FTProp::getOverCountedFlag(){return this->_overcounted;}
bool FTProp::getMatchesOnlyFlag(){return this->_matchesOnly;}

void FTProp::setRefOnlyFlag(bool refOnly){if (refOnly != this->getRefOnlyFlag()){ _refOnly = refOnly;}}
void FTProp::setIgnoreNonUniqueKmersFlag(bool ignoreNonUnique){if (ignoreNonUnique != this->getIgnoreNonUniqueKmersFlag()){ _ignoreNonUniqueKmers = ignoreNonUnique;}}
void FTProp::setKmerCountsFlag(bool kmerCounts){if (kmerCounts != this->getKmerCountsFlag()){ _kmerCounts = kmerCounts;}}
void FTProp::setCrossoverFlag(bool crossover){if (crossover != this->getCrossoverFlag()){ _crossover = crossover;}}
void FTProp::setOverCountedFlag(bool overcounted){if (overcounted != this->getOverCountedFlag()){ _overcounted = overcounted;}}
void FTProp::setMatchesOnlyFlag(bool matchesOnly){if (matchesOnly != this->getMatchesOnlyFlag()){ _matchesOnly = matchesOnly;}}



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
                  uint threadNumber,
                  bool flagOverCountedKmers,
                  bool ignoreNonUniqueKmers,
                  bool crossover,
                  bool printSearchTime,
                  uint maxKmers,
                  uint totalKmers,
                  const fs::path &matchingReads)
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
    this->setThreadNumber(threadNumber);
    this->setOverCountedFlag(flagOverCountedKmers);
    this->setIgnoreNonUniqueKmersFlag(ignoreNonUniqueKmers);
    this->setCrossoverFlag(crossover);
    this->setPrintSearchTimeFlag(printSearchTime);
    this->setMaxKmers(maxKmers);
    this->setMaxTotalKmers(totalKmers);
    this->setMatchingReads(matchingReads);

}


FTProp::~FTProp()
{
}


}
