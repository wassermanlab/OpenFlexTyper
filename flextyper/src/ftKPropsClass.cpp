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
uint KmerProperties::getKmerSize() const{return _kmerSize;}
bool KmerProperties::getRefOnly() const {return _refOnly;}
SearchType KmerProperties::getSearchType() const {return _searchType;}
uint KmerProperties::getOverlap() const {return _overlap;}
uint KmerProperties::getStride() const {return _stride;}
bool KmerProperties::getKmerCountsFlag() const {return _kmerCounts;}
uint KmerProperties::getMaxKmers() const {return _maxKmers;}

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
