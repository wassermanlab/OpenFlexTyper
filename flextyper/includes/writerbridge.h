#ifndef __WRITER_BRIDGE_H__
#define __WRITER_BRIDGE_H__

#include <experimental/filesystem>
#include "utils.h"
#include "iutils.h"
#include "iwriterbridge.h"
#include "ftMapClass.h"

namespace ft {

class WriterBridge : public IWriterBridge {
public:
    ////////////////////////////////////////////////////////////////////////
    /// \brief WriterBridge constructor
    ////////////////////////////////////////////////////////////////////////
    WriterBridge();

    void setOutputOptions(const ft::FTMap& ftMap);
    std::string joinString(const std::set<std::string>& setOfStr, std::string delimeter);

    std::string createHeader();
    std::string formatOutputMap();
    std::string getFlagKmers(const ft::QueryClass& query, const ft::FlagType flag);
    void addQueryToOutput( const ft::QueryClass& query, const std::string prefix);


    ////////////////////////////////////////////////////////////////////////
    /// \brief saveQueryOutput
    /// \param allCounts
    /// \param returnMatchesOnly
    ////////////////////////////////////////////////////////////////////////
    void saveOutput(const ft::FTMap& ftMap);

    ////////////////////////////////////////////////////////////////////////
    /// `brief destructor
    ////////////////////////////////////////////////////////////////////////
    virtual ~WriterBridge();

    ////////////////////////////////////////////////////////////////////////
    /// \brief overrideUtils
    /// \param utils
    ////////////////////////////////////////////////////////////////////////
    void overrideUtils(std::shared_ptr<IUtils> utils);

    ////////////////////////////////////////////////////////////////////////
    /// \brief getters
    ////////////////////////////////////////////////////////////////////////
    bool getRefData();
    bool getAltData();
    bool getCroData();
    bool getOCKFlag();
    bool getNUKFlag();
    bool getMatchesOnlyFlag();
    std::map<std::string, std::string> getOutputMap();


private:
    std::map<std::string, std::string> _outputMap;
    bool _refData;
    bool _altData;
    bool _croData;
    bool _OCK;
    bool _NUK;
    bool _MatchesOnly;

    ////////////////////////////////////////////////////////////////////////
    /// \brief _utils
    ////////////////////////////////////////////////////////////////////////
    Utils _ownedUtils;

    ////////////////////////////////////////////////////////////////////////
    /// \brief _utils
    ////////////////////////////////////////////////////////////////////////
    IUtils* _utils;
};
}

#endif // end of __WRITER_BRIDGE_H__
