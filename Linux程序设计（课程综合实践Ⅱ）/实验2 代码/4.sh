#FileName: 4.sh
#Author: Ziteng Wang
#Create Date: 2020-06-19
#Last Modify: 2020-06-20
#Description: 
#  move files larger than 100k to ~/tmp/

#! /bin/bash
array=$(find -size +100k)	# size > 100k
for i in $array				# traverse
do
	mv $i ~/tmp/			# transport
done
echo "success"				# echo info
exit 0
