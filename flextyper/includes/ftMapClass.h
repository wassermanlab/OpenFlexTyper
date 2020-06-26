#ifndef __TYPE_DEFS_H__
#define __TYPE_DEFS_H__

#include <set>
#include <iostream>
#include <map>
#include <future>
#include <vector>
#include "kmerClass.h"
#include "queryClass.h"
#include "ftKPropsClass.h"
#include "ftPropsClass.h"
#include "kmergenerator.h"


namespace ft {

  // query id, ref, alt, crossover

typedef std::map<ft::QueryClass, std::set<KmerClass>> QKMAP;

class FTMap
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// \brief FTMapClass
    ////////////////////////////////////////////////////////////////////////
    FTMap(FTProp _ftProps);

    ////////////////////////////////////////////////////////////////////////
    /// \brief FTMapClass
    ////////////////////////////////////////////////////////////////////////
    virtual ~FTMap();

    ////////////////////////////////////////////////////////////////////////
    /// \brief properties
    ////////////////////////////////////////////////////////////////////////
    FTProp   _ftProps;
    std::set<ft::KmerClass> _kmerSet;
    std::set<ft::QueryClass> _querySet;
    std::map<ft::QueryClass, std::set<KmerClass>> _qkMap;
    std::vector<std::set<ft::KmerClass>> _searchResults;


    ft::KmerProperties* genKProps();
    ////////////////////////////////////////////////////////////////////////
    /// \brief getters
    ////////////////////////////////////////////////////////////////////////
    std::set<ft::KmerClass> getKmerSet();
    std::set<ft::QueryClass> getQuerySet();
    std::map<ft::QueryClass, std::set<KmerClass>> getQKMap();
    std::vector<std::set<ft::KmerClass>> getResults();
    FTProp getFTProps();

    ////////////////////////////////////////////////////////////////////////
    /// \brief setters
    ////////////////////////////////////////////////////////////////////////
    void setKmers(std::set<ft::KmerClass>);
    void setQueries(std::set<ft::QueryClass>);

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
    /// \brief Access functions for _qkMap
    ////////////////////////////////////////////////////////////////////////
    void addInputQueries(std::set<Query> inputQueries);
    void genQKMap(std::set<ft::QueryClass> queries);
    std::set<ft::QueryClass> retrieveQueries(ft::KmerClass);
    std::set<ft::KmerClass> retrieveKmers(ft::QueryClass);
    bool checkForMatch(ft::KmerClass, ft::QueryClass);
    void addQKPair(ft::QueryClass query, ft::KmerClass kmer);
    void addQKSet(ft::QueryClass query, std::set<ft::KmerClass> kmers);

    ////////////////////////////////////////////////////////////////////////
    /// \brief Adds results from parallel search
    /// All kmer results from a single index
    ////////////////////////////////////////////////////////////////////////
    void addIndexResults(std::set<ft::KmerClass> indexResults);
    void processIndexResults(std::set<ft::KmerClass> indexResults, uint readLength);


private:



};

//typedef std::map<QIdT, std::set<std::string>>                  SearchKmers;            // int is the query ID

//typedef std::pair<std::set<long long>, std::set<FlagType>>     Results;                // set of positions and flags
//typedef std::pair<std::set<size_t>, std::set<FlagType>>                       ResultsFuture;          // set of positions and flags
//typedef std::map<QIdT, Results>                                                 ResultsMap;             // int is the query ID

//typedef std::map<QIdT, std::set<size_t>>                                        ReaIDsMap;              // int is the query ID
//typedef std::map<QIdT, uint>                                                    MapOfCounts;            // int is the query ID, uint = count


}

#endif // TYPE_DEFINITION
