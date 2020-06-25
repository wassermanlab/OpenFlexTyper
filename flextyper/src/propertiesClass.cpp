#include <set>
#include <iostream>
#include <map>
#include "propertiesClass.h"

namespace ft {

class FTProp::FTProp
{}

void FTProp::setKmerSize(uint kmerSize){if (kmerSize != this->getKmerSize()){_kmerSize = kmerSize;}}
void FTProp::setSearchType(ft::SearchType searchType){if (searchType != this->getSearchType()){_searchType = searchType;}}
void FTProp::setOverlap(uint overlap){if (overlap != this->getOverlap()){_overlap = overlap;}}
void FTProp::setStride(uint stride){if (stride != this->getStride()){_stride = stride;}}
void FTProp::setMaxKmers(uint maxKmers){if (maxKmers != this->getMaxKmers()){_maxKmers = maxKmers;}}
void FTProp::setMaxTotalKmers(uint maxTotalKmers){if (maxTotalKmers != this->getMaxTotalKmers()){_maxTotalKmers = maxTotalKmers;}}
void FTProp::setMaxOcc(uint maxOcc){if (maxOcc != this->getMaxOcc()){_maxOcc = maxOcc;}}
void FTProp::setReadLength(uint readLength){if (readLength != this->getReadLength()){_readLen = readLength;}}

SearchType FTProp::getSearchType(){return this->_searchType;}
uint FTProp::getKmerSize(){return this->_kmerSize;}
uint FTProp::getOverlap(){return this->_overlap;}
uint FTProp::getStride(){return this->_stride;}
uint FTProp::getMaxKmers(){return this->_maxKmers;}
uint FTProp::getMaxTotalKmers(){return this->_maxTotalKmers;}
uint FTProp::getMaxOcc(){return this->_maxOcc;}
uint FTProp::getReadLength(){return this->_readLen;}

//=============== FLAGS ==============================
bool FTMap::getRefOnlyFlag(){return this->_refOnly;}
bool FTMap::getIgnoreNonUniqueKmersFlag(){return this->_ignoreNonUniqueKmers;}
bool FTMap::getKmerCountsFlag(){return this->_kmerCounts;}
bool FTMap::getCrossoverFlag(){return this->_crossover;}
bool FTMap::getOverCountedFlag(){return this->_overcounted;}
bool FTMap::getMatchesOnlyFlag(){return this->_matchesOnly;}
void FTMap::setRefOnlyFlag(bool refOnly){if (refOnly != this->getRefOnlyFlag()){ _refOnly = refOnly;}}
void FTMap::setIgnoreNonUniqueKmersFlag(bool ignoreNonUnique){if (ignoreNonUnique != this->getIgnoreNonUniqueKmersFlag()){ _ignoreNonUniqueKmers = ignoreNonUnique;}}
void FTMap::setKmerCountsFlag(bool kmerCounts){if (kmerCounts != this->getKmerCountsFlag()){ _kmerCounts = kmerCounts;}}
void FTMap::setCrossoverFlag(bool crossover){if (crossover != this->getCrossoverFlag()){ _crossover = crossover;}}
void FTMap::setOverCountedFlag(bool overcounted){if (overcounted != this->getOverCountedFlag()){ _overcounted = overcounted;}}
void FTMap::setMatchesOnlyFlag(bool matchesOnly){if (matchesOnly != this->getMatchesOnlyFlag()){ _matchesOnly = matchesOnly;}}




FTProp::~FTProp()
{
}


}
