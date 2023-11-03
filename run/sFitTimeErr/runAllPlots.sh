#!/bin/bash
#source ${setup_LCG_new}
pythonNew="/cvmfs/sft.cern.ch/lcg/views/LCG_97a/x86_64-centos7-gcc9-opt/bin/python"
cd ${B2HH_RUN}/sFitTimeErr
# cuts_bdt="KK_0.04__PIPI_0.12"
# years="201516__2017s29r2p2__2018"
# magnets="Tot"
# Ncpu="1"

years=${1//'__'/' '}
magnets=${2//'__'/' '}
cuts_bdt=${3//'__'/' '}
Ncpu=${4}
opt=${5}
# rm -f jobsPlots.txt

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
            

            mkdir -p ${B2HH_OUT}/sFitTimeErr/${outDir}/plots
            echo ${taggers} ${cut_bdt//"_"/" "} ${year} ${mag}

            ${pythonNew} ${B2HH_SRC}/sFitTimeErr/preparePlotJobs.py   \
                                    -t ${taggers//"_"/" "}\
                                    -C ${cut_bdt//"_"/" -b "}\
                                    -y ${year//"_"/" "}      \
                                    -s ${year}               \
                                    -m ${mag}                \
                                    -d ${outDir}             \
                                    -n ${Ncpu}
        done
    done
done

# condor_submit submitPlots.jdl
