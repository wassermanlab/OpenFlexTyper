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

#if ENABLE_FAST_POSITION
// _index[] is mapped to csa_wt.hpp operator[]
// To speed up, other positions are pre-filled.
// FmIndex::hits() will show how effective is the pre-fill.
size_t FmIndex::getPosition(size_t i)
{
    if (i >= _index.size())
        return _index[i];

    size_t _i = i;
    if (positions[i] == 0) {
        size_t off = 0;
        while (!_index.sa_sample.is_sampled(i)) {
            i = _index.lf[i];
            ++off;
        }
        //now pre-fill other positions
        i = _i;
        do {
            size_t result = _index.sa_sample[i];
            if (result + off < _index.size()) {
                positions[i] = result + off;
            } else {
                positions[i] = result + off - _index.size();
            }
            i = _index.lf[i];

            if (i >= _index.size())
                break;  //stop if index is beyond array size

        } while (off > 0 && off-- < 4000); //skip loop if 'off' is a large number
    }
    else
        pos_hits++;
 
    return positions[_i];
}
#endif

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
        //occ_end is not always correct
        occ_end = occ_begin + occs;
        for (size_t i=occ_begin; i < occ_end; ++i) {
#if ENABLE_FAST_POSITION
            kmerResult.addKPosition(getPosition(i));
#else
            kmerResult.addKPosition(_index[i]);
#endif
        }
    }
    return kmerResult;
}

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
        ft::LogClass::ThrowRuntimeError("Error: Preprocessed Fasta File is empty " + preprocessedFasta.string());
    }

    if (!exists(preprocessedFasta))
    {
        ft::LogClass::ThrowRuntimeError("Error: Preprocessed Fasta File doesn't exist " + preprocessedFasta.string());
    }
    if (fs::exists(outputIndex))
    {
        ft::LogClass::ThrowRuntimeError( "Error: Index already exists " + outputIndex.string());
    }

    if (!sdsl::load_from_file(_index, outputIndex)) {

        positions.reserve(_index.size());
        positions.assign(0, _index.size());

        std::ifstream in(preprocessedFasta);
        if (!in) {
            ft::LogClass::ThrowRuntimeError("Error: Cannot load to ifstream " + preprocessedFasta.string());
        }
        if (!fs::exists(_props.getOutputFolder())){

            ft::LogClass::ThrowRuntimeError("Error: output Folder doesnt exist " + _props.getOutputFolder().string());
        }

        try {
            construct(tmpIndex, preprocessedFasta, 1);
        } catch (std::exception& e) {
            ft::LogClass::ThrowRuntimeError("Error in FM Index Creation " + std::string(e.what()));
        }

        try {
            store_to_file(tmpIndex, outputIndex);
        } catch (std::exception& e) {
            ft::LogClass::ThrowRuntimeError("Error while saving FM Index " + std::string(e.what()));
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

    positions.reserve(_index.size());
    positions.assign(0, _index.size());
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
