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
    //csa_wt<wt_huff<rrr_vector<256>>, 512, 1024> _testindex;
    //sdsl::load_from_file(_testindex, indexPath);
    //auto occ = sdsl::count(_testindex, testkmer);
    bool overCountedFlag = ftProps.getOverCountedFlag();
    ft::KmerClass tmpResult = fmIndex->search(testkmer,
                                                ftProps.getMaxOcc(),
                                                overCountedFlag);
    if (tmpResult.getKPositions().size() == 0) {
        FTProp::Log << "(E) testIndex " << testkmer << " Error" << std::endl;
        FTProp::Log << "(E) occ(" << tmpResult.getOCC() << ") < MaxOcc(" << ftProps.getMaxOcc() << ") cause the search to drop" <<  std::endl;
        if (overCountedFlag == false)
            FTProp::Log << "(I) getOverCountedFlag: " << overCountedFlag << " won't set ABK " << std::endl;
        throw std::runtime_error("testing index failed ");
    }

}
//======================================================================
void Finder::searchIndexes(ft::FTMap &ftMap)
{
    int numOfIndexes = ftMap.getFTProps().getNumOfIndexes();
    FTProp::Log << "(I) ftMap number of indexes " << numOfIndexes << std::endl;

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
        const std::set<long long>& positions = tmpResult.getKPositions();
        result.setKPositions(positions, offset);
        it->second = result;
    } else {
        indexResults[resultkmer] = tmpResult;
    }
}

//======================================================================
void Finder::parallelSearch(FTMap &ftMap, const fs::path &indexPath,
                            long long offset)
{
    FTProp::Benchmark benchmark = FTProp::Benchmark(0);

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
        FTProp::Log << "(E) load " << e.what() << std::endl;
    }

    FTProp::Log << "(I) parallelSearch: loaded " << indexPath.string() << std::endl;
    //std::string testKmer = "AAT";
    //testIndex(ftProps, fmIndex, indexPath, testKmer);

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
        if (++j < maxThreads) {
            continue;
        }

        for (auto& e : resultsFutures) {
            e.wait();

            j--;
            ft::KmerClass tmpResult = e.get();
            const std::string& kmer = tmpResult.getKmer();
            uint occ = tmpResult.getOCC();
            elts++;
            if (tmpResult.getKPositions().size() > 0)
            {
                addResultsFutures(indexResults, tmpResult, offset);
               //FTProp::Log  << "(I) " << kmwer << " kpositions=" << tmpResult.getKPositions().size() << std::endl;
            }
            else if (occ > 0 && occ < maxOcc) {
           FTProp::Log  << "(W) " << kmer << " search abandoned due to occ= " << occ << " > maxOccurences" << std::endl;
            }
            //else {
            //    FTProp::Log  << "(I) " << kmer << " search no occurrences, occ=" << occ << std::endl;
            //}
        }
        resultsFutures.clear();
    }


    ftMap.addIndexResults(indexResults);
    FTProp::Log  << "(I) number of indexes processed " << indexResults.size() << std::endl;
    benchmark.now("parallelSearch DONE ");
}

//======================================================================
void Finder::sequentialSearch(ft::FTMap &ftMap,
                              const fs::path &indexPath, long long offset)
{
    FTProp::Benchmark benchmark = FTProp::Benchmark(0);
    const FTProp& ftProps = ftMap.getFTProps();
    uint maxOcc = ftProps.getMaxOcc();
    uint overCountedFlag = ftProps.getOverCountedFlag();

    const std::unordered_map<std::string, ft::KmerClass>& kmerMap = ftMap.getKmerSet();

    algo::IFmIndex* fmIndex = new algo::FmIndex(ftProps.isVerbose());

    std::map<std::string, ft::KmerClass> indexResults;

    try {
        fmIndex->loadIndexFromFile(fs::absolute(indexPath));
    } catch (std::exception& e) {
        FTProp::Log << "(E) load " << e.what() << std::endl;
    }
    FTProp::Log << "(I) sequentialSearch: loaded " << indexPath.string() << std::endl;
    //std::string testKmer = "AAT";
    //testIndex(ftProps, fmIndex, indexPath, testKmer);

    std::unordered_map<std::string, ft::KmerClass>::const_iterator it = kmerMap.begin();
    FTProp::Log << "(I) Kmer map loaded, beginning search on " << kmerMap.size() << " kmers" << std::endl;

    while (it != kmerMap.end())
    {
       std::string kmer = it->first;
       ft::KmerClass tmpResult = fmIndex->search(kmer, maxOcc, overCountedFlag);
       uint occ = tmpResult.getOCC();
       if (tmpResult.getKPositions().size() > 0)
       {
           addResultsFutures(indexResults,tmpResult, offset);
           //FTProp::Log  << "(I) " << kmwer << " kpositions=" << tmpResult.getKPositions().size() << std::endl;
       }
       else if (occ > 0 && occ < maxOcc) {
           FTProp::Log  << "(W) " << kmer << " search abandoned due to occ= " << occ << " > maxOccurences" << std::endl;
       }
       //else {
       //    FTProp::Log  << "(I) " << kmer << " search no occurrences, occ=" << occ << std::endl;
       //}

       it++;
    }

    ftMap.addIndexResults(indexResults);
    FTProp::Log  << "(I) number of indexes processed " << indexResults.size() << std::endl;
    benchmark.now("sequentialSearch DONE ");

    indexResults.clear();
}


//======================================================================
Finder::~Finder()
{
}
}
