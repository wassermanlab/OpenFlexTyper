#!/bin/bash

########################################################################
###
### Copyright (c) 2018, Wasserman lab
###
### FILE        compile.sh
###
### DESCRIPTION This is the compile.sh script for the project
###
### Initial version @ Godfrain Jacques KOUNKOU
###
########################################################################

set -e 

function build() {
	mkdir build
	cd build
	qmake ..
	make
}

# __main__
current_dir=$PWD
build
cd $current_dir
