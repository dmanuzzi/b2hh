#!/bin/bash

cd ${B2HH_RUN}/FitTotal
cuts_bdt="KK_0.04 PIPI_0.12"
years="201516 2017s29r2p2 2018"
magnets="Tot"
Ncpu="56"
rm -f jobsPlots.txt

vars="mass time eta asym"
massRanges="bkg sig523 sig5.33 sig5.45 total 3body'"
massRanges+="asymKK asymPIPI asymKPI asymKPIBs asymKKLow asymKKHigh"
finalStates="PIPI_tot KPI_tot KPI_kpi KPI_pik KK_tot"
btags="B Bbar Untag tot"

for cut_bdt in ${cuts_bdt}; do
    for year in ${years}; do
        for mag in ${magnets}; do
          outDir="${cut_bdt}_${year}_${mag}"
          mkdir -p ${B2HH_OUT}/FitTotal/${outDir}/plots
          taggers=''
          if   [[ ${cut_bdt} == *PIPI* ]]; then taggers="OS_SS";
          elif [[ ${cut_bdt} == *KK* ]];   then taggers="OS_SSk";
          else continue;
          fi

          python ${B2HH_SRC}/submitPlot.py \
                        ${taggers} ${cut_bdt//"_"/" "} ${year} ${mag}\
                        ${outDir}
            echo ${taggers} ${cut_bdt//"_"/" "} ${year} ${mag}
            echo ${taggers} ${cut_bdt//"_"/" "} ${year} ${mag} ${year} \
                 ${outDir}  ${Ncpu}             ${var}  ${massRange}   \
                 ${finalState}     ${btag}      ${ftag} ${tagger}>> jobs.txt


        done
    done
done

condor_submit submit.jdl
