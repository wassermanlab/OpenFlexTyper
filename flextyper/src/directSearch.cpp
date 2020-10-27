#include <set>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include "directSearch.h"

namespace ft {

KSearch::KSearch()
{

}


void KSearch::init(const ft::KSCmdLineArg& kSProps)
{
     _maxOcc = kSProps.maxOccurences;
     _maxThreads = kSProps.maxThreads;
     _readLength = kSProps.readLength;
     _numOfReads = kSProps.numOfReads;
     _pairedReads = kSProps.pairedReads;
     _indexRevComp = kSProps.indexRevComp;
     _countAsPairs = kSProps.countAsPairs;
     _revCompSearch = kSProps.revCompSearch;

     _outputFile = fs::path(kSProps.outputFileName);
     _kmerFile = kSProps.kmerFile;
     _indexSet = kSProps.indexFiles;

     _verbose = kSProps.verbose;

     loadKmers(_kmerFile);

     std::map<fs::path, uint>::iterator it = _indexSet.begin();
     while ( it != _indexSet.end()) {
         fs::path indexPath = it->first;
         uint offset = it->second;
         parallelSearch(indexPath, offset);
         it++;
     }
    writeOutput();

}

void KSearch::loadKmers(const fs::path& kmerFile)
{

    std::cout << "path to kmer file : " <<  kmerFile << std::endl;
    std::ifstream kmerFileStream(kmerFile);
    if (!kmerFileStream.is_open()) {
        LogClass::ThrowRuntimeError( "Couldn't open queryFile");
    }
    std::string line;

    while (getline(kmerFileStream, line)) {
        if (line[0] == '#') continue;
        std::string kmer = line;
        LogClass::Log << "Kmer added " << kmer << std::endl;
        ft::KmerClass newkmer(kmer);
        _kmerSet[kmer] = newkmer;
}

}

//======================================================================
void KSearch::addResultsFutures(std::map<std::string, ft::KmerClass> & indexResults, ft::KmerClass &tmpResult, uint offset)
{
    const std::string& resultkmer = tmpResult.getKmer();
    std::map<std::string, ft::KmerClass>::iterator it = indexResults.find(resultkmer);
    if (it != indexResults.end())
    {
        LogClass::ThrowRuntimeError("addResults " + resultkmer + " already inserted");
    }

    tmpResult.adjustPositionsWithOffset(offset);
    indexResults[tmpResult.getKmer()] = tmpResult;
}

//======================================================
void KSearch::addKmerResults(const ft::KmerClass& kmerResult)
{
    if (!checkForKmer(kmerResult.getKmer())){
        createKmer(kmerResult.getKmer());
    }

    KmerClass* kmer = findKmer(kmerResult.getKmer());

    // add read IDs
    for (ft::ReadID resultID : kmerResult.getReadIDs())
    {
        kmer->addReadID(resultID);
        if (!kmer->hasReadID(resultID))
        {
            std::cout << "Error: couldnt add readID to Kmer" << std::endl;
        }
    }
}

//======================================================
int KSearch::calculateKmerCount(const KmerClass& kmer)
{
    std::set<ft::ReadID> readIDs = kmer.getReadIDs();
    int kmercount = 0;
    if (_countAsPairs){
        std::set<int> pairIDs;
        for (ft::ReadID readID : readIDs){
            pairIDs.insert(readID.first);
        }
        kmercount = pairIDs.size();
    } else {
        kmercount = readIDs.size();
    }
    return kmercount;
}

//======================================================
void KSearch::processIndexResults(const std::map<std::string, ft::KmerClass>& indexResult)
{
    std::map<std::string, ft::KmerClass>::const_iterator it = indexResult.begin();
    while (it != indexResult.end()){
       ft::KmerClass kmerResult = it->second;
       kmerResult.convertPosToReadID( _readLength ,
                                      _numOfReads,
                                     _pairedReads,
                                     _indexRevComp);
       addKmerResults(kmerResult);
       it++;
    }
}



//======================================================================
void KSearch::parallelSearch(const fs::path &indexPath,
                            long long offset)
{
    LogClass::Benchmark benchmark;

    algo::IFmIndex* fmIndex = new algo::FmIndex(_verbose);
    const std::unordered_map<std::string, ft::KmerClass>& kmerMap = _kmerSet;
    std::map<std::string, ft::KmerClass>  indexResults;

    try {
        fmIndex->loadIndexFromFile(indexPath);
    } catch (std::exception& e) {
        LogClass::Log << "(E) load " << e.what() << std::endl;
    }

    LogClass::Log << "(I) parallel: loaded " << indexPath.string() << std::endl;

    // create a vector of futures
    std::vector<std::future<ft::KmerClass>> resultsFutures;
    uint j = 0;
    uint elts = 0;

    std::unordered_map<std::string, ft::KmerClass>::const_iterator it = kmerMap.begin();
    std::cout << "parallelSearch " << kmerMap.size() << std::endl;
    while (it != kmerMap.end())
    {
        std::string kmer = it->first;
        LogClass::Log << "searching for kmer " << kmer << std::endl;
        resultsFutures.push_back(std::async(std::launch::async, &algo::FmIndex::search,
                                                dynamic_cast<algo::FmIndex*>(fmIndex),
                                                kmer, _maxOcc));
        it++;
        if (++j < _maxThreads && it != kmerMap.end()) {
            continue;
        }

        for (auto& e : resultsFutures) {
            e.wait();
            j--;
            ft::KmerClass tmpResult = e.get();
            elts++;
            LogClass::Log << "number of results for " << tmpResult.getKmer() << " " << tmpResult.getKPositions().size() << std::endl;
            addResultsFutures(indexResults, tmpResult, offset);
        }
        resultsFutures.clear();
    }

    _searchResults.push_back(indexResults);
    LogClass::Log  << "(I) number of indexes processed " << indexResults.size() << std::endl;
    benchmark.now("parallelSearch DONE ");
    delete fmIndex;
}

//======================================================
void KSearch::writeOutput()
{
    std::fstream outputFileStream;
    outputFileStream.open(_outputFile, std::ios::out);
    if (!outputFileStream || !outputFileStream.is_open()) {
        LogClass::Log  << "Couldn't open " << _outputFile.string() << std::endl;
    }

    std::ifstream queryFileStream;
    queryFileStream.open(_kmerFile, std::ios::in);

    if (!queryFileStream || !queryFileStream.is_open()) {
        LogClass::Log  << "Couldn't open " << _kmerFile.string() << std::endl;
    }

    std::string line;

    while (getline(queryFileStream, line)) {
        if (line[line.length()-1] == '\n') {
            line.erase(line.length()-1);
        }

        // header line <- might be issue if there is >1 header line
        if (line[0] == '#') {
            std::cout << "line is a header line" << std::endl;
            line.append('\t' + std::string("Count") + '\n');
            outputFileStream << line;
            continue;
        }

        const ft::KmerClass& kmer = getKmer(line);
        u_int kmercount = calculateKmerCount(kmer);
        std::string outputLine = '\t' + std::to_string(kmercount);
        line.append(outputLine);
        line.append("\n");
        outputFileStream << line;

    }
    outputFileStream.close();
}

//======================================================
//================= KMERS ==============================
//======================================================
#define KMERSTART {
bool KSearch::checkForKmer(const std::string &testKmer) const
{
    return (_kmerSet.count(testKmer) > 0);
}

//======================================================
ft::KmerClass* KSearch::findKmer(const std::string& testKmer)
{
    std::unordered_map<std::string, ft::KmerClass>::iterator it = _kmerSet.find(testKmer);
    if (it != _kmerSet.end()) {
        return  &((*it).second);
    } else {return NULL;}
}

//======================================================
const ft::KmerClass& KSearch::getKmer(const std::string& kmerString) const
{
    if (_kmerSet.count(kmerString) == 0) {
        LogClass::ThrowRuntimeError("Kmer Doesnt Exist");
    }
    return  _kmerSet.find(kmerString)->second;
}
//======================================================
void KSearch::addKmer(const std::string &kmer)
{
    if(!checkForKmer(kmer)){
        createKmer(kmer);
    }
}

//======================================================
void KSearch::createKmer(const std::string &kmer)
{
    ft::KmerClass newkmer(kmer);
    _kmerSet[kmer] = newkmer;
}

#define KMERSEND }
KSearch::~KSearch(){}

}
