#!/bin/bash

hostname
source ${setup_LCG_106}

cd ${B2HH_SRC}/newBDTtrain
python assignFinal.py -c $1 -y $2 -p $3

#also fix the compatibility bit
root -b -q ${B2HH_SRC}/newBDTtrain/compatibilityBitFixFinal.cpp\(\"$1\",\"$2\",\"$3\"\)