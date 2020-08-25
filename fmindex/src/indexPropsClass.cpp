#include "indexPropsClass.h"

namespace algo {
IndexProps::IndexProps()
   :IndexProps(false) 
{ }

IndexProps::IndexProps(bool verbose)
    : _verbose(verbose)
{
    _outputFolder = fs::current_path();
}


std::string IndexProps::createBash(){
    std::cout << "build directory " << _buildDir << std::endl;
    fs::path pathToUtils = _buildDir;
    fs::path preprocess = _buildDir;
    preprocess /= "preprocess.sh";
    std::string bashargs = "bash ";
    bashargs += preprocess.string();
    bashargs += " -r " + _R1.string();
    bashargs += " -o " + _outputFolder.string();
    bashargs += " -f " + _outputFile.stem().string();

    pathToUtils  /= "bin/";
    bashargs += " -u " + pathToUtils.string();
    if (_numOfIndexes > 1 ) {bashargs += " -n " + std::to_string(_numOfIndexes);}
    if (_readFileType == algo::FileType::GZ) {bashargs += " -z 1"; }
    if (_pairedReads) {bashargs += " -p " + _R2.string() ;}
    if (_revComp){bashargs += " -c 1";}

    return bashargs;
}

void IndexProps::printToStdOut(std::string outputString) const{
    if (_verbose)
    { std::cout << outputString << std::endl;  }
}
//================= PARAMETER GETTERS ========================
uint IndexProps::getNumOfIndexes() const {return _numOfIndexes;}
uint IndexProps::getNumOfReads() const {return _numOfReads;}

bool IndexProps::getDelFQFlag() const {return _delFQ;}
bool IndexProps::getDelFastaFlag() const {return _delFasta;}
bool IndexProps::getRevCompFlag() const {return _revComp;}
bool IndexProps::getPairedReadsFlag() const {return _pairedReads;}

const std::string& IndexProps::getReadSetName() const {return _readSetName;}
const std::string& IndexProps::getIndexFileName() const {return _indexFileName;}
const algo::FileType& IndexProps::getReadFileType()const {return _readFileType;}

//==================== PARAMETER SETTERS ===================
void IndexProps::setNumOfIndexes(uint numOfIndexes) {_numOfIndexes = numOfIndexes;}
void IndexProps::setNumOfReads(uint numOfReads) {_numOfReads = numOfReads;}

void IndexProps::setDelFQFlag(bool delFQ){ _delFQ = delFQ;}
void IndexProps::setDelFastaFlag(bool delFasta){ _delFasta = delFasta;}
void IndexProps::setRevCompFlag(bool revComp){ _revComp = revComp;}
void IndexProps::setPairedReadsFlag(bool pairedReads){ _pairedReads = pairedReads;}
void IndexProps::setVerboseFlag(bool verbose){_verbose = verbose;}
void IndexProps::setReadSetName(const std::string readSetName){_readSetName = readSetName;}
void IndexProps::setReadFileType(const algo::FileType& readFileType){_readFileType = readFileType;}
void IndexProps::setIndexFileName(const std::string indexFileName){_indexFileName = indexFileName;}
//====================== FILE GETTERS ======================
const fs::path& IndexProps::getBuildDir() const {return _buildDir;}
const fs::path& IndexProps::getOutputFile() const {return _outputFile;}
const fs::path& IndexProps::getOutputFolder()const {return _outputFolder;}

const fs::path& IndexProps::getReadFQ()const {return _readFQ;}
const fs::path& IndexProps::getR1()const {return _R1;}
const fs::path& IndexProps::getR2()const {return _R2;}

const std::map<fs::path, std::pair<u_int, u_int>>& IndexProps::getPreProcessedFastas()const {return _ppFSet;}
const std::map<fs::path, uint>& IndexProps::getIndexSet() const {return _indexSet;}

//====================== FILE SETTERS ======================
void IndexProps::setReadFQ(const fs::path& readFile)
{   printToStdOut("Read FQ set " + fs::absolute(readFile).string());
    _readFQ = fs::absolute(readFile);   }

bool IndexProps::setR1(const fs::path& readFile)
{
    fs::path r1 = fs::absolute(readFile);
    if (!fs::exists(r1)) {
        printToStdOut("R1 doesn't exist at " +r1.string());
        return false;
    }
    _R1 = r1;
    printToStdOut("Set R1 " + _R1.string());
    return true;
}

bool IndexProps::setR2(const fs::path& readFile)
{
    fs::path r2 = fs::absolute(readFile);
    if (!fs::exists(r2)) {
        printToStdOut("R2 doesn't exist at " +r2.string());
        return false;
    }
    _R2 = r2;
    printToStdOut("Set R2 " + _R2.string());
    return true;
}


void IndexProps::delR1(){
    fs::remove(_R1);
}
void IndexProps::delR2(){
    fs::remove(_R2);
}
void IndexProps::delReadFQ(){
    fs::remove(_readFQ);
}
void IndexProps::delReadFastas(){
    for (auto _ppf : _ppFSet){
        fs::remove(_ppf.first);
    }
}
void IndexProps::delSpecificReadFasta(const fs::path& _preProcessedFasta){
    fs::remove(_preProcessedFasta);
}

void IndexProps::setBuildDir(const fs::path &buildDir)
{        _buildDir = buildDir;   }

void IndexProps::setOutputFile()
{
    fs::path outputFile = _outputFolder;
    outputFile /= _indexFileName ;

    if (!_readSetName.empty()) {
         outputFile += "_" + _readSetName;
    }

    outputFile.replace_extension(".fm9");
    _outputFile = outputFile;

    setOutputFolder(outputFile.parent_path());
    printToStdOut("output file " + _outputFile.string());
}

void IndexProps::setOutputFolder(const fs::path& outputFolder)
{
    fs::path outfolder = fs::absolute(outputFolder);
printToStdOut("setOutputFolder " + outfolder.string());
    if (!fs::exists(outfolder)){
         try {
             fs::create_directory(outfolder);
         } catch (std::exception& e ) {
             throw std::runtime_error("Cannot create output folder " + outfolder.string());
         }
    }
    _outputFolder = outfolder;
}

void IndexProps::addPPF(fs::path _ppf, uint start, uint end){
    printToStdOut("add to _ppFSet " + _ppf.string() + " start " + std::to_string(start) + " end " + std::to_string(end));
    _ppFSet[_ppf] = std::make_pair(start, end);
    if (_ppFSet.count(_ppf) == 0)
    {
        throw std::runtime_error("Couldnt add " + _ppf.string() + "to _ppFSet");
    }
}
void IndexProps::setPreProcessedFastas(std::map<fs::path, std::pair<u_int, u_int>>& preProcessedFastas)
{       _ppFSet = preProcessedFastas; }
void IndexProps::setIndexSet(std::map<fs::path, uint>& indexes)
{        _indexSet = indexes;   }
void IndexProps::addToIndexSet(fs::path index, uint offset){
    _indexSet[index] = offset;
}


//====================== FILE PREPROCESS ======================
void IndexProps::createPPFSet(){

    fs::path ppFN = _outputFile;

    ppFN.replace_extension(".fasta");
    printToStdOut( "creating _ppFN " + ppFN.string());

    u_int start = 0;
    if (_numOfIndexes > 1){
        for (u_int i=0; i<_numOfIndexes; ++i)
        {
            std::string newfilename = ppFN.stem();
            newfilename += "_" + std::to_string(i) + ppFN.extension().string();

            fs::path tmpPPF = ppFN;
            tmpPPF.replace_filename(newfilename);
            printToStdOut("tmp PPF " + tmpPPF.string() + " " + newfilename);

            u_int lines = countLines(tmpPPF);
            printToStdOut("number of lines " + std::to_string(lines));
            u_int end = start + lines;
            addPPF(tmpPPF, start, end);
            start += lines;
        }
    } else {
    printToStdOut("tmp PPF " + ppFN.string());
        u_int lines = countLines(ppFN);
        printToStdOut("number of lines " + std::to_string(lines));
        addPPF(ppFN, 0, lines);
    }

}

//====================== INDEX PROPS I/O ======================
void IndexProps::saveIndexProps(const fs::path& _indexPropsFile) const {

    std::string  savePath = _indexPropsFile.string();
//    if (_indexPropsFile.parent_path() == _outputFolder){
//        printToStdOut("save path for " + _indexPropsFile.string() + " is not in set outputFolder " + _outputFolder.string());
//        savePath = _outputFolder;
//        savePath /= _indexPropsFile;
//        printToStdOut("updated save path to " + savePath.string());
//    }
    printToStdOut("saving index properties " + savePath);

    QSettings settings(_indexPropsFile.c_str(), QSettings::NativeFormat);

    settings.setValue("readFQ", QString::fromStdString(_readFQ.string()));
    settings.setValue("R1", QString::fromStdString(_R1.string()));
    settings.setValue("R2", QString::fromStdString(_R2.string()));
    settings.setValue("outputFile", QString::fromStdString(_outputFile.string()));
    settings.setValue("indexFileName", QString::fromStdString(_indexFileName));
    settings.setValue("readSetName", QString::fromStdString(_readSetName));
    settings.setValue("indexDirectory", QString::fromStdString(_outputFolder.string()));
    settings.setValue("buildDirectory", QString::fromStdString(_buildDir.string()));
    settings.setValue("numOfReads", _numOfReads);
    settings.setValue("numOfIndexes", _numOfIndexes);
    settings.setValue("revComp", _revComp);
    settings.setValue("pairedReads", _pairedReads);
    settings.setValue("delFQ", _delFQ);
    settings.setValue("delFasta", _delFasta);

    settings.beginWriteArray("IndexFiles");
    int i = 0;
    for (auto index : _indexSet) {
        fs::path indexFile = index.first;
        u_int offset = index.second;
        settings.setArrayIndex(i);
        settings.setValue("fileName", indexFile.string().c_str() );
        settings.setValue("offset", offset);
        ++i;
        }
    settings.endArray();

    if (_verbose){
    std::cout << "Properties saved to Index File     " <<  std::endl;
    std::cout << "Paired Reads      : " << settings.value("pairedReads").toString().toStdString() <<  std::endl;
    std::cout << "reverse Comp      : " << settings.value("revComp").toString().toStdString() <<  std::endl;
    std::cout << "build Directory   : " << settings.value("buildDirectory").toString().toStdString() <<  std::endl;
    std::cout << "index Directory   : " << settings.value("indexDirectory").toString().toStdString() <<  std::endl;
    std::cout << "Index File Name   : " << settings.value("indexFileName").toString().toStdString() <<  std::endl;
    std::cout << "read Set Name     : " << settings.value("readSetName").toString().toStdString() <<  std::endl;
    std::cout << "Read FQ           : " << settings.value("readFQ").toString().toStdString() <<  std::endl;
    std::cout << "Number of Reads   : " << settings.value("numOfReads").toString().toStdString() <<  std::endl;
    std::cout << "Number of Indexes : " << settings.value("numOfIndexes").toString().toStdString() <<  std::endl;
    if (_pairedReads)
        {std::cout << "R1                : " << settings.value("R1").toString().toStdString() <<  std::endl;
         std::cout << "R2                : " << settings.value("R2").toString().toStdString() <<  std::endl;
        }

    }

}


//====================== INDEX PROPS I/O ======================
void IndexProps::loadFromIni(const fs::path inifile){
    QSettings isettings(inifile.string().c_str(), QSettings::IniFormat);
    bool _pairedReads = isettings.value("pairedReads").toBool();
    bool _indexRevComp = isettings.value("revComp").toBool();
    fs::path _buildDir = isettings.value("buildDirectory").toString().toStdString();
    fs::path _indexDir = isettings.value("indexDirectory").toString().toStdString();
    std::string _readSetName = isettings.value("readSetName").toString().toStdString();
    std::string _indexFileName = isettings.value("indexFileName").toString().toStdString();
    std::string _inputFastQ;
    if (_pairedReads){
        _inputFastQ = isettings.value("R1").toString().toStdString();
       std::string _R1 = isettings.value("R1").toString().toStdString();
       std::string _R2 = isettings.value("R2").toString().toStdString();
    } else {
       _inputFastQ = isettings.value("readFQ").toString().toStdString();
    }

    u_int _numOfReads = isettings.value("numOfReads").toUInt();
    u_int _numOfIndexes = isettings.value("numOfIndexes").toUInt();

    std::map<fs::path, uint> indexSet;

    int size = isettings.beginReadArray("IndexFiles");
    for (int i = 0; i < size; ++i) {
        isettings.setArrayIndex(i);
        std::string fileName = isettings.value("fileName").toString().toStdString();
        u_int offset = isettings.value("offset").toInt();
        if (_verbose){
            std::cout << "Index " << fileName << " offset: " << offset << std::endl;
        }
        indexSet[fileName] = offset;
    }
    isettings.endArray();

    if (_verbose){
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
    for (auto index : indexSet){
        std::cout << "Index File : " << index.first << " Offset: " << index.second <<  std::endl;
    }
    }

    setR1(_R1);
    setR2(_R2);
    setReadFQ(_inputFastQ);
    setBuildDir(_buildDir);
    setNumOfReads(_numOfReads);
    setNumOfIndexes(_numOfIndexes);
    setIndexSet(indexSet);
    setIndexFileName(_indexFileName);
    setReadSetName(_readSetName);
    setOutputFolder(_indexDir);



}

//======================================================================
void IndexProps::countNumOfReads() {

    uint reads = 0;
    for (auto ppF : _ppFSet)
    {
        uint lines = countLines(ppF.first);
        reads +=lines;
    }
    if (reads == 0)
    {
        throw std::runtime_error("Pre Processed Fasta files contain no reads");
    }
    _numOfReads = reads;

}
//======================================================================
u_int IndexProps::countLines(fs::path fileToCount){
    std::ifstream in(fileToCount);
    u_int n = 0;
    std::string line;

    while (std::getline(in, line))
    {
        ++n;
    }
    in.close();
    return n;

}
//======================================================================
u_int IndexProps::getOffsetForIndex(fs::path indexFile)
{
    fs::path fastaFile = indexFile.replace_extension(".fasta");

    std::pair<u_int, u_int> offset = _ppFSet[fastaFile];

    return offset.first;
}


//======================================================================

IndexProps::~IndexProps()
{}
}
