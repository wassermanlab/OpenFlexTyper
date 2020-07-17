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
    const std::set<ft::KmerClass>& getKmerSet();
    const std::set<ft::QueryClass>& getQuerySet();
    const QKMap& getQKMap();
    const std::vector<std::set<ft::KmerClass>>& getResults();
    const FTProp& getFTProps();

    ////////////////////////////////////////////////////////////////////////
    /// \brief setters
    ////////////////////////////////////////////////////////////////////////
    void setKmers(std::set<ft::KmerClass>);
    void setQueries(std::set<ft::QueryClass>);

    ////////////////////////////////////////////////////////////////////////
    /// \brief Access functions for single kmer and queries
    ////////////////////////////////////////////////////////////////////////
    bool checkForKmer(const std::string &testKmer) const;
    ft::KmerClass* findKmer(const std::string& kmer);
    ft::KmerClass& getKmer(const ft::KmerClass& kmerObject);
    void addKmer(const ft::KmerClass& kmerObject);

    bool checkForQIDT(const ft::QIdT& testQueryObject) const;
    ft::QueryClass* findQuery(const ft::QIdT& qIDT);
    ft::QueryClass& getQuery(const ft::QIdT& qIDT) const;
    void addQuery(const ft::QueryClass& queryObject);

    ////////////////////////////////////////////////////////////////////////
    /// \brief Adds results from parallel search
    /// All kmer results from a single index
    ////////////////////////////////////////////////////////////////////////
    void addIndexResults(std::set<ft::KmerClass> indexResults);
    void addKmerResults(const ft::KmerClass& kmerResult);
    void processIndexResults(std::set<ft::KmerClass> indexResults);

#define PROPSSTART {
    ////////////////////////////////////////////////////////////////////////
    /// \brief Properties getters
    ////////////////////////////////////////////////////////////////////////
    SearchType getSearchType() const;
    std::string getReadSetName()const ;
    uint getKmerSize() const;
    uint getOverlap() const;
    uint getStride() const;
    uint getMaxKmers() const;
    uint getReadLength() const;
    uint getMaxOcc() const;
    uint getMaxThreads() const;
    uint getMaxKmersPerQuery() const;
    uint getMaxTotalKmers() const;
    uint getNumOfIndexes() const;
    uint getNumOfReads() const;
    bool getKmerCountsFlag() const;
    bool getMultithreadFlag() const;
    bool getRefOnlyFlag() const;
    bool getMatchesOnlyFlag() const;
    bool getOverCountedFlag() const;
    bool getIgnoreNonUniqueKmersFlag() const;
    bool getCrossoverFlag() const;
    bool getPrintSearchTimeFlag() const;
    bool getPairedReadFlag() const;
    bool getRevCompFlag() const;
    bool getMatchingReadsFlag() const;
    const fs::path& getPathToQueryFile() const;
    const fs::path& getIndexDir() const;
    const fs::path& getOutputFolder() const;
    const fs::path& getMatchingReadFQ() const;
    const fs::path& getInputFastQ() const;
    const fs::path& getOutputFile() const;
    const std::map<fs::path, uint>& getIndexSet() const;
    const fs::path& getBuildDir() const;
    const fs::path& getR1() const;
    const fs::path& getR2() const;
#define PROPSEND }
#define QKMAPSTART {
    std::set<ft::QueryClass*> retrieveQueriesFromMap(const ft::KmerClass& kmer);
    std::set<ft::KmerClass*> retrieveKmersFromMap(ft::QueryClass *query);
    bool checkMapForMatch(const ft::QueryClass& query, const ft::KmerClass &kmer) const;
    void addQKPairToMap(ft::QueryClass* query, ft::KmerClass* kmer);
    void addQKSetToMap(ft::QueryClass* query, std::set<ft::KmerClass*> kmers);

#define QKMAPEND }
private:



};

}

#endif // TYPE_DEFINITION
