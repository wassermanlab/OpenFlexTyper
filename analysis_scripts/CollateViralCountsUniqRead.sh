# This script will collate results from the pathogen query for the two sets of viral analyses.
# First Viral analyses is pure virus
# Next is mixed virus

# Pure viral analysis collation
# initialize a tsv
SUMMARYFILE=/scratch/ex-ofornes-1/RICHMOND/FLEXTYPER/RESUBMISSION/NonMixedVirusIndexes/CollatedNonMixedVirusFull.csv
rm -f $SUMMARYFILE
printf "Sample\nParameters\nEBV\nFR751039\nHIV-1\nU21941\nSearchTime" >> $SUMMARYFILE


FULL_DIR=/scratch/ex-ofornes-1/RICHMOND/FLEXTYPER/RESUBMISSION/NonMixedVirusIndexes/
cd $FULL_DIR
DIRS=($(ls -d $FULL_DIR*/))
for dir in ${DIRS[@]}
do
	printf $dir
	IFS='/' read -a array <<< $dir
	Sample=${array[-1]}
	echo $Sample

	# change to sample directory, we now know the sample name
	cd $dir
	Files=($(ls $dir/*UniqReads*))
	for file in ${Files[@]}
	do
		# ignore other files in the dir
		if [[ $file != *"FTsearch"* ]];
		then
			continue

		# Log file
		elif [[ ${file: -3} == *'log'* ]];
		then
			continue
			#echo $file

		else
			IFS='_' read -a array2 <<< $file
			params=${array2[-1]}

			# initialize a temp file, then paste to existing master file
			TMPFILE=${Sample}_${params}.tmp
			printf "$Sample\n" >> $TMPFILE
			printf "$params\n" >> $TMPFILE
			cut -f4 $file | tail -n+2 >> $TMPFILE

			# Grab time from the log file, which is called $file.log
			TIME=`grep "parallelSearch DONE" ${file}.log | sed 's/[^0-9]*//g'`
			printf "$TIME\n" >> $TMPFILE

			# add to master file
			paste -d , $SUMMARYFILE $TMPFILE >> ${SUMMARYFILE}.tmp
			mv ${SUMMARYFILE}.tmp $SUMMARYFILE
			rm $TMPFILE
		fi
		
	done
		

done





