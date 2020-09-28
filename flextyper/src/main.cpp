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
    QCoreApplication::setApplicationVersion("version 1.0");
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
        parser.addPositionalArgument("outputFile", QCoreApplication::translate("main","fm9 dataset"));

        parser.addOptions({
            {{"v", "verbose"},  QCoreApplication::translate("main", "prints debugging messages")},
            {{"c", "config"},   QCoreApplication::translate("main", "ini file to use"),
                                QCoreApplication::translate("main", "file")},
            {{"k", "kmerSize"}, QCoreApplication::translate("main", "kmer size"),
                                QCoreApplication::translate("main", "value")},
            {{"s", "stride"},   QCoreApplication::translate("main", "stride"),
                                QCoreApplication::translate("main", "value")},
            {{"m", "maxOcc"},   QCoreApplication::translate("main", "maxOcc"),
                                QCoreApplication::translate("main", "value")},
            {{"u", "unique"},   QCoreApplication::translate("main", "ignore nonunique kmers")},
        });

        parser.process(aps);

        ft::FTProp::CmdLineArg cmdArg = {};
        cmdArg.iniFile = "setting.ini";

        const QStringList positionalArguments = parser.positionalArguments();
        if (positionalArguments.size() != 2) {
            std::cerr << "missing the outputFile" << std::endl;
            parser.showHelp();
            return 1;
        }
        //first argument is search
        cmdArg.outputFile = positionalArguments.at(1).toStdString();

        cmdArg.verbose = parser.isSet("verbose");
        cmdArg.unique = parser.isSet("unique");
        if (parser.isSet("c"))
            cmdArg.iniFile = parser.value("c").toStdString();
        if (parser.isSet("k"))
            cmdArg.kmerSize = parser.value("k").toInt();
        if (parser.isSet("s"))
            cmdArg.stride = parser.value("s").toInt();
        if (parser.isSet("m"))
            cmdArg.maxOccurences = parser.value("m").toInt();

        std::string logName = cmdArg.outputFile + ".log";
        if (parser.isSet("k") || parser.isSet("s") || parser.isSet("m") || parser.isSet("u")) {
            logName = cmdArg.outputFile + "_" + 
                      (cmdArg.kmerSize != 0 ? ("k"+parser.value("k").toStdString()):"") +
                      (cmdArg.stride ? ("s"+parser.value("s").toStdString()):"") + 
                      (cmdArg.maxOccurences ? ("m"+parser.value("m").toStdString()):"") + 
                      (cmdArg.unique ? "u":"") + 
                      ".log";
        }

        if (parser.isSet("k") || parser.isSet("s") || parser.isSet("m") || parser.isSet("u")) {
            cmdArg.outputFile += "_" +
                  (cmdArg.kmerSize != 0 ? ("k"+parser.value("k").toStdString()):"") +
                  (cmdArg.stride ? ("s"+parser.value("s").toStdString()):"") +
                  (cmdArg.maxOccurences ? ("m"+parser.value("m").toStdString()):"") +
                  (cmdArg.unique ? "u":"");
        }
//#if 0 //remove after testing
    for(int i=0 ; i < positionalArguments.length() ; i++) {
        std::cout << i << ": " << positionalArguments.at(i).toStdString() << std::endl;
    }
    std::cout << "verbose: " << parser.isSet("verbose") << std::endl;
    std::cout << "unique: " << parser.isSet("unique") << std::endl;
    std::cout << "c: " << parser.isSet("c") << " " << cmdArg.iniFile << std::endl;
    std::cout << "k: " << parser.isSet("k") << " " << cmdArg.kmerSize << std::endl;
    std::cout << "s: " << parser.isSet("s") << " " << cmdArg.stride << std::endl;
    std::cout << "m: " << parser.isSet("m") << " " << cmdArg.maxOccurences << std::endl;
    std::cout << "LogName : " << logName << std::endl;
    exit(1);
//#endif


        ft::LogClass::OpenLog(logName);

        ft::LogClass::Log << "Running " << cmdline << std::endl;

        ft::FTProp props;
        try {
            props.initFromQSettings(cmdArg);
        } catch (std::exception& e) {
            std::cerr << "Config Error: " << e.what() << std::endl;
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

        parser.addOptions({
            {{"o", "outputDir"},        QCoreApplication::translate("main", " output index directory"),
                                        QCoreApplication::translate("main", "directory")},
            {{"x", "indexFileName"},    QCoreApplication::translate("main", "index filename (!without .fm9 extension)"),
                                        QCoreApplication::translate("main", "file")},
            {{"p", "readPairfile"},     QCoreApplication::translate("main", "name of the paired read file"),
                                        QCoreApplication::translate("main", "file")},
            {{"n", "numOfIndexes"},     QCoreApplication::translate("main", "split the reads into n indexes"),
                                        QCoreApplication::translate("main", "value")},
            {{"l", "readLength"},       QCoreApplication::translate("main", "read length"),
                                        QCoreApplication::translate("main", "value")},
            {{"fq", "fastq"},           QCoreApplication::translate("main", "input file is in fq format")},
            {{"fa", "fasta"},           QCoreApplication::translate("main", "input file is in fasta format")},
            {{"gz", "fq.gz"},           QCoreApplication::translate("main", "input file is in fq.gz format")},
            {{"c", "revComp"},          QCoreApplication::translate("main", "include the rev comp in the index")},
            {{"dfq", "delFQ" },         QCoreApplication::translate("main", "delete the fq files once the index is built")},
            {{"dfa", "delFasta"},       QCoreApplication::translate("main", "delete the fa fastas once the index is built")},
            {{"v", "verbose"},          QCoreApplication::translate("main", "prints debugging messages")},
            });

        parser.process(aps);

        algo::IndexProps *props = new algo::IndexProps();

        props->setVerboseFlag(parser.isSet("verbose"));

        fs::path buildDir = QCoreApplication::applicationDirPath().toStdString();
        props->setBuildDir(buildDir);
        props->printToStdOut("Build directory " + props->getBuildDir().string());

        //set Read Files
        fs::path readFile = parser.value(readFileName).toStdString();
        props->printToStdOut("R1 " + readFile.string());

        props->setR1(readFile);

        if (parser.isSet("fq.gz"))
        {  props->setReadFileType(algo::FileType::GZ);
            props->setReadSetName(readFile.stem().replace_extension());}

        else if (parser.isSet("fq"))
        {  props->setReadFileType(algo::FileType::FQ);
            props->setReadSetName(readFile.stem());}
        else if (parser.isSet("fa"))
        {  props->setReadFileType(algo::FileType::FA);}
        else
        { std::cout << "Error: Please specify the read file type " << std::endl;
            return 1;
        }

        props->setPairedReadsFlag(parser.isSet("p"));

        if (props->getPairedReadsFlag())
        {
            props->setR2(parser.value("p").toStdString());
            std::string readsetName = props->getReadSetName();
            props->setReadSetName(readsetName.substr(0,readsetName.size()-2));
            props->printToStdOut("R2 " + props->getR2().string());
        }

         props->printToStdOut( "read set Name " + props->getReadSetName());

        //set output values
        if (!parser.isSet("outputDir")){
            props->printToStdOut( "Output Folder not set");
            if (readFile.parent_path() != "" ){
            props->printToStdOut( "Setting Output Folder to readFile directory " + readFile.parent_path().string());
            props->setOutputFolder(readFile.parent_path());
            }else {
                props->printToStdOut( "Setting Output Folder to current path" + fs::current_path().string());
                props->setOutputFolder(fs::current_path());
            }
        }else{
        props->setOutputFolder(parser.value("outputDir").toStdString());
        }
        props->printToStdOut( "Output Folder "+ props->getOutputFolder().string());
        fs::path ppfFolder = props->getOutputFolder();
        ppfFolder /= "tmp_ppf";
        props->setppfFolder(ppfFolder);
        props->printToStdOut( "PPF Folder "+ props->getppfFolder().string());
        if (!parser.isSet("indexFileName")){
            props->printToStdOut("Index File Name not set");
            props->printToStdOut("Default Index Name set: " + props->getIndexName());
        }else {
            props->printToStdOut( "Setting Index File Name to " + parser.value("indexFileName").toStdString());
            props->setIndexName(parser.value("indexFileName").toStdString());
        }

        //set parameters
        props->setRevCompFlag(parser.isSet("revComp"));
        props->setDelFQFlag(parser.isSet("delFQ"));
        props->setDelFastaFlag(parser.isSet("delFasta"));

        if (!parser.isSet(readFileName)) {
            std::cerr << "-r or --readfile is required for indexing" << std::endl;
            parser.showHelp();
            return 1;
        }

        if (parser.isSet("numOfIndexes"))
        { u_int numOfIndicies = std::stoi(parser.value("numOfIndexes").toStdString());
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
        if (parser.isSet("readLength"))
        { u_int length = std::stoi(parser.value("readLength").toStdString());
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
