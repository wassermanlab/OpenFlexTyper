////////////////////////////////////////////////////////////////////////
/// \copyright Copyright (c) 2019, Wasserman lab
/// \brief This file contains the definition of ftsearch. The class can
///             be summarized as the init point for the application.
///             The init function calls other parts of the application
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

#include "stats.h"
#include "istats.h"

#include "writerbridge.h"
#include "iwriterbridge.h"

#include "resultprocessor.h"
#include "iresultprocessor.h"
#include "queryextractor.h"
#include "iqueryextractor.h"

namespace fs = std::experimental::filesystem;

namespace ft {

class FTSearch {
public:
    ////////////////////////////////////////////////////////////////////////
    /// \brief FTSearch
    ////////////////////////////////////////////////////////////////////////
    FTSearch();

    ////////////////////////////////////////////////////////////////////////
    /// \brief ~FTSearch
    ////////////////////////////////////////////////////////////////////////
    virtual ~FTSearch();

    ////////////////////////////////////////////////////////////////////////
    /// \brief init
    ////////////////////////////////////////////////////////////////////////
    void init(FTProp ftProp);

public:
    void checkInputFastQ(FTProp ftProps);
    void checkOutputFile(FTProp ftProps);
    void overrideUtils(std::shared_ptr<IUtils> utils);
    void overrideStats(std::shared_ptr<IStats> stats);
    void overrideWriterBridge(std::shared_ptr<IWriterBridge> writerBridge);
    //void overrideKmerGenerator(std::shared_ptr<IKmerGenerator> kmerGenerator);
    void overrideFinder(std::shared_ptr<IFinder> finder);
    void overrideResultProcessor(std::shared_ptr<IResultProcessor> resultProcessor);
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
    /// \brief _stats
    ////////////////////////////////////////////////////////////////////////
    Stats   _ownedStats;
    IStats* _stats;

    ////////////////////////////////////////////////////////////////////////
    /// \brief _writerBridge
    ////////////////////////////////////////////////////////////////////////
    WriterBridge   _ownedWriterBridge;
    IWriterBridge* _writerBridge;

    ////////////////////////////////////////////////////////////////////////
    /// \brief _kmerGenerator
    ////////////////////////////////////////////////////////////////////////
    //KmerGenerator   _ownedKmerGenerator;
    //IKmerGenerator* _kmerGenerator;

    ////////////////////////////////////////////////////////////////////////
    /// \brief _finder
    ////////////////////////////////////////////////////////////////////////
    Finder   _ownedFinder;
    IFinder* _finder;

    ////////////////////////////////////////////////////////////////////////
    /// \brief _resultProcessor
    ////////////////////////////////////////////////////////////////////////
    ResultProcessor   _ownedResultProcessor;
    IResultProcessor* _resultProcessor;

    ////////////////////////////////////////////////////////////////////////
    /// \brief _queryExtractor
    ////////////////////////////////////////////////////////////////////////
    QueryExtractor   _ownedQueryExtractor;
    IQueryExtractor* _queryExtractor;



};
}

#endif // __FM_SEARCH_H__

