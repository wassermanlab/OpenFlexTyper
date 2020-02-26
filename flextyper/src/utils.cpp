#include "utils.h"
#include <fstream>
#include <algorithm>

namespace ft {

//======================================================================
Utils::Utils()
{
}

//======================================================================
Utils::~Utils()
{
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
    // std::cout << indexList << std::endl;

    // get the paths to the indexes
    std::set<fs::path> setOfIndexes;
    std::ifstream file(indexList);
    std::string line;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            line.erase(std::remove(line.begin(), line.end(), '"'), line.end());
            setOfIndexes.emplace(line);
            // std::cout << "adding : " << line.c_str() << std::endl;
        }
    }
    file.close();
    return setOfIndexes;
}

//======================================================================
std::set<size_t> Utils::convertIndexPositionsToReadIDs(std::set<long long> indexPositions, uint readLength)
{
    // takes a set of index positions and converts each element to the readID
    // my concern is that we need to know which index it is to know whether its 5100000 or what
    std::set<size_t> readIDs;
    // std::cout << "initial size : " << indexPositions.size() << ", readLength : " << readLength << std::endl;

    // std::remove("occurences.txt");
    for (auto indexPos : indexPositions) {
        auto r = (size_t) std::ceil(indexPos / (readLength + 1));
        // std::cout << indexPos << " -> " << r << std::endl;
        readIDs.insert(r);
    }

    return readIDs;
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
int Utils::fileIndexToQueryIndex(uint fileIndex)
{
    // query index cannot be zero
    int queryIndex = fileIndex + 1;

    if (queryIndex <= 0) {
        exit(1);
    }

    return queryIndex;
}

//======================================================================
std::string Utils::trimmedReadFileName(const fs::path& p)
{
    std::string result;
    for(auto& e : p) {
        result = e;
    }
    size_t pos = result.find_last_of("_");
    std::string filename = result;
    if (pos != std::string::npos) {
        filename = result.substr(pos + 1);
    }
    return filename;
}

//======================================================================
uint Utils::queryIndexToFileIndex(int queryIndex)
{
    // file index can be zero
    uint fileIndex = abs(queryIndex) -1;
    return fileIndex;
}
}
