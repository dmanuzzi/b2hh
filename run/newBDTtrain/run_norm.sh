#!/bin/bash
#source /cvmfs/sft.cern.ch/lcg/views/LCG_86/x86_64-slc6-gcc62-opt/setup.sh
source ${setup_LCG_105}
#cd $B2HH_HOME/Selection.new
cd $B2HH_SRC/newBDTtrain
./normalisation $1 $2 #year/magnet; BDT, PID, channel are hardcoded
