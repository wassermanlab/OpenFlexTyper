#ifndef __TYPE_DEFS_H__
#define __TYPE_DEFS_H__

#include <set>
#include <iostream>
#include <map>
#include <future>
#include <vector>
#include "kmerClass.h"
#include "queryClass.h"


namespace ft {

typedef std::string     SearchType;             // SearchType declaration
const   std::string     CENTERED = "CENTERED";  // search type centered approach
const   std::string     SLIDING  = "SLIDING";   // search type sliding approach
typedef std::tuple<uint, std::string, std::string, std::string>  Query;    // query id, ref, alt, crossover

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
    std::set<ft::KmerClass> _kmerSet;
    std::set<ft::QueryClass> _querySet;
    std::map<ft::QueryClass, std::set<KmerClass>> _qkMap;
    std::vector<std::set<ft::KmerClass>> _searchResults;

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
    bool _matchesOnly;

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
                        uint _maxTotalKmers,
                       bool _returnMatchesOnly);

    ////////////////////////////////////////////////////////////////////////
    /// \brief getters
    ////////////////////////////////////////////////////////////////////////
    std::set<ft::KmerClass> getKmerSet();
    std::set<ft::QueryClass> getQuerySet();
    std::map<ft::QueryClass, std::set<KmerClass>> getQKMap();
    std::vector<std::set<ft::KmerClass>> getResults();
    SearchType getSearchType();
    uint getKmerSize();

    uint getOverlap();
    uint getStride();
    uint getMaxKmers();
    uint getMaxTotalKmers();
    uint getMaxOcc();
    uint getReadLength();

    ////////////////////////////////////////////////////////////////////////
    /// \brief setters
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
    /// \brief Flag getters and setters
    ////////////////////////////////////////////////////////////////////////
    bool getRefOnlyFlag();
    bool getIgnoreNonUniqueKmersFlag();
    bool getKmerCountsFlag();
    bool getCrossoverFlag();
    bool getOverCountedFlag();
    bool getMatchesOnlyFlag();

    void setRefOnlyFlag(bool refOnly);
    void setIgnoreNonUniqueKmersFlag(bool ignoreNonUnique);
    void setKmerCountsFlag(bool kmerCounts);
    void setCrossoverFlag(bool crossover);
    void setOverCountedFlag(bool overcounted);
    void setMatchesOnlyFlag(bool matchesOnly);

    ////////////////////////////////////////////////////////////////////////
    /// \brief Access functions for single kmer and queries
    ////////////////////////////////////////////////////////////////////////
    bool checkForKmer(ft::KmerClass testKmerObject);
    bool checkForQIDT(ft::QIdT testQueryObject);

    ft::KmerClass findKmer(std::string kmer);
    ft::KmerClass getKmer(ft::KmerClass kmerObject);
    ft::QueryClass getQuery(ft::QIdT qIDT);

    void addKmer(ft::KmerClass kmerObject);
    void addQuery(ft::QueryClass queryObject);

    void addQIDtoKmer(std::string kmer, int queryID, ft::QueryType queryType);

    ////////////////////////////////////////////////////////////////////////
    /// \brief Adds results from parallel search
    /// All kmer results from a single index
    ////////////////////////////////////////////////////////////////////////
    void addIndexResults(std::set<ft::KmerClass> indexResults);
    void processIndexResults(std::set<ft::KmerClass> indexResults, uint readLength);

};

//typedef std::map<QIdT, std::set<std::string>>                  SearchKmers;            // int is the query ID

//typedef std::pair<std::set<long long>, std::set<FlagType>>     Results;                // set of positions and flags
//typedef std::pair<std::set<size_t>, std::set<FlagType>>                       ResultsFuture;          // set of positions and flags
//typedef std::map<QIdT, Results>                                                 ResultsMap;             // int is the query ID

//typedef std::map<QIdT, std::set<size_t>>                                        ReaIDsMap;              // int is the query ID
//typedef std::map<QIdT, uint>                                                    MapOfCounts;            // int is the query ID, uint = count


}

#endif // TYPE_DEFINITION
