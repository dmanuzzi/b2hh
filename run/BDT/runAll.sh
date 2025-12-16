#!/bin/bash

mkdir -p ${B2HH_LOG}/BDT/out
mkdir -p ${B2HH_LOG}/BDT/err
mkdir -p ${B2HH_LOG}/BDT/log

#mkdir -p ${B2HH_OUT}/BDT/models
#mkdir -p ${B2HH_OUT}/BDT/plots

#mkdir -p ${B2HH_OUT}/BDT/Norm/
#mkdir -p ${B2HH_OUT}/BDT/Norm/temp #temporary for the assignment

mkdir -p ${B2HH_OUT}/Data/temp

hostname
######################################################################################################################################
###################
# T r a i n i n g #
###################

models="gradient"
#models="gradient__adaboost" # adaboost needs to be checked for compatibility

ids="1 2 3"
treeSizes="100 200 300 400 500 600 700 800"
treeDepths="1 2 3 4 5 6 7"

#ids="1"
treeSizes="400"
treeDepths="4"

: '
optionalFlag="removedFeatures"

rm jobs_train.txt
for model in ${models}; do
    for id in ${ids}; do
        for treeSize in ${treeSizes}; do
            for treeDepth in ${treeDepths}; do
                echo ${model} ${id} ${treeSize} ${treeDepth} ${optionalFlag}
                echo ${model} ${id} ${treeSize} ${treeDepth} ${optionalFlag} >> jobs_train.txt
            done
        done
    done
done

#condor_submit submit_train.jdl
condor_submit submit_train_flag.jdl
#condor_wait ${B2HH_LOG}/newBDTtrain/log/training_newBDT.txt
'

: '
######################################################################################################################################
###################
##  A s s i g n  ##
###################
mkdir -p ${B2HH_OUT}/newBDTtrain/forNorm/bitFix
rm jobs_assign.txt

channels="bspipi"
years="201516 2017s29r2p2 2018"
polarities="Tot"

for channel in ${channels}; do
    for year in ${years}; do
        for polarity in ${polarities}; do
            echo ${channel} ${year} ${polarity}
            echo ${channel} ${year} ${polarity} >> jobs_assign.txt
        done
    done
done

channels="b2hh sideband_b2hh"
years="2015 2016 2017s29r2p2 2018"
polarities="Up Down"

for channel in ${channels}; do
    for year in ${years}; do
        for polarity in ${polarities}; do
            echo ${channel} ${year} ${polarity}
            echo ${channel} ${year} ${polarity} >> jobs_assign.txt
        done
    done
done
condor_submit sub_assign.jdl
condor_wait ${B2HH_LOG}/newBDTtrain/log/assign_newBDTtrain_forNorm.txt

######################################################################################################################################
###############################
## N o r m a l i s a t i o n ##
###############################
#running the normalisation
( #limiting the environment sourcing, we want to keep the shell cleaned #use ( )
cd $B2HH_SRC/newBDTtrain
source ${setup_LCG_105}
g++ normalisation.cpp sel_RooJohnsonFunc.cxx sel_RooJohnsonFunc_dict.cxx -o normalisation `root-config --cflags --libs` -lRooFit -lRooFitCore
cd $B2HH_RUN/newBDTtrain

rm jobs_norm.txt

#channels="bdpipi" #legacy b2hh -> hardcoded for the bdpipi (PIPI final state) / also contains hardcoded BDT old cut
#years="201516 2017s29r2p2 2018"
years="201516 2017s29r2p2 2018"
polarities="Tot" #mass models only for magnet Tot -> should get also CF models for separated magnet polarity
#PIDcuts="-1.3.-1.3"  #PID cuts are hardcoded in normalisation 
#for channel in ${channels}; do
    for year in ${years}; do
        for polarity in ${polarities}; do
            #for PIDcut in ${PIDcuts}; do
                #echo ${channel} ${year} ${polarity} ${PIDcut}
                #echo ${channel} ${year} ${polarity} ${PIDcut} >> jobs_norm.txt
                echo ${year} ${polarity}
                echo ${year} ${polarity} >> jobs_norm.txt
            #done
        done
    done
#done

condor_submit sub_norm.jdl
)

######################################################################################################################################
##############################
## O p t i m i s a t i o n ###
##############################
rm jobs_optim.txt
echo "ATTENTION: hardcoded bdts in the runAll.sh"

bdts="bdtgradient_300_3 bdtgradient_300_4 bdtgradient_300_5 bdtgradient_300_6 bdtgradient_400_3 bdtgradient_400_4 bdtgradient_400_5 bdtgradient_400_6 bdtgradient_500_3 bdtgradient_500_4 bdtgradient_500_5 bdtgradient_500_6 bdtgradient_600_3 bdtgradient_600_4 bdtgradient_600_5 bdtgradient_600_6 bdtgradient_700_3 bdtgradient_700_4 bdtgradient_700_5 bdtgradient_700_6"

mkdir -p ${B2HH_OUT}/newBDTtrain/BDToptim/bestSignificances

for bdt in ${bdts}; do
    mkdir -p ${B2HH_OUT}/newBDTtrain/BDToptim/${bdt}
    echo ${bdt}
    echo ${bdt} >> jobs_optim.txt
done
condor_submit sub_optim.jdl
condor_wait ${B2HH_LOG}/newBDTtrain/log/optim.txt


##sorting BDTs from best to worst

( #again limiting the environment sourcing
cd $B2HH_SRC/newBDTtrain
source ${setup_LCG_105}
echo "running the bestBDTSorter -> contains hardcoded BDTs inside"
root -q bestBDTSorter.cpp
#most models are clearly overtrained -> chose 400_4
)
'
######################################################################################################################################
#####################################
## Assign best BDT to all channels ##
#####################################
## mv tuple_merged tuple_merged.bak #should be done once -> avoid losing the original tuples
## mkdir -p ${B2HH_OUT}/Data/tempFinalAssign   #### rm -r ${B2HH_OUT}/Data/tempFinalAssign ##removed after compatibility bit fixing


cd $B2HH_RUN/BDT
#rm jobs_assignFinal.txt
rm jobs_assignFinal_data.txt ##only for b2hh
echo "assigning new BDT"

years="2015 2016 2017s29r2p2 2018"
polarities="Up Down"

channels="b2hh"
for channel in ${channels}; do
    for year in ${years}; do
        for polarity in ${polarities}; do
            echo ${channel} ${year} ${polarity}
            echo ${channel} ${year} ${polarity} >> jobs_assignFinal_data.txt
        done
    done
done

channels="bdkk bdkpi bdpik bdpipi bskk bskpi bspik bspipi lbkp lbpip lbpk lbppi"
for channel in ${channels}; do
    for year in ${years}; do
        for polarity in ${polarities}; do
            echo ${channel} ${year} ${polarity}
            echo ${channel} ${year} ${polarity} >> jobs_assignFinal.txt
        done
    done
done
##improving readability

condor_submit sub_assignFinal_Data.jdl
condor_submit sub_assignFinal.jdl

