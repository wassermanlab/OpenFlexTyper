#!/bin/bash

READ_FILE="/var/tmp/TestData/ERR194147/output.fasta"

k1="k1.txt"
k2="k2.txt"
k3="k3.txt"
k4="k4.txt"
k5="k5.txt"

#______________________________________
function searchKmersFgrep() 
{
	while read line; do
		fgrep -n --color $line $1
	done < $2
}
#______________________________________
function searchKmersEgrep() 
{
	while read line; do
		egrep -n --color $line $1
	done < $2
}
#______________________________________
function searchKmersGrep() 
{
	while read line; do
		grep -n --color $line $1
	done < $2
}

# grep results
# time searchKmersFgrep $READ_FILE $k1 > flog1
# time searchKmersFgrep $READ_FILE $k2 > flog2
# time searchKmersFgrep $READ_FILE $k3 > flog3
# time searchKmersFgrep $READ_FILE $k4 > flog4
# time searchKmersFgrep $READ_FILE $k5 > flog5

# time searchKmersEgrep $READ_FILE $k1 > elog6
# time searchKmersEgrep $READ_FILE $k2 > elog7
# time searchKmersEgrep $READ_FILE $k3 > elog8
# time searchKmersEgrep $READ_FILE $k4 > elog9
# time searchKmersEgrep $READ_FILE $k5 > elog10

time searchKmersGrep $READ_FILE $k1 > log11
time searchKmersGrep $READ_FILE $k2 > log12
time searchKmersGrep $READ_FILE $k3 > log13
time searchKmersGrep $READ_FILE $k4 > log14
time searchKmersGrep $READ_FILE $k5 > log15

