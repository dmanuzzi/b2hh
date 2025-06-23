#!/bin/bash


mkdir -p ${B2HH_LOG}/MassFit/out
mkdir -p ${B2HH_LOG}/MassFit/err
mkdir -p ${B2HH_LOG}/MassFit/log
mkdir -p ${B2HH_OUT}/MassFit

cd ${B2HH_RUN}/MassFit


# cuts_bdt="KK_0.04 PIPI_0.12"
# years="201516 2017s29r2p2 2018"
# magnets="Tot"
# Ncpu="56"
echo `pwd`
years=${1//'__'/' '}
magnets=${2//'__'/' '}
cuts_bdt=${3//'__'/' '}
Ncpu=${4}

rm -f jobs.txt
for cut_bdt in ${cuts_bdt}; do  
    for year in ${years}; do 
        for mag in ${magnets}; do
#            outDir="${cut_bdt}_${year}_${mag}_TimeBiasFromConstCkkSkk201516"
#            outDir="${cut_bdt}_${year}_${mag}_ConstCkkSkk201516FreeTimeBias"
#            outDir="${cut_bdt}_${year}_${mag}_ConstCkkSkk2018FreeTimeBias"
#            outDir="${cut_bdt}_${year}_${mag}_dmsFree"
            outDir="${cut_bdt}_${year}_${mag}"
            mkdir -p ${B2HH_OUT}/MassFit/${outDir}
            taggers=''
            if   [[ ${cut_bdt} == *GraNEW* ]];  then taggers="OS_SSk"; #for the bspipi i want to select the bs
            elif [[ ${cut_bdt} == *PIPI* ]]; then taggers="OS_SS";
            elif [[ ${cut_bdt} == *KK* ]];   then taggers="OS_SSk";
            else continue;
            fi
            echo ${taggers} ${cut_bdt//"_"/" "} ${year} ${mag}
            echo ${taggers} ${cut_bdt//"_"/" "} ${year} ${mag} ${year} ${outDir} ${Ncpu} >> jobs.txt            
        done
    done
done

condor_submit submit.jdl
