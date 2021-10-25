#!/bin/bash
hostname
cd ${B2HH_SRC}/FitTotal
export B2DXFITTERSROOT=${B2HH_SRC}/B2DXFitters
export PYTHONPATH=${B2HH_SRC}/B2DXFitters/python:$PYTHONPATH
export LD_LIBRARY_PATH=${B2HH_SRC}/B2DXFitters/standalone:$LD_LIBRARY_PATH

taggers=$1
bdtName=$2
bdtCut=$3
year=$4
magnet=$5
splitConf=$6
outDir=$7
Ncpu=$8

${lbRunDaVinciOld} python fit.py -t ${taggers//'_'/' '}  \
                                 -C ${bdtName}   -b ${bdtCut} \
                                 -y ${year}      -m ${magnet} \
                                 -s ${splitConf} -d ${outDir}  -n ${Ncpu}
python fit.py -m Tot -t OS SS -C PIPI -b 0.12 -n 1 -d 2018 -s 2018 -y 2018 -p -v eta -r sig5.45 -f KK_2018 -B Bbar -F tot -A SS
