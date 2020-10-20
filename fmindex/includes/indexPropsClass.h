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
/// \enum FileTypes: FQ = Fastq, FA = fasta/plain text, GZ = Fastq.gz
enum FileType {FQ = 1, FA, GZ};

////////////////////////////////////////////////////////////////////////
/// \class IndexProps
/// \brief A class that contains all the properties for an FmIndex
////////////////////////////////////////////////////////////////////////

class IndexProps
{
public:
    /// Constructor
    IndexProps();
    IndexProps(bool verbose);

    /// Destructor
    virtual ~IndexProps();

    /// \fn
    /// Create the bash string to generate the pre processed fasta files
    /// \return string Bash command
    std::string createBash();

    void printToStdOut(std::string) const;

    /// @name Parameter Getters
    /// Constant functions to return properties of the Index
    /// @{
    /// \public
    /// \fn
    uint getNumOfIndexes() const;
    uint getNumOfReads() const;
    uint getReadLength() const;

    bool getDelFQFlag() const;
    bool getDelFastaFlag() const;
    bool getRevCompFlag() const;
    bool getPairedReadsFlag() const;

    const std::string& getReadSetName() const;
    const std::string& getIndexName() const;
    const algo::FileType& getReadFileType() const;
    /// @}

    /// \name Parameter Setters
    /// Non-constant functions to update properties of the Index
    /// @{
    /// \public
    void setNumOfIndexes(uint numIndexes);
    void setNumOfReads(uint numOfReads);
    void setReadLength(uint readLength);

    void setDelFQFlag(bool delFQFlag);
    void setDelFastaFlag(bool delFastaFlag);
    void setRevCompFlag(bool revCompFlag);
    void setPairedReadsFlag(bool pairedReads);
    void setVerboseFlag(bool verbose);
    void setReadSetName(const std::string readSetName);
    void setReadFileType(const algo::FileType& readFileType);
    /// @}

    /// @name File Getters
    /// Constant functions to return properties of the Index
    /// @{
    /// \public
    /// \fn
    const fs::path& getR1() const;
    const fs::path& getR2() const;

    const fs::path& getBuildDir() const;
    const fs::path& getOutputFolder() const;
    const fs::path& getppfFolder() const;

    const std::map<fs::path, std::pair<u_int, u_int>>& getPreProcessedFastas() const;
    const std::map<fs::path, uint>& getIndexSet() const;
    /// @}

    /// \name File Setters
    /// Non-constant functions to update properties of the Index
    /// @{
    /// \public
    bool setR1(const fs::path& r1);
    bool setR2(const fs::path& r2);

    void setBuildDir(const fs::path& buildDir);
    void setIndexName(const std::string indexName);
    void setOutputFolder(const fs::path& outputFolder);
    void setppfFolder(const fs::path& ppfFolder);
    /// @}

    /// \name File Deleters
    /// Non-constant functions to remove files after processing
    /// @{
    /// \public
    bool delR1();
    bool delR2();

    void delFQ();
    void delReadFastas();
    void delSpecificReadFasta(const fs::path& _preProcessedFasta);
    /// @}

    /// \name PreProcessed Fastas
    /// Functions to handle preprocessed fasta files
    /// \public
    /// @{
    void setPreProcessedFastas(std::map<fs::path, std::pair<u_int, u_int>>& _ppFSet);
    void addPPF(fs::path _ppf, uint start, uint end);
    void setIndexSet(std::map<fs::path, uint>& indexes);
    void addToIndexSet(fs::path index, uint offset);
    void createPPFSet();
    /// @}

    /// \name Index Props I/O
    /// \public
    /// @{
    void countNumOfReads();
    void countReadLength(fs::path readFile);

    void saveIndexProps(const fs::path& indexPropsFile) const;
    void loadFromIni(const fs::path inifile);
    u_int getOffsetForIndex(fs::path indexFile);
    /// @}

private:
    /// \name Properties
    /// Properties of the Indexed Read Set
    /// \private
    /// @{
    fs::path _R1;
    fs::path _R2;

    std::map<fs::path, std::pair<u_int, u_int>> _ppFSet; ///< this is the set of pre process fasta files, plus start, end read numbers created by preprocess.sh
    std::map<fs::path, uint> _indexSet; ///< this is the set of generated index files and their offsets

    fs::path _outputFolder; ///< where to save the indexes and ini file
    fs::path _ppfFolder; ///< where to save the pre processed fast files
    fs::path _buildDir;

    uint _numOfReads;
    uint _readLength;
    uint _numOfIndexes = 1;

    bool _revComp = 0;
    bool _pairedReads = 0;
    bool _delFQ = 0;
    bool _delFasta= 0;

    bool _verbose = 0;

    std::string _readSetName;
    std::string _indexName = "Index";
    algo::FileType _readFileType;

    u_int countLines(fs::path fileToCount);
    /// @}
};


}
#endif // INDEXPROPSCLASS_H
