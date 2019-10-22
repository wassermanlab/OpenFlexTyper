#!/bin/bash

########################################################################
###
### Copyright (c) 2018, Wasserman lab
###
### FILE        uninstall.sh
###
### DESCRIPTION This is the build.sh script for the project
###
### Initial version @ Godfrain Jacques KOUNKOU
###
########################################################################

# set -e

if [[ $(id -u) -ne 0 ]]; then 
   echo "Please run as root"
   exit 1 
fi

# usage
function usage() {
   echo "Usage: $0 [-d | --deletedeps, -h | --help] or without param" 1>&2
   exit 1
}


# install dependencies
function uninstallDeps() {
   echo 'removing dependencies'
   sudo apt-get remove -y curl graphviz libdivsufsort-dev libdivsufsort3 libsdsl-dev libsdsl3             \
                          libpqxx-dev libpqxx-4.0v5 libgtest-dev libboost-all-dev g++-8 gcc-8             \
			   			  dialog && apt-get install -y whiptail git zlib1g-dev              			  \
			   		      libbz2-dev cmake wget libx11-dev libdbus-glib-1-2 qt5-qmake libx11-xcb-dev      \
			  	 	      libglu1-mesa-dev libxrender-dev build-essential qt5-default qtdeclarative5-dev  \
			   			  libqt5webview5-dev
}

# install the application
function uninstallApp() {
   echo 'uninstalling the application'
   rm -rf /opt/FlexTyper
   sed -i 's/opt\/FlexTyper\/bin\:\///g' /etc/environment
}

SHORT=hd
LONG=help,deletedeps
OPTS=$(getopt --options $SHORT --long $LONG --name "$0" -- "$@")

if [ $? != 0 ]; then
   echo "Failed to parse options...exiting." >&2
   exit 1
fi


eval set -- "$OPTS"

while true ; do
  case "$1" in
    -h | --help)
      usage 
      exit 0
      ;;
    -d | --deletedeps)
      uninstallDeps
      break;
      ;;
    --)
      break;
      ;;
    \?)
      usage
      exit 1
      ;;
  esac
done

uninstallApp

echo "Thanks $user, Uninstallation finished ! Please restart the System for the changes to take effects"
