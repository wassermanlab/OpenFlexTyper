////////////////////////////////////////////////////////////////////////
/// \copyright Copyright (c) 2019, Wasserman lab
/// \brief This file contains the declaration of kmergenerator class
////////////////////////////////////////////////////////////////////////

#ifndef __KMER_GENERATOR_H__
#define __KMER_GENERATOR_H__

#include <set>
#include <string>
#include <map>
#include "ftKPropsClass.h"
#include "ikmergenerator.h"

#include "stats.h"

namespace ft {


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
