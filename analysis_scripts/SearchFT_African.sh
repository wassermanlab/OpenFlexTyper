#!/bin/bash

#SBATCH --partition=defq

#SBATCH --mail-user=prichmond@bcchr.ca
#SBATCH --mail-type=ALL

## CPU Usage
#SBATCH --mem=360G
#SBATCH --cpus-per-task=40
#SBATCH --time=24:00:00
#SBATCH --nodes=1

## Output and Stderr
#SBATCH --output=%x-%j.out
#SBATCH --error=%x-%j.error

## Job Array stuff
#SBATCH --array=0-1%1

# Flextyper path
FLEXTYPER=/mnt/common/WASSERMAN_SOFTWARE/Test_flextyper/OpenFlexTyper/build/flextyper

# Set working space
WORKING_DIR=/mnt/common/OPEN_DATA/FLEXTYPER_INDEXES/

# Define sample id from set of fastq files (which we've indexed already), based on the job array index
RAW_DIR=/mnt/common/OPEN_DATA/POLARIS_RAW/
Files=(${RAW_DIR}*_1.fastq.gz)
IFS='/' read -a array <<< ${Files[$SLURM_ARRAY_TASK_ID]}
SampleR1Fastq=${array[-1]}
IFS='_' read -a array2 <<< "${SampleR1Fastq}"
SAMPLE=${array2[0]}

echo $SAMPLE

INDEX_DIR=/mnt/common/OPEN_DATA/FLEXTYPER_INDEXES/${SAMPLE}_FlextyperIndex/
SEARCH_CONFIG=/mnt/common/OPEN_DATA/FLEXTYPER_INDEXES/${SAMPLE}_AfricanContigs.ini
cd $INDEX_DIR

$FLEXTYPER search \
	-c $SEARCH_CONFIG \
	-k 50 -s 5 -m 150 \
	${SAMPLE}_African_FTSearch


