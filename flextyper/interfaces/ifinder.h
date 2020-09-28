////////////////////////////////////////////////////////////////////////
/// \copyright Copyright (c) 2020, Wasserman lab
////////////////////////////////////////////////////////////////////////

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
    /// \brief searchIndexes
    ////////////////////////////////////////////////////////////////////////
    virtual void searchIndexes(ft::FTMap &ftMap) =0;

};
}

#endif // end of Finder class
