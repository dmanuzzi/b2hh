#!/bin/bash
cd ${B2HH_SRC}/AccSignal
source ${setup_LCG_std}
n=$1
b=$2
y=$3
m=$4
d=$5
f=$6
BB=$7
dd=$8
ff=$9
if [[ $dd  == "0" ]]; then
    ${B2HH_SRC}/AccSignal/kineWeight2 -n $n -b $b -y $y -m $m -d $d -f $f -B $BB 
else
    ${B2HH_SRC}/AccSignal/kineWeight2 -n $n -b $b -y $y -m $m -d $d -f $f -B $BB -d2 $dd -f2 $ff
fi
