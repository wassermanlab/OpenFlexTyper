#include "ftSearch.h"


namespace ft {

//======================================================================
FTSearch::FTSearch()
    : _utils(&_ownedUtils)
    , _writerBridge(&_ownedWriterBridge)
    , _finder(&_ownedFinder)
    , _queryExtractor(&_ownedQueryExtractor)
{
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
    std::cout << "Error: Output File doesnt exist" << std::endl;
    std::cout << "checking for output directory"  << std::endl;
    if (!exists(ftProps.getOutputFolder()))
    {
        std::cout << "Error: Output folder doesnt exist" << std::endl;
        std::cout << "Making output folder " << std::endl;
        create_directory(ftProps.getOutputFolder());
        if (!exists(ftProps.getOutputFolder()))
        {
            std::cout << "Error: Couldnt create output folder" << std::endl;
        }
    } else {
        std::cout << "Output Folder exists " << std::endl;
    }



}
}

//======================================================================
void FTSearch::init(const FTProp& ftProps)
{
    ft::FTMap ftMap(ftProps);
    //checkInputFastQ(ftProps);
    checkOutputFile(ftProps);
    std::cout << "extracting queries " << std::endl;
    std::set<Query> inputQueries = _queryExtractor->getInputQueries(ftProps.getRefOnlyFlag(), ftProps.getCrossoverFlag(), ftProps.getPathToQueryFile());

    std::cout << " number of queries " << inputQueries.size() << std::endl;

    ftMap.addInputQueries(inputQueries);

    std::cout << " number of queries in FTMap " << ftMap._querySet.size() << std::endl;

    ftMap.genQKMap();

    std::cout << "\nsearching..." << std::endl;

    _finder->searchIndexes(ftMap);

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
