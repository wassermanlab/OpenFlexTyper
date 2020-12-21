##########################################
#!/bin/bash

#PBS -l walltime=14:00:00,select=1:ncpus=20:mem=120gb
#PBS -A ex-ofornes-1
#PBS -m abe
#PBS -M prichmond@cmmt.ubc.ca

# Initialize flextyper
FLEXTYPER_REPO=/scratch/ex-ofornes-1/RICHMOND/FLEXTYPER/RESUBMISSION/Test_flextyper/OpenFlexTyper/

cd $PBS_O_WORKDIR

# Run Flextyper Search
Samples=( "Patient-4" )

for sample in ${Samples[@]}
do
	echo $sample
	DATE=`date`
	echo $DATE
	cd /scratch/ex-ofornes-1/RICHMOND/FLEXTYPER/RESUBMISSION/MixedPatientIndexes/$sample/
	# No UniqR, Single-end, k30, s5
	$FLEXTYPER_REPO/build/flextyper search \
	        -c /scratch/ex-ofornes-1/RICHMOND/FLEXTYPER/RESUBMISSION/MixedPatientIndexes/${sample}_MixedVirus.ini \
		-k 30 -s 5 --maxOcc 10000 -u \
		${sample}_FTsearched_SE_noUniq
	# No UniqR, pair-end, k30, s5
	$FLEXTYPER_REPO/build/flextyper search \
	        -c /scratch/ex-ofornes-1/RICHMOND/FLEXTYPER/RESUBMISSION/MixedPatientIndexes/${sample}_MixedVirus_AsPairs.ini \
		-k 30 -s 5 --maxOcc 10000 -u \
		${sample}_FTsearched_PE_noUniq

	# UniqR, Single-end, k30, s5
	$FLEXTYPER_REPO/build/flextyper search \
	        -c /scratch/ex-ofornes-1/RICHMOND/FLEXTYPER/RESUBMISSION/MixedPatientIndexes/${sample}_MixedVirus_UniqReads.ini \
		-k 30 -s 5 --maxOcc 10000 -u \
		${sample}_FTsearched_SE_Uniq
	# UniqR, pair-end, k30, s5
	$FLEXTYPER_REPO/build/flextyper search \
	        -c /scratch/ex-ofornes-1/RICHMOND/FLEXTYPER/RESUBMISSION/MixedPatientIndexes/${sample}_MixedVirus_UniqReads_AsPairs.ini \
		-k 30 -s 5 --maxOcc 10000 -u \
		${sample}_FTsearched_PE_Uniq
done
