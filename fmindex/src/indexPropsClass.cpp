#include "indexPropsClass.h"

namespace algo {

IndexProps::IndexProps()
{}


//================= PARAMETER GETTERS ========================
uint IndexProps::getKmerSize() const {return _kmerSize;}
bool IndexProps::getRefOnlyFlag() const {return _refOnly;}

//==================== PARAMETER SETTERS ===================
void IndexProps::setKmerSize(uint kmerSize) {_kmerSize = kmerSize;}
void IndexProps::setRefOnlyFlag(bool refOnly){ _refOnly = refOnly;}


//====================== FILE SETTERS ======================
void IndexProps::setIndexFileLocation(const fs::path& indexFileLocation)
{        _indexFileLocation = indexFileLocation; }
void IndexProps::setOutputFolder(const fs::path& outputFolder)
{        _outputFolder = outputFolder;    }
void IndexProps::setMatchingReadFQ(const fs::path& matchingReadFQ)
{        _matchingReadFQ = matchingReadFQ;    }
void IndexProps::setInputFastQ(const fs::path& inputFastQ)
{       _inputFastQ = inputFastQ;   }
void IndexProps::setOutputFile(const fs::path& outputFile)
{        _outputFile = outputFile;   }
void IndexProps::setIndexSet(std::set<fs::path>& indexes)
{        _indexSet = indexes;   }

//====================== FILE GETTERS ======================
const fs::path& IndexProps::getIndexFileLocation()const {return _indexFileLocation;}
const fs::path& IndexProps::getOutputFolder()const {return _outputFolder;}
const fs::path& IndexProps::getMatchingReadFQ() const {return _matchingReadFQ;}
const fs::path& IndexProps::getInputFastQ()const {return _inputFastQ;}
const fs::path& IndexProps::getOutputFile() const {return _outputFile;}
const std::set<fs::path>& IndexProps::getIndexSet() const {return _indexSet;}

////////////////////////////////////////////////////////////////////////
/// \brief IO functions
////////////////////////////////////////////////////////////////////////


IndexProps::~IndexProps()
{}
}
