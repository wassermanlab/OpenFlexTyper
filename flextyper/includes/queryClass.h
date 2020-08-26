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
    QueryClass();

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
    const std::set<std::string> getFlagKmers(const ft::FlagType flag) const;

    ////////////////////////////////////////////////////////////////////////
    /// \brief setters
    ////////////////////////////////////////////////////////////////////////
    void setQueryString(std::string queryString);
    void setCount(int count);
    void setFlags(const std::map<ft::FlagType, std::set<std::string>>& qFlags);

    ////////////////////////////////////////////////////////////////////////
    /// \brief adders
    ////////////////////////////////////////////////////////////////////////
    void addFlags(const ft::FlagType& flagType, const std::set<std::string>& kmers);
    void addFlag(const ft::FlagType& flagType, const std::string& kmer);

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
    bool hasFlag(const ft::FlagType& flag) const;
    bool hasKmerFlag(const ft::FlagType& flag, const std::string& kmer) const;
    bool hasNonZeroCount() const;

    ////////////////////////////////////////////////////////////////////////
    /// \brief overload
    ////////////////////////////////////////////////////////////////////////
    bool operator< (const ft::QueryClass &q) const;
    bool operator== (const ft::QueryClass &q) const;

    static const std::string& queryTypeToString (const ft::QueryType& qType) {
        switch (qType) {
        case REF:
           return QUERYTYPE_REF;
        case ALT:
           return QUERYTYPE_ALT;
        case CRO:
        default:
           return QUERYTYPE_CRO;
        }
    };


private:
};
}


#endif // QUERYCLASS_H
