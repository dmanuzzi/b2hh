#!/bin/bash

$VO_LHCB_SW_DIR/lib/LbLogin.sh

mode=$1
year=$2
comb=$3
conf=$4
echo $mode $year $comb $conf
cd ../"$mode"_calib
python ../tools/finaliseCalibPlots.py "$mode" "$year" "$comb" "$conf"
