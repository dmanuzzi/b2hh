#!/bin/bash
cd ${B2HH_SRC}/AccSignal
#source ${setup_LCG_std}

${lbRunDaVinciStd} ${B2HH_SRC}/AccSignal/subtractBkg -n $1 -b $2 -y $3 -m $4
