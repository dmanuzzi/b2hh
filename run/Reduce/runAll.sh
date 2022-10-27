#!/bin/bash

mkdir -p ${B2HH_OUT}/Reduce
mkdir -p ${B2HH_LOG}/Reduce/out
mkdir -p ${B2HH_LOG}/Reduce/err
mkdir -p ${B2HH_LOG}/Reduce/log

cd ${B2HH_SRC}/Reduce
source ${setup_LCG_new}
touch reduce.C
make reduce

cd ${B2HH_RUN}/Reduce
# years="201516 2017s29r2p2 2018"
# magnets="Tot"
years=${1//'__'/' '}
magnets=${2//'__'/' '}
cuts_bdt=${3//'__'/' '}
cuts_pid=${4//'__'/' '}
cuts_pid=${cuts_pid//'kpi_'/' '}
cuts_pid=${cuts_pid//'pik_'/' '}
cuts_pid=${cuts_pid//'pipi_'/' '}
cuts_pid=${cuts_pid//'kk_'/' '}

rm -f jobs.txt
for year in ${years}; do
    for mag in ${magnets}; do
        for cut_bdt in ${cuts_bdt}; do
            echo ${cut_bdt//'_'/' '} ${year} ${mag} ${cuts_pid}
            echo ${cut_bdt//'_'/' '} ${year} ${mag} ${cuts_pid}>> jobs.txt
        done
    done
done

condor_submit submit.jdl
