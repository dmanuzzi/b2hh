#!/bin/bash

mkdir -p ${B2HH_OUT}/resT/plots
mkdir -p ${B2HH_OUT}/resT/sWeights
mkdir -p ${B2HH_OUT}/resT/tuples
mkdir -p ${B2HH_OUT}/resT/stats
mkdir -p ${B2HH_OUT}/resT/params
mkdir -p ${B2HH_LOG}/resT/out
mkdir -p ${B2HH_LOG}/resT/err
mkdir -p ${B2HH_LOG}/resT/log



years=${1//'__'/' '}
magnets=${2//'__'/' '}
cuts_bdt=${3//'__'/' '}
#cuts_pid=${4//'__'/' '}
#PIDkpi=''
#PIDpik=''
#PIDpipi=''
#PIDkk=''
#for cut_pid in $cuts_pid; do
#    if    [[ $cut_pid == *kpi* ]]; then PIDkpi=$cut_pid; continue;
#    elif  [[ $cut_pid == *pik* ]]; then PIDpik=$cut_pid; continue;
#    elif  [[ $cut_pid == *pipi* ]]; then PIDpipi=$cut_pid; continue;
#    elif  [[ $cut_pid == *kk* ]]; then PIDkk=$cut_pid; continue;
#    fi
#done


# tuples
# TODO

# sWeights
# TODO

# run calibrations
cd ${B2HH_SRC}/resT
touch resolution.C
touch resFit.C
touch averageSigmaT.C
source ${setup_LCG_106}
make resolution
make resFit
make averageSigmaT

cd ${B2HH_RUN}/resT

rm jobs.txt

#WARNING: in the current implementation no kine reweight is included for MC (both Jpsi and B2HH)

for year in ${years}; do
    for mag in ${magnets}; do
	_year=${year}
	if [[ ${year} == "201516" ]]; then _year="2016"; fi
	if [[ ${year} == "2017s29r2p2" ]]; then _year="2017"; fi
	echo Jpsi ${_year} ${mag} data Nsig_sw NONE NONE >> jobs.txt
	echo Jpsi ${_year} ${mag} MC NONE NONE NONE >> jobs.txt
	for cut_bdt in ${cuts_bdt}; do
	    #TODO: to work with multiple PID cuts the configuration of MC case should depend also on the PID cut
	    echo bskk_kk ${year} ${mag} MC weight ${cut_bdt//'_'/' '} >> jobs.txt
	    echo bspipi_pipi ${year} ${mag} MC weight ${cut_bdt//'_'/' '} >> jobs.txt
	done
    done
done

#condor_submit submit.jdl
#condor_wait ../../log/resT/log/resT.txt
for year in ${years}; do
    for mag in ${magnets}; do
	for cut_bdt in ${cuts_bdt}; do
	    echo '+---------------------------------------------------+'
	    echo "| ${year} ${mag} ${cut_bdt} pol1 |"
	    echo '+---------------------------------------------------+'
	    ${B2HH_SRC}/resT/averageSigmaT -y ${year} -m ${mag} -n ${cut_bdt//'_'/' -b '} -M pol1
	    echo ''
	done
    done
done



