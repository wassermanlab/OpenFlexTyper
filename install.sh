#!/bin/bash

########################################################################
###
### Copyright (c) 2020, Wasserman lab
###
### FILE        install.sh
###
### DESCRIPTION This is the install.sh script for the project.
###             We use conda in order to install the application.
###
### Initial version @ Godfrain Jacques KOUNKOU
### Modified @ Phillip Richmond
########################################################################

# set -e


##########################################
# DESC This function will find all FlexTyper dependencies and build FlexTyper 
# ARGS This function doesnt require any arguments
# RSLT The side effect is the newly created FlexTyper directory with the FlexTyper binary
##########################################
function buildFlexTyper() 
{
	DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
	OPT_DIR=${DIR}/opt
	mkdir -p ${OPT_DIR}
	pushd ${OPT_DIR}
	MINI_CONDA_INSTALL_DIR=$OPT_DIR/miniconda3

	wget https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh
	bash Miniconda3-latest-Linux-x86_64.sh -b -p $MINI_CONDA_INSTALL_DIR 

	source ${MINI_CONDA_INSTALL_DIR}/etc/profile.d/conda.sh
	conda env create --prefix ${OPT_DIR}/openFlexTyper -f $DIR/OpenFlexTyper_CondaEnv.yml 
	cd $DIR
	conda activate opt/openFlexTyper
	mkdir -p build
	cd build/
	qmake ..
	make
}

##########################################
# DESC This function will clone seqtk repository and build it
# ARGS This function doesnt take any arguments
# RSLT The side effect is the newly create seqtk directory with the seqtk binary
##########################################
function buildSeqTk() {
        DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
        git clone https://github.com/lh3/seqtk.git
        cd seqtk
        make
        cd $DIR
}

##########################################
# DESC This function creates an utils directory inside the build directory
#      It contains flextyper and seqtk
# ARGS This function takes no arguments
# RSLT The side effect is the new utils directory
##########################################
function createUtilsDirectory() {
        if [ ! -d utils ]; then
                mkdir utils
                cp seqtk/seqtk utils/seqtk
                cp flextyper utils/flextyper
        fi
}

buildFlexTyper
buildSeqTk
createUtilsDirectory
