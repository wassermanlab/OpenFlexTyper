\page viralsearchexample

# Viral Detection with FlexTyper Search

This is an example of ways to detect pathogenic virus reads from raw fastq files.

This dataset includes a pre-made viral query file (pathogen\_query.txt), and paired-end RNA-seq fastq files (MixedVirus\_100\_1.fq.gz and MixedVirus\_100\_2.fq.gz).

*To generate your own query file, go to the fmformatter/ directory in the main repository.*

### Generate the Index 

Generate the index for the files first by running: 

~~~~~~~~~~~~~~~~~~~~~
../build/flextyper index -r MixedVirus_100_1.fq.gz -p MixedVirus_100_2.fq.gz --gz 
~~~~~~~~~~~~~~~~~~~~~
\see indexexample

### Adjust settings ini file 

The folder contains two settings files that can be used to perform the search. 

Check that the path to the ini file for the index is correct 
~~~~~~~~~~~~~~~~~~~~~
# Path to the index Props ini
Index_MixedVirus_100_index.ini
~~~~~~~~~~~~~~~~~~~~~
\see indexexample

Check that the path to the query file is correct 
~~~~~~~~~~~~~~~~~~~~~
# Path to the input Query File
queryFile = "path_query.txt"
~~~~~~~~~~~~~~~~~~~~~

For a full breakdown of all options \see settingini

### Run the search

To execute, simply type:
~~~~~~~~~~~~~~~~~~~~~
../build/flextyper search -c setting_1.ini -u outputFileName
~~~~~~~~~~~~~~~~~~~~~

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

~~~~~~~~~~~~~~~~~~~~~
sh clean.sh
~~~~~~~~~~~~~~~~~~~~~

Then run the second script:

~~~~~~~~~~~~~~~~~~~~~
sh ex_2.sh
~~~~~~~~~~~~~~~~~~~~~

Expected Counts for the MixedVirus_100.fq set:
Virus | Expected Count | Setting1
-|-|-
HIV-1 | 6100 | 4713
U21941.1 (HPV 70) | 5200 | 4054
FR751031.1 (HPV 68b) | 5200 | 4057

