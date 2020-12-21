##########################################
#!/bin/bash

#PBS -l walltime=16:00:00,select=1:ncpus=40:mem=160gb
#PBS -A ex-ofornes-1
#PBS -m abe
#PBS -M prichmond@cmmt.ubc.ca

# Initialize flextyper
FLEXTYPER_REPO=/scratch/ex-ofornes-1/RICHMOND/FLEXTYPER/RESUBMISSION/Test_flextyper/OpenFlexTyper/
cd $PBS_O_WORKDIR

# Define Kmers & Strides
Kmers=( 15 30 100 )
Strides=( 1 5 )
Samples=( "EBV-100" "HIV1-100" "U21941-100" "FR751039-100" "ERR2322364")
MaxOcc=( 2000 50 )
for k in ${Kmers[@]}
do
	for s in ${Strides[@]}
	do
		for sample in ${Samples[@]}
		do
			for maxOcc in ${MaxOcc[@]}
			do 
				echo "Searching $sample with k=$k, s=$s, maxOcc=$maxOcc"
				mkdir -p /scratch/ex-ofornes-1/RICHMOND/FLEXTYPER/RESUBMISSION/NonMixedVirusIndexes/${sample}/
				cd /scratch/ex-ofornes-1/RICHMOND/FLEXTYPER/RESUBMISSION/NonMixedVirusIndexes/$sample/

				# Search Unique
				$FLEXTYPER_REPO/build/flextyper search \
					-c /scratch/ex-ofornes-1/RICHMOND/FLEXTYPER/RESUBMISSION/NonMixedVirusIndexes/${sample}_NonMixedVirus.ini \
					-k $k -s $s -m $maxOcc -u \
					${sample}_FTsearch

				# Search NonUnique
				$FLEXTYPER_REPO/build/flextyper search \
					-c /scratch/ex-ofornes-1/RICHMOND/FLEXTYPER/RESUBMISSION/NonMixedVirusIndexes/${sample}_NonMixedVirus.ini \
					-k $k -s $s -m $maxOcc \
					${sample}_FTsearch
	


			done
		done

	done
done
