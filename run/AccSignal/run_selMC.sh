#!/bin/bash
cd ${B2HH_SRC}/AccSignal
#source ${setup_LCG_std}

${lbRunDaVinciStd} ${B2HH_SRC}/AccSignal/selMC -n $1 -b $2 -y $3 -m $4 -d $5 -f $6 -c $7 -F 0_0_0_0
