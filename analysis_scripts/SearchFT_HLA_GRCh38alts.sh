#!/bin/bash

#SBATCH --partition=defq

#SBATCH --mail-user=prichmond@bcchr.ca
#SBATCH --mail-type=ALL

## CPU Usage
#SBATCH --mem=360G
#SBATCH --cpus-per-task=80
#SBATCH --time=24:00:00
#SBATCH --nodes=1

## Output and Stderr
#SBATCH --output=%x-%j.out
#SBATCH --error=%x-%j.error

## Job Array stuff
#SBATCH --array=0-2%2

# Flextyper path
FLEXTYPER=/mnt/common/WASSERMAN_SOFTWARE/Test_flextyper/OpenFlexTyper/build/flextyper

# Set working space
WORKING_DIR=/mnt/common/OPEN_DATA/FLEXTYPER_INDEXES/

# Define sample id from set of fastq files (which we've indexed already), based on the job array index
RAW_DIR=/mnt/common/OPEN_DATA/POLARIS_RAW/LEFTOVER/
Files=(${RAW_DIR}*_1.fastq.gz)
IFS='/' read -a array <<< ${Files[$SLURM_ARRAY_TASK_ID]}
SampleR1Fastq=${array[-1]}
IFS='_' read -a array2 <<< "${SampleR1Fastq}"
SAMPLE=${array2[0]}

echo $SAMPLE

INDEX_DIR=/mnt/common/OPEN_DATA/FLEXTYPER_INDEXES/${SAMPLE}_FlextyperIndex/
cd $INDEX_DIR



BASE_SEARCH_CONFIG=/mnt/common/OPEN_DATA/FLEXTYPER_INDEXES/INIFILES/${SAMPLE}_HLA_UniqReads.ini
for query in $(ls /mnt/common/OPEN_DATA/FLEXTYPER_INDEXES/HLA/HLA_GRCh38/*query.tsv )
do
	echo $query
	IFS='/' read -a array <<< $query
	queryFile=${array[-1]}
	IFS="_" read -a array2 <<< $queryFile
	queryGene=${array2[0]}
	
	QUERY_SEARCH_CONFIG=$INDEX_DIR/${SAMPLE}_HLA_GRCh38alts_${queryGene}_UniqReads.ini
	sed -e "s/hla_seqs_query.tsv/HLA_GRCh38\/${queryGene}_HLA_GRCh38alt_query.tsv/g" $BASE_SEARCH_CONFIG > $QUERY_SEARCH_CONFIG
	
	$FLEXTYPER search \
		-v \
		-c $QUERY_SEARCH_CONFIG \
		-k 31 -s 1 -m 150 -u \
		${SAMPLE}_${queryGene}_HLA_GRCh38alts_FTSearch_UniqReads

	$FLEXTYPER search \
		-v \
		-c $QUERY_SEARCH_CONFIG \
		-k 50 -s 1 -m 150 -u \
		${SAMPLE}_${queryGene}_HLA_GRCh38alts_FTSearch_UniqReads
	
done




