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
                 " flextyper search -h                                \n\n";
}

int main(int argc, char** argv)
{
    std::vector<std::string> argList(argv, argv + argc);
    std::string cmdline;
    for (const auto &piece : argList)
        cmdline += piece + " ";

    // making cout fast
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << fs::current_path() << std::endl;
    QCoreApplication aps(argc, argv);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
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
        QCommandLineOption verbose(QStringList() << "v" << "verbose" , QCoreApplication::translate("main", "prints debugging messages"));
        parser.addOption(verbose);
        parser.process(aps);

        if (!parser.isSet(config))   {
            std::cerr << "-c or --config     is required for " << std::endl;
            parser.showHelp(); return 1;
        }

        // file locations
        std::string configFile    = parser.value(config).toStdString();
        std::cout << "\nconfig File                   : " << configFile   << std::endl;
        bool printInputs = true;

        ft::LogClass::OpenLog("search.log");
        ft::LogClass::Log << "Running " << cmdline << std::endl;

        ft::FTProp props;
        try {
            props.initFromQSettings(configFile, printInputs);
        } catch (std::exception& e) {
            std::cerr << "Config Error: " << e.what() << std::endl;
            return 1;
        }

        if (props.getInputFastQ().empty()) {
            std::cerr << "you need to provide the read file location\n";
            return 1;
        }

        ft::FTSearch *flexTyperInstance = new ft::FTSearch();
        try {
            flexTyperInstance->init(props);
        } catch (std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return 1;
        }
        free(flexTyperInstance);

        ft::LogClass::CloseLog();

    } else if (command == "index") {
        parser.clearPositionalArguments();
        parser.addHelpOption();

        parser.addPositionalArgument("readFileName", "contains the name of the read file", "");
        QCommandLineOption readFileName = QCommandLineOption(QStringList() << "r" << "readFile", QCoreApplication::translate("main", "Please provide the name of the read file"));
        readFileName.setValueName("readFileName");
        parser.addOption(readFileName);

        //parser.addPositionalArgument("outputDir", "contains the ouput directory for the index", "");
        QCommandLineOption outputDir = QCommandLineOption(QStringList() << "o" << "outindexDir", QCoreApplication::translate("main", "Please provide the output index directory"));
        outputDir.setValueName("outputDir");
        parser.addOption(outputDir);

        //parser.addPositionalArgument("indexFileName", "contains the filename for the index", "");
        QCommandLineOption indexFileName = QCommandLineOption(QStringList() << "x" << "indexFileName",   QCoreApplication::translate("main", "Please provide the index filename (!without .fm9 extension)"));
        indexFileName.setValueName("indexFileName");
        parser.addOption(indexFileName);


        QCommandLineOption readPairFileName = QCommandLineOption(QStringList() << "p" << "readPairfile", QCoreApplication::translate("main", "Please provide the name of the paired read file"));
        readPairFileName.setValueName("readPairFileName");
        parser.addOption(readPairFileName);

        QCommandLineOption numOfIndexes(QStringList() << "n" << "numOfIndexes" , QCoreApplication::translate("main", "split the reads into n indexes "));
        numOfIndexes.setValueName("numOfIndexes");
        parser.addOption(numOfIndexes);

        QCommandLineOption readLength(QStringList() << "l" << "readLength" , QCoreApplication::translate("main", "read length "));
        readLength.setValueName("readLength");
        parser.addOption(readLength);

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

        QCommandLineOption verbose(QStringList() << "v" << "verbose" , QCoreApplication::translate("main", "prints debugging messages"));
        parser.addOption(verbose);

        parser.process(aps);

        algo::IndexProps *props = new algo::IndexProps();

        props->setVerboseFlag(parser.isSet(verbose));

        fs::path buildDir = QCoreApplication::applicationDirPath().toStdString();
        props->setBuildDir(buildDir);
        props->printToStdOut("Build directory " + props->getBuildDir().string());

        //set Read Files
        fs::path readFile = parser.value(readFileName).toStdString();
        props->printToStdOut("R1 " + readFile.string());

        props->setR1(readFile);

        if (parser.isSet(readZip))
        {  props->setReadFileType(algo::FileType::GZ);
            props->setReadSetName(readFile.stem().replace_extension());}

        else if (parser.isSet(readFastq))
        {  props->setReadFileType(algo::FileType::FQ);
            props->setReadSetName(readFile.stem());}
        else if (parser.isSet(readFasta))
        {  props->setReadFileType(algo::FileType::FA);}
        else
        { std::cout << "Error: Please specify the read file type " << std::endl;
            return 1;
        }

        props->setPairedReadsFlag(parser.isSet(readPairFileName));

        if (props->getPairedReadsFlag())
        {
            props->setR2(parser.value(readPairFileName).toStdString());
            std::string readsetName = props->getReadSetName();
            props->setReadSetName(readsetName.substr(0,readsetName.size()-2));
            props->printToStdOut("R2 " + props->getR2().string());
        }

         props->printToStdOut( "read set Name " + props->getReadSetName());

        //set output values
        if (!parser.isSet(outputDir)){
            props->printToStdOut( "Output Folder not set");
            if (readFile.parent_path() != "" ){
            props->printToStdOut( "Setting Output Folder to readFile directory " + readFile.parent_path().string());
            props->setOutputFolder(readFile.parent_path());
            }else {
                props->printToStdOut( "Setting Output Folder to current path" + fs::current_path().string());
                props->setOutputFolder(fs::current_path());
            }
        }else{
        props->setOutputFolder(parser.value(outputDir).toStdString());
        }
        props->printToStdOut( "Output Folder "+ props->getOutputFolder().string());
        fs::path ppfFolder = props->getOutputFolder();
        ppfFolder /= "tmp_ppf";
        props->setppfFolder(ppfFolder);
        props->printToStdOut( "PPF Folder "+ props->getppfFolder().string());
        if (!parser.isSet(indexFileName)){
            props->printToStdOut("Index File Name not set");
            props->printToStdOut("Default Index Name set: " + props->getIndexName());
        }else {
            props->printToStdOut( "Setting Index File Name to " + parser.value(indexFileName).toStdString());
            props->setIndexName(parser.value(indexFileName).toStdString());
        }

        //set parameters
        props->setRevCompFlag(parser.isSet(revCompFlag));
        props->setDelFQFlag(parser.isSet(delFQFlag));
        props->setDelFastaFlag(parser.isSet(delFastaFlag));

        if (!parser.isSet(readFileName)) {
            std::cerr << "-r or --readfile is required for indexing" << std::endl;
            parser.showHelp();
            return 1;
        }

        if (parser.isSet(numOfIndexes))
        { u_int numOfIndicies = std::stoi(parser.value(numOfIndexes).toStdString());
            props->setNumOfIndexes(numOfIndicies);
        } else {
            props->setNumOfIndexes(1);
        }


        // call bash script to manipulate the input files
        std::string bashargs = props->createBash();
        std::cout << "bash args " << bashargs << std::endl;
        fs::path preprocess = props->getBuildDir();
        preprocess /= "preprocess.sh";

        std::cout << "Preprocess path " << preprocess.string() << std::endl;

        if (fs::exists(preprocess)){
            try {
                props->printToStdOut( "running preprocess.sh with " + bashargs);
                system(bashargs.c_str());
            } catch (std::exception& e) {
                std::cout << "Error in preprocessing " << e.what() << std::endl;
            }

        } else {
            std::cerr << "cannot find preprocess.sh in " << props->getBuildDir() << std::endl;
        }

        props->createPPFSet();

        // count number of reads in read set
        props->countNumOfReads();

        // set the read length, or count from PPF
        if (parser.isSet(readLength))
        { u_int length = std::stoi(parser.value(readLength).toStdString());
            props->setReadLength(length);
        } else {
            fs::path ppf = props->getPreProcessedFastas().begin()->first;
            props->countReadLength(ppf);
        }

        algo::FmIndex fmIndexObj;

        try {
            fmIndexObj.parallelFmIndex(*props);
        } catch (std::exception& e) {
            std::cout << "Error in FM Index Creation " << e.what() << std::endl;
            return 1;
        }

        if (props->getDelFQFlag()){
            props->delFQ();
            std::cout << "Deleting FQ files " << std::endl;
        }
        if (props->getDelFastaFlag()){
            props->delReadFastas();
            std::cout << "Deleting PPF files " << std::endl;

        }



    }

    return 0;
}
