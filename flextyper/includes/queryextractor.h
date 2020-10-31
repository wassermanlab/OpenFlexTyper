#ifndef __QUERY_EXTRACTOR_H__
#define __QUERY_EXTRACTOR_H__

#include <set>
#include <experimental/filesystem>
#include "utils.h"
#include "iutils.h"
#include <fstream>
#include "iqueryextractor.h"

namespace fs = std::experimental::filesystem;

namespace ft {
////////////////////////////////////////////////////////////////////////
/// \class QueryExtractor
/// \brief Read and format query file
////////////////////////////////////////////////////////////////////////
class QueryExtractor : public IQueryExtractor {
public:
    /// Constructor
    QueryExtractor();

    /// Destructor
    virtual ~QueryExtractor();

    ////////////////////////////////////////////////////////////////////////
    /// \brief getInputQueries
    /// \param bool refOnly
    /// \param bool crossover
    /// \param fs::path pathToQueryFile
    /// \return std::set<Query> set of queries, @see QueryClass
    ////////////////////////////////////////////////////////////////////////
    std::set<Query> getInputQueries(bool refOnly, bool crossover, const fs::path& pathToQueryFile);

    void overrideUtils(std::shared_ptr<IUtils> utils);

private:
    Utils _ownedUtils;
    IUtils* _utils;
};
}

#endif // end of the class
