#ifndef __UTILS_H__
#define __UTILS_H__

#include <vector>
#include <string>
#include <experimental/filesystem>
#include <set>
#include <cmath>

#include "iutils.h"

namespace fs = std::experimental::filesystem;

namespace ft {


class Utils : public IUtils {
public:
    /// Constructor
    Utils();

    /// Destructor
    virtual ~Utils();

public:
    ////////////////////////////////////////////////////////////////////////
    /// \brief  join
    /// \param  std::set<std::string> setOfStr
    /// \param  std::string delimeter
    /// \return std::string joined string
    ////////////////////////////////////////////////////////////////////////
    std::string joinString(const std::set<std::string>& setOfStr, std::string delimeter = ", ");

    ////////////////////////////////////////////////////////////////////////
    /// \brief  split
    /// \param  std::string strToSplit
    /// \param  char delimeter
    /// \return std::set<std::string> returns tokens obtained from the given string
    ////////////////////////////////////////////////////////////////////////
    std::vector<std::string> split(const std::string& strToSplit, char delimeter);

    ////////////////////////////////////////////////////////////////////////
    /// \brief  FTSearch::reverseComplement
    /// \param  std::string inputString
    /// \return std::string returns the reverse complement sequence
    ////////////////////////////////////////////////////////////////////////
    std::string reverseComplement(const std::string& inputString) const;

};
}

#endif // end of Utils
