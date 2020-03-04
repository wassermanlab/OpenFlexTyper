#!/bin/bash

##########################################
# 
# Copyright (c) Wasserman lab 2020
# 
# DESCRIPTION This is an example using the master_script.sh
#             In this example, we have a mix of simulated viral data
#             containing 3 viruses.
#
# AUTHOR      Godfrain Jacques Kounkou
#
##########################################

bash ../scripts/master_script.sh -r MixedVirus_100 \
                                 -s setting.ini    \
                                 -n 1              \
                                 -c 1              \
                                 -p ../build/bin/
