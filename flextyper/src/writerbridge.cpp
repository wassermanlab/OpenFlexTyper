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
void WriterBridge::saveQueryOutput(ft::FTMap ftMap,
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
            if (ftMap.getCrossoverFlag()) {
                header = '\t' + std::string("start_point_count") + '\t' + std::string("crossover_count") + '\t' + std::string("endpoint_count");
                if (ftMap.getIgnoreNonUniqueKmersFlag()) {
                    header += '\t' + std::string("Start_Non_Unique_Kmers") + '\t' + std::string("Crossover_Non_Unique_Kmers") + '\t' + std::string("Endpoint_Non_Unique_Kmers");
                }
                if (ftMap.getOverCountedFlag()) {
                    header += '\t' + std::string("Start_Over_Counted_Kmers") + '\t' + std::string("Crossover_Over_Counted_Kmers") + '\t' + std::string("Endpoint_Over_Counted_Kmers");
                }

            } else {
                header = '\t' + std::string("Ref_count") + '\t' + std::string("Alt_count") ;

                if (ftMap.getIgnoreNonUniqueKmersFlag()) {
                    header += '\t' + std::string("Ref_Non_Unique_Kmers") + '\t' + std::string("Alt_Non_Unique_Kmers");
                }
                if (ftMap.getOverCountedFlag()) {
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

        if (ftMap.checkQIDT(std::make_pair(queryIndex, QueryType::REF))) {
            ft::QueryClass refQuery = ftMap.getQuery(std::make_pair(queryIndex, QueryType::REF));
            u_int ref_count = refQuery.getCount();
            std::string ref_NUK =  _utils->joinString(refQuery.getFlagKmers(FlagType::NUK));
        } else {
            u_int ref_count = 0;
        }

        if (ftMap.checkQIDT(std::make_pair(queryIndex, QueryType::ALT))) {
            ft::QueryClass altQuery = ftMap.getQuery(std::make_pair(queryIndex, QueryType::ALT));
            u_int alt_count = altQuery.getCount();
            std::string alt_NUK =  _utils->joinString(altQuery.getFlagKmers(FlagType::NUK));
            std::string alt_OCK =  _utils->joinString(altQuery.getFlagKmers(FlagType::OCK));
        } else {
            u_int alt_count = 0;
        }

        if (ftMap.checkQIDT(std::make_pair(queryIndex, QueryType::CRO))) {
            ft::QueryClass croQuery = ftMap.getQuery(std::make_pair(queryIndex, QueryType::CRO));
            u_int cro_count = croQuery.getCount();
            std::string cro_NUK =  _utils->joinString(croQuery.getFlagKmers(FlagType::NUK));
            std::string cro_OCK =  _utils->joinString(croQuery.getFlagKmers(FlagType::OCK));
        } else {
            u_int cro_count = 0;
        }

        std::string counts;
        if (ftMap.getCrossoverFlag()) {
            counts = '\t' + std::to_string(ref_count) + '\t' + std::to_string(cro_count) + '\t' + std::to_string(alt_count) ;
            if (ftMap.getIgnoreNonUniqueKmersFlag()) {
                counts += '\t' + ref_NUK + '\t' + cro_NUK + '\t' + alt_NUK ;
            }
            if (ftMap.getOverCountedFlag()) {
               counts += '\t' + ref_OCK + '\t' + cro_OCK + '\t' + alt_OCK ;
            }

        } else {
            counts = '\t' + std::to_string(ref_count) + '\t' + std::to_string(alt_count) ;
            if (ftMap.getIgnoreNonUniqueKmersFlag()) {
                counts += '\t' + ref_NUK + '\t' + alt_NUK ;
            }
            if (ftMap.getOverCountedFlag()) {
               counts += '\t' + ref_OCK + '\t' + alt_OCK ;
            }

        }

        counts += '\n';
        // returnMatchesOnly doesnt work as we are just appending the lines, not creating a new file


        if (ftMap.getMatchesOnlyFlag()){
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
