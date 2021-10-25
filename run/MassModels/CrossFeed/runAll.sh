#!/bin/bash


mkdir -p ${B2HH_LOG}/MassModels/CrossFeed/out
mkdir -p ${B2HH_LOG}/MassModels/CrossFeed/err
mkdir -p ${B2HH_LOG}/MassModels/CrossFeed/log

mkdir -p ${B2HH_OUT}/MassModels/CrossFeed

cd ${B2HH_SRC}/MassModels/CrossFeed
touch *.C
${lbRunDaVinciOld} make create

cd ${B2HH_RUN}/MassModels/CrossFeed

magnets="Tot"
years="201516 2017s29r2p2 2018"
effNoFid="0_0_0_0"
cuts_pid="kpi_5.-2.-5.3 pik_-5.3.5.-2 pipi_-2.3.-2.3 kk_2.-2.2.-2"
cuts_bdt="KK_0.04 PIPI_0.12"

rm -f jobs.txt
for cut_bdt in ${cuts_bdt}; do
    for cut_pid in ${cuts_pid}; do
        for year in ${years}; do
            for mag in ${magnets}; do
                echo ${cut_bdt//"_"/" "} ${cut_pid//"_"/" "} ${year} ${mag} ${effNoFid}
                echo ${cut_bdt//"_"/" "} ${cut_pid//"_"/" "} ${year} ${mag} ${effNoFid} >> jobs.txt                
            done
        done
    done
done

condor_submit submit.jdl