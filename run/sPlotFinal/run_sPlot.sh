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
                                 -s ${splitConf} -d ${outDir}  -n ${Ncpu} -sw
