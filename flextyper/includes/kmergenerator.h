////////////////////////////////////////////////////////////////////////
/// \copyright Copyright (c) 2019, Wasserman lab
/// \brief This file contains the declaration of kmergenerator class
////////////////////////////////////////////////////////////////////////

#ifndef __KMER_GENERATOR_H__
#define __KMER_GENERATOR_H__

#include <set>
#include <string>
#include <map>

#include "ikmergenerator.h"

#include "stats.h"

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

class KmerGenerator : public IKmerGenerator {
public:
    ////////////////////////////////////////////////////////////////////////
    /// \brief KmerGenerator
    ////////////////////////////////////////////////////////////////////////
    KmerGenerator(KmerProperties _kProps);
    KmerProperties _kProps;

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
    /// \brief genCenteredSearchStrings
    /// \param inputQuery
    /// \param kmerSize
    /// \param refOnly
    /// \param searchType
    /// \param overlap
    /// \param stride
    /// \param crossover
    /// \return
    ////////////////////////////////////////////////////////////////////////
    virtual std::set<std::string> genQueryClassKmers(ft::QueryClass queryObj);

    ////////////////////////////////////////////////////////////////////////
    /// \brief genSearchKmers
    /// \param inputQuery
    /// \param Kmer Properties
    /// \return
    ////////////////////////////////////////////////////////////////////////
    virtual std::set<std::string> genSearchKmers(ft::QueryClass queryObj);


    ////////////////////////////////////////////////////////////////////////
    /// \brief overrideStats
    /// \param stats
    ////////////////////////////////////////////////////////////////////////
    void overrideStats(std::shared_ptr<IStats> stats);

private:
    ////////////////////////////////////////////////////////////////////////
    /// \brief _counter
    ////////////////////////////////////////////////////////////////////////
    std::map<std::string, uint> _counter;

    ////////////////////////////////////////////////////////////////////////
    /// \brief _ownedStats
    ////////////////////////////////////////////////////////////////////////
    Stats _ownedStats;

    ////////////////////////////////////////////////////////////////////////
    /// \brief _stats
    ////////////////////////////////////////////////////////////////////////
    IStats* _stats;
};
}

#endif // kmerGenerator class
