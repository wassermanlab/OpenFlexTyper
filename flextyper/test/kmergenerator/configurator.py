import json


class Configurator(object):
    # default constructor
    def __init__(self):
        self.conf = {}
        self.conf["queryFile"] = "tmpQueryFile.tsv"
        self.conf["kmerSize"] = 0
        self.conf["overlap"] = 0
        self.conf["stride"] = 1
        self.conf["maxOccurences"] = 200
        self.conf["threadNumber"] = 30
        self.conf["readLength"] = 150
        self.conf["indexFileLocation"] = "ERR1955491_nodp_nons/" # "PerfectReads.fm9"
        self.conf["outputFolder"] = ""
        self.conf["refOnly"] = True
        self.conf["searchType"] = "CENTERED"
        self.conf["multithread"] = True
        self.conf["ignoreNonUniqueKmers"] = False
        self.conf["kmerCounts"] = True
        self.conf["maxKmersPerQuery"] = 3
        self.conf["maxTotalKmers"] = 0 

    # initialization with values, (pass in a dictionary)
    def initWithParams(self, **kwargs):
        for key, value in kwargs.items():
            self.conf[key] = value

    # setter for kmerSize field, add others if needed
    def setKmerSize(self, kmerSize):
        self.conf["kmerSize"] = kmerSize

    # setter for the max Total kmers
    def setMaxTotalKmers(self, maxTotalKmers):
        self.conf["maxTotalKmers"] = maxTotalKmers

    # json file configuration creator
    def createConf(self):
        jsonFile = open('conf.json', 'w')
        jsonFile.write(json.dumps(self.conf, indent=4, sort_keys=True))
        jsonFile.close()

    # FlexTyper setting style file creator
    def createSettingFile(self, filename):
       settingOutput = open(filename, 'w')
       for k, v in self.conf.items():
           settingOutput.write(str(k) + " = " + str(v) + str('\n'))

