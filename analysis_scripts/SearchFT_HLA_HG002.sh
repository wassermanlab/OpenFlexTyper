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
#SBATCH --array=0-8%1

# Flextyper path
FLEXTYPER=/mnt/common/WASSERMAN_SOFTWARE/Testing_flextyper/OpenFlexTyper/build/flextyper

# Set working space
WORKING_DIR=/mnt/common/OPEN_DATA/FLEXTYPER_INDEXES/


SAMPLE=HG002
echo $SAMPLE

INDEX_DIR=/mnt/common/OPEN_DATA/FLEXTYPER_INDEXES/${SAMPLE}_FlextyperIndex/
SEARCH_CONFIG=/mnt/common/OPEN_DATA/FLEXTYPER_INDEXES/${SAMPLE}_HLA.ini
cd $INDEX_DIR

$FLEXTYPER search \
	-v \
	-c $SEARCH_CONFIG \
	-k 75 -s 1 -m 150 -u \
	${SAMPLE}_HLA_FTSearch


