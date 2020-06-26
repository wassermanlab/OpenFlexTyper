////////////////////////////////////////////////////////////////////////
/// \copyright Copyright (c) 2019, Wasserman lab
/// \brief This file contains the declaration of finder class. It contains
///             functions used to search for kmers inside the FmIndex
////////////////////////////////////////////////////////////////////////

#ifndef __IFINDER_H__
#define __IFINDER_H__

#include "ftMapClass.h"
#include <experimental/filesystem>
#include "fmindex.h"
#include "ifmindex.h"
#include <algorithm>
#include "ifinder.h"

namespace fs = std::experimental::filesystem;

namespace ft {

class IFinder {
public:

    virtual ~IFinder() {}

    ////////////////////////////////////////////////////////////////////////
    /// \brief searchMonoIndex
    /// \param indexPosResults
    /// \param kmerMap
    /// \param indexPath
    /// \param indexFileLocation
    /// \param maxOccurences
    /// \param parallel
    /// \param threadNumber
    ////////////////////////////////////////////////////////////////////////
    virtual void searchMonoIndex(ft::FTMap& ftMap, const fs::path& indexPath,
                                 long long offset) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// \brief searchMultipleIndexes
    /// \param indexPosResults
    /// \param kmerMap
    /// \param indexPaths
    /// \param indexFileLocation
    /// \param maxOccurences
    /// \param parallel
    /// \param threadNumber
    ////////////////////////////////////////////////////////////////////////
    virtual void searchMultipleIndexes(ft::FTMap& ftMap, const std::set<fs::path>& indexPaths,
                                       long long offset) = 0;
};
}

#endif // end of Finder class
