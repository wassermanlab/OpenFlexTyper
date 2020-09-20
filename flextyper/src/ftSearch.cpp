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
    FTProp::Log << "======== Search Log " << "======== " << std::endl;

    ft::FTMap ftMap(ftProps);
    checkOutputFile(ftProps);
    printToStdOut("extracting queries " );
    std::set<Query> inputQueries;
    try {
        inputQueries = _queryExtractor->getInputQueries(ftProps.getRefOnlyFlag(), ftProps.getCrossoverFlag(), ftProps.getPathToQueryFile());

    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

    ftMap.addInputQueries(inputQueries);

    ftMap.genQKMap();

    _finder->searchIndexes(ftMap);

    printToStdOut("search complete ");

    ftMap.processResults();

    _writerBridge->saveOutput(ftMap);
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
