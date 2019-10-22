////////////////////////////////////////////////////////////////////////
///
/// Copyright (c) 2019, Wasserman lab
///
/// FILE        stats.cpp
///
/// DESCRIPTION This file contains the definition of stats.cpp, it contains
///             all functions necessary to generate some stats or related
///             stats contents
///
/// Initial version @
///
////////////////////////////////////////////////////////////////////////

#include "stats.h"
#include <fstream>

namespace ft {
//======================================================================
Stats::Stats()
{
}

//======================================================================
void Stats::printKmerCountToFile(const fs::path& outputFile, std::map<std::string, uint>& counter) const
{
    if (fs::exists(outputFile))
        std::remove(outputFile.c_str());

    if (counter.empty())
        return;

    std::ofstream file(outputFile);

    if (file.is_open()) {
        for (auto e : counter) {
            file << e.first << " : " << e.second << "\n";
        }
    }
    file.close();
}

//======================================================================
void Stats::printKmerSearchTimeToFile(const fs::path& outputFile, const std::string& kmer, uint time) const
{
    std::ofstream file;
    file.open(outputFile, std::ios_base::app);

    if (file.is_open()) {
        file << kmer << " : " << time << " microsecond(s)\n";
    }
    file.close();
}

//======================================================================
Stats::~Stats()
{
}

}
