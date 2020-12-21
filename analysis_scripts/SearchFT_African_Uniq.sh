#!/bin/bash

#SBATCH --partition=defq

#SBATCH --mail-user=prichmond@bcchr.ca
#SBATCH --mail-type=ALL

## CPU Usage
#SBATCH --mem=340G
#SBATCH --cpus-per-task=80
#SBATCH --time=80:00:00
#SBATCH --nodes=1

## Output and Stderr
#SBATCH --output=%x-%j.out
#SBATCH --error=%x-%j.error

## Job Array stuff
#SBATCH --array=0-8%9

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
SEARCH_CONFIG=/mnt/common/OPEN_DATA/FLEXTYPER_INDEXES/INIFILES/${SAMPLE}_AfricanContigs_UniqReads.ini
cd $INDEX_DIR

$FLEXTYPER search \
	-c $SEARCH_CONFIG \
	-k 50 -s 5 -m 100 -u \
	${SAMPLE}_African_FTSearch_UniqReads


