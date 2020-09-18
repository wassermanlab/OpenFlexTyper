#include "queryextractor.h"
#include <regex>

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
        throw std::runtime_error( "Couldn't open queryFile");
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
        std::cout << "Ref sequence " << refSequence.substr(0,10) << std::endl;
        std::cout << "Alt sequence " << altSequence.substr(0,10) << std::endl;

        std::size_t rfound = refSequence.find_first_not_of("acgtACGT");
        if (rfound != std::string::npos)
        {
             throw std::runtime_error("invalid query sequences: Ref sequence contains invalid characters ");
            exit(1);
        }
        std::size_t afound = altSequence.find_first_not_of("acgtACGT");
        if (afound != std::string::npos)
        {
             throw std::runtime_error("invalid query sequences: Alt sequence contains invalid characters ");
            exit(1);
        }

        if (!crossover) {
            inputQueries.insert(std::make_tuple(fileIndex, refSequence, altSequence, "" /* is empty */));
            std::cout << fileIndex << "  " << refSequence.substr(0,10) << "  " << altSequence.substr(0,10) << std::endl;
        } else {
            std::string startPointSeq = refSequence.substr(0);
            std::string endPointSeq   = altSequence.substr(0);
            std::string crossoverSeq  = refSequence.substr(0, refSequence.length() / 2) + altSequence.substr(altSequence.length() / 2);
            inputQueries.insert(std::make_tuple(fileIndex, startPointSeq, endPointSeq, crossoverSeq));
            std::cout << fileIndex << "  " << startPointSeq.substr(0,10) << "  " << endPointSeq.substr(0,10) << "  " << crossoverSeq.substr(0,10) << std::endl;
        }
    }

    queryFileStream.close();

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
