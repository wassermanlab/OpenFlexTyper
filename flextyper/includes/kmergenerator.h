#ifndef __KMER_GENERATOR_H__
#define __KMER_GENERATOR_H__

#include <set>
#include <string>
#include <map>
#include "ikmergenerator.h"
#include "queryClass.h"
#include "ftPropsClass.h"

namespace ft {


class KmerGenerator  {
public:
    ////////////////////////////////////////////////////////////////////////
    /// \brief KmerGenerator
    ////////////////////////////////////////////////////////////////////////
    KmerGenerator(const uint& _kmerSize ,
                    const bool& _refOnly ,
                    const SearchType& _searchType ,
                    const uint& _overlap = 0,
                    const uint& _stride = 1,
                    //const bool& _kmerCounts = false,
                    const uint& _maxKmers = 1000000000,
                    const bool& _verbose = false);


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
    //bool getKmerCountsFlag() const;
    uint getMaxKmers() const;

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
    //bool _kmerCounts;
    uint _maxKmers;
    bool _verbose;

};
}

#endif // kmerGenerator class
