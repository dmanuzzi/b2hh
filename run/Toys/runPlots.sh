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
splitConf=${6}
outDir=${7}
Ncpu=${8}
var=${9}
massRange=${10}
finalState=${11}
btag=${12}
ftag=${13}
tagger=${14}
toyIndex=${15}
${lbRunDaVinciOld} python fit.py -t ${taggers//'_'/' '}  \
                                 -C ${bdtName}   -b ${bdtCut} \
                                 -y ${year}      -m ${magnet} \
                                 -s ${splitConf} -d ${outDir}  -n ${Ncpu}\
                                 -p \
                                 -v ${var}  -r ${massRange} -f ${finalState}\
                                 -B ${btag} -F ${ftag}      -A ${tagger}\
				 -i ${toyIndex}

#((machine == "lhcb-128g-56ht-a.cr.cnaf.infn.it") || (machine == "lhcb-128g-56ht-b.cr.cnaf.infn.it") || (machine == "lhcb-128g-56ht-c.cr.cnaf.infn.it") || (machine == "lhcb-128g-56ht-d.cr.cnaf.infn.it") || (machine == "lhcb-128g-64ht-b.cr.cnaf.infn.it") || (machine == "lhcb-256g-96ht-a.cr.cnaf.infn.it"))
