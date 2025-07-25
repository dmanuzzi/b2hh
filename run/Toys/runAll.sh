#!/bin/bash
mkdir -p ${B2HH_LOG}/Toys
mkdir -p ${B2HH_LOG}/Toys/log
mkdir -p ${B2HH_LOG}/Toys/out
mkdir -p ${B2HH_LOG}/Toys/err
mkdir -p ${B2HH_OUT}/Toys

cd ${B2HH_RUN}/Toys


years=${1//'__'/' '}
magnets=${2//'__'/' '}
cuts_bdt=${3//'__'/' '}
Ntoys=${4}
Ncpu=${5}
opts=${6//'__'/' '}
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
		mkdir -p ${B2HH_OUT}/Toys/${outDir}
		taggers=''
		if   [[ ${cut_bdt} == *GraNEW* ]];  then taggers="OS_SSk"; ##should be SSk but we are reverting to daniele's baseline
		elif [[ ${cut_bdt} == *PIPI* ]]; then taggers="OS_SS";
		elif [[ ${cut_bdt} == *KK* ]];   then taggers="OS_SSk";
		else continue;
		fi
		echo ${taggers} ${cut_bdt//"_"/" "} ${year} ${mag} ${opt}
		for i in `seq 20 $((${Ntoys}-1))`; do
		    echo ${taggers} ${cut_bdt//"_"/" "} ${year} ${mag} ${year} ${outDir} ${i} ${Ncpu} >> jobs.txt
		done
	    done
        done
    done
done

condor_submit submit.jdl
