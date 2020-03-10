# Copyright (c) Wasserman lab 2020
# Author Godfrain Jacques Kounkou
# Description 
# This file is the configurator file of the testinfra framework
# It will contain the configuration of our test case
# The configuration of our test case contains information about
# the queryFile, the kmersize, the overlap, ...

import json

class Configurator(object):
    # default constructor
    def __init__(self):
        self.conf = {}
        self.conf["queryFile"] 	          = "tmpQueryFile.tsv"
        self.conf["kmerSize"]             = 0
        self.conf["overlap"]              = 0
        self.conf["stride"]               = 0
        self.conf["maxOccurences"]        = 0
        self.conf["threadNumber"]         = 0
        self.conf["readLength"]           = 0
        self.conf["indexFileLocation"]    = ""
        self.conf["outputFolder"]         = ""
        self.conf["refOnly"] 	          = False
        self.conf["searchType"]           = "SLIDING"
        self.conf["multithread"]       	  = True
        self.conf["ignoreNonUniqueKmers"] = True
        self.conf["kmerCounts"]           = False
        self.conf["maxKmersPerQuery"]     = 0
        self.conf["maxTotalKmers"]        = 0 
        self.conf["matchingReads"]        = ""

    # initialization with values, (pass in a dictionary)
    def initWithParams(self, **kwargs):
        for key, value in kwargs.items():
            self.conf[key] = value

    # setter for kmerSize field, add others if needed
    def setKmerSize(self, kmerSize):
        self.conf["kmerSize"] = kmerSize

    # search type
    def setSearchType(self, searchType): 
        self.conf["searchType"] = searchType

    # setter for the max Total kmers
    def setMaxTotalKmers(self, maxTotalKmers):
        self.conf["maxTotalKmers"] = maxTotalKmers

    # indexFile location
    def setIndexFileLocation(self, indexFileLocation):
        self.conf["indexFileLocation"] = indexFileLocation

    # mathing reads
    def setMatchingReads(self, matchingreads):
        self.conf["matchingReads"] = matchingreads

    def setMaxOccurrences(self, maxOccurrences):
        self.conf["maxOccurences"] = maxOccurrences

    def setThreadNumber(self, threadNumber):
        self.conf["threadNumber"] = threadNumber

    def setReadLength(self, readLength):
        self.conf["readLength"] = readLength

    def setMultithread(self, multithread):
        self.conf["multithread"] = multithread

    def setIgnoreNonUniqueKmers(self, ignoreNonUniqueKmers):
        self.conf["ignoreNonUniqueKmers"] = ignoreNonUniqueKmers

    def setStride(self, stride):
        self.conf["stride"] = stride

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

