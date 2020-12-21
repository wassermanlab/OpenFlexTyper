#!/bin/bash

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

# Flextyper path
FLEXTYPER=/mnt/common/WASSERMAN_SOFTWARE/Test_flextyper/OpenFlexTyper/build/flextyper

# Set working space
WORKING_DIR=/mnt/common/OPEN_DATA/FLEXTYPER_INDEXES/

SAMPLE=ERR1955420
echo $SAMPLE

INDEX_DIR=/mnt/common/OPEN_DATA/FLEXTYPER_INDEXES/${SAMPLE}_FlextyperIndex/
cd $INDEX_DIR

SEARCH_CONFIG=/mnt/common/OPEN_DATA/FLEXTYPER_INDEXES/${SAMPLE}_SMNsites_UniqReads.ini
$FLEXTYPER search \
	-v \
	-c $SEARCH_CONFIG \
	-k 30 -s 1 -m 250 -u \
	${SAMPLE}_SMNsites_FTSearch_UniqReads

SEARCH_CONFIG=/mnt/common/OPEN_DATA/FLEXTYPER_INDEXES/${SAMPLE}_SMNseqs_UniqReads.ini
$FLEXTYPER search \
        -v \
        -c $SEARCH_CONFIG \
        -k 30 -s 1 -m 250 -u \
        ${SAMPLE}_SMNseqs_FTSearch_UniqReads


