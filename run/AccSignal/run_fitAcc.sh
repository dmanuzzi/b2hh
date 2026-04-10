#!/bin/bash
cd ${B2HH_SRC}/AccSignal
#source ${setup_LCG_std}

if [[ $7 == '1' ]]; then
    if [[ $8 == '1' ]]; then    
        ${lbRunDaVinciStd} ${B2HH_SRC}/AccSignal/fitAcc -C $1 -b $2 -y $3 -m $4 -n $5 -f $6 -D -T -F
    else
        ${lbRunDaVinciStd} ${B2HH_SRC}/AccSignal/fitAcc -C $1 -b $2 -y $3 -m $4 -n $5 -f $6 -D -F
    fi
else 
    if [[ $8 == '1' ]]; then    
        ${lbRunDaVinciStd} ${B2HH_SRC}/AccSignal/fitAcc -C $1 -b $2 -y $3 -m $4 -n $5 -f $6 -T -F
    else
        ${lbRunDaVinciStd} ${B2HH_SRC}/AccSignal/fitAcc -C $1 -b $2 -y $3 -m $4 -n $5 -f $6 -F
    fi
fi
