#include "indexPropsClass.h"

namespace algo {
IndexProps::IndexProps(){}

IndexProps::IndexProps(bool verbose)
    : _verbose(verbose)
{}

std::string IndexProps::createBash(){
    std::string bashargs = "bash preprocess.sh";
    bashargs += " -r " + fs::absolute(_R1).string();
    bashargs += " -o " + fs::absolute(_outputFolder).string();
    bashargs += " -f " + _outputFile.string();
    fs::path pathToUtils = _buildDir;
    pathToUtils  /= "bin/";
    bashargs += " -u " + pathToUtils.string();
    if (_numOfIndexes > 1 ) {bashargs += " -n " + std::to_string(_numOfIndexes);}
    if (_readFileType == algo::FileType::GZ) {bashargs += " -z 1"; }
    if (_pairedReads) {bashargs += " -p " + fs::absolute(_R2).string() ;}
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

void IndexProps::setR1(const fs::path& readFile)
{   printToStdOut("Read 1 set " + fs::absolute(readFile).string());
    _R1 = fs::absolute(readFile);
    if (!fs::exists(_R1))
    {
     printToStdOut("R1 doesnt exist at " +_R1.string());
     fs::path r1 = fs::current_path();
     r1 /= readFile;

     if (fs::exists(r1))
      {
         printToStdOut("R1 exists at " +r1.string());
         _R1 = fs::absolute(r1);
      }
    }
}
void IndexProps::setR2(const fs::path& readFile)
{   printToStdOut("Read 2 set " + fs::absolute(readFile).string());
    _R2 = fs::absolute(readFile);   }


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

void IndexProps::setOutputFile(const std::string outputFileName)
{
    printToStdOut("output Folder " + _outputFolder.string());
    fs::path outputFile = _outputFolder;
    outputFile /=outputFileName;
    printToStdOut("output file " + outputFile.string());
    _outputFile = outputFile;
    if (!fs::exists(_outputFile.parent_path())){
     printToStdOut("creating output Folder " +_outputFolder.string());
     fs::create_directory(_outputFolder);
    }

    //check permission to create files
    fs::path tmpOutputFile = _outputFolder;
    tmpOutputFile /="test123456789.tsv";
    std::ofstream(tmpOutputFile.string());
    if (!fs::exists(tmpOutputFile))
    {
        fs::remove(tmpOutputFile);
        throw std::runtime_error("Cannot create files in output folder " + _outputFolder.string());
    }
    fs::remove(tmpOutputFile);
}

void IndexProps::setOutputFolder(const fs::path& outputFolder)
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

    fs::path ppFN = fs::absolute(_outputFile);

    printToStdOut( "creating _ppFN " + ppFN.string());
    ppFN.replace_extension(".fasta");

    printToStdOut( "creating _ppFSet for " + ppFN.string());
    u_int start = 0;
    if (_numOfIndexes > 1){
        for (u_int i=0; i<_numOfIndexes; ++i)
        {
            fs::path tmpPPF = ppFN;
            printToStdOut("tmp PPF " + tmpPPF.string());
            std::string tmpPPFName = ppFN.stem();
             printToStdOut( "tmp PPFName " + tmpPPFName);
            tmpPPFName += "_" + std::to_string(i);
            tmpPPF.replace_filename(tmpPPFName);
            tmpPPF.replace_extension(".fasta");
            printToStdOut( "tmp PPF new " + tmpPPF.string());
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

    fs::path savePath = _indexPropsFile;
//    if (_indexPropsFile.parent_path() == _outputFolder){
//        printToStdOut("save path for " + _indexPropsFile.string() + " is not in set outputFolder " + _outputFolder.string());
//        savePath = _outputFolder;
//        savePath /= _indexPropsFile;
//        printToStdOut("updated save path to " + savePath.string());
//    }
    printToStdOut("saving index properties " + savePath.string());

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

            throw std::runtime_error("R1 and R2 do not contain the same number of reads. R1 has " + std::to_string(nR1) + " and R2 has " + std::to_string(nR2));
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
