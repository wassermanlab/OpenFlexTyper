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
	conda config --add channels conda-forge
	conda create --prefix ../openFlexTyper_env --file requirements.txt
	conda activate ../openFlexTyper_env
	mkdir build
	cd build
	qmake ..
	make
}

install
