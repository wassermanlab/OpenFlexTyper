////////////////////////////////////////////////////////////////////////
/// \copyright Copyright (c) 2020, Wasserman lab
////////////////////////////////////////////////////////////////////////

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
    /// \brief QKMapClass
    ////////////////////////////////////////////////////////////////////////
    QKMap();
    virtual ~QKMap();
    std::map<ft::QIdT, std::set<std::string>> _map;

    ////////////////////////////////////////////////////////////////////////
    /// \skip
    ////////////////////////////////////////////////////////////////////////
    const std::map<ft::QIdT, std::set<std::string>>& getQKMap();

    ////////////////////////////////////////////////////////////////////////
    /// \section
    /// \brief Access functions for _qkMap
    ////////////////////////////////////////////////////////////////////////
    ///
    /// \fn retrieveQueries
    ///
    std::set<ft::QIdT> retrieveQueries(const ft::KmerClass& kmer);
    ///
    /// \fn retrieveKmers
    ///
    std::set<std::string> retrieveKmers(const ft::QIdT& queryIDT); /// \fn
    bool checkForMatch(const ft::QueryClass& query, const ft::KmerClass &kmer) const; /// \fn
    bool checkForQuery(const ft::QueryClass& query) const; /// \fn
    void addQKPair(const ft::QIdT& qIDT, const std::string& kmer); /// \fn

private:

};
}
#endif // QKMAPCLASS_H
