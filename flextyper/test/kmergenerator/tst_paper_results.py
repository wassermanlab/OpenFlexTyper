import json
import datetime
from configurator import Configurator
from kmerretriever import KmerRetriever


# config (could be exported to json file)
S = [150,125,100,75,50,31,25]      # kmer sizes
L = [1, 10 ,100,1000,10000,100000] # number of kmers

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
            conf.setMaxTotalKmers(kmernbr)
            conf.createConf()
            settingFile = datetime.date.today().strftime("Setting_%B%d%Y.ini")
            conf.createSettingFile(settingFile)
    
            kmerRetriever = KmerRetriever()
            queryFile = "ERR1955491_CProbe.BamQueryOutput.tsv" # "Benchmark.tsv"
            querynbr  = kmerRetriever.getNbrQueries(kmernbr) 
            kmerRetriever.getQueries(querynbr, queryFile, "tmpQueryFile.tsv")
            kmerRetriever.generateKmers(kmernbr, kmersize, "tmpQueryFile.tsv", settingFile)

            # open generated kmer file and grab kmernbr
            kmerRetriever.retrieveKmers(kmernbr)


