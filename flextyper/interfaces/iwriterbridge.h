////////////////////////////////////////////////////////////////////////
/// \copyright Copyright (c) 2019, Wasserman lab
/// \brief This file contains the declaration of writerbridge.h, it contains
///             all utility functions needed to writes results to result file
////////////////////////////////////////////////////////////////////////

#ifndef __IWRITER_BRIDGE_H__
#define __IWRITER_BRIDGE_H__

#include "FTMapClass.h"
#include <experimental/filesystem>
#include "utils.h"

namespace fs = std::experimental::filesystem;

namespace ft {

class IWriterBridge {
public:
    ////////////////////////////////////////////////////////////////////////
    /// \brief saveQueryOutput
    /// \param allCounts
    /// \param returnMatchesOnly
    ////////////////////////////////////////////////////////////////////////
    virtual void saveQueryOutput(ft::FTMap ftMap, const fs::path& pathToQueryFile, const fs::path& queryOutputFile) = 0;
};
}

#endif // end of __WRITER_BRIDGE_H__
