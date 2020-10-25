#ifndef __IQUERY_EXTRACTOR_H__
#define __IQUERY_EXTRACTOR_H__

#include <set>
#include <experimental/filesystem>
#include "utils.h"
#include <fstream>

namespace fs = std::experimental::filesystem;

namespace ft {

class IQueryExtractor {
public:
    virtual ~IQueryExtractor() {}

    ////////////////////////////////////////////////////////////////////////
    /// \brief getInputQueries
    /// \param refOnly
    /// \param crossover
    /// \param pathToQueryFile
    /// \return
    ////////////////////////////////////////////////////////////////////////
    virtual std::set<Query> getInputQueries(bool refOnly, bool crossover, const fs::path& pathToQueryFile) = 0;
};
}

#endif // end of the class
