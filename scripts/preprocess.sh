#!/bin/bash

set -e

function buildSeqTk() {
        DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
        git clone https://github.com/lh3/seqtk.git
        cd seqtk
        make
        cd $DIR
}

##########################################
function getFileSize() {
        local filename=$1
        echo $(stat --printf="%s\n" $filename)
}

##########################################
function unzipReadFile()
{
        local readFile=$1
        local readName=$2
        local outputDir=$3

        echo 'uncompress files'
        #start_time=$( date +%s.%N )

        if [[ $1 == *.fq ]];
        then
            echo 'file is not compressed'
            return
        fi
        if [ -f "${readName}.fq" ];
        then
            echo 'uncompressed file already exists'
            return
        fi

        if [ ! -d "$outputDir" ]; then
            echo "directory ${outputDir} doesnt exist "
            echo "making directory ${outputDir} "
            mkdir ${outputDir}
        fi

        gunzip -c ${readFile} >  "${outputDir}/${readName}.fq"

        #elapsed_time=$( date +%s.%N --date="$start_time seconds ago" )
        #echo uncommpress took : $elapsed_time


}

##########################################
function createFasta()
{
        local readFQ=$1
        local readName=$2
        local utilsPath=$3
        local readdir=$(dirname $readFQ)
        local fastaFile="$readdir/${readName}.fasta"

        if [[ -f $fwFile ]] ; then
                echo 'fasta file already exists'
                return
        fi

        if [ $# -eq 3 ]; then
            #start_time=$( date +%s.%N )
            #echo "create forward fasta file from" $readFQ
            if [ ! -f ${utilsPath}/seqtk ]; then
                if [ ! -f ${utilsPath}seqtk/seqtk ]; then
                    echo "cannot find seqtk, installing in " ${utilsPath}
                    cd ${utilsPath}
                    buildSeqTk
                    utilsPath=${utilsPath}/seqtk
                else
                    #echo "found seqtk in " ${utilsPath}seqtk
                    utilsPath=${utilsPath}seqtk
                fi
            fi

            ${utilsPath}/seqtk seq -A -C -U  ${PWD}/${readFQ} | egrep -v '[>]' > $fastaFile
            #elapsed_time=$( date +%s.%N --date="$start_time seconds ago" )
            #echo task took : $elapsed_time
            fw_size=$(stat -c "%s" $fastaFile)
        fi
}

##########################################
function createRevComp()
{
        local readFQ=$1
        local readName=$2
        local utilsPath=$3

        local readDir=$(dirname $readFQ)

        local fastaFile="${readDir}/${readName}.fasta"
        local rcFile="${readDir}/rc_${readName}.fasta"

        if [[ -f $rcFile ]]; then
                echo 'reverse complement file already exists'
                return
        fi

        if [ $# -eq 3 ]; then
            #start_time=$( date +%s.%N )
            if [ ! -f ${utilsPath}/seqtk ]; then
                if [ ! -f ${utilsPath}seqtk/seqtk ]; then
                    echo "cannot find seqtk, installing in " ${utilsPath}
                    cd ${utilsPath}
                    buildSeqTk
                    utilsPath=${utilsPath}/seqtk
                else
                    #echo "found seqtk in " ${utilsPath}seqtk
                    utilsPath=${utilsPath}seqtk
                fi
            fi

            echo "create reverse complement fasta file from" ${readFQ}
            ${utilsPath}/seqtk seq -A -C -U -r ${PWD}/${readFQ} | egrep -v '[>]' > $rcFile

            #elapsed_time=$( date +%s.%N --date="$start_time seconds ago" )
            #echo task took : $elapsed_time

            fw_size=$(stat -c "%s" $fastaFile)
            rc_size=$(stat -c "%s" $rcFile)
            margins=5000000000

            if [ $fw_size -gt $(($rc_size + $margins)) ] || [ $fw_size -lt $(($rc_size - $margins)) ]; then
                    echo 'error, fw and rc are not the same size !'
                    exit 1
            fi

        fi
        cat $rcFile >> $fastaFile
        rm $rcFile
}

##########################################
function splitReadFiles() {
    local readfilename=$1
    local readname=$2
    local readdir=$(dirname $readfilename)
    local subIndexes=$3
    local digits=${#subIndexes}

    split "${readdir}/${readname}.fasta" -n "l/${subIndexes}" -a $((digits)) -d ${readdir}/output_ --additional-suffix=.fasta

}

##########################################
function processReadFile(){

    local readFile=$1
    local readName=$2
    local outputDir=$3
    local zippedReads=$4
    local reverseComp=$5
    local utilsPath=$6

    local readFileFQ="${outputDir}/${readName}.fq"
    local readFileFA="${outputDir}/${readName}.fasta"

    #Unzip the input files
    if [ $zippedReads -eq 1 ];then
        unzipReadFile ${readFile} ${readName} ${outputDir}
    else
        mv ${readFile} ${outputDir}

    fi
    #echo "read File FQ " $readFileFQ
    if [ ! -f ${readFileFQ} ];then
        echo "cannot find read file " ${readFileFQ}
    fi

    #Create Plain Fastas
    createFasta ${readFileFQ} ${readName} ${utilsPath}

    #Add reverse complement
    if [ $reverseComp -eq 1 ];then
        createRevComp ${readFileFQ} ${readName} ${utilsPath}
    fi
    echo "read file processed " ${readFile}
    echo "output saved to $readdir/${readName}.fasta"
}

##########################################
# main function call
function main() {
#main $readFile  $outputDir $outputFileName $zippedReads $numberOfIndexes $reverseComp $pairedReads $pathToUtils $readPairFile
        local readFile=$1
        local outputDir=$2
        local outputFileName=$3
        local zippedReads=$4
        local numIndexes=$5
        local reverseComp=$6
        local pairedReads=$7
        local utilsPath=$8
        local readPairFile=$9

        local readFileName=$(basename $readFile)
        local readFileName=${readFileName%.*}
        #if zipped, remove both file extensions ( .fq.gz)
        if [ $zippedReads -eq 1 ]; then readFileName=${readFileName%.*}; fi

        local readFileFA="${outputDir}/${readFileName}.fasta"
        local outputReadFile="${outputDir}/${outputFileName}.fasta"

        #echo "read file FA: " $readFileFA
        echo "outputReadFile: " $outputReadFile
        processReadFile $readFile $readFileName $outputDir $zippedReads $reverseComp $utilsPath

        #Repeat steps for paired reads
        if [ ${pairedReads} -eq 1 ]; then
            local readPairName=$(basename $readPairFile)
            local readPairName=${readPairName%.*}

            #if zipped, remove both file extensions ( .fq.gz)
            if [ $zippedReads -eq 1 ]; then readPairName=${readPairName%.*}; fi

            local readPairFA="${outputDir}/$readPairName.fasta"
            #echo "readPairFA: " $readPairFA
            processReadFile $readPairFile $readPairName $outputDir $zippedReads $reverseComp $utilsPath
            cat $readFileFA $readPairFA > ${outputReadFile}
            rm $readFileFA
            rm $readPairFA
        else
        cat $readFileFA > ${outputReadFile}
        rm $readFileFA
        fi

        echo "processed fasta file  " ${outputReadFile}

        #Split Read Files
        if [ ${numIndexes} -gt 1 ]; then
            splitReadFiles ${outputReadFile} ${outputFileName} ${numIndexes}
        fi

}

function usage() {
        echo 'preprocessing script'
        echo ' '
        echo 'usage :'
        echo ' '
        echo 'preprocessing [options]'
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
#if [ $# -lt 5 ]; then
        #echo '==== ERROR : requires at least 5'
        #usage
#fi

# initialise all variables
readFile=''
readPairFile=''
numberOfIndexes=0
reverseComp=0
pairedReads=0
zippedReads=0
pathToUtils='./'
outputDir='./'
outputFileName='processedReads'

# retrieve arguments
while getopts ":z:r:p:n:c:o:f:u:" arg ; do
    case ${arg} in
        z) zippedReads=${OPTARG};;
        r) readFile=${OPTARG};;
        p) readPairFile=${OPTARG};;
        n) numberOfIndexes=${OPTARG};;
        c) reverseComp=${OPTARG};;
        o) outputDir=${OPTARG};;
        f) outputFileName=${OPTARG};;
        u) pathToUtils=${OPTARG};;
        *) usage;;
    esac
done

if [ "$readPairFile" != "" ]; then pairedReads=1; fi

# call the main function
echo 'preprocessing with: '
echo '-r readFilename ' $readFile
echo '-o outputDir  ' $outputDir
echo '-f outputFileName  ' $outputFileName
echo '-z zippedReads ' $zippedReads
echo '-n numberOfIndexes ' $numberOfIndexes
echo '-c reverseComplement ' $reverseComp
echo '-u pathToUtils  ' $pathToUtils
echo '-p readPairFile ' $readPairFile

main $readFile $outputDir $outputFileName $zippedReads $numberOfIndexes $reverseComp $pairedReads $pathToUtils  $readPairFile
