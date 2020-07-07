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
void WriterBridge::saveQueryOutput(ft::FTMap& ftMap)

{
    FTProp ftProps = ftMap.getFTProps();
    fs::path inputQueryFile = ftProps.getPathToQueryFile();
    fs::path outputQueryFile = ftProps.getOutputFolder();

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
            if (ftProps.getCrossoverFlag()) {
                header = '\t' + std::string("start_point_count") + '\t' + std::string("crossover_count") + '\t' + std::string("endpoint_count");
                if (ftProps.getIgnoreNonUniqueKmersFlag()) {
                    header += '\t' + std::string("Start_Non_Unique_Kmers") + '\t' + std::string("Crossover_Non_Unique_Kmers") + '\t' + std::string("Endpoint_Non_Unique_Kmers");
                }
                if (ftProps.getOverCountedFlag()) {
                    header += '\t' + std::string("Start_Over_Counted_Kmers") + '\t' + std::string("Crossover_Over_Counted_Kmers") + '\t' + std::string("Endpoint_Over_Counted_Kmers");
                }

            } else {
                header = '\t' + std::string("Ref_count") + '\t' + std::string("Alt_count") ;

                if (ftProps.getIgnoreNonUniqueKmersFlag()) {
                    header += '\t' + std::string("Ref_Non_Unique_Kmers") + '\t' + std::string("Alt_Non_Unique_Kmers");
                }
                if (ftProps.getOverCountedFlag()) {
                    header += '\t' + std::string("Ref_Over_Counted_Kmers") + '\t' + std::string("Alt_Over_Counted_Kmers");
                }
            }

            header += '\n';

            std::cout << header << std::endl;

            line.append(header);
            outputFileStream << line;
            continue;
        }
        std::vector<std::string> splitline = _utils->split(line, '\t');
        uint fileIndex = atoi(splitline[0].c_str());
        int queryIndex = _utils->fileIndexToQueryIndex(fileIndex);


        u_int ref_count =0;
        std::string ref_NUK;
        std::string ref_OCK;
        u_int alt_count =0;
        std::string alt_NUK;
        std::string alt_OCK;
        u_int cro_count =0;
        std::string cro_NUK;
        std::string cro_OCK;

        if (ftMap.checkForQIDT(std::make_pair(queryIndex, QueryType::REF))) {
            QueryClass& refQuery = ftMap.getQuery(std::make_pair(queryIndex, QueryType::REF));
            ref_count = refQuery.getCount();
            ref_NUK =  _utils->joinString(refQuery.getFlagKmers(FlagType::NUK));
            ref_OCK =  _utils->joinString(refQuery.getFlagKmers(FlagType::OCK));
        }

        if (ftMap.checkForQIDT(std::make_pair(queryIndex, QueryType::ALT))) {
            QueryClass& altQuery = ftMap.getQuery(std::make_pair(queryIndex, QueryType::ALT));
            alt_count = altQuery.getCount();
            alt_NUK =  _utils->joinString(altQuery.getFlagKmers(FlagType::NUK));
            alt_OCK =  _utils->joinString(altQuery.getFlagKmers(FlagType::OCK));
        }

        if (ftMap.checkForQIDT(std::make_pair(queryIndex, QueryType::CRO))) {
            QueryClass& croQuery = ftMap.getQuery(std::make_pair(queryIndex, QueryType::CRO));
            cro_count = croQuery.getCount();
            cro_NUK =  _utils->joinString(croQuery.getFlagKmers(FlagType::NUK));
            cro_OCK =  _utils->joinString(croQuery.getFlagKmers(FlagType::OCK));
        }

        std::string counts;
        if (ftProps.getCrossoverFlag()) {
            counts = '\t' + std::to_string(ref_count) + '\t' + std::to_string(cro_count) + '\t' + std::to_string(alt_count) ;
            if (ftProps.getIgnoreNonUniqueKmersFlag()) {
                counts += '\t' + ref_NUK + '\t' + cro_NUK + '\t' + alt_NUK ;
            }
            if (ftProps.getOverCountedFlag()) {
               counts += '\t' + ref_OCK + '\t' + cro_OCK + '\t' + alt_OCK ;
            }

        } else {
            counts = '\t' + std::to_string(ref_count) + '\t' + std::to_string(alt_count) ;
            if (ftProps.getIgnoreNonUniqueKmersFlag()) {
                counts += '\t' + ref_NUK + '\t' + alt_NUK ;
            }
            if (ftProps.getOverCountedFlag()) {
               counts += '\t' + ref_OCK + '\t' + alt_OCK ;
            }

        }

        counts += '\n';
        // returnMatchesOnly doesnt work as we are just appending the lines, not creating a new file


        if (ftProps.getMatchesOnlyFlag()){
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
