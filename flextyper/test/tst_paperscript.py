import subprocess

# config (could be exported to json file)
S = [150,125,100,75,50,31,25]    # kmer sizes
X = 3                            # number of kmers per query
N = [1,35000]                    # number of queries (range)
L = [1,10,100,1000,10000,100000] # number of kmers

class KmerRetriever(object):
    # default constructor
    def __init__(self):
        pass

    # provides the number of queries needed to generate
    # expected number of kmers
    def getNbrQueries(self, kmerNbr):
        return kmerNbr / X

    # retrieve given number of queries in query file
    def getQueries(self, queryNbr, queryFile, outputFile):
        f = open(queryFile,  "r")
        g = open(outputFile, "a")

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

        inf = "iqueries.txt"
        out = "oqueries.tsv"
        self.getQueries(queryNbr, inf, out)

        # call subprocess
        subprocess.call(["flextyper", "searching", "-c", "Settings.ini"])

        # ... 

# main function
if __name__ == '__main__':

    pass
