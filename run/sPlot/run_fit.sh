#!/bin/bash
hostname
source ${setup_LCG_new}
cd ${B2HH_OUT}/sPlot
#${B2HH_SRC}/sPlot/reduce -d $1 -b $2 -y $3 -m $4 -f $5
${B2HH_SRC}/sPlot/fit    -d $1 -b $2 -y $3 -m $4 -f $5


