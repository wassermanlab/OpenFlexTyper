#ifndef __IFINDER_H__
#define __IFINDER_H__

#include "ftMapClass.h"
#include <experimental/filesystem>
#include "fmindex.h"
#include "ifmindex.h"
#include <algorithm>

namespace fs = std::experimental::filesystem;

namespace ft {

class IFinder {
public:
    virtual ~IFinder() {}

    ////////////////////////////////////////////////////////////////////////
    /// \brief searchMonoIndex
    ////////////////////////////////////////////////////////////////////////
    virtual void searchMonoIndex(ft::FTMap& ftMap, const fs::path& indexPath,
                                 long long offset) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// \brief searchMultipleIndexes
    ////////////////////////////////////////////////////////////////////////
    virtual void searchMultipleIndexes(ft::FTMap& ftMap ) = 0;
};
}

#endif // end of Finder class
