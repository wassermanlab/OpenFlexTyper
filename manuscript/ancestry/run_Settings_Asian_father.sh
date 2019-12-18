#!/bin/bash

#PBS -A st-wasserww-1
#PBS -N ancestry_test_asian_father
#PBS -V
#PBS -M gkounkou@cmmt.ubc.ca
#PBS -l select=1:ncpus=32:mem=100gb
#PBS -l walltime=20:0:0

export QT_QPA_PLATFORM='offscreen'
cd $PBS_O_WORKDIR

FLEX_BIN='/scratch/st-wasserww-1/FLEXTYPER/OpenFlexTyper/build'
time $FLEX_BIN/flextyper searching -c Settings_Asian_father.ini