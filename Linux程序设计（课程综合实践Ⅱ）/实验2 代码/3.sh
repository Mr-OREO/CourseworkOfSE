#FileName: 3.sh
#Author: Ziteng Wang
#Create Date: 2020-06-19
#Last Modify: 2020-06-20
#Description: 
#  input 1 string argument: 
#    ignore non-alphabetic character, check if palindrome

#! /bin/bash
echo -n "Input a string:"
read line		# read in a var in $line
line=`echo $line | tr -cd [:alpha:]`	# delete non-alpha characters
rline=`echo $line | rev`				# reverse the string
if [[ $line == $rline ]]				# if $line equals to reverse $line
	then
		echo "$line is palindrome"		# palindrome
	else
		echo "$line is not palindrome"	# not palindrome
fi
exit 0
