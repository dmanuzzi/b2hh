#!/bin/bash

mkdir -p ${B2HH_LOG}/FitTotal/out
mkdir -p ${B2HH_LOG}/FitTotal/err
mkdir -p ${B2HH_LOG}/FitTotal/log

mkdir -p ${B2HH_OUT}/FitTotal

cd ${B2HH_RUN}/FitTotal

taggerss=${1//'__'/' '}
years=${2//'__'/' '}
magnets=${3//'__'/' '}
cuts_bdt=${4//'__'/' '}
cuts_pid=${5//'__'/' '}
Ncpu=${6}

rm -f jobs.txt
for taggers in ${taggerss}; do
    for cut_bdt in ${cuts_bdt}; do  
	for year in ${years}; do 
            for mag in ${magnets}; do
		for cut_pid in ${cuts_pid}; do
		    if   [[ ${cut_bdt} == *PIPI* && ${taggers} == "OS_SSk" ]]; then continue; fi
		    if   [[ ${cut_bdt} == *KK* && ${taggers} == "OS_SS" ]]; then continue; fi
		    outDir="${cut_bdt}_${year}_${mag}_${taggers}"
		    mkdir -p ${B2HH_OUT}/FitTotal/${outDir}
		    echo ${taggers} ${cut_bdt//"_"/" "} ${year} ${mag} ${cut_pid}
		    echo ${taggers} ${cut_bdt//"_"/" "} ${year} ${mag} ${cut_pid} ${year} ${outDir} >> jobs.txt
		done
	    done
        done
    done
done

condor_submit submit.jdl
