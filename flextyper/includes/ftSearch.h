////////////////////////////////////////////////////////////////////////
/// \copyright Copyright (c) 2020, Wasserman lab
////////////////////////////////////////////////////////////////////////

#ifndef __FM_SEARCH_H__
#define __FM_SEARCH_H__

#include <experimental/filesystem>
#include <climits>

#include "finder.h"
#include "ifinder.h"

#include "ftMapClass.h"

#include "utils.h"
#include "iutils.h"

#include "writerbridge.h"
#include "iwriterbridge.h"

#include "queryextractor.h"
#include "iqueryextractor.h"

namespace fs = std::experimental::filesystem;

namespace ft {
////////////////////////////////////////////////////////////////////////
/// \class FTSearch
/// \brief A class that handles the flow of a single search
////////////////////////////////////////////////////////////////////////

class FTSearch {
public:
    /// Constructor
    FTSearch(bool verbose=false);

    /// Class Destructor
    virtual ~FTSearch();

    /// @name init
    /// Functions to set up the search
    /// @{
    /// \fn
    /// \public
    void init(const FTProp& ftProp);
    void printToStdOut(const std::string outputString) const;
    void checkOutputFile(FTProp ftProps);
    /// @}

    /// @name override functions
    /// @{
    void overrideUtils(std::shared_ptr<IUtils> utils);
    void overrideWriterBridge(std::shared_ptr<IWriterBridge> writerBridge);
    void overrideFinder(std::shared_ptr<IFinder> finder);
    void overrideQueryExtractor(std::shared_ptr<IQueryExtractor> queryExtractor);
    /// @}

private:
    /// @name Properties
    /// @{
    /// \private
    /// \variable
    fs::path _readFile;

    std::map<std::string, uint> _counter;

    Utils   _ownedUtils;
    IUtils* _utils;

    WriterBridge   _ownedWriterBridge;
    IWriterBridge* _writerBridge;

    Finder   _ownedFinder;
    IFinder* _finder;

    QueryExtractor   _ownedQueryExtractor;
    IQueryExtractor* _queryExtractor;

    bool _verbose;
    /// @}
};
}

#endif // __FM_SEARCH_H__

