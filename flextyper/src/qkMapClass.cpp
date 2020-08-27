#include <set>
#include <iostream>
#include <unordered_map>
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
    if (_map.count(qID) > 0) {return true;}
    else {return false;}
}


//======================================================
//================= KMERS ==============================
//======================================================
std::set<ft::QIdT> QKMap::retrieveQueries(const ft::KmerClass& kmerClass)
{
    std::set<ft::QIdT> _matchingQueries;
    std::string kmer = kmerClass.getKmer();
     for (auto qk : _map){
         if (qk.second.count(kmer) > 0)
         {
             _matchingQueries.insert(qk.first);
         }
     }
     return _matchingQueries;
}
//=======================================================
std::set<std::string> QKMap::retrieveKmers(const ft::QIdT& queryIDT){
    return _map[queryIDT];
}

//=======================================================
bool QKMap::checkForMatch(const ft::QueryClass& query, const ft::KmerClass& kmer) const
{
    ft::QIdT qIDT = query.getQIdT();
    if (_map.count(qIDT) == 0) //query not in QKMap
    {
        //std::cout << "Cannot find query in QKMap" << std::endl;
        return false;
    } else {
        std::set<std::string> qkmers = _map.find(qIDT)->second;
        std::string testKmer = kmer.getKmer();
        if ( qkmers.find(testKmer) != qkmers.end()) // found match
        {
            return true;
        } else {
            return false; // query doesnt contain that kmer
        }
    }
}

//=======================================================
void QKMap::addQKPair(const ft::QIdT& qIDT, const std::string& kmer){
    if (_map.count(qIDT) > 0){
        //std::cout << " add to existing qIDT" << std::endl;
        _map[qIDT].insert(kmer);
    } else {
        //std::cout << " create new map entry " << std::endl;
         _map[qIDT] = {kmer};
    }
}


//======================================================
QKMap::~QKMap(){}

}
