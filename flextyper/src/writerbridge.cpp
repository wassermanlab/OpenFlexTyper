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

        ft::QueryClass refQuery = ftMap.checkQuery(std::make_pair(queryIndex, QueryType::REF));
        if (refQuery) {
            u_int ref_count = refQuery.getCount();
            std::string ref_NUK =  _utils->joinString(refQuery.getFlagKmers(FlagType::NUK));
        } else {
            u_int ref_count = 0;
        }

        ft::QueryClass altQuery = ftMap.getQuery(std::make_pair(queryIndex, QueryType::ALT));
        if (altQuery) {
            u_int ref_count = refQuery.getCount();
        } else {
            u_int ref_count = 0;
        }
        ft::QueryClass croQuery = ftMap.getQuery(std::make_pair(queryIndex, QueryType::CRO));
        if (croQuery) {
            u_int cro_count = croQuery.getCount();
        } else {
            u_int ref_count = 0;
        }

        std::string ref_NUK = "";
        std::string alt_NUK = "";
        std::string cro_NUK = "";
        std::string ref_OCK = "";
        std::string alt_OCK = "";
        std::string cro_OCK = "";




        int QueryClass::getCount(){return _count;}

        if (allCounts.count({queryIndex, QueryType::REF}) > 0){
            ref_count = allCounts[{queryIndex, QueryType::REF}];
        }
        if (allCounts.count({queryIndex, QueryType::ALT}) > 0){
            alt_count = allCounts[{queryIndex, QueryType::ALT}];
        }
        if (allCounts.count({queryIndex, QueryType::CRO}) > 0) {
            cro_count = allCounts[{queryIndex, QueryType::CRO}];
        }

        if (nonUniqueKmers.count({queryIndex, QueryType::REF}) > 0){
            std::set<std::string> ref_NUKs = nonUniqueKmers[{queryIndex, QueryType::REF}];
            for (auto it=ref_NUKs.begin(); it != ref_NUKs.end(); ++it)
                ref_NUK += *it + ',' ;
        }
        if (nonUniqueKmers.count({queryIndex, QueryType::ALT}) > 0){
            std::set<std::string> alt_NUKs = nonUniqueKmers[{queryIndex, QueryType::ALT}];
            for (auto it=alt_NUKs.begin(); it != alt_NUKs.end(); ++it)
                alt_NUK += *it + ',' ;
        }
        if (nonUniqueKmers.count({queryIndex, QueryType::CRO}) > 0){
            std::set<std::string> cro_NUKs = nonUniqueKmers[{queryIndex, QueryType::CRO}];
            for (auto it=cro_NUKs.begin(); it != cro_NUKs.end(); ++it)
                cro_NUK += *it + ',' ;
        }
        /*
        if (overCountedKmers.count({queryIndex, QueryType::REF}) > 0){
            std::set<std::string> ref_OCKs = overCountedKmers[{queryIndex, QueryType::REF}];
            for (auto it=ref_OCKs.begin(); it != ref_OCKs.end(); ++it)
                ref_OCK += *it + ',' ;
        }
        if (overCountedKmers.count({queryIndex, QueryType::ALT}) > 0){
            std::set<std::string> alt_OCKs = overCountedKmers[{queryIndex, QueryType::ALT}];
            for (auto it=alt_OCKs.begin(); it != alt_OCKs.end(); ++it)
                alt_OCK += *it + ',' ;
        }
        if (overCountedKmers.count({queryIndex, QueryType::CRO}) > 0){
            std::set<std::string> cro_OCKs = overCountedKmers[{queryIndex, QueryType::CRO}];
            for (auto it=cro_OCKs.begin(); it != cro_OCKs.end(); ++it)
                cro_OCK += *it + ',' ;
        }
        */

        std::string counts;
        if (crossover) {
            counts = '\t' + std::to_string(ref_count) + '\t' + std::to_string(cro_count) + '\t' + std::to_string(alt_count) ;
            if (ignoreNonUniqueKmers) {
                counts += '\t' + ref_NUK + '\t' + cro_NUK + '\t' + alt_NUK ;
            }
            if (includeOverCountedKmers) {
               counts += '\t' + ref_OCK + '\t' + cro_OCK + '\t' + alt_OCK ;
            }

        } else {
            counts = '\t' + std::to_string(ref_count) + '\t' + std::to_string(alt_count) ;
            if (ignoreNonUniqueKmers) {
                counts += '\t' + ref_NUK + '\t' + alt_NUK ;
            }
            if (includeOverCountedKmers) {
               counts += '\t' + ref_OCK + '\t' + alt_OCK ;
            }

        }

        counts += '\n';
        // returnMatchesOnly doesnt work as we are just appending the lines, not creating a new file


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
