////////////////////////////////////////////////////////////////////////
/// \copyright Copyright (c) 2019, Wasserman lab
/// \brief This file contains the declaration of finder class. It contains
///             functions used to search for kmers inside the FmIndex
////////////////////////////////////////////////////////////////////////

#ifndef __FINDER_H__
#define __FINDER_H__

#include <experimental/filesystem>
#include "fmindex.h"
#include "ifmindex.h"
#include <algorithm>
#include "ifinder.h"

namespace fs = std::experimental::filesystem;

namespace ft {

class Finder : public IFinder {
public:
    ////////////////////////////////////////////////////////////////////////
    /// \brief Finder
    ////////////////////////////////////////////////////////////////////////
    Finder();

    ////////////////////////////////////////////////////////////////////////
    /// \brief ~Finder
    ////////////////////////////////////////////////////////////////////////
    virtual ~Finder();

    ////////////////////////////////////////////////////////////////////////
    /// \brief Finder
    /// \param other
    ////////////////////////////////////////////////////////////////////////
    Finder(const Finder& other) = delete;

    ////////////////////////////////////////////////////////////////////////
    /// \brief operator =
    /// \param other
    /// \return
    ////////////////////////////////////////////////////////////////////////
    const Finder& operator=(const Finder& other) = delete;

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
    void searchMonoIndex(ft::FTMap& ftMap, const fs::path& indexPath,
                         const std::string& indexFileLocation, bool parallel, uint threadNumber,
                         bool printSearchTime, long long offset);

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
    void searchMultipleIndexes(ft::FTMap& ftMap, const std::set<fs::path>& indexPaths,
                               const std::string& indexFileLocation, bool parallel, uint threadNumber,
                               bool printSearchTime, long long offset);

    ////////////////////////////////////////////////////////////////////////
    /// \brief Finder::addResultsFutures
    /// \param fmIndex
    ////////////////////////////////////////////////////////////////////////
    void addResultsFutures( std::set<ft::KmerClass>& indexResults, ft::KmerClass& tmpResult, uint offset);


    ////////////////////////////////////////////////////////////////////////
    /// \brief Finder::overrideFmIndex
    /// \param fmIndex
    ////////////////////////////////////////////////////////////////////////
    void overrideFmIndex(std::shared_ptr<algo::IFmIndex> fmIndex);


public:
    ////////////////////////////////////////////////////////////////////////
    /// \brief parallelSearch is a core function to search in parallel. This function
    ///        can be used by higher level functions.
    /// \param indexPosResults
    /// \param indexFileLocation
    /// \param kmerMap
    /// \param indexPath
    /// \param maxOcc
    /// \param threadNumber
    ////////////////////////////////////////////////////////////////////////
    void parallelSearch(FTMap& ftMap, const fs::path& indexFileLocation,
                        fs::path indexPath, uint threadNumber, bool printSearchTime, long long offset);

    ////////////////////////////////////////////////////////////////////////
    /// \brief sequentialSearch searches for kmers inside a single FmIndex
    ///        in a sequential way.
    /// \param indexPosResults
    /// \param indexFileLocation
    /// \param kmerMap
    /// \param indexPath
    /// \param maxOcc
    ////////////////////////////////////////////////////////////////////////
    void sequentialSearch(ft::FTMap& ftMap,
                          const fs::path& indexFileLocation,
                          fs::path indexPath, bool printSearchTime, long long offset);

    ////////////////////////////////////////////////////////////////////////
    /// \brief multipleIndexesParallelSearch searches for kmers inside multiple
    ///        indexes in parallel
    /// \param indexPosResults
    /// \param indexFileLocation
    /// \param kmerMap
    /// \param indexPath
    /// \param maxOcc
    /// \param threadNumber
    ////////////////////////////////////////////////////////////////////////
    void multipleIndexesParallelSearch(ft::FTMap& ftMap, const fs::path& indexFileLocation,
                                       const std::set<fs::path>& indexPath, uint threadNumber, bool printSearchTime, long long offset);

    ////////////////////////////////////////////////////////////////////////
    /// \brief multipleIndexesSequentialSearch searches for kmers inside a multiple
    ///        FmIndexes in q sequential way
    /// \param indexPosResults
    /// \param indexFileLocation
    /// \param kmerMap
    /// \param indexPath
    /// \param maxOcc
    ////////////////////////////////////////////////////////////////////////
    void multipleIndexesSequentialSearch(ft::FTMap& ftMap, const fs::path& indexFileLocation,
                                         std::set<fs::path> indexPath, bool printSearchTime, long long offset);

private:
    ////////////////////////////////////////////////////////////////////////
    /// \brief fmIndex
    ////////////////////////////////////////////////////////////////////////
    algo::IFmIndex* _fmIndex;

    ////////////////////////////////////////////////////////////////////////
    /// \brief fmIndex
    ////////////////////////////////////////////////////////////////////////
    algo::FmIndex _ownedFmIndex;
};
}

#endif // end of Finder class
