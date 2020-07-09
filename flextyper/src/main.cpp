#include <QGuiApplication>
#include <QCommandLineParser>
#include <QSettings>
#include <iostream>
#include "ftPropsClass.h"
#include "ftSearch.h"
#include "fmindex.h"
#include "indexPropsClass.h"

static void usage()
{
    std::cout << "\nUsage\n flextyper [feature] [options...]               \n"
                 "                                                         \n"
                 " Features :                                              \n"
                 "    search   uses the FmIndex to search kmers         \n"
                 "    index   uses a a single or paired fasta/fastq/zipped fq file to produce the FmIndex \n"
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
    std::cout << fs::current_path() << std::endl;

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
        QCommandLineOption readFileName = QCommandLineOption(QStringList() << "r" << "readFile", QCoreApplication::translate("main", "Please provide the name of the read file"));
        readFileName.setValueName("readFileName");
        parser.addOption(readFileName);

        parser.addPositionalArgument("outputDir", "contains the ouput directory for the index", "");
        QCommandLineOption outputDir = QCommandLineOption(QStringList() << "o" << "outindexDir", QCoreApplication::translate("main", "Please provide the output index directory"));
        outputDir.setValueName("outputDir");
        parser.addOption(outputDir);

        parser.addPositionalArgument("indexFileName", "contains the filename for the index", "");
        QCommandLineOption indexFileName = QCommandLineOption(QStringList() << "x" << "indexFileName",   QCoreApplication::translate("main", "Please provide the index filename (!without .fm9 extension)"));
        indexFileName.setValueName("indexFileName");
        parser.addOption(indexFileName);


        QCommandLineOption readPairFileName = QCommandLineOption(QStringList() << "p" << "readPairfile", QCoreApplication::translate("main", "Please provide the name of the paired read file"));
        readPairFileName.setValueName("readPairFileName");
        parser.addOption(readPairFileName);

        QCommandLineOption readFastq(QStringList() << "fq" << "fastq" , QCoreApplication::translate("main", "the input file is in fq format "));
        parser.addOption(readFastq);

        QCommandLineOption readFasta(QStringList() << "fa" << "fasta" , QCoreApplication::translate("main", "the input file is in fasta format"));
        parser.addOption(readFasta);

        QCommandLineOption readZip(QStringList() << "gz" << "fastqgz" , QCoreApplication::translate("main", "the input file is in fq.gz format"));
        parser.addOption(readZip);

        QCommandLineOption revCompFlag(QStringList() << "c" << "rev" << "revComp", QCoreApplication::translate("main", "identifies whether to include the rev complement in the index"));
        parser.addOption(revCompFlag);

        QCommandLineOption delFQFlag(QStringList() << "dfq" << "delFQ" << "delFastQ", QCoreApplication::translate("main", "delete the FQ once the index is built"));
        parser.addOption(delFQFlag);

        QCommandLineOption delFastaFlag(QStringList() << "dfa" << "delFA" << "delFasta", QCoreApplication::translate("main", "deletes the preprocess fasta once the index is built"));
        parser.addOption(delFastaFlag);

        parser.process(aps);

        algo::IndexProps *props = new algo::IndexProps();
        fs::path buildDir = QCoreApplication::applicationDirPath().toStdString();
        props->setBuildDir(buildDir);

        if (parser.isSet(readZip))
        {  props->setReadFileType(algo::FileType::GZ);}
        else if (parser.isSet(readFastq))
        {  props->setReadFileType(algo::FileType::FQ);}
        else if (parser.isSet(readFasta))
        {  props->setReadFileType(algo::FileType::FA);}
        else
        { std::cout << "Error: Please specify the read file type " << std::endl;
            return 1;
        }

        //set Read Files
        props->setR1(parser.value(readFileName).toStdString());

        props->setPairedReadsFlag(parser.isSet(readPairFileName));
        if (props->getPairedReadsFlag())
        {
            props->setR2(parser.value(readPairFileName).toStdString());
        }

        //set output values
        props->setOutputFolder(parser.value(outputDir).toStdString());
        props->setOutputFile(parser.value(indexFileName).toStdString());

        //set parameters
        props->setRevCompFlag(parser.isSet(revCompFlag));
        props->setDelFQFlag(parser.isSet(delFQFlag));
        props->setDelFastaFlag(parser.isSet(delFastaFlag));

        if (!parser.isSet(readFileName)) {
            std::cerr << "-r or --readfile is required for indexing" << std::endl;
            parser.showHelp();
            return 1;
        }

        // call bash script to manipulate the input files
        std::string bashargs = props->createBash();
        if (fs::exists(props->getBuildDir() /+ "preprocess.sh")){
            std::cout << "bash args : " << bashargs << std::endl;
            std::cout << "running preprocess.sh" << std::endl;
            system(bashargs.c_str());
        } else {
            std::cerr << "cannot find preprocess.sh in " << props->getBuildDir() << std::endl;
        }


        algo::FmIndex fmIndexObj;

        try {
            fmIndexObj.createFMIndex(*props);
        } catch (std::exception& e) {
            std::cout << "Error in FM Index Creation! " << e.what() << std::endl;
        }
    }

    return 0;
}
