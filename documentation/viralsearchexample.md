\page viralsearchexample

# Viral Detection with FlexTyper Search

This is an example of ways to detect pathogenic virus reads from raw fastq files.

This dataset includes a pre-made viral query file (pathogen\_query.txt), and paired-end RNA-seq fastq files (MixedVirus\_100\_1.fq.gz and MixedVirus\_100\_2.fq.gz).

*To generate your own query file, go to the fmformatter/ directory in the main repository.*

______
### Generate the Index 

Generate the index for the files first by running: 

~~~~~~~~~~~~~~~~~~~~~
../build/flextyper index -r MixedVirus_100_1.fq.gz -p MixedVirus_100_2.fq.gz --gz 
~~~~~~~~~~~~~~~~~~~~~
\see [Indexing](@ref indexexample)

______
### Adjust settings ini file 

The folder contains two settings files that can be used to perform the search. 

Check that the path to the ini file for the index is correct 
~~~~~~~~~~~~~~~~~~~~~
# Path to the index Props ini
Index_MixedVirus_100_index.ini
~~~~~~~~~~~~~~~~~~~~~
\see [Indexing](@ref indexexample)

Check that the path to the query file is correct 
~~~~~~~~~~~~~~~~~~~~~
# Path to the input Query File
queryFile = "path_query.txt"
~~~~~~~~~~~~~~~~~~~~~

\see [Setting Ini File](@ref settingini)

______
### Run the search

To execute, simply type:
~~~~~~~~~~~~~~~~~~~~~
../build/flextyper search -c setting_1.ini -u outputFileName
~~~~~~~~~~~~~~~~~~~~~

______
### Expected Output 

Expected Counts for the MixedVirus_100.fq set:
Virus | Expected Count | Setting1
-|-|-
HIV-1 | 6100 | 4713
U21941.1 (HPV 70) | 5200 | 4054
FR751031.1 (HPV 68b) | 5200 | 4057

