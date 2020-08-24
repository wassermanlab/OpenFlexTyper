#ifndef INDEXPROPSCLASS_H
#define INDEXPROPSCLASS_H
#include <set>
#include <iostream>
#include <fstream>
#include <map>
#include <experimental/filesystem>
#include <QSettings>


namespace fs = std::experimental::filesystem;


namespace algo {


enum FileType {FQ = 1, FA, GZ};

class IndexProps{
public:
    IndexProps();
    IndexProps(bool verbose);

    virtual ~IndexProps();

    /// Properties ///
    fs::path _readFQ;
    fs::path _R1;
    fs::path _R2;
    std::map<fs::path, std::pair<u_int, u_int>> _ppFSet; //this is the set of pre process fasta files, plus start, end read numbers created by preprocess.sh

    fs::path _outputFile;
    fs::path _outputFolder; //where to save the indexes and ini file
    fs::path _buildDir;

    std::map<fs::path, uint> _indexSet; //this is the set of generated index files and their offsets

    uint _numOfReads;
    uint _numOfIndexes = 1;

    bool _revComp = 0;
    bool _pairedReads = 0;
    bool _delFQ = 0;
    bool _delFasta= 0;
    bool _verbose = 0;

    std::string _readSetName;
    algo::FileType _readFileType;
    std::string _indexFileName = "Index";
    std::string createBash();

    void printToStdOut(std::string) const;

    /// Parameter Getters ///
    uint getNumOfIndexes() const;
    uint getNumOfReads() const;

    bool getDelFQFlag() const;
    bool getDelFastaFlag() const;
    bool getRevCompFlag() const;
    bool getPairedReadsFlag() const;

    const std::string& getReadSetName() const;
    const std::string& getIndexFileName() const;
    const algo::FileType& getReadFileType() const;

    /// Parameter Setters ///
    void setNumOfIndexes(uint numIndexes);
    void setNumOfReads(uint numOfReads);

    void setDelFQFlag(bool delFQFlag);
    void setDelFastaFlag(bool delFastaFlag);
    void setRevCompFlag(bool revCompFlag);
    void setPairedReadsFlag(bool pairedReads);
    void setVerboseFlag(bool verbose);
    void setReadSetName(const std::string readSetName);
    void setReadFileType(const algo::FileType& readFileType);

    /// File Getters ///
    const fs::path& getReadFQ() const;
    const fs::path& getR1() const;
    const fs::path& getR2() const;

    const fs::path& getBuildDir() const;
    const fs::path& getOutputFile() const;
    const fs::path& getOutputFolder() const;

    const std::map<fs::path, std::pair<u_int, u_int>>& getPreProcessedFastas() const;
    const std::map<fs::path, uint>& getIndexSet() const;

    /// File Setters ///
    void setReadFQ(const fs::path& readFQ);
    void setR1(const fs::path& r1);
    void setR2(const fs::path& r2);

    void delR1();
    void delR2();
    void delReadFQ();
    void delReadFastas();
    void delSpecificReadFasta(const fs::path& _preProcessedFasta);

    void setBuildDir(const fs::path& buildDir);
    void setIndexFileName(const std::string indexFileName);
    void setOutputFile();
    void setOutputFolder(const fs::path& outputFolder);

    void setPreProcessedFastas(std::map<fs::path, std::pair<u_int, u_int>>& _ppFSet);
    void addPPF(fs::path _ppf, uint start, uint end);
    void setIndexSet(std::map<fs::path, uint>& indexes);
    void addToIndexSet(fs::path index, uint offset);

    /// File Preprocess ///
    void createPPFSet();

    /// Index Props I/O ///
    void countNumOfReads();
    u_int countLines(fs::path fileToCount);
    void saveIndexProps(const fs::path& indexPropsFile);
    void loadFromIni(const fs::path inifile);
    u_int getOffsetForIndex(fs::path indexFile);

};


}
#endif // INDEXPROPSCLASS_H
