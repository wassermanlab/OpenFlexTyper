import json
import datetime
from configurator import Configurator
from kmerretriever import KmerRetriever


# config (could be exported to json file)
with open('data.json') as json_file:
	inputData = json.load(json_file)
sampleId = inputData["id"]

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
	for kmersize in inputData["kmerSize"]:
		for index in [inputData[sampleId]["index"]]:
			conf.setKmerSize(kmersize)
			conf.setIndexFileLocation(index)
			conf.setMatchingReads(inputData[sampleId]["read"])
			conf.setMaxOccurrences(inputData["maxOccurrences"])
			conf.setThreadNumber(inputData["threadNumber"])
			conf.setReadLength(inputData["readLength"])
			conf.setMultithread(inputData["multithread"])
			conf.setIgnoreNonUniqueKmers(inputData["ignoreNonUniqueKmers"])
			conf.setStride(inputData["stride"])
			conf.createConf()
			settingFile = datetime.date.today().strftime("Setting_%B%d%Y.ini")
			conf.createSettingFile(settingFile)

			kmerRetriever = KmerRetriever()
			queryFile = inputData["queryPath"]
			querynbr  = kmerRetriever.getNbrQueries(4) 
			kmerRetriever.getQueries(querynbr, queryFile, "tmpQueryFile.tsv")
			kmerRetriever.generateKmers(index, 4, kmersize, "tmpQueryFile.tsv", settingFile)

			# open generated kmer file and grab kmernbr
			# kmerRetriever.retrieveKmers(kmernbr)
