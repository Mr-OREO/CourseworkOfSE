#FileName: 1.sh
#Author: Ziteng Wang
#Create Date: 2020-06-19
#Last Modify: 2020-06-20
#Description: 
#  if 1 ordinary file name argument: print owner name and modify date
#  if more than 1 argument: print error info
#  if the file is not an ordinary file: print error info

#! /bin/bash
if test $# -ne 1	# Not 1 Argument
	then
		echo "Exactly 1 argument is expected"	# Error info
		exit 1		# Error
fi
if test -f "$1"		# Ordinary File
	then
		filename="$1"		# Ordinary File
		set -- $(ls -l $filename)	# List result
		user_name="$3"		# Owner
		modify_date="$6$7 $8"	# Date
		echo "Name	Date"	# Head line
		echo "$user_name	$modify_date"	# Print
		exit 0
fi
echo "$0: argument should be an ordinary file"	# Error
exit 1
