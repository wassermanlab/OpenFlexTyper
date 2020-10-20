#ifndef __FM_INDEX_H__
#define __FM_INDEX_H__
#include <time.h>
#include <future>
#include <chrono>
#include <fstream>
#include <vector>
#include <iostream>
#include "ifmindex.h"
#include <sdsl/suffix_arrays.hpp>
#include <mutex>
#include "indexPropsClass.h"

////////////////////////////////////////////////////////////////////////
/// \namespace algo
/// \brief This contains the functions used to interact with the FM index
////////////////////////////////////////////////////////////////////////
namespace algo {

////////////////////////////////////////////////////////////////////////
/// \class FmIndex
/// \brief A class that contains all the functions for use with an FmIndex
////////////////////////////////////////////////////////////////////////
class FmIndex : public IFmIndex {

public:

    /// Constructor
    FmIndex();
    FmIndex(bool verbose);

    /// Destructor
    virtual ~FmIndex();

    /// Generate FM Index
    /// \brief Main function to generate the fm index files
    /// Generate the FmIndex for a preprocessed Fasta File
    /// \public
    /// \param algo::IndexProps Index Properties
    /// \param fs::path filesystem path to the preprocessed Fasta
    /// \return (path to the Index, path to the preprocessed Fasta)
    std::pair<fs::path, fs::path> createFMIndex(const algo::IndexProps& _props, const fs::path& preprocessedFasta);

    /// Load Index
    /// \brief loadIndexFromFile
    /// \param indexname
    /// \public
    void loadIndexFromFile(const fs::path& indexname);

    /// Search
    /// \brief search within an index file for a kmer
    /// \param string Kmer
    /// \param u_int max Occurence, default 200
    /// \return ft::KmerClass
    /// \public
    ft::KmerClass search(const std::string& kmer,
                         u_int maxOcc = 200
                         );

    /// parallel FM Index creation

    /// \brief create all the indexes for an input set
    /// \param algo::IndexProps Index Properties
    /// \public
    void parallelFmIndex(algo::IndexProps& _props);


    int indexCount();

private:

    FmIndex(const FmIndex& other);
    const FmIndex& operator=(const FmIndex& other);

    bool _verbose = 0;

    ////////////////////////////////////////////////////////////////////////
    /// \brief This is the structure of our FmIndex.
    ///        csa     : compressed suffix array
    ///        wt_huff : wavelet tree huffman
    ///        rrr     : rrr bit vector of the FmIndex
    ///        For more information, please refere to :
    ///        https://github.com/simongog/sdsl-lite
    ////////////////////////////////////////////////////////////////////////
    csa_wt<wt_huff<rrr_vector<256>>, 512, 1024> _index;
    long long *_indexPosition;

    ////////////////////////////////////////////////////////////////////////
    /// \brief mtx
    ////////////////////////////////////////////////////////////////////////
    std::mutex _mtx;

    ////////////////////////////////////////////////////////////////////////
    /// \brief _kmerMapSize
    ////////////////////////////////////////////////////////////////////////
    size_t _kmerMapSize;
};
}

#endif // end of __FM_INDEX_H__
