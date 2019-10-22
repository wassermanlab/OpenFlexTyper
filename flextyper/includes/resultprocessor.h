////////////////////////////////////////////////////////////////////////
///
/// Copyright (c) 2018, Wasserman lab
///
/// FILE        resultprocessor.h
///
/// DESCRIPTION This file contains the declaration of kmergenerator class
///
/// Initial version @ Godfrain Jacques Kounkou
///
////////////////////////////////////////////////////////////////////////

#ifndef __RESULT_PROCESSOR_H__
#define __RESULT_PROCESSOR_H__

#include "typedefs.h"
#include <experimental/filesystem>
#include "utils.h"
#include "iutils.h"
#include "iresultprocessor.h"

namespace fs = std::experimental::filesystem;

namespace ft {
class ResultProcessor : public IResultProcessor {
public:
    ////////////////////////////////////////////////////////////////////////
    /// \brief ResultProcessor
    ////////////////////////////////////////////////////////////////////////
    ResultProcessor();

    ////////////////////////////////////////////////////////////////////////
    /// \brief ~ResultProcessor
    ////////////////////////////////////////////////////////////////////////
    virtual ~ResultProcessor();

    ////////////////////////////////////////////////////////////////////////
    /// \brief ResultProcessor::getIndexCounts
    /// \param readIDResults
    /// \return
    ////////////////////////////////////////////////////////////////////////
    MapOfCounts getIndexCounts(ResultsMap readIDResults);

    ////////////////////////////////////////////////////////////////////////
    /// \brief ResultProcessor::processIndexPos
    /// \param indexPosResults
    /// \param ignore_multi_hits
    /// \param readLen
    /// \return
    ////////////////////////////////////////////////////////////////////////
    ResultsMap processIndexPos(ResultsMap& indexPosResults, uint readLen);

    ////////////////////////////////////////////////////////////////////////
    /// \brief ResultProcessor::processResults
    /// \param indexPosResults
    /// \param indexMapFile
    /// \param extract_matching_reads
    /// \param ignore_multi_hits
    /// \param readLen
    /// \return
    ////////////////////////////////////////////////////////////////////////
    MapOfCounts processResults(ResultsMap& indexPosResults, uint readLen);

    ////////////////////////////////////////////////////////////////////////
    /// \brief overrideUtils
    /// \param utils
    ////////////////////////////////////////////////////////////////////////
    void overrideUtils(std::shared_ptr<IUtils> utils);

private:
    ////////////////////////////////////////////////////////////////////////
    /// \brief _utils
    ////////////////////////////////////////////////////////////////////////
    Utils _ownedUtils;
    IUtils* _utils;
};
}

#endif // end of class
