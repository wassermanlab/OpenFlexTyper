#ifndef __TYPE_DEFS_H__
#define __TYPE_DEFS_H__

#include <set>
#include <iostream>
#include <map>
#include <future>
#include <vector>
#include "kmerClass.h"
#include "queryClass.h"
#include "qkMapClass.h"
#include "ftPropsClass.h"
#include "kmergenerator.h"

namespace ft {

class FTMap
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// \brief FTMapClass
    ////////////////////////////////////////////////////////////////////////
    FTMap(FTProp& _ftProps);

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
    QKMap _qkMap;
    std::vector<std::set<ft::KmerClass>> _searchResults;

    ////////////////////////////////////////////////////////////////////////
    /// \brief init
    ////////////////////////////////////////////////////////////////////////
    void addInputQueries(const std::set<Query> &inputQueries);
    void genQKMap();

    ////////////////////////////////////////////////////////////////////////
    /// \brief getters
    ////////////////////////////////////////////////////////////////////////
    const std::vector<std::set<ft::KmerClass>>& getResults();
    const FTProp& getFTProps();

    ////////////////////////////////////////////////////////////////////////
    /// \brief Access functions for single kmer and queries
    ////////////////////////////////////////////////////////////////////////
    bool checkForKmer(const std::string &testKmer) const;
    ft::KmerClass* findKmer(const std::string& kmer);
    ft::KmerClass& getKmer(const ft::KmerClass& kmerObject);
    void addKmer(const ft::KmerClass& kmerObject);
    void createKmer(const std::string& kmer);

    bool checkForQIDT(const ft::QIdT& testQueryObject) const;
    ft::QueryClass* findQuery(const ft::QIdT& qIDT);
    ft::QueryClass& getQuery(const ft::QIdT& qIDT) const;
    void addQuery(const ft::QueryClass& queryObject);
    void createQuery(int queryID, ft::QueryType queryType);

    ////////////////////////////////////////////////////////////////////////
    /// \brief Adds results from parallel search
    /// All kmer results from a single index
    ////////////////////////////////////////////////////////////////////////
    void addIndexResults(std::set<ft::KmerClass> indexResults);
    void addKmerResults(const ft::KmerClass& kmerResult);
    void processIndexResults(std::set<ft::KmerClass> indexResults);

private:



};

}

#endif // TYPE_DEFINITION
