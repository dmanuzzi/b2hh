#!/bin/bash
cd ${B2HH_OUT}/Tagging
#${lbRunDaVinciOld} python ${B2HH_SRC}/Tagging/run.py -n $1 -b $2 -y $3 -m $4 

echo "hardcoded PID cuts in tagging run file"

if [[ $5 == "PIPI" ]]; then
    ${lbRunDaVinciOld} ${B2HH_SRC}/Tagging/pidWeights    -d $1 -b $2 -y $3 -m $4 -f PIPI -c "-1.3.-1.3"
    ${lbRunDaVinciOld} ${B2HH_SRC}/Tagging/reweightSS    -d $1 -b $2 -y $3 -m $4 -f pipi -c bddpi
    ${lbRunDaVinciOld} ${B2HH_SRC}/Tagging/reweightSS    -d $1 -b $2 -y $3 -m $4 -f pipi -c bsdspi
    ${lbRunDaVinciOld} ${B2HH_SRC}/Tagging/makeTemplates -n $1 -b $2 -y $3 -m $4 -f 0 -r bd
    ${lbRunDaVinciOld} ${B2HH_SRC}/Tagging/createBKG     -C $1 -b $2 -y $3 -m $4 -f pipi -c "-1.3.-1.3"
elif [[ $5 == "KK" ]]; then
    ${lbRunDaVinciOld} ${B2HH_SRC}/Tagging/pidWeights    -d $1 -b $2 -y $3 -m $4 -f KK -c "2.-2.2.-2"
    ${lbRunDaVinciOld} ${B2HH_SRC}/Tagging/reweightSS    -d $1 -b $2 -y $3 -m $4 -f kk -c bddpi
    ${lbRunDaVinciOld} ${B2HH_SRC}/Tagging/reweightSS    -d $1 -b $2 -y $3 -m $4 -f kk -c bsdspi
    ${lbRunDaVinciOld} ${B2HH_SRC}/Tagging/makeTemplates -n $1 -b $2 -y $3 -m $4 -f 2 -r bs
    ${lbRunDaVinciOld} ${B2HH_SRC}/Tagging/createBKG     -C $1 -b $2 -y $3 -m $4 -f kk -c "2.-2.2.-2"
elif [[ $5 == "KPI" ]]; then 
    ${lbRunDaVinciOld} ${B2HH_SRC}/Tagging/pidWeights    -d $1 -b $2 -y $3 -m $4 -f KPI -c "5.-2.-5.3"
    ${lbRunDaVinciOld} ${B2HH_SRC}/Tagging/reweightSS    -d $1 -b $2 -y $3 -m $4 -f kpi -c bddpi
    ${lbRunDaVinciOld} ${B2HH_SRC}/Tagging/reweightSS    -d $1 -b $2 -y $3 -m $4 -f kpi -c bsdspi
    ${lbRunDaVinciOld} ${B2HH_SRC}/Tagging/makeTemplates -n $1 -b $2 -y $3 -m $4 -f 1 -r bd
    ${lbRunDaVinciOld} ${B2HH_SRC}/Tagging/createBKG     -C $1 -b $2 -y $3 -m $4 -f kpi -c "5.-2.-5.3"
else
    echo "Wrong final state!"
fi