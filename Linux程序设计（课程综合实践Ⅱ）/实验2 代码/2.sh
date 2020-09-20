#FileName: 2.sh
#Author: Ziteng Wang
#Create Date: 2020-06-19
#Last Modify: 2020-06-20
#Description: 
#  if 1 direction file name argument: 
#    calculate numbers of ordinary files/ subdirection files/ excutable files
#    claculate bytes of ordinary files
#  if more than 1 argument: print error info
#  if not an direction file: print error info

#! /bin/bash
if test $# -ne 1	# Not 1 Argument
	then
		echo "Exactly 1 argument is expected"	# Error info
		exit 1		# Error
fi
f_cnt=0			# ordinary file counter
d_cnt=0			# dir file counter
x_cnt=0			# excutable file counter
b_cnt=0			# bytes counter
array=$(find $1)	# find all files within dir $1
for i in $array		# traversal $array
do
	if [ -f $i ]	# ordinary file
		then
			((f_cnt++))
			set `wc -c $i`	# get bytes
			((b_cnt+=$1))
	fi
	if [ -d $i ]	# dir file
		then
			((d_cnt++))
	fi
	if [ -x $i ]	# excutable file
		then
			((x_cnt++))
	fi
done
echo "Calculatin Result:"		# head line
echo "-f	-d	-x	bytes"
echo "$f_cnt	$d_cnt	$x_cnt	$b_cnt"	# result
exit 0
