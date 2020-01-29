#ifndef __IUTILS_H__
#define __IUTILS_H__

#include <vector>
#include <string>
#include <experimental/filesystem>
#include <set>
#include "typedefs.h"
#include <cmath>

namespace fs = std::experimental::filesystem;

namespace ft {
////////////////////////////////////////////////////////////////////////
/// \copyright Copyright (c) 2019, Wasserman lab
/// \author    Godfrain Jacques Kounkou
/// \brief This file contains the declaration of utils.h, it contains
///             all utility functions needed to perform fast typer searches
////////////////////////////////////////////////////////////////////////
class IUtils {
public:
    ////////////////////////////////////////////////////////////////////////
    /// \brief  split
    /// \param  strToSplit
    /// \param  delimeter
    /// \return returns tokens obtained from the given string
    ////////////////////////////////////////////////////////////////////////
    virtual std::vector<std::string> split(const std::string& strToSplit, char delimeter) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// \brief  getSetOfIndicies
    /// \param  indexList Filename
    /// \return returns a set of paths corresponding to indexes
    ////////////////////////////////////////////////////////////////////////
    virtual std::set<fs::path> getSetOfIndexes(const fs::path& indexList = "indices.txt") = 0;

    ////////////////////////////////////////////////////////////////////////
    /// \brief  convertIndexPositionsToReadIDs
    /// \param  indexPos
    /// \param  readLength
    /// \return returns a set of ReadID's corresponding to Index Positions
    ////////////////////////////////////////////////////////////////////////
    virtual std::set<size_t> convertIndexPositionsToReadIDs(std::set<long long> indexPositions, uint readLength) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// \brief  convertReadIDsToReadNames
    /// \param  indexMapFile
    /// \param  readIDs
    /// \return
    ////////////////////////////////////////////////////////////////////////
    virtual std::set<std::string> convertReadIDsToReadNames(const fs::path& indexMapFile, std::set<size_t> readIDs) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// \brief  FTSearch::reverseComplement
    /// \param  inputString
    /// \return returns the reverse complement sequence
    ////////////////////////////////////////////////////////////////////////
    virtual std::string reverseComplement(const std::string& inputString) const = 0;

    ////////////////////////////////////////////////////////////////////////
    /// \brief Utils::fileIndexToQueryIndex
    /// \param fileIndex
    /// \return
    ////////////////////////////////////////////////////////////////////////
    virtual int fileIndexToQueryIndex(uint fileIndex) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// \brief trimmedReadFileName
    /// \param p
    /// \return
    ////////////////////////////////////////////////////////////////////////
    virtual std::string trimmedReadFileName(const fs::path& p) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// \brief queryIndexToFileIndex
    /// \param queryIndex
    /// \return
    ////////////////////////////////////////////////////////////////////////
    virtual uint queryIndexToFileIndex(int queryIndex) = 0;
};
}

#endif // end of Utils
