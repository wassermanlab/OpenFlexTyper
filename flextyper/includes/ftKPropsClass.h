#ifndef FTKPROPSCLASS_H
#define FTKPROPSCLASS_H

#include <set>
#include <iostream>
#include <map>
#include "ftPropsClass.h"

namespace ft {
class KmerProperties {
public:
    /// Properties ///
    uint _kmerSize;
    bool _refOnly;
    SearchType _searchType;
    uint _overlap;
    uint _stride;
    bool _kmerCounts;
    uint _maxKmers;

    /// Getters ///
    uint getKmerSize(){return this->getKmerSize();};
    bool getRefOnly(){return this->_refOnly;};
    SearchType getSearchType(){return this->_searchType;};
    uint getOverlap(){return this->_overlap;};
    uint getStride(){return this->_stride;};
    bool getKmerCountsFlag(){return this->_kmerCounts;};
    uint getMaxKmers(){return this->getMaxKmers();};

    /// Setters ///
    void setKmerSize(uint kmerSize){if (kmerSize != this->getOverlap()){_kmerSize = kmerSize;}};
    void setRefOnly(bool refOnly){if (refOnly != this->getRefOnly()){_refOnly = refOnly;}};
    void setSearchType(SearchType searchType){if (searchType != this->getSearchType()){_searchType = searchType;}};
    void setOverlap(uint overlap){if (overlap != this->getOverlap()){_overlap = overlap;}};
    void setStride(uint stride){if (stride != this->getStride()){_stride = stride;}};
    void setKmerCountsFlag(bool kmerCounts){if (kmerCounts != this->getKmerCountsFlag()){_kmerCounts = kmerCounts;}};
    void setMaxKmers(uint maxKmers){if (maxKmers != this->getMaxKmers()){_maxKmers = maxKmers;}};
};
}
#endif // FTKPROPSCLASS_H
