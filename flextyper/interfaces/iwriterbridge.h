#ifndef __IWRITER_BRIDGE_H__
#define __IWRITER_BRIDGE_H__

#include "ftMapClass.h"
#include "queryClass.h"
#include <experimental/filesystem>
#include "utils.h"

namespace fs = std::experimental::filesystem;

namespace ft {

class IWriterBridge {
public:
    virtual ~IWriterBridge() {}

    ////////////////////////////////////////////////////////////////////////
    /// \brief saveQueryOutput
    ////////////////////////////////////////////////////////////////////////
    virtual void saveQueryOutput(ft::FTMap& ftMap) = 0;
};
}

#endif // end of __WRITER_BRIDGE_H__
