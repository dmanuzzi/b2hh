#!/bin/bash

mkdir -p ${B2HH_LOG}/Tagging/out
mkdir -p ${B2HH_LOG}/Tagging/err
mkdir -p ${B2HH_LOG}/Tagging/log

mkdir -p ${B2HH_OUT}/Tagging/templates
mkdir -p ${B2HH_OUT}/Tagging/test
mkdir -p ${B2HH_OUT}/Tagging/plots

mkdir -p ${B2HH_OUT}/Tagging/iftTemplates
mkdir -p ${B2HH_OUT}/Tagging/iftTemplates/plots

cd ${B2HH_SRC}/Tagging
rm pidWeights reweightSS makeTemplates createBKG iftTagTemplate iftMakeTemplates iftCreateBKG
touch *.C
#rm iftTagTemplate
#touch iftTagTemplate.C
${lbRunDaVinciOld} make -B

cd ${B2HH_RUN}/Tagging
# cuts_bdt="KK_0.04 PIPI_0.12"
# years="201516 2017s29r2p2 2018"
# magnets="Tot"

years=${1//'__'/' '}
magnets=${2//'__'/' '}
cuts_bdt=${3//'__'/' '}
pipi_pid=$4
kk_pid=$5
kpi_pid=$6


rm -f jobs.txt
rm -f jobsIFT.txt
for cut_bdt in ${cuts_bdt}; do  
    for year in ${years}; do 
        for mag in ${magnets}; do
            for fState in "PIPI" "KK" "KPI"; do
                echo ${cut_bdt//"_"/" "} ${year} ${mag} ${fState}
                echo ${cut_bdt//"_"/" "} ${year} ${mag} ${fState} ${pipi_pid} ${kk_pid} ${kpi_pid}>> jobs.txt            
            	echo ${cut_bdt//"_"/" "} ${year} ${mag} ${fState} ${pipi_pid} ${kk_pid} ${kpi_pid}>> jobsIFT.txt
	    done
        done
    done
done


condor_submit submit.jdl
condor_submit submitIFT.jdl #just the b2hh MC templates for the IFT
