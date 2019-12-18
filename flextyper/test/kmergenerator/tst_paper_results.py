import json
import datetime
from configurator import Configurator
from kmerretriever import KmerRetriever

# config (could be exported to json file)
S = [150,125,100,75,50,31,25]    # kmer sizes
X = 3                            # number of kmers
N = [1,35000]                    # number of queries (range)
L = [1,10,100,1000,10000,100000] # number of kmers

# static function
def readJsonConfigFile(configFile):
    if configFile:
        with open(configFile, 'r') as f:
            data = json.load(f)
    return data

# main function
if __name__ == '__main__':        
    conf = Configurator()

    # O(M * N) anyway...
    for kmersize in S:
        for kmernbr in L:
            conf.setKmerSize(kmersize)
            conf.createConf()
            settingFile = datetime.date.today().strftime("Setting_%B%d%Y.ini")
            conf.createSettingFile(settingFile)
    
            kmerRetriever = KmerRetriever()
            queryFile = "Benchmark.tsv"
            kmerRetriever.generateKmers(kmernbr, queryFile, settingFile)

            # open generated kmer file and grab 1,  
            print(kmerRetriever.retrieveKmers(kmernbr))
