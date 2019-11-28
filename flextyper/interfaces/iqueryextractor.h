#ifndef __IQUERY_EXTRACTOR_H__
#define __IQUERY_EXTRACTOR_H__

#include <set>
#include "typedefs.h"
#include <experimental/filesystem>
#include "utils.h"
#include <fstream>

namespace fs = std::experimental::filesystem;

namespace ft {
////////////////////////////////////////////////////////////////////////
/// \copyright Copyright (c) 2019, Wasserman lab
/// \author    Godfrain Jacques Kounkou
/// \brief This file contains the declaration of kmergenerator interface
////////////////////////////////////////////////////////////////////////
class IQueryExtractor {
public:
    ////////////////////////////////////////////////////////////////////////
    /// \brief getInputQueriesRoutine
    /// \param refSequence
    /// \param altSequence
    /// \param fileIndex
    /// \param inputQueries
    ////////////////////////////////////////////////////////////////////////
    virtual void getInputQueriesRoutine(const std::string& refSequence, const std::string& altSequence, uint fileIndex, std::set<Query>& inputQueries) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// \brief getStartAndEndPointSequences
    /// \param startPointRef
    /// \param endPointRef
    /// \param fileIndex
    /// \param inputQueries
    ////////////////////////////////////////////////////////////////////////
    virtual void getStartAndEndPointSequences(const std::string& startPointRef, const std::string& endPointRef, uint fileIndex, std::set<Query>& inputQueries) = 0;

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
