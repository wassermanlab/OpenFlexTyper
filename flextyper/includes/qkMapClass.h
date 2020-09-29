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

    ////////////////////////////////////////////////////////////////////////
    /// \brief properties
    ////////////////////////////////////////////////////////////////////////
    std::map<ft::QIdT, std::set<std::string>> _map;

    ////////////////////////////////////////////////////////////////////////
    /// \brief getters
    ////////////////////////////////////////////////////////////////////////
    const std::map<ft::QIdT, std::set<std::string>>& getQKMap();

    ////////////////////////////////////////////////////////////////////////
    /// \brief Access functions for _qkMap
    ////////////////////////////////////////////////////////////////////////
    std::set<ft::QIdT> retrieveQueries(const ft::KmerClass& kmer);
    const std::set<std::string>& retrieveKmers(const ft::QIdT& queryIDT);
    bool checkForMatch(const ft::QueryClass& query, const ft::KmerClass &kmer) const;
    bool checkForQuery(const ft::QueryClass& query) const;
    void addQKPair(const ft::QIdT& qIDT, const std::string& kmer);

private:


};
}
#endif // QKMAPCLASS_H
