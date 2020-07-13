#include <set>
#include <iostream>
#include <map>
#include "ftKPropsClass.h"

namespace ft {

KmerProperties::KmerProperties()
{
}
//=============== INIT ==============================
void KmerProperties::genKProps(FTProp _ftProps){
    setKmerSize(_ftProps.getKmerSize());
    setRefOnly(_ftProps.getRefOnlyFlag());
    setSearchType(_ftProps.getSearchType());
    setOverlap(_ftProps.getOverlap());
    setKmerCountsFlag(_ftProps.getKmerCountsFlag());
    setMaxKmers(_ftProps.getMaxKmers());
}

//================= PARAMETER GETTERS ========================
uint KmerProperties::getKmerSize(){return getKmerSize();}
bool KmerProperties::getRefOnly(){return _refOnly;}
SearchType KmerProperties::getSearchType(){return _searchType;}
uint KmerProperties::getOverlap(){return _overlap;}
uint KmerProperties::getStride(){return _stride;}
bool KmerProperties::getKmerCountsFlag(){return _kmerCounts;}
uint KmerProperties::getMaxKmers(){return _maxKmers;}

//==================== PARAMETER SETTERS ===================
void KmerProperties::setKmerSize(uint kmerSize){_kmerSize = kmerSize;}
void KmerProperties::setRefOnly(bool refOnly){_refOnly = refOnly;}
void KmerProperties::setSearchType(SearchType searchType){_searchType = searchType;}
void KmerProperties::setOverlap(uint overlap){_overlap = overlap;}
void KmerProperties::setStride(uint stride){_stride = stride;}
void KmerProperties::setKmerCountsFlag(bool kmerCounts){_kmerCounts = kmerCounts;}
void KmerProperties::setMaxKmers(uint maxKmers){_maxKmers = maxKmers;}

KmerProperties::~KmerProperties()
{}
}
