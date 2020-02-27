#!/bin/bash

## Sockeye configuration header
#PBS -A xxxxx
#PBS -N test_name
#PBS -V
#PBS -M xxx@xxx
#PBS -l select=1:ncpus=32:mem=250gb
#PBS -l walltime=24:0:0

## Cedar configuration header
##SBATCH --account=xxxxx
##SBATCH --time=10:00:00
##SBATCH --mem-per-cpu=100G
##SBATCH --nodes=1
##SBATCH --mail-user=xxx@xxx
##SBATCH --mail-type=END
##SBATCH --array=1-1%1


export QT_QPA_PLATFORM='offscreen'
cd $PBS_O_WORKDIR

python tst_paper_results.py

