#!/bin/bash
cd ${B2HH_SRC}/AccSignal
source ${setup_LCG_std}
python ${B2HH_SRC}/AccSignal/run.py    -n $1 -b $2 -y $3 -m $4 
python ${B2HH_SRC}/AccSignal/runFit.py -n $1 -b $2 -y $3 -m $4 -F


