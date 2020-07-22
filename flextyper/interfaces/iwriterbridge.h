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

    virtual void setOutputOptions(const ft::FTMap& ftMap) = 0;
    virtual std::string createHeader() = 0;
    virtual std::string formatOutputMap() = 0;
    virtual std::string getFlagKmers(const ft::QueryClass& query, const ft::FlagType flag) = 0;
    virtual void addQueryToOutput(const ft::QueryClass& query, const std::string prefix)  = 0;



    ////////////////////////////////////////////////////////////////////////
    /// \brief saveQueryOutput
    ////////////////////////////////////////////////////////////////////////
    virtual void saveOutput(const ft::FTMap& ftMap) = 0;
};
}

#endif // end of __WRITER_BRIDGE_H__
