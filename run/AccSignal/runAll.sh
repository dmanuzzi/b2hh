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

# rm -f jobs.txt
# for cut_bdt in ${cuts_bdt}; do  
#     for year in ${years}; do 
#         for mag in ${magnets}; do
#             echo ${cut_bdt//"_"/" "} ${year} ${mag}
#             echo ${cut_bdt//"_"/" "} ${year} ${mag} >> jobs.txt            
#         done
#     done
# done
# condor_submit submit.jdl

## sel MC
# rm -f jobs_selMC.txt
# rm -f ${B2HH_LOG}/AccSignal/log/AccSignal_selMC.txt
# selMC_cases='bdkpi_kpi_5.-2.-5.3 bdkpi_pipi_-2.3.-2.3 bdkpi_kk_2.-2.2.-2'
# selMC_cases+=' bdpik_pik_-5.3.5.-2 bdpik_pipi_-2.3.-2.3 bdpik_kk_2.-2.2.-2'
# selMC_cases+=' bskpi_kpi_5.-2.-5.3 bspik_pik_-5.3.5.-2'
# selMC_cases+=' bdpipi_pipi_-2.3.-2.3 bdpipi_kpi_5.-2.-5.3'
# selMC_cases+=' bspipi_pipi_-2.3.-2.3 bspipi_kpi_5.-2.-5.3'
# selMC_cases+=' bskk_kk_2.-2.2.-2 bskk_kpi_5.-2.-5.3'
# selMC_cases+=' bdkk_kk_2.-2.2.-2'
# selMC_cases+=' lbpk_kk_2.-2.2.-2 lbkp_kk_2.-2.2.-2'
# selMC_cases+=' lbppi_kpi_5.-2.-5.3 lbpip_pik_-5.3.5.-2'
# for cut_bdt in ${cuts_bdt}; do  
#     for year in ${years}; do 
#         for mag in ${magnets}; do
#             for selMC_case in ${selMC_cases}; do
#                 echo ${cut_bdt//"_"/" "} ${year} ${mag} ${selMC_case//"_"/" "}
#                 echo ${cut_bdt//"_"/" "} ${year} ${mag} ${selMC_case//"_"/" "} >> jobs_selMC.txt            
#             done
#         done
#     done
# done
# condor_submit submit_selMC.jdl
# condor_wait ${B2HH_LOG}/AccSignal/log/AccSignal_selMC.txt

# ##kineWeight
# rm -f jobs_kineWeight.txt
# rm -f ${B2HH_LOG}/AccSignal/log/AccSignal_kineWeight.txt

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
# for cut_bdt in ${cuts_bdt}; do  
#     for year in ${years}; do 
#         for mag in ${magnets}; do
#             for kineWeight_case in ${kineWeight_cases}; do
#                 echo ${cut_bdt//"_"/" "} ${year} ${mag} ${kineWeight_case//"_"/" "}
#                 echo ${cut_bdt//"_"/" "} ${year} ${mag} ${kineWeight_case//"_"/" "} >> jobs_kineWeight.txt            
#             done
#         done
#     done
# done
# condor_submit submit_kineWeight.jdl
# condor_wait ${B2HH_LOG}/AccSignal/log/AccSignal_kineWeight.txt

# ##subtractBkg
# rm -f jobs_subtractBkg.txt
# rm -f ${B2HH_LOG}/AccSignal/log/AccSignal_subtractBkg.txt

# for cut_bdt in ${cuts_bdt}; do  
#     for year in ${years}; do 
#         for mag in ${magnets}; do
#             echo ${cut_bdt//"_"/" "} ${year} ${mag}
#             echo ${cut_bdt//"_"/" "} ${year} ${mag} >> jobs_subtractBkg.txt            
#         done
#     done
# done
# condor_submit submit_subtractBkg.jdl
# condor_wait ${B2HH_LOG}/AccSignal/log/AccSignal_subtractBkg.txt

#fitAccData
rm -f jobs_fitAcc.txt
rm -f ${B2HH_LOG}/AccSignal/log/AccSignal_fitAcc.txt
fitAccData_cases='bdkpi_kpi bdpik_pik'
for cut_bdt in ${cuts_bdt}; do  
    for year in ${years}; do 
        for mag in ${magnets}; do
            for n in ${fitAccData_cases}; do
                for tag in '0' '1'; do
                    echo ${cut_bdt//"_"/" "} ${year} ${mag} ${n//"_"/" "} '1' ${tag} 
                    echo ${cut_bdt//"_"/" "} ${year} ${mag} ${n//"_"/" "} '1' ${tag} >> jobs_fitAcc.txt            
                done
            done 
        done
    done
done

##fitAccMC
fitAccMC_cases='bdkpi_kpi bdkpi_pipi bdkpi_kk bdpipi_pipi bdpipi_kpi bdkk_kk bskk_kk bskk_kpi bskpi_kpi bspipi_pipi lbpk_kk'
for cut_bdt in ${cuts_bdt}; do  
    for year in ${years}; do 
        for mag in ${magnets}; do
            for n in ${fitAccMC_cases}; do
                for tag in '0' '1'; do
                    echo ${cut_bdt//"_"/" "} ${year} ${mag} ${n//"_"/" "} '0' ${tag} 
                    echo ${cut_bdt//"_"/" "} ${year} ${mag} ${n//"_"/" "} '0' ${tag} >> jobs_fitAcc.txt            
                done
            done 
        done
    done
done
condor_submit submit_fitAcc.jdl
condor_wait ${B2HH_LOG}/AccSignal/log/AccSignal_fitAcc.txt

##makeRatioData
rm -f jobs_makeRatio.txt
rm -f ${B2HH_LOG}/AccSignal/log/AccSignal_makeRatio.txt
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

##makeRatioMC
makeRatioMC_cases='bdkpi_kpi bdkpi_pipi bdkpi_kk bdpipi_pipi bdpipi_kpi bdkk_kk bskk_kk bskk_kpi bskpi_kpi bspipi_pipi lbpk_kk'
for cut_bdt in ${cuts_bdt}; do  
    for year in ${years}; do 
        for mag in ${magnets}; do
            for n in ${makeRatioMC_cases}; do
                for tag in '0' '1'; do
                    echo ${cut_bdt//"_"/" "} ${year} ${mag} ${n//"_"/" "} '0' ${tag} 
                    echo ${cut_bdt//"_"/" "} ${year} ${mag} ${n//"_"/" "} '0' ${tag} >> jobs_makeRatio.txt            
                done
            done 
        done
    done
done
condor_submit submit_makeRatio.jdl
condor_wait ${B2HH_LOG}/AccSignal/log/AccSignal_makeRatio.txt
