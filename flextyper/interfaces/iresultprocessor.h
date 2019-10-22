////////////////////////////////////////////////////////////////////////
///
/// Copyright (c) 2018, Wasserman lab
///
/// FILE        kmergenerator.h
///
/// DESCRIPTION This file contains the declaration of kmergenerator
///
/// Initial version @
///
////////////////////////////////////////////////////////////////////////

#ifndef __IRESULT_PROCESSOR_H__
#define __IRESULT_PROCESSOR_H__

#include "typedefs.h"
#include <experimental/filesystem>
#include "utils.h"

namespace fs = std::experimental::filesystem;

namespace ft {
class IResultProcessor {
public:
    ////////////////////////////////////////////////////////////////////////
    /// \brief ResultProcessor::getIndexCounts
    /// \param readIDResults
    /// \return
    ////////////////////////////////////////////////////////////////////////
    virtual MapOfCounts getIndexCounts(ResultsMap readIDResults) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// \brief ResultProcessor::processIndexPos
    /// \param indexPosResults
    /// \param ignore_multi_hits
    /// \param readLen
    /// \return
    ////////////////////////////////////////////////////////////////////////
    virtual ResultsMap processIndexPos(ResultsMap& indexPosResults, uint readLen) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// \brief ResultProcessor::processResults
    /// \param indexPosResults
    /// \param indexMapFile
    /// \param extract_matching_reads
    /// \param ignore_multi_hits
    /// \param readLen
    /// \return
    ////////////////////////////////////////////////////////////////////////
    virtual MapOfCounts processResults(ResultsMap& indexPosResults, uint readLen) = 0;
};
}

#endif // end of class
