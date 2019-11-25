#include "writerbridge.h"
#include <sstream>
#include <iostream>
#include <fstream>

namespace ft {
//======================================================================
WriterBridge::WriterBridge()
    : _utils(&_ownedUtils)
{
}

//======================================================================
void WriterBridge::saveQueryOutput(MapOfCounts allCounts, bool returnMatchesOnly, bool crossover,
                                   const fs::path& inputQueryFile,
                                   const fs::path& outputQueryFile)
{
    // save counts to output tsv
    std::fstream outputFileStream;
    outputFileStream.open(outputQueryFile, std::ios::out);
    if (!outputFileStream || !outputFileStream.is_open()) {
        std::cout << "Couldn't open output file" << std::endl;
    }

    std::ifstream queryFileStream;
    queryFileStream.open(inputQueryFile, std::ios::in);

    if (!queryFileStream || !queryFileStream.is_open()) {
        std::cout << "Couldn't open query file" << std::endl;
    }

    std::string line;

    while (getline(queryFileStream, line)) {
        if (line[line.length()-1] == '\n') {
            line.erase(line.length()-1);
        }
        if (line[0] == '#') {
            std::string header;
            if (crossover) {
                header = '\t' + std::string("start_point_count") + '\t' + std::string("crossover_count") + '\t' + std::string("endpoint_count") + '\n';
            } else {
                header = '\t' + std::string("Ref_count") + '\t'+ std::string("Alt_count") + '\n';
            }
            line.append(header);
            outputFileStream << line;
            continue;
        }
        std::vector<std::string> splitline = _utils->split(line, '\t');
        uint fileIndex = atoi(splitline[0].c_str());
        int queryIndex = _utils->fileIndexToQueryIndex(fileIndex);
        uint ref_count = 0;
        uint alt_count = 0;
        uint cro_count = 0;

        if (allCounts.count({queryIndex, QueryType::REF}) > 0){
            ref_count = allCounts[{queryIndex, QueryType::REF}];
        }
        if (allCounts.count({queryIndex, QueryType::ALT}) > 0){
            alt_count = allCounts[{queryIndex, QueryType::ALT}];
        }
        if (allCounts.count({queryIndex, QueryType::CRO}) > 0) {
            cro_count = allCounts[{queryIndex, QueryType::CRO}];
        }

        std::string counts;
        if (crossover) {
            counts = '\t' + std::to_string(ref_count) + '\t' + std::to_string(cro_count) + '\t' + std::to_string(alt_count) + '\n';
        } else {
            counts = '\t' + std::to_string(ref_count) + '\t' + std::to_string(alt_count) + '\n';
        }
        if (returnMatchesOnly){
            line.append(counts);
            //std::cout << line; //<< std::endl;
            outputFileStream << line;
        }else{
            line.append(counts);
            // std::cout << line; //<< std::endl;
            outputFileStream << line;
        }
    }
}

//======================================================================
void WriterBridge::overrideUtils(std::shared_ptr<IUtils> utils)
{
    _utils = utils.get();
}

//======================================================================
WriterBridge::~WriterBridge()
{
}
}
