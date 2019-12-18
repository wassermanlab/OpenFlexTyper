import subprocess
import math

X = 3

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
    def generateKmers(self, kmerNbr, queryFile, settingFile):
        queryNbr = self.getNbrQueries(kmerNbr)
        print(int(queryNbr), ' queries required')
        out = "oqueries.tsv"
        self.getQueries(queryNbr, queryFile, out)
        # create Setting.ini corresponding to our testcase
        # call subprocess
        subprocess.call(["./flextyper", "searching", "-c", settingFile])

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

