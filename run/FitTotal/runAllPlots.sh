#!/bin/bash
#source ${setup_LCG_new}
pythonNew="/cvmfs/sft.cern.ch/lcg/views/LCG_97a/x86_64-centos7-gcc9-opt/bin/python"
cd ${B2HH_RUN}/FitTotal
# cuts_bdt="KK_0.04__PIPI_0.12"
# years="201516__2017s29r2p2__2018"
# magnets="Tot"
# Ncpu="1"

taggerss=${1//'__'/' '}
years=${2//'__'/' '}
magnets=${3//'__'/' '}
cuts_bdt=${4//'__'/' '}
cuts_pid=${5//'__'/' '}

rm -f jobsPlots.txt


for taggers in ${taggerss}; do
    for cut_bdt in ${cuts_bdt}; do
	for year in ${years}; do
            for mag in ${magnets}; do
		for cut_pid in ${cuts_pid}; do
		    outDir="${cut_bdt}_${year}_${mag}_${taggers}"
		    mkdir -p ${B2HH_OUT}/FitTotal/${outDir}/plots
		    if   [[ ${cut_bdt} == *PIPI* && ${taggers} == "OS_SSk" ]]; then continue; fi
                    if   [[ ${cut_bdt} == *KK* && ${taggers} == "OS_SS" ]]; then continue; fi
		    echo ${taggers} ${cut_bdt//"_"/" "} ${year} ${mag} ${cut_pid}

		${pythonNew} ${B2HH_SRC}/FitTotal/preparePlotJobs.py   \
                             -t ${taggers//"_"/" "}\
                             -C ${cut_bdt//"_"/" -b "}\
                             -y ${year}               \
                             -m ${mag}                \
			     -p ${cut_pid}            \
                             -d ${outDir}
		done
            done
	done
    done
done

condor_submit submitPlots.jdl
