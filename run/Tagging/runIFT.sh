#!/bin/bash
cd ${B2HH_OUT}/Tagging
#${lbRunDaVinciOld} python ${B2HH_SRC}/Tagging/run.py -n $1 -b $2 -y $3 -m $4 

hostname
date

if [[ $5 == "PIPI" ]]; then
    ${lbRunDaVinciOld} ${B2HH_SRC}/Tagging/iftTagTemplate -d $1 -b $2 -y $3 -m $4 -f pipi -c "${6}"
    ${lbRunDaVinciOld} ${B2HH_SRC}/Tagging/iftMakeTemplates -n $1 -b $2 -y $3 -m $4 -f 0 -r bd
    ${lbRunDaVinciOld} ${B2HH_SRC}/Tagging/iftCreateBKG     -C $1 -b $2 -y $3 -m $4 -f pipi -c "${6}"
elif [[ $5 == "KK" ]]; then
    ${lbRunDaVinciOld} ${B2HH_SRC}/Tagging/iftTagTemplate -d $1 -b $2 -y $3 -m $4 -f kk -c "${7}"
    ${lbRunDaVinciOld} ${B2HH_SRC}/Tagging/iftMakeTemplates -n $1 -b $2 -y $3 -m $4 -f 2 -r bs
    ${lbRunDaVinciOld} ${B2HH_SRC}/Tagging/iftCreateBKG     -C $1 -b $2 -y $3 -m $4 -f kk -c "${7}"
elif [[ $5 == "KPI" ]]; then
    ${lbRunDaVinciOld} ${B2HH_SRC}/Tagging/iftTagTemplate -d $1 -b $2 -y $3 -m $4 -f kpi -c "${8}"
    ${lbRunDaVinciOld} ${B2HH_SRC}/Tagging/iftMakeTemplates -n $1 -b $2 -y $3 -m $4 -f 1 -r bd
    ${lbRunDaVinciOld} ${B2HH_SRC}/Tagging/iftCreateBKG     -C $1 -b $2 -y $3 -m $4 -f kpi -c "${8}"
else
    echo "Wrong final state!"
fi
