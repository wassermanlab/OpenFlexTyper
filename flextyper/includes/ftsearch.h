#ifndef __FM_SEARCH_H__
#define __FM_SEARCH_H__

#include <experimental/filesystem>
#include "utils.h"
#include "stats.h"
#include "writerbridge.h"
#include "kmergenerator.h"
#include "finder.h"
#include "resultprocessor.h"
#include "queryextractor.h"
#include <climits>

namespace fs = std::experimental::filesystem;

namespace ft {
////////////////////////////////////////////////////////////////////////
/// \copyright Copyright (c) 2019, Wasserman lab
/// \author    Godfrain Jacques Kounkou
/// \brief This file contains the definition of ftsearch. The class can
///             be summarized as the init point for the application.
///             The init function calls other parts of the application
////////////////////////////////////////////////////////////////////////
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

public:
    ////////////////////////////////////////////////////////////////////////
    /// \brief search
    /// \param pathToQueryFile
    /// \param kmerSize
    /// \param readLength
    /// \param listIndexFiles
    /// \param outputFile
    /// \param refOnly
    /// \param searchType
    /// \param multithread
    /// \param ignore_multi_hits
    /// \param extract_matching_reads
    ////////////////////////////////////////////////////////////////////////
    void init(const fs::path& pathToQueryFile       ,
              uint kmerSize                         ,
              uint readLength                       ,
              const fs::path& indexLocation         ,
              const fs::path& outputFile            ,
              bool refOnly                          ,
              SearchType searchType                 ,
              bool multithread              = false ,
              const fs::path& inputFastQ    = ""    ,
              uint overlap                  = 0     ,
              bool returnMatchesOnly        = false ,
              bool kmerCounts               = false ,
              uint stride                   = 10    ,
              uint maxOccurences            = 200   ,
              uint threadNumber             = 1     ,
              bool ignoreNonUniqueKmers     = true  ,
              bool crossover                = false ,
              bool printSearchTime          = false,
              uint maxKmers                 = UINT_MAX,
              uint totalKmers               = UINT_MAX,
              const fs::path& matchingReads = "");

    void overrideUtils(std::shared_ptr<IUtils> utils);
    void overrideStats(std::shared_ptr<IStats> stats);
    void overrideWriterBridge(std::shared_ptr<IWriterBridge> writerBridge);
    void overrideKmerGenerator(std::shared_ptr<IKmerGenerator> kmerGenerator);
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
    KmerGenerator   _ownedKmerGenerator;
    IKmerGenerator* _kmerGenerator;

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

