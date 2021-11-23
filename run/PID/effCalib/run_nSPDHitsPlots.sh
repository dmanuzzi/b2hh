#!/bin/bash

hostname 
cd ${B2HH_RUN}/PID
echo `pwd`

m=$1
y=$2
bdtCUT=$3

${B2HH_SRC}/PID/effCalib/nSPD_sWeight ${m} ${y} ${bdtCUT}
