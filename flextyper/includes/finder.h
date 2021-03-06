#ifndef __FINDER_H__
#define __FINDER_H__

#include <experimental/filesystem>
#include "fmindex.h"
#include "ifmindex.h"
#include <algorithm>
#include "ifinder.h"

namespace ft {

namespace fs = std::experimental::filesystem;

////////////////////////////////////////////////////////////////////////
/// \class Finder
/// \brief A class that handles the main search functions
////////////////////////////////////////////////////////////////////////
class Finder : public IFinder
{
public:
    /// Constructor
    Finder();
    Finder(const Finder& other) = delete;

    /// Destructor
    virtual ~Finder();
    const Finder& operator=(const Finder &other) = delete;

    /// Search Indexes
    /// \brief Main search function based on the parameters set in FTMap
    /// \param ft::FTMap ftMap containing all the search properties
    void searchIndexes(ft::FTMap &ftMap);

    /// Parallel Search
    /// \brief parallelSearch searches kmers in parallel in a single index.
    /// \details parallelSearch will search each kmer in parallel across a single index using asynchronous programming
    /// \param FTMap: The search class containing parameters and results
    /// \param indexPath: the index to search
    /// \param offset: the position offset of the index
    /// \result adds the results of the search to the FTMap
    void parallelSearch(FTMap &ftMap,
                        const fs::path &indexPath, long long offset);

    /// Sequential Search
    /// \public
    /// \brief sequentialSearch searches kmers sequentially in a single index.
    /// \param FTMap: The search class containing parameters and results
    /// \param indexPath: the index to search
    /// \param offset: the position offset of the index
    /// \result adds the results of the search to the FTMap
    void sequentialSearch(ft::FTMap &ftMap,
                          const fs::path &indexPath,long long offset);

private:

    /// \brief add results from an index to FTMap
    /// \private
    void addResultsFutures(std::map<std::string, ft::KmerClass> & indexResults, ft::KmerClass &tmpResult, uint offset);

    /// \brief indexParallelSearch searches across all indexes in parallel
    /// \private
    void indexParallelSearch(ft::FTMap &ftMap);

    /// \brief indexSequentialSearch searches across all indexes sequentially
    /// \private
    void indexSequentialSearch(ft::FTMap &ftMap);

    /// \skip
    void testIndex(const FTProp& ftProps, algo::IFmIndex* fmIndex, const fs::path &indexPath, std::string &testkmer);
};
}

#endif // end of Finder class
