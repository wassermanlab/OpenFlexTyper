////////////////////////////////////////////////////////////////////////
/// \copyright Copyright (c) 2019, Wasserman lab
/// \brief This file contains the declaration of queryextractor class
////////////////////////////////////////////////////////////////////////

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

class QueryExtractor : public IQueryExtractor {
public:
    ////////////////////////////////////////////////////////////////////////
    /// \brief QueryExtractor
    ////////////////////////////////////////////////////////////////////////
    QueryExtractor();

    ////////////////////////////////////////////////////////////////////////
    /// \brief ~QueryExtractor
    ////////////////////////////////////////////////////////////////////////
    virtual ~QueryExtractor();

    ////////////////////////////////////////////////////////////////////////
    /// \brief getInputQueriesRoutine
    /// \param refSequence
    /// \param altSequence
    /// \param fileIndex
    /// \param inputQueries
    ////////////////////////////////////////////////////////////////////////
    void getInputQueriesRoutine(const std::string& refSequence, const std::string& altSequence, uint fileIndex, std::set<Query>& inputQueries);

    ////////////////////////////////////////////////////////////////////////
    /// \brief getStartAndEndPointSequences
    /// \param startPointRef
    /// \param endPointRef
    /// \param fileIndex
    /// \param inputQueries
    ////////////////////////////////////////////////////////////////////////
    void getStartAndEndPointSequences(const std::string& startPointRef, const std::string& endPointRef, uint fileIndex, std::set<Query>& inputQueries);

    ////////////////////////////////////////////////////////////////////////
    /// \brief getInputQueries
    /// \param refOnly
    /// \param crossover
    /// \param pathToQueryFile
    /// \return
    ////////////////////////////////////////////////////////////////////////
    std::set<Query> getInputQueries(bool refOnly, bool crossover, const fs::path& pathToQueryFile);

    ////////////////////////////////////////////////////////////////////////
    /// \brief overrideUtils
    /// \param utils
    ////////////////////////////////////////////////////////////////////////
    void overrideUtils(std::shared_ptr<IUtils> utils);

private:
    ////////////////////////////////////////////////////////////////////////
    /// \brief _utils
    ////////////////////////////////////////////////////////////////////////
    Utils _ownedUtils;
    IUtils* _utils;
};
}

#endif // end of the class
