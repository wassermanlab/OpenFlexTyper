#ifndef FTKPROPSCLASS_H
#define FTKPROPSCLASS_H

#include <set>
#include <iostream>
#include <map>
#include "ftPropsClass.h"

namespace ft {
class KmerProperties {
public:
    KmerProperties(FTProp _ftProps);
    virtual ~KmerProperties();
    void genKProps(FTProp _ftProps);

    /// Properties ///
    uint _kmerSize;
    bool _refOnly;
    SearchType _searchType;
    uint _overlap;
    uint _stride;
    bool _kmerCounts;
    uint _maxKmers;

    /// Getters ///
    uint getKmerSize();
    bool getRefOnly();
    SearchType getSearchType();
    uint getOverlap();
    uint getStride();
    bool getKmerCountsFlag();
    uint getMaxKmers();

    /// Setters ///
    void setKmerSize(uint kmerSize);
    void setRefOnly(bool refOnly);
    void setSearchType(SearchType searchType);
    void setOverlap(uint overlap);
    void setStride(uint stride);
    void setKmerCountsFlag(bool kmerCounts);
    void setMaxKmers(uint maxKmers);
};
}
#endif // FTKPROPSCLASS_H
