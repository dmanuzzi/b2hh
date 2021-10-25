#!/bin/bash

mkdir -p ${B2HH_LOG}/AccSignal/out
mkdir -p ${B2HH_LOG}/AccSignal/err
mkdir -p ${B2HH_LOG}/AccSignal/log

mkdir -p ${B2HH_OUT}/AccSignal/bkgSubtractedSamples
mkdir -p ${B2HH_OUT}/AccSignal/kineWeight
mkdir -p ${B2HH_OUT}/AccSignal/selectedMC
mkdir -p ${B2HH_OUT}/AccSignal/params
mkdir -p ${B2HH_OUT}/AccSignal/plots
mkdir -p ${B2HH_OUT}/AccSignal/acceptances

source ${setup_LCG_std}
cd ${B2HH_SRC}/AccSignal
root -l -b -q RooTimeAccPdf.cxx+
touch ./*.C
make 

cd ${B2HH_RUN}/AccSignal
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
