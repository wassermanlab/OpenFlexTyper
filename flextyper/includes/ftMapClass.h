#ifndef __TYPE_DEFS_H__
#define __TYPE_DEFS_H__

#include <set>
#include <iostream>
#include <map>
#include <future>
#include <vector>
#include "stats.h"
#include "kmerClass.h"
#include "queryClass.h"
#include "ftKPropsClass.h"
#include "ftPropsClass.h"
#include "kmergenerator.h"

namespace ft {

typedef std::map<ft::QueryClass, std::set<ft::KmerClass>> QKMAP;

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
    FTProp  _ftProps;
    std::set<ft::KmerClass> _kmerSet;
    std::set<ft::QueryClass> _querySet;
    std::map<ft::QueryClass*, std::set<KmerClass*>> _qkMap;
    std::vector<std::set<ft::KmerClass>> _searchResults;

    ////////////////////////////////////////////////////////////////////////
    /// \brief init
    ////////////////////////////////////////////////////////////////////////
    void addInputQueries(const std::set<Query> &inputQueries);
    void genQKMap(const std::set<ft::QueryClass> &queries);

    ////////////////////////////////////////////////////////////////////////
    /// \brief getters
    ////////////////////////////////////////////////////////////////////////
    const std::set<ft::KmerClass>& getKmerSet();
    const std::set<ft::QueryClass>& getQuerySet();
    const std::map<ft::QueryClass*, std::set<KmerClass*>>& getQKMap();
    const std::vector<std::set<ft::KmerClass>>& getResults();
    const FTProp& getFTProps();

    ////////////////////////////////////////////////////////////////////////
    /// \brief setters
    ////////////////////////////////////////////////////////////////////////
    void setKmers(std::set<ft::KmerClass>);
    void setQueries(std::set<ft::QueryClass>);

    ////////////////////////////////////////////////////////////////////////
    /// \brief Access functions for single kmer and queries
    ////////////////////////////////////////////////////////////////////////
    bool checkForKmer(const std::string &testKmer);
    bool checkForQIDT(ft::QIdT testQueryObject);

    ft::KmerClass* findKmer(const std::string& kmer);
    ft::KmerClass& getKmer(const ft::KmerClass& kmerObject);
    ft::QueryClass* getQuery(ft::QIdT qIDT);

    void addKmer(const ft::KmerClass& kmerObject);

    void addQuery(const ft::QueryClass& queryObject);
    void addQIDtoKmer(std::string kmer, int queryID, ft::QueryType queryType);

    ////////////////////////////////////////////////////////////////////////
    /// \brief Access functions for _qkMap
    ////////////////////////////////////////////////////////////////////////
    std::set<ft::QueryClass*> retrieveQueries(const ft::KmerClass& kmer);
    std::set<ft::KmerClass*> retrieveKmers(ft::QueryClass *query);
    bool checkForMatch(ft::QueryClass *query, const ft::KmerClass &kmer);
    void addQKPair(ft::QueryClass* query, ft::KmerClass* kmer);
    void addQKSet(ft::QueryClass* query, std::set<ft::KmerClass*> kmers);

    ////////////////////////////////////////////////////////////////////////
    /// \brief Adds results from parallel search
    /// All kmer results from a single index
    ////////////////////////////////////////////////////////////////////////
    void addIndexResults(std::set<ft::KmerClass> indexResults);
    void processIndexResults(std::set<ft::KmerClass> indexResults, uint readLength);

private:



};

}

#endif // TYPE_DEFINITION
