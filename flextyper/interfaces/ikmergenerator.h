////////////////////////////////////////////////////////////////////////
/// \copyright Copyright (c) 2019, Wasserman lab
/// \brief This file contains the declaration of kmergenerator interface
////////////////////////////////////////////////////////////////////////

#ifndef __IKMER_GENERATOR_H__
#define __IKMER_GENERATOR_H__

#include <set>
#include <string>
#include <map>
#include "ftMapClass.h"

namespace ft {

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
    virtual std::set<std::string> genQueryClassKmers(int queryID, std::string querystring, ft::QueryType queryType, SearchType searchType, uint kmerSize, uint overlap,
                                                    uint stride, bool kmerCounts, uint maxKmers) = 0;

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
    virtual std::set<std::string> genSearchKmers(ft::QueryClass queryObj, KmerProperties kmerProperties) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// \brief KmerGenerator::addtoKmerMap
    /// \param kmerMap
    /// \param queryKmers
    ////////////////////////////////////////////////////////////////////////
    //virtual void addQueriestoKmerMap(ft::FTMap& ftMap, const std::set<QueryClass>& queryMa) = 0;

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
    //virtual void genKmerMap(std::set<Query>& inputQueries,  ft::FTMap& ftMap) = 0;
};
}

#endif // kmerGenerator class
