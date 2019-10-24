#include "resultprocessor.h"

namespace ft {
//======================================================================
ResultProcessor::ResultProcessor()
    : _utils(&_ownedUtils)
{
}

//======================================================================
MapOfCounts ResultProcessor::getIndexCounts(ResultsMap readIDResults)
{
    /*
     multi hit = when a read matches to multiple different queries.
     if ignore_multi_hits is true then we want to keep track of the observed reads and discount any
     that have been observed as a match for multiple queries

     iterate over readIDResults, count number of reads,
     ignore multi hits
    */
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
MapOfCounts ResultProcessor::processResults(ResultsMap& indexPosResults, uint readLen)
{
    // convert index positions to read ids
    auto res = processIndexPos(indexPosResults, readLen);

    // return index Counts <query ID, number of read hits>
    return getIndexCounts(res);
}

//======================================================================
void ResultProcessor::overrideUtils(std::shared_ptr<IUtils> utils)
{
    _utils = utils.get();
}

//======================================================================
ResultProcessor::~ResultProcessor()
{
}
}
