#!/bin/bash
#source ${setup_LCG_new}


mkdir -p ${B2HH_LOG}/Toys/plots
mkdir -p ${B2HH_LOG}/Toys/plots/out
mkdir -p ${B2HH_LOG}/Toys/plots/err
mkdir -p ${B2HH_LOG}/Toys/plots/log


pythonNew="/cvmfs/sft.cern.ch/lcg/views/LCG_97a/x86_64-centos7-gcc9-opt/bin/python"
cd ${B2HH_RUN}/Toys
# cuts_bdt="KK_0.04__PIPI_0.12"
# years="201516__2017s29r2p2__2018"
# magnets="Tot"
# Ncpu="1"

years=${1//'__'/' '}
magnets=${2//'__'/' '}
cuts_bdt=${3//'__'/' '}
Ncpu="4"
Ntoys=${4}
rm -f jobsPlots.txt

for cut_bdt in ${cuts_bdt}; do
    for year in ${years}; do
        for mag in ${magnets}; do
	    for toyIndex in `seq 0 $((${Ntoys}-1))`; do
		outDir="${cut_bdt}_${year}_${mag}"
		mkdir -p ${B2HH_OUT}/Toys/${outDir}/${toyIndex}/plots
		taggers=''
		if   [[ ${cut_bdt} == *GraNEW*  ]]; then taggers="OS_SSk"; ##should be SSk but we are reverting to daniele's baseline
		elif [[ ${cut_bdt} == *PIPI* ]]; then taggers="OS_SS";
		elif [[ ${cut_bdt} == *KK*   ]]; then taggers="OS_SSk";
		else continue;
		fi
		echo ${taggers} ${cut_bdt//"_"/" "} ${year} ${mag} ${toyIndex}
		${pythonNew} ${B2HH_SRC}/FitTotal/preparePlotJobs.py   \
                             -t ${taggers//"_"/" "}\
                             -C ${cut_bdt//"_"/" -b "}\
                             -y ${year}               \
                             -m ${mag}                \
                             -d ${outDir}             \
                             -n ${Ncpu}               \
			     -i ${toyIndex}
	    done
        done
    done
done

#condor_submit submitPlots.jdl
