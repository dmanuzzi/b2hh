#!/bin/bash

# source ${setup_LCG_new}
cd ${B2HH_SRC}/Data
${lbRunDaVinciStd} python ${B2HH_SRC}/Data/run.py -n $1 -y $2 -m $3 -c $4 -i $5 -d $6
