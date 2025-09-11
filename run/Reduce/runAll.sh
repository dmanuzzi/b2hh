#!/bin/bash

mkdir -p ${B2HH_OUT}/Reduce
mkdir -p ${B2HH_LOG}/Reduce/out
mkdir -p ${B2HH_LOG}/Reduce/err
mkdir -p ${B2HH_LOG}/Reduce/log

cd ${B2HH_SRC}/Reduce
#rm reduce
touch reduce.C
${lbRunDaVinciStd} make -B reduce

cd ${B2HH_RUN}/Reduce
years=${1//'__'/' '}
magnets=${2//'__'/' '}
cuts_bdt=${3//'__'/' '}
kpi_pid=$4
pik_pid=$5
pipi_pid=$6
kk_pid=$7
rm -f jobs.txt
for year in ${years}; do
    for mag in ${magnets}; do
        for cut_bdt in ${cuts_bdt}; do
            echo ${cut_bdt//'_'/' '} ${year} ${mag}
            echo ${cut_bdt//'_'/' '} ${year} ${mag} ${pipi_pid} ${kk_pid} ${kpi_pid} ${pik_pid} >> jobs.txt
        done
    done
done

#condor_submit submit.jdl
