#!/bin/bash
hostname
# source ${setup_LCG_new}
cd ${B2HH_OUT}/sPlot
${lbRunDaVinciStd} ${B2HH_SRC}/sPlot/create -d $1 -b $2 -y $3 -m $4 -f pipi


