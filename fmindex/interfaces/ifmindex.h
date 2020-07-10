#ifndef __I_FM_INDEX_H__
#define __I_FM_INDEX_H__

#include <vector>
#include <set>
#include <iostream>
#include <experimental/filesystem>
#include "ftMapClass.h"
#include "indexPropsClass.h"

namespace fs = std::experimental::filesystem;

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
    virtual fs::path createFMIndex(algo::IndexProps& _props, const fs::path& preprocessedFasta ) = 0;

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
    virtual ft::KmerClass search(ft::KmerClass kmerClass,
                                 u_int maxOccurences = 200,
                                 size_t i = 0,
                                 bool flagOverCountedKmers = false) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// \brief generate the Reads Mapping
    /// \param filename
    ////////////////////////////////////////////////////////////////////////
    //virtual void generateReadsMap(const std::string& filename) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// \brief setKmerMapSize
    /// \param kmerMapSize
    ////////////////////////////////////////////////////////////////////////
    virtual void setKmerMapSize(size_t kmerMapSize) = 0;
};
}

#endif // end of __FM_INDEX_H_
