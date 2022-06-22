#!/bin/bash
source ${setup_LCG_std}
cd ${B2HH_SRC}/AccSignal
make plotRatios_year
make plotAcceptances_year

for name in 'bdkpi' 'bdkpi_pipi' 'bdkpi_kk' 'bdpipi' 'bdpipi_kpi' 'bdkk' 'bskk' 'bskk_kpi' 'bskpi' 'bspipi' 'lbpk_kk'; do
    for bdt in 'PIPI_0.2' 'KK_0.1'; do
	echo  "$name" "$bdt" 
#	./plotRatios_year "$name" "$bdt" "Tot" "U"
#	./plotRatios_year "$name" "$bdt" "Tot" "T"
    done
done

for name in 'data' 'bdkpi_kpi' 'bdkpi_pipi' 'bdkpi_kk' 'bdpipi_pipi' 'bdpipi_kpi' 'bdkk_kk' 'bskk_kk' 'bskk_kpi' 'bskpi_kpi' 'bspipi_pipi' 'lbpk_kk'; do
    for bdt in 'PIPI_0.2' 'KK_0.1'; do
	echo  "$name" "$bdt" 
	./plotAcceptances_year "$name" "$bdt" "Tot" 
	./plotAcceptances_year "$name" "$bdt" "Tot" "T"
    done
done
