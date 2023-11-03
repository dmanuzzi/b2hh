#!/bin/bash
cd ${B2HH_OUT}/TimeErr

if [[ $5 == "PIPI" ]]; then
    ${lbRunDaVinciOld} ${B2HH_SRC}/TimeErr/pidWeights    -d $1 -b $2 -y $3 -m $4 -f PIPI -c -2.3.-2.3
elif [[ $5 == "KK" ]]; then
    ${lbRunDaVinciOld} ${B2HH_SRC}/TimeErr/pidWeights    -d $1 -b $2 -y $3 -m $4 -f KK -c 2.-2.2.-2
elif [[ $5 == "KPI" ]]; then 
    ${lbRunDaVinciOld} ${B2HH_SRC}/TimeErr/pidWeights    -d $1 -b $2 -y $3 -m $4 -f KPI -c 5.-2.-5.3
else
    echo "Wrong final state!"
fi
