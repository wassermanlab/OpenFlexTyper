#ifndef QKMAPCLASS_H
#define QKMAPCLASS_H

#include <set>
#include <iostream>
#include <unordered_map>
#include <future>
#include <vector>
#include "kmerClass.h"
#include "queryClass.h"

namespace ft {

class QKMap
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// \name QKMapClass
    ////////////////////////////////////////////////////////////////////////
    QKMap();
    virtual ~QKMap();

    std::map<ft::QIdT, std::set<std::string>> _map;
    ////////////////////////////////////////////////////////////////////////
    /// \name map
    /// \brief map between queries and sets of kmers
    ////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////
    /// \name getQKMap
    /// \brief retrieve the qkmap
    /// \return _map
    ////////////////////////////////////////////////////////////////////////
    const std::map<ft::QIdT, std::set<std::string>>& getQKMap();

    ////////////////////////////////////////////////////////////////////////
    /// \section1
    /// \name Access Functions
    /// \brief Access functions for _qkMap
    ////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////
    /// \name retrieveQueries
    /// \brief retrieve queries that map to a specific Kmer
    /// \param kmer
    /// \return set of query Ids
    ////////////////////////////////////////////////////////////////////////
    std::set<ft::QIdT> retrieveQueries(const ft::KmerClass& kmer);
    std::set<std::string> retrieveKmers(const ft::QIdT& queryIDT);
    bool checkForMatch(const ft::QueryClass& query, const ft::KmerClass &kmer) const;
    bool checkForQuery(const ft::QueryClass& query) const;
    void addQKPair(const ft::QIdT& qIDT, const std::string& kmer);

private:

};
}
#endif // QKMAPCLASS_H
