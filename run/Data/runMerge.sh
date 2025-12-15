#!/bin/bash
hostname
date
source ${setup_LCG_105}

mode=$1
y=$2
m=$3
hadd -fk ${B2HH_OUT}/Data/tuple_merged_preFinalBDT/"$mode"_"$y"_"$m".root \
         ${B2HH_OUT}/Data/tuple/"$mode"_"$y"_"$m"_*.root

date
