#!/bin/sh

string="string1
string2
string3
" # a empty string line

echo "$string"| (
	while read line; do
		echo $line "1"
	done
	) | while read m; do
			echo $m "2"
		done
