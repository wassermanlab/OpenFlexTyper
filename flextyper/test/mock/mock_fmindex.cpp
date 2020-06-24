////////////////////////////////////////////////////////////////////////
///
/// Copyright (c) 2018, Wasserman lab
///
/// FILE        tst_queryextractor.cpp
///
/// DESCRIPTION This file contains tests for the query extractions
///
/// Initial version @ Godfrain Jacques Kounkou
///
////////////////////////////////////////////////////////////////////////

#include "gmock/gmock.h"
#include "ifmindex.h"
#include "FTMapClass.h"
#include <iostream>
#include <set>
#include <tuple>
#include <vector>

using namespace std;
using namespace ft;

namespace ft {
class MockFmIndex : public algo::IFmIndex {
public:
    MOCK_METHOD3(createFMIndex,        fs::path(const fs::path&, const fs::path&, const fs::path&));
    //MOCK_METHOD3(searchmany,           std::map<std::string, std::set<size_t>>(const std::vector<std::string>&, const std::string&, const std::string&));
    MOCK_METHOD3(parallelFmIndex,      void(std::vector<fs::path> filenames, std::vector<fs::path> indexNames, const fs::path& indexList));
    MOCK_METHOD1(generateReadsMap,     void(const std::string&));
    MOCK_METHOD1(setKmerMapSize,       void(size_t));
    MOCK_METHOD8(search,               std::tuple<ft::KmerClass>(const std::string&, const std::set<std::pair<int, ft::QueryType>>&, const std::string&, const std::string&, u_int, size_t, bool, bool));
    MOCK_METHOD1(loadIndexFromFile,    void(const std::string&));
};
}
