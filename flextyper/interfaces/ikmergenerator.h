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
#include "stats.h"
#include "istats.h"

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
    virtual std::set<std::string> genSlidingSearchStrings(const std::string& queryString) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// \brief genCenteredSearchStrings
    /// \param queryString
    /// \param kmerSize
    /// \param overlap
    /// \param stride
    /// \return
    ////////////////////////////////////////////////////////////////////////
    virtual std::set<std::string> genCenteredSearchStrings(const std::string& queryString) = 0;

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
    virtual std::set<std::string> genSearchKmers(const ft::QueryClass& queryObj) = 0;

};
}

#endif // kmerGenerator class
