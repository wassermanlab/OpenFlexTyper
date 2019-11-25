#ifndef __IWRITER_BRIDGE_H__
#define __IWRITER_BRIDGE_H__

#include "typedefs.h"
#include <experimental/filesystem>
#include "utils.h"

namespace fs = std::experimental::filesystem;

namespace ft {
////////////////////////////////////////////////////////////////////////
/// \copyright Copyright (c) 2019, Wasserman lab
/// \author    Godfrain Jacques Kounkou
/// \brief This file contains the declaration of writerbridge.h, it contains
///             all utility functions needed to writes results to result file
////////////////////////////////////////////////////////////////////////
class IWriterBridge {
public:
    ////////////////////////////////////////////////////////////////////////
    /// \brief saveQueryOutput
    /// \param allCounts
    /// \param returnMatchesOnly
    ////////////////////////////////////////////////////////////////////////
    virtual void saveQueryOutput(MapOfCounts allCounts, bool returnMatchesOnly, bool crossover, const fs::path& pathToQueryFile, const fs::path& queryOutputFile) = 0;
};
}

#endif // end of __WRITER_BRIDGE_H__
