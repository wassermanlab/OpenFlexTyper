#!/bin/bash

#PBS -A st-wasserww-1
#PBS -N ERR2322364 
#PBS -V
#PBS -M gkounkou@cmmt.ubc.ca
#PBS -l select=1:ncpus=32:mem=100gb
#PBS -l walltime=5:0:0

export QT_QPA_PLATFORM='offscreen'
cd $PBS_O_WORKDIR

python tst_paper_results.py
