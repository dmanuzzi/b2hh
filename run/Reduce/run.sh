#!/bin/bash

source ${setup_LCG_new}
cd ${B2HH_RUN}/Reduce
${B2HH_SRC}/Reduce/reduce -n $1 -b $2 -y $3 -m $4 -kpi $5 -pik $6 -pipi $7 -kk $8 

