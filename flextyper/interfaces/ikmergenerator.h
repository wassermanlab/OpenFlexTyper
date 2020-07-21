////////////////////////////////////////////////////////////////////////
/// \copyright Copyright (c) 2019, Wasserman lab
/// \brief This file contains the declaration of kmergenerator interface
////////////////////////////////////////////////////////////////////////

#ifndef __IKMER_GENERATOR_H__
#define __IKMER_GENERATOR_H__

#include <set>
#include <string>
#include <map>
#include "ftPropsClass.h"
#include "queryClass.h"

namespace ft {

class IKmerGenerator {
public:
    virtual ~IKmerGenerator() {}

    virtual void init(const uint& _kmerSize ,
                      const bool& _refOnly ,
                      const SearchType& _searchType ,
                      const uint& _overlap ,
                      const uint& _stride,
                      const bool& _kmerCounts,
                      const uint& _maxKmers) =0;

    ////////////////////////////////////////////////////////////////////////
    /// \brief genSlidingSearchStrings
    ////////////////////////////////////////////////////////////////////////
    virtual std::set<std::string> genSlidingSearchStrings(const std::string& queryString) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// \brief genCenteredSearchStrings
    ////////////////////////////////////////////////////////////////////////
    virtual std::set<std::string> genCenteredSearchStrings(const std::string& queryString) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// \brief genSearchKmers
    ////////////////////////////////////////////////////////////////////////
    virtual std::set<std::string> genSearchKmers(const ft::QueryClass& queryObj) = 0;

};
}

#endif // kmerGenerator class
