#!/bin/bash
mkdir -p ${B2HH_LOG}/FitTotal
mkdir -p ${B2HH_LOG}/FitTotal/fit
mkdir -p ${B2HH_LOG}/FitTotal/fit/out
mkdir -p ${B2HH_LOG}/FitTotal/fit/err
mkdir -p ${B2HH_LOG}/FitTotal/fit/log

mkdir -p ${B2HH_OUT}/FitTotal

cd ${B2HH_RUN}/FitTotal
# cuts_bdt="KK_0.04 PIPI_0.12"
# years="201516 2017s29r2p2 2018"
# magnets="Tot"
# Ncpu="56"

cpuForFit="48"

years=${1//'__'/' '}
magnets=${2//'__'/' '}
cuts_bdt=${3//'__'/' '}
Ncpu=${4}
opts=${5//'__'/' '}
if [[ ${opts} == '' ]]; then
    opts='baseline'
fi



rm -f jobs.txt
for cut_bdt in ${cuts_bdt}; do  
    for year in ${years}; do 
        for mag in ${magnets}; do
			for opt in ${opts}; do
				outDir="${cut_bdt}_${year}_${mag}"
				if [[ ${opt} != 'baseline' ]]; then
					outDir+="_${opt}"
				fi
				
				mkdir -p ${B2HH_OUT}/FitTotal/${outDir}
				taggers=''
				if   [[ ${cut_bdt} == *GraNEW* ]];  then taggers="OS_SSk"; ##should be SSk but we are reverting to daniele's baseline
				elif [[ ${cut_bdt} == *PIPI* ]]; then taggers="OS_SS";
				elif [[ ${cut_bdt} == *KK* ]];   then taggers="OS_SSk";
				else continue;
				fi
				echo ${taggers} ${cut_bdt//"_"/" "} ${year} ${mag} ${opt}
				echo ${taggers} ${cut_bdt//"_"/" "} ${year} ${mag} ${year} ${outDir} ${Ncpu} >> jobs.txt
			done
        done
    done
done

condor_submit submit.jdl
