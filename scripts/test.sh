#!/bin/bash

########################################################################
###
### Copyright (c) 2018, Wasserman lab
###
### FILE        build.sh
###
### DESCRIPTION This is the build.sh script for the project
###
### Initial version @ Godfrain Jacques KOUNKOU
###
########################################################################

set -e

#______________________________________
function installGTest() {
	current_dir=$PWD
	wget https://github.com/google/googletest/archive/release-1.8.0.tar.gz
	tar xzf release-1.8.0.tar.gz
	cd googletest-release-1.8.0
	mkdir build && cd build
	cmake ..
	make -j
	cp -r ../googletest/include /usr/local/include
	cp -r ./googlemock/gtest/libgtest*.a /usr/local/lib/
	cp -r ./googlemock/libgmock*.a /usr/local/lib/
	cd $current_dir
}

#______________________________________
function test() {
	if [ -d flextyper/test ]; then
		cd flextyper/test/
	    	qmake
	    	make
	    	./test
    	fi
	if [ -d fmindex/test ]; then
		cd fmindex/test/
		qmake
		make
		./test
	fi
}

# __ main__
current_dir=$PWD
installGTest
test
cd $current_dir
