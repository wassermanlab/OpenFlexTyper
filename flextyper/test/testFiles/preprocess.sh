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


        gunzip -c ${readFile} >  "${readName}.fq"

        #elapsed_time=$( date +%s.%N --date="$start_time seconds ago" )
        #echo uncommpress took : $elapsed_time


}

##########################################
function createFasta()
{

#createFasta ${readFileFQ} ${readSetName} ${utilsPath} ${outputDir}
        local readFileFQ=$1
        local readSetName=$2
        local utilsPath=$3
        local outputDir=$4

        local fastaFile="$outputDir/${readSetName}.fasta"
        echo "createFasta: fasta file :" ${fastaFile}
        if [[ -f $fastaFile ]] ; then
                echo 'createFasta: fasta file already exists' ${fastaFile}
                return
        fi


        if [ ! -f ${utilsPath}/seqtk ]; then
            echo "cant find" ${utilsPath}"seqtk"
            if [ ! -f ${utilsPath}/seqtk/seqtk ]; then
                echo "cannot find seqtk, installing in " ${utilsPath}
                cd ${utilsPath}
                buildSeqTk
                utilsPath=${utilsPath}seqtk
                echo "installed seqtk in " ${utilsPath}
            else
                echo "found seqtk in " ${utilsPath}seqtk
                utilsPath=${utilsPath}seqtk
            fi
        fi
        echo "creating fasta " ${readFileFQ} "into " $fastaFile
        echo "running ${utilsPath}/seqtk seq -A -C -U ${readFileFQ} | egrep -v '[>]' > ${fastaFile} "
        ${utilsPath}/seqtk seq -A -C -U ${readFileFQ} | egrep -v '[>]' > $fastaFile


        if [ -f $fastaFile ]
        then
            if [ ! -s $fastaFile ]
            then
                echo "createFasta: " $fastaFile " is empty"
                exit 1
            fi
        else
            echo "createFasta: " $fastaFile " not found"
            exit 1
        fi
        echo  "createFasta: " $fastaFile " created"
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
                if [ ! -f ${utilsPath}/seqtk/seqtk ]; then
                    echo "cannot find seqtk, installing in " ${utilsPath}
                    cd ${utilsPath}
                    buildSeqTk
                    utilsPath=${utilsPath}/seqtk
                else
                    #echo "found seqtk in " ${utilsPath}seqtk
                    utilsPath=${utilsPath}/seqtk
                fi
            fi

            #echo "create reverse complement fasta file from" ${readFQ} "into" $rcFile
            ${utilsPath}/seqtk seq -A -C -U -r ${readFQ} | egrep -v '[>]' > $rcFile

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

    echo "splitReadFiles: read dir " readdir
    echo "splitReadFiles: read name " readname
    echo "splitReadFiles: subIndexes " subIndexes

    split "${readdir}/${readname}.fasta" -n "l/${subIndexes}" -a $((digits)) -d ${readdir}/output_ --additional-suffix=.fasta

}

##########################################
function processReadFile(){
    #processReadFile $readFile $readFileName $readSetName $ppfDir $zippedReads $reverseComp $utilsPath
    local readFile=$1
    local readFileName=$2
    local readSetName=$3
    local outputDir=$4
    local zippedReads=$5
    local reverseComp=$6
    local utilsPath=$7


    local readFileFA="${readFileName}.fasta"
    local readFileFQ="${readFileName}.fq"
    local outputFastaFile="$outputDir/${readSetName}.fasta"
    echo "Process Read File: readName: " $readFileName

    #Unzip the input files
    if [ $zippedReads -eq 1 ];then
        unzipReadFile ${readFile} ${readFileName}
    fi

    echo "read File FQ " $readFileFQ
    if [ ! -f ${readFileFQ} ];then
        echo "Process Read File: cannot find read file " ${readFileFQ}
        exit 1
    fi

    #Create Plain Fastas
    createFasta ${readFileFQ} ${readSetName} ${utilsPath} ${outputDir}

    if [ ! -f ${outputFastaFile} ];then
        echo "Process Read File: cannot find fasta file " ${outputFastaFile}
        exit 1
    fi

    #Add reverse complement
    if [ $reverseComp -eq 1 ];then
        createRevComp ${readFileFQ} ${readSetName} ${utilsPath} ${outputDir}
    fi
    if [ ! -f ${readFileFA} ];then
        echo "Process Read File: cannot find fasta file after reverse Comp" ${outputFastaFile}
        exit 1
    fi
    if [ ! -s ${readFileFA} ];then
        echo "Process Read File: fasta file is empty after reverse Comp" ${outputFastaFile}
        exit 1
    fi
    echo "Process Read File: read file processed " ${outputFastaFile}
    echo "Process Read File: output saved to "${outputFastaFile}
}

##########################################
# main function call
function main() {
#main $readFile  $outputDir $readSetName $zippedReads $numberOfIndexes $reverseComp $pairedReads $pathToUtils $readPairFile
        local readFile=$1
        local ppfDir="$2/tmp_ppf"
        local readSetName=$3
        local zippedReads=$4
        local numIndexes=$5
        local reverseComp=$6
        local pairedReads=$7
        local utilsPath=$8
        local readPairFile=$9

        echo "main: ppf dir: " $ppfDir


        local readFileName=$(basename $readFile)
        local readFileName=${readFileName%.*}
        #if zipped, remove both file extensions ( .fq.gz)
        if [ $zippedReads -eq 1 ]; then readFileName=${readFileName%.*}; fi

        local readFileFA="${readFileName}.fasta"
        local readFileFQ="${readFileName}.fq"
        local outputReadFile="${ppfDir}/${readSetName}.fasta"


        if [ ! -d ${utilsPath} ]; then
            echo "Utils folder doesnt exist " $utilsPath " , mkdir"
            mkdir ${utilsPath}
        fi
        echo "main: read File" $readFile
        echo "main: read file FA: " $readFileFA
        echo "main: read file FQ: " $readFileFQ
        echo "main: output file FA: " $outputReadFile
        echo "main: read File Name: " $readFileName
        echo "main: read Set Name: " $readSetName
        processReadFile $readFile $readFileName $readSetName $ppfDir $zippedReads $reverseComp $utilsPath

        if [ ! ${readFileFA} == ${outputReadFile} ]; then
            echo "copying " $readFileFA " to " $outputReadFile
            cat $readFileFA > $outputReadFile
        fi
        #Repeat steps for paired reads
        if [ ${pairedReads} -eq 1 ]; then
            local readPairName=$(basename $readPairFile)
            local readPairName=${readPairName%.*}

            #if zipped, remove both file extensions ( .fq.gz)
            if [ $zippedReads -eq 1 ]; then readPairName=${readPairName%.*}; fi

            local readPairFA="${ppfDir}/$readPairName.fasta"
            echo "main: readPairFA: " $readPairFA
            processReadFile $readPairFile $readPairName $ppfDir $zippedReads $reverseComp $utilsPath

            cat $readPairFA >> $outputReadFile

        fi

        #Split Read Files
        if [ ${numIndexes} -gt 1 ]; then
            #echo "splitting Read Files into " ${numIndexes}
            splitReadFiles ${outputReadFile} ${readSetName} ${numIndexes}
        fi

        if [ -f $outputReadFile ]
        then
            if [ ! -s $outputReadFile ]
            then
                echo "File is empty"
                exit 1
            fi
        else
            echo "File not found"
            exit 1
        fi

        echo "preprocessing complete " ${outputReadFile}
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
numberOfIndexes=1
reverseComp=0
pairedReads=0
zippedReads=0
pathToUtils=${PWD}
outputDir=${PWD}

# retrieve arguments
while getopts ":z:r:p:n:c:o:f:u:" arg ; do
    case ${arg} in
        z) zippedReads=${OPTARG};;
        r) readFile=${OPTARG};;
        p) readPairFile=${OPTARG};;
        n) numberOfIndexes=${OPTARG};;
        c) reverseComp=${OPTARG};;
        o) outputDir=${OPTARG};;
        f) readSetName=${OPTARG};;
        u) pathToUtils=${OPTARG};;
        *) usage;;
    esac
done

if [ "$readPairFile" != "" ]; then pairedReads=1; fi

# call the main function
echo 'preprocessing with: '
echo '-r readFile ' $readFile
echo '-f readSetName ' $readSetName
echo '-o outputDir  ' $outputDir
echo '-z zippedReads ' $zippedReads
echo '-n numberOfIndexes ' $numberOfIndexes
echo '-c reverseComplement ' $reverseComp
echo '-u pathToUtils  ' $pathToUtils
echo ' using paired reads ' $pairedReads
echo '-p readPairFile ' $readPairFile

main $readFile $outputDir $readSetName $zippedReads $numberOfIndexes $reverseComp $pairedReads $pathToUtils  $readPairFile
