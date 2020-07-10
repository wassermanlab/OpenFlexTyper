#include "ftSearch.h"


namespace ft {

//======================================================================
FTSearch::FTSearch()
    : _utils(&_ownedUtils)
    , _writerBridge(&_ownedWriterBridge)
    //, _kmerGenerator(&_ownedKmerGenerator)
    , _finder(&_ownedFinder)
    , _resultProcessor(&_ownedResultProcessor)
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

    fs::path queryOutputFile = ftProps.getOutputFolder();
    queryOutputFile /= ftProps.getPathToQueryFile().stem() += std::string("_") += ftProps.getInputFastQ().stem() += "_Results.tsv";
    ftProps.setOutputFile(queryOutputFile);
}


//======================================================================
void FTSearch::init(FTProp ftProps)
{
    ft::FTMap ftMap(ftProps);
    checkInputFastQ(ftProps);

    checkOutputFile(ftProps);

    std::set<Query> inputQueries = _queryExtractor->getInputQueries(ftProps.getRefOnlyFlag(), ftProps.getCrossoverFlag(), ftProps.getPathToQueryFile());

    ftMap.addInputQueries(inputQueries);

    ftMap.getQKMap();

    std::cout << "\nsearching..." << std::endl;

    // selecting the correct strategy depending on the size of the index size set
    if (ftProps.getNumOfIndexes() == 1) {
        std::cout << "searching with " << ftProps.getNumOfIndexes() << " indexes" << std::endl;
        std::pair<fs::path, uint> index = *ftProps.getIndexSet().begin();
        fs::path indexFile = index.first;
        uint offset = index.second;
        _finder->searchMonoIndex(ftMap, indexFile, offset);

    } else if (ftProps.getNumOfIndexes() > 1) {
        _finder->searchMultipleIndexes(ftMap);
    }

    _resultProcessor->processResults(ftMap);
    _writerBridge->saveQueryOutput(ftMap);
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
//void FTSearch::overrideKmerGenerator(std::shared_ptr<IKmerGenerator> kmerGenerator)
//{
//    _kmerGenerator = kmerGenerator.get();
//}

//======================================================================
void FTSearch::overrideFinder(std::shared_ptr<IFinder> finder)
{
    _finder = finder.get();
}

//======================================================================
void FTSearch::overrideResultProcessor(std::shared_ptr<IResultProcessor> resultProcessor)
{
    _resultProcessor = resultProcessor.get();
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
