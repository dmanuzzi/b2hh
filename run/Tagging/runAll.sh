#!/bin/bash

mkdir -p ${B2HH_LOG}/Tagging/out
mkdir -p ${B2HH_LOG}/Tagging/err
mkdir -p ${B2HH_LOG}/Tagging/log

mkdir -p ${B2HH_OUT}/Tagging/templates
mkdir -p ${B2HH_OUT}/Tagging/test
mkdir -p ${B2HH_OUT}/Tagging/plots


cd ${B2HH_SRC}/Tagging
touch *.C
${lbRunDaVinciOld} make 

cd ${B2HH_RUN}/Tagging

years=${1//'__'/' '}
magnets=${2//'__'/' '}
cuts_bdt=${3//'__'/' '}
cuts_pid=${4//'__'/' '}

rm -f jobs.txt
for cut_bdt in ${cuts_bdt}; do  
    for year in ${years}; do 
        for mag in ${magnets}; do
            for fState in "PIPI" "KK" "KPI"; do
                echo ${cut_bdt//"_"/" "} ${year} ${mag} ${fState} ${cuts_pid}
                echo ${cut_bdt//"_"/" "} ${year} ${mag} ${fState} ${cuts_pid} >> jobs.txt            
            done
        done
    done
done

condor_submit submit.jdl
