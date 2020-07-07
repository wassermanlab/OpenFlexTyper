#ifndef PREPROCESS_H
#define PREPROCESS_H
#include <set>
#include <iostream>
#include <map>
#include <experimental/filesystem>
#include "indexPropsClass.h"


namespace fs = std::experimental::filesystem;
namespace algo {

class PreProcess{
public:
    PreProcess(const algo::IndexProps& _indexProps);
    virtual ~PreProcess();

    algo::IndexProps _indexProps;

    void gunzipPairedFQ();
    void combineFasta(const fs::path& file1, const fs::path& file2, const fs::path& output);
    fs::path createFWDFasta();
    fs::path createRevFasta();
    fs::path createPreProcessFasta();
    void addR1R2();
    void preProcessFQGZ();
    void preProcessFQ();
    void processPairedReadFiles();
    void processReadFile();

};

}
#endif // PREPROCESS_H
