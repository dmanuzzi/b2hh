#!/bin/bash
mode=$1
cutTag=$2

echo `pwd`
cd ../tools/
make combineTaggers
cd ../"$mode"_calib
rm -f jobs_combineTaggers.txt
for y in 2015 2016 2017 2018; do
    for m in Up Dw; do
	echo $mode, $y, $m, $cutTag >> jobs_combineTaggers.txt
    done
done
condor_submit ../tools/submit_combineTaggers.jdl
