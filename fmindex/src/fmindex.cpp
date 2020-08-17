#include "fmindex.h"

using namespace std::chrono;

namespace algo {

//======================================================================
FmIndex::FmIndex()
{
}

//======================================================================
ft::KmerClass FmIndex::search(ft::Kmer kmer,
                              u_int maxOcc, bool flagOverCountedKmers)
{
    // This code is executed in a different thread for multithreaded
    // executions and in main thread for monothreaded applications

    //std::cout << "searching index of size " << getIndex().size() << " for " << kmer << std::endl;
    ft::KmerClass kmerResult(kmer);

    size_t occs = sdsl::count(getIndex(), kmer.begin(), kmer.end());
    //std::cout << "Kmer Search count "<< occs << " for " << kmer << std::endl;

    // if number kmers > max, flag kmer as "abundant"
    if (occs > maxOcc && flagOverCountedKmers) {
        std::cout << "Kmer flagged as Abundant " << kmer << std::endl;
        kmerResult.addKFlag(ft::FlagType::ABK);
    }
    if (occs > 0  && occs <= maxOcc) {
        //std::cout << "locating kmer positions " << kmer << " with count " << occs <<  std::endl;
        auto locations = sdsl::locate(getIndex(), kmer.begin(), kmer.begin()+kmer.length());
        if (locations.size() != occs)
        {
            std::runtime_error("number of locations doesnt equal number of occurences for kmer " + kmer );
        }

        //std::cout << "adding " << locations.size()<< " hits to kmer positions " << kmer << std::endl;
        for (auto e : locations) {
            //std::cout << "e " << e << std::endl;
            kmerResult.addKPosition(e);
        }
    }
    //std::cout << "index search positions  " << kmerResult._positions.size() << std::endl;
    return kmerResult;
}

//======================================================================
fs::path FmIndex::createFMIndex(const algo::IndexProps& _props, const fs::path& preprocessedFasta)
{
    std::lock_guard<std::mutex> lock(_mtx);
    //std::cout << "create index for " << preprocessedFasta << std::endl;
    fs::path outputIndex = _props.getOutputFolder();

    outputIndex /= preprocessedFasta.filename();

    outputIndex.replace_extension(".fm9");

    //std::cout << "creating output index " << outputIndex << std::endl;
    if (!load_from_file(_index, outputIndex)) {

        std::ifstream in(preprocessedFasta);
        if (!in) {
            std::cout << "ERROR: File " << preprocessedFasta << " does not exist. Exit." << std::endl;
            if (!fs::exists(_props.getOutputFolder())){
                std::cout << " output Folder doesnt exist " << _props.getOutputFolder() << std::endl;
            }
            return "";
        }
        // mtx.lock();
        std::cout << "No index " << outputIndex << " located. Building index now." << std::endl;
        // mtx.unlock();
        construct(_index, preprocessedFasta, 1);
        store_to_file(_index, outputIndex);
    }

    return outputIndex;
}

//======================================================================
void FmIndex::loadIndexFromFile(const std::string& indexname)
{
    if (!load_from_file(_index, indexname)) {
        std::cerr << "Error loading the index, please provide the index file";
    }
}
//======================================================================
const csa_wt<wt_huff<rrr_vector<256>>, 512, 1024>& FmIndex::getIndex(){
    return _index;
}

//======================================================================
void FmIndex::parallelFmIndex(algo::IndexProps& _props)
{
    //   fs::path createFMIndex(algo::IndexProps& _props, const fs::path& preprocessedFasta);
    std::cout << "Running FM Index" << std::endl;
    std::vector<std::future<fs::path>> operations;
    //std::cout << "number of files to index  " << _props.getNumOfIndexes() << std::endl;
    std::map<fs::path, std::pair<u_int, u_int>> _ppfs = _props.getPreProcessedFastas();
    //std::cout << "number of files found  " << _ppfs.size() << std::endl;

    if  (_props.getNumOfIndexes() != _ppfs.size()){
        std::cout << "Error: wrong number of files found "<< std::endl;
    }
    for (auto _ppf : _props.getPreProcessedFastas()){
        //std::cout << "indexing " << _ppf.first << std::endl;
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
