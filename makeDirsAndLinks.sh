#!/bin/bash
mkdir -p ${B2HH_STORAGE}
mkdir -p ${B2HH_STORAGE}/out
mkdir -p ${B2HH_STORAGE}/log
ln -s ${B2HH_STORAGE}/out ${B2HH_HOME}/out
ln -s ${B2HH_STORAGE}/log ${B2HH_HOME}/log


ln -s /storage/gpfs_data/local/lhcb/users/dmanuzzi/b2hhNewBDT/out/PID ${B2HH_OUT}/PID
ln -s /storage/gpfs_data/local/lhcb/users/dmanuzzi/b2hhNewBDT/out/Reduce ${B2HH_OUT}/Reduce
ln -s /storage/gpfs_data/local/lhcb/users/dmanuzzi/b2hhNewBDT/out/TimeModels ${B2HH_OUT}/TimeModels
ln -s /storage/gpfs_data/local/lhcb/users/dmanuzzi/b2hhNewBDT/out/MassModels ${B2HH_OUT}/MassModels
ln -s /storage/gpfs_data/local/lhcb/users/dmanuzzi/b2hhNewBDT/out/Tagging ${B2HH_OUT}/Tagging
mkdir -p ${B2HH_OUT}/AccSignal
ln -s /storage/gpfs_data/local/lhcb/users/dmanuzzi/b2hhNewBDT/out/AccSignal/plots ${B2HH_OUT}/AccSignal/plots

