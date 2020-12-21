##########################################
#!/bin/bash

#PBS -l walltime=12:00:00,select=1:ncpus=40:mem=160gb
#PBS -A ex-ofornes-1
#PBS -m abe
#PBS -M prichmond@cmmt.ubc.ca

# Initialize flextyper
FLEXTYPER_REPO=/scratch/ex-ofornes-1/RICHMOND/FLEXTYPER/RESUBMISSION/Test_flextyper/OpenFlexTyper/

cd $PBS_O_WORKDIR

# Run Flextyper Search
Samples=( "Patient-1" "Patient-2" "Patient-3" "Patient-4" "Patient-5" )

for sample in ${Samples[@]}
do
	echo $sample
	cd /scratch/ex-ofornes-1/RICHMOND/FLEXTYPER/RESUBMISSION/MixedPatientIndexes/$sample/
	$FLEXTYPER_REPO/build/flextyper search \
	        -c /scratch/ex-ofornes-1/RICHMOND/FLEXTYPER/RESUBMISSION/MixedPatientIndexes/${sample}_MixedVirus_UniqReads.ini \
		-k 30 -s 5 --maxOcc 2000 -u \
		${sample}_FTsearched_UniqReads

	$FLEXTYPER_REPO/build/flextyper search \
                -c /scratch/ex-ofornes-1/RICHMOND/FLEXTYPER/RESUBMISSION/MixedPatientIndexes/${sample}_MixedVirus_UniqReads.ini \
                -k 100 -s 25 --maxOcc 2000 -u \
                ${sample}_FTsearched_UniqReads
	
done
