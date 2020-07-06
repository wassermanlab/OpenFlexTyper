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
    uint getKmerSize() const;
    bool getRefOnly() const;
    SearchType getSearchType() const;
    uint getOverlap() const;
    uint getStride() const;
    bool getKmerCountsFlag() const;
    uint getMaxKmers() const;

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
