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


    bool isQIdTEqual(ft::QIdT test);

    std::set<std::string> getFlagKmers(ft::FlagType);

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

    bool operator< (const ft::QueryClass &q);

private:
};
}


#endif // QUERYCLASS_H
