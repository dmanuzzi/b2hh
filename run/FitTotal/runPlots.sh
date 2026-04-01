#!/bin/bash
hostname
cd ${B2HH_SRC}/FitTotal
export B2DXFITTERSROOT=${B2HH_SRC}/B2DXFitters
export PYTHONPATH=${B2HH_SRC}/B2DXFitters/python:$PYTHONPATH
export LD_LIBRARY_PATH=${B2HH_SRC}/B2DXFitters/standalone:$LD_LIBRARY_PATH

taggers=${1}
bdtName=${2}
bdtCut=${3}
year=${4}
magnet=${5}
pidCuts=${6//'--'/' '}
splitConf=${7}
outDir=${8}
Ncpu=${9}
var=${10}
massRange=${11}
finalState=${12}
btag=${13}
ftag=${14}
tagger=${15}

pid_pipi=''
pid_kk=''
pid_kpi=''
pid_pik=''
for pidCut in ${pidCuts}; do
    echo $pidCut
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

${lbRunDaVinciOld} python fit.py -t ${taggers//'_'/' '}  \
                                 -C ${bdtName}   -b ${bdtCut} \
                                 -y ${year}      -m ${magnet} \
				 --pidpipi=${pid_pipi} --pidkk=${pid_kk} \
                                 --pidkpi=${pid_kpi} --pidpik=${pid_pik} \
                                 -s ${splitConf} -d ${outDir}  -n ${Ncpu}\
                                 -p \
                                 -v ${var}  -r ${massRange} -f ${finalState}\
                                 -B ${btag} -F ${ftag}      -A ${tagger}
