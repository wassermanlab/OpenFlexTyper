#!/bin/bash

#SBATCH --partition=defq

#SBATCH --mail-user=prichmond@bcchr.ca
#SBATCH --mail-type=ALL

## CPU Usage
#SBATCH --mem=360G
#SBATCH --cpus-per-task=40
#SBATCH --time=28:00:00
#SBATCH --nodes=1

## Output and Stderr
#SBATCH --output=%x-%j.out
#SBATCH --error=%x-%j.error

## Job Array stuff
#SBATCH --array=0-%2

# Flextyper path
FLEXTYPER=/mnt/common/WASSERMAN_SOFTWARE/OpenFlexTyper/build/flextyper

# Fastq paths
# Set working space
WORKING_DIR=/mnt/common/OPEN_DATA/FLEXTYPER_INDEXES/
mkdir -p $WORKING_DIR
RAW_DIR=/mnt/common/OPEN_DATA/POLARIS_RAW/LEFTOVER/
NSLOTS=$SLURM_CPUS_PER_TASK

# Define sample id from set of fastq files, based on the job array index
Files=(${RAW_DIR}*_1.fastq.gz)
IFS='/' read -a array <<< ${Files[$SLURM_ARRAY_TASK_ID]}
SampleR1Fastq=${array[-1]}
IFS='_' read -a array2 <<< "${SampleR1Fastq}"
SAMPLE=${array2[0]}

echo $SAMPLE
echo "${SAMPLE}_1.fastq.gz"
echo "${SAMPLE}_2.fastq.gz"

FASTQR1=$RAW_DIR${SAMPLE}_1.fastq.gz
FASTQR2=$RAW_DIR${SAMPLE}_2.fastq.gz

ls $FASTQR1
ls $FASTQR2

OUT_DIR=/mnt/common/OPEN_DATA/FLEXTYPER_INDEXES/${SAMPLE}_FlextyperIndex/
mkdir -p $OUT_DIR
cd $OUT_DIR

$FLEXTYPER index \
	-r $FASTQR1 \
	-p $FASTQR2 \
	-n 8 --gz -v \
	--dfq --dfa \
	-o $OUT_DIR

