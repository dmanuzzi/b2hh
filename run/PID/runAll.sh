#!/bin/bash

for task in "prepareCalib" "effCalib" "effB2HH"; do
    mkdir -p "${B2HH_LOG}/PID/${task}/out"
    mkdir -p "${B2HH_LOG}/PID/${task}/err"
    mkdir -p "${B2HH_LOG}/PID/${task}/log"
    mkdir -p "${B2HH_OUT}/PID/${task}"
    mkdir -p "${B2HH_OUT}/PID/${task}/results"
done
mkdir -p ${B2HH_OUT}/PID/effB2HH/jobs

# magnets="Tot"
# years="201516 2017s29r2p2 2018"
# cuts_pid="kpi_5.-2.-5.3 pik_-5.3.5.-2 pipi_-2.3.-2.3 kk_2.-2.2.-2"
# cuts_bdt="KK_0.04 PIPI_0.12"
# binnings="71_10_1_6"

years=${1//'__'/' '}
magnets=${2//'__'/' '}
cuts_bdt=${3//'__'/' '}
cuts_pid=${4//'__'/' '}
binnings=${5//'__'/' '}

## prepareCalib
#### to be implemented

## effCalib
#### to be implemented

## effB2HH

cd ${B2HH_SRC}/PID/effB2HH
source ${setup_LCG_new}
touch *.C
make effB2HH

cd ${B2HH_RUN}/PID/effB2HH
rm -f ${B2HH_LOG}/PID/effB2HH/log/PID_effB2HH.txt
rm -rf jobs.txt
for mag in ${magnets}; do
    for year in ${years}; do
        for cut_bdt in ${cuts_bdt}; do
            for cut_pid in ${cuts_pid}; do
                for bin in ${binnings}; do
                    echo ${bin//'_'/' '} ${cut_pid//'_'/' '} ${mag} ${year} ${cut_bdt//'_'/' '} -s >> jobs.txt
                done
            done
        done
    done 
done

condor_submit submit.jdl
condor_wait ${B2HH_LOG}/PID/effB2HH/log/PID_effB2HH.txt

mv ${B2HH_OUT}/PID/effB2HH/pidEffs.db ${B2HH_OUT}/PID/effB2HH/pidEffs.db.bak
python ${B2HH_SRC}/PID/effB2HH/mergeDB.py -d ${B2HH_OUT}/PID/effB2HH

for mag in ${magnets}; do
    for year in ${years}; do
        for cut_bdt in ${cuts_bdt}; do
            for cut_pid in ${cuts_pid}; do
                echo python ${B2HH_SRC}/PID/effB2HH/efficiencies.py -i ${B2HH_OUT}/PID/effB2HH/pidEffs.db \
                                                               -o ${B2HH_OUT}/PID/effB2HH \
                                                               -f ${cut_pid//'_'/' --pidCuts='} \
                                                               -y ${year} -m ${mag} \
                                                               -n ${cut_bdt//'_'/' -b '}
                python ${B2HH_SRC}/PID/effB2HH/efficiencies.py -i ${B2HH_OUT}/PID/effB2HH/pidEffs.db \
                                                               -o ${B2HH_OUT}/PID/effB2HH \
                                                               -f ${cut_pid//'_'/' --pidCuts='} \
                                                               -y ${year} -m ${mag} \
                                                               -n ${cut_bdt//'_'/' -b '}
            done
        done
    done 
done
