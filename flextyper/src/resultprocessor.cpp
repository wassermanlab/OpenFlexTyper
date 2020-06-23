#include "resultprocessor.h"
#include "FTMapClass.h"

namespace ft {
//======================================================================
ResultProcessor::ResultProcessor()
    : _utils(&_ownedUtils)
    , _stats(&_ownedStats)
{
}

////======================================================================
//void ResultProcessor::getIndexCounts(std::set<ft::KmerClass> readIDResults)
//{
//    std::set<ft::QueryClass> _queryMap;

//    int count = 0;

//    for (auto e : readIDResults) {
//        count  = 0;
//        for (auto f : e.second) {
//            count++;
//        }
//        indexCounts.insert({{e.first.first, e.first.second}, count});
//    }
//}

////======================================================================
//std::set<ft::QueryClass> ResultProcessor::processIndexPos(std::set<ft::KmerClass> indexResults, uint readLen)
//{
//    std::set<ft::QueryClass> readIDResults; // map< query ID, set<read ID>>

//    for (auto e : indexResults) {
//        auto result = _utils->convertIndexPositionsToReadIDs(e.second.first, readLen);
//        readIDResults.insert({e.first, result});
//    }

//    return readIDResults;
//}

//======================================================================
void ResultProcessor::processResults(ft::FTMap ftMap, uint readLen, uint readlines, const fs::path& matchingReads)
{

    ftMap.setReadLength(readLen);
    std::set<std::set<ft::KmerClass>> resultsMap = ftMap.getResultsMap();

    //for each set of results:
        // covertPosToReadID
        // Add ReadIDs to QueryMap
    for (auto indexResult : resultsMap)
    {
        ftMap.processIndexResults(indexResult, ftMap.getReadLength());
    }

    //processIndexPos(ftMap, readLen);

    // std::cout << "lines : " << readlines << std::endl;

    if (readlines % 2 != 0) {
        std::cout << "error with the number of reads\n";
        exit(-1);
    }

//    ReaIDsMap res;

//    int rcMin = (readlines / 2) + 1; // readid >= 1

//    for (auto e : tmp) {
//        for (auto f : e.second) {
//            if (f >= rcMin) {
//                if (e.second.find(f - (readlines / 2)) == e.second.end()) {
//                    res[e.first].insert(f);
//                }
//            } else {
//                std::set<size_t>::iterator it = e.second.find(f + (readlines / 2));
//                if (it != e.second.end()) {
//                    e.second.erase(it);
//                }
//                res[e.first].insert(f);
//            }
//        }
//    }

//    if (!matchingReads.empty()) {
//        _stats->printMatchingReadsToFile("extracted_reads.fa", matchingReads, res);
//    }

    // return index Counts <query ID, number of read hits>

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
