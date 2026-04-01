#!/bin/bash

cd ${B2HH_RUN}/Reduce

bdtName=${1}
bdtCut=${2}
year=${3}
magnet=${4}
pidCuts=${5//'--'/' '}
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

${lbRunDaVinciStd} ${B2HH_SRC}/Reduce/reduce -n ${bdtName} -b ${bdtCut} -y ${year} -m ${magnet} \
		                             -pipi ${pid_pipi} -kk ${pid_kk} -kpi ${pid_kpi} -pik ${pid_pik}

