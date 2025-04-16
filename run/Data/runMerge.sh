#!/bin/bash
hostname
mode=$1
y=$2
m=$3
${lbRunDaVinciStd} hadd -fk ${B2HH_OUT}/Data/tuple_merged/${mode}_${y}_${m}.root ${B2HH_OUT}/Data/tuple/${mode}_${y}_${m}_*.root