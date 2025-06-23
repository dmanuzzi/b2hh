#!/bin/bash

source ${setup_LCG_105}

cd ${B2HH_SRC}/newBDTtrain/

root -b -q optim.cpp\(\"$1\"\)