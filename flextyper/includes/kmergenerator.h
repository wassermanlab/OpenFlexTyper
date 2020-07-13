#ifndef __KMER_GENERATOR_H__
#define __KMER_GENERATOR_H__

#include <set>
#include <string>
#include <map>
#include "ikmergenerator.h"
#include "ftPropsClass.h"

namespace ft {


class KmerGenerator  {
public:
    ////////////////////////////////////////////////////////////////////////
    /// \brief KmerGenerator
    ////////////////////////////////////////////////////////////////////////
    KmerGenerator();

    ////////////////////////////////////////////////////////////////////////
    /// \brief KmerGenerator
    ////////////////////////////////////////////////////////////////////////
    void init(const ft::FTProp& _ftprops);

    ////////////////////////////////////////////////////////////////////////
    /// \brief ~KmerGenerator
    ////////////////////////////////////////////////////////////////////////
    virtual ~KmerGenerator();

    ////////////////////////////////////////////////////////////////////////
    /// \brief genSlidingSearchStrings
    /// \param queryString
    /// \param kmerSize
    /// \param stride
    /// \return
    ////////////////////////////////////////////////////////////////////////
    virtual std::set<std::string> genSlidingSearchStrings(const std::string& queryString);

    ////////////////////////////////////////////////////////////////////////
    /// \brief genCenteredSearchStrings
    /// \param queryString
    /// \param kmerSize
    /// \param overlap
    /// \param stride
    /// \return
    ////////////////////////////////////////////////////////////////////////
    virtual std::set<std::string> genCenteredSearchStrings(const std::string& queryString);

    ////////////////////////////////////////////////////////////////////////
    /// \brief genSearchKmers
    /// \param inputQuery
    /// \param Kmer Properties
    /// \return
    ////////////////////////////////////////////////////////////////////////
    virtual std::set<std::string> genSearchKmers(const ft::QueryClass& queryObj);

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



private:
    ////////////////////////////////////////////////////////////////////////
    /// \brief _counter
    ////////////////////////////////////////////////////////////////////////
    std::map<std::string, uint> _counter;

    uint _kmerSize;
    bool _refOnly;
    SearchType _searchType;
    uint _overlap;
    uint _stride;
    bool _kmerCounts;
    uint _maxKmers;

};
}

#endif // kmerGenerator class
