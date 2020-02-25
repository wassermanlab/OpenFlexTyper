#include <QGuiApplication>
#include <QCommandLineParser>
#include <iostream>
#include "ftsearch.h"
#include <QSettings>
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
        QString m_sSettingsFile(configFile.c_str());
        QSettings settings(m_sSettingsFile, QSettings::NativeFormat);

        fs::path       pathToQueryFile        = settings.value("queryFile").toString().toStdString();
        uint           kmerSize               = settings.value("kmerSize").toInt();
        uint           readLength             = settings.value("readLength").toInt();
        fs::path       indexFileLocation      = settings.value("indexFileLocation").toString().toStdString();
        fs::path       outputFolder           = settings.value("outputFolder").toString().toStdString();
        bool           refOnly                = settings.value("refOnly").toBool();
        ft::SearchType searchType             = static_cast<ft::SearchType>(settings.value("searchType").toString().toStdString()) ;
        bool           multithread            = settings.value("multithread").toBool();
        fs::path       matchingReads          = settings.value("matchingReads").toString().toStdString();
        fs::path       inputFastQ             = settings.value("inputFastQ").toString().toStdString();
        uint           overlap                = settings.value("overlap").toInt();
        bool           returnMatchesOnly      = settings.value("return_only_positive_matches").toBool();
        bool           kmerCounts             = settings.value("kmerCounts").toBool();
        uint           stride                 = settings.value("stride").toInt();
        uint           maxOccurences          = settings.value("maxOccurences").toInt();
        uint           threadNumber           = settings.value("threadNumber").toInt();
        bool           ignoreNonUniqueKmers   = settings.value("ignoreNonUniqueKmers").toBool();
        bool           crossover              = settings.value("crossover").toBool();
        bool           printSearchTime        = settings.value("printSearchTime").toBool();
		uint           maxKmersPerQuery       = settings.value("maxKmersPerQuery").toInt();
        uint           maxTotalKmers          = settings.value("maxTotalKmers").toInt();

        std::cout << "pathToQueryFile               : " << pathToQueryFile.string() <<  std::endl;
        std::cout << "kmerSize                      : " << kmerSize <<  std::endl;
        std::cout << "readLength                    : " << readLength <<  std::endl;
        std::cout << "indexFileLocation             : " << indexFileLocation.string() <<  std::endl;
        std::cout << "outputFolder                  : " << outputFolder.string() <<  std::endl;
        std::cout << "refOnly                       : " << refOnly <<  std::endl;
        std::cout << "searchType                    : " << searchType <<  std::endl;
        std::cout << "multithread                   : " << multithread <<  std::endl;
        std::cout << "overlap                       : " << overlap <<  std::endl;
        std::cout << "return_only_positive_matches  : " << returnMatchesOnly <<  std::endl;
        std::cout << "kmerCounts                    : " << kmerCounts << std::endl;
        std::cout << "stride                        : " << stride << std::endl;
        std::cout << "maxOccurences                 : " << maxOccurences << std::endl;
        std::cout << "threadNumber                  : " << threadNumber << std::endl;
        std::cout << "ignoreNonUniqueKmers          : " << ignoreNonUniqueKmers << std::endl;
        std::cout << "printSearchTime               : " << printSearchTime << std::endl;
		std::cout << "maxKmersPerQuery              : " << maxKmersPerQuery << std::endl;
        std::cout << "maxTotalKmers                 : " << maxTotalKmers << std::endl;
        std::cout << "matchinReads                  : " << matchingReads << std::endl;

        createdIndexRepo(indexFileLocation);
	    
	if (matchingReads.empty()) {
		std::cerr << "you need to provide the read file location\n";
		return 1;
	}

        ft::FTSearch flexTyperInstance;
        flexTyperInstance.init(pathToQueryFile, kmerSize, readLength, indexFileLocation,
                               outputFolder, refOnly, searchType, multithread, inputFastQ,
                               overlap, returnMatchesOnly, kmerCounts,
                               stride, maxOccurences, threadNumber, ignoreNonUniqueKmers, crossover,
                               printSearchTime, maxKmersPerQuery, maxTotalKmers, matchingReads);
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
