#!/bin/bash
cd ${B2HH_RUN}/Data
# source ${setup_LCG_new}

## folder architecture
mkdir -p ${B2HH_LOG}/Data/out
mkdir -p ${B2HH_LOG}/Data/err
mkdir -p ${B2HH_LOG}/Data/log
mkdir -p ${B2HH_OUT}/Data/tuple
mkdir -p ${B2HH_OUT}/Data/tuple_merged

## preliminary operations
# ${B2HH_SRC}/Data/makeInputLists.sh
# ${lbRunDaVinciStd} ${B2HH_SRC}/Data/compileSelCode.sh

## preseletion
modesMC="bdkk bdkpi bdpik bdpipi bskk bskpi bspik bspipi lbkp lbpk lbpip lbppi"
years="2015 2016 2017s29r2p2 2018"
magnets="Up Down"

rm -f jobs.txt
rm -f ${B2HH_LOG}/Data/log/Data_mc.txt
rm -f ${B2HH_LOG}/Data/log/Data_sel.txt
${lbRunDaVinciStd} python ${B2HH_SRC}/Data/prepareAllJobs.py -o ${B2HH_RUN}/Data/jobs.txt -c mc  -d ${modesMC} -y ${years} -m ${magnets}
${lbRunDaVinciStd} python ${B2HH_SRC}/Data/prepareAllJobs.py -o ${B2HH_RUN}/Data/jobs.txt -c sel -d b2hh       -y ${years} -m ${magnets}
condor_submit submit.jdl
condor_wait ${B2HH_LOG}/Data/log/Data_mc.txt
condor_wait ${B2HH_LOG}/Data/log/Data_sel.txt

## merge preselected tuples
rm -f jobsMerge.txt
for mode in ${modesMC} "b2hh";do
    for y in $years; do
        for m in $magnets; do
            echo ${mode} ${y} ${m}
	    echo ${mode} ${y} ${m} >> jobsMerge.txt
        done
    done
done

condor_submit submitMerge.jdl
