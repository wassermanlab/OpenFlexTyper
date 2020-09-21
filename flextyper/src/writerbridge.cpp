#include "writerbridge.h"
#include <sstream>
#include <iostream>
#include <fstream>

namespace ft {
//======================================================================
WriterBridge::WriterBridge()
    : _outputMap(),
      _utils(&_ownedUtils)

{
    _refData = false;
    _altData = false;
    _croData = false;
    _OCK = false;
    _NUK = false;
    _MatchesOnly = false;
}
//======================================================================
void WriterBridge::setOutputOptions(const ft::FTMap& ftMap)
{
    const FTProp& ftProps = ftMap.getFTProps();
    _refData = true;
    if (!ftProps.getRefOnlyFlag()){ _altData = true;}
    if (ftProps.getCrossoverFlag()){_croData = true;}
    if (ftProps.outputFlag(ft::FlagType::OCK)){_OCK = true;}
    if (ftProps.outputFlag(ft::FlagType::NUK)){_NUK = true;}
    if (ftProps.getMatchesOnlyFlag()){_MatchesOnly = true;}
}

std::string WriterBridge::joinString(const std::set<std::string>& setOfStr, std::string delimeter)
{
    std::string output;
    std::set<std::string>::iterator it = setOfStr.begin();

    while (it != std::prev(setOfStr.end()))
    {
        output += (*it++) + delimeter;
    }
    output += *std::prev(setOfStr.end());
    return output;
}

//======================================================================
std::string WriterBridge::createHeader()
{
    std::string header;
    if (_croData) {
        header = '\t' + std::string("Start_Count") + '\t' + std::string("Crossover_Count") + '\t' + std::string("End_Count");
        if (_NUK) {
            header += '\t' + std::string("Start_Non_Unique_Kmers") + '\t' + std::string("Crossover_Non_Unique_Kmers") + '\t' + std::string("End_Non_Unique_Kmers");
        }
        if (_OCK) {
            header += '\t' + std::string("Start_Over_Counted_Kmers") + '\t' + std::string("Crossover_Over_Counted_Kmers") + '\t' + std::string("End_Over_Counted_Kmers");
        }
    } else if (!_croData && _altData){
        header = '\t' + std::string("Ref_Count") + '\t' + std::string("Alt_Count");

        if (_NUK) {
            header += '\t' + std::string("Ref_Non_Unique_Kmers") + '\t' + std::string("Alt_Non_Unique_Kmers");
        }
        if (_OCK) {
            header += '\t' + std::string("Ref_Over_Counted_Kmers") + '\t' + std::string("Alt_Over_Counted_Kmers");
        }
    } else if (!_croData && !_altData){
        header = '\t' + std::string("Ref_Count");
        if (_NUK) {
            header += '\t' + std::string("Ref_Non_Unique_Kmers");
        }
        if (_OCK) {
            header += '\t' + std::string("Ref_Over_Counted_Kmers");
        }
    }
    header += '\n';
    return header;
}
//======================================================================
std::string WriterBridge::formatOutputMap()
{
    std::string outputLine = "";
    if (_croData) {
        outputLine = '\t' + _outputMap["refCount"] + '\t' + _outputMap["croCount"]  + '\t' + _outputMap["altCount"] ;
        if (_NUK) {
            outputLine +='\t' + _outputMap["refNUK"] + '\t' + _outputMap["croNUK"]  + '\t' + _outputMap["altNUK"] ;
        }
        if (_OCK) {
            outputLine +='\t' + _outputMap["refOCK"] + '\t' + _outputMap["croOCK"]  + '\t' + _outputMap["altOCK"] ;
        }

    } else if (!_croData && _altData){
        outputLine = '\t' + _outputMap["refCount"] + '\t' + _outputMap["altCount"] ;
        if (_NUK) {
            outputLine +='\t' + _outputMap["refNUK"] + '\t' + _outputMap["altNUK"] ;
        }
        if (_OCK) {
            outputLine +='\t' + _outputMap["refOCK"] + '\t' + _outputMap["altOCK"] ;
        }

    } else if (!_croData && !_altData){
        outputLine = '\t' + _outputMap["refCount"] ;

        if (_NUK) {
            outputLine +='\t' + _outputMap["refNUK"]  ;
        }
        if (_OCK) {
            outputLine +='\t' + _outputMap["refOCK"] ;
        }
    }
    return outputLine;
}

//======================================================================
std::string WriterBridge::getFlagKmers(const ft::QueryClass& query, const ft::FlagType flag)
{

    std::string queryFlagK;

    std::set<std::string> flagKmers = query.getFlagKmers(flag);
    std::cout << "Query has " << flagKmers.size() << " flag kmers " << std::endl;
    if (flagKmers.size() > 0){
    queryFlagK = joinString(flagKmers, ",");
    }

    return queryFlagK;
}

//======================================================================
void WriterBridge::addQueryToOutput( const ft::QueryClass& query, const std::string prefix)
{
    u_int count = query.getCount();
    _outputMap[prefix+"Matches"] = "false";
    if (count > 0){
        _outputMap[prefix+"Matches"] = "true";
    } else {
        _outputMap[prefix+"Matches"] = "false"; 
    }

    _outputMap[prefix+"Count"] = std::to_string(count);

    if (_OCK)
    {
        std::cout << "get overCounted Kmers" << std::endl;
         std::string refOCK = getFlagKmers(query, ft::FlagType::OCK);
        std::cout << "OCK " << refOCK << std::endl;
        _outputMap[prefix+"OCK"] = refOCK;
    }

    if (_NUK)
    {
        std::cout << "get NonUnique Kmers" << std::endl;
        std::string refNUK = getFlagKmers(query, ft::FlagType::NUK);
        std::cout << "NUK " << refNUK << std::endl;
        _outputMap[prefix+"NUK"] = refNUK;
    }
}

//======================================================================
void WriterBridge::saveOutput(const ft::FTMap& ftMap)
{
    FTProp::Benchmark benchmark = FTProp::Benchmark(0);

    const FTProp& ftProps = ftMap.getFTProps();
    setOutputOptions(ftMap);

    const fs::path& inputQueryFile = ftProps.getPathToQueryFile();
    const fs::path& outputQueryFile = ftProps.getOutputFile();

    // save counts to output tsv
    std::fstream outputFileStream;
    outputFileStream.open(outputQueryFile, std::ios::out);
    if (!outputFileStream || !outputFileStream.is_open()) {
        FTProp::Log  << "Couldn't open " << outputQueryFile.string() << std::endl;
    }

    std::ifstream queryFileStream;
    queryFileStream.open(inputQueryFile, std::ios::in);

    if (!queryFileStream || !queryFileStream.is_open()) {
        FTProp::Log  << "Couldn't open " << inputQueryFile.string() << std::endl;
    }

    std::string line;

    while (getline(queryFileStream, line)) {
        if (line[line.length()-1] == '\n') {
            line.erase(line.length()-1);
        }

        // header line <- might be issue if there is >1 header line
        if (line[0] == '#') {
            std::cout << "line is a header line" << std::endl;
            std::string header = createHeader();
            line.append(header);
            outputFileStream << line;
            continue;
        }

        std::vector<std::string> splitline = _utils->split(line, '\t');
        uint fileIndex = atoi(splitline[0].c_str());
        int queryIndex = fileIndex;
        const ft::QueryClass& refQuery = ftMap.getQuery(std::make_pair(queryIndex, ft::QueryType::REF));
        addQueryToOutput(refQuery, "ref");


        if (_altData){
            const ft::QueryClass& altQuery = ftMap.getQuery(std::make_pair(queryIndex, ft::QueryType::ALT));
            addQueryToOutput(altQuery, "alt");
        }

        if (_croData){
            const ft::QueryClass& croQuery = ftMap.getQuery(std::make_pair(queryIndex, ft::QueryType::CRO));
            addQueryToOutput(croQuery, "cro");
        }

        if (_MatchesOnly)
        {
            // if no matches for any of the expected data sets then skip
            bool skip = true;
            if (_refData &&  _outputMap["refMatches"] == "true"){skip = false;} //ref counts found, dont skip
            if (_altData &&  _outputMap["altMatches"] == "true"){skip = false;} //alt counts found, dont skip
            if (_croData &&  _outputMap["croMatches"] == "true"){skip = false;} //cro counts found, dont skip

            if (skip){
                std::cout << "Skipping line " << std::endl;
                _outputMap.clear(); continue;
            }
        }

        std::string outputLine = formatOutputMap();
        _outputMap.clear();

        line.append(outputLine);
        line.append("\n");
        outputFileStream << line;

    }
    outputFileStream.close();
    benchmark.now("SaveOutput DONE ");
}

//======================================================================
void WriterBridge::overrideUtils(std::shared_ptr<IUtils> utils)
{
    _utils = utils.get();
}

//======================================================================
bool WriterBridge::getRefData(){return _refData;}
bool WriterBridge::getAltData(){return _altData;}
bool WriterBridge::getCroData(){return _croData;}
bool WriterBridge::getOCKFlag(){return _OCK;}
bool WriterBridge::getNUKFlag(){return _NUK;}
bool WriterBridge::getMatchesOnlyFlag(){return _MatchesOnly;}
std::map<std::string, std::string> WriterBridge::getOutputMap(){return _outputMap;}

//======================================================================
WriterBridge::~WriterBridge()
{
}
}
