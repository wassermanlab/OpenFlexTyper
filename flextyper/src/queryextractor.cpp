#include "queryextractor.h"

namespace ft {

//======================================================================
QueryExtractor::QueryExtractor()
    : _utils(&_ownedUtils)
{
}

//======================================================================
void QueryExtractor::getInputQueriesRoutine(const std::string& refSequence, const std::string& altSequence, uint fileIndex, std::set<Query>& inputQueries)
{
    int queryIndex = _utils->fileIndexToQueryIndex(fileIndex);
    inputQueries.insert(std::make_tuple(queryIndex, refSequence, altSequence, "" /* is empty */));
}

//======================================================================
void QueryExtractor::getStartAndEndPointSequences(const std::string& startPointRef, const std::string& endPointRef, uint fileIndex, std::set<Query>& inputQueries)
{
    int queryIndex = _utils->fileIndexToQueryIndex(fileIndex);

    std::string startPointSeq = startPointRef.substr(0);
    std::string endPointSeq   = endPointRef.substr(0);
    std::string crossoverSeq  = startPointRef.substr(0, startPointRef.length() / 2) + endPointRef.substr(endPointRef.length() / 2);

    inputQueries.insert(std::make_tuple(queryIndex, startPointSeq, endPointSeq, crossoverSeq));
}

//======================================================================
std::set<Query> QueryExtractor::getInputQueries(bool refOnly, bool crossover, const fs::path& pathToQueryFile)
{
    //generate the inputQueries
    // query id, ref, alt, var pos
    //typedef std::tuple<uint, std::string, std::string, uint> query;

    std::set<Query> inputQueries;

    // std::cout << "path to query file : " << _inputQueryFile << std::endl;
    std::ifstream queryFileStream(pathToQueryFile);
    if (!queryFileStream.is_open()) {
        std::cerr << "Couldn't open queryFile" << std::endl;
        exit(1);
    }
    std::string line;

    while (getline(queryFileStream, line)) {
        if (line[0] == '#') continue;
        std::vector<std::string> splitline = _utils->split(line, '\t');
        uint fileIndex = atoi(splitline[0].c_str());
        std::string refSequence;
        std::string altSequence;

        if (refOnly) {
            refSequence = splitline[1];
            altSequence = "";
        } else {
            refSequence = splitline[1];
            altSequence = splitline[2];
        }

        if (!crossover) {
            getInputQueriesRoutine(refSequence, altSequence, fileIndex, inputQueries);
        } else {
            getStartAndEndPointSequences(refSequence, altSequence, fileIndex, inputQueries);
        }
    }

    queryFileStream.close();
    return inputQueries;
}

//======================================================================
void QueryExtractor::overrideUtils(std::shared_ptr<IUtils> utils)
{
    _utils = utils.get();
}

//======================================================================
QueryExtractor::~QueryExtractor()
{
}
}
