#ifndef __TYPE_DEFS_H__
#define __TYPE_DEFS_H__

#include <set>
#include <iostream>
#include <map>

namespace ft {

enum QueryType {
    REF = 1, ALT, CRO
};
enum FlagType {
    ABK = 1, OCK, NUK // abundant, overcounted, non-unique
};

typedef std::string                                                 SearchType;             // SearchType declaration
const   std::string                                                 CENTERED = "CENTERED";  // search type centered approach
const   std::string                                                 SLIDING  = "SLIDING";   // search type sliding approach

typedef std::pair<int, QueryType>                                               QIdT; // int is the query ID

typedef std::map<QIdT, std::set<std::string>>                                   SearchKmers;            // int is the query ID

typedef std::pair<std::set< long long>, std::set<FlagType>>                     Results;                // set of positions and flags
typedef std::pair<std::set<size_t>, std::set<FlagType>>                         ResultsFuture;          // set of positions and flags
typedef std::map<QIdT, Results>                                                 ResultsMap;             // int is the query ID

typedef std::map<QIdT, std::set<size_t>>                                        ReaIDsMap;              // int is the query ID
typedef std::map<QIdT, uint>                                                    MapOfCounts;            // int is the query ID, uint = count
typedef std::tuple<uint, std::string, std::string, std::string>                 Query;                  // query id, ref, alt, crossover
typedef std::map<std::string, std::pair<std::set<QIdT>, std::set<FlagType>>>    KmerMap;                // kmer, queryID
typedef std::map<QIdT, std::set<std::string>>                                   QueryKmers;             // <query id, query type>, set kmers
}

#endif // TYPE_DEFINITION
