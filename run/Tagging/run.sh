#!/bin/bash
cd ${B2HH_OUT}/Tagging
${lbRunDaVinciOld} python ${B2HH_SRC}/Tagging/run.py -n $1 -b $2 -y $3 -m $4 -kpi $5 -pipi $6 -kk $7
