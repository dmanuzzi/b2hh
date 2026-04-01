#!/bin/bash
hostname

mode=$1
y=$2
m=$3
source ${setup_LCG_105}
#${lbRunDaVinciStd}
hadd -fk ${B2HH_OUT}/Data/tuple_merged/"$mode"_"$y"_"$m".root \
     ${B2HH_OUT}/Data/tuple/"$mode"_"$y"_"$m"_*.root
