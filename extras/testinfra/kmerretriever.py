# Copyright (c) Wasserman lab 2020
# Author Godfrain Jacques Kounkou
# Description 
# This file is the kmer retriever file.
# It contains the code necessary to retrieve kmers.
# There is a tight coupling between the kmer retriever and the 
# and the flextyper binary launcher. This can be improved

import subprocess
import math
import time
import json

X = 3 # number of kmers per query 

class KmerRetriever(object):
    # default constructor
    def __init__(self):
        pass

    # provides the number of queries needed to generate
    # expected number of kmers
    def getNbrQueries(self, kmerNbr):        
        return kmerNbr # return math.ceil(kmerNbr / X) # this not true !

    # retrieve given number of queries in query file
    def getQueries(self, queryNbr, queryFile, outputFile):
        f = open(queryFile,  "r")
        g = open(outputFile, "w")

        l = -1
        for line in f:
            if l == queryNbr:
                break
            g.write(line)
            l += 1

        f.close()
        f.close()

        print('file generated in : ', outputFile)

    # generate kmers using FlexTyper and return them
    def generateKmers(self, label, kmerNbr, kmersize, queryFile, settingFile):
        queryNbr = self.getNbrQueries(kmerNbr)
        print(int(queryNbr), ' queries required')
        out = "oqueries.tsv"
        self.getQueries(queryNbr, queryFile, out)
        # create Setting.ini corresponding to our testcase
        # call subprocess
        with open('data.json') as json_file:
            inputData = json.load(json_file)
        flextyperBin = inputData["flextyperBin"]

        try:
            start_time = time.time()
            subprocess.call([flextyperBin, "searching", "-c", settingFile])
            elapse_time = time.time() - start_time
            print('elapse time : ', elapse_time)

            # csv_file.write('number of kmers, kmer length, time taken')
            with open('performances.csv', mode = 'a') as csv_file:
                csv_file.write(label + str(kmerNbr) + ', ' + str(kmersize) + ', ' + str(elapse_time) + '\n')
            csv_file.close()

        except getopt.GetoptError:
            print("Calling FlexTyper didn't succeed")

    # retrieve kmers from flexTyper output
    def retrieveKmers(self, kmernbr):
        # open generated kmer file and grab 1,  
        outputKmers = "kmerCount.log"
        f = open(outputKmers, 'r')
        lines = f.readlines()
        result = []
        if outputKmers:
            i = 0 
            for x in lines:
                if i >= kmernbr:
                    break;
                result.append(x.split(' ')[0])
                i += 1
            f.close()
        return result

