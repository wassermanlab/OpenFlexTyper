#include <set>
#include <iostream>
#include <map>
#include "ftKPropsClass.h"

namespace ft {

KmerProperties::KmerProperties(FTProp _ftProps)
{
    this->genKProps(_ftProps);
}
//=============== INIT ==============================
void KmerProperties::genKProps(FTProp _ftProps){
    this->setKmerSize(_ftProps.getKmerSize());
    this->setRefOnly(_ftProps.getRefOnlyFlag());
    this->setSearchType(_ftProps.getSearchType());
    this->setOverlap(_ftProps.getOverlap());
    this->setKmerCountsFlag(_ftProps.getKmerCountsFlag());
    this->setMaxKmers(_ftProps.getMaxKmers());
}

//================= PARAMETER GETTERS ========================
uint KmerProperties::getKmerSize(){return this->getKmerSize();}
bool KmerProperties::getRefOnly(){return this->_refOnly;}
SearchType KmerProperties::getSearchType(){return this->_searchType;}
uint KmerProperties::getOverlap(){return this->_overlap;}
uint KmerProperties::getStride(){return this->_stride;}
bool KmerProperties::getKmerCountsFlag(){return this->_kmerCounts;}
uint KmerProperties::getMaxKmers(){return this->getMaxKmers();}

//==================== PARAMETER SETTERS ===================
void KmerProperties::setKmerSize(uint kmerSize){if (kmerSize != this->getOverlap()){_kmerSize = kmerSize;}}
void KmerProperties::setRefOnly(bool refOnly){if (refOnly != this->getRefOnly()){_refOnly = refOnly;}}
void KmerProperties::setSearchType(SearchType searchType){if (searchType != this->getSearchType()){_searchType = searchType;}}
void KmerProperties::setOverlap(uint overlap){if (overlap != this->getOverlap()){_overlap = overlap;}}
void KmerProperties::setStride(uint stride){if (stride != this->getStride()){_stride = stride;}}
void KmerProperties::setKmerCountsFlag(bool kmerCounts){if (kmerCounts != this->getKmerCountsFlag()){_kmerCounts = kmerCounts;}}
void KmerProperties::setMaxKmers(uint maxKmers){if (maxKmers != this->getMaxKmers()){_maxKmers = maxKmers;}}

KmerProperties::~KmerProperties()
{}
}
