////////////////////////////////////////////////////////////////////////
/// \copyright Copyright (c) 2020, Wasserman lab
////////////////////////////////////////////////////////////////////////

#include "utils.h"
#include <fstream>
#include <algorithm>

namespace ft {

//======================================================================
Utils::Utils()
{
}

//======================================================================
std::string Utils::joinString(const std::set<std::string>& setOfStr, std::string delimeter)
{
    std::string output;
    std::set<std::string>::iterator it = setOfStr.begin();

    while (it != std::prev(setOfStr.end()))
    {
        output += (*it++) + delimeter;
    }
    output += *std::prev(setOfStr.end());
    return output;
}

//======================================================================
std::vector<std::string> Utils::split(const std::string& strToSplit, char delimeter)
{
    std::stringstream ss(strToSplit);
    std::string item;
    std::vector<std::string> splitString;

    while (std::getline(ss, item, delimeter)) {
        splitString.push_back(item);
    }
    return splitString;
}

//======================================================================
std::string Utils::reverseComplement(const std::string& inputString) const
{
    std::string reverseComp = inputString;

    std::transform(begin(reverseComp),
                   end(reverseComp),
                   begin(reverseComp),
                   [] (char inputChar) -> char {
        switch(inputChar)
        {
        case 'A': return 'T';
        case 'T': return 'A';
        case 'G': return 'C';
        case 'C': return 'G';
        }
        return '_';
    });

    std::reverse(reverseComp.begin(), reverseComp.end());

    if (reverseComp.find("_") != std::string::npos)
        return "";

    return reverseComp;
}

//======================================================================
Utils::~Utils()
{
}

}
