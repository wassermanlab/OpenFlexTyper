#ifndef QUERYCLASS_H
#define QUERYCLASS_H

#include <set>
#include <iostream>
#include <map>
#include "typedefs.h"


namespace ft {

class QueryClass
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// \brief QueryClass
    ////////////////////////////////////////////////////////////////////////
    QueryClass(int queryID, ft::QueryType queryType);

    ////////////////////////////////////////////////////////////////////////
    /// \brief ~QueryClass
    ////////////////////////////////////////////////////////////////////////
    virtual ~QueryClass();

    ////////////////////////////////////////////////////////////////////////
    /// \brief properties
    ////////////////////////////////////////////////////////////////////////
    int _qID;
    QueryType _qType;
    std::string _string;
    std::set<std::string> _kmers;
    std::set<int> _readIDs;
    int _count;
    std::map<ft::FlagType, std::set<std::string>> _qFlags;

    ////////////////////////////////////////////////////////////////////////
    /// \brief getters
    ////////////////////////////////////////////////////////////////////////
    int getqID();
    QueryType getqType();
    std::string getQueryString();
    std::set<std::string> getKmers();
    std::set<int> getReadIDs();
    int getCount();
    std::map<ft::FlagType, std::set<std::string>> getQFlags();
    ft::QIdT getQIdT();
    std::set<std::string> getFlagKmers(ft::FlagType);

    ////////////////////////////////////////////////////////////////////////
    /// \brief setters
    ////////////////////////////////////////////////////////////////////////
    void setqID(int qID);
    void setqType(QueryType queryType);
    void setQueryString(std::string queryString);
    void setCount(int count);
    void setKmers(std::set<std::string> kmers);
    void setFlags(std::map<ft::FlagType, std::set<std::string>> qFlags);

    ////////////////////////////////////////////////////////////////////////
    /// \brief adders
    ////////////////////////////////////////////////////////////////////////
    void addKmer(std::string kmer);
    void addFlag(ft::FlagType flagType, std::set<std::string> kmers);
    void addReadID(int readID);
    void addReadIDs(std::set<int> readIDs);

    ////////////////////////////////////////////////////////////////////////
    /// \brief removers
    ////////////////////////////////////////////////////////////////////////
    void removeKmer(std::string kmer);
    void removeFlag(ft::FlagType flagType);
    void removeKmerFlag(ft::FlagType flagTyper, std::string kmers);
    void removeReadID(int readID);
    void removeCount();

    ////////////////////////////////////////////////////////////////////////
    /// \brief checkers
    ////////////////////////////////////////////////////////////////////////
    bool isQIdTEqual(ft::QIdT test);
    bool hasQueryID(int qid) const;
    bool hasQueryType(ft::QueryType qType) const;
    bool hasKmer(std::string kmer) ;
    bool hasKmerFlag(ft::FlagType flag, std::string kmer);
    bool hasReadID(int readID) const;
    bool hasNonZeroCount();

    ////////////////////////////////////////////////////////////////////////
    /// \brief overload
    ////////////////////////////////////////////////////////////////////////
    bool operator< (const ft::QueryClass &q) const;

private:
};
}


#endif // QUERYCLASS_H
