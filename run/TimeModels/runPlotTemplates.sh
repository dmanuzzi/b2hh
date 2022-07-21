#!/bin/bash
source ${setup_LCG_std}
cd ${B2HH_SRC}/TimeModels
make plotTemplates_years

for name in 'kpi' 'pipi' 'kk'; do
    for bdt in 'PIPI_0.2' 'KK_0.1'; do
	${B2HH_SRC}/TimeModels/plotTemplates_years "$name" "$bdt" "Tot" "00"
	${B2HH_SRC}/TimeModels/plotTemplates_years "$name" "$bdt" "Tot" "01"
	${B2HH_SRC}/TimeModels/plotTemplates_years "$name" "$bdt" "Tot" "10"
	${B2HH_SRC}/TimeModels/plotTemplates_years "$name" "$bdt" "Tot" "11"
	${B2HH_SRC}/TimeModels/plotTemplates_years "$name" "$bdt" "Tot" "U"
	${B2HH_SRC}/TimeModels/plotTemplates_years "$name" "$bdt" "Tot" "T"
    done
done
