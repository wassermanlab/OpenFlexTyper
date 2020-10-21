\page indexexample 
# Example of FlexTyper Indexing

How to generate the index for a read set. 


## Cmd Line: 
You can display the input options using 

~~~~~~~~~~~~~~~~~~~~~{.html}

$ ./flextyper index -h

Usage: ./flextyper [options] readFileName
Description: flextyper enables the user to quickly search for kmers inside the FmIndex

Options:
  -h, 	 --help                     		     Displays this help.
  -r, 	 --readFile &lt;readFileName&gt;     Please provide the name of the read file
  -o, 	 --outputDir &lt;directory&gt;       output index directory
  -x, 	 --indexFileName &lt;file&gt;        index filename (!without .fm9 extension)
  -p, 	 --readPairfile &lt;file&gt;         name of the paired read file
  -n, 	 --numOfIndexes &lt;value&gt;    	   split the reads into n indexes
  -l, 	 --readLength &lt;value&gt;      	   read length
  --fq,  --fastq                  			     input file is in fq format
  --fa,  --fasta                  			     input file is in fasta format
  --gz,  --fq.gz                  			     input file is in fq.gz format
  -c, 	 --revComp                  		     include the rev comp in the index
  --dfq, --delFQ                 			       delete the fq files once the index is built
  --dfa, --delFasta              			       delete the fa fastas once the index is built
  -v, 	 --verbose                  		     prints debugging messages

Arguments:
  readFileName                   		contains the name of the read file

~~~~~~~~~~~~~~~~~~~~~

## Test Example

To generate the index for the Mixed Virus sample in the Test_Example folder: 
~~~~~~~~~~~~~~~~~~~~~

cd Test_Example
../build/flextyper index -r MixedVirus_100_1.fq.gz -p MixedVirus_100_2.fq.gz --gz 

~~~~~~~~~~~~~~~~~~~~~

This will show on std::cout something similar to (with file paths adjusted):
~~~~~~~~~~~~~~~~~~~~~{.sh}

"./Test_Example"
build directory "../build"
preprocessing with: 
-r readFile  MixedVirus_100_1.fq.gz
-f readSetName  MixedVirus_100
-o outputDir   ./tmp_ppf
-z zippedReads  1
-n numberOfIndexes  1
-c reverseComplement  0
-u pathToUtils   OpenFlexTyper/build/bin/
 using paired reads  1
-p readPairFile  MixedVirus_100_2.fq.gz
createFasta:  ./tmp_ppf/MixedVirus_100.fasta  created
processReadFile: output saved to ./tmp_ppf/MixedVirus_100.fasta
createFasta:  ./tmp_ppf/MixedVirus_100_pair.fasta  created
processReadFile: output saved to ./tmp_ppf/MixedVirus_100_pair.fasta
main: preprocessing complete  ./tmp_ppf/MixedVirus_100.fasta
Running FM Index

~~~~~~~~~~~~~~~~~~~~~

## Output Files 

And generates the following files: 

**tmp_ppf/MixedVirus_100.fasta**

This contains the pre processed reads, that have been stripped of everything but the sequences. 

**Index.log**
~~~~~~~~~~~~~~~~~~~~~

======== Wed Oct 21 14:57:00 2020
Running ../build/flextyper index -r MixedVirus_100_1.fq.gz -p MixedVirus_100_2.fq.gz --gz 
Build directory ../build
R1 MixedVirus_100_1.fq.gz
R2 MixedVirus_100_2.fq.gz
read set Name MixedVirus_100
Output Folder not set
Setting Output Folder to current path
Output Folder .
PPF Folder ./tmp_ppf
Index File Name not set
Default Index Name set: Index
bash args bash ../build/preprocess.sh -r MixedVirus_100_1.fq.gz -o ./tmp_ppf -f MixedVirus_100 -u ../build/bin/ -z 1 -p MixedVirus_100_2.fq.gz
Preprocess path ../build/preprocess.sh
running preprocess.sh with bash ../build/preprocess.sh -r MixedVirus_100_1.fq.gz -o ./tmp_ppf -f MixedVirus_100 -u ../build/bin/ -z 1 -p MixedVirus_100_2.fq.gz
indexing "tmp_ppf/MixedVirus_100.fasta"
creating index for MixedVirus_100 at "Index_MixedVirus_100.fm9"
index created "Index_MixedVirus_100.fm9" with offset 0

~~~~~~~~~~~~~~~~~~~~~


**Index_MixedVirus_100.fm9**

This is the index binary itself. 


**Index_MixedVirus_100_index.ini**

This contains the auto generated properties of the index file and should be kept in the same directory as the index file 

~~~~~~~~~~~~~~~~~~~~~

[General]
R1=MixedVirus_100_1.fq.gz
R2=MixedVirus_100_2.fq.gz
buildDirectory=../build
delFQ=false
delFasta=false
indexDirectory=.
indexFileName=Index
numOfIndexes=1
numOfReads=16500
pairedReads=true
readLength=150
readSetName=MixedVirus_100
revComp=false

[IndexFiles]
1\fileName=Index_MixedVirus_100.fm9
1\offset=0
size=1

~~~~~~~~~~~~~~~~~~~~~