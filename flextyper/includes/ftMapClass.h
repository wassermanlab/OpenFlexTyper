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
#include "utils.h"
#include <unordered_map>

namespace ft {

class FTMap
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// \brief FTMapClass
    ////////////////////////////////////////////////////////////////////////
    FTMap(const FTProp& _ftProps);

    ////////////////////////////////////////////////////////////////////////
    /// \brief FTMapClass
    ////////////////////////////////////////////////////////////////////////
    virtual ~FTMap();

    ////////////////////////////////////////////////////////////////////////
    /// \brief properties
    ////////////////////////////////////////////////////////////////////////
    FTProp  _ftProps;
    std::unordered_map<ft::Kmer, ft::KmerClass> _kmerSet;
    std::map<ft::QIdT, ft::QueryClass> _querySet;
    QKMap _qkMap;
    QKMap _qkRCMap;
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
    bool checkForKmer(const ft::Kmer& testKmer) const;
    const ft::KmerClass& getKmer(const ft::Kmer& kmer) const;

    bool checkForQIDT(const ft::QIdT& testQueryObject) const;
    const ft::QueryClass& getQuery(const ft::QIdT& qIDT) const;

    ////////////////////////////////////////////////////////////////////////
    /// \brief Adds results from parallel search
    /// All kmer results from a single index
    ////////////////////////////////////////////////////////////////////////
    void addIndexResults(std::set<ft::KmerClass> indexResults);
    void addKmerResults(const ft::KmerClass& kmerResult);
    void processResults();
    void processIndexResults(std::set<ft::KmerClass> indexResults);
    void processQueryResults(const ft::QIdT& query);



private:
    void createKmer(const std::string& kmer);
    ft::KmerClass* findKmer(const ft::Kmer& kmer);

    void createQuery(int queryID, ft::QueryType queryType);
    void addNewQuery(int queryID, ft::QueryType queryType, std::string queryString);
    ft::QueryClass* findQuery(const ft::QIdT& qIDT);

};

}

#endif // TYPE_DEFINITION
