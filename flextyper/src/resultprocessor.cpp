#include "resultprocessor.h"

namespace ft {
//======================================================================
ResultProcessor::ResultProcessor()
    : _utils(&_ownedUtils)
    , _stats(&_ownedStats)
{
}

//======================================================================
MapOfCounts ResultProcessor::getIndexCounts(ResultsMap readIDResults)
{
    MapOfCounts indexCounts;

    for (auto e : readIDResults) {
        // std::cout << e.first.first << " " << e.second.size() << std::endl;
        indexCounts.insert({{e.first.first, e.first.second}, e.second.size()});
    }

    return indexCounts;
}

//======================================================================
ResultsMap ResultProcessor::processIndexPos(ResultsMap& indexPosResults, uint readLen)
{
    ResultsMap readIDResults; // map< query ID, set<read ID>>

    for (auto e : indexPosResults) {
        auto result = _utils->convertIndexPositionsToReadIDs(e.second, readLen);
        readIDResults.insert({e.first, result});
    }

    return readIDResults;
}

//======================================================================
MapOfCounts ResultProcessor::processResults(ResultsMap& indexPosResults, uint readLen, const fs::path& matchingReads)
{
    // convert index positions to read ids
    ResultsMap res = processIndexPos(indexPosResults, readLen);

    // ResultsMap is :
    // <<QueryId, QueryType>, <set of reads>>

    if (!matchingReads.empty()) {
        for (auto e : res) {
            for (auto f : e.second) {
                // std::cout << "Read : " << f << std::endl;
                _stats->printMatchingReadsToFile("extracted_reads.fa", matchingReads, f);
            }
        }
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
