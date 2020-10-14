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
////////////////////////////////////////////////////////////////////////
/// \class Finder
////////////////////////////////////////////////////////////////////////
class Finder : public IFinder {
public:

    Finder();
    virtual ~Finder();
    Finder(const Finder& other) = delete;
    const Finder& operator=(const Finder &other) = delete;

    ////////////////////////////////////////////////////////////////////////
    /// \brief Main search function based on the parameters set in FTMap
    ////////////////////////////////////////////////////////////////////////
    void searchIndexes(ft::FTMap &ftMap);

    ////////////////////////////////////////////////////////////////////////
    /// \brief parallelSearch searches kmers in parallel in a single index.
    /// \details parallelSearch will search each kmer in parallel across a single index using asynchronous programming
    /// \param FTMap: The search class containing parameters and results
    /// \param indexPath: the index to search
    /// \param offset: the position offset of the index
    /// \result adds the results of the search to the FTMap
    ////////////////////////////////////////////////////////////////////////
    void parallelSearch(FTMap &ftMap,
                        const fs::path &indexPath, long long offset);

    ////////////////////////////////////////////////////////////////////////
    /// \brief sequentialSearch searches kmers sequentially in a single index.
    /// \param FTMap: The search class containing parameters and results
    /// \param indexPath: the index to search
    /// \param offset: the position offset of the index
    /// \result adds the results of the search to the FTMap
    ////////////////////////////////////////////////////////////////////////
    void sequentialSearch(ft::FTMap &ftMap,
                          const fs::path &indexPath,long long offset);

/// \privatesection
private:

    ////////////////////////////////////////////////////////////////////////
    /// \brief add results from an index to FTMap
    ////////////////////////////////////////////////////////////////////////
    void addResultsFutures(std::map<std::string, ft::KmerClass> & indexResults, ft::KmerClass &tmpResult, uint offset);

    ////////////////////////////////////////////////////////////////////////
    /// \brief indexParallelSearch searches across all indexes in parallel
    ////////////////////////////////////////////////////////////////////////
    void indexParallelSearch(ft::FTMap &ftMap);

    ////////////////////////////////////////////////////////////////////////
    /// \brief indexSequentialSearch searches across all indexes sequentially
    ////////////////////////////////////////////////////////////////////////
    void indexSequentialSearch(ft::FTMap &ftMap);


    void testIndex(const FTProp& ftProps, algo::IFmIndex* fmIndex, const fs::path &indexPath, std::string &testkmer);
};
}

#endif // end of Finder class
