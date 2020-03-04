#!/bin/bash

##########################################
# 
# Copyright (c) Wasserman lab 2020
# 
# DESCRIPTION master_script.sh is an all in one script
#             that enables the user to run a FlexTyper search by providing
#	      a set of paired readFiles with the format : read_1.fq.gz and read_2.fq.gz
#	      a settingFile containing information about the resources to be used
#	      a numberOfIndexes (FM-Index) to be generated 
#	      a reverseComp parameter used as a flag to generate reverse complement or not
#	      a pathToUtils used to find flextyper and seqtk binaries.
#
# AUTHOR      Godfrain Jacques Kounkou
#
##########################################

set -e

# . input_validator.sh
##########################################
# DESC routine to obtain file size
# ARGS filename
# RSLT return the size in bytes
##########################################
function getFileSize() {
	local filename=$1
	echo $(stat --printf="%s\n" $filename)
}

##########################################
# DESC processes the queries by checking their size
# ARGS query filename
# RSLT the function will stop the program if sizes dont match
##########################################
function processQueries() {
	local queries=$1
	local queryFileSize=$(getFileSize $queries)

	if [ $queryFileSize -eq 0 ]; then
		echo '==== ERROR : wrong query file'
		exit 0
	fi
}

##########################################
# DESC processes the reads by checking their sizes
# ARGS pair read filenames
# RSLT the function will stop the program if sizes dont match
##########################################
function processReads() {
	local read_1=$1
	local read_2=$2
	local read_1Size=$(getFileSize ${read_1})
	local read_2Size=$(getFileSize ${read_2})

	if [[ $read_1Size == 0 ]] || [[ $read_2Size == 0 ]]; then
		echo '==== ERROR : wrong read file'
		exit 0
	fi
}

##########################################
# DESC processes the setting file by checking its size
# ARGS setting filename
# RSLT the function will stop the program if the setting file is empty
##########################################
function processSettings() {
	local settingfile=$1
	local settingfileSize=$(getFileSize ${settingfile})	

	if [ $settingfileSize == 0 ]; then
		echo '==== ERROR : wrong setting file'
		exit 0
	fi
}

##########################################
# DESC high level function to process inputs. The function
#      will mainly check that the queries and the reads
#      aren't empty. A sophisticated level of checking
#      can be further added.
# ARGS queries and pair reads
# RSLT the function forwards the responsibility to underlying functions
##########################################
function processInputs() {
	local readname=$1
	local readfile_1=$(ls ${readname}_1*)
	local readfile_2=$(ls ${readname}_2*)

	processReads ${readfile_1} ${readfile_2}
}

# . read_indexer.sh
##########################################
# DESC This function uncompresses the pair read files
# ARGS the only argument is the readname
# RSLT This function will create a fastq file
##########################################
function uncompress() 
{
	local readname=$1

	echo 'uncompress files'
	start_time=$( date +%s.%N )

	if [ -f "${readname}.fq" ]; then
		echo 'uncompressed file exists'
		return
	fi

	if [[ -f "${readname}_1.fq" ]] && [[ -f "${readname}_2.fq" ]]; then
		cat "${readname}_1.fq" "${readname}_2.fq" > "${readname}.fq"
		return
	fi

	R1_FILE=$(ls ${readname}_1*)
	R2_FILE=$(ls ${readname}_2*)

	gunzip -c ${R1_FILE} >  "${readname}.fq"
	gunzip -c ${R2_FILE} >> "${readname}.fq"

	elapsed_time=$( date +%s.%N --date="$start_time seconds ago" )
	echo uncommpress took : $elapsed_time
}

##########################################
# DESC This function will create the fw and reverse complement reads
# ARGS the argument is the FastQ file and if yes or no we need to reverse complement the file
# RSLT This function will create the final fasta file
##########################################
function createFastaReadFile()
{
        local readfile=$1
	local readname=$(basename $readfile)
	local readdir=$(dirname $readfile)
	local reversecomplement=$2
	local utilsPath=$3
	local fastqFile="${readdir}/${readname}.fq"
	local fastaFile="$readdir/${readname}.fasta"
	local fwFile="$readdir/fw_${readname}.fasta"
	local rcFile="$readdir/rc_${readname}.fasta"

        if [[ -f $fwFile ]] || [[ -f $rcFile ]]; then
                echo 'forward or reverse complement file exists'
                return
        fi

        if [ $# -eq 3 ]; then
                start_time=$( date +%s.%N )
		echo create forward fasta file from $fastqFile
                "${utilsPath}/seqtk" seq -A -C -U    $fastqFile | egrep -v '[>]' > $fwFile

		if [ $reversecomplement -eq 1 ]; then
			echo create reverse complement fasta file from $fastqFile
                	"${utilsPath}/seqtk" seq -A -C -U -r $fastqFile | egrep -v '[>]' > $rcFile
		fi
                elapsed_time=$( date +%s.%N --date="$start_time seconds ago" )
                echo task took : $elapsed_time

                fw_size=$(stat -c "%s" $fwFile)
		if [ -f $rcFile ]; then
                	rc_size=$(stat -c "%s" $rcFile)
		fi
                margins=5000000000

		if [ -f $rcFile ]; then
                	if [ $fw_size -gt $(($rc_size + $margins)) ] || [ $fw_size -lt $(($rc_size - $margins)) ]; then
                        	echo 'error, fw and rc are not the same size !'
                        	exit 1
                	fi
		fi
        fi

	if [ -f $rcFile ]; then
        	cat $fwFile $rcFile > $fastaFile
	else
		cat $fwFile > $fastaFile
	fi
}

##########################################
# DESC function that will split the reads in N reads
# ARGS the function takes the read filename, and the sub index
# RSLT the side effect is the output_ files produced
##########################################
function splitReadFiles() {
	local readfilename=$1
	local readname=$(basename $readfilename)
	local readdir=$(dirname $readfilename)
	local subIndexes=$2
	local digits=${#subIndexes}
	
	split "${readdir}/${readname}.fasta" -n "l/${subIndexes}" -a $((digits)) -d ${readdir}/output_
}

##########################################
# DESC creates FM-Indexes from read files
# ARGS the only argument is the read file
# RSLT for each read file formated with output_, 
#      the function will create an FM-Index
##########################################
function createIndex()
{
	local readfilename=$1
	local readname=$(basename $readfilename)
	local readdir=$(dirname $readfilename)
	local utilsPath=$2

	files=$(ls "${readdir}"/output_*)
	for e in ${files[@]}; do
		if [ -f $e.fm9 ]; then
			continue
		fi
		echo "creating index for ${1}" 
		"${utilsPath}/flextyper" indexing -f $e -o ${readdir} -x ${e}.fm9
	done
}

# . searcher.sh
##########################################
# DESC performs searches by calling FlexTyper search
#      functionality.
# ARGS
#      - Setting file
# RSLT the function output is a result file containing
#      query counts
##########################################
function search() {
	local settingfile=$1
	local utilsPath=$2
	processSettings $settingfile

	"${utilsPath}/flextyper" searching -c ${settingfile}
}

##########################################
# DESC this function moves generated files to the final directory
# ARGS this function takes the location of the reads
# RSLT this function cleans up the current dir with generated data
##########################################
function moveFiles() {
	local readname=$1

	readdir=$(dirname $readname)

	if [ ${readdir} != '.' ]; then
		mv *__Results.tsv ${readdir}
		mv indices.txt ${readdir}
		mv extracted_reads.fa ${readdir}
	fi
}

# main function call
function main() {
	local readFile=$1
	local settingFile=$2
	local nbreIndexes=$3
	local reverseComplement=$4
	local utilsPath=$5

	processInputs ${readFile}
	uncompress ${readFile}
	createFastaReadFile ${readFile} ${reverseComplement} ${utilsPath}
	splitReadFiles ${readFile} ${nbreIndexes}
	createIndex ${readFile} ${utilsPath}
	search ${settingFile} ${utilsPath}
}

##########################################
# DESC this function displays how to use the master_script
# ARGS it doesnt take any arguments
# RSLT the function is a simple printing function. It produces
#      no side effects
##########################################
function usage() {
	echo 'master_script - all in one script for FlexTyper execution'
	echo ' '
	echo 'usage :'
	echo ' '
	echo 'master_script [options]'
	echo ' '
	echo 'options:'
	echo '-r readname          [string]  Example_100_[1 and 2].fq.gz -> Example_100'
	echo '-s settingfile       [string]  setting.ini'
	echo '-n numberOfIndexes   [integer] 1'
	echo '-c reverseComplement [1 or 0]  1'
	echo '-p path_to_utils     [string]  relative or absolute path to utils is created during FlexTyper bash install.sh'
	echo ' '
	exit 0
}

# check the total number of arguments
if [ $# -lt 10 ]; then
	echo '==== ERROR : 5 arguments required'
	usage
fi

# initialise all variables
readFile=''
settingFile=''
numberOfIndexes=0
reverseComp=0
pathToUtils=''

# retrieve arguments
while getopts 'r:s:n:c:p:' arg ; do
	case $arg in
		r) readFile=${OPTARG};;
		s) settingFile=${OPTARG};;
		n) numberOfIndexes=${OPTARG};;
		c) reverseComp=${OPTARG};;
		p) pathToUtils=${OPTARG};;
		*) usage;;
	esac
done

# call the main function
main $readFile $settingFile $numberOfIndexes $reverseComp $pathToUtils && moveFiles $readFile
