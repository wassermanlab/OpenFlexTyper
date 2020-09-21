#include "finder.h"
#include <future>

namespace ft {
//======================================================================
Finder::Finder()
{
}

//======================================================================
void Finder::testIndex(const FTProp& ftProps, algo::IFmIndex* fmIndex, const fs::path &indexPath, std::string& testkmer )
{
    (void)indexPath;
    //test the index can be loaded correctly

    bool overCountedFlag = ftProps.getOverCountedFlag();
    ft::KmerClass tmpResult = fmIndex->search(testkmer,
                                                ftProps.getMaxOcc(),
                                                overCountedFlag);
    if (tmpResult.getKPositions().size() == 0) {
        LogClass::Log << "(E) testIndex " << testkmer << " Error" << std::endl;
        LogClass::Log << "(E) occ(" << tmpResult.getOCC() << ") < MaxOcc(" << ftProps.getMaxOcc() << ") cause the search to drop" <<  std::endl;
        if (overCountedFlag == false)
            LogClass::Log << "(I) getOverCountedFlag: " << overCountedFlag << " won't set ABK " << std::endl;
        LogClass::ThrowRuntimeError("testing index failed ");
    }

}
//======================================================================
void Finder::searchIndexes(ft::FTMap &ftMap)
{
    int numOfIndexes = ftMap.getFTProps().getNumOfIndexes();
    LogClass::Log << "(I) ftMap number of indexes " << numOfIndexes << std::endl;
    if (ftMap.getFTProps().getMultithreadFlag()) {
        indexParallelSearch(ftMap);
    } else {
        indexSequentialSearch(ftMap);
    }
}

//======================================================================
void Finder::indexSequentialSearch(FTMap &ftMap)
{
    std::map<fs::path, uint> indexes = ftMap.getFTProps().getIndexSet();
    for (std::pair<fs::path, u_int> item : indexes){
        fs::path indexPath = item.first;
        u_int offset = item.second;
        sequentialSearch(ftMap, indexPath, offset);
    }
    LogClass::Log << "(I) Search Completed for all indexes " << std::endl;
}

//======================================================================
void Finder::indexParallelSearch(FTMap &ftMap)
{
    std::map<fs::path, uint> indexes = ftMap.getFTProps().getIndexSet();
    std::map<fs::path, uint>::iterator it = indexes.begin();
    while ( it != indexes.end()) {
        fs::path indexPath = it->first;
        uint offset = it->second;
        parallelSearch(ftMap, indexPath, offset);
        it++;
    }
}

//======================================================================
void Finder::addResultsFutures(std::map<std::string, ft::KmerClass> & indexResults, ft::KmerClass &tmpResult, uint offset)
{
    const std::string& resultkmer = tmpResult.getKmer();
    std::map<std::string, ft::KmerClass>::iterator it = indexResults.find(resultkmer);
    if (it != indexResults.end())
    {
        ft::KmerClass result = it->second;

        tmpResult.adjustPositionsWithOffset(offset);
        result.setKPositions(tmpResult.getKPositions());

        result.setOCC(result.getOCC() + tmpResult.getOCC());

        for (std::size_t i = 0; i < 8; ++i) {
            if ( tmpResult.getKFlags().test(i) ) {
                result.addKFlag(ft::FlagType(i));
            }
        }
        it->second = result;
    } else {
        tmpResult.adjustPositionsWithOffset(offset);
        indexResults[resultkmer] = tmpResult;
    }
}

//======================================================================
void Finder::parallelSearch(FTMap &ftMap, const fs::path &indexPath,
                            long long offset)
{
    LogClass::Benchmark benchmark;

    const FTProp& ftProps = ftMap.getFTProps();
    uint maxOcc = ftProps.getMaxOcc();
    uint overCountedFlag = ftProps.getOverCountedFlag();
    uint maxThreads = ftProps.getMaxThreads();

    algo::IFmIndex* fmIndex = new algo::FmIndex(ftProps.isVerbose());
    const std::unordered_map<std::string, ft::KmerClass>& kmerMap = ftMap.getKmerSet();


    std::map<std::string, ft::KmerClass>  indexResults;

    try {
        fmIndex->loadIndexFromFile(indexPath);
    } catch (std::exception& e) {
        LogClass::Log << "(E) load " << e.what() << std::endl;
    }

    LogClass::Log << "(I) parallelSearch: loaded " << indexPath.string() << std::endl;

    // create a vector of futures
    std::vector<std::future<ft::KmerClass>> resultsFutures;
    uint j = 0;
    uint elts = 0;

    std::unordered_map<std::string, ft::KmerClass>::const_iterator it = kmerMap.begin();
    while (it != kmerMap.end())
    {
        std::string kmer = it->first;
        resultsFutures.push_back(std::async(std::launch::async, &algo::FmIndex::search,
                                                dynamic_cast<algo::FmIndex*>(fmIndex),
                                                kmer, maxOcc, overCountedFlag));
        it++;
        if (++j < maxThreads && it != kmerMap.end()) {
            continue;
        }

        for (auto& e : resultsFutures) {
            e.wait();
            j--;
            ft::KmerClass tmpResult = e.get();
            elts++;
            addResultsFutures(indexResults, tmpResult, offset);
        }
        resultsFutures.clear();
    }

    ftMap.addIndexResults(indexResults);
    LogClass::Log  << "(I) number of indexes processed " << indexResults.size() << std::endl;
    benchmark.now("parallelSearch DONE ");
}

//======================================================================
void Finder::sequentialSearch(ft::FTMap &ftMap,
                              const fs::path &indexPath, long long offset)
{
    LogClass::Benchmark benchmark;
    const FTProp& ftProps = ftMap.getFTProps();
    uint maxOcc = ftProps.getMaxOcc();
    uint overCountedFlag = ftProps.getOverCountedFlag();
    std::cout << "index " << indexPath << " with offset " << offset << std::endl;
    const std::unordered_map<std::string, ft::KmerClass>& kmerMap = ftMap.getKmerSet();

    algo::IFmIndex* fmIndex = new algo::FmIndex(ftProps.isVerbose());

    std::map<std::string, ft::KmerClass> indexResults;

    try {
        fmIndex->loadIndexFromFile(fs::absolute(indexPath));
    } catch (std::exception& e) {
        LogClass::Log << "(E) load " << e.what() << std::endl;
    }
    LogClass::Log << "(I) sequentialSearch: loaded " << indexPath.string() << std::endl;


    std::unordered_map<std::string, ft::KmerClass>::const_iterator it = kmerMap.begin();
    LogClass::Log << "(I) Kmer map loaded, beginning search on " << kmerMap.size() << " kmers" << std::endl;

    while (it != kmerMap.end())
    {
       std::string kmer = it->first;
       ft::KmerClass tmpResult = fmIndex->search(kmer, maxOcc, overCountedFlag);
       //LogClass::Log  << "(I) Kmer Search completed " << kmer << std::endl;
       addResultsFutures(indexResults,tmpResult, offset);
       //LogClass::Log  << "(I) Kmer results added  " << kmer << std::endl;
       it++;
    }

    ftMap.addIndexResults(indexResults);
    LogClass::Log  << "(I) number of indexes processed " << indexResults.size() << std::endl;
    benchmark.now("sequentialSearch DONE ");

    indexResults.clear();
}


//======================================================================
Finder::~Finder()
{
}
}
