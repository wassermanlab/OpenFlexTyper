////////////////////////////////////////////////////////////////////////
/// \copyright Copyright (c) 2020, Wasserman lab
////////////////////////////////////////////////////////////////////////

#include "fmindex.h"

using namespace std::chrono;

namespace algo {

//======================================================================
FmIndex::FmIndex()
{
}
FmIndex::FmIndex(bool verbose)
    : _verbose(verbose)
{}

#if 0
//======================================================================
ft::KmerClass FmIndex::search(const std::string& kmer,
                              u_int maxOcc)
{
    // This code is executed in a different thread for multithreaded
    // executions and in main thread for monothreaded applications

    ft::KmerClass kmerResult = ft::KmerClass(kmer);

    size_t occs = sdsl::count(_index, kmer.begin(),  kmer.end());
    kmerResult.setOCC(occs);

    // if number kmers > max, flag kmer as "over counted"
    if (occs > maxOcc ) {
        kmerResult.addKFlag(ft::FlagType::OCK);
    }
    if (occs > 0  && occs <= maxOcc) {
        auto locations = sdsl::locate(_index, kmer.begin(), kmer.end());
        if (locations.size() != occs)
        {
            std::runtime_error("number of locations doesn't equal number of occurences for kmer " + kmer );
        }

        for (auto e : locations) {
            kmerResult.addKPosition(e);
        }
    }

    return kmerResult;
}
#else
//======================================================================
ft::KmerClass FmIndex::search(const std::string& kmer,
                              u_int maxOcc)
{
    // This code is executed in a different thread for multithreaded
    // executions and in main thread for monothreaded applications

    ft::KmerClass kmerResult = ft::KmerClass(kmer);

    size_t occ_begin, occ_end, occs;
    occs = backward_search(_index, 0, _index.size()-1, kmer.begin(),  kmer.end(), occ_begin, occ_end);

    kmerResult.setOCC(occs);

    // if number kmers > max, flag kmer as "over counted"
    if (occs > maxOcc ) {
        kmerResult.addKFlag(ft::FlagType::OCK);
    }
    if (occs > 0  && occs <= maxOcc) {
        for (size_t i=0; i < occs; ++i) {
            kmerResult.addKPosition(_index[occ_begin+i]);
        }
    }
    return kmerResult;
}
#endif

//======================================================================
std::pair<fs::path, fs::path> FmIndex::createFMIndex(const algo::IndexProps& _props, const fs::path& preprocessedFasta)
{
    std::lock_guard<std::mutex> lock(_mtx);
    std::string ppfname = preprocessedFasta.stem();

    fs::path outputIndex = _props.getOutputFolder();
    std::string newfilename = _props.getIndexName() + "_" + ppfname;

    csa_wt<wt_huff<rrr_vector<256>>, 512, 1024> tmpIndex;
    outputIndex /= newfilename;
    outputIndex.replace_extension("fm9");

    ft::LogClass::Log << "creating index for " << ppfname << " at " << outputIndex << std::endl;
    if (preprocessedFasta.empty())
    {
        throw std::runtime_error( "Error: Preprocessed Fasta File is empty " + preprocessedFasta.string());
    }

    if (!exists(preprocessedFasta))
    {
        throw std::runtime_error( "Error: Preprocessed Fasta File doesn't exist " + preprocessedFasta.string());
    }
    if (fs::exists(outputIndex))
    {
        throw std::runtime_error( "Error: Index already exists " + outputIndex.string());
    }

    if (!sdsl::load_from_file(_index, outputIndex)) {

        std::ifstream in(preprocessedFasta);
        if (!in) {
            throw std::runtime_error( "Error: Cannot load to ifstream " + preprocessedFasta.string());
        }
        if (!fs::exists(_props.getOutputFolder())){

            throw std::runtime_error( "Error: output Folder doesnt exist " + _props.getOutputFolder().string());
        }

        try {
            construct(tmpIndex, preprocessedFasta, 1);
        } catch (std::exception& e) {
            std::cout << "Error in FM Index Creation " << e.what() << std::endl;
            throw std::runtime_error(e.what());
        }

        try {
            store_to_file(tmpIndex, outputIndex);
        } catch (std::exception& e) {
            std::cout << "Error while saving FM Index " << e.what() << std::endl;
        }

    }

    return std::make_pair(outputIndex, preprocessedFasta);
}

//======================================================================
void FmIndex::loadIndexFromFile(const fs::path& indexname)
{
    ft::LogClass::Log << "load index from file " << indexname << std::endl;
    if (!fs::exists(indexname)){
        std::runtime_error("cannot find index at " + indexname.string());
    }
    if (!sdsl::load_from_file(_index, fs::absolute(indexname).string())) {
        std::runtime_error("Error loading the index, please provide the index file " + indexname.string());
    }
    ft::LogClass::Log << "Index loaded " << _index.size() << std::endl;
}
//======================================================================
void FmIndex::parallelFmIndex(algo::IndexProps& _props)
{
    //   fs::path createFMIndex(algo::IndexProps& _props, const fs::path& preprocessedFasta);
    std::cout << "Running FM Index" << std::endl;
    std::vector<std::future<std::pair<fs::path, fs::path>>> operations;
    std::map<fs::path, std::pair<u_int, u_int>> _ppfs = _props.getPreProcessedFastas();

    if  (_props.getNumOfIndexes() != _ppfs.size()){
        throw std::runtime_error("Error: wrong number of files found ");
    }
    for (auto _ppf : _props.getPreProcessedFastas()){
        ft::LogClass::Log << "indexing " << _ppf.first << std::endl;
        operations.push_back(std::async(std::launch::async,
                                        &FmIndex::createFMIndex,
                                        this,
                                        _props,
                                        _ppf.first));
    }

    for (size_t i = 0; i < _ppfs.size(); i++){
        std::pair<fs::path, fs::path> output = operations[i].get();
        fs::path outputIndex = output.first;
        fs::path outputPPF = output.second;
        u_int offset = _props.getOffsetForIndex(outputPPF);
        ft::LogClass::Log << "index created " << outputIndex << " with offset " << offset <<  std::endl;
        _props.addToIndexSet(outputIndex, offset);
       }
    fs::path indexPropsINI =  _props.getOutputFolder();
    indexPropsINI /= _props.getIndexName() + "_" + _props.getReadSetName() + "_index.ini";

    _props.saveIndexProps(indexPropsINI);
}

int FmIndex::indexCount()
{
    return _index.size();
}

//======================================================================
FmIndex::~FmIndex()
{
}
}
