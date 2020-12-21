#!/bin/bash

#SBATCH --partition=defq

#SBATCH --mail-user=prichmond@bcchr.ca
#SBATCH --mail-type=ALL

## CPU Usage
#SBATCH --mem=360G
#SBATCH --cpus-per-task=80
#SBATCH --time=80:00:00
#SBATCH --nodes=1

## Output and Stderr
#SBATCH --output=%x-%j.out
#SBATCH --error=%x-%j.error

# Flextyper path
FLEXTYPER=/mnt/common/WASSERMAN_SOFTWARE/Test_flextyper/OpenFlexTyper/build/flextyper

# Fastq paths
# Set working space
WORKING_DIR=/mnt/common/OPEN_DATA/FLEXTYPER_INDEXES/ERR1955491_FlextyperIndex/
mkdir -p $WORKING_DIR
cd $WORKING_DIR

$FLEXTYPER search \
	-c $WORKING_DIR/../INIFILES/ERR1955491_Cytoscan.ini \
	-k 31 -s 10 -m 200 -u \
	ERR1955491_Cytoscan_FTSearch_Paper

