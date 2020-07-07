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
    fs::path _preProcessedFasta;
    fs::path _outputFile;
    fs::path _outputFolder; //where to save the indexes

    std::set<fs::path> _indexSet; //this is the set of generated index files

    uint _numOfReads;

    bool _revComp;
    bool _pairedReads;
    bool _delFQ;
    bool _delFasta;

    std::string _readSetName;
    algo::FileType _readFileType;

    /// Parameter Getters ///
    uint getNumOfReads() const;

    bool getDelFQFlag() const;
    bool getDelFastaFlag() const;
    bool getRevCompFlag() const;
    bool getPairedReadsFlag() const;

    const std::string& getReadSetName() const;
    const algo::FileType& getReadFileType() const;

    /// Parameter Setters ///
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

    const fs::path& getOutputFile() const;
    const fs::path& getOutputFolder() const;

    const fs::path& getPreProcessedFasta() const;
    const std::set<fs::path>& getIndexSet() const;

    /// File Setters ///
    void setReadFQ(const fs::path& readFQ);
    void setR1(const fs::path& r1);
    void setR2(const fs::path& r2);

    void delR1();
    void delR2();
    void delReadFQ();
    void delReadFasta();

    void setOutputFile(const fs::path& outputFile);
    void setOutputFolder(const fs::path& outputFolder);

    void setPreProcessedFasta(const fs::path& preProcessedFasta);
    void setIndexSet(std::set<fs::path>& indexes);
    void addToIndexSet(const fs::path& index);

};


}
#endif // INDEXPROPSCLASS_H
