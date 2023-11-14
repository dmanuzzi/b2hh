#!/bin/bash

mkdir -p ${B2HH_LOG}/AccSignal/out
mkdir -p ${B2HH_LOG}/AccSignal/err
mkdir -p ${B2HH_LOG}/AccSignal/log

mkdir -p ${B2HH_OUT}/AccSignal/bkgSubtractedSamples
mkdir -p ${B2HH_OUT}/AccSignal/kineWeight
mkdir -p ${B2HH_OUT}/AccSignal/selectedMC
mkdir -p ${B2HH_OUT}/AccSignal/params
### REMEMBER! cp -r /home/LHCB-T3/dmanuzzi/B2HH/AccSignal.new/params ${B2HH_OUT}/AccSignal/params
mkdir -p ${B2HH_OUT}/AccSignal/plots
mkdir -p ${B2HH_OUT}/AccSignal/acceptances

source ${setup_LCG_std}
cd ${B2HH_SRC}/AccSignal
root -l -b -q RooTimeAccPdf.cxx+
touch ./*.C
make 

cd ${B2HH_RUN}/AccSignal
# cuts_bdt="KK_0.04 PIPI_0.12"
# years="201516 2017s29r2p2 2018"
# magnets="Tot"
years=${1//'__'/' '}
magnets=${2//'__'/' '}
cuts_bdt=${3//'__'/' '}
cuts_pid=${4//'__'/' '}
PIDkpi=''
PIDpik=''
PIDpipi=''
PIDkk=''
for cut_pid in $cuts_pid; do
    if    [[ $cut_pid == *kpi* ]]; then PIDkpi=$cut_pid; continue; 
    elif  [[ $cut_pid == *pik* ]]; then PIDpik=$cut_pid; continue;
    elif  [[ $cut_pid == *pipi* ]]; then PIDpipi=$cut_pid; continue;
    elif  [[ $cut_pid == *kk* ]]; then PIDkk=$cut_pid; continue;
    fi
done

doSelMC=0
doKineWeight=0
doSubtractBkg=0
doFitAcc=0
doMakeRatio=1

## sel MC
if [[ $doSelMC == 1 ]]; then
    rm -f jobs_selMC.txt
    rm -f ${B2HH_LOG}/AccSignal/log/AccSignal_selMC.txt
    # selMC_cases="bdkpi_${PIDkpi} bdkpi_${PIDpipi} bdkpi_${PIDkk}"
    # selMC_cases+=" bdpik_${PIDpik} bdpik_${PIDpipi} bdpik_${PIDkk}"
    # selMC_cases+=" bskpi_${PIDkpi} bspik_${PIDpik}"
    # selMC_cases+=" bdpipi_${PIDpipi} bdpipi_${PIDkpi}"
    # selMC_cases+=" bspipi_${PIDpipi} bspipi_${PIDkpi}"
    # selMC_cases+=" bskk_${PIDkk} bskk_${PIDkpi}"
    # selMC_cases+=" bdkk_${PIDkk}"
    # selMC_cases+=" lbpk_${PIDkk} lbkp_${PIDkk}"
    # selMC_cases+=" lbppi_${PIDkpi} lbpip_${PIDpik}"

    selMC_cases+=" bskk_${PIDkk}"
    for cut_bdt in ${cuts_bdt}; do  
        for year in ${years}; do 
            for mag in ${magnets}; do
                for selMC_case in ${selMC_cases}; do
                    echo ${cut_bdt//"_"/" "} ${year} ${mag} ${selMC_case//"_"/" "}
                    echo ${cut_bdt//"_"/" "} ${year} ${mag} ${selMC_case//"_"/" "} >> jobs_selMC.txt            
                done
            done
        done
    done
    condor_submit submit_selMC.jdl
    condor_wait ${B2HH_LOG}/AccSignal/log/AccSignal_selMC.txt
fi
#kineWeight
if [[ $doKineWeight == 1 ]]; then
    rm -f jobs_kineWeight.txt
    rm -f ${B2HH_LOG}/AccSignal/log/AccSignal_kineWeight.txt

    # kineWeight_cases='bdkpi_kpi_bd_bdpik_pik'
    # kineWeight_cases+=' bdkpi_pipi_bd_bdpik_pipi'
    # kineWeight_cases+=' bdkpi_kk_bd_bdpik_bd'
    # kineWeight_cases+=' bdpipi_pipi_bd_0_0'
    # kineWeight_cases+=' bdpipi_kpi_bd_0_0'
    # kineWeight_cases+=' bdkk_kk_bd_0_0'
    # kineWeight_cases+=' bskk_kk_bs_0_0'
    # kineWeight_cases+=' bskk_kpi_bs_0_0'
    # kineWeight_cases+=' bskpi_kpi_bs_bspik_pik'
    # kineWeight_cases+=' bspipi_pipi_bs_0_0'
    # kineWeight_cases+=' lbpk_kk_bs_lbkp_kk'
    # kineWeight_cases+=' lbppi_kpi_bs_lbpip_pik'
    kineWeight_cases+=' bskk_kk_bs_0_0'

    for cut_bdt in ${cuts_bdt}; do  
        for year in ${years}; do 
            for mag in ${magnets}; do
                for kineWeight_case in ${kineWeight_cases}; do
                    echo ${cut_bdt//"_"/" "} ${year} ${mag} ${kineWeight_case//"_"/" "}
                    echo ${cut_bdt//"_"/" "} ${year} ${mag} ${kineWeight_case//"_"/" "} >> jobs_kineWeight.txt            
                done
            done
        done
    done
    condor_submit submit_kineWeight.jdl
    condor_wait ${B2HH_LOG}/AccSignal/log/AccSignal_kineWeight.txt
fi


# subtractBkg
if [[ $doSubtractBkg == 1 ]]; then
    rm -f jobs_subtractBkg.txt
    rm -f ${B2HH_LOG}/AccSignal/log/AccSignal_subtractBkg.txt

    for cut_bdt in ${cuts_bdt}; do  
        for year in ${years}; do 
            for mag in ${magnets}; do
                echo ${cut_bdt//"_"/" "} ${year} ${mag}
                echo ${cut_bdt//"_"/" "} ${year} ${mag} >> jobs_subtractBkg.txt            
            done
        done
    done
    condor_submit submit_subtractBkg.jdl
    condor_wait ${B2HH_LOG}/AccSignal/log/AccSignal_subtractBkg.txt
fi 


if [[ $doFitAcc == 1 ]]; then
    # #fitAccData
    rm -f jobs_fitAcc.txt
    rm -f ${B2HH_LOG}/AccSignal/log/AccSignal_fitAcc.txt
    # fitAccData_cases='bdkpi_kpi bdpik_pik'
    # for cut_bdt in ${cuts_bdt}; do  
    #     for year in ${years}; do 
    #         for mag in ${magnets}; do
    #             for n in ${fitAccData_cases}; do
    #                 for tag in '0' '1'; do
    #                     echo ${cut_bdt//"_"/" "} ${year} ${mag} ${n//"_"/" "} '1' ${tag} 
    #                     echo ${cut_bdt//"_"/" "} ${year} ${mag} ${n//"_"/" "} '1' ${tag} >> jobs_fitAcc.txt            
    #                 done
    #             done 
    #         done
    #     done
    # done

    ##fitAccMC
    #fitAccMC_cases='bdkpi_kpi bdkpi_pipi bdkpi_kk bdpipi_pipi bdpipi_kpi bdkk_kk bskk_kk bskk_kpi bskpi_kpi bspipi_pipi lbpk_kk'
    fitAccMC_cases='bskk_kk'
    for cut_bdt in ${cuts_bdt}; do  
        for year in ${years}; do 
            for mag in ${magnets}; do
                for n in ${fitAccMC_cases}; do
                    for tag in '0' '1'; do
                        for weight in '0' '1'; do
                            for trueTau in '0' '1'; do
                                echo ${cut_bdt//"_"/" "} ${year} ${mag} ${n//"_"/" "} '0' ${tag} ${weight} ${trueTau} 
                                echo ${cut_bdt//"_"/" "} ${year} ${mag} ${n//"_"/" "} '0' ${tag} ${weight} ${trueTau} >> jobs_fitAcc.txt            
                            done
                        done
                    done
                done 
            done
        done
    done
    condor_submit submit_fitAcc.jdl
    condor_wait ${B2HH_LOG}/AccSignal/log/AccSignal_fitAcc.txt
fi


if [[ $doMakeRatio == 1 ]]; then
    rm -f jobs_makeRatio.txt
    rm -f ${B2HH_LOG}/AccSignal/log/AccSignal_makeRatio.txt
    
    #makeRatioData  
    makeRatioData_cases='bdkpi_kpi bdpik_pik'
    for cut_bdt in ${cuts_bdt}; do  
        for year in ${years}; do 
            for mag in ${magnets}; do
                for n in ${makeRatioData_cases}; do
                    for tag in '0' '1'; do
                        echo ${cut_bdt//"_"/" "} ${year} ${mag} ${n//"_"/" "} '1' ${tag} 
                        echo ${cut_bdt//"_"/" "} ${year} ${mag} ${n//"_"/" "} '1' ${tag} >> jobs_makeRatio.txt            
                    done
                done 
            done
        done
    done

    #makeRatioMC
    makeRatioMC_cases='bskk_kk'
    for cut_bdt in ${cuts_bdt}; do  
        for year in ${years}; do 
            for mag in ${magnets}; do
                for n in ${makeRatioMC_cases}; do
                    for tag in '0' '1'; do
                        for weight in '0' '1'; do
                            for trueTau in '0' '1'; do        
                                echo ${cut_bdt//"_"/" "} ${year} ${mag} ${n//"_"/" "} '0' ${tag} ${weight} ${trueTau} 
                                echo ${cut_bdt//"_"/" "} ${year} ${mag} ${n//"_"/" "} '0' ${tag} ${weight} ${trueTau} >> jobs_makeRatio.txt            
                            done
                        done
                    done
                done 
            done
        done
    done
    condor_submit submit_makeRatio.jdl
    condor_wait ${B2HH_LOG}/AccSignal/log/AccSignal_makeRatio.txt
fi
