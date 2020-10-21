\page indexexample 
# Example of FlexTyper Indexing

How to generate the index for a read set. 


## Cmd Line: 
~~~~~~~~~~~~~~~~~~~~~{.html}
<pre>Usage: ./flextyper [options] readFileName
Description: flextyper enables the user to quickly search for kmers inside the FmIndex

Options:
  -h, --help                     		Displays this help.
  -r, --readFile &lt;readFileName&gt;  	Please provide the name of the read file
  -o, --outputDir &lt;directory&gt;     output index directory
  -x, --indexFileName &lt;file&gt;     	index filename (!without .fm9 extension)
  -p, --readPairfile &lt;file&gt;      	name of the paired read file
  -n, --numOfIndexes &lt;value&gt;    	split the reads into n indexes
  -l, --readLength &lt;value&gt;      	read length
  --fq, --fastq                  		input file is in fq format
  --fa, --fasta                  		input file is in fasta format
  --gz, --fq.gz                  		input file is in fq.gz format
  -c, --revComp                  		include the rev comp in the index
  --dfq, --delFQ                 		delete the fq files once the index is built
  --dfa, --delFasta              		delete the fa fastas once the index is built
  -v, --verbose                  		prints debugging messages

Arguments:
  readFileName                   		contains the name of the read file
</pre>
~~~~~~~~~~~~~~~~~~~~~

