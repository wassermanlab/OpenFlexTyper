#!/bin/bash

########################################################################
###
### Copyright (c) 2018, Wasserman lab
###
### FILE        install.sh
###
### DESCRIPTION This is the install.sh script for the project.
###             We use conda in order to install the application.
###
### Initial version @ Godfrain Jacques KOUNKOU
###
########################################################################

# set -e

function install() 
{
	CURRENT_DIR=$(pwd)
	MINI_CONDA_INSTALL_DIR=$(pwd | awk -F'/' '{print "/"$2"/"$3"/miniconda3"}')

	wget https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh
	bash Miniconda3-latest-Linux-x86_64.sh

	source ${MINI_CONDA_INSTALL_DIR}/etc/profile.d/conda.sh
	conda create --prefix ../openFlexTyper
	conda activate ${CURRENT_DIR}/../openFlexTyper
	conda install qt
	conda install -c conda-forge sdsl-lite
	mkdir build
	cd build/
	qmake ..
	make
}

install
