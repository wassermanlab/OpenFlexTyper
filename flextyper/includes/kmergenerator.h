#ifndef __KMER_GENERATOR_H__
#define __KMER_GENERATOR_H__

#include <set>
#include <string>
#include <map>
#include "ikmergenerator.h"
#include "queryClass.h"
#include "ftPropsClass.h"

namespace ft {

////////////////////////////////////////////////////////////////////////
/// \class KmerGenerator
/// \brief A class that creates the Kmers for a set of input queries
////////////////////////////////////////////////////////////////////////
class KmerGenerator
{

public:
    /// Constructor
    KmerGenerator(const uint& _kmerSize ,
                    const bool& _refOnly ,
                    const SearchType& _searchType ,
                    const uint& _overlap = 0,
                    const uint& _stride = 1,
                    const uint& _maxKmers = 1000000000,
                    const bool& _verbose = false);

    /// Destructor
    virtual ~KmerGenerator();

    /// \fn genSlidingSearchStrings
    /// \brief Generate search strings (i.e. kmers) for a sliding search
    /// \param queryString
    /// \return set of kmers
    virtual std::set<std::string> genSlidingSearchStrings(const std::string& queryString);

    /// \fn genCenteredSearchStrings
    /// \brief Generate search strings (i.e. kmers) for a centered search
    /// \param queryString
    /// \return set of kmers
    virtual std::set<std::string> genCenteredSearchStrings(const std::string& queryString);

    /// \fn genSearchKmers
    /// \brief Generate search strings (i.e. kmers)
    /// \param ft::QueryClass query
    /// \return set of kmers
    virtual std::set<std::string> genSearchKmers(const ft::QueryClass& queryObj);

    /// \name Getters
    /// Constant functions to get properties for Kmer Generation
    /// @{
    /// \public
    /// \fn
    uint getKmerSize() const;
    bool getRefOnly() const;
    SearchType getSearchType() const;
    uint getOverlap() const;
    uint getStride() const;
    uint getMaxKmers() const;
    /// @}

private:
    /// @name Properties
    /// Fixed Properties
    /// @{
    /// \private
    /// \var
    std::map<std::string, uint> _counter;

    uint _kmerSize;
    bool _refOnly;
    SearchType _searchType;
    uint _overlap;
    uint _stride;
    uint _maxKmers;
    bool _verbose;
    /// @}

};
}

#endif // kmerGenerator class
