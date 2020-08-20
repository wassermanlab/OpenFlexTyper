#ifndef __I_FM_INDEX_H__
#define __I_FM_INDEX_H__

#include <vector>
#include <set>
#include <iostream>
#include <experimental/filesystem>
#include "ftMapClass.h"
#include "indexPropsClass.h"
#include <sdsl/suffix_arrays.hpp>

namespace fs = std::experimental::filesystem;
using namespace sdsl;
namespace algo {

typedef unsigned int Position;

class IFmIndex {

public:

    virtual ~IFmIndex() {}
    virtual void printToStdOut(const std::string& outputString) = 0 ;
    ////////////////////////////////////////////////////////////////////////
    /// \brief  createFMIndex
    /// \param  stringToIndex
    /// \return The function will return the name of the generated index
    ////////////////////////////////////////////////////////////////////////
    virtual fs::path createFMIndex(const algo::IndexProps& _props, const fs::path& preprocessedFasta ) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// \brief loadIndexFromFile
    /// \param indexname
    ////////////////////////////////////////////////////////////////////////
    virtual void loadIndexFromFile(const std::string& indexname) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// \brief parallelFmIndex
    /// \param filenames
    /// \param indexNames
    /// \param outputFolder
    ////////////////////////////////////////////////////////////////////////
    virtual void parallelFmIndex(algo::IndexProps& _props) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// \brief search
    /// \param filename
    /// \param queryString
    /// \return
    ////////////////////////////////////////////////////////////////////////
    virtual ft::KmerClass search(ft::Kmer kmer,
                                 u_int maxOccurences = 200,
                                 bool flagOverCountedKmers = false) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// \brief parallelFmIndex
    ////////////////////////////////////////////////////////////////////////
    virtual const csa_wt<wt_huff<rrr_vector<256>>, 512, 1024>& getIndex() = 0;

};
}

#endif // end of __FM_INDEX_H_
