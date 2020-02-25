#include "resultprocessor.h"

namespace ft {
//======================================================================
ResultProcessor::ResultProcessor()
    : _utils(&_ownedUtils)
    , _stats(&_ownedStats)
{
}

//======================================================================
MapOfCounts ResultProcessor::getIndexCounts(ReaIDsMap &readIDResults)
{
    MapOfCounts indexCounts;

    int count = 0;

    for (auto e : readIDResults) {
        count  = 0;
        for (auto f : e.second) {
            count++;
        }
        indexCounts.insert({{e.first.first, e.first.second}, count});
    }

    return indexCounts;
}

//======================================================================
ReaIDsMap ResultProcessor::processIndexPos(ResultsMap& indexPosResults, uint readLen)
{
    ReaIDsMap readIDResults; // map< query ID, set<read ID>>

    for (auto e : indexPosResults) {
        auto result = _utils->convertIndexPositionsToReadIDs(e.second, readLen);
        readIDResults.insert({e.first, result});
    }

    return readIDResults;
}

//======================================================================
MapOfCounts ResultProcessor::processResults(ResultsMap& indexPosResults, uint readLen, uint readlines, const fs::path& matchingReads)
{
    // convert index positions to read ids
    ReaIDsMap tmp = processIndexPos(indexPosResults, readLen);

    /*
    std::cout << "read Ids : \n";
    for (auto e : tmp) {
        for (auto f : e.second)
            std::cout << f << " ";
        std::cout << std::endl;
    }
    */

    // std::cout << "lines : " << readlines << std::endl;

    if (readlines % 2 != 0) {
        std::cout << "error with the number of reads\n";
        exit(-1);
    }

    ReaIDsMap res;

    int rcMin = (readlines / 2) + 1; // readid >= 1

    for (auto e : tmp) {
        for (auto f : e.second) {
            if (f >= rcMin) {
                if (e.second.find(f - (readlines / 2)) == e.second.end()) {
                    res[e.first].insert(f);
                }
            } else {
                std::set<size_t>::iterator it = e.second.find(f + (readlines / 2));
                if (it != e.second.end()) {
                    e.second.erase(it);
                }
                res[e.first].insert(f);
            }
        }
    }

    /*
    std::cout << "read Ids processed : \n";
    for (const auto& e : res) {
        for (const auto& f : e.second)
            std::cout << "element : " << f << " ";
        std::cout << std::endl;
    }

    std::cout << "res.size() : " << res.size() << std::endl;
    */

    // ResultsMap is :
    // <<QueryId, QueryType>, <set of reads>>

    if (!matchingReads.empty()) {
        _stats->printMatchingReadsToFile("extracted_reads.fa", matchingReads, res);
    }

    // return index Counts <query ID, number of read hits>
    return getIndexCounts(res);
}

//======================================================================
void ResultProcessor::overrideUtils(std::shared_ptr<IUtils> utils)
{
    _utils = utils.get();
}

//======================================================================
void ResultProcessor::overrideStats(std::shared_ptr<IStats> stats)
{
    _stats = stats.get();
}

//======================================================================
ResultProcessor::~ResultProcessor()
{
}
}
