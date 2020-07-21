#ifndef QKMAPCLASS_H
#define QKMAPCLASS_H

#include <set>
#include <iostream>
#include <map>
#include <future>
#include <vector>
#include "kmerClass.h"
#include "queryClass.h"


namespace ft {

class QKMap
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// \brief QKMapClass
    ////////////////////////////////////////////////////////////////////////
    QKMap();
    virtual ~QKMap();

    ////////////////////////////////////////////////////////////////////////
    /// \brief properties
    ////////////////////////////////////////////////////////////////////////
    std::map<ft::QueryClass*, std::set<KmerClass*>> _map;


    ////////////////////////////////////////////////////////////////////////
    /// \brief getters
    ////////////////////////////////////////////////////////////////////////
    const std::map<ft::QueryClass*, std::set<KmerClass*>>& getQKMap();

    bool checkForQuery(const ft::QueryClass& query) const;
    ft::QueryClass* getQueryPointer(const ft::QueryClass& query);


    ////////////////////////////////////////////////////////////////////////
    /// \brief Access functions for _qkMap
    ////////////////////////////////////////////////////////////////////////
    std::set<ft::QueryClass*> retrieveQueries(const ft::KmerClass& kmer);
    std::set<ft::KmerClass*> retrieveKmers(ft::QueryClass *query);
    bool checkForMatch(const ft::QueryClass& query, const ft::KmerClass &kmer) const;
    void addQKPair(ft::QueryClass* query, ft::KmerClass* kmer);
    void addQKSet(ft::QueryClass* query, std::set<ft::KmerClass*> kmers);






};
}
#endif // QKMAPCLASS_H
