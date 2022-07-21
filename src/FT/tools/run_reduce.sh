#!/bin/bash

#$VO_LHCB_SW_DIR/lib/LbLogin.sh

mode=$1
y=$2
m=$3
echo $mode $y $m
#cd ../"$mode"_calib
#./reduceAndArrangeTuples $y $m
cd ../tools/
./reweighPT $mode $y $m
