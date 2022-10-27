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
# cuts_bdt="KK_0.04 PIPI_0.12"
# years="201516 2017s29r2p2 2018"
# magnets="Tot"

years=${1//'__'/' '}
magnets=${2//'__'/' '}
cuts_bdt=${3//'__'/' '}
cuts_pid=${4//'__'/' '}
rm -f jobs.txt
for cut_bdt in ${cuts_bdt}; do  
    for year in ${years}; do 
        for mag in ${magnets}; do
	    for cut_pid in ${cuts_pid}; do
		if [[ ${cut_pid} == *pik* ]]; then continue; fi
		echo ${cut_bdt//"_"/" "} ${year} ${mag} ${cut_pid//"_"/" "}
		echo ${cut_bdt//"_"/" "} ${year} ${mag} ${cut_pid//"_"/" "}>> jobs.txt            
	    done
        done
    done
done

condor_submit submit.jdl
