#!/bin/bash
cd ${B2HH_OUT}/TimeModels
source ${setup_LCG_std}
${B2HH_SRC}/TimeModels/provaVin           -n $1 -b $2 -y $3 -m $4 -f $5 -F
${B2HH_SRC}/TimeModels/createTemplate     -n $1 -b $2 -y $3 -m $4 -f $5
${B2HH_SRC}/TimeModels/createPhysTemplate -n $1 -b $2 -y $3 -m $4 -f $5

