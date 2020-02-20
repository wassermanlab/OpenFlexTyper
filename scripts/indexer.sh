#!/bin/bash

#SBATCH --account=xxx-xxxx
#SBATCH --time=23:00:00
#SBATCH --mem-per-cpu=1100G
#SBATCH --nodes=1
#SBATCH --mail-user=xxxxxx@xxxx
#SBATCH --mail-type=END
#SBATCH --array=1-1%1

export QT_QPA_PLATFORM='offscreen'

SCRIPTS='path to utilities seqtk, flextyper binary'

#---------------------------------------------------------------------------------------
# Uncomment if working on a local machine
# if [ $# -ne 3 ]; then
#	echo 'brief : indexer.sh indexes the files given in a text file as parameter'
#	echo '        each file to be indexed corresponds to a line inside readname.txt'
#	echo "Usage : $0 <filesToTransform>"
#	echo "Eg :"
#	echo "sbatch indexer.sh files.txt 1 mono"
#	exit 0
# fi
# FILES=$1
# LINE=$2
#---------------------------------------------------------------------------------------

FILES='readname.txt'
LINE=1
FMIND="${SCRIPTS}/flextyper indexing "
SEQTK=${SCRIPTS}/seqtk
THREADS=30

#______________________________________________________________
function uncompress() 
{
	echo 'uncompress files'
	FILE=$(cat $FILES | sed -n "$TASK_ID"p)
	start_time=$( date +%s.%N )

	if [ -f "${FILE}.fq" ]; then
		echo 'uncompressed file exists'
		return
	fi

	R1_FILE=$(ls ${FILE}_1*)
	R2_FILE=$(ls ${FILE}_2*)

	gunzip -c ${R1_FILE} >  "${FILE}.fq"
	gunzip -c ${R2_FILE} >> "${FILE}.fq"
	elapsed_time=$( date +%s.%N --date="$start_time seconds ago" )
	echo uncommpress took : $elapsed_time
}

#______________________________________________________________
function createForwardAndReverseComplement()
{
	mv $1 temp.fq 

	echo 'create forward and reverse complement'
	if [ -f fw_pre_tmp_output.fasta ] && [ -f rc_pre_tmp_output.fasta ]; then
		echo 'forward and reverse complement file exists'
		return
	fi

	if [ $# -eq 1 ]; then
		start_time=$( date +%s.%N )
		${SEQTK} seq -A -C -U    temp.fq | egrep -v '[>]' > fw_pre_tmp_output.fasta
		${SEQTK} seq -A -C -U -r temp.fq | egrep -v '[>]' > rc_pre_tmp_output.fasta
		elapsed_time=$( date +%s.%N --date="$start_time seconds ago" )
		echo create fw and rc took : $elapsed_time

		fw_size=$(stat -c "%s" fw_pre_tmp_output.fasta)
		rc_size=$(stat -c "%s" rc_pre_tmp_output.fasta)
		margins=5000000000

		if [ $fw_size -gt $(($rc_size + $margins)) ] || [ $fw_size -lt $(($rc_size - $margins)) ]; then
			echo 'error, fw and rc are not the same size !'
			exit 1
		fi	
	fi

	cat fw_pre_tmp_output.fasta rc_pre_tmp_output.fasta > "output_${TASK_ID}.fasta"
}

#______________________________________________________________
function filterFastaByLastTwoCharacters()
{
	echo 'filter by last 2 chars'
        if [ -f output.fasta ]; then
		echo 'output.fasta exists'
		return
	fi

	start_time=$( date +%s.%N )

	PATTERNS=(AA AC AG AT CA CC CG CT GA GC GG GT TA TC TG TT)
	for e in ${PATTERNS[@]}; do
		grep ${e}$ tmp_output.fasta | sort -rn --parallel=30 > temp_${e}.fasta
	done

	# copy files in tmp_output
	if [ ! -d tmp_output ]; then
		mkdir tmp_output
	fi
	ls * | egrep '^temp*[A-T]*' | xargs mv -t tmp_output/

	cat $(ls -1 -d tmp_output/*) > output.fasta
	elapsed_time=$( date +%s.%N --date="$start_time seconds ago" )
	echo filter fasta by 2 last chars took : $elapsed_time
}

#______________________________________________________________
function removeDuplicates() 
{
	echo 'removing duplicates'
	time awk '!a[$0]++' $1 > $2
}

#______________________________________________________________
function removeNs()
{
	echo 'removing Ns'
	sed '/N/d' $1  > $2
}

#______________________________________________________________
function concatenate()
{
	cat $1 $2 > $3 
}

#______________________________________________________________
function splitReads()
{
	echo 'split reads'
	split $1 -n "l/$2" -a 1 -d output_
}

#______________________________________________________________
function createIndex()
{
	echo 'create index'
	start_time=$( date +%s.%N )
	cmd="${FMIND} -f $1 -o . -x ${1}.fm9"
	eval $cmd
	echo ${SLURM_ARRAY_JOB_ID}_$TASK_ID >> jobs.log
	elapsed_time=$( date +%s.%N --date="$start_time seconds ago" )
	echo creating index took : $elapsed_time
}

#______________________________________________________________
function createMultipleIndexes() 
{
	echo 'creating multiple indexes'

	files=$(ls output_*)
	for e in ${files[@]}; do
		if [ -f $e.fm9 ]; then
			continue
		fi
		time createIndex $e
	done
}

#______________________________________________________________
function moveFileToCorrectName()
{
	echo 'moving files'
	mv output.fasta.fm9 "${1}.fm9"
	# rm *.fq 
	# rm *.fasta
	# rm -rf tmp_output
	rm -rf *.sdsl
}

#______________________________________________________________
function archiveFiles()
{
	if [ -d garbage_${TASK_ID} ]; then
		echo 'directory exists'
	else
		mkdir garbage_${TASK_ID}
	fi
	mv *.fasta garbage_${TASK_ID}/
	mv *.fq garbage_${TASK_ID}/
}

#______________________________________________________________
function generateCheckSum()
{
	md5sum $1 > md5.txt
}

# --- generate indexes for one R1  and R2 files ---
function generateIndex()
{
	# uncompress R1 and R2
	time uncompress $FILES

	SPE=$(cat $FILES | sed -n "$TASK_ID"p)

	# create fw and rc
	time createForwardAndReverseComplement ${SPE}.fq

	# remove Ns if the parameter is set
	if [ "$2" = true ]; then
		echo 'removing Ns'
		removeNs "output_${TASK_ID}.fasta" temp.fasta
		mv temp.fasta "output_${TASK_ID}.fasta"
	fi

	# remove duplicates if the parameter is set
	if [ "$3" = true ]; then
		echo 'removing duplicates'
		removeDuplicates "output_${TASK_ID}.fasta" temp.fasta
		mv temp.fasta "output_${TASK_ID}.fasta"
	fi
	
	# split reads if requested
	if [ "$1" -gt 1 ]; then
	        time splitReads "output_${TASK_ID}.fasta" $1
	elif [ "$1" -eq 1 ]; then
		time mv "output_${TASK_ID}.fasta" output_0
	else
		echo "$1" ' indexes requested, terminating the application'
		exit 0
	fi
	
	# create index
	outputs=($(ls output_[0-9]))

	for file in ${outputs[@]}; do
		time createIndex $file
	done
}

# main call

TASK_ID=$LINE

echo "setting TASK_ID to ${TASK_ID} by default"

# echo 'generating one index'
# generateIndex 1 false false
echo 'generating multiple indexes'
generateIndex 8 false false


#---------------------------------------------------------------------------------------
# Uncomment if working on a local machine
# if [ $3 == mono ]; then 
#	echo 'generating one index'
#	generateIndex 1 false false
# elif [ $3 == multi ]; then
#	echo 'generating multiple indexes'
#	generateIndex 8 false false
# else
#	echo 'not supported, provide indexing type'
# fi
#---------------------------------------------------------------------------------------
