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
    ////////////////////////////////////////////////////////////////////////
    /// \brief  createFMIndex
    /// \param  stringToIndex
    /// \return The function will return the name of the generated index
    ////////////////////////////////////////////////////////////////////////
    virtual std::pair<fs::path, fs::path> createFMIndex(const algo::IndexProps& _props, const fs::path& preprocessedFasta ) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// \brief loadIndexFromFile
    /// \param indexname
    ////////////////////////////////////////////////////////////////////////
    virtual void loadIndexFromFile(const fs::path& indexname) = 0;

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
    virtual ft::KmerClass search(const std::string& kmer,
                                 u_int maxOccurences = 200) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// \brief parallelFmIndex
    ////////////////////////////////////////////////////////////////////////

    virtual int indexCount() = 0;

    virtual int hits() = 0;
};
}

#endif // end of __FM_INDEX_H_
