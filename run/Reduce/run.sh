#!/bin/bash

source ${setup_LCG_new}
cd ${B2HH_RUN}/Reduce
${B2HH_SRC}/Reduce/reduce -n $1 -b $2 -y $3 -m $4 -pipi -2.3.-2.3 -kk 2.-2.2.-2 -kpi 5.-2.-5.3 -pik -5.3.5.-2

