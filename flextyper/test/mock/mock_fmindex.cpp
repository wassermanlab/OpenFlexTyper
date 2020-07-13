#include "gmock/gmock.h"
#include "ifmindex.h"

#include <iostream>
#include <set>
#include <tuple>
#include <vector>

using namespace std;
using namespace ft;

namespace ft {
class MockFmIndex : public algo::IFmIndex {
public:
    MOCK_METHOD2(createFMIndex,        fs::path( const algo::IndexProps& _props, const fs::path& preprocessedFasta));
    //MOCK_METHOD3(searchmany,           std::map<std::string, std::set<size_t>>(const std::vector<std::string>&, const std::string&, const std::string&));
    MOCK_METHOD1(parallelFmIndex,      void(algo::IndexProps& _props));
    //MOCK_METHOD1(generateReadsMap,     void(const std::string&));
    MOCK_METHOD1(setKmerMapSize,       void(size_t));
    MOCK_METHOD4(search,               ft::KmerClass(ft::KmerClass, u_int, size_t, bool));
    MOCK_METHOD1(loadIndexFromFile,    void(const std::string&));
};
}
