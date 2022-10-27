#!/bin/bash
source /cvmfs/sft.cern.ch/lcg/views/LCG_86/x86_64-slc6-gcc62-opt/setup.sh
#make plotRatios_year
#make plotAcceptances_year
make plotAcceptances_bdtCuts
for name in 'data' 'bdkpi_kpi' 'bdkpi_pipi' 'bdkpi_kk' 'bdpipi_pipi' 'bdpipi_kpi' 'bdkk_kk' 'bskk_kk' 'bskk_kpi' 'bskpi_kpi' 'bspipi_pipi' 'lbpk_kk'; do
    for year in '201516' '2017s29r2p2' '2018'; do
#    for year in '20151618' ; do
	./plotAcceptances_bdtCuts "$name" "$year" "Tot" 
	./plotAcceptances_bdtCuts "$name" "$year" "Tot" "T"
    done
done
#for name in 'bdkpi' 'bdkpi_pipi' 'bdkpi_kk' 'bdpipi' 'bdpipi_kpi' 'bdkk' 'bskk' 'bskk_kpi' 'bskpi' 'bspipi' 'lbpk_kk'; do
#    #for bdt in 'PIPI_0.12' 'KK_0.04' 'KK_0.06' 'KK_0.08'; do
#    for bdt in 'PIPI_0.12' 'KK_0.04'; do
#	echo  "$name" "$bdt" 
#	./plotRatios_year "$name" "$bdt" "Tot" "U"
#	./plotRatios_year "$name" "$bdt" "Tot" "T"
#    done
#done

#for name in 'data' 'bdkpi_kpi' 'bdkpi_pipi' 'bdkpi_kk' 'bdpipi_pipi' 'bdpipi_kpi' 'bdkk_kk' 'bskk_kk' 'bskk_kpi' 'bskpi_kpi' 'bspipi_pipi' 'lbpk_kk'; do
#    for bdt in 'PIPI_0.12' 'KK_0.04' 'KK_0.06' 'KK_0.08'; do
#	echo  "$name" "$bdt" 
#	./plotAcceptances_year "$name" "$bdt" "Tot" 
#	./plotAcceptances_year "$name" "$bdt" "Tot" "T"
#    done
#done
