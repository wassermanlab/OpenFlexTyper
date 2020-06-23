////////////////////////////////////////////////////////////////////////
/// \copyright Copyright (c) 2019, Wasserman lab
/// \brief This file contains the implementation of the ifmindex class
////////////////////////////////////////////////////////////////////////

#ifndef __I_FM_INDEX_H__
#define __I_FM_INDEX_H__

#include <vector>
#include <set>
#include <iostream>
#include <experimental/filesystem>
#include "FTMapClass.h"

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
    virtual fs::path createFMIndex(const fs::path& fileToIndex, const fs::path& output, const fs::path& indexList) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// \brief loadIndexFromFile
    /// \param indexname
    ////////////////////////////////////////////////////////////////////////
    virtual void loadIndexFromFile(const std::string& indexname) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// \brief search
    /// \param filename
    /// \param queryString
    /// \return
    ////////////////////////////////////////////////////////////////////////
    virtual std::map<std::string, std::set<size_t> > searchmany(const std::vector<std::string>& queryString,
                                                                const std::string& = "indexFile",
                                                                const std::string& = "/tmp/") = 0;

    ////////////////////////////////////////////////////////////////////////
    /// \brief parallelFmIndex
    /// \param filenames
    /// \param indexNames
    /// \param outputFolder
    ////////////////////////////////////////////////////////////////////////
    virtual void parallelFmIndex(std::vector<fs::path> filenames, std::vector<fs::path> indexNames, const fs::path& indexList) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// \brief search
    /// \param filename
    /// \param queryString
    /// \return
    ////////////////////////////////////////////////////////////////////////
    virtual ft::KmerClass search(ft::KmerClass kmerClass,
                                 const std::string& filename = "indexFile",
                                 const std::string& outputFolder = "./", u_int maxOccurences = 200,
                                 size_t i = 0,
                                 bool flagOverCountedKmers = false,
                                 bool printSearchTime = false) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// \brief generate the Reads Mapping
    /// \param filename
    ////////////////////////////////////////////////////////////////////////
    virtual void generateReadsMap(const std::string& filename) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// \brief setKmerMapSize
    /// \param kmerMapSize
    ////////////////////////////////////////////////////////////////////////
    virtual void setKmerMapSize(size_t kmerMapSize) = 0;
};
}

#endif // end of __FM_INDEX_H_
