#include "fmindex.h"

using namespace std::chrono;

namespace algo {

//======================================================================
FmIndex::FmIndex()
{
}

//======================================================================
void FmIndex::setKmerMapSize(size_t kmerMapSize)
{
    _kmerMapSize = kmerMapSize;
}

//======================================================================
ft::KmerClass FmIndex::search(ft::KmerClass kmerClass,
                              u_int maxOcc, size_t i,
                              bool flagOverCountedKmers)
{
    // This code is executed in a different thread for multithreaded
    // executions and in main thread for monothreaded applications

    std::string kmer = kmerClass.getKmer();
    ft::KmerClass resultsfutures(kmer);

    auto start = high_resolution_clock::now();

    size_t occs = count(_fmindex, kmer.begin(), kmer.end());

    _mtx.lock();
    std::cout << '\r' << float(((float)i * 100) / _kmerMapSize) << " % " << std::flush;
    _mtx.unlock();

    // if number kmers > max, flag kmer as "abundant"
    if (occs > maxOcc && flagOverCountedKmers) {
        resultsfutures.addKFlag(ft::FlagType::ABK);
    }

    if (occs > 0  && occs <= maxOcc) {
        auto locations = sdsl::locate(_fmindex, kmer.begin(), kmer.begin() + kmer.length());
        for (auto e : locations) {
            // std::cout << e << " --> " << (e / 59) + 1 << std::endl;
            resultsfutures.addKPosition(e);
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    return resultsfutures;
}


//======================================================================
fs::path FmIndex::createFMIndex(algo::IndexProps& _props, const fs::path& preprocessedFasta)
{
    std::lock_guard<std::mutex> lock(_mtx);
    fs::path outputIndex = _props.getOutputFolder();
    outputIndex /= preprocessedFasta.filename();
    outputIndex.replace_extension(".fm9");
    std::cout << "output index " << outputIndex << std::endl;
    if (!load_from_file(_fmindex, _props.getOutputFolder())) {
        std::ifstream in(preprocessedFasta);
        if (!in) {
            std::cout << "ERROR: File " << preprocessedFasta << " does not exist. Exit." << std::endl;
            return "";
        }
        // mtx.lock();
        std::cout << "No index " << _props.getOutputFolder() << " located. Building index now." << std::endl;
        // mtx.unlock();
        construct(_fmindex, preprocessedFasta, 1);
        store_to_file(_fmindex, _props.getOutputFolder());
    }

    _props.addToIndexSet(outputIndex);
    return outputIndex;
}

//======================================================================
void FmIndex::loadIndexFromFile(const std::string& indexname)
{
    if (!load_from_file(_fmindex, indexname)) {
        std::cerr << "Error loading the index, please provide the index file";
    }
}

//======================================================================
void FmIndex::parallelFmIndex(algo::IndexProps& _props)
{
    //   fs::path createFMIndex(algo::IndexProps& _props, const fs::path& preprocessedFasta);

    std::vector<std::future<fs::path>> operations;
    std::set<fs::path> _ppfs = _props.getPreProcessedFastas();
    for (fs::path _ppf : _props.getPreProcessedFastas()){
        operations.push_back(std::async(std::launch::async,
                                        &FmIndex::createFMIndex,
                                        this,
                                        _props,
                                        _ppf));
    }

    for (size_t i = 0; i < _ppfs.size(); i++)
        operations[i].get();
}

//======================================================================
FmIndex::~FmIndex()
{
    std::rename("tmp.log", "kmerSearchTime.log");
}
}
