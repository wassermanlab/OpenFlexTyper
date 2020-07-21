#include <set>
#include <iostream>
#include <map>
#include <algorithm>
#include "qkMapClass.h"

namespace ft {

QKMap::QKMap()
{
}


//======================================================
//================= QUERIES ============================
//======================================================
bool QKMap::checkForQuery(const ft::QueryClass& query) const
{
    ft::QIdT qID = query.getQIdT();
    auto it = std::find_if(std::begin(_map), std::end(_map),
        [&] (std::pair<ft::QueryClass* const, std::set<ft::KmerClass*>> q) {return q.first->isQIdTEqual(qID);});
    if (it != _map.end()) {return true;}
    else {return false;}
}


ft::QueryClass* QKMap::getQueryPointer(const ft::QueryClass& query)
{
    ft::QIdT qID = query.getQIdT();
    auto it = std::find_if(std::begin(_map), std::end(_map),
        [&] (std::pair<ft::QueryClass* const, std::set<ft::KmerClass*>> q) {return q.first->isQIdTEqual(qID);});
    if (it != _map.end())
    {
        return (ft::QueryClass *) &(*it->first);
    } else {
        return NULL;
    }
}

//======================================================
//================= KMERS ==============================
//======================================================


std::set<ft::QueryClass*> QKMap::retrieveQueries(const ft::KmerClass& kmer)
{
    std::set<ft::QueryClass*> _matchingQueries;
     for (auto qk : _map){
         auto it = std::find_if(std::begin(qk.second), std::end(qk.second),
             [&] (const ft::KmerClass* k) {return k->isKmerEqual(kmer);});
         if (it != qk.second.end()) {_matchingQueries.insert(qk.first);}
     }
     return _matchingQueries;
}
//=======================================================
std::set<ft::KmerClass*> QKMap::retrieveKmers(ft::QueryClass* query){
    return _map[query];
}

//=======================================================
bool QKMap::checkForMatch(const ft::QueryClass& query, const ft::KmerClass& kmer) const
{
    if (!checkForQuery(query)) //query not in QKMap
    {
        std::cout << "Cannot find query in QKMap" << std::endl;
        return false;
    } else {
        ft::QIdT qID = query.getQIdT();
        auto it = std::find_if(std::begin(_map), std::end(_map),
            [&] (std::pair<ft::QueryClass* const, std::set<ft::KmerClass*>> q) {return q.first->isQIdTEqual(qID);});

        auto it2 = std::find_if(std::begin(it->second), std::end(it->second),
            [&] (const ft::KmerClass* k) {return k->isKmerEqual(kmer);});
        if (it2 != it->second.end()) // found match
        {
            return true;
        } else {
            return false; // query doesnt contain that kmer
        }
    }


}

//=======================================================
void QKMap::addQKPair(ft::QueryClass* query, ft::KmerClass* kmer){
    if (! checkForMatch(*query, *kmer)){
        _map[query].insert(kmer);
    }
}
//=======================================================
void QKMap::addQKSet(ft::QueryClass* query, std::set<ft::KmerClass*> kmers){
    for (auto kmer: kmers){
        addQKPair(query, kmer);
        }
}

//======================================================
QKMap::~QKMap(){}

}
