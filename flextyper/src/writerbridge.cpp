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
void WriterBridge::setOutputOptions(const ft::FTMap& ftMap)
{
    _refData = true;
    if (!ftMap.getRefOnlyFlag()){ _altData = true;}
    if (!ftMap.getCrossoverFlag()){_croData = true;}
    if (!ftMap.getOverCountedFlag()){_OCK = true;}
    if (!ftMap.getIgnoreNonUniqueKmersFlag()){_NUK = true;}
    if (ftMap.getMatchesOnlyFlag()){_MatchesOnly = true;}
}


std::string WriterBridge::createHeader()
{
    std::string header;

    if (_croData) {
        header = '\t' + std::string("start_point_count") + '\t' + std::string("crossover_count") + '\t' + std::string("endpoint_count");
        if (_NUK) {
            header += '\t' + std::string("Start_Non_Unique_Kmers") + '\t' + std::string("Crossover_Non_Unique_Kmers") + '\t' + std::string("Endpoint_Non_Unique_Kmers");
        }
        if (_OCK) {
            header += '\t' + std::string("Start_Over_Counted_Kmers") + '\t' + std::string("Crossover_Over_Counted_Kmers") + '\t' + std::string("Endpoint_Over_Counted_Kmers");
        }

    } else {
        header = '\t' + std::string("Ref_count") + '\t' + std::string("Alt_count") ;

        if (_NUK) {
            header += '\t' + std::string("Ref_Non_Unique_Kmers") + '\t' + std::string("Alt_Non_Unique_Kmers");
        }
        if (_OCK) {
            header += '\t' + std::string("Ref_Over_Counted_Kmers") + '\t' + std::string("Alt_Over_Counted_Kmers");
        }
    }

    header += '\n';
    std::cout << header << std::endl;
    return header;

}
//======================================================================
std::string WriterBridge::formatOutputMap(std::map<std::string, std::string>& outputMap)
{
    std::string outputLine;

    if (_croData) {
        outputLine = '\t' + outputMap["refCount"] + '\t' + outputMap["croCount"]  + '\t' + outputMap["altCount"] ;
        if (_NUK) {
            outputLine +='\t' + outputMap["refNUK"] + '\t' + outputMap["croNUK"]  + '\t' + outputMap["altNUK"] ;
        }
        if (_OCK) {
            outputLine +='\t' + outputMap["refOCK"] + '\t' + outputMap["croOCK"]  + '\t' + outputMap["altOCK"] ;
        }

    } else {
        outputLine = '\t' + outputMap["refCount"] + '\t' + outputMap["altCount"] ;
        if (_NUK) {
            outputLine +='\t' + outputMap["refNUK"] + '\t' + outputMap["altNUK"] ;
        }
        if (_OCK) {
            outputLine +='\t' + outputMap["refOCK"] + '\t' + outputMap["altOCK"] ;
        }

    }
    std::cout << " outputLine " << outputLine <<std::endl;
    return outputLine;
}

//======================================================================
std::string WriterBridge::getFlagKmers(const ft::QueryClass& query, const ft::FlagType flag)
{
    std::string queryFlagK = _utils->joinString(query.getFlagKmers(flag));
    return queryFlagK;
}

//======================================================================
void WriterBridge::addQueryToOutput(std::map<std::string, std::string>& outputMap, const ft::QueryClass& query, const std::string prefix)
{
    u_int count = query.getCount();
    if (count == 0){outputMap[prefix+"Matches"] = false;}
    else {outputMap[prefix+"Matches"] = true;}
    outputMap[prefix+"counts"] = '\t' + std::to_string(count);

    if (_OCK)
    {
        std::string refOCK = getFlagKmers(query, ft::FlagType::OCK);
        outputMap[prefix+"OCK"] = refOCK;
    }

    if (_NUK)
    {
        std::string refNUK = getFlagKmers(query, ft::FlagType::NUK);
        outputMap[prefix+"NUK"] = refNUK;
    }

}



//======================================================================
void WriterBridge::saveOutput(const ft::FTMap& ftMap)
{

    setOutputOptions(ftMap);
    const fs::path& inputQueryFile = ftMap.getPathToQueryFile();
    const fs::path& outputQueryFile = ftMap.getOutputFile();

    std::cout << "Input Query File " << inputQueryFile << std::endl;
    std::cout << "Output Query File " << outputQueryFile << std::endl;
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

        // header line <- might be issue if there is >1 header line
        if (line[0] == '#') {
            std::string header = createHeader();
            line.append(header);
            outputFileStream << line;
            continue;
        }

        std::vector<std::string> splitline = _utils->split(line, '\t');
        uint fileIndex = atoi(splitline[0].c_str());
        int queryIndex = _utils->fileIndexToQueryIndex(fileIndex);

        std::map<std::string, std::string> outputMap;


        ft::QueryClass refQuery = ftMap.getQuery(std::make_pair(queryIndex, ft::QueryType::REF));
        addQueryToOutput(outputMap, refQuery, "ref");

        if (_altData){
            ft::QueryClass altQuery = ftMap.getQuery(std::make_pair(queryIndex, ft::QueryType::ALT));
            addQueryToOutput(outputMap, altQuery, "alt");
        }

        if (_croData){
            ft::QueryClass croQuery = ftMap.getQuery(std::make_pair(queryIndex, ft::QueryType::CRO));
            addQueryToOutput(outputMap, croQuery, "cro");
        }

        if (_MatchesOnly)
        {
            // if no matches for any of the expected data sets then skip
            bool skip = true;
            if (_refData &&  outputMap["refMatches"] == "true"){skip = false;} //ref counts found, dont skip
            if (_altData &&  outputMap["altMatches"] == "true"){skip = false;} //alt counts found, dont skip
            if (_croData &&  outputMap["croMatches"] == "true"){skip = false;} //cro counts found, dont skip

            if (skip){outputMap.clear(); continue;}
        }

        std::string outputLine = formatOutputMap(outputMap);

        outputMap.clear();

        line.append(outputLine);
        // std::cout << line; //<< std::endl;
        outputFileStream << line;

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
