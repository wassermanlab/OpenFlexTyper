////////////////////////////////////////////////////////////////////////
/// \copyright Copyright (c) 2020, Wasserman lab
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
    const Finder& operator=(const Finder &other) = delete;

    ////////////////////////////////////////////////////////////////////////
    /// \brief searchIndexes
    ////////////////////////////////////////////////////////////////////////
    void searchIndexes(ft::FTMap &ftMap);

    ////////////////////////////////////////////////////////////////////////
    /// \brief parallelSearch is a core function to search in parallel. This function
    ///        can be used by higher level functions.
    ////////////////////////////////////////////////////////////////////////
    void parallelSearch(FTMap &ftMap,
                        const fs::path &indexPath, long long offset);

    ////////////////////////////////////////////////////////////////////////
    /// \brief sequentialSearch searches for kmers inside a single FmIndex
    ///        in a sequential way.
    ////////////////////////////////////////////////////////////////////////
    void sequentialSearch(ft::FTMap &ftMap,
                          const fs::path &indexPath,long long offset);

private:

    ////////////////////////////////////////////////////////////////////////
    /// \brief Finder::addResultsFutures
    /// \param fmIndex
    ////////////////////////////////////////////////////////////////////////
    void addResultsFutures(std::map<std::string, ft::KmerClass> & indexResults, ft::KmerClass &tmpResult, uint offset);

    ////////////////////////////////////////////////////////////////////////
    /// \brief indexParallelSearch searches for kmers in parallel
    ////////////////////////////////////////////////////////////////////////
    void indexParallelSearch(ft::FTMap &ftMap);

    ////////////////////////////////////////////////////////////////////////
    /// \brief indexSequentialSearch searches for kmers sequentially
    ////////////////////////////////////////////////////////////////////////
    void indexSequentialSearch(ft::FTMap &ftMap);

    void testIndex(const FTProp& ftProps, algo::IFmIndex* fmIndex, const fs::path &indexPath, std::string &testkmer);
};
}

#endif // end of Finder class
