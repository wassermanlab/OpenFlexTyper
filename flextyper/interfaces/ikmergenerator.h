////////////////////////////////////////////////////////////////////////
///
/// Copyright (c) 2018, Wasserman lab
///
/// FILE        ikmergenerator.h
///
/// DESCRIPTION This file contains the declaration of kmergenerator interface

#ifndef __IKMER_GENERATOR_H__
#define __IKMER_GENERATOR_H__

#include <set>
#include <string>
#include <map>
#include "typedefs.h"

namespace ft {
////////////////////////////////////////////////////////////////////////
/// \copyright Copyright (c) 2019, Wasserman lab
/// \author    Godfrain Jacques Kounkou
/// \brief This file contains the declaration of kmergenerator interface
////////////////////////////////////////////////////////////////////////
class IKmerGenerator {
public:
    ////////////////////////////////////////////////////////////////////////
    /// \brief genSlidingSearchStrings
    /// \param queryString
    /// \param kmerSize
    /// \param stride
    /// \return
    ////////////////////////////////////////////////////////////////////////
    virtual std::set<std::string> genSlidingSearchStrings(const std::string& queryString, uint kmerSize, uint stride, bool kmerCounts, uint maxKmers) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// \brief genCenteredSearchStrings
    /// \param queryString
    /// \param kmerSize
    /// \param overlap
    /// \param stride
    /// \return
    ////////////////////////////////////////////////////////////////////////
    virtual std::set<std::string> genCenteredSearchStrings(const std::string& queryString, uint kmerSize, uint overlap, uint stride, bool kmerCounts, uint maxKmers) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// \brief KmerGenerator::genQueryKmers
    /// \param inputQuery
    /// \param kmerSize
    /// \param refOnly
    /// \param searchType
    /// \param overlap
    /// \param stride
    /// \param crossover
    /// \return
    ////////////////////////////////////////////////////////////////////////
    virtual SearchKmers genQueryKmers(Query inputQuery, uint kmerSize, bool refOnly, SearchType searchType, uint overlap, uint stride, bool crossover, bool kmerCounts, uint maxKmers) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// \brief genSearchKmers
    /// \param inputQueries
    /// \param kmerSize
    /// \param refOnly
    /// \param searchType
    /// \param overlap
    /// \param stride
    /// \return
    ////////////////////////////////////////////////////////////////////////
    virtual SearchKmers genSearchKmers(std::set<Query> inputQueries, uint kmerSize, bool refOnly, SearchType searchType, uint overlap,  uint stride, bool kmerCounts, uint maxKmers) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// \brief KmerGenerator::addtoKmerMap
    /// \param kmerMap
    /// \param queryKmers
    ////////////////////////////////////////////////////////////////////////
    virtual void addtoKmerMap(KmerMap& kmerMap, const SearchKmers& queryKmers) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// \brief KmerGenerator::genKmerMap
    /// \param inputQueries
    /// \param kmerSize
    /// \param refOnly
    /// \param searchType
    /// \param kmerMap
    /// \param overlap
    /// \param stride
    /// \param crossover
    /// \param ignoreNonUniqueKmers
    ////////////////////////////////////////////////////////////////////////
    virtual void genKmerMap(std::set<Query>& inputQueries, uint kmerSize, bool refOnly, const SearchType& searchType, KmerMap& kmerMap, uint overlap, uint stride,
                              bool crossover, bool ignoreNonUniqueKmers, bool kmerCounts, uint maxKmers, uint maxTotalKmers) = 0;
};
}

#endif // kmerGenerator class
