////////////////////////////////////////////////////////////////////////
/// \copyright Copyright (c) 2019, Wasserman lab
/// \brief This file contains the declaration of kmergenerator class
////////////////////////////////////////////////////////////////////////

#ifndef __KMER_GENERATOR_H__
#define __KMER_GENERATOR_H__

#include <set>
#include <string>
#include <map>
#include "FTMapClass.h"
#include "ikmergenerator.h"
#include "stats.h"

namespace ft {

class KmerGenerator : public IKmerGenerator {
public:
    ////////////////////////////////////////////////////////////////////////
    /// \brief KmerGenerator
    ////////////////////////////////////////////////////////////////////////
    KmerGenerator();

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
    virtual std::set<std::string> genSlidingSearchStrings(const std::string& queryString, uint kmerSize, uint stride, bool kmerCounts, uint maxKmers);

    ////////////////////////////////////////////////////////////////////////
    /// \brief genCenteredSearchStrings
    /// \param queryString
    /// \param kmerSize
    /// \param overlap
    /// \param stride
    /// \return
    ////////////////////////////////////////////////////////////////////////
    virtual std::set<std::string> genCenteredSearchStrings(const std::string& queryString, uint kmerSize, uint overlap, uint stride, bool kmerCounts, uint maxKmers);


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
    QueryClass genQueryClassKmers(int queryID, std::string querystring, ft::QueryType queryType, SearchType searchType, uint kmerSize, uint overlap,
                                                 uint stride, bool kmerCounts, uint maxKmers);

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
    virtual std::set<QueryClass> genSearchKmers(std::set<Query> inputQueries, uint kmerSize, bool refOnly, SearchType searchType, uint overlap,
                                               uint stride, bool crossover, bool kmerCounts, uint maxKmers);

    ////////////////////////////////////////////////////////////////////////
    /// \brief KmerGenerator::addtoKmerMap
    /// \param kmerMap
    /// \param queryKmers
    ////////////////////////////////////////////////////////////////////////
    void addtoKmerMap(KmerMap& kmerMap, const SearchKmers& queryKmers);

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
    void genKmerMap(std::set<Query>& inputQueries, uint kmerSize, bool refOnly, const SearchType& searchType, KmerMap& kmerMap, uint overlap, uint stride,
                              bool crossover, bool ignoreNonUniqueKmers, bool kmerCounts, uint maxKmers, uint maxTotalKmers);

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
