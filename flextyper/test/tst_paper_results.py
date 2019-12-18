import subprocess
import math
import json
import datetime

# config (could be exported to json file)
S = [150,125,100,75,50,31,25]    # kmer sizes
X = 3                            # number of kmers per query
N = [1,35000]                    # number of queries (range)
L = [1,10,100,1000,10000,100000] # number of kmers

class Configuration(object):
    # default constructor
    def __init__(self):
        self.conf = {}
        self.conf["queryFile"] = "Benchmark.tsv"
        self.conf["kmerSize"] = 31
        self.conf["overlap"] = False
        self.conf["stride"] = 1
        self.conf["maxOcc"] = 200
        self.conf["threadNumber"] = 1
        self.conf["readLen"] = 100
        self.conf["indexFileLoc"] = ""
        self.conf["outputFolder"] = ""
        self.conf["refOnly"] = False
        self.conf["searchType"] = "CENTERED"
        self.conf["multithread"] = False
        self.conf["ignoreNonUniqueKmers"] = False

    # initialization with values, pass in a dictionary
    def initWithParams(self, **kwargs):
        for key, value in kwargs.items():
            self.conf[key] = value

    # set each field
    def setQueryFile(self, queryFile):
        self.queryFile = queryFile
    def setKmerSize(self, kmerSize):
        self.kmerSize = kmerSize
    def setOverlap(self, overlap):
        self.overlap = overlap
    def setStride(self, stride):
        self.stride = stride
    def setMaxOcc(self, maxOcc):
        self.maxOcc = maxOcc
    def setThreadNumber(self, threadNumber):
        self.threadNumber = threadNumber
    def setReadLen(self, readLen):
        self.readLen = readLen
    def setIndexFileLoc(self, indexLoc):
        self.indexLoc = indexLoc
    def setOutputFolder(self, outputFolder):
        self.outputFolder = outputFolder
    def setRefOnly(self, refOnly):
        self.refOnly = refOnly
    def setSearchTyper(self, searchType):
        self.searchType = searchType
    def setMultithread(self, multithread):
        self.multithread = multithread
    def setIgnoreNonUniqueKmers(self, ignoreNonUniqueKmers):
        self.ignoreNonUniqueKmers

    def createConf(self):
        jsonFile = open('conf.json', 'w')
        jsonFile.write(json.dumps(self.conf, indent=4, sort_keys=True))
        jsonFile.close()

    def createSettingFile(self):
       settingFile = datetime.date.today().strftime("Setting_%h%B%d%Y.ini") 

       print('settingFile : ', settingFile)

       settingOutput = open(settingFile, 'w')
       for k, v in self.conf.items():
           settingOutput.write(str(k) + " = " + str(v) + str('\n'))


class KmerRetriever(object):
    # default constructor
    def __init__(self):
        pass

    # provides the number of queries needed to generate
    # expected number of kmers
    def getNbrQueries(self, kmerNbr):        
        return math.ceil(kmerNbr / X)

    # retrieve given number of queries in query file
    def getQueries(self, queryNbr, queryFile, outputFile):
        f = open(queryFile,  "r")
        g = open(outputFile, "w")

        l = 1
        for line in f:
            if l == 5:
                break
            g.write(line)
            l += 1

        f.close()
        f.close()

    # generate kmers using FlexTyper and return them
    def generateKmers(self, kmerNbr, queryFile):
        queryNbr = self.getNbrQueries(kmerNbr)
        print(int(queryNbr), ' queries required')
        out = "oqueries.tsv"
        self.getQueries(queryNbr, queryFile, out)
        # create Setting.ini corresponding to our testcase
        # call subprocess
        subprocess.call(["./flextyper", "searching", "-c", "Setting_DecDecember182019.ini"])

# main function
if __name__ == '__main__':

    # params can be read from a configuration file
    conf = Configuration()
    configFile = "conftest.json"
    if configFile:
        with open(configFile, 'r') as f:
            data = json.load(f)
    conf.initWithParams(**data)
    conf.createConf()
    conf.createSettingFile()

    kmerRetriever = KmerRetriever()
    kmerNbr = 10
    queryFile = "Benchmark.tsv"
    kmerRetriever.generateKmers(kmerNbr, queryFile)
