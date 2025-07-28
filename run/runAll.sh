#!/bin/bash
## echo kinit
## kinit
## echo lhcb-proxy-init
## lhcb-proxy-init
#rm -f ${B2HH_LOG}/Data/log/DataMerge.txt
#${B2HH_RUN}/Data/runAll.sh
#condor_wait ${B2HH_LOG}/Data/log/DataMerge.txt

#years="201516__2017s29r2p2__2018"
years="Tot"
#years="201516__2017s29r2p2__2018__Tot"
#years="2018__Tot"

# years="2015__2016"
# years="201516__2018"
# years="2017s29r2p2__201516"
# years="201516__2017s29r2p2"
#years="201516"
#years="2017s29r2p2__2018"
#years="2017s29r2p2"
#years="201516__2017s29r2p2__2018"

#years="Tot"

#years="2018"
#years="201516__2018"

magnets="Tot"
#magnets="Up__Down" #missing efficiency maps for down magnet polarity

cuts_pid="kpi_5.-2.-5.3__pik_-5.3.5.-2__pipi_-1.3.-1.3__kk_2.-2.2.-2"

#cuts_bdt="KK_0.1__PIPI_0.2"
#cuts_bdt="KK_0.1__KK_0.2__KK_0.3__KK_0.4"
#cuts_bdt="PIPI_0" #

#cuts_bdt="GraNEW_0.76__GraNEW_0.78__GraNEW_0.8__GraNEW_0.82__GraNEW_0.84"
#cuts_bdt="GraNEW_0.86"
#cuts_bdt="GraNEW_0.83"
cuts_bdt="GraNEW_0.78__GraNEW_0.8__GraNEW_0.83__GraNEW_0.86__GraNEW_0.89"
#cuts_bdt="GraNEW_0.78__GraNEW_0.8__GraNEW_0.83__GraNEW_0.89"
#cuts_bdt="GraNEW_0.78__GraNEW_0.86__GraNEW_0.89"
#cuts_bdt="GraNEW_0.8__GraNEW_0.83"


#cuts_bdt="KK_0.3__KK_0.4"
#cuts_bdt="PIPI_0.2"
binnings="71_10_1_6"
effNoFid="0_0_0_0"
Ncpu="64"
Ntoys="21"
opts=''
opts+="__noCPVbspipi"

: '
opts+=" OSonly_newFTcalib_freeCPV_freeEpsFT"
opts+=" SSonly_newFTcalib_freeCPV_freeEpsFT"
opts+=" newFTcalib_freeCPV_freeEpsFT_freeAp"
opts+=" OSonly_newFTcalib_freeCPV_freeEpsFT_freeAp"
opts+=" SSonly_newFTcalib_freeCPV_freeEpsFT_freeAp"
'


## REDUCE                #okay tot,up,down
#rm -f ${B2HH_LOG}/Reduce/log/Reduce.txt
#${B2HH_RUN}/Reduce/runAll.sh ${years} ${magnets} ${cuts_bdt}

## sPlot  ##CHECK FIT CONVERGENCE
#rm -f ${B2HH_LOG}/sPlot/log/sPlot_create.txt
#rm -f ${B2HH_LOG}/sPlot/log/sPlot_fit.txt
#${B2HH_RUN}/sPlot/runAll.sh ${years} ${magnets} ${cuts_bdt} 

#condor_wait ${B2HH_LOG}/Reduce/log/Reduce.txt
##### REDUCE DONE
#condor_wait ${B2HH_LOG}/sPlot/log/sPlot_fit.txt
# #### SPLOT DONE
 
## PID                   #okay tot,up, -> down not ok for PIPI  -> DOING TOT ANA
#rm -f ${B2HH_LOG}/PID/log/PID.txt
#${B2HH_RUN}/PID/runAll.sh ${years} ${magnets} ${cuts_bdt} ${cuts_pid} ${binnings}
### PID DONE

## MassModels            #okay tot -> missing Tot all years 
#rm -f ${B2HH_LOG}/MassModels/CrossFeed/log/MassModels_CrossFeed.txt
#${B2HH_RUN}/MassModels/CrossFeed/runAll.sh ${years} ${magnets} ${cuts_bdt} ${cuts_pid} ${effNoFid}

## TimeModels                         ###something fishy going on in the canvas printing wtf 
#rm -f ${B2HH_LOG}/TimeModels/log/TimeModels.txt
#${B2HH_RUN}/TimeModels/runAll.sh ${years} ${magnets} ${cuts_bdt} 



## Tagging
#rm -f ${B2HH_LOG}/Tagging/log/Tagging.txt
#${B2HH_RUN}/Tagging/runAll.sh  ${years} ${magnets} ${cuts_bdt}

#condor_wait ${B2HH_LOG}/TimeModels/log/TimeModels.txt
### TIME MODELS DONE

# AccSignal
#rm -f ${B2HH_LOG}/AccSignal/log/AccSignal.txt
#${B2HH_RUN}/AccSignal/runAll.sh ${years} ${magnets} ${cuts_bdt} ${cuts_pid}

#####
#####
#####

#up to this point code RUNS, now onto the physics -> FitTotal will require dedicated debugging

#condor_wait ${B2HH_LOG}/AccSignal/log/AccSignal.txt
#condor_wait ${B2HH_LOG}/MassModels/CrossFeed/log/MassModels_CrossFeed.txt
#condor_wait ${B2HH_LOG}/Tagging/log/Tagging.txt

##we running MassFit -> taken from old b2hh

#### MassFit #wants magnet tot -> due to database files
###rm -rf  ${B2HH_LOG}/MassFit/log/MassFit.txt
###${B2HH_RUN}/MassFit/runAll.sh ${years} ${magnets} ${cuts_bdt} ${Ncpu}

#### Plots MassFit
###condor_wait ${B2HH_LOG}/MassFit/log/MassFit.txt
###echo "End Time: $(date)"
###${B2HH_RUN}/MassFit/runAllPlots.sh ${years} ${magnets} ${cuts_bdt} 1









## FitTotal
#rm -rf  ${B2HH_LOG}/FitTotal/log/FitTotal.txt
#${B2HH_RUN}/FitTotal/runAll.sh ${years} ${magnets} ${cuts_bdt} ${Ncpu} ${opts}

## Plots FitTotal    
#condor_wait ${B2HH_LOG}/FitTotal/log/FitTotal.txt
#${B2HH_RUN}/FitTotal/runAllPlots.sh ${years} ${magnets} ${cuts_bdt} 1 ${opts}



## Toys
rm -rf  ${B2HH_LOG}/Toys/fit/log/Toys.txt
${B2HH_RUN}/Toys/runAll.sh ${years} ${magnets} ${cuts_bdt} ${Ntoys} 8 ${opts}

## Plots Toys
#condor_wait ${B2HH_LOG}/Toys/fit/log/Toys.txt
#${B2HH_RUN}/Toys/runAllPlots.sh ${years} ${magnets} ${cuts_bdt} 5 #${Ntoys}













## MassFit
# rm -rf  ${B2HH_LOG}/MassFit/log/MassFit.txt
#${B2HH_RUN}/MassFit/runAll.sh ${years} ${magnets} ${cuts_bdt} ${Ncpu}

## Plots MassFit
# condor_wait ${B2HH_LOG}/MassFit/log/MassFit.txt
#${B2HH_RUN}/MassFit/runAllPlots.sh ${years} ${magnets} ${cuts_bdt} 1

## sPlotFinal
# rm -rf  ${B2HH_LOG}/sPlotFinal/log/sPlot.txt
# ${B2HH_RUN}/sPlotFinal/runAll_sPlot.sh ${years} ${magnets} ${cuts_bdt} ${Ncpu}


: '
#### sFit
rm -f  ${B2HH_LOG}/sFit/log/sFit.txt
rm -f ${B2HH_RUN}/sFit/jobs.txt
for opt in  ${opts}; do
    echo ${opt}
 #   ${B2HH_RUN}/sFit/runAll.sh ${years} ${magnets} ${cuts_bdt} ${Ncpu} ${opt}
#    ${B2HH_RUN}/sFit/runAll.sh ${years} ${magnets} ${cuts_bdt} ${Ncpu} OSonly_${opt}
    #${B2HH_RUN}/sFit/runAll.sh ${years} ${magnets} ${cuts_bdt} ${Ncpu} MC_${opt}
    #${B2HH_RUN}/sFit/runAll.sh ${years} ${magnets} ${cuts_bdt} ${Ncpu} MC_OSonly_${opt}
done
cd ${B2HH_RUN}/sFit
condor_submit submit.jdl
# #### Plot sFit
condor_wait ${B2HH_LOG}/sFit/log/sFit.txt
rm -f ${B2HH_RUN}/sFit/jobsPlots.txt
for opt in  ${opts}; do
    echo ${opt}
#    ${B2HH_RUN}/sFit/runAllPlots.sh ${years} ${magnets} ${cuts_bdt} 1 ${opt}
    # ${B2HH_RUN}/sFit/runAllPlots.sh ${years} ${magnets} ${cuts_bdt} 1 OSonly_${opt}
    #${B2HH_RUN}/sFit/runAllPlots.sh ${years} ${magnets} ${cuts_bdt} 1 MC_${opt}
    #${B2HH_RUN}/sFit/runAllPlots.sh ${years} ${magnets} ${cuts_bdt} 1 MC_OSonly_${opt}
done
condor_submit submitPlots.jdl
cd ${B2HH_RUN}
'
