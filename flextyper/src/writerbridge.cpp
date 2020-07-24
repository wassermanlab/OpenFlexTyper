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
    _refData = true;
    if (!ftMap._ftProps.getRefOnlyFlag()){ _altData = true;}
    if (ftMap._ftProps.getCrossoverFlag()){_croData = true;}
    if (ftMap._ftProps.getOverCountedFlag()){_OCK = true;}
    if (ftMap._ftProps.getIgnoreNonUniqueKmersFlag()){_NUK = true;}
    if (ftMap._ftProps.getMatchesOnlyFlag()){_MatchesOnly = true;}
}

//======================================================================
std::string WriterBridge::createHeader()
{
    std::string header;
    if (_croData) {
        std::cout << "CrossOver Header" << std::endl;
        header = '\t' + std::string("Start_Count") + '\t' + std::string("Crossover_Count") + '\t' + std::string("End_Count");
        if (_NUK) {
            header += '\t' + std::string("Start_Non_Unique_Kmers") + '\t' + std::string("Crossover_Non_Unique_Kmers") + '\t' + std::string("End_Non_Unique_Kmers");
        }
        if (_OCK) {
            header += '\t' + std::string("Start_Over_Counted_Kmers") + '\t' + std::string("Crossover_Over_Counted_Kmers") + '\t' + std::string("End_Over_Counted_Kmers");
        }
    } else if (!_croData && _altData){
        std::cout << "Ref and Alt Header" << std::endl;
        header = '\t' + std::string("Ref_Count") + '\t' + std::string("Alt_Count");

        if (_NUK) {
            header += '\t' + std::string("Ref_Non_Unique_Kmers") + '\t' + std::string("Alt_Non_Unique_Kmers");
        }
        if (_OCK) {
            header += '\t' + std::string("Ref_Over_Counted_Kmers") + '\t' + std::string("Alt_Over_Counted_Kmers");
        }
    } else if (!_croData && !_altData){
        std::cout << "Ref Only Header" << std::endl;
        header = '\t' + std::string("Ref_Count");
        if (_NUK) {
            header += '\t' + std::string("Ref_Non_Unique_Kmers");
        }
        if (_OCK) {
            header += '\t' + std::string("Ref_Over_Counted_Kmers");
        }
    }
    header += '\n';
    std::cout << header << std::endl;
    return header;
}
//======================================================================
std::string WriterBridge::formatOutputMap()
{
    std::string outputLine = "";
    if (_croData) {
        //std::cout << "Ref , alt and cro " << std::endl;
        //std::cout << "output CRO Map count " << _outputMap["croCount"] << std::endl;
        outputLine = '\t' + _outputMap["refCount"] + '\t' + _outputMap["croCount"]  + '\t' + _outputMap["altCount"] ;
        if (_NUK) {
            outputLine +='\t' + _outputMap["refNUK"] + '\t' + _outputMap["croNUK"]  + '\t' + _outputMap["altNUK"] ;
        }
        if (_OCK) {
            outputLine +='\t' + _outputMap["refOCK"] + '\t' + _outputMap["croOCK"]  + '\t' + _outputMap["altOCK"] ;
        }

    } else if (!_croData && _altData){
        //std::cout << "Ref and Alt" << std::endl;
        //std::cout << "output alt Map count " << _outputMap["altCount"] << std::endl;
        outputLine = '\t' + _outputMap["refCount"] + '\t' + _outputMap["altCount"] ;
        if (_NUK) {
            outputLine +='\t' + _outputMap["refNUK"] + '\t' + _outputMap["altNUK"] ;
        }
        if (_OCK) {
            outputLine +='\t' + _outputMap["refOCK"] + '\t' + _outputMap["altOCK"] ;
        }

    } else if (!_croData && !_altData){
        //std::cout << "Ref only" << std::endl;
        //std::cout << "output REF Map count " << _outputMap["refCount"] << std::endl;
        outputLine = '\t' + _outputMap["refCount"] ;
        //std::cout << " outputLine " << outputLine <<std::endl;
        if (_NUK) {
            outputLine +='\t' + _outputMap["refNUK"]  ;
        }
        if (_OCK) {
            outputLine +='\t' + _outputMap["refOCK"] ;
        }
    }
    //std::cout << " outputLine " << outputLine <<std::endl;
    return outputLine;
}

//======================================================================
std::string WriterBridge::getFlagKmers(const ft::QueryClass& query, const ft::FlagType flag)
{
    std::cout << "add flag kmers " << std::endl;
    std::string queryFlagK;
    if (query.hasFlag(flag)){
        std::set<std::string> flagKmers = query.getFlagKmers(flag);
        std::cout << "Number of flag kmers " << flagKmers.size() << std::endl;
        queryFlagK = _utils->joinString(query.getFlagKmers(flag));

    } else {
        std::cout<< "Query doesnt have that flag" << std::endl;
    }
    std::cout << "formatted string " << queryFlagK << std::endl;
    return queryFlagK;
}

//======================================================================
void WriterBridge::addQueryToOutput( const ft::QueryClass& query, const std::string prefix)
{
    //std::cout << "add query to output Map" << std::endl;
    u_int count = query.getCount();
    _outputMap[prefix+"Matches"] = "false";
    if (count > 0){
        _outputMap[prefix+"Matches"] = "true";
        //std::cout << "Output Map Matches " << _outputMap[prefix+"Matches"] << std::endl;
    } else {
        _outputMap[prefix+"Matches"] = "false";
        //std::cout << "No output Map Matches " << _outputMap[prefix+"Matches"] << std::endl;
    }
    //std::cout << "output Map Matches " << _outputMap[prefix+"Matches"] << std::endl;

    _outputMap[prefix+"Count"] = std::to_string(count);
    //std::cout << "prefix " << prefix << " output Map count " << _outputMap[prefix+"Count"] << std::endl;
    if (_OCK)
    {
        //std::cout << "Add OCK" << std::endl;
         std::string refOCK = getFlagKmers(query, ft::FlagType::OCK);
        _outputMap[prefix+"OCK"] = refOCK;
        //std::cout << "OCKs  " << refOCK << std::endl;
    }

    if (_NUK)
    {
        //std::cout << "Add NUK" << std::endl;
        std::string refNUK = getFlagKmers(query, ft::FlagType::NUK);
        _outputMap[prefix+"NUK"] = refNUK;
        //std::cout << "NUKs  " << refNUK << std::endl;
    }
}

//======================================================================
void WriterBridge::saveOutput(const ft::FTMap& ftMap)
{

    setOutputOptions(ftMap);

    const fs::path& inputQueryFile = ftMap._ftProps.getPathToQueryFile();
    const fs::path& outputQueryFile = ftMap._ftProps.getOutputFile();

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
        std::cout<< "line  " << line << std::endl;
        if (line[line.length()-1] == '\n') {
            line.erase(line.length()-1);
        }

        // header line <- might be issue if there is >1 header line
        if (line[0] == '#') {
            //std::cout << "line is a header line" << std::endl;
            std::string header = createHeader();
            line.append(header);
            outputFileStream << line;
            continue;
        }

        std::vector<std::string> splitline = _utils->split(line, '\t');
        uint fileIndex = atoi(splitline[0].c_str());
        int queryIndex = _utils->fileIndexToQueryIndex(fileIndex);
        //std::cout << "fileIndex " << fileIndex  << " query Index " << queryIndex << std::endl;

        ft::QueryClass refQuery = ftMap.getQuery(std::make_pair(queryIndex, ft::QueryType::REF));


        //std::cout << "Ref Query " << refQuery._qID << std::endl;
        addQueryToOutput(refQuery, "ref");
        //std::cout << "prefix ref " << " output Map count " << _outputMap["refCount"] << std::endl;
        //std::cout << "Check for Alt and Cro" << std::endl;

        if (_altData){
            //std::cout << "Alt Query " << std::endl;
            ft::QueryClass altQuery = ftMap.getQuery(std::make_pair(queryIndex, ft::QueryType::ALT));
            //std::cout << "Alt Query " << altQuery._qID << std::endl;
            addQueryToOutput(altQuery, "alt");
            //std::cout << "output Alt Map count " << _outputMap["altCount"] << std::endl;
        }

        if (_croData){
            //std::cout << "Cro Query " << std::endl;
            ft::QueryClass croQuery = ftMap.getQuery(std::make_pair(queryIndex, ft::QueryType::CRO));
            addQueryToOutput(croQuery, "cro");
            //std::cout << "output CRO Map count " << _outputMap["croCount"] << std::endl;
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
        //std::cout << "outputLine  " << outputLine << std::endl;
        _outputMap.clear();

        line.append(outputLine);
        line.append("\n");
        std::cout << line << std::endl;
        outputFileStream << line;

    }
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
