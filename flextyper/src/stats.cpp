#include "stats.h"
#include <fstream>
#include <iostream>
#include "iutils.h"

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
void Stats::printMatchingReadsToFile(const fs::path& outputFile, const std::string& read, ReaIDsMap &res) const
{
    std::ofstream file;
    file.open(outputFile, std::ios_base::app);
    std::string line;
    std::ifstream f(read);

    if (res.size() == 0) {
        std::cout << "lines is empty at this point\n";
        return;
    }

    std::set<size_t> lines;

    // std::cout << "display elements" << std::endl;
    for (auto e : res) {
        for (auto f : e.second)
            lines.insert(f);
    }

    /*
    std::cout << "lines size : " << lines.size()   << std::endl;
    std::cout << "max line : " << *(lines.end())+1 << std::endl;
    */

    if (file.is_open()) {
        for (int i = 0; i <= *lines.rbegin() + 1; i++) {
            std::getline(f, line);
            if (lines.find(i) != lines.end()) {
                // std::cout << "taking line : " << i+1 << std::endl;
                file << line << "\n";
            }
        }
    }

    file.close();
}

//======================================================================
Stats::~Stats()
{
}

}
