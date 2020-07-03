#ifndef __IRESULT_PROCESSOR_H__
#define __IRESULT_PROCESSOR_H__

#include <experimental/filesystem>
#include "utils.h"

namespace fs = std::experimental::filesystem;

namespace ft {

class IResultProcessor {
public:
    virtual ~IResultProcessor() {}

    ////////////////////////////////////////////////////////////////////////
    /// \brief ResultProcessor::getIndexCounts
    /// \param readIDResults
    /// \return
    ////////////////////////////////////////////////////////////////////////
    //virtual MapOfCounts getIndexCounts(ReaIDsMap& readIDResults) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// \brief ResultProcessor::processIndexPos
    /// \param indexPosResults
    /// \param ignore_multi_hits
    /// \param readLen
    /// \return
    ////////////////////////////////////////////////////////////////////////
    //virtual ReaIDsMap processIndexPos(ResultsMap& indexPosResults, uint readLen) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// \brief processResults
    ////////////////////////////////////////////////////////////////////////
    virtual void processResults(ft::FTMap& ftMap) = 0;
};
}

#endif // end of class
