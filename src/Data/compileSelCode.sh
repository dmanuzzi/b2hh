#!/bin/bash
source ${setup_LCG_105}
cd ${B2HH_OUT}/Data
echo `pwd`
root -l -b -q ${B2HH_SRC}/Data/sel.C++
root -l -b -q ${B2HH_SRC}/Data/mc.C++

