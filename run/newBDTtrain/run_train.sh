#!/bin/bash


hostname
#source "/cvmfs/sft.cern.ch/lcg/views/LCG_105/x86_64-centos7-gcc12-opt/setup.sh" #(fatto prima)
#source ${setup_LCG_new}
#cd ${B2HH_OUT}/sPlot

source ${setup_LCG_106}

cd ${B2HH_SRC}/newBDTtrain
python train.py -m $1 -i $2 -t $3 -d $4
