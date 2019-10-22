# FlexTyper Utilities

## Utility List
1. vcf_2_query.py
2. fasta_2_query.py
3. flextyper_formater.py

## vcf_2_query
This utility converts any vcf into a valid query file. The instructions below explain the setup and usage of this utility.

#### 1. Setup
```bash
# Clone Flex Typer
git clone <flex typer>
# set up conda env
conda env create -f environment.yml
source activate flextyper

#download testfiles
cd utilities/testfiles

#download GRCh37
wget http://www.bcgsc.ca/downloads/genomes/9606/hg19/1000genomes/bwa_ind/genome/GRCh37-lite.fa
wget http://www.bcgsc.ca/downloads/genomes/9606/hg19/1000genomes/bwa_ind/genome/GRCh37-lite.fa.fai
```

#### 2. Running

``` bash
# within the Flex Typer directory

# activate conda enviornment
conda activate flextyper

# for standard VCF file like clinvar
python utilities/vcf_2_query.py \
-f <corresponding reference genome> \
-v <vcf to turn into query> \
-n <name of query file>
```

#### 3. Example with files within the Flex Typer directory after setup

```bash
# within the Fast-typer directory

# activate conda enviornment
conda activate flextyper

# for standard VCF file like clinvar
python utilities/vcf_2_query.py \
-f utilities/testfiles/GRCh37-lite.fa \
-v utilities/testfiles/clinvar.3000.vcf \
-n clinvar.3000.query.tsv
```

## fasta_2_query
This utility converts any fasta file into a valid query file. The instructions below explain the setup and usage of this utility.

#### Usage
The formatter is located at `utilities/fasta_2_query.py` and has the following usage.
```
python utilities/fasta_2_query.py -h
usage: fasta_2_query.py [-h] -f FASTA [-n FILENAME] [-d DATA_TYPE]                                                                                 optional arguments:
  -h, --help  show this help message and exit
  -f FASTA, --fasta FASTA  Fasta file to turn to query
  -n FILENAME, --filename FILENAME name of query file generated
  -d DATA_TYPE, --data_type DATA_TYPE where the data came from
```

To run the formatter use:
```
python utilities/flextyper_formater.py -f <fasta_file> -n <name>
```

## flextyper_formater
This utility converts takes an output from flextyper and converts it into a valid VCF or array. The instructions below explain the setup and usage of this utility.

#### Usage
The formatter is located at `utilities/flextyper_formater.py` and has the following usage.

```
python utilities/flextyper_formater.py --h
usage: flextyper_formater.py [-h] -f {VCF,23_and_me,ancestry} -i INPUT -n NAME

optional arguments:
  -h, --help            show this help message and exit
  -f {VCF,23_and_me,ancestry}, --format {VCF,23_and_me,ancestry}
                        format of output
  -i INPUT, --input INPUT
                        input tsv
  -n NAME, --name NAME  name of save file
```

To run the formatter use:

```
python utilities/flextyper_formater.py -f <format> -i <flextyper output> -n <name>
```

