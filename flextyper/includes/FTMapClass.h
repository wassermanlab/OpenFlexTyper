#ifndef __TYPE_DEFS_H__
#define __TYPE_DEFS_H__

#include <set>
#include <iostream>
#include <map>
#include "kmerClass.h"
#include "queryClass.h"
#include "resultsClass.h"

namespace ft {

typedef std::string     SearchType;             // SearchType declaration
const   std::string     CENTERED = "CENTERED";  // search type centered approach
const   std::string     SLIDING  = "SLIDING";   // search type sliding approach
typedef std::tuple<uint, std::string, std::string, std::string>         Query;    // query id, ref, alt, crossover



class FTMap
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// \brief FTMapClass
    ////////////////////////////////////////////////////////////////////////
    FTMap();

    ////////////////////////////////////////////////////////////////////////
    /// \brief FTMapClass
    ////////////////////////////////////////////////////////////////////////
    virtual ~FTMap();

    ////////////////////////////////////////////////////////////////////////
    /// \brief properties
    ////////////////////////////////////////////////////////////////////////
    std::set<ft::KmerClass> _kmerMap;
    std::set<ft::QueryClass> _queryMap;
    std::map<ft::QueryClass, std::set<KmerClass>> _results;
    uint _kmerSize;
    bool _refOnly;
    SearchType _searchType;
    uint _overlap;
    uint _stride;
    bool _crossover;
    bool _ignoreNonUniqueKmers;
    bool _kmerCounts;
    uint _maxKmers;
    uint _maxTotalKmers;
    uint _maxOcc;
    bool _overcounted;



    ////////////////////////////////////////////////////////////////////////
    /// \brief set properties
    ////////////////////////////////////////////////////////////////////////
    void setProperties(uint _kmerSize,
                            bool _refOnly,
                            SearchType _searchType,
                            uint _overlap,
                            uint _stride,
                            bool _crossover,
                            bool _ignoreNonUniqueKmers,
                            bool _kmerCounts,
                            uint _maxKmers,
                            uint _maxTotalKmers);



    ////////////////////////////////////////////////////////////////////////
    /// \brief getters
    ////////////////////////////////////////////////////////////////////////
    std::set<ft::KmerClass> getKmerMap();
    std::set<ft::QueryClass> getQueryMap();
    std::map<ft::QueryClass, std::set<KmerClass>> getResultsMap();
    uint getKmerSize();
    SearchType getSearchType();
    uint getOverlap();
    uint getStride();
    uint getMaxKmers();
    uint getMaxTotalKmers();
    uint getMaxOcc();

    ////////////////////////////////////////////////////////////////////////
    /// \brief getters
    ////////////////////////////////////////////////////////////////////////
    void setKmers(std::set<ft::KmerClass>);
    void setQueries(std::set<ft::QueryClass>);
    void setKmerSize(uint kmerSize);
    void setSearchType(ft::SearchType searchType);
    void setOverlap(uint overlap);
    void setStride(uint stride);
    void setMaxKmers(uint maxKmers);
    void setMaxTotalKmers(uint maxTotalKmers);
    void setMaxOcc(uint maxOcc);

    ////////////////////////////////////////////////////////////////////////
    /// \brief Flags
    ////////////////////////////////////////////////////////////////////////
    bool getRefOnlyFlag();
    bool getIgnoreNonUniqueKmersFlag();
    bool getKmerCountsFlag();
    bool getCrossoverFlag();
    bool getOverCountedFlag();

    void setRefOnlyFlag(bool refOnly);
    void setIgnoreNonUniqueKmersFlag(bool ignoreNonUnique);
    void setKmerCountsFlag(bool kmerCounts);
    void setCrossoverFlag(bool crossover);
    void setOverCountedFlag(bool overcounted);

    ////////////////////////////////////////////////////////////////////////
    /// \brief Access functions for single kmer and queries
    ////////////////////////////////////////////////////////////////////////
    ft::KmerClass getKmer(std::string kmer);
    ft::QueryClass getQuery(ft::QIdT qIDT);

    void addKmer(ft::KmerClass kmer);
    void addQuery(ft::QueryClass query);

    void addQIDtoKmer(std::string kmer, int queryID, ft::QueryType queryIDType);
    void addResultsFuture(ft::FTResults tmpResults, uint offset);

    void addResults(std::map<ft::QueryClass, std::set<KmerClass>> tmpResults);
};

//typedef std::map<QIdT, std::set<std::string>>                                   SearchKmers;            // int is the query ID

//typedef std::pair<std::set<long long>, std::set<FlagType>>        Results;                // set of positions and flags
//typedef std::pair<std::set<size_t>, std::set<FlagType>>           ResultsFuture;          // set of positions and flags
//typedef std::map<QIdT, Results>                                                 ResultsMap;             // int is the query ID

//typedef std::map<QIdT, std::set<size_t>>                                        ReaIDsMap;              // int is the query ID
//typedef std::map<QIdT, uint>                                                    MapOfCounts;            // int is the query ID, uint = count


}

#endif // TYPE_DEFINITION
