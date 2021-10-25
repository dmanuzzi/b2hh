#!/bin/bash

mkdir -p ${B2HH_LOG}/TimeModels/out
mkdir -p ${B2HH_LOG}/TimeModels/err
mkdir -p ${B2HH_LOG}/TimeModels/log

mkdir -p ${B2HH_OUT}/TimeModels/templateFiles
mkdir -p ${B2HH_OUT}/TimeModels/weightedFiles
mkdir -p ${B2HH_OUT}/TimeModels/params
mkdir -p ${B2HH_OUT}/TimeModels/plots

source ${setup_LCG_std}
cd ${B2HH_SRC}/TimeModels
touch *.C
make 

cd ${B2HH_RUN}/TimeModels
cuts_bdt="KK_0.04 PIPI_0.12"
years="201516 2017s29r2p2 2018"
magnets="Tot"

rm -f jobs.txt
for cut_bdt in ${cuts_bdt}; do  
    for year in ${years}; do 
        for mag in ${magnets}; do
            echo ${cut_bdt//"_"/" "} ${year} ${mag}
            echo ${cut_bdt//"_"/" "} ${year} ${mag} >> jobs.txt            
        done
    done
done

condor_submit submit.jdl
