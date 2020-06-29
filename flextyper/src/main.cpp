#include <QGuiApplication>
#include <QCommandLineParser>
#include <QSettings>
#include <iostream>
#include "ftPropsClass.h"
#include "ftSearch.h"
#include "fmindex.h"

static void usage()
{
    std::cout << "\nUsage\n flextyper [feature] [options...]               \n"
                 "                                                         \n"
                 " Features :                                              \n"
                 "    searching   uses the FmIndex to search kmers         \n"
                 "    indexing    uses a fasta file to produce the FmIndex \n"
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

    if (command == "searching")
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


    } else if (command == "indexing") {
        parser.clearPositionalArguments();
        parser.addHelpOption();

        parser.addPositionalArgument("fasta file of reads", "contains the preprocess fasta of reads", "");
        QCommandLineOption reads = QCommandLineOption(QStringList() << "f" << "fasta", QCoreApplication::translate("main", "Please provide the fastQ file to be indexed"));
        reads.setValueName("reads");
        parser.addOption(reads);

        parser.addPositionalArgument("outindexdir", "contains the ouput directory for the index", "");
        QCommandLineOption outindexdir = QCommandLineOption(QStringList() << "o" << "outindexdir", QCoreApplication::translate("main", "Please provide the output index directory"));
        outindexdir.setValueName("outindexdir");
        parser.addOption(outindexdir);


        parser.addPositionalArgument("indexfile", "contains the output index file", "");
        QCommandLineOption indexfile = QCommandLineOption(QStringList() << "x" << "indexfile",   QCoreApplication::translate("main", "Please provide the index filename (!without .fm9 extension)"));
        indexfile.setValueName("indexfile");
        parser.addOption(indexfile);

        parser.process(aps);

        if (!parser.isSet(reads)) {
            std::cerr << "-r or --readsfile is required for indexing" << std::endl;
            parser.showHelp();
            return 1;
        }

        std::string tmpReads = parser.value(reads).toStdString();
        std::string tmpIndexFile;
        std::string tmpOutIndexDir;

        if (!parser.isSet(indexfile))   {
            std::cout << "! setting -x indexFile or --indexfile indexFile" << std::endl;
            tmpIndexFile   = "indexFile";
        } else {
            tmpIndexFile   = parser.value(indexfile).toStdString();
        }

        if (!parser.isSet(outindexdir)) {
            std::cout << "! setting -o . or --oui ." << std::endl;
            tmpOutIndexDir = ".";
        } else {
            tmpOutIndexDir = parser.value(outindexdir).toStdString();
        }

        std::cout << "read fasta file     : " << tmpReads       << std::endl;
        std::cout << "indexfile     : " << tmpIndexFile   << std::endl;
        std::cout << "outindexdir   : " << tmpOutIndexDir << std::endl;

        algo::FmIndex fmIndexObj;

        try {
            fmIndexObj.createFMIndex(tmpReads, tmpIndexFile, "indices.txt");
        } catch (std::exception& e) {
            std::cout << "Error ! " << e.what() << std::endl;
        }
    }

    return 0;
}
