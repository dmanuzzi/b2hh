#!/bin/bash

source ${setup_LCG_106}
decay=${1}
year=${2}
mag=${3}
dtype=${4}
wname=${5}
bdtname=${6}
bdtcut=${7}

#${B2HH_SRC}/resT/resolution -d ${decay} -y ${year} -m ${mag} -D ${dtype} -w ${wname}  -n ${bdtname} -b ${bdtcut}
${B2HH_SRC}/resT/resFit      -d ${decay} -y ${year} -m ${mag} -D ${dtype} -w ${wname}  -n ${bdtname} -b ${bdtcut} -M pol1
