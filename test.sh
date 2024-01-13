#!/bin/bash
declare -i index=1
exec_file="./pmerge"
make re
while :
do
	echo $index
	echo $index | xargs $exec_file
	index+=1
	sleep 1
done
