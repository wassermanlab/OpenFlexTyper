#ifndef __FM_INDEX_H__
#define __FM_INDEX_H__

#include <vector>
#include <iostream>
#include "ifmindex.h"
#include <sdsl/suffix_arrays.hpp>
#include <mutex>
#include "ftMapClass.h"
#include "stats.h"
#include "istats.h"
#include "ftPropsClass.h"
#include "indexPropsClass.h"

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
    fs::path createFMIndex(algo::IndexProps& _props, const fs::path& preprocessedFasta);

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
                         u_int maxOcc = 200, size_t i = 0,
                         bool flagOverCountedKmers = false,
                         bool printSearchTime = false);

    ////////////////////////////////////////////////////////////////////////
    /// \brief parallelFmIndex
    /// \param filenames
    /// \param indexNames
    ////////////////////////////////////////////////////////////////////////
    void parallelFmIndex(algo::IndexProps& _props);

    ////////////////////////////////////////////////////////////////////////
    /// \brief generate the Reads Mapping
    /// \param filename
    ////////////////////////////////////////////////////////////////////////
    //void generateReadsMap(const std::string& filename);

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
