#!/bin/bash
## echo kinit
## kinit
## echo lhcb-proxy-init
## lhcb-proxy-init
# rm -f ${B2HH_LOG}/Data/log/DataMerge.txt
# ${B2HH_RUN}/Data/runAll.sh
# condor_wait ${B2HH_LOG}/Data/log/DataMerge.txt

years="201516__2017s29r2p2__2018"
# years="201516_2017s29r2p2_2018"

#years="2015__2016"
#years="201516__2018"
#years="2017s29r2p2__2018"
#years="201516__2017s29r2p2"
# years="201516"
#years="2017s29r2p2"
# years="2018"
magnets="Tot"
#magnets="Up__Down"
#magnets="Tot__Up__Down"
cuts_pid="kpi_5.-2.-5.3__pik_-5.3.5.-2__pipi_-2.3.-2.3__kk_2.-2.2.-2"
#cuts_bdt="KK_0.1__PIPI_0.2"
#cuts_bdt="KK_0.1__KK_0.2__KK_0.3__KK_0.4"
cuts_bdt="KK_0.1"
#cuts_bdt="KK_0.3__KK_0.4"
#cuts_bdt="PIPI_0.2"
binnings="71_10_1_6"
effNoFid="0_0_0_0"
Ncpu="56"

opts="allConst" 
# opts+=" allConst_CalibTimeErr" 
# opts+=" allConst_CalibTimeErr_CalibTimeBias2" 

# opts+=" freeCPV_freeEpsFT" 
# opts+=" freeCPV_freeAp" 
#opts="freeCPV" 
#opts+=" freeCPV_CalibTimeErr_fromBs2Dspi_CalibTimeBias2" 
#opts+=" freeCPV_CalibTimeErr_fromJpsi_CalibTimeBias2" 


opts+=" freeCPV_freeAp_freeEpsFT" 
opts+=" freeCPV_freeAp_freeEpsFT_freeEpsAsymFT" 
#opts+=" freeCPV_freeAp_freeEpsFT_CalibTimeErr" 
#opts+=" freeCPV_freeAp_freeEpsFT_CalibTimeErr_CalibTimeBias2" 
#opts+=" freeCPV_freeAp_freeEpsFT_CalibTimeErr_fromBs2Dspi_CalibTimeBias2" 
#opts+=" freeCPV_freeAp_freeEpsFT_CalibTimeErr_fromJpsi_CalibTimeBias2" 

# opts+=" freeCPV_freeAp_freeEpsFT_AccFromSim" 
# opts+=" freeCPV_freeAp_freeEpsFT_FlatAcc" 
# opts+=" freeCPV_freeEpsFT_FlatAcc"
# opts+=" freeCKKSKK_freeAp_freeEpsFT_FlatAcc"
# opts+=" freeCKKSKK_freeEpsFT_FlatAcc"
# opts+=" freeCKKSKK_freeEpsFT_FlatAcc_ADG-0.5"

# opts=" OSonly_qOSplus_freeCPV" 
# opts+=" OSonly_qOSminus_freeCPV" 
# opts+=" SSonly_qSSplus_freeCPV" 
# opts+=" SSonly_qSSminus_freeCPV" 
# opts+=" qOSplus_qSSplus_freeCPV" 
# opts+=" qOSminus_qSSminus_freeCPV" 


## REDUCE
#rm -f ${B2HH_LOG}/Reduce/log/Reduce.txt
#${B2HH_RUN}/Reduce/runAll.sh ${years} ${magnets} ${cuts_bdt}

## sPlot
#rm -f ${B2HH_LOG}/sPlot/log/sPlot_create.txt
#rm -f ${B2HH_LOG}/sPlot/log/sPlot_fit.txt
#${B2HH_RUN}/sPlot/runAll.sh ${years} ${magnets} ${cuts_bdt} 

# condor_wait ${B2HH_LOG}/Reduce/log/Reduce.txt
# #### REDUCE DONE
# condor_wait ${B2HH_LOG}/sPlot/log/sPlot_fit.txt
# #### SPLOT DONE

## PID
#rm -f ${B2HH_LOG}/PID/log/PID.txt
#${B2HH_RUN}/PID/runAll.sh ${years} ${magnets} ${cuts_bdt} ${cuts_pid} ${binnings}
### PID DONE


## MassModels
#rm -f ${B2HH_LOG}/MassModels/CrossFeed/log/MassModels_CrossFeed.txt
#${B2HH_RUN}/MassModels/CrossFeed/runAll.sh ${years} ${magnets} ${cuts_bdt} ${cuts_pid} ${effNoFid}

## TimeModels
#rm -f ${B2HH_LOG}/TimeModels/log/TimeModels.txt
#${B2HH_RUN}/TimeModels/runAll.sh ${years} ${magnets} ${cuts_bdt} 

## Tagging
#rm -f ${B2HH_LOG}/Tagging/log/Tagging.txt
#${B2HH_RUN}/Tagging/runAll.sh  ${years} ${magnets} ${cuts_bdt}

## TimeErr
# rm -f ${B2HH_LOG}/TimeErr/log/TimeErr.txt
# ${B2HH_RUN}/TimeErr/runAll.sh  ${years} ${magnets} ${cuts_bdt}

#condor_wait ${B2HH_LOG}/TimeModels/log/TimeModels.txt
### TIME MODELS DONE

# # AccSignal
# rm -f ${B2HH_LOG}/AccSignal/log/AccSignal.txt
# ${B2HH_RUN}/AccSignal/runAll.sh ${years} ${magnets} ${cuts_bdt} ${cuts_pid}

#condor_wait ${B2HH_LOG}/AccSignal/log/AccSignal.txt
#condor_wait ${B2HH_LOG}/MassModels/CrossFeed/log/MassModels_CrossFeed.txt
#condor_wait ${B2HH_LOG}/Tagging/log/Tagging.txt

# # FitTotal
# rm -rf  ${B2HH_LOG}/FitTotal/log/FitTotal.txt
# ${B2HH_RUN}/FitTotal/runAll.sh ${years} ${magnets} ${cuts_bdt} ${Ncpu}

# # Plots FitTotal
# condor_wait ${B2HH_LOG}/FitTotal/log/FitTotal.txt
# ${B2HH_RUN}/FitTotal/runAllPlots.sh ${years} ${magnets} ${cuts_bdt} 1

# # sPlotFinal
# rm -rf  ${B2HH_LOG}/sPlotFinal/log/sPlot.txt
# ${B2HH_RUN}/sPlotFinal/runAll_sPlot.sh ${years} ${magnets} ${cuts_bdt} ${Ncpu}

# # sFit
# rm -f  ${B2HH_LOG}/sFit/log/sFit.txt
# rm -f ${B2HH_RUN}/sFit/jobs.txt
# for opt in  ${opts}; do
#     echo ${opt}
#     ${B2HH_RUN}/sFit/runAll.sh ${years} ${magnets} ${cuts_bdt} ${Ncpu} ${opt}
#     # ${B2HH_RUN}/sFit/runAll.sh ${years} ${magnets} ${cuts_bdt} ${Ncpu} OSonly_${opt}
#     # ${B2HH_RUN}/sFit/runAll.sh ${years} ${magnets} ${cuts_bdt} ${Ncpu} MC_${opt}
#     # ${B2HH_RUN}/sFit/runAll.sh ${years} ${magnets} ${cuts_bdt} ${Ncpu} MC_OSonly_${opt}
# done
# cd ${B2HH_RUN}/sFit
# condor_submit submit.jdl
# # # Plot sFit
# condor_wait ${B2HH_LOG}/sFit/log/sFit.txt
# rm -f ${B2HH_RUN}/sFit/jobsPlots.txt
# for opt in  ${opts}; do
#     # ${B2HH_RUN}/sFit/runAllPlots.sh ${years} ${magnets} ${cuts_bdt} 1 ${opt}
#     # ${B2HH_RUN}/sFit/runAllPlots.sh ${years} ${magnets} ${cuts_bdt} 1 OSonly_${opt}
#     ${B2HH_RUN}/sFit/runAllPlots.sh ${years} ${magnets} ${cuts_bdt} 1 MC_${opt}
#     ${B2HH_RUN}/sFit/runAllPlots.sh ${years} ${magnets} ${cuts_bdt} 1 MC_OSonly_${opt}
# done
# condor_submit submitPlots.jdl
# cd ${B2HH_RUN}

#### sFitTimeErr
rm -f ${B2HH_LOG}/sFitTimeErr/log/sFitTimeErr.txt
rm -f ${B2HH_RUN}/sFitTimeErr/jobs.txt
for opt in  ${opts}; do
    echo ${opt}
    # ${B2HH_RUN}/sFitTimeErr/runAll.sh ${years} ${magnets} ${cuts_bdt} ${Ncpu} ${opt}
    # ${B2HH_RUN}/sFitTimeErr/runAll.sh ${years} ${magnets} ${cuts_bdt} ${Ncpu} OSonly_${opt}
    ${B2HH_RUN}/sFitTimeErr/runAll.sh ${years} ${magnets} ${cuts_bdt} ${Ncpu} MC_${opt}
    # ${B2HH_RUN}/sFitTimeErr/runAll.sh ${years} ${magnets} ${cuts_bdt} ${Ncpu} MC_OSonly_${opt}
done
cd ${B2HH_RUN}/sFitTimeErr
condor_submit submit.jdl
cd ${B2HH_RUN}

########## Plot sFitTimeErr
condor_wait ${B2HH_LOG}/sFitTimeErr/log/sFitTimeErr.txt
rm -f ${B2HH_RUN}/sFitTimeErr/jobsPlots.txt
for opt in  ${opts}; do
    echo ${opt}
    # ${B2HH_RUN}/sFitTimeErr/runAllPlots.sh ${years} ${magnets} ${cuts_bdt} 1 ${opt}
    # ${B2HH_RUN}/sFitTimeErr/runAllPlots.sh ${years} ${magnets} ${cuts_bdt} 1 OSonly_${opt}
    ${B2HH_RUN}/sFitTimeErr/runAllPlots.sh ${years} ${magnets} ${cuts_bdt} 1 MC_${opt}
    # ${B2HH_RUN}/sFitTimeErr/runAllPlots.sh ${years} ${magnets} ${cuts_bdt} 1 MC_OSonly_${opt}
done
cd ${B2HH_RUN}/sFitTimeErr
condor_submit submitPlots.jdl
cd ${B2HH_RUN}
