#!/bin/bash

export B2HH_HOME=/home/ceph/manuzzi/b2hhTest/b2hh_ift
export B2HH_STORAGE=/ceph-data/lhcb_g/users/manuzzi/b2hhTest/b2hh_ift
export B2HH_LOG=$B2HH_HOME/log
export B2HH_OUT=$B2HH_HOME/out
export B2HH_SRC=$B2HH_HOME/src
export B2HH_RUN=$B2HH_HOME/run
export B2HH_CONFIG=$B2HH_HOME/config


export ROOT_INCLUDE_PATH=$B2HH_CONFIG/:$ROOT_INCLUDE_PATH
export LD_LIBRARY_PATH=$B2HH_CONFIG/:$LD_LIBRARY_PATH
export ROOT_INCLUDE_PATH=$B2HH_SRC/Lib/:$ROOT_INCLUDE_PATH
export LD_LIBRARY_PATH=$B2HH_SRC/Lib/:$LD_LIBRARY_PATH
export ROOT_INCLUDE_PATH=$B2HH_SRC/Tools/:$ROOT_INCLUDE_PATH
export LD_LIBRARY_PATH=$B2HH_SRC/Tools/:$LD_LIBRARY_PATH


export B2DXFITTERSROOT=$B2HH_SRC/B2DXFitters
export PYTHONPATH=$B2DXFITTERSROOT/python:$PYTHONPATH
export LD_LIBRARY_PATH=$B2HH_SRC/B2DXFitters/standalone:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$B2HH_SRC/MassModels/CrossFeed:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$B2HH_SRC/AccSignal:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$B2HH_SRC/TimeModels:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$B2HH_SRC/resT:$LD_LIBRARY_PATH

#alias lbRunDaVinciOld='/cvmfs/lhcb.cern.ch/lib/var/lib/LbEnv/2090/stable/linux-64/bin/lb-run -c x86_64-slc6-gcc48-opt DaVinci/v36r1p1'
alias setLCG_std='source /cvmfs/sft.cern.ch/lcg/views/LCG_86/x86_64-slc6-gcc62-opt/setup.sh'	
alias setLCG_new='source /cvmfs/sft.cern.ch/lcg/views/LCG_97a/x86_64-centos7-gcc9-opt/setup.sh'

export setup_LCG_new='/cvmfs/sft.cern.ch/lcg/views/LCG_97a/x86_64-centos7-gcc9-opt/setup.sh'
export setup_LCG_std='/cvmfs/sft.cern.ch/lcg/views/LCG_86/x86_64-slc6-gcc62-opt/setup.sh'
#export lbRunDaVinciOld='/cvmfs/lhcb.cern.ch/lib/var/lib/LbEnv/2090/stable/linux-64/bin/lb-run -c x86_64-slc6-gcc48-opt  DaVinci/v36r1p1'

BIND_BASE="/eos/lhcb/grid/prod/lhcb/anaprod/lhcb/LHCb"
COLLISIONS=$(printf ",%s/BNOC_B2HH.ROOT" \
		    "$BIND_BASE/Collision"{15,16,17,18})
BIND_BASE="/eos/lhcb/grid/prod/lhcb/anaprod/lhcb/MC"
COLLISIONS+=$(printf ",%s/BNOC_B2HH_MC.ROOT" \
	 	    "$BIND_BASE/20"{15,16,17,18})

BIND_REST="/home/ceph/manuzzi/B2HH/resT"
BIND_LIST="/ceph-data,${B2HH_HOME},/home/ceph/manuzzi/B2HH/Selection.new/$COLLISIONS,$BIND_REST"
export lbRunDaVinciStd="lb-run -c x86_64-centos7-gcc62-opt --bind $BIND_LIST DaVinci/v44r11p1"
#export lbRunDaVinciOld="lb-run -c x86_64-slc6-gcc48-opt --bind /ceph-data,${B2HH_HOME} DaVinci/v36r1p1"
export lbRunDaVinciOld="lb-run -c x86_64-slc6-gcc48-opt --bind $BIND_LIST DaVinci/v36r1p1"
export setup_LCG_105='/cvmfs/sft.cern.ch/lcg/views/LCG_105/x86_64-el9-gcc13-opt/setup.sh'
export setup_LCG_106='/cvmfs/sft.cern.ch/lcg/views/LCG_106/x86_64-el9-gcc13-opt/setup.sh'
