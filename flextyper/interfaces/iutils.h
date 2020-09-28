////////////////////////////////////////////////////////////////////////
/// \copyright Copyright (c) 2020, Wasserman lab
////////////////////////////////////////////////////////////////////////

#ifndef __IUTILS_H__
#define __IUTILS_H__

#include <vector>
#include <string>
#include <experimental/filesystem>
#include <set>
#include "ftMapClass.h"
#include <cmath>

namespace fs = std::experimental::filesystem;

namespace ft {

class IUtils {
public:

    virtual ~IUtils() {}

    ////////////////////////////////////////////////////////////////////////
    /// \brief  join
    /// \param  setOfStr
    /// \param  delimeter
    ////////////////////////////////////////////////////////////////////////
    virtual std::string joinString(const std::set<std::string>& setOfStr, std::string delimeter = ", ") = 0;

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


};
}

#endif // end of Utils
