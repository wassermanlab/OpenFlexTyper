# Example of FlexTyper

> This directory contains examples of how to run FlexTyper on small datasets.

These examples will guide the usage of FlexTyper, and can be adapted for larger datasets in an applied setting.

They incude ViralExample/ and WGSExample/


## Example 1 - Viral detection

This is an example of ways to detect pathogenic virus reads from a raw fastq file. 

This dataset includes a pre-made viral query file (pathogen\_query.txt), and a paired-end RNA-seq fastq file (Mixed\_virus\_1.fastq and Mixed\_virus\_2.fastq).

~To generate your own query file, go to the fmformatter/ directory in the main repository.~ 

It also includes two different execution scripts (ex1.sh and ex2.sh), which refer to different settings files (settings.ini, settings2.ini)

### Execution

To execute, simply type:
```
bash ex.sh
```

### Input files

This script relies upon these input files:
- Fastq data (in FASTQ or FASTQ.GZ format)
- Settings File (settings.ini), which defines search parameters
- Query file (in .tsv/.txt format)
- A master script to call the tool, located in scripts/ from main repository

### Output files

You will have these output files:
- Output FM-index of reads: output\_0.fm9 
- Output Results from Query: path\_query\_\_Results.tsv
- Output matching reads: extracted\_reads.fa 

There are additional files created during processing:
- rc_MixedVirus_100.fasta
- output_0
- MixedVirus_100.fq
- MixedVirus_100.fasta
- fw_MixedVirus_100.fasta
- indices.txt

There is another script in this directory, which will run a separate set of indexing and querying with slightly different parameters. Before running, execute the clean-up function

```
sh clean.sh
```

## Example 2 - SNV detection
*Under construction*


