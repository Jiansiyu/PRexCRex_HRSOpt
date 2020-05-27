#!/bin/bash

FolderPath=$1


pstr="[=======================================================================]"

TotalFileNumber=$(ls ${FolderPath} | wc -l)
echo "Total Files need to Process : ${TotalFileNumber}"
echo "Current progress :"

CurrentReplayedNumber=$(ls ${FolderPath}/*/CheckDp_test_result.txt | wc -l) 

while [ ${TotalFileNumber} -gt ${CurrentReplayedNumber} ];
do 
	
	pd=$(( ${CurrentReplayedNumber} * 73 / ${TotalFileNumber} ))
	printf "\r%3d.%1d%% %.${pd}s"  $(( ${CurrentReplayedNumber} * 100 / ${TotalFileNumber} )) $(( (${CurrentReplayedNumber} * 10000 / ${TotalFileNumber}) % 100 ))  $pstr
	sleep 10
	CurrentReplayedNumber=$(ls ${FolderPath}/*/CheckDp_test_result.txt | wc -l)
done 

# post run process

CurrentReplayedNumber=$(ls ${FolderPath}/*/CheckDp_test_result.txt | wc -l)
pd=$(( ${CurrentReplayedNumber} * 73 / ${TotalFileNumber} ))
printf "\r%3d.%1d%% %.${pd}s"  $(( ${CurrentReplayedNumber} * 100 / ${TotalFileNumber} )) $(( (${CurrentReplayedNumber} * 10000 / ${TotalFileNumber}) % 100 ))  $pstr

echo 
echo "Process Done !!!"
