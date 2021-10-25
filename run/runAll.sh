#!/bin/bash

## kinit
## lhcb-proxy-init
# rm -f ${B2HH_LOG}/Data/log/DataMerge.txt
# ${B2HH_RUN}/Data/runAll.sh
# condor_wait ${B2HH_LOG}/Data/log/DataMerge.txt

## REDUCE
# rm -f ${B2HH_LOG}/Reduce/log/Reduce.txt
# ${B2HH_RUN}/Reduce/runAll.sh

## sPlot
# rm -f ${B2HH_LOG}/sPlot/log/sPlot.txt
# ${B2HH_RUN}/sPlot/runAll.sh

## PID
# rm -f ${B2HH_LOG}/PID/log/PID.txt
# ${B2HH_RUN}/PID/runAll.sh
#### PID DONE

# condor_wait ${B2HH_LOG}/Reduce/log/Reduce.txt
#### REDUCE DONE

## MassModels
#rm -f ${B2HH_LOG}/MassModels/CrossFeed/log/MassModels_CrossFeed.txt
#${B2HH_RUN}/MassModels/CrossFeed/runAll.sh

## TimeModels
#rm -f ${B2HH_LOG}/TimeModels/log/TimeModels.txt
#${B2HH_RUN}/TimeModels/runAll.sh

#condor_wait ${B2HH_LOG}/sPlot/log/sPlot.txt
#### SPLOT DONE

## Tagging
#rm -f ${B2HH_LOG}/Tagging/log/Tagging.txt
#${B2HH_RUN}/Tagging/runAll.sh

#condor_wait ${B2HH_LOG}/TimeModels/log/TimeModels.txt
#### TIME MODELS DONE

## AccSignal
# rm -f ${B2HH_LOG}/AccSignal/log/AccSignal.txt
# ${B2HH_RUN}/AccSignal/runAll.sh


#condor_wait ${B2HH_LOG}/AccSignal/log/AccSignal.txt
#condor_wait ${B2HH_LOG}/MassModels/CrossFeed/log/MassModels_CrossFeed.txt
#condor_wait ${B2HH_LOG}/Tagging/log/Tagging.txt

## FitTotal
${B2HH_RUN}/FitTotal/runAll.sh