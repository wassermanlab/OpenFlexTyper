#include "indexPropsClass.h"

namespace algo {

IndexProps::IndexProps()
{}

std::string IndexProps::createBash(){
    std::string bashargs = "bash preprocess.sh";
    bashargs += " -r " + _R1.string();
    bashargs += " -o " + _outputFolder.string();
    bashargs += " -f " + _outputFile.string();
    fs::path pathToUtils = _buildDir;
    pathToUtils  /= "bin/";
    bashargs += " -u " + pathToUtils.string();
    if (_numOfIndexes > 1 ) {bashargs += " -n " + std::to_string(_numOfIndexes);}
    if (_readFileType == algo::FileType::GZ) {bashargs += " -z 1"; }
    if (_pairedReads) {bashargs += " -p " + _R2.string() ;}
    if (_revComp){bashargs += " -c 1";}

    return bashargs;
}
//================= PARAMETER GETTERS ========================
uint IndexProps::getNumOfIndexes() const {return _numOfIndexes;}
uint IndexProps::getNumOfReads() const {return _numOfReads;}

bool IndexProps::getDelFQFlag() const {return _delFQ;}
bool IndexProps::getDelFastaFlag() const {return _delFasta;}
bool IndexProps::getRevCompFlag() const {return _revComp;}
bool IndexProps::getPairedReadsFlag() const {return _pairedReads;}

const std::string& IndexProps::getReadSetName() const {return _readSetName;}
const algo::FileType& IndexProps::getReadFileType()const {return _readFileType;}

//==================== PARAMETER SETTERS ===================
void IndexProps::setNumOfIndexes(uint numOfIndexes) {_numOfIndexes = numOfIndexes;}
void IndexProps::setNumOfReads(uint numOfReads) {_numOfReads = numOfReads;}

void IndexProps::setDelFQFlag(bool delFQ){ _delFQ = delFQ;}
void IndexProps::setDelFastaFlag(bool delFasta){ _delFasta = delFasta;}
void IndexProps::setRevCompFlag(bool revComp){ _revComp = revComp;}
void IndexProps::setPairedReadsFlag(bool pairedReads){ _pairedReads = pairedReads;}

void IndexProps::setReadSetName(const std::string readSetName){_readSetName = readSetName;}
void IndexProps::setReadFileType(const algo::FileType& readFileType){_readFileType = readFileType;}

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
{       _readFQ = readFile;   }
void IndexProps::setR1(const fs::path& readFile)
{       _R1 = readFile;   }
void IndexProps::setR2(const fs::path& readFile)
{       _R2 = readFile;   }


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
void IndexProps::setOutputFile(const fs::path& outputFile)
{        _outputFile = outputFile;   }
void IndexProps::setOutputFolder(const fs::path& outputFolder)
{   if (!fs::exists(outputFolder)){
        std::cout << "creating output Folder " << outputFolder << std::endl;
        fs::create_directory(outputFolder);
    }
    _outputFolder = outputFolder;    }
void IndexProps::addPPF(fs::path _ppf, uint start, uint end){
    _ppFSet[_ppf] = std::make_pair(start, end);
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
    fs::path ppFN = _outputFolder;
    ppFN /= _outputFile;
    ppFN.replace_extension(".fasta");
    std::cout << "creating _ppFSet" << std::endl;
    u_int start = 0;
    if (_numOfIndexes > 1){
        for (u_int i=0; i<_numOfIndexes; ++i)
        {
            fs::path tmpPPF = ppFN;
            //std::cout << "tmp PPF " << tmpPPF << std::endl;
            std::string tmpPPFName = ppFN.stem();
            //std::cout << "tmp PPFName " << tmpPPFName << std::endl;
            tmpPPFName += "_" + std::to_string(i);
            tmpPPF.replace_filename(tmpPPFName);
            tmpPPF.replace_extension(".fasta");
            std::cout << "tmp PPF new " << tmpPPF << std::endl;
            u_int lines = countLines(tmpPPF);
            u_int end = start + lines;
            addPPF(tmpPPF, start, end);
            start += lines;
        }


    } else {
        u_int lines = countLines(ppFN);
        addPPF(ppFN, 0, lines);
    }

}

//====================== INDEX PROPS I/O ======================
void IndexProps::saveIndexProps(const fs::path& _indexPropsFile) const {
        std::cout << "saving index properties " << _indexPropsFile << std::endl;


        QSettings settings(_indexPropsFile.string().c_str(), QSettings::NativeFormat);

        settings.setValue("readFQ", QString::fromStdString(_readFQ.string()));
        settings.setValue("R1", QString::fromStdString(_R1.string()));
        settings.setValue("R2", QString::fromStdString(_R2.string()));
        settings.setValue("indexSetName", QString::fromStdString(_outputFile.string()));
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



      }
//======================================================================
void IndexProps::countNumOfReads(){

    //count R1
    fs::path r1Fasta = _outputFolder ;
    r1Fasta /= _R1.filename();
    u_int nR1 = 0;
    u_int nR2 = 0;

    if (_readFileType == algo::FileType::GZ)
    {
        r1Fasta.filename();
        r1Fasta.replace_extension();
        r1Fasta.replace_extension(".fasta");
    }
    else if (_readFileType == algo::FileType::FQ)
    {
        r1Fasta.filename();
        r1Fasta.replace_extension(".fasta");
    }

    nR1 = countLines(r1Fasta);

    //count R2
    if (_pairedReads){
        fs::path r2Fasta = _outputFolder ;
        r2Fasta /= _R2.filename();
        if (_readFileType == algo::FileType::GZ)
        {
            r2Fasta.filename();
            r2Fasta.replace_extension();
            r2Fasta.replace_extension(".fasta");
        }
        else if (_readFileType == algo::FileType::FQ)
        {
            r2Fasta.filename();
            r2Fasta.replace_extension(".fasta");
        }
        nR2 = countLines(r2Fasta);

        if ( nR1 != nR2){
            std::cout << "error: R1 and R2 do not contain the same number of reads" << std::endl;
        }
    }

  _numOfReads = nR1 + nR2;

}
//======================================================================
u_int IndexProps::countLines(fs::path fileToCount){
    std::ifstream in(fileToCount);
    u_int n = 0;
    std::string line;

    while (std::getline(in, line))
    {
        n++;
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
