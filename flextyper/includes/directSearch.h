#ifndef DIRECTSEARCH_H
#define DIRECTSEARCH_H
#include <climits>
#include <set>
#include <bitset>
#include <iostream>
#include <fstream>
#include <chrono>
#include <map>
#include <experimental/filesystem>
#include <QSettings>

#include <fmindex.h>


namespace ft {
namespace fs = std::experimental::filesystem;
/// \struct CmdLineArg
struct KSCmdLineArg {
    fs::path kmerFile;
    std::map<fs::path, uint> indexFiles;

    std::string indexSetName;
    std::string kmerSetName;
    std::string outputFileName;
    uint numOfReads;
    uint maxOccurences = 100000;
    uint maxThreads = 1;
    uint readLength = 100;
    bool pairedReads = false;
    bool indexRevComp = false;
    bool countAsPairs = false;
    bool revCompSearch = false;
    bool iniFile = false;
    bool verbose = false;
};


////////////////////////////////////////////////////////////////////////
/// \class KSearch
/// \brief A class that contains all the properties to directly count kmers
////////////////////////////////////////////////////////////////////////
class KSearch
{
public:
    /// Constructor
    KSearch();

    /// Destructor
    virtual ~KSearch();

    void init(const KSCmdLineArg& KSProps);

    void loadKmers(const fs::path& kmerFile);
    void addResultsFutures(std::map<std::string, ft::KmerClass> & indexResults, ft::KmerClass &tmpResult, uint offset);
    void parallelSearch(const fs::path &indexPath, long long offset);
    void processIndexResults(const std::map<std::string, ft::KmerClass>& indexResult);
    void processResults();
    void writeOutput();

    /// \name Access
    /// Access functions for single kmer and queries
    /// @{
    /// \public
    bool checkForKmer(const std::string& testKmer) const;

    const ft::KmerClass& getKmer(const std::string& kmer) const;
    void addKmer(const std::string &kmer);

    void addKmerResults(const ft::KmerClass& kmerResult);
    int calculateKmerCount(const KmerClass& kmer);
    /// @}
    ///
    ///


 private:
    fs::path _outputFile;

    fs::path _kmerFile;

    uint _numOfReads;
    uint _readLength;
    uint _maxOcc;
    uint _maxThreads;
    bool _verbose;
    bool _pairedReads;
    bool _indexRevComp;
    bool _countAsPairs;
    bool _revCompSearch;
    std::map<fs::path, uint> _indexSet;
    std::unordered_map<std::string, ft::KmerClass> _kmerSet;
    std::vector<std::map<std::string, ft::KmerClass>> _searchResults;

    void createKmer(const std::string& kmer);
    ft::KmerClass* findKmer(const std::string& kmer);



};

}
#endif // DIRECTSEARCH_H
