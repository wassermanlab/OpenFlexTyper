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

class FTSearch {
public:
    ////////////////////////////////////////////////////////////////////////
    /// \brief FTSearch
    ////////////////////////////////////////////////////////////////////////
    FTSearch(bool verbose=false);

    ////////////////////////////////////////////////////////////////////////
    /// \brief ~FTSearch
    ////////////////////////////////////////////////////////////////////////
    virtual ~FTSearch();

    ////////////////////////////////////////////////////////////////////////
    /// \brief init
    ////////////////////////////////////////////////////////////////////////
    void init(const FTProp& ftProp);
    void printToStdOut(const std::string outputString) const;

    void checkOutputFile(FTProp ftProps);
    void overrideUtils(std::shared_ptr<IUtils> utils);
    void overrideWriterBridge(std::shared_ptr<IWriterBridge> writerBridge);
    void overrideFinder(std::shared_ptr<IFinder> finder);
    void overrideQueryExtractor(std::shared_ptr<IQueryExtractor> queryExtractor);

private:
    ////////////////////////////////////////////////////////////////////////
    /// \brief _readFile
    ////////////////////////////////////////////////////////////////////////
    fs::path _readFile;

    ////////////////////////////////////////////////////////////////////////
    /// \brief _counter
    ////////////////////////////////////////////////////////////////////////
    std::map<std::string, uint> _counter;

    ////////////////////////////////////////////////////////////////////////
    /// \brief _utils
    ////////////////////////////////////////////////////////////////////////
    Utils   _ownedUtils;
    IUtils* _utils;

    ////////////////////////////////////////////////////////////////////////
    /// \brief _writerBridge
    ////////////////////////////////////////////////////////////////////////
    WriterBridge   _ownedWriterBridge;
    IWriterBridge* _writerBridge;

    ////////////////////////////////////////////////////////////////////////
    /// \brief _finder
    ////////////////////////////////////////////////////////////////////////
    Finder   _ownedFinder;
    IFinder* _finder;

    ////////////////////////////////////////////////////////////////////////
    /// \brief _queryExtractor
    ////////////////////////////////////////////////////////////////////////
    QueryExtractor   _ownedQueryExtractor;
    IQueryExtractor* _queryExtractor;

    bool _verbose;
};
}

#endif // __FM_SEARCH_H__

