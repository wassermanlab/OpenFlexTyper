#ifndef __WRITER_BRIDGE_H__
#define __WRITER_BRIDGE_H__

#include <experimental/filesystem>
#include "utils.h"
#include "iutils.h"
#include "iwriterbridge.h"
#include "ftMapClass.h"

namespace ft {

////////////////////////////////////////////////////////////////////////
/// \class Writer Bridge
/// \brief A class that handles writing the results to file
////////////////////////////////////////////////////////////////////////
class WriterBridge : public IWriterBridge {
public:
    /// Constructor
    WriterBridge();

    /// Destructor
    virtual ~WriterBridge();

    /// \brief Main function to save the results
    /// \param ft::FTMap FtMap containing results
    void saveOutput(const ft::FTMap& ftMap);

    void setOutputOptions(const ft::FTMap& ftMap);
    std::string joinString(const std::set<std::string>& setOfStr, std::string delimeter);
    std::string createHeader();
    std::string formatOutputMap();
    std::string getFlagKmers(const ft::QueryClass& query, const ft::FlagType flag);
    void addQueryToOutput( const ft::QueryClass& query, const std::string prefix);
    void overrideUtils(std::shared_ptr<IUtils> utils);

    /// @name Getters
    /// Constant functions to return properties
    /// @{
    /// \public
    /// \fn
    bool getRefData();
    bool getAltData();
    bool getCroData();
    bool getOCKFlag();
    bool getNUKFlag();
    bool getMatchesOnlyFlag();
    std::map<std::string, std::string> getOutputMap();
    /// @}


private:
    /// @name Properties
    /// @{
    /// \private
    /// \var
    std::map<std::string, std::string> _outputMap;
    bool _refData;
    bool _altData;
    bool _croData;
    bool _OCK;
    bool _NUK;
    bool _MatchesOnly;
    /// @}


    Utils _ownedUtils;
    IUtils* _utils;
};
}

#endif // end of __WRITER_BRIDGE_H__
