#!/bin/bash

mkdir -p ${B2HH_LOG}/sFit/out
mkdir -p ${B2HH_LOG}/sFit/err
mkdir -p ${B2HH_LOG}/sFit/log

mkdir -p ${B2HH_OUT}/sFit

cd ${B2HH_RUN}/sFit
# cuts_bdt="KK_0.04 PIPI_0.12"
# years="201516 2017s29r2p2 2018"
# magnets="Tot"
# Ncpu="56"

years=${1//'__'/' '}
magnets=${2//'__'/' '}
cuts_bdt=${3//'__'/' '}
Ncpu=${4}
opt=${5}
# rm -f jobs.txt
for cut_bdt in ${cuts_bdt}; do  
    for year in ${years}; do 
        for mag in ${magnets}; do
            outDir="${cut_bdt}_${year}_${mag}_${opt}"
            taggers=''
            if   [[ ${cut_bdt} == *PIPI* ]]; then taggers="OS_SS";
            elif [[ ${cut_bdt} == *KK* ]];   then taggers="OS_SSk";
            else continue;
            fi
            if [[ ${opt} == *"OSonly"* ]]; then
                taggers='OS'
            fi
            if [[ ${opt} == *"SSonly"* ]]; then
                if   [[ ${cut_bdt} == *PIPI* ]]; then taggers="SS";
                elif [[ ${cut_bdt} == *KK* ]];   then taggers="SSk";
                fi
            fi
            
            

            
            
            mkdir -p ${B2HH_OUT}/sFit/${outDir}
            
            echo ${taggers} ${cut_bdt//"_"/" "} ${year} ${mag} ${outDir}
            echo ${taggers} ${cut_bdt//"_"/" "} ${year} ${mag} ${year} ${outDir} >> jobs.txt            
        done
    done
done

# condor_submit submit.jdl
