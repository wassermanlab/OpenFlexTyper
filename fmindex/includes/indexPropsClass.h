#ifndef INDEXPROPSCLASS_H
#define INDEXPROPSCLASS_H
#include <set>
#include <iostream>
#include <fstream>
#include <map>
#include <experimental/filesystem>



namespace fs = std::experimental::filesystem;


namespace algo {


enum FileType {FQ = 1, FA, GZ};

class IndexProps{
public:
    IndexProps();

    virtual ~IndexProps();

    /// Properties ///
    fs::path _readFQ;
    fs::path _R1;
    fs::path _R2;
    std::set<fs::path> _preProcessedFastas; //this is the set of pre process fasta files created by preprocess.sh
    fs::path _outputFile;
    fs::path _outputFolder; //where to save the indexes
    fs::path _buildDir;

    std::set<fs::path> _indexSet; //this is the set of generated index files

    uint _numOfReads;
    uint _numOfIndexes;

    bool _revComp = 0;
    bool _pairedReads = 0;
    bool _delFQ = 0;
    bool _delFasta= 0;

    std::string _readSetName;
    algo::FileType _readFileType;

    std::string createBash();

    /// Parameter Getters ///
    uint getNumOfIndexes() const;
    uint getNumOfReads() const;

    bool getDelFQFlag() const;
    bool getDelFastaFlag() const;
    bool getRevCompFlag() const;
    bool getPairedReadsFlag() const;

    const std::string& getReadSetName() const;
    const algo::FileType& getReadFileType() const;

    /// Parameter Setters ///
    void setNumOfIndexes(uint numIndexes);
    void setNumOfReads(uint numOfReads);

    void setDelFQFlag(bool delFQFlag);
    void setDelFastaFlag(bool delFastaFlag);
    void setRevCompFlag(bool revCompFlag);
    void setPairedReadsFlag(bool pairedReads);

    void setReadSetName(const std::string readSetName);
    void setReadFileType(const algo::FileType& readFileType);

    /// File Getters ///
    const fs::path& getReadFQ() const;
    const fs::path& getR1() const;
    const fs::path& getR2() const;

    const fs::path& getBuildDir() const;
    const fs::path& getOutputFile() const;
    const fs::path& getOutputFolder() const;

    const std::set<fs::path>& getPreProcessedFastas() const;
    const std::set<fs::path>& getIndexSet() const;

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
    void setOutputFile(const fs::path& outputFile);
    void setOutputFolder(const fs::path& outputFolder);

    void setPreProcessedFastas(std::set<fs::path>& preProcessedFastas);
    void addToPreProcessedFastas(const fs::path& preProcessedFastas);
    void setIndexSet(std::set<fs::path>& indexes);
    void addToIndexSet(const fs::path& index);

    void createPPFSet() const;
};


}
#endif // INDEXPROPSCLASS_H
