\page settingini

# Example Setting ini File for Search 

~~~~~~~~~~~~~~~~~~~~~
# Benchmarking Config File for FTSearch 

# Path to the input Query File
queryFile = "path_query.txt"

# size of kmer to search for 
kmerSize = 30

# read length
readLength = 150

# Path to the index Props ini
indexPropsFile = "Index_MixedVirus_100_index.ini"

# Directory to save the results file
outputFolder = ""

# Query File has Ref or Ref&Alt sequences
refOnly = true

# Search type: CENTERED or SLIDING
searchType = SLIDING

# search for the reverse complement of each kmer 
revCompSearch = true

# Count only once for paired reads 
countAsPairs = false

# Search using multiple threads
multithread = true

# Create a fastq file for each query that contains reads
# which match to that query
matchingReads  = false

# overlap between kmers
overlap = 0

# return only those queries that have read matches
return_only_positive_matches = false

# stride of the sequence taken
stride = 5

# max occurences is the upper bound number of occurences for a sequence
maxOccurences = 100

# thread number is the number of threads to run the algorithm with
numOfThreads = 20

# ignore Kmers 
ignoreNonUniqueKmers = true
ignoreOverCountedKmers = true

#output flagged kmers 
outputNonUniqueKmers = true; 
outputOverCountedKmers = true; 

# crossover
crossover = false

#print search time
printSearchTime = false

#max Kmers Per Query
maxKmersPerQuery = 100000000

#max total kmers
maxTotalKmers = 1000000
~~~~~~~~~~~~~~~~~~~~~
