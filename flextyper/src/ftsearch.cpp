#include "ftsearch.h"
#include "kmerClass.h"
#include "queryClass.h"

namespace ft {

//======================================================================
FTSearch::FTSearch()
    : _utils(&_ownedUtils)
    , _stats(&_ownedStats)
    , _writerBridge(&_ownedWriterBridge)
    , _kmerGenerator(&_ownedKmerGenerator)
    , _finder(&_ownedFinder)
    , _resultProcessor(&_ownedResultProcessor)
    , _queryExtractor(&_ownedQueryExtractor)
{
}

//======================================================================
void FTSearch::init(const fs::path& pathToQueryFile, uint kmerSize, uint readLength,
                    const fs::path& indexFileLocation, const fs::path& outputFolder,
                    bool refOnly, SearchType searchType, bool multithread, const fs::path& inputFastQ,
                    uint overlap, bool returnMatchesOnly, bool kmerCounts,
                    uint stride, uint maxOccurences, uint threadNumber, bool flagOverCountedKmers, bool ignoreNonUniqueKmers, bool crossover,
                    bool printSearchTime, uint maxKmers, uint totalKmers, const fs::path& matchingReads)
{
    ft::FTMap ftMap;
    ftMap.setProperties(kmerSize,
                         refOnly,
                         searchType,
                         overlap,
                         stride,
                         crossover,
                         ignoreNonUniqueKmers,
                         kmerCounts,
                         maxKmers,
                         totalKmers);
    ftMap.setMaxOcc(maxOccurences);
    ftMap.setOverCountedFlag(flagOverCountedKmers);


    std::ifstream in(matchingReads, std::ifstream::ate | std::ifstream::binary);
    long long offset = in.tellg();
    fs::path readFile;

    uint lines = offset / (readLength + 1);

    if (inputFastQ.empty()) {
        readFile.stem() = _utils->trimmedReadFileName(indexFileLocation); // want to remove the "Indexes_" at the beginning
    } else {
        readFile = inputFastQ;
    }

    fs::path queryOutputFile;

    queryOutputFile  = outputFolder;
    queryOutputFile /= pathToQueryFile.stem() += std::string("_") += readFile.stem() += "_Results.tsv";
    std::set<fs::path> setOfIndexes = _utils->getSetOfIndexes();
    std::set<Query> inputQueries    = _queryExtractor->getInputQueries(refOnly, crossover, pathToQueryFile);

    _kmerGenerator->genKmerMap(inputQueries, ftMap);
    //std::cout << "kmerMap size                  : " << kmerMap.size() << std::endl;

    /*
    for (auto e : kmerMap) {
        std::cout << e.first << std::endl;
    }
    */

    std::cout << "\nsearching..." << std::endl;
    auto indexFile = setOfIndexes.begin()->c_str();

    // selecting the correct strategy depending on the size of the index size set
    if (setOfIndexes.size() == 1) {
        std::cout << "searching with " << setOfIndexes.size() << " indexes" << std::endl;
        std::cout << "offset : " << offset << std::endl;
        _finder->searchMonoIndex(ftMap, indexFile, indexFileLocation, multithread, threadNumber, printSearchTime);

    } else if (setOfIndexes.size() > 1) {

        offset /= setOfIndexes.size();
        std::cout << "offset : " << offset << std::endl;
        std::cout << "searching with " << setOfIndexes.size() << " indexes" << std::endl;
        _finder->searchMultipleIndexes(ftMap, setOfIndexes, indexFileLocation, multithread, threadNumber,
                                       printSearchTime, offset);
    }

    fs::path indexMapFile = indexFile;
    indexMapFile += ".map";

    _resultProcessor->processResults(ftMap, readLength, lines, matchingReads);
    _writerBridge->saveQueryOutput(ftMap.getQueryMap(), returnMatchesOnly, flagOverCountedKmers, ignoreNonUniqueKmers, crossover, pathToQueryFile, queryOutputFile);
}

//======================================================================
void FTSearch::overrideUtils(std::shared_ptr<IUtils> utils)
{
    _utils = utils.get();
}

//======================================================================
void FTSearch::overrideStats(std::shared_ptr<IStats> stats)
{
    _stats = stats.get();
}

//======================================================================
void FTSearch::overrideWriterBridge(std::shared_ptr<IWriterBridge> writerBridge)
{
    _writerBridge = writerBridge.get();
}

//======================================================================
void FTSearch::overrideKmerGenerator(std::shared_ptr<IKmerGenerator> kmerGenerator)
{
    _kmerGenerator = kmerGenerator.get();
}

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
