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

////////////////////////////////////////////////////////////////////////
/// \class FTMapClass
/// \brief A class that contains information for the FlexTyper Instance.
////////////////////////////////////////////////////////////////////////
class FTMap
{
public:
    /// Constructor
    /// \param FTProp  FlexTyper Properties for this instance
    FTMap(const FTProp& _ftProps);
    /// Class Destructor
    virtual ~FTMap();

    /// @name init
    /// Functions to set up the FTMap
    /// @{
    /// \fn
    /// \public
    void addInputQueries(const std::set<Query> &inputQueries);
    void genQKMap();
    /// @}


    /// @name Getters
    /// Constant functions to return properties of the query
    /// @{
    /// \public
    /// \fn
    const std::vector<std::map<std::string, ft::KmerClass>>& getResults();
    const FTProp& getFTProps() const;
    const std::unordered_map<std::string, ft::KmerClass>& getKmerSet() const;
    /// @}

    /// \name Access
    /// Access functions for single kmer and queries
    /// @{
    /// \publicsection
    bool checkForKmer(const std::string& testKmer) const;
    void addKmer(const std::string &kmer);
    const ft::KmerClass& getKmer(const std::string& kmer) const;

    bool checkForQIDT(const ft::QIdT& testQueryObject) const;
    void addQuery(int queryID, ft::QueryType queryType, const std::string& queryString);
    const ft::QueryClass& getQuery(const ft::QIdT& qIDT) const;
    /// @}

    /// \name Results
    /// Functions to process the results of a search
    /// @{
    void addIndexResults(const std::map<std::string, ft::KmerClass> & indexResults);
    void addKmerResults(const ft::KmerClass& kmerResult);
    void processResults();
    void processIndexResults(const std::map<std::string, ft::KmerClass>& indexResults);
    void processQueryResults(const ft::QIdT& qIDT);
    std::set<ft::ReadID> addKmersToQueryResults(ft::QueryClass& query, std::set<std::string> kmers,  std::set<ft::ReadID> readIds);
    int calculateQueryCount(std::set<ft::ReadID> readIds);\
    /// @}

private:
    /// @name Properties
    /// @{
    /// \private
    /// \variable
    FTProp  _ftProps;
    std::unordered_map<std::string, ft::KmerClass> _kmerSet;
    std::map<ft::QIdT, ft::QueryClass> _querySet;
    QKMap _qkMap;
    QKMap _qkRCMap;
    std::vector<std::map<std::string, ft::KmerClass>> _searchResults;
    /// @}


    void createKmer(const std::string& kmer);
    ft::KmerClass* findKmer(const std::string& kmer);

    bool operator()(const ft::QIdT& a, const ft::QIdT& b) const;
};

}

#endif // TYPE_DEFINITION
