#FileName: dirsync
#Author: Ziteng Wang
#Create Date: 2020-06-19
#Last Modify: 2020-06-20
#Description: 
#   1: backup -- update new file and keep increment copy
#   2: synchronize -- update two dirs in bothway, keep both dir most updated

#! /bin/bash
# Function Sync()
# synchronize
Sync(){
local cur1 cur2 status1 list1 list2 i j		# declare all local vars
cur1=$1		# src
cur2=$2		# dest
status1=0	# flag: find or not (0: not find)
if [ ! -d $cur2 ]	# if $2 is not direction
then
	mkdir $cur2		# mkdir
fi
list1=$(ls $cur1)	# content of 1
list2=$(ls $cur2)	# content of 2
for i in $list1				# Outer loop: files in src
do
	for j in $list2			# Inner loop: files in dest
	do
		if [[ $i != $j ]]	# Not same name
		then
			continue;
		elif [ -d ${cur1}/${i} ] && [ -d ${cur2}/${j} ]	# same name && same -d
		then
			status1=1		# find
			# echo -n "digui1:"
			# echo "${cur1}/${i} ${cur2}/${j}"
			Sync ${cur1}/${i} ${cur2}/${j}
		elif [ -f ${cur1}/${i} ] && [ -f ${cur2}/${j} ]	# same name && same -f
		then
			status1=1		# find
			# echo "here1"
			if [[ `find ${cur1}/${i} -newer ${cur2}/${j}` == ${cur1}/${i} ]] # $i is newer
			then
				\cp -rf ${cur1}/${i} ${cur2}/${j}	# $i -> $j
			fi
		fi
	done

	if [[ $status1 == 0 ]]	# not find $i in list2
	then
		if [ ${cur1}/${i} == ${cur2} ]		# check if (dest) is in (src) ---> avoid recursive copy
		then
			echo "file exist" 1>/dev/null
		elif [ -d ${cur1}/${i} ]	# dir file
		then
			# echo "copy: ${cur1}/${i} -> $cur2"
			cp -a ${cur1}/${i} $cur2	# copy the folder to (dest) dir
		else
			cp -a ${cur1}/${i} $cur2	# copy the file to (dest) dir
		fi
	fi
	
	status1=0		# re-initialise
done

status1=0			# initialise for next loop

for i in $list2		# Outer loop: files in dest
do
	for j in $list1	# inner loop: files in src
	do
		if [[ ${i} != ${j} ]]	# Not same name
		then
			continue;
		elif [ -f ${cur2}/${i} ] && [ -f ${cur1}/${j} ]	# same name && same -f
		then
			status1=1		# find
			# echo "here2"
			if [[ `find ${cur2}/${i} -newer ${cur1}/${j}` == ${cur2}/${i} ]] # $i is newer
			then
				\cp -rf ${cur2}/${i} ${cur1}/${j}	# $i -> $j
			fi
		fi
	done

	if [[ $status1 == 0 ]]	# not find $i in list1
	then
		if [ ${cur1} == ${cur2}/${i} ]	# check if (dest) is in (src) ---> avoid recursive copy
		then
			echo "file exist" 1>/dev/null
		elif [ -d ${cur2}/${i} ]	# dir file
		then
			rm -r ${cur2}/${i}	# remove dir that is not in list1
		else
			cp ${cur2}/${i} ${cur1}		# reverse update
		fi
	fi
	status1=0;					# re-init
done
# echo success
}

# Entrance for the shell
src=$1							# source dir
dest=$2							# destination dir
echo "Choose a mode:"			# tips
echo "	1:Backup"
echo "	2:synchronize"
echo -n "Your choice: "
read line						# read in "option"
case $line in
	1) rsync -r ${src}/ ${dest}	# function call
	;;
	2) Sync $src $dest			# Sync function call
	;;
esac
echo finish						# echo back
exit 0



