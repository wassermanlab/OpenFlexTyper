#!/bin/bash

#SBATCH --partition=defq

#SBATCH --mail-user=prichmond@bcchr.ca
#SBATCH --mail-type=ALL

## CPU Usage
#SBATCH --mem=360G
#SBATCH --cpus-per-task=80
#SBATCH --time=200:00:00
#SBATCH --nodes=1

## Output and Stderr
#SBATCH --output=%x-%j.out
#SBATCH --error=%x-%j.error

# Flextyper path
FLEXTYPER=/mnt/common/WASSERMAN_SOFTWARE/OpenFlexTyper/build/flextyper

# Fastq paths
# Set working space
WORKING_DIR=/mnt/common/OPEN_DATA/FLEXTYPER_INDEXES/
mkdir -p $WORKING_DIR
RAW_DIR=/mnt/common/OPEN_DATA/FLEXTYPER_INDEXES/HLA/RAW/
NSLOTS=$SLURM_CPUS_PER_TASK

SAMPLE=HG002
FASTQR1=$RAW_DIR${SAMPLE}_R1.fastq.gz
FASTQR2=$RAW_DIR${SAMPLE}_R2.fastq.gz

ls $FASTQR1
ls $FASTQR2

OUT_DIR=/mnt/common/OPEN_DATA/FLEXTYPER_INDEXES/${SAMPLE}_FlextyperIndex/
mkdir -p $OUT_DIR
cd $OUT_DIR

$FLEXTYPER index \
	-r $FASTQR1 \
	-p $FASTQR2 \
	-n 12 --gz -v \
	--dfq --dfa \
	-o $OUT_DIR

