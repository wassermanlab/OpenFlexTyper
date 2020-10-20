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

////////////////////////////////////////////////////////////////////////
/// \class QKMap
/// \brief A class that contains the map between queries and kmers
////////////////////////////////////////////////////////////////////////

class QKMap
{
public:
    /// Constructor
    QKMap();
    /// Destructor
    virtual ~QKMap();

    /// \property _map
    /// map between queries and sets of kmers
    std::map<ft::QIdT, std::set<std::string>> _map;

    /// \fn getQKMap
    /// \brief retrieve the qkmap
    /// \return _map
    const std::map<ft::QIdT, std::set<std::string>>& getQKMap();

    /// \section Access Functions
    /// \brief Access functions for _qkMap

    /// \fn retrieveQueries
    /// \brief retrieve queries that map to a specific Kmer
    /// \param ft::KmerClass kmer
    /// \return set of query Ids
    std::set<ft::QIdT> retrieveQueries(const ft::KmerClass& kmer);
    /// \fn retrieveKmers
    /// \brief retrieve kmers that map to a specific query ID and type
    /// \param ft::QIdT
    /// \return set of kmer strings
    std::set<std::string> retrieveKmers(const ft::QIdT& queryIDT);
    /// \fn checkForMatch
    /// \brief see if a query contains a kmer
    /// \param ft::KmerClass kmer
    /// \param ft::QueryClass query
    bool checkForMatch(const ft::QueryClass& query, const ft::KmerClass &kmer) const;
    /// \fn checkForQuery
    /// \brief see if a query is in the qkMap
    /// \param ft::QueryClass query
    bool checkForQuery(const ft::QueryClass& query) const;
    /// \fn addQKPair
    /// \brief add a query ID, Type and Kmer pair to the QKMap
    /// \param ft::KmerClass kmer
    /// \param ft::QIdT (query ID, query Type)
    void addQKPair(const ft::QIdT& qIDT, const std::string& kmer);

private:

};
}
#endif // QKMAPCLASS_H
