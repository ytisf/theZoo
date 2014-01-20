#!/bin/bash

bold=`tput bold`
normal=`tput sgr0`
green_plus='\e[00;32m[+]\e[00m'
red_min='\e[01;31m[-]\e[00m'

# This file rebuilds the index.csv file based on the local index.log file in each folder.

# Backup previous 
mv conf/index.csv conf/Index.Backup.csv

# finds all index.log files:

find `pwd` -name 'index.log' > /tmp/indexrebuild.tmp
touch conf/index.csv
i=1
cat /tmp/indexrebuild.tmp | while read file ; do
	let string="$i"
	string="$string,`echo "$file"`,`cat "$file"`,"
	echo -e "$green_plus $i was added successfully"
	echo "$string" >> conf/index.csv
	let i=i+1
done

linesofdb=`wc -l < conf/index.csv`

if [ $linesofdb = 0 ]; then
	echo ""
	echo -e "$red_min   No index files were detected!"
	echo ""
	exit 0
fi
if [ $linesofdb > 0 ]; then
	echo ""
	echo -e "$green_plus   Rebuilt index with $linesofdb malwares. Be safe."
	echo "       Go and have some fun :)"
	echo ""
	exit 1
fi

