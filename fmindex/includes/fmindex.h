////////////////////////////////////////////////////////////////////////
/// \copyright Copyright (c) 2019, Wasserman lab
/// \brief This file contains the implementation of the fmindex class
////////////////////////////////////////////////////////////////////////

#ifndef __FM_INDEX_H__
#define __FM_INDEX_H__

#include <vector>
#include <iostream>
#include "ifmindex.h"
#include <sdsl/suffix_arrays.hpp>
#include <mutex>
#include "ftMapClass.h"
#include "stats.h"
#include "ftPropsClass.h"

namespace algo {

using namespace sdsl;

class FmIndex : public IFmIndex {

public:
    ////////////////////////////////////////////////////////////////////////
    /// \brief FmIndex constructor
    ////////////////////////////////////////////////////////////////////////
    FmIndex();

    ////////////////////////////////////////////////////////////////////////
    /// \brief ~FmIndex destructor
    ////////////////////////////////////////////////////////////////////////
    virtual ~FmIndex();

    ////////////////////////////////////////////////////////////////////////
    /// \brief createFMIndex
    /// \param stringToIndex
    ////////////////////////////////////////////////////////////////////////
    fs::path createFMIndex(const fs::path& fileToIndex, const fs::path& output, const fs::path& indexList);

    ////////////////////////////////////////////////////////////////////////
    /// \brief loadIndexFromFile
    /// \param indexname
    ////////////////////////////////////////////////////////////////////////
    void loadIndexFromFile(const std::string& indexname);

    ////////////////////////////////////////////////////////////////////////
    /// \brief search
    /// \param filename
    /// \param queryString
    /// \return
    ////////////////////////////////////////////////////////////////////////
    ft::KmerClass search(ft::KmerClass kmerClass,
                         const std::string& = "indexFile",
                         const std::string& = "/tmp/", u_int maxOcc = 200, size_t i = 0,
                         bool flagOverCountedKmers = false,
                         bool printSearchTime = false);

    ////////////////////////////////////////////////////////////////////////
    /// \brief search
    /// \param filename
    /// \param queryString
    /// \return
    ////////////////////////////////////////////////////////////////////////
    //std::map<ft::KmerClass, std::set<size_t>> searchmany(std::set<ft::KmerClass>& kmerSet,
                                                        //const std::string& = "indexFile",
                                                        //const std::string& = "/tmp/");

    ////////////////////////////////////////////////////////////////////////
    /// \brief parallelFmIndex
    /// \param filenames
    /// \param indexNames
    ////////////////////////////////////////////////////////////////////////
    void parallelFmIndex(std::vector<fs::path> filenames, std::vector<fs::path> indexNames, const fs::path& indexList);

    ////////////////////////////////////////////////////////////////////////
    /// \brief generate the Reads Mapping
    /// \param filename
    ////////////////////////////////////////////////////////////////////////
    void generateReadsMap(const std::string& filename);

    ////////////////////////////////////////////////////////////////////////
    /// \brief setKmerMapSize
    /// \param kmerMapSize
    ////////////////////////////////////////////////////////////////////////
    void setKmerMapSize(size_t kmerMapSize);

private:
    ////////////////////////////////////////////////////////////////////////
    /// \brief FmIndex copy constructor
    /// \param other object for the FmIndex to be copied
    ////////////////////////////////////////////////////////////////////////
    FmIndex(const FmIndex& other);

    ////////////////////////////////////////////////////////////////////////
    /// \brief  operator = assignment operator
    /// \param  other
    /// \return returns a reference on the assigned object
    ////////////////////////////////////////////////////////////////////////
    const FmIndex& operator=(const FmIndex& other);

    ////////////////////////////////////////////////////////////////////////
    /// \brief overrideStats
    /// \param stats
    ////////////////////////////////////////////////////////////////////////
    void overrideStats(std::shared_ptr<ft::IStats> stats);

private:
    ////////////////////////////////////////////////////////////////////////
    /// \brief This is the structure of our FmIndex.
    ///        csa     : compressed suffix array
    ///        wt_huff : wavelet tree huffman
    ///        rrr     : rrr bit vector of the FmIndex
    ///        For more information, please refere to :
    ///        https://github.com/simongog/sdsl-lite
    ////////////////////////////////////////////////////////////////////////
    csa_wt<wt_huff<rrr_vector<256>>, 512, 1024> _fmindex;

    ////////////////////////////////////////////////////////////////////////
    /// \brief mtx
    ////////////////////////////////////////////////////////////////////////
    std::mutex _mtx;

    ////////////////////////////////////////////////////////////////////////
    /// \brief _kmerMapSize
    ////////////////////////////////////////////////////////////////////////
    size_t _kmerMapSize;

    ////////////////////////////////////////////////////////////////////////
    /// \brief _ownedStats
    ////////////////////////////////////////////////////////////////////////
    ft::Stats _ownedStats;

    ////////////////////////////////////////////////////////////////////////
    /// \brief _stats
    ////////////////////////////////////////////////////////////////////////
    ft::IStats* _stats;

    ////////////////////////////////////////////////////////////////////////
    /// \brief _counter
    ////////////////////////////////////////////////////////////////////////
    std::map<std::string, u_int> _counter;
};
}

#endif // end of __FM_INDEX_H__
