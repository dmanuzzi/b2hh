#!/bin/bash

mkdir -p ${B2HH_LOG}/sPlot/out
mkdir -p ${B2HH_LOG}/sPlot/err
mkdir -p ${B2HH_LOG}/sPlot/log

mkdir -p ${B2HH_OUT}/sPlot/template
mkdir -p ${B2HH_OUT}/sPlot/tuple_reduced
mkdir -p ${B2HH_OUT}/sPlot/params
mkdir -p ${B2HH_OUT}/sPlot/plots

cd ${B2HH_SRC}/sPlot
source ${setup_LCG_new}
touch *.C
make


cd ${B2HH_RUN}/sPlot
# magnets="Tot"
# years="201516 2017s29r2p2 2018"
# cuts_bdt="KK_0.04 PIPI_0.12"
years=${1//'__'/' '}
magnets=${2//'__'/' '}
cuts_bdt=${3//'__'/' '}


rm -f jobs_create.txt
for cut_bdt in ${cuts_bdt}; do  
    for year in ${years}; do 
        for mag in ${magnets}; do
            echo ${cut_bdt//"_"/" "} ${year} ${mag}
            echo ${cut_bdt//"_"/" "} ${year} ${mag} >> jobs_create.txt            
        done
    done
done
condor_submit submit_create.jdl
condor_wait ${B2HH_LOG}/sPlot/log/sPlot_create.txt

rm -f jobs_fit.txt
for cut_bdt in ${cuts_bdt}; do  
    for year in ${years}; do 
        for mag in ${magnets}; do
            for fstate in "PIPI" "KPI" "KK"; do
                echo ${cut_bdt//"_"/" "} ${year} ${mag} ${fstate}
                echo ${cut_bdt//"_"/" "} ${year} ${mag} ${fstate} >> jobs_fit.txt            
            done
        done
    done
done
condor_submit submit_fit.jdl
condor_wait ${B2HH_LOG}/sPlot/log/sPlot_fit.txt


