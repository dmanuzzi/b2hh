#!/bin/bash
mode=$1
EPMstep=$2
cutTag=$3
cut=$4

echo `pwd`
cd ../"$mode"_calib
rm -f jobs_"$EPMstep".txt
for y in 2015and2016 2017 2018 All; do
    for vTag in newTags oldTags; do	
	echo $mode, $y, $vTag, $cutTag, $cut >> jobs_"$EPMstep".txt
    done
done

condor_submit ../tools/submit_"$EPMstep".jdl
    
