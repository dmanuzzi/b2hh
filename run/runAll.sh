#!/bin/bash
## echo kinit
## kinit
## echo lhcb-proxy-init
## lhcb-proxy-init
#rm -f ${B2HH_LOG}/Data/log/DataMerge.txt
#${B2HH_RUN}/Data/runAll.sh
#condor_wait ${B2HH_LOG}/Data/log/DataMerge.txt

years="201516__2017s29r2p2__2018"
#years="2015__2016"
#years="201516__2018"
#years="2017s29r2p2__2018"
#years="201516__2017s29r2p2"
#years="201516"
#years="2017s29r2p2"
#years="2018"
magnets="Tot"
#magnets="Up__Down"
#magnets="Tot__Up__Down"
cuts_pid="kpi_5.-2.-5.3__pik_-5.3.5.-2__pipi_-2.3.-2.3__kk_2.-2.2.-2"
#cuts_bdt="KK_0.1__PIPI_0.2"
cuts_bdt="KK_0.1"
#cuts_bdt="PIPI_0.2"
binnings="71_10_1_6"
effNoFid="0_0_0_0"
Ncpu="56"


## FitTotal
rm -rf  ${B2HH_LOG}/FitTotal/log/FitTotal.txt
${B2HH_RUN}/FitTotal/runAll.sh ${years} ${magnets} ${cuts_bdt} ${Ncpu}

## Plots FitTotal
#condor_wait ${B2HH_LOG}/FitTotal/log/FitTotal.txt
#${B2HH_RUN}/FitTotal/runAllPlots.sh ${years} ${magnets} ${cuts_bdt} 1
