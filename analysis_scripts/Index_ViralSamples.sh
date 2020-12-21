##########################################
#!/bin/bash

#PBS -l walltime=8:00:00,select=1:ncpus=40:mem=160gb
#PBS -A ex-ofornes-1
#PBS -m abe
#PBS -M prichmond@cmmt.ubc.ca


# Initialize flextyper
FLEXTYPER_REPO=/scratch/ex-ofornes-1/RICHMOND/FLEXTYPER/RESUBMISSION/OpenFlexTyper/

# Define directory for fastq data
RAW_DIR=/scratch/ex-ofornes-1/RICHMOND/FLEXTYPER/RESUBMISSION/NonMixedVirus/Human/

# Define sample id from set of fastq files, based on the job array index
Files=(${RAW_DIR}*_1.fastq.gz)
PBS_ARRAY_INDEX=0
IFS='/' read -a array <<< ${Files[$PBS_ARRAY_INDEX]}
SampleR1Fastq=${array[-1]}
IFS='_' read -a array2 <<< "${SampleR1Fastq}"
SAMPLE=${array2[0]}

echo $SAMPLE
echo "${SAMPLE}_1.fastq.gz"
echo "${SAMPLE}_2.fastq.gz"

OUT_DIR=/scratch/ex-ofornes-1/RICHMOND/FLEXTYPER/RESUBMISSION/NonMixedVirusIndexes/$SAMPLE/
mkdir -p $OUT_DIR
cd $OUT_DIR

FASTQR1=$RAW_DIR${SAMPLE}_1.fastq.gz
FASTQR2=$RAW_DIR${SAMPLE}_2.fastq.gz

ls $FASTQR1
ls $FASTQR2

# Run Flextyper Index
$FLEXTYPER_REPO/build/flextyper index \
        -r $FASTQR1 \
        -p $FASTQR2 \
        -n 1 --gz \
	--dfq --dfa \
	-o $OUT_DIR

