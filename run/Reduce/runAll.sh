#!/bin/bash

mkdir -p ${B2HH_OUT}/Reduce
mkdir -p ${B2HH_LOG}/Reduce/out
mkdir -p ${B2HH_LOG}/Reduce/err
mkdir -p ${B2HH_LOG}/Reduce/log

cd ${B2HH_SRC}/Reduce
touch reduce.C
${lbRunDaVinciStd} make reduce

cd ${B2HH_RUN}/Reduce
years=${1//'__'/' '}
magnets=${2//'__'/' '}
cuts_bdt=${3//'__'/' '}
cuts_pid=${4//'__'/' '}

rm -f jobs.txt
for year in ${years}; do
    for mag in ${magnets}; do
        for cut_bdt in ${cuts_bdt}; do
	    for cut_pid in ${cuts_pid}; do
		echo ${cut_bdt//'_'/' '} ${year} ${mag} ${cut_pid}
		echo ${cut_bdt//'_'/' '} ${year} ${mag} ${cut_pid} >> jobs.txt
	    done
        done
    done
done

condor_submit submit.jdl
