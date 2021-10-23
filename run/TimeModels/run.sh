#!/bin/bash
cd ${B2HH_OUT}/TimeModels
source ${setup_LCG_std}
python ${B2HH_SRC}/TimeModels/run.py -n $1 -b $2 -y $3 -m $4 -F


