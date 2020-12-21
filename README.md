# FlexTyper Manuscript

> This is a repository for the analysis reported in the FlexTyper manuscript (link forthcoming).


## Overview
- Accessing data
- Data processing 
- Plotting


## Accessing Data

The raw data for this project is either drawn from online sources (e.g. sequence archives), simulated from fasta genomes.

### Human WGS
Human WGS samples used in this work can be downloaded here:

```
mkdir -p POLARIS_RAW
cd POLARIS_RAW

############
# EUROPEAN #
############
### HG01682 - EUR - Family: IBS030 (Father)
wget ftp://ftp.sra.ebi.ac.uk/vol1/fastq/ERR195/004/ERR1955404/ERR1955404_1.fastq.gz
wget ftp://ftp.sra.ebi.ac.uk/vol1/fastq/ERR195/004/ERR1955404/ERR1955404_2.fastq.gz
### HG01684 - EUR - Family: IBS030 (Mother)
wget ftp://ftp.sra.ebi.ac.uk/vol1/fastq/ERR195/001/ERR1955491/ERR1955491_1.fastq.gz
wget ftp://ftp.sra.ebi.ac.uk/vol1/fastq/ERR195/001/ERR1955491/ERR1955491_2.fastq.gz
### HG01683 - EUR - Family: IBS030 (Proband,M)
wget ftp://ftp.sra.ebi.ac.uk/vol1/fastq/ERR230/007/ERR2304597/ERR2304597_1.fastq.gz
wget ftp://ftp.sra.ebi.ac.uk/vol1/fastq/ERR230/007/ERR2304597/ERR2304597_2.fastq.gz

###########
# AFRICAN #
###########
## HG02771 - Family GB58 - AFR - GWD - FATHER
wget -c -q ftp://ftp.sra.ebi.ac.uk/vol1/fastq/ERR195/000/ERR1955420/ERR1955420_1.fastq.gz
wget -c -q ftp://ftp.sra.ebi.ac.uk/vol1/fastq/ERR195/000/ERR1955420/ERR1955420_2.fastq.gz
## HG02772 - Family GB58 - AFR - GWD - MOTHER
wget -c -q ftp://ftp.sra.ebi.ac.uk/vol1/fastq/ERR195/003/ERR1955443/ERR1955443_1.fastq.gz
wget -c -q ftp://ftp.sra.ebi.ac.uk/vol1/fastq/ERR195/003/ERR1955443/ERR1955443_2.fastq.gz
## HG02773 - Family GB58 - AFR - GWD - KID (M)
wget -c -q ftp://ftp.sra.ebi.ac.uk/vol1/fastq/ERR230/006/ERR2304556/ERR2304556_1.fastq.gz
wget -c -q ftp://ftp.sra.ebi.ac.uk/vol1/fastq/ERR230/006/ERR2304556/ERR2304556_2.fastq.gz

#########
# ASIAN #
#########
## HG00662 - Family SH076 - EAS - CHS - FATHER
wget -c -q ftp://ftp.sra.ebi.ac.uk/vol1/fastq/ERR195/007/ERR1955507/ERR1955507_1.fastq.gz
wget -c -q ftp://ftp.sra.ebi.ac.uk/vol1/fastq/ERR195/007/ERR1955507/ERR1955507_2.fastq.gz
## HG00663 - Family SH076 - EAS - CHS - MOTHER
wget -c -q ftp://ftp.sra.ebi.ac.uk/vol1/fastq/ERR195/005/ERR1955495/ERR1955495_1.fastq.gz
wget -c -q ftp://ftp.sra.ebi.ac.uk/vol1/fastq/ERR195/005/ERR1955495/ERR1955495_2.fastq.gz
## HG00664 - Family SH076 - EAS - CHS - KID (M)
wget -c -q ftp://ftp.sra.ebi.ac.uk/vol1/fastq/ERR230/009/ERR2304569/ERR2304569_1.fastq.gz
wget -c -q ftp://ftp.sra.ebi.ac.uk/vol1/fastq/ERR230/009/ERR2304569/ERR2304569_2.fastq.gz

```

### Human RNAseq
Human RNAseq comes from the Genome England project.
```
# Data links provided from here:
# https://www.ebi.ac.uk/arrayexpress/experiments/E-MTAB-6523/samples/
wget ftp://ftp.sra.ebi.ac.uk/vol1/fastq/ERR232/006/ERR2322366/ERR2322366_1.fastq.gz
wget ftp://ftp.sra.ebi.ac.uk/vol1/fastq/ERR232/006/ERR2322366/ERR2322366_2.fastq.gz

wget ftp://ftp.sra.ebi.ac.uk/vol1/fastq/ERR232/005/ERR2322365/ERR2322365_1.fastq.gz
wget ftp://ftp.sra.ebi.ac.uk/vol1/fastq/ERR232/005/ERR2322365/ERR2322365_2.fastq.gz

wget ftp://ftp.sra.ebi.ac.uk/vol1/fastq/ERR232/008/ERR2322368/ERR2322368_1.fastq.gz
wget ftp://ftp.sra.ebi.ac.uk/vol1/fastq/ERR232/008/ERR2322368/ERR2322368_2.fastq.gz

wget ftp://ftp.sra.ebi.ac.uk/vol1/fastq/ERR232/004/ERR2322364/ERR2322364_1.fastq.gz
wget ftp://ftp.sra.ebi.ac.uk/vol1/fastq/ERR232/004/ERR2322364/ERR2322364_2.fastq.gz

wget ftp://ftp.sra.ebi.ac.uk/vol1/fastq/ERR232/001/ERR2322371/ERR2322371_1.fastq.gz
wget ftp://ftp.sra.ebi.ac.uk/vol1/fastq/ERR232/001/ERR2322371/ERR2322371_2.fastq.gz

wget ftp://ftp.sra.ebi.ac.uk/vol1/fastq/ERR232/003/ERR2322363/ERR2322363_1.fastq.gz
wget ftp://ftp.sra.ebi.ac.uk/vol1/fastq/ERR232/003/ERR2322363/ERR2322363_2.fastq.gz

wget ftp://ftp.sra.ebi.ac.uk/vol1/fastq/ERR232/009/ERR2322369/ERR2322369_1.fastq.gz
wget ftp://ftp.sra.ebi.ac.uk/vol1/fastq/ERR232/009/ERR2322369/ERR2322369_2.fastq.gz

wget ftp://ftp.sra.ebi.ac.uk/vol1/fastq/ERR232/007/ERR2322367/ERR2322367_1.fastq.gz
wget ftp://ftp.sra.ebi.ac.uk/vol1/fastq/ERR232/007/ERR2322367/ERR2322367_2.fastq.gz
```

### Simulated viral samples
Viral genomes were downloaded from NCBI (see paper for details).

```
U21941.fasta
FR751039.fasta
EBV_sequence.fasta
HIV-1_sequence.fasta

```

The four viral genomes were simulated using ART\_illumina at various concentrations (read depths).
 
This code chunk was executed within a SLURM shell script:

```
cd $FASTADIR
for FASTA in $(ls *fasta)
do
	for COV in 10 100 1000 10000 
	do
		IFS='.' read -a array <<< $FASTA
		STRAIN_ID=${array[0]}
		SAMPLE_ID=${STRAIN_ID}_${COV}_
		echo $SAMPLE_ID
		/project/projects/def-wyeth/RICHMOND/SIMULATION/varsim-0.8.1/varsim_run/ART/art_bin_VanillaIceCream/art_illumina \
			-na -l 150 -s 100 -f $COV -p -m 300 -i $FASTA -d $SAMPLE_ID -o $SAMPLE_ID
	done
done

# Make one more person with cov = 1x
COV=1
FASTADIR=/project/projects/def-wyeth/FastTyper/SimulatePathogens/FASTA/
cd $FASTADIR
for FASTA in $(ls *fasta)
do
	IFS='.' read -a array <<< $FASTA
	STRAIN_ID=${array[0]}
	SAMPLE_ID=${STRAIN_ID}_${COV}_
	echo $SAMPLE_ID
	/project/projects/def-wyeth/RICHMOND/SIMULATION/varsim-0.8.1/varsim_run/ART/art_bin_VanillaIceCream/art_illumina \
		-na -l 150 -s 100 -f $COV -p -m 300 -i $FASTA -d $SAMPLE_ID -o $SAMPLE_ID

done

```



### Generating Mixed Viral Samples

Yes, these files are, for whatever reason, 151bp long. FlexTyper assumes a fixed read length, so we first trim with Trimmomatic and then combine human RNA seq files with simulated reads derived above.

#### Trim

```
# Trimmomatic to trim the ERR sequences
TRIMMOMATICJAR=/project/projects/def-wyeth/TOOLS/Trimmomatic-0.39/trimmomatic-0.39.jar
HUMAN_RNA_FASTQDIR=/project/projects/def-wyeth/FastTyper/SimulatePathogens/HumanRNA/
for ERR in 'ERR2322363' 'ERR2322364' 'ERR2322365' 'ERR2322366' 'ERR2322367'
do
        ls $HUMAN_RNA_FASTQDIR/${ERR}_1.fastq
        ls $HUMAN_RNA_FASTQDIR/${ERR}_2.fastq
        INFQ1=$HUMAN_RNA_FASTQDIR/${ERR}_1.fastq
        INFQ2=$HUMAN_RNA_FASTQDIR/${ERR}_2.fastq
        OUTPAIRFQ1=$HUMAN_RNA_FASTQDIR/${ERR}_trim_1.fastq
        OUTPAIRFQ2=$HUMAN_RNA_FASTQDIR/${ERR}_trim_2.fastq
        OUTUNPAIRFQ1=$HUMAN_RNA_FASTQDIR/${ERR}_trimunpair_1.fastq
        OUTUNPAIRFQ2=$HUMAN_RNA_FASTQDIR/${ERR}_trimunpair_2.fastq

        java -jar $TRIMMOMATICJAR \
                PE -threads $SLURM_JOB_CPUS_PER_NODE \
                $INFQ1 $INFQ2 \
                $OUTPAIRFQ1 $OUTUNPAIRFQ1 \
                $OUTPAIRFQ2 $OUTUNPAIRFQ2 \
                CROP:150 MINLEN:150

done
```


#### Concatenate
```
cat EBV_sequence_1_1.fq HIV-1_sequence_10_1.fq U21941_100_1.fq FR751039_1000_1.fq $HUMAN_RNA_FASTQDIR/ERR2322363_trim_1.fastq > Patient_1_1.fastq
cat EBV_sequence_1_2.fq HIV-1_sequence_10_2.fq U21941_100_2.fq FR751039_1000_2.fq $HUMAN_RNA_FASTQDIR/ERR2322363_trim_2.fastq > Patient_1_2.fastq
bgzip -c Patient_1_1.fastq > Patient_1_1.fastq.gz
bgzip -c Patient_1_2.fastq > Patient_1_2.fastq.gz

cat EBV_sequence_10_1.fq HIV-1_sequence_100_1.fq U21941_1000_1.fq FR751039_1_1.fq $HUMAN_RNA_FASTQDIR/ERR2322364_trim_1.fastq > Patient_2_1.fastq
cat EBV_sequence_10_2.fq HIV-1_sequence_100_2.fq U21941_1000_2.fq FR751039_1_2.fq $HUMAN_RNA_FASTQDIR/ERR2322364_trim_2.fastq > Patient_2_2.fastq
bgzip -c Patient_2_1.fastq > Patient_2_1.fastq.gz
bgzip -c Patient_2_2.fastq > Patient_2_2.fastq.gz

cat EBV_sequence_100_1.fq HIV-1_sequence_1000_1.fq U21941_1_1.fq FR751039_10_1.fq $HUMAN_RNA_FASTQDIR/ERR2322365_trim_1.fastq > Patient_3_1.fastq
cat EBV_sequence_100_2.fq HIV-1_sequence_1000_2.fq U21941_1_2.fq FR751039_10_2.fq $HUMAN_RNA_FASTQDIR/ERR2322365_trim_2.fastq > Patient_3_2.fastq
bgzip -c Patient_3_1.fastq > Patient_3_1.fastq.gz
bgzip -c Patient_3_2.fastq > Patient_3_2.fastq.gz

cat EBV_sequence_1000_1.fq HIV-1_sequence_1_1.fq U21941_10_1.fq FR751039_100_1.fq $HUMAN_RNA_FASTQDIR/ERR2322366_trim_1.fastq > Patient_4_1.fastq
cat EBV_sequence_1000_2.fq HIV-1_sequence_1_2.fq U21941_10_2.fq FR751039_100_2.fq $HUMAN_RNA_FASTQDIR/ERR2322366_trim_2.fastq > Patient_4_2.fastq
bgzip -c Patient_4_1.fastq > Patient_4_1.fastq.gz
bgzip -c Patient_4_2.fastq > Patient_4_2.fastq.gz

cat EBV_sequence_1_1.fq HIV-1_sequence_1_1.fq U21941_1_1.fq FR751039_1_1.fq $HUMAN_RNA_FASTQDIR/ERR2322367_trim_1.fastq > Patient_5_1.fastq
cat EBV_sequence_1_2.fq HIV-1_sequence_1_2.fq U21941_1_2.fq FR751039_1_2.fq $HUMAN_RNA_FASTQDIR/ERR2322367_trim_2.fastq > Patient_5_2.fastq
bgzip -c Patient_5_1.fastq > Patient_5_1.fastq.gz
bgzip -c Patient_5_2.fastq > Patient_5_2.fastq.gz
```

## Data Processing

The scripts for data processing, e.g. generating indexes from fastq files and searching indexes can be found in scripts/.

These scripts are relative to either a SLURM or PBSPro queueing system, but the shell commands within are valid. In some cases, the data aggregation scripts are provided as well (e.g. collating FlexTyper output into tables).

The query files used for this analysis can be found on the Zenodo upload (see link above). 

Summarized and/or individual output files can be found on the Zenodo upload (see link above). 


## Plotting

The R scripts for plotting can be found in the Plotting/ directory. These scripts refer to files found on the Zenodo drive (often too large for github).






