#ifndef __IFINDER_H__
#define __IFINDER_H__

#include "typedefs.h"
#include <experimental/filesystem>
#include "fmindex.h"
#include "ifmindex.h"
#include <algorithm>
#include "ifinder.h"

namespace fs = std::experimental::filesystem;

namespace ft {
////////////////////////////////////////////////////////////////////////
/// \copyright Copyright (c) 2019, Wasserman lab
/// \author    Godfrain Jacques Kounkou
/// \brief This file contains the declaration of finder class. It contains
///             functions used to search for kmers inside the FmIndex
////////////////////////////////////////////////////////////////////////
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
    virtual void searchMonoIndex(ResultsMap& indexPosResults, const KmerMap &kmerMap, const fs::path& indexPath,
                                 const std::string& indexFileLocation, uint maxOccurences, bool parallel, uint threadNumber,
                                 bool printSearchTime) = 0;

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
    virtual void searchMultipleIndexes(ResultsMap& indexPosResults, const KmerMap& kmerMap, const std::set<fs::path>& indexPaths,
                                       const std::string& indexFileLocation, uint maxOccurences, bool parallel, uint threadNumber,
                                       bool printSearchTime, long long offset) = 0;
};
}

#endif // end of Finder class
