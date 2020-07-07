#include <QGuiApplication>
#include <QCommandLineParser>
#include <QSettings>
#include <iostream>
#include "ftPropsClass.h"
#include "ftSearch.h"
#include "fmindex.h"
#include "preProcess.h"
#include "indexPropsClass.h"

static void usage()
{
    std::cout << "\nUsage\n flextyper [feature] [options...]               \n"
                 "                                                         \n"
                 " Features :                                              \n"
                 "    search   uses the FmIndex to search kmers         \n"
                 "    index   uses a fasta file to produce the FmIndex \n"
                 "                                                         \n"
                 " Options  :                                              \n"
                 "    -h, --help  displays this help                       \n"
                 "                                                         \n"
                 " Example :                                               \n"
                 " flextyper searching -h                                \n\n";
}

static void createdIndexRepo(const fs::path& indexFileLocation)
{
    std::ofstream indices("indices.txt");

    if (indices.is_open()) {
        if (indexFileLocation.extension() == ".fm9") {
            std::string r = indexFileLocation;
            r.erase(std::remove(r.begin(), r.end(), '"'), r.end());
            indices << r << "\n";

        } else {
            for (const auto& entry : fs::directory_iterator(indexFileLocation)) {
                fs::path res_entry = entry;
                if (res_entry.extension() == ".fm9") {
                    std::string r = res_entry;
                    r.erase(std::remove(r.begin(), r.end(), '"'), r.end());
                    indices << r << "\n";
                }
            }
        }
    }
    indices.close();
}

int main(int argc, char** argv)
{
    // making cout fast
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication aps(argc, argv);
    QCoreApplication::setApplicationName("flextyper");
    QCoreApplication::setApplicationVersion("version 0.2");
    QCommandLineParser parser;

    if (argc <= 2) {
        usage();
        return 0;
    }

    parser.setApplicationDescription("Description: flextyper enables the user to quickly search for kmers inside the FmIndex");
    parser.addPositionalArgument("command", "The command to execute.");

    // Call parse() to find out the positional arguments.
    parser.parse(QCoreApplication::arguments());
    const QStringList args = parser.positionalArguments();

    const QString command = args.isEmpty() ? QString() : args.first();

    if (command == "search")
    {
        parser.clearPositionalArguments();
        parser.addHelpOption();
        parser.addPositionalArgument("configuration file", "file containing search configurations", "");
        QCommandLineOption config = QCommandLineOption(QStringList() << "c" << "config",   QCoreApplication::translate("main", "Please provide configuration file"));
        config.setValueName("config");
        parser.addOption(config);
        parser.process(aps);

        if (!parser.isSet(config))   {
            std::cerr << "-c or --config     is required for " << std::endl;
            parser.showHelp(); return 1;
        }

        // file locations
        std::string configFile    = parser.value(config).toStdString();
        std::cout << "\nconfig File                   : " << configFile   << std::endl;
        bool printInputs = true;

        ft::FTProp *props = new ft::FTProp();
        props->initFromQSettings(configFile, printInputs);

        createdIndexRepo(props->getIndexFileLocation());
	    
        if (props->getMatchingReadFQ().empty()) {
            std::cerr << "you need to provide the read file location\n";
            return 1;
        }

        ft::FTSearch *flexTyperInstance = new ft::FTSearch();
        flexTyperInstance->init(*props);


    } else if (command == "index") {
        parser.clearPositionalArguments();
        parser.addHelpOption();

        parser.addPositionalArgument("readFileName", "contains the name of the read file", "");
        QCommandLineOption readFileName = QCommandLineOption(QStringList() << "f" << "readfile", QCoreApplication::translate("main", "Please provide the name of the read file"));
        readFileName.setValueName("readFileName");
        parser.addOption(readFileName);

        parser.addPositionalArgument("outputDir", "contains the ouput directory for the index", "");
        QCommandLineOption outputDir = QCommandLineOption(QStringList() << "o" << "outindexdir", QCoreApplication::translate("main", "Please provide the output index directory"));
        outputDir.setValueName("outputDir");
        parser.addOption(outputDir);

        parser.addPositionalArgument("indexFileName", "contains the filename for the index", "");
        QCommandLineOption indexFileName = QCommandLineOption(QStringList() << "x" << "indexfile",   QCoreApplication::translate("main", "Please provide the index filename (!without .fm9 extension)"));
        indexFileName.setValueName("indexFileName");
        parser.addOption(indexFileName);

        QCommandLineOption readFastq(QStringList() << "fq" << "fastq" , QCoreApplication::translate("main", "identifies whether to include the rev complement in the index"));
        parser.addOption(readFastq);

        QCommandLineOption readFasta(QStringList() << "fa" << "fasta" , QCoreApplication::translate("main", "identifies whether to include the rev complement in the index"));
        parser.addOption(readFasta);

        QCommandLineOption readZip(QStringList() << "gz" << "fastqgz" , QCoreApplication::translate("main", "identifies whether to include the rev complement in the index"));
        parser.addOption(readZip);

        QCommandLineOption revCompFlag(QStringList() << "r" << "rev" << "revComp", QCoreApplication::translate("main", "identifies whether to include the rev complement in the index"));
        parser.addOption(revCompFlag);

        QCommandLineOption pairedReadsFlag(QStringList() << "p" << "paired" << "pairedReads", QCoreApplication::translate("main", "identifies whether the reads are paired"));
        parser.addOption(pairedReadsFlag);

        QCommandLineOption delFQFlag(QStringList() << "dfq" << "delFQ" << "delFastQ", QCoreApplication::translate("main", "identifies whether the reads are paired"));
        parser.addOption(delFQFlag);

        QCommandLineOption delFastaFlag(QStringList() << "dfa" << "delFA" << "delFasta", QCoreApplication::translate("main", "identifies whether the reads are paired"));
        parser.addOption(delFastaFlag);

        parser.process(aps);

        algo::IndexProps *props = new algo::IndexProps();

        if (parser.isSet(readFastq))
        {  props->setReadFileType(algo::FileType::FQ);}
        else if (parser.isSet(readFastq))
        {  props->setReadFileType(algo::FileType::FQ);}
        else if (parser.isSet(readFastq))
        {  props->setReadFileType(algo::FileType::FQ);}
        else
        { std::cout << "Error: Please specify the read file type " << std::endl;
            return 1;
        }

        props->setReadSetName(parser.value(readFileName).toStdString());
        props->setOutputFolder(parser.value(outputDir).toStdString());
        props->setOutputFile(parser.value(indexFileName).toStdString());
        props->setRevCompFlag(parser.isSet(revCompFlag));
        props->setPairedReadsFlag(parser.isSet(pairedReadsFlag));
        props->setDelFQFlag(parser.isSet(delFQFlag));
        props->setDelFastaFlag(parser.isSet(delFastaFlag));

        if (!parser.isSet(readFileName)) {
            std::cerr << "-r or --readfile is required for indexing" << std::endl;
            parser.showHelp();
            return 1;
        }

        algo::PreProcess _preProcess(*props);

        if (props->getPairedReadsFlag())
        {
           _preProcess.processPairedReadFiles();
        } else {
           _preProcess.processReadFile();
        }


        algo::FmIndex fmIndexObj;

        try {
            fmIndexObj.createFMIndex(*props);
        } catch (std::exception& e) {
            std::cout << "Error ! " << e.what() << std::endl;
        }
    }

    return 0;
}
