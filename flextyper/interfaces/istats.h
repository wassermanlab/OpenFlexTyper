#ifndef __ISTATS_H__
#define __ISTATS_H__

#include <map>
#include <string>
#include <set>
#include "iutils.h"
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

namespace ft {
////////////////////////////////////////////////////////////////////////
/// \brief Copyright (c) 2019, Wasserman lab
/// \author    Godfrain Jacques Kounkou
/// \brief This file contains the declaration of stats.h, it contains
///             all functions necessary to generate some stats or related
///             stats contents
////////////////////////////////////////////////////////////////////////
class IStats {
public:
    ////////////////////////////////////////////////////////////////////////
    /// \brief printKmerCountToFile
    /// \param outputFile
    /// \param counter
    ////////////////////////////////////////////////////////////////////////
    virtual void printKmerCountToFile(const fs::path& outputFile, std::map<std::string, uint>& counter) const = 0;

    ////////////////////////////////////////////////////////////////////////
    /// \brief Stats::printKmerSearchTimeToFile
    /// \param outputFile
    /// \param kmer
    /// \param time
    ////////////////////////////////////////////////////////////////////////
    virtual void printKmerSearchTimeToFile(const fs::path& outputFile, const std::string& kmer, uint time) const = 0;

    ////////////////////////////////////////////////////////////////////////
    /// \brief printMatchingReadsToFile
    /// \param outputFile
    /// \param read
    ////////////////////////////////////////////////////////////////////////
    virtual void  printMatchingReadsToFile(const fs::path& outputFile, const std::string& read, ReaIDsMap& line) const = 0;
};
}

#endif // __STATS_H__
