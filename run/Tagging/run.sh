#!/bin/bash
cd ${B2HH_OUT}/Tagging

pidCuts=${6//'--'/' '}
pid_pipi=''
pid_kk=''
pid_kpi=''
pid_pik=''
for pidCut in ${pidCuts}; do
    if [[ ${pidCut} == pipi_* ]]; then
        pid_pipi=${pidCut//'pipi_'/''}
    elif [[ ${pidCut} == kk_* ]]; then
        pid_kk=${pidCut//'kk_'/''}
    elif [[ ${pidCut} == kpi_* ]]; then
        pid_kpi=${pidCut//'kpi_'/''}
    elif [[ ${pidCut} == pik_* ]]; then
        pid_pik=${pidCut//'pik_'/''}
    fi
done

if [[ $5 == "PIPI" ]]; then
     ${lbRunDaVinciOld} ${B2HH_SRC}/Tagging/pidWeights    -d $1 -b $2 -y $3 -m $4 -f PIPI -c ${pid_pipi}
     ${lbRunDaVinciOld} ${B2HH_SRC}/Tagging/reweightSS    -d $1 -b $2 -y $3 -m $4 -f pipi -c bddpi
     ${lbRunDaVinciOld} ${B2HH_SRC}/Tagging/reweightSS    -d $1 -b $2 -y $3 -m $4 -f pipi -c bsdspi
     ${lbRunDaVinciOld} ${B2HH_SRC}/Tagging/makeTemplates -n $1 -b $2 -y $3 -m $4 -f 0 -r bd
     ${lbRunDaVinciOld} ${B2HH_SRC}/Tagging/createBKG     -C $1 -b $2 -y $3 -m $4 -f pipi -c ${pid_pipi}
elif [[ $5 == "KK" ]]; then
     ${lbRunDaVinciOld} ${B2HH_SRC}/Tagging/pidWeights    -d $1 -b $2 -y $3 -m $4 -f KK -c ${pid_kk}
     ${lbRunDaVinciOld} ${B2HH_SRC}/Tagging/reweightSS    -d $1 -b $2 -y $3 -m $4 -f kk -c bddpi
     ${lbRunDaVinciOld} ${B2HH_SRC}/Tagging/reweightSS    -d $1 -b $2 -y $3 -m $4 -f kk -c bsdspi
     ${lbRunDaVinciOld} ${B2HH_SRC}/Tagging/makeTemplates -n $1 -b $2 -y $3 -m $4 -f 2 -r bs
     ${lbRunDaVinciOld} ${B2HH_SRC}/Tagging/createBKG     -C $1 -b $2 -y $3 -m $4 -f kk -c ${pid_kk}
elif [[ $5 == "KPI" ]]; then 
     ${lbRunDaVinciOld} ${B2HH_SRC}/Tagging/pidWeights    -d $1 -b $2 -y $3 -m $4 -f KPI -c ${pid_kpi}
     ${lbRunDaVinciOld} ${B2HH_SRC}/Tagging/reweightSS    -d $1 -b $2 -y $3 -m $4 -f kpi -c bddpi
     ${lbRunDaVinciOld} ${B2HH_SRC}/Tagging/reweightSS    -d $1 -b $2 -y $3 -m $4 -f kpi -c bsdspi
     ${lbRunDaVinciOld} ${B2HH_SRC}/Tagging/makeTemplates -n $1 -b $2 -y $3 -m $4 -f 1 -r bd
     ${lbRunDaVinciOld} ${B2HH_SRC}/Tagging/createBKG     -C $1 -b $2 -y $3 -m $4 -f kpi -c ${pid_kpi}
else
    echo "Wrong final state!"
fi
