#ifndef __TYPE_DEFS_H__
#define __TYPE_DEFS_H__

#include <set>
#include <iostream>
#include <map>
#include <future>

#include "kmerClass.h"
#include "queryClass.h"


namespace ft {

typedef std::string     SearchType;             // SearchType declaration
const   std::string     CENTERED = "CENTERED";  // search type centered approach
const   std::string     SLIDING  = "SLIDING";   // search type sliding approach
typedef std::tuple<uint, std::string, std::string, std::string>         Query;    // query id, ref, alt, crossover
typedef std::map<ft::QueryClass, std::set<KmerClass>> Results;


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
    std::set<std::set<ft::KmerClass>> _resultsMap;

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
    uint _readLen;



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
    std::set<std::set<ft::KmerClass>> getResultsMap();
    uint getKmerSize();
    SearchType getSearchType();
    uint getOverlap();
    uint getStride();
    uint getMaxKmers();
    uint getMaxTotalKmers();
    uint getMaxOcc();
    uint getReadLength();

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
    void setReadLength(uint readlength);

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

    ////////////////////////////////////////////////////////////////////////
    /// \brief Adds results from parallel search
    /// All kmer results from a single index
    ////////////////////////////////////////////////////////////////////////
    void addIndexResults(std::set<ft::KmerClass> indexResults);


    void processIndexResults(std::set<ft::KmerClass> indexResults, uint readLength);

};

//typedef std::map<QIdT, std::set<std::string>>                                   SearchKmers;            // int is the query ID

//typedef std::pair<std::set<long long>, std::set<FlagType>>        Results;                // set of positions and flags
//typedef std::pair<std::set<size_t>, std::set<FlagType>>           ResultsFuture;          // set of positions and flags
//typedef std::map<QIdT, Results>                                                 ResultsMap;             // int is the query ID

//typedef std::map<QIdT, std::set<size_t>>                                        ReaIDsMap;              // int is the query ID
//typedef std::map<QIdT, uint>                                                    MapOfCounts;            // int is the query ID, uint = count


}

#endif // TYPE_DEFINITION
