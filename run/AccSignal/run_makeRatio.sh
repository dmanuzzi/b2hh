#!/bin/bash
cd ${B2HH_SRC}/AccSignal
#source ${setup_LCG_std}
#source ${setup_LCG_105}

if [[ $7 == '1' ]]; then
    if [[ $8 == '1' ]]; then    
        ${lbRunDaVinciStd} ${B2HH_SRC}/AccSignal/makeRatio -C $1 -b $2 -y $3 -m $4 -n $5 -f $6 -D -T
    else
        ${lbRunDaVinciStd} ${B2HH_SRC}/AccSignal/makeRatio -C $1 -b $2 -y $3 -m $4 -n $5 -f $6 -D
    fi
else 
    if [[ $8 == '1' ]]; then    
        ${lbRunDaVinciStd} ${B2HH_SRC}/AccSignal/makeRatio -C $1 -b $2 -y $3 -m $4 -n $5 -f $6 -T
    else
        ${lbRunDaVinciStd} ${B2HH_SRC}/AccSignal/makeRatio -C $1 -b $2 -y $3 -m $4 -n $5 -f $6 
    fi
fi
