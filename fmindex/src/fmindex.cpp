#include "fmindex.h"
#include <time.h>
#include <future>
#include <chrono>
#include <iostream>
#include <fstream>

using namespace std::chrono;

namespace algo {

//======================================================================
FmIndex::FmIndex()
    : _stats(&_ownedStats)
{
}

//======================================================================
void FmIndex::setKmerMapSize(size_t kmerMapSize)
{
    _kmerMapSize = kmerMapSize;
}

//======================================================================
void FmIndex::generateReadsMap(const std::string& filename)
{
    std::ifstream in(filename);
    std::ofstream ou("map_file");

    size_t readid = 0;
    size_t start  = 0;
    size_t llen   = 0;

    std::string line;
    if (in.is_open() && ou.is_open()) {

        // header
        // ou << "length\t" << "readid\t" << "start\t" << "end" << '\n';

        while (getline(in, line)) {
            // std::cout << line << std::endl;
            ou << llen << "\t" << readid++ << "\t" << start  << "\t" << start + line.length() - 2 << '\n';
            llen  += line.length();
            start += line.length();
        }

        in.close();
        ou.close();
    }
}

//======================================================================
std::tuple<std::set<size_t>, std::set<std::pair<int, ft::QueryType>>> FmIndex::search(const std::string& query, const std::set<std::pair<int, ft::QueryType> > &queryIds,
                                                            const std::string& /* filename */, const std::string& /* indexDirectory */,
                                                            u_int maxOcc, size_t i, bool printSearchTime)
{
    // This code is executed in a different thread for multithreaded
    // executions and in main thread for monothreaded applications

    std::set<size_t> result;

    auto start = high_resolution_clock::now();

    size_t occs = count(_fmindex, query.begin(), query.end());

    _mtx.lock();
    std::cout << '\r' << float(((float)i * 100) / _kmerMapSize) << " % " << std::flush;
    _mtx.unlock();

    if (occs > 0  && occs <= maxOcc) {
        auto locations = sdsl::locate(_fmindex, query.begin(), query.begin() + query.length());
        for (auto e : locations) {
            // std::cout << e << " --> " << (e / 59) + 1 << std::endl;
            result.insert(e);
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    if (printSearchTime) {
        _stats->printKmerSearchTimeToFile("tmp.log", query, duration.count());
    }

    return std::make_tuple(result, queryIds);
}

//======================================================================
std::map<std::string, std::set<size_t>> FmIndex::searchmany(const std::vector<std::string>& queries,
                                                            const std::string& /* filename */,
                                                            const std::string& /* indexDirectory */)
{
    std::map<std::string, std::set<size_t>> results;

    for (auto queryString : queries) {
        std::set<size_t> r;
        results.insert(std::make_pair(queryString, r));
    }

    return results;
}

//======================================================================
fs::path FmIndex::createFMIndex(const fs::path& fileToIndex, const fs::path& output, const fs::path& indexList)
{
    std::lock_guard<std::mutex> lock(_mtx);

    if (!load_from_file(_fmindex, output)) {
        std::ifstream in(fileToIndex);
        if (!in) {
            std::cout << "ERROR: File " << fileToIndex << " does not exist. Exit." << std::endl;
            return "";
        }
        // mtx.lock();
        std::cout << "No index " << output << " located. Building index now." << std::endl;
        // mtx.unlock();
        construct(_fmindex, fileToIndex, 1);
        store_to_file(_fmindex, output);
    }

    std::ofstream indxl (indexList, std::ios::app);
    if (indxl.is_open()) {
        indxl << output.string() << std::endl;
    }
    indxl.close();

    // mtx.lock();
    // std::cout << "Index construction complete in " << index_file << " index requires " << size_in_mega_bytes(_fm_index) << " MiB." << std::endl;
    // mtx.unlock();

    return output;
}

//======================================================================
void FmIndex::loadIndexFromFile(const std::string& indexname)
{
    if (!load_from_file(_fmindex, indexname)) {
        std::cerr << "Error loading the index, please provide the index file";
    }
}

//======================================================================
void FmIndex::parallelFmIndex(std::vector<fs::path> filenames, std::vector<fs::path> indexNames, const fs::path& indexList)
{
    std::vector<std::future<fs::path>> operations;

    for (size_t i = 0; i < filenames.size(); i++)
        operations.push_back(std::async(std::launch::async, &FmIndex::createFMIndex, this,
                                        filenames[i], indexNames[i], indexList));

    for (size_t i = 0; i < filenames.size(); i++)
        operations[i].get();
}

//======================================================================
void FmIndex::overrideStats(std::shared_ptr<ft::IStats> stats)
{
    _stats = stats.get();
}

//======================================================================
FmIndex::~FmIndex()
{
    std::rename("tmp.log", "kmerSearchTime.log");
}
}
