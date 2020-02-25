#ifndef __TYPE_DEFS_H__
#define __TYPE_DEFS_H__

#include <set>
#include <iostream>
#include <map>

namespace ft {

enum QueryType {
    REF = 1, ALT, CRO
};

typedef std::string                                                  SearchType;             // SearchType declaration
const   std::string                                                  CENTERED = "CENTERED";  // search type centered approach
const   std::string                                                  SLIDING  = "SLIDING";   // search type sliding approach
typedef std::map<std::pair<QueryType, int>, std::set<std::string>>   SearchKmers;            // int is the query ID
typedef std::map<std::pair<int, QueryType>, std::set<long long>>     ResultsMap;             // int is the query ID
typedef std::map<std::pair<int, QueryType>, std::set<size_t>>        ReaIDsMap;              // int is the query ID
typedef std::map<std::pair<int, QueryType>, uint>                    MapOfCounts;            // int is the query ID, uint = count
typedef std::tuple<uint, std::string, std::string, std::string>      Query;                  // query id, ref, alt, crossover
typedef std::map<std::string, std::set<std::pair<int, QueryType>>>   KmerMap;                // kmer, queryID
}

#endif // TYPE_DEFINITION
