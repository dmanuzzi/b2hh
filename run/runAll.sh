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
cuts_bdt="KK_0.1_KK_0.2_KK_0.3_KK_0.4"
#cuts_bdt="PIPI_0.2"
binnings="71_10_1_6"
effNoFid="0_0_0_0"
Ncpu="56"

## REDUCE
rm -f ${B2HH_LOG}/Reduce/log/Reduce.txt
${B2HH_RUN}/Reduce/runAll.sh ${years} ${magnets} ${cuts_bdt}

## sPlot
#rm -f ${B2HH_LOG}/sPlot/log/sPlot.txt
#${B2HH_RUN}/sPlot/runAll.sh ${years} ${magnets} ${cuts_bdt} 

# condor_wait ${B2HH_LOG}/Reduce/log/Reduce.txt
# #### REDUCE DONE
# condor_wait ${B2HH_LOG}/sPlot/log/sPlot.txt
# #### SPLOT DONE

## PID
#rm -f ${B2HH_LOG}/PID/log/PID.txt
#${B2HH_RUN}/PID/runAll.sh ${years} ${magnets} ${cuts_bdt} ${cuts_pid} ${binnings}
#### PID DONE


## MassModels
#rm -f ${B2HH_LOG}/MassModels/CrossFeed/log/MassModels_CrossFeed.txt
#${B2HH_RUN}/MassModels/CrossFeed/runAll.sh ${years} ${magnets} ${cuts_bdt} ${cuts_pid} ${effNoFid}

## TimeModels
#rm -f ${B2HH_LOG}/TimeModels/log/TimeModels.txt
#${B2HH_RUN}/TimeModels/runAll.sh ${years} ${magnets} ${cuts_bdt} 

## Tagging
#rm -f ${B2HH_LOG}/Tagging/log/Tagging.txt
#${B2HH_RUN}/Tagging/runAll.sh  ${years} ${magnets} ${cuts_bdt}

#condor_wait ${B2HH_LOG}/TimeModels/log/TimeModels.txt
### TIME MODELS DONE

# AccSignal
#rm -f ${B2HH_LOG}/AccSignal/log/AccSignal.txt
#${B2HH_RUN}/AccSignal/runAll.sh ${years} ${magnets} ${cuts_bdt}


#condor_wait ${B2HH_LOG}/AccSignal/log/AccSignal.txt
#condor_wait ${B2HH_LOG}/MassModels/CrossFeed/log/MassModels_CrossFeed.txt
#condor_wait ${B2HH_LOG}/Tagging/log/Tagging.txt

## FitTotal
#rm -rf  ${B2HH_LOG}/FitTotal/log/FitTotal.txt
#${B2HH_RUN}/FitTotal/runAll.sh ${years} ${magnets} ${cuts_bdt} ${Ncpu}

## Plots FitTotal
#condor_wait ${B2HH_LOG}/FitTotal/log/FitTotal.txt
#${B2HH_RUN}/FitTotal/runAllPlots.sh ${years} ${magnets} ${cuts_bdt} 1
