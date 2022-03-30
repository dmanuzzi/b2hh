#!/bin/bash
hostname
source ${setup_LCG_new}
cd ${B2HH_OUT}/sPlot
python ${B2HH_SRC}/sPlot/run.py -n $1 -b $2 -y $3 -m $4


