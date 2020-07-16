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
csa_wt<wt_huff<rrr_vector<256>>, 512, 1024> FmIndex::getFmIndex()
{
    return _fmindex;
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
    std::cout << "Kmer Search count "<< occs << " for " << kmer << std::endl;
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
fs::path FmIndex::createFMIndex(const algo::IndexProps& _props, const fs::path& preprocessedFasta)
{
    std::lock_guard<std::mutex> lock(_mtx);
    std::cout << "create index for " << preprocessedFasta << std::endl;
    fs::path outputIndex = _props.getOutputFolder();

    outputIndex /= preprocessedFasta.filename();

    outputIndex.replace_extension(".fm9");

    std::cout << "creating output index " << outputIndex << std::endl;
    if (!load_from_file(_fmindex, outputIndex)) {

        std::ifstream in(preprocessedFasta);
        if (!in) {
            std::cout << "ERROR: File " << preprocessedFasta << " does not exist. Exit." << std::endl;
            return "";
        }
        // mtx.lock();
        std::cout << "No index " << outputIndex << " located. Building index now." << std::endl;
        // mtx.unlock();
        construct(_fmindex, preprocessedFasta, 1);
        store_to_file(_fmindex, outputIndex);
    }


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
    std::cout << "Running FM Index" << std::endl;
    std::vector<std::future<fs::path>> operations;
    std::cout << "number of files to index  " << _props.getNumOfIndexes() << std::endl;
    std::map<fs::path, std::pair<u_int, u_int>> _ppfs = _props.getPreProcessedFastas();
    std::cout << "number of files found  " << _ppfs.size() << std::endl;

    if  (_props.getNumOfIndexes() != _ppfs.size()){
        std::cout << "Error: wrong number of files found "<< std::endl;
    }
    for (auto _ppf : _props.getPreProcessedFastas()){
        std::cout << "indexing " << _ppf.first << std::endl;
        operations.push_back(std::async(std::launch::async,
                                        &FmIndex::createFMIndex,
                                        this,
                                        _props,
                                        _ppf.first));
    }

    for (size_t i = 0; i < _ppfs.size(); i++){
        fs::path outputIndex = operations[i].get();
        u_int offset = _props.getOffsetForIndex(outputIndex);
        std::cout << "index created " << outputIndex << std::endl;
        _props.addToIndexSet(outputIndex, offset);
       }
    fs::path indexPropsINI =  _props.getOutputFolder();
    indexPropsINI /= _props.getOutputFile().filename();
    indexPropsINI.replace_extension(".ini");

    _props.saveIndexProps(indexPropsINI);
}

//======================================================================
FmIndex::~FmIndex()
{
}
}
