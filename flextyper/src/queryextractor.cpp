#include "queryextractor.h"

namespace ft {

//======================================================================
QueryExtractor::QueryExtractor()
    : _utils(&_ownedUtils)
{
}

//======================================================================
std::set<Query> QueryExtractor::getInputQueries(bool refOnly, bool crossover, const fs::path& pathToQueryFile)
{
    //generate the inputQueries
    // query id, ref, alt, var pos
    //typedef std::tuple<uint, std::string, std::string, uint> query;

    std::set<Query> inputQueries;

    std::cout << "path to query file : " << pathToQueryFile << std::endl;
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
        //std::cout << "file Index " << fileIndex << std::endl;
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
            //std::cout << "add ref/alt sequences " << fileIndex << std::endl;
            //std::cout << "number of queries extracted " << inputQueries.size() << std::endl;
            inputQueries.insert(std::make_tuple(fileIndex, refSequence, altSequence, "" /* is empty */));
            //std::cout << "number of queries extracted " << inputQueries.size() << std::endl;
        } else {
            int queryIndex = _utils->fileIndexToQueryIndex(fileIndex);
            std::string startPointSeq = refSequence.substr(0);
            std::string endPointSeq   = altSequence.substr(0);
            std::string crossoverSeq  = refSequence.substr(0, refSequence.length() / 2) + altSequence.substr(altSequence.length() / 2);
            inputQueries.insert(std::make_tuple(queryIndex, startPointSeq, endPointSeq, crossoverSeq));
        }
    }

    queryFileStream.close();
    //std::cout << "number of queries extracted " << inputQueries.size() << std::endl;
    return (inputQueries);
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
