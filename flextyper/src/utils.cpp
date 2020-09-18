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
std::set<fs::path> Utils::getSetOfIndexes(const fs::path& indexList)
{
    // get the paths to the indexes
    std::set<fs::path> setOfIndexes;
    std::ifstream file(indexList);
    std::string line;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            line.erase(std::remove(line.begin(), line.end(), '"'), line.end());
            setOfIndexes.emplace(line);
        }
    }
    file.close();
    return setOfIndexes;
}


//======================================================================
std::set<std::string> Utils::convertReadIDsToReadNames(const fs::path& indexMapFile, std::set<size_t> readIDs)
{
    // take a set of read IDs and return the set of readNames
    std::set<std::string> readNames;
    //go to map file for the index, and take the line at for that read Number

    std::ifstream file(indexMapFile);
    std::string line;

    if (file.is_open()) {
        int i = 0;
        while (std::getline(file, line)) {
            if (readIDs.find(i) != readIDs.end()) {
                readNames.insert(line);
            }
            i++;
        }
    }
    file.close();

    return readNames;
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
