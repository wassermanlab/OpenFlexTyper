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
void Stats::printMatchingReadsToFile(const fs::path& outputFile, const std::string& read, size_t line) const
{
    std::ofstream file;
    file.open(outputFile, std::ios_base::app);
    std::string s;
    std::ifstream f(read);

    if (file.is_open()) {
        for (int i = 1; i <= line + 1; i++)
            std::getline(f, s);
        file << s << "\n";
    }

    file.close();
}

//======================================================================
Stats::~Stats()
{
}

}
