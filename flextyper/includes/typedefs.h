#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <set>
#include <iostream>
#include <map>

namespace ft {

enum QueryType {
    REF = 1, ALT, CRO
};

typedef std::pair<int, QueryType>  QIdT; // int is the query ID


 enum FlagType {
     ABK = 1, OCK, NUK // abundant, overcounted, non-unique
 };

 }
#endif // TYPEDEFS_H
