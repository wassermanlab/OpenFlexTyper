#ifndef __TYPE_DEFS_H__
#define __TYPE_DEFS_H__

#include <set>
#include <iostream>
#include <map>
#include "kmerClass.h"
#include "queryClass.h"

namespace ft {

typedef std::string     SearchType;             // SearchType declaration
const   std::string     CENTERED = "CENTERED";  // search type centered approach
const   std::string     SLIDING  = "SLIDING";   // search type sliding approach
typedef std::tuple<uint, std::string, std::string, std::string>         Query;    // query id, ref, alt, crossover


class FTMap
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// \brief KmerClass
    ////////////////////////////////////////////////////////////////////////
    FTMap();

    ////////////////////////////////////////////////////////////////////////
    /// \brief KmerClass
    ////////////////////////////////////////////////////////////////////////
    virtual ~FTMap();

    ////////////////////////////////////////////////////////////////////////
    /// \brief properties
    ////////////////////////////////////////////////////////////////////////
    std::set<ft::KmerClass> _kmerMap;
    std::set<ft::QueryClass> _queryMap;

    ////////////////////////////////////////////////////////////////////////
    /// \brief getters
    ////////////////////////////////////////////////////////////////////////
    ft::KmerClass getKmer(std::string kmer);
    ft::QueryClass getQuery(ft::QIdT qIDT);

    ////////////////////////////////////////////////////////////////////////
    /// \brief getters
    ////////////////////////////////////////////////////////////////////////
    void addKmer(ft::KmerClass kmer);
    void addQuery(ft::QueryClass query);



};

//typedef std::map<QIdT, std::set<std::string>>                                   SearchKmers;            // int is the query ID

//typedef std::pair<std::set<long long>, std::set<FlagType>>        Results;                // set of positions and flags
//typedef std::pair<std::set<size_t>, std::set<FlagType>>           ResultsFuture;          // set of positions and flags
//typedef std::map<QIdT, Results>                                                 ResultsMap;             // int is the query ID

//typedef std::map<QIdT, std::set<size_t>>                                        ReaIDsMap;              // int is the query ID
//typedef std::map<QIdT, uint>                                                    MapOfCounts;            // int is the query ID, uint = count


}

#endif // TYPE_DEFINITION
