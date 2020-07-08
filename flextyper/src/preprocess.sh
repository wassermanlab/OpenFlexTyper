#!/bin/bash

set -e

##########################################
function getFileSize() {
        local filename=$1
        echo $(stat --printf="%s\n" $filename)
}

##########################################
function unzipReadFile()
{
        local readFileName=$1
        local outputDir=$2
        local readName=$(basename $readFileName)

        echo 'uncompress files'
        start_time=$( date +%s.%N )

        if [[ $1 == *.fq ]];
        then
            echo 'file is not compressed'
            return
        fi
        if [ -f "${readName}.fq" ];
        then
            echo 'uncompressed file exists'
            return
        fi
        gunzip -c ${R1_FILE} >  "${outputDir}/${readName}.fq"

        elapsed_time=$( date +%s.%N --date="$start_time seconds ago" )
        echo uncommpress took : $elapsed_time
}

##########################################
function createFasta()
{
        local readFQ=$1
        local utilsPath=$2
        local readname=$(basename $readFQ)
        local readdir=$(dirname $readFQ)
        local fastaFile="$readdir/${readname}.fasta"

        if [[ -f $fwFile ]] ; then
                echo 'fasta file exists'
                return
        fi

        if [ $# -eq 2 ]; then
                start_time=$( date +%s.%N )
                echo create forward fasta file from $fastqFile
                "${utilsPath}/seqtk" seq -A -C -U    $fastqFile | egrep -v '[>]' > $fastaFile
                elapsed_time=$( date +%s.%N --date="$start_time seconds ago" )
                echo task took : $elapsed_time
                fw_size=$(stat -c "%s" $fwFile)
        fi
}

##########################################
function createRevComp()
{
        local readFQ=$1
        local utilsPath=$2
        local readname=$(basename $readFQ)
        local readdir=$(dirname $readFQ)
        local fastaFile="${readdir}/${readname}.fasta"
        local fwFile="${readdir}/${readname}.fasta"
        local rcFile="${readdir}/rc_${readname}.fasta"

        if [[ -f $rcFile ]]; then
                echo 'reverse complement file exists'
                return
        fi

        if [ $# -eq 2 ]; then
                start_time=$( date +%s.%N )

                echo create reverse complement fasta file from $fastqFile
                "${utilsPath}/seqtk" seq -A -C -U -r $readFQ | egrep -v '[>]' > $rcFile

                elapsed_time=$( date +%s.%N --date="$start_time seconds ago" )
                echo task took : $elapsed_time

                fw_size=$(stat -c "%s" $fwFile)
                rc_size=$(stat -c "%s" $rcFile)
                margins=5000000000

                if [ $fw_size -gt $(($rc_size + $margins)) ] || [ $fw_size -lt $(($rc_size - $margins)) ]; then
                        echo 'error, fw and rc are not the same size !'
                        exit 1
                fi
        fi
        cat $fwFile $rcFile > $fastaFile
}

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
function processReadFile(){
        local readFile=$1
        local outputDir=$2
        local zippedReads=$3
        local reverseComp=$4
        local utilsPath=$5

        local readName=$(basename $readFile)
        local readDir=$(dirname $readFile)
        local readFileFQ="${outputDir}/${readName}.fq"
        local readFileFA="${outputDir}/${readName}.fasta"

        #Unzip the input files
        if [zippedReads -eq 1];then
            unzipReadFile ${readFile} ${outputDir}
        fi

        #Create Plain Fastas
        createFasta ${readFileFQ} ${utilsPath}

        #Add reverse complement
        if [reverseComp -eq 1];then
            createRevComp ${readFileFA} ${utilsPath}
        fi

}

##########################################
# main function call
function main() {
        local readFile=$1
        local readPairFile=$2
        local outputDir=$3
        local outputFileName=$4
        local zippedReads=$5
        local numIndexes=$6
        local reverseComp=$7
        local pairedReads=$8
        local utilsPath=$9

        local readFileFA="${outputDir}/$(basename $readFile).fasta"
        local readPairFA="${outputDir}/$(basename $readPairFile).fasta"
        local outputReadFile = "${outputDir}/${outputFileName}.fasta"

        processReadFile ${readFile} ${outputDir} ${zippedReads} ${reverseComp} ${utilsPath}

        #Repeat steps for paired reads
        if [pairedReads -eq 1]; then
            processReadFile ${readPairFile} ${outputDir} ${zippedReads} ${reverseComp} ${utilsPath}
            cat $readFileFA $readPairFA > ${outputReadFile}
        else
        cat $readFileFA > ${outputReadFile}
        fi

        #Split Read Files
        splitReadFiles ${outputReadFile} ${numIndexes}

}

function usage() {
        echo 'preprocessing script'
        echo ' '
        echo 'usage :'
        echo ' '
        echo 'master_script [options]'
        echo ' '
        echo 'options:'
        echo '-r readFilename      [string]  '
        echo '-p readPairFile      [string]  '
        echo '-n numberOfIndexes   [integer] 1'
        echo '-c reverseComplement [1 or 0]  0'
        echo '-o outputDir         [string]  1'
        echo '-z zippedReads [1 or 0]  1'
        echo ' '
        exit 0
}
# check the total number of arguments
if [ $# -lt 10 ]; then
        echo '==== ERROR : requires at least 5'
        usage
fi

# initialise all variables
readFile=''
readPairFile=''
numberOfIndexes=0
reverseComp=0
pairedReads=0
zippedReads=0
pathToUtils=''
outputDir=''
outputFileName=''

# retrieve arguments
while getopts 'z:r:p:n:c:u:' arg ; do
    case $arg in
        -z) zippedReads=$(OPTARG};;
        -r) readFile=${OPTARG};;
        -p) readPairFile=${OPTARG}
            pairedReads=1;;
        -n) numberOfIndexes=${OPTARG};;
        -c) reverseComp=${OPTARG};;
        -o) outputDir=${OPTARG};;
        -f) outputFileName=${OPTARG};;
        -u) pathToUtils=${OPTARG};;
        *) usage;;
    esac
done

# call the main function

main $readFile $readPairFile $outputDir $outputFileName $zippedReads $numberOfIndexes $reverseComp $pairedReads $pathToUtils
