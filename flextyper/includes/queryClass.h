#ifndef QUERYCLASS_H
#define QUERYCLASS_H

#include <set>
#include <iostream>
#include <map>
#include "ftPropsClass.h"

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
    std::string _qstring;
    int _count;
    std::map<ft::FlagType, std::set<std::string>> _qFlags;

    ////////////////////////////////////////////////////////////////////////
    /// \brief getters
    ////////////////////////////////////////////////////////////////////////
    int getqID() const;
    QueryType getqType() const;
    std::string getQueryString() const;
    int getCount() const;
    std::map<ft::FlagType, std::set<std::string>> getQFlags() const;
    ft::QIdT getQIdT() const;
    std::set<std::string> getFlagKmers(const ft::FlagType& flag) const;

    ////////////////////////////////////////////////////////////////////////
    /// \brief setters
    ////////////////////////////////////////////////////////////////////////
    void setqID(int qID);
    void setqType(QueryType queryType);
    void setQueryString(std::string queryString);
    void setCount(int count);
    void setFlags(const std::map<ft::FlagType, std::set<std::string>>& qFlags);

    ////////////////////////////////////////////////////////////////////////
    /// \brief adders
    ////////////////////////////////////////////////////////////////////////
    void addFlag(const ft::FlagType& flagType, const std::set<std::string>& kmers);

    ////////////////////////////////////////////////////////////////////////
    /// \brief removers
    ////////////////////////////////////////////////////////////////////////
    void removeFlag(ft::FlagType flagType);
    void removeKmerFlag(const ft::FlagType& flagTyper, const std::string& kmers);
    void removeCount();

    ////////////////////////////////////////////////////////////////////////
    /// \brief checkers
    ////////////////////////////////////////////////////////////////////////
    bool isQIdTEqual(const ft::QIdT& test) const;
    bool hasQueryID(const int& qid) const;
    bool hasQueryType(const ft::QueryType& qType) const;
    bool hasKmerFlag(const ft::FlagType& flag, const std::string& kmer) const;
    bool hasNonZeroCount() const;

    ////////////////////////////////////////////////////////////////////////
    /// \brief overload
    ////////////////////////////////////////////////////////////////////////
    bool operator< (const ft::QueryClass &q) const;
    bool operator== (const ft::QueryClass &q) const;

private:
};
}


#endif // QUERYCLASS_H
