#include "ftSearch.h"

namespace ft {

//======================================================================
FTSearch::FTSearch(bool verbose)
    : _utils(&_ownedUtils)
    , _writerBridge(&_ownedWriterBridge)
    , _finder(&_ownedFinder)
    , _queryExtractor(&_ownedQueryExtractor)
    , _verbose(verbose)
{
}

void FTSearch::printToStdOut(const std::string outputString) const {
    if (_verbose){
        std::cout << outputString << std::endl;
    }
}
//======================================================================
void FTSearch::checkInputFastQ(FTProp ftProps){

    // want to remove the "Indexes_" at the beginning

if (ftProps.getInputFastQ().empty()) {
    ftProps.getInputFastQ().stem() = _utils->trimmedReadFileName(ftProps.getIndexDir());
}
}

//======================================================================
void FTSearch::checkOutputFile(FTProp ftProps){

if (!exists(ftProps.getOutputFile())) {
    printToStdOut("Error: Output File doesnt exist");
    printToStdOut( "checking for output directory");
    if (!exists(ftProps.getOutputFolder()))
    {
        printToStdOut("Error: Output folder doesnt exist" );
        printToStdOut( "Making output folder " );
        create_directory(ftProps.getOutputFolder());
        if (!exists(ftProps.getOutputFolder()))
        {
            printToStdOut("Error: Couldnt create output folder" );
        }
    } else {
        printToStdOut( "Output Folder exists " );
    }
}
}

//======================================================================
void FTSearch::init(const FTProp& ftProps)
{
    FTProp::OpenLog("searchIndexes.log");
    FTProp::Benchmark benchmark = FTProp::Benchmark(0);

    ft::FTMap ftMap(ftProps);
    //checkInputFastQ(ftProps);
    checkOutputFile(ftProps);
    printToStdOut("extracting queries " );
    std::set<Query> inputQueries;
    try {
        inputQueries = _queryExtractor->getInputQueries(ftProps.getRefOnlyFlag(), ftProps.getCrossoverFlag(), ftProps.getPathToQueryFile());

    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

    benchmark.now("InputQueries retrieved " + std::to_string(inputQueries.size()) + " DONE ");

    ftMap.addInputQueries(inputQueries);

    benchmark.now("FTMap AddInputQueries DONE ");

    ftMap.genQKMap();

    benchmark.now("FTMap genQKMap DONE ");

    _finder->searchIndexes(ftMap);

    benchmark.now("FTMap SearchIndexes DONE ");

    ftMap.processResults();

    benchmark.now("FTMap ProcessResults DONE ");

    _writerBridge->saveOutput(ftMap);

    benchmark.now("SaveOutput DONE ");

    FTProp::CloseLog();

}

//======================================================================
void FTSearch::overrideUtils(std::shared_ptr<IUtils> utils)
{
    _utils = utils.get();
}

//======================================================================
void FTSearch::overrideWriterBridge(std::shared_ptr<IWriterBridge> writerBridge)
{
    _writerBridge = writerBridge.get();
}

//======================================================================
void FTSearch::overrideFinder(std::shared_ptr<IFinder> finder)
{
    _finder = finder.get();
}


//======================================================================
void FTSearch::overrideQueryExtractor(std::shared_ptr<IQueryExtractor> queryExtractor)
{
    _queryExtractor = queryExtractor.get();
}

//======================================================================
FTSearch::~FTSearch()
{
}
}
