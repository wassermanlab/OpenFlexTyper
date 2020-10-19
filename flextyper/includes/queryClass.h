#ifndef QUERYCLASS_H
#define QUERYCLASS_H

#include <set>
#include <iostream>
#include <map>
#include "ftPropsClass.h"

namespace ft {

////////////////////////////////////////////////////////////////////////
/// \class QueryClass
/// \brief A class that contains information for one query ID, Type pair
////////////////////////////////////////////////////////////////////////


class QueryClass
{

public:
    /// Constructor
    /// \param int  query ID as an integer
    /// \param ft::QueryType    query type {REF, ALT, CRO}
    QueryClass(int queryID, ft::QueryType queryType);
    QueryClass();

    /// Class Destructor
    virtual ~QueryClass();

    /// @name Properties
    /// @{
    /// \public
    /// \var
    int _qID;
    QueryType _qType;
    std::string _qstring;
    int _count;
    std::map<ft::FlagType, std::set<std::string>> _qFlags;
    /// @}

    /// @name Getters
    /// Constant functions to return properties of the query
    /// @{
    /// \public
    /// \fn
    int getqID() const;
    QueryType getqType() const;
    std::string getQueryString() const;
    int getCount() const;
    std::map<ft::FlagType, std::set<std::string>> getQFlags() const;
    ft::QIdT getQIdT() const;
    const std::set<std::string> getFlagKmers(const ft::FlagType flag) const;
    /// @}

    /// \name Setters
    /// Non-constant functions to update properties of the query class
    /// @{
    /// \publicsection
    void setQueryString(std::string queryString);
    void setCount(int count);
    void setFlags(const std::map<ft::FlagType, std::set<std::string>>& qFlags);
    /// @}

    /// \name Adders
    /// Non-constant functions to add properties to the query class
    /// @{
    void addFlags(const ft::FlagType& flagType, const std::set<std::string>& kmers);
    void addFlag(const ft::FlagType& flagType, const std::string& kmer);
    /// @}

    /// \name Removers
    /// Non-constant functions to remove properties from the query class
    /// @{
    void removeFlag(ft::FlagType flagType);
    void removeKmerFlag(const ft::FlagType& flagTyper, const std::string& kmers);
    void removeCount();
    /// @}

    /// \name Checkers
    /// Constant functions to check the properties of the query class
    /// @{
    bool isQIdTEqual(const ft::QIdT& test) const;
    bool hasQueryID(const int& qid) const;
    bool hasQueryType(const ft::QueryType& qType) const;
    bool hasFlag(const ft::FlagType& flag) const;
    bool hasKmerFlag(const ft::FlagType& flag, const std::string& kmer) const;
    bool hasNonZeroCount() const;
    /// @}

    /// \name Overloaded Operators
    /// \brief Constant functions that define how to compare two query classes for equality
    /// @{
    bool operator< (const ft::QueryClass &q) const;
    bool operator== (const ft::QueryClass &q) const;
    /// @}

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


};
}

#endif // QUERYCLASS_H
