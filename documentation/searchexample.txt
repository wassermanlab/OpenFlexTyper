/////////////////////////////////////////////////////////////////////
/// \page search Search Example
/////////////////////////////////////////////////////////////////////
/// \name Example of FlexTyper

This directory contains examples of how to run FlexTyper on small datasets.

These examples will guide the usage of FlexTyper, and can be adapted for larger datasets in an applied setting.

They include Viral\_Example/ and WGS\_Example/.


## Example 1 - Viral detection

This is an example of ways to detect pathogenic virus reads from raw fastq files.

This dataset includes a pre-made viral query file (pathogen\_query.txt), and paired-end RNA-seq fastq files (Mixed\_virus\_1.fastq and Mixed\_virus\_2.fastq).

*To generate your own query file, go to the fmformatter/ directory in the main repository.*

It also includes two different execution scripts (ex\_1.sh and ex\_2.sh), which refer to different settings files (settings\_1.ini, settings\_2.ini)

### Execution

To execute, simply type:
```
sh ex_1.sh
```

### Input files

This script relies upon these input files:
- Fastq data (in fastq or fastq.gz format)
- Settings File (settings.ini), which defines search parameters
- Query file (in .tsv/.txt format)
- A master script to call the tool, located in scripts/ from main repository

### Output files

You will have these output files:
- Output FM-index of reads: output\_0.fm9
- Output Results from Query: path\_query\_\_Results.tsv
- Output matching reads: extracted\_reads.fa

There are additional files created during processing:
- Combined fastq together: MixedVirus_100.fq
- Forward (non-reverse complement) fasta file fw_MixedVirus_100.fasta
- Reverse Complement of fasta file: rc_MixedVirus_100.fasta
- Combined fasta file from fastq data: MixedVirus_100.fasta
- Temporary file which stores fasta files per-index when multiple indexes are used: output_0
- Text file which lists the indices created for the read set: indices.txt

There is another script in this directory, which will run a separate set of indexing and querying with slightly different parameters.

Before running, execute the clean-up function

```
sh clean.sh
```

Then run the second script:

```
sh ex_2.sh
```

Expected Counts for the MixedVirus_100.fq set:
Virus | Expected Count | Setting1
-|-|-
HIV-1 | 6100 | 4713
U21941.1 (HPV 70) | 5200 | 4054
FR751031.1 (HPV 68b) | 5200 | 4057

## Example 2 - SNV detection
Under construction
*/
