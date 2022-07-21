#!/bin/bash

$VO_LHCB_SW_DIR/lib/LbLogin.sh

mode=$1
year=$2
mag=$3
cutTag=$4
yearCalib=$year
if [[ $year == 2015 ]]; then yearCalib=2015and2016; fi
if [[ $year == 2016 ]]; then yearCalib=2015and2016; fi

#cd ../"$mode"_calib
echo `pwd`
echo "COMBINE TAGGERS"
echo "mode: $mode, year: $year, magnet: $mag, cutTag: $cutTag"
../tools/combineTaggers \
    data/"$year"/Mag"$mag"/B2DX_"$year"_"$mag"_"$mode"_sWeight_wPT.root \
    EPMout_"$yearCalib"_newTags"$cutTag"/MyCalibrations.py \
    EPMout_"$yearCalib"_oldTags"$cutTag"/MyCalibrations.py \
    data/"$year"/Mag"$mag"/B2DX_"$year"_"$mag"_"$mode"_sWeight_wPT_TagComb"$cutTag".root 

