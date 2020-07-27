#ifndef __FM_INDEX_H__
#define __FM_INDEX_H__
#include <time.h>
#include <future>
#include <chrono>
#include <fstream>
#include <vector>
#include <iostream>
#include "ifmindex.h"
#include <sdsl/suffix_arrays.hpp>
#include <mutex>
#include "ftMapClass.h"
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
    fs::path createFMIndex(const algo::IndexProps& _props, const fs::path& preprocessedFasta);

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
                         u_int maxOcc = 200,
                         bool flagOverCountedKmers = false);

    ////////////////////////////////////////////////////////////////////////
    /// \brief parallelFmIndex
    /// \param filenames
    /// \param indexNames
    ////////////////////////////////////////////////////////////////////////
    void parallelFmIndex(algo::IndexProps& _props);

    ////////////////////////////////////////////////////////////////////////
    /// \brief parallelFmIndex
    ////////////////////////////////////////////////////////////////////////
    csa_wt<wt_huff<rrr_vector<256>>, 512, 1024> getIndex();


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

private:
    ////////////////////////////////////////////////////////////////////////
    /// \brief This is the structure of our FmIndex.
    ///        csa     : compressed suffix array
    ///        wt_huff : wavelet tree huffman
    ///        rrr     : rrr bit vector of the FmIndex
    ///        For more information, please refere to :
    ///        https://github.com/simongog/sdsl-lite
    ////////////////////////////////////////////////////////////////////////
    csa_wt<wt_huff<rrr_vector<256>>, 512, 1024> _index;

    ////////////////////////////////////////////////////////////////////////
    /// \brief mtx
    ////////////////////////////////////////////////////////////////////////
    std::mutex _mtx;

    ////////////////////////////////////////////////////////////////////////
    /// \brief _kmerMapSize
    ////////////////////////////////////////////////////////////////////////
    size_t _kmerMapSize;

    ////////////////////////////////////////////////////////////////////////
    /// \brief _counter
    ////////////////////////////////////////////////////////////////////////
    std::map<std::string, u_int> _counter;
};
}

#endif // end of __FM_INDEX_H__
