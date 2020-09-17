#include <set>
#include <iostream>
#include <map>
#include "ftPropsClass.h"

namespace ft {

FTProp::FTProp()
{}

//=============== INIT ==============================

void FTProp::init(const fs::path &pathToQueryFile,
                  uint kmerSize,
                  uint readLength,
                  const fs::path &indexPropsFile,
                  const fs::path &outputFolder,
                  bool refOnly,
                  bool revCompSearch,
                  SearchType searchType,
                  bool multithread,
                  uint overlap,
                  bool returnMatchesOnly,
                  bool kmerCounts,
                  uint stride,
                  uint maxOccurences,
                  uint numOfThreads,
                  bool flagOverCountedKmers,
                  bool flagNonUniqueKmers,
                  bool ignoreNonUniqueKmers,
                  bool countAsPairs,
                  bool crossover,
                  bool printSearchTime,
                  uint maxKmersPerQuery,
                  uint maxTotalKmers,
                  bool printInputs,
                  bool matchingReads)
{
    _pathToQueryFile = pathToQueryFile;
    _kmerSize = kmerSize;
    _readLength = readLength;
    loadIndexProps(indexPropsFile, printInputs);
    setOutputFolder(outputFolder);
    _refOnly = refOnly;
    _revCompSearch = revCompSearch;
    _searchType = searchType;
    _multithread = multithread;
    _overlap = overlap;
    _matchesOnly = returnMatchesOnly;
    _kmerCounts = kmerCounts;
    _stride = stride;
    _maxOccurences = maxOccurences;
    _maxThreads = numOfThreads;
    _overcounted = flagOverCountedKmers;
    _nonUnique = flagNonUniqueKmers;
    _ignoreNonUniqueKmers = ignoreNonUniqueKmers;
    _countAsPairs = countAsPairs;
    _crossover = crossover;
    _printSearchTime = printSearchTime;
    _maxKmersPerQuery = maxKmersPerQuery;
    _maxTotalKmers = maxTotalKmers;
    _matchingReads = matchingReads;

    fs::path queryOutputFile = _outputFolder;
    fs::path queryFileName = _pathToQueryFile.filename();
    queryFileName.replace_extension();
    queryOutputFile /= queryFileName+= std::string("_") += _readSetName += "_Results.tsv";
    _outputFile = queryOutputFile;

    if (printInputs){
        std::cout << "pathToQueryFile               : " << pathToQueryFile <<  std::endl;
        std::cout << "kmerSize                      : " << kmerSize <<  std::endl;
        std::cout << "readLength                    : " << readLength <<  std::endl;
        std::cout << "indexPropsFile                : " << indexPropsFile <<  std::endl;
        std::cout << "outputFolder                  : " << outputFolder <<  std::endl;
        std::cout << "refOnly                       : " << refOnly <<  std::endl;
        std::cout << "revCompSearch                 : " << revCompSearch <<  std::endl;
        std::cout << "searchType                    : " << searchType <<  std::endl;
        std::cout << "multithread                   : " << multithread <<  std::endl;
        std::cout << "overlap                       : " << overlap <<  std::endl;
        std::cout << "return_only_positive_matches  : " << returnMatchesOnly <<  std::endl;
        std::cout << "kmerCounts                    : " << kmerCounts << std::endl;
        std::cout << "stride                        : " << stride << std::endl;
        std::cout << "maxOccurences                 : " << maxOccurences << std::endl;
        std::cout << "numOfThreads                  : " << numOfThreads << std::endl;
        std::cout << "flagOverCountedKmers          : " << flagOverCountedKmers << std::endl;
        std::cout << "flagNonUniqueKmers            : " << flagNonUniqueKmers << std::endl;
        std::cout << "ignoreNonUniqueKmers          : " << ignoreNonUniqueKmers << std::endl;
        std::cout << "countAsPairs                  : " << countAsPairs << std::endl;
        std::cout << "printSearchTime               : " << printSearchTime << std::endl;
        std::cout << "maxKmersPerQuery              : " << maxKmersPerQuery << std::endl;
        std::cout << "maxTotalKmers                 : " << maxTotalKmers << std::endl;
        std::cout << "matchingReads                 : " << matchingReads << std::endl;
        std::cout << "Query search results will be save in " << _outputFile << std::endl;
    }
    if (FTProp::Log.is_open()){
        Log << "======== Settings " << "======== " << std::endl;
        FTProp::Log << "pathToQueryFile               : " << pathToQueryFile <<  std::endl;
        FTProp::Log << "kmerSize                      : " << kmerSize <<  std::endl;
        FTProp::Log << "readLength                    : " << readLength <<  std::endl;
        FTProp::Log << "indexPropsFile                : " << indexPropsFile <<  std::endl;
        FTProp::Log << "outputFolder                  : " << outputFolder <<  std::endl;
        FTProp::Log << "refOnly                       : " << refOnly <<  std::endl;
        FTProp::Log << "revCompSearch                 : " << revCompSearch <<  std::endl;
        FTProp::Log << "searchType                    : " << searchType <<  std::endl;
        FTProp::Log << "multithread                   : " << multithread <<  std::endl;
        FTProp::Log << "overlap                       : " << overlap <<  std::endl;
        FTProp::Log << "return_only_positive_matches  : " << returnMatchesOnly <<  std::endl;
        FTProp::Log << "kmerCounts                    : " << kmerCounts << std::endl;
        FTProp::Log << "stride                        : " << stride << std::endl;
        FTProp::Log << "maxOccurences                 : " << maxOccurences << std::endl;
        FTProp::Log << "numOfThreads                  : " << numOfThreads << std::endl;
        FTProp::Log << "flagOverCountedKmers          : " << flagOverCountedKmers << std::endl;
        FTProp::Log << "flagNonUniqueKmers            : " << flagNonUniqueKmers << std::endl;
        FTProp::Log << "ignoreNonUniqueKmers          : " << ignoreNonUniqueKmers << std::endl;
        FTProp::Log << "countAsPairs                  : " << countAsPairs << std::endl;
        FTProp::Log << "printSearchTime               : " << printSearchTime << std::endl;
        FTProp::Log << "maxKmersPerQuery              : " << maxKmersPerQuery << std::endl;
        FTProp::Log << "maxTotalKmers                 : " << maxTotalKmers << std::endl;
        FTProp::Log << "matchingReads                 : " << matchingReads << std::endl;
        FTProp::Log << "Query search results will be save in " << _outputFile << std::endl;
    }
}

void FTProp::setVerbose(bool verbose)
{
    _verbose = verbose;
}
bool FTProp::isVerbose() const
{
    return _verbose;
}
//================= INIT From Q SETTINGS ========================
void FTProp::initFromQSettings (std::string configFile, bool printInputs){

    QString m_sSettingsFile(configFile.c_str());
    QSettings settings(m_sSettingsFile, QSettings::NativeFormat);

    fs::path       pathToQueryFile         = settings.value("queryFile").toString().toStdString();
    uint           kmerSize                = settings.value("kmerSize").toInt();
    uint           readLength              = settings.value("readLength").toInt();
    fs::path       indexPropsFile          = settings.value("indexPropsFile").toString().toStdString();
    fs::path       outputFolder            = settings.value("outputFolder").toString().toStdString();
    bool           refOnly                 = settings.value("refOnly").toBool();
    bool           revCompSearch           = settings.value("revCompSearch").toBool();
    ft::SearchType searchType              = static_cast<ft::SearchType>(settings.value("searchType").toString().toStdString()) ;
    bool           multithread             = settings.value("multithread").toBool();
    bool           matchingReads           = settings.value("matchingReads").toBool();
    uint           overlap                 = settings.value("overlap").toInt();
    bool           returnMatchesOnly       = settings.value("return_only_positive_matches").toBool();
    bool           kmerCounts              = settings.value("kmerCounts").toBool();
    uint           stride                  = settings.value("stride").toInt();
    uint           maxOccurences           = settings.value("maxOccurences").toInt();
    uint           numOfThreads            = settings.value("numOfThreads").toInt();
    bool           flagOverCountedKmers    = settings.value("flagOverCountedKmers").toBool();
    bool           flagNonUniqueKmers      = settings.value("flagNonUniqueKmers").toBool();
    bool           ignoreNonUniqueKmers    = settings.value("ignoreNonUniqueKmers").toBool();
    bool           countAsPairs            = settings.value("countAsPairs").toBool();
    bool           crossover               = settings.value("crossover").toBool();
    bool           printSearchTime         = settings.value("printSearchTime").toBool();
    uint           maxKmersPerQuery        = settings.value("maxKmersPerQuery").toInt();
    uint           maxTotalKmers           = settings.value("maxTotalKmers").toInt();

    init(pathToQueryFile, kmerSize, readLength,
         indexPropsFile, outputFolder, refOnly, revCompSearch,
         searchType, multithread, overlap,
         returnMatchesOnly, kmerCounts, stride,
         maxOccurences, numOfThreads, flagOverCountedKmers, flagNonUniqueKmers,
         ignoreNonUniqueKmers, countAsPairs, crossover, printSearchTime,
         maxKmersPerQuery, maxTotalKmers, printInputs, matchingReads);
}

void FTProp::printToStdOut(const std::string outputString) const {
    if (_verbose){
        std::cout << outputString << std::endl;
    }
}
//================= Load Index Props ========================
void FTProp::loadIndexProps(const fs::path &_indexPropsFile, bool printInputs){
    QSettings isettings(_indexPropsFile.string().c_str(), QSettings::IniFormat);

    _pairedReads = isettings.value("pairedReads").toBool();
    _indexRevComp = isettings.value("revComp").toBool();
    _buildDir = isettings.value("buildDirectory").toString().toStdString();
    _indexDir = isettings.value("indexDirectory").toString().toStdString();
    _readSetName = isettings.value("readSetName").toString().toStdString();
    _indexFileName = isettings.value("indexFileName").toString().toStdString();

    if (_pairedReads){
       _inputFastQ = isettings.value("R1").toString().toStdString();
       _R1 = isettings.value("R1").toString().toStdString();
       _R2 = isettings.value("R2").toString().toStdString();
    } else {
       _inputFastQ = isettings.value("R1").toString().toStdString();
    }

    _numOfReads = isettings.value("numOfReads").toUInt();
    _numOfIndexes = isettings.value("numOfIndexes").toUInt();

    std::map<fs::path, uint> indexSet;

    int size = isettings.beginReadArray("IndexFiles");
    for (int i = 0; i < size; ++i) {
        isettings.setArrayIndex(i);
        fs::path fileName = isettings.value("fileName").toString().toStdString();
        u_int offset = isettings.value("offset").toInt();
        printToStdOut("index fileName " + fileName.string());
        indexSet[fileName] = offset;
    }
    isettings.endArray();
    _indexSet = indexSet;


    if (printInputs){
    std::cout << "Properties loaded from Index File     " <<  std::endl;
    std::cout << "Paired Reads      : " << _pairedReads <<  std::endl;
    std::cout << "reverse Comp      : " << _indexRevComp <<  std::endl;
    std::cout << "build Directory   : " << _buildDir <<  std::endl;
    std::cout << "index Directory   : " << _indexDir <<  std::endl;
    std::cout << "Index File Name   : " << _indexFileName <<  std::endl;
    std::cout << "read Set Name     : " << _readSetName <<  std::endl;
    std::cout << "Read FQ           : " << _inputFastQ <<  std::endl;
    std::cout << "Number of Reads   : " << _numOfReads <<  std::endl;
    std::cout << "Number of Indexes : " << _numOfIndexes <<  std::endl;
    if (_pairedReads)
        {std::cout << "R1                : " << _R1 <<  std::endl;
         std::cout << "R2                : " << _R2 <<  std::endl;
        }
    for (auto index : _indexSet){
        std::cout << "Index File : " << index.first << " Offset: " << index.second <<  std::endl;
    }
    }

}

//======================================================================
void FTProp::initIndexProps( const bool pairedReads,
                             const bool revComp,
                             fs::path buildDir,
                             fs::path indexDir,
                             std::string indexFileName,
                             std::string readSetName,
                             fs::path inputFastQ,
                             uint numOfReads,
                             uint numOfIndexes,
                             bool printInputs)
{
    _pairedReads = pairedReads;
    _indexRevComp = revComp;
    _buildDir = buildDir;
    _indexDir = indexDir;
    _indexFileName = indexFileName;
    _readSetName = readSetName;
    _inputFastQ = inputFastQ;
    _numOfReads = numOfReads;
    _numOfIndexes = numOfIndexes;

    if (_countAsPairs && !_pairedReads)
    {
        throw std::runtime_error("Error: Cannot count as pairs as input reads arent paired");
    }


    if (printInputs){
    std::cout << "Properties loaded from Index File     " <<  std::endl;
    std::cout << "Paired Reads      : " << _pairedReads <<  std::endl;
    std::cout << "index contains reverse Comp      : " << _indexRevComp <<  std::endl;
    std::cout << "build Directory   : " << _buildDir <<  std::endl;
    std::cout << "index Directory   : " << _indexDir <<  std::endl;
    std::cout << "read Set Name     : " << _readSetName <<  std::endl;
    std::cout << "Read FQ           : " << _inputFastQ <<  std::endl;
    std::cout << "Number of Reads   : " << _numOfReads <<  std::endl;
    std::cout << "Number of Indexes : " << _numOfIndexes <<  std::endl;
    }
}

//======================================================================
void FTProp::addToIndexSet(const fs::path& index, u_int offset){
    std::cout<< "add index to set " << fs::absolute(index) << std::endl;

    if (_indexSet.count(index) == 0){
        _indexSet[index] = offset;
        _numOfIndexes = _indexSet.size();
    }
}

//================= PARAMETER GETTERS ========================
SearchType FTProp::getSearchType() const {return _searchType;}
std::string FTProp::getReadSetName() const{return _readSetName;}
std::string FTProp::getIndexFileName() const{return _indexFileName;}
uint FTProp::getKmerSize() const {return _kmerSize;}
uint FTProp::getOverlap() const {return _overlap;}
uint FTProp::getStride() const {return _stride;}
uint FTProp::getReadLength() const {return _readLength;}
uint FTProp::getMaxOcc() const {return _maxOccurences;}
uint FTProp::getMaxThreads() const {return _maxThreads;}
uint FTProp::getMaxKmersPerQuery() const {return _maxKmersPerQuery;}
uint FTProp::getMaxTotalKmers() const {return _maxTotalKmers;}
uint FTProp::getNumOfIndexes() const {return _numOfIndexes;}
uint FTProp::getNumOfReads() const {return _numOfReads;}

//====================== FLAG GETTERS ======================
bool FTProp::getKmerCountsFlag() const {return _kmerCounts;}
bool FTProp::getMultithreadFlag() const {return _multithread;}
bool FTProp::getRefOnlyFlag() const {return _refOnly;}
bool FTProp::getMatchesOnlyFlag() const {return _matchesOnly;}
bool FTProp::getOverCountedFlag() const {return _overcounted;}
bool FTProp::getNonUniqueFlag() const {return _nonUnique;}
bool FTProp::getIgnoreNonUniqueKmersFlag() const {return _ignoreNonUniqueKmers;}
bool FTProp::getCrossoverFlag() const {return _crossover;}
bool FTProp::getPrintSearchTimeFlag() const {return _matchesOnly;}
bool FTProp::getPairedReadFlag() const {return _pairedReads;}
bool FTProp::getCountAsPairsFlag() const {return _countAsPairs;}
bool FTProp::getRevCompSearchFlag() const {return _revCompSearch;}
bool FTProp::getIndexRevCompFlag() const {return _indexRevComp;}
bool FTProp::getMatchingReadsFlag() const{return _matchingReads;}

//====================== FILE GETTERS ======================
const fs::path& FTProp::getPathToQueryFile() const {return _pathToQueryFile;}
const fs::path& FTProp::getIndexDir() const {return _indexDir;}
const fs::path& FTProp::getOutputFolder()const {return _outputFolder;}
const fs::path& FTProp::getOutputFile() const {return _outputFile;}
const fs::path& FTProp::getInputFastQ()const {return _inputFastQ;}
const std::map<fs::path, uint>& FTProp::getIndexSet() const {return _indexSet;}
const fs::path& FTProp::getBuildDir() const {return _buildDir;}
const fs::path& FTProp::getR1() const{return _R1;}
const fs::path& FTProp::getR2() const{return _R2;}

//====================== FILE GETTERS ======================
void FTProp::setTestProps(const uint numOfReads, const uint readLength, bool revComp, bool countAsPairs){
    _numOfReads = numOfReads;
    _readLength = readLength;
    _indexRevComp = revComp;
    _countAsPairs = countAsPairs;
}

void FTProp::setOutputFolder(const fs::path& outputFolder)
{
    fs::path outfolder;
    if (outputFolder == "" or outputFolder =="."){
        printToStdOut("no output folder set ");
        outfolder = fs::current_path();
    } else if (outputFolder == "../"){
        printToStdOut("set as parent path  " + outputFolder.string());
        outfolder = fs::current_path().parent_path();
    } else {
        printToStdOut("set absolute path as output Folder " + outputFolder.string());
        outfolder = fs::absolute(outputFolder);
    }
    _outputFolder = outfolder;
    printToStdOut(_outputFolder.string());

    if (!fs::exists(_outputFolder)){
     printToStdOut("creating output Folder " +outputFolder.string());
         try {
             fs::create_directory(outputFolder);
         } catch (std::exception& e ) {
             throw std::runtime_error("Cannot create output folder " + _outputFolder.string());
         }
    }

    if (!fs::exists(_outputFolder))
    {
        throw std::runtime_error("Cannot create output folder " + _outputFolder.string());
    }

}

//====================== STATIC FUNCTIONS ======================

std::fstream FTProp::Log;
void FTProp::OpenLog(const std::string& name)
{
    Log.open(name, std::fstream::out);
    if (!Log || !Log.is_open()) {
        std::cout << "Couldn't open " << name << " file" << std::endl;
    }
    auto start = std::chrono::system_clock::now();
    std::time_t start_time = std::chrono::system_clock::to_time_t(start);
    Log << "======== " << std::ctime(&start_time);
}

void FTProp::CloseLog()
{
    Log.close();
}

FTProp::~FTProp()
{
}


}
