#!/bin/bash
#source ${setup_LCG_new}
pythonNew="/cvmfs/sft.cern.ch/lcg/views/LCG_97a/x86_64-centos7-gcc9-opt/bin/python"
cd ${B2HH_RUN}/MassFit
# cuts_bdt="KK_0.04__PIPI_0.12"
# years="201516__2017s29r2p2__2018"
# magnets="Tot"
# Ncpu="1"

years=${1//'__'/' '}
magnets=${2//'__'/' '}
cuts_bdt=${3//'__'/' '}
Ncpu=${4}

rm -f jobsPlots.txt

for cut_bdt in ${cuts_bdt}; do
    for year in ${years}; do
        for mag in ${magnets}; do
            #outDir="${cut_bdt}_${year}_${mag}_ConstCkkSkk201516FreeTimeBias"
            outDir="${cut_bdt}_${year}_${mag}"
            mkdir -p ${B2HH_OUT}/MassFit/${outDir}/plots
            taggers=''
            if   [[ ${cut_bdt} == *PIPI* ]]; then taggers="OS_SS";
            elif [[ ${cut_bdt} == *KK* ]];   then taggers="OS_SSk";
            else continue;
            fi
            echo ${taggers} ${cut_bdt//"_"/" "} ${year} ${mag}

            ${pythonNew} ${B2HH_SRC}/MassFit/preparePlotJobs.py   \
                                    -t ${taggers//"_"/" "}\
                                    -C ${cut_bdt//"_"/" -b "}\
                                    -y ${year}               \
                                    -m ${mag}                \
                                    -d ${outDir}             \
                                    -n ${Ncpu}
        done
    done
done

condor_submit submitPlots.jdl
