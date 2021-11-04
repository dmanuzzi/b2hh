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
rm -f jobs.txt
for year in ${years}; do
    for mag in ${magnets}; do
        for cut_bdt in ${cuts_bdt}; do
            echo ${cut_bdt//'_'/' '} ${year} ${mag}
            echo ${cut_bdt//'_'/' '} ${year} ${mag} >> jobs.txt
            #echo "KK" "0.04" ${year} ${mag} >> jobs.txt
            #echo "KK" "0.08" ${year} ${mag} >> jobs.txt
            #echo "KK" "0.20" ${year} ${mag} >> jobs.txt
            #echo "PIPI" "0.12" ${year} ${mag} >> jobs.txt
            #echo "gKK" "0.08" ${year} ${mag} >> jobs.txt
            #echo "gPIPI" "0.12" ${year} ${mag} >> jobs.txt
        done
    done
done

condor_submit submit.jdl
