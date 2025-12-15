#!/bin/bash

hostname
source ${setup_LCG_106}

cd ${B2HH_SRC}/BDT
#echo "assign final" 
python assignFinal.py -c $1 -y $2 -p $3
##done!

#also fix the compatibility bit
root -b -q ${B2HH_SRC}/BDT/compatibilityBitFixFinal.cpp\(\"$1\",\"$2\",\"$3\"\)
