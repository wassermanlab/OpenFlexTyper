#ifndef INDEXPROPSCLASS_H
#define INDEXPROPSCLASS_H
#include <set>
#include <iostream>
#include <map>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
namespace algo {

class IndexProps{
public:
    IndexProps();

    virtual ~IndexProps();

    /// Properties ///

    fs::path _indexFileLocation;
    fs::path _outputFolder;
    fs::path _matchingReadFQ;
    fs::path _inputFastQ;
    fs::path _outputFile;
    std::set<fs::path> _indexSet;

    uint _numOfReads;

    bool _revComplement;
    bool _pairedReads;

    /// Getters ///
    const fs::path& getPathToQueryFile() const;
    const fs::path& getIndexFileLocation() const;
    const fs::path& getOutputFolder() const;
    const fs::path& getMatchingReadFQ() const;
    const fs::path& getInputFastQ() const;
    const fs::path& getOutputFile() const;
    const std::set<fs::path>& getIndexSet() const;

    uint getNumOfReads() const;

    bool getRevComplementFlag() const;
    bool getPairedReadsFlag() const;

    /// Setters ///
    void setPathToQueryFile(const fs::path& pathToQueryFile);
    void setIndexFileLocation(const fs::path& indexFileLocation);
    void setOutputFolder(const fs::path& outputFolder);
    void setMatchingReadFQ(const fs::path& matchingReadFQ);
    void setInputFastQ(const fs::path& inputFastQ);
    void setOutputFile(const fs::path& outputFile);
    void setIndexSet(std::set<fs::path>& indexes);

    void setNumOfReads(uint numOfReads);

    void setRevCompFlag(bool revCompFlag);
    void setPairedReadsFlag(bool pairedReads);


    ////////////////////////////////////////////////////////////////////////
    /// \brief IO functions
    ////////////////////////////////////////////////////////////////////////

};


}
#endif // INDEXPROPSCLASS_H
