#!/bin/bash

cd ${B2HH_RUN}/Reduce
hostname
date
${lbRunDaVinciStd} ${B2HH_SRC}/Reduce/reduce -n $1 -b $2 -y $3 -m $4 -pipi $5 -kk $6 -kpi $7 -pik $8
date
