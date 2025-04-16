#!/bin/bash
hostname
cd ${B2HH_SRC}/sPlotFinal
#source ${setup_LCG_new}


${lbRunDaVinciStd} root -l -b -q addDoubleNumbers.cpp++'("../../out/Reduce/b2hh_KK_0.1_201516_Tot.root", "../../out/Reduce/b2hh_KK_0.1_201516_Tot_tmp.root")' &> logAddDoubleNumbers201516
mv ../../out/Reduce/b2hh_KK_0.1_201516_Tot.root ../../out/Reduce/b2hh_KK_0.1_201516_Tot_bak.root
mv ../../out/Reduce/b2hh_KK_0.1_201516_Tot_tmp.root ../../out/Reduce/b2hh_KK_0.1_201516_Tot.root
echo "201516 done"

${lbRunDaVinciStd} root -l -b -q addDoubleNumbers.cpp+'("../../out/Reduce/b2hh_KK_0.1_2017s29r2p2_Tot.root", "../../out/Reduce/b2hh_KK_0.1_2017s29r2p2_Tot_tmp.root")' &> logAddDoubleNumbers2017s29r2p2
mv ../../out/Reduce/b2hh_KK_0.1_2017s29r2p2_Tot.root ../../out/Reduce/b2hh_KK_0.1_2017s29r2p2_Tot_bak.root
mv ../../out/Reduce/b2hh_KK_0.1_2017s29r2p2_Tot_tmp.root ../../out/Reduce/b2hh_KK_0.1_2017s29r2p2_Tot.root
echo "2017 done"

${lbRunDaVinciStd} root -l -b -q addDoubleNumbers.cpp+'("../../out/Reduce/b2hh_KK_0.1_2018_Tot.root", "../../out/Reduce/b2hh_KK_0.1_2018_Tot_tmp.root")' &> logAddDoubleNumbers2018
mv ../../out/Reduce/b2hh_KK_0.1_2018_Tot.root ../../out/Reduce/b2hh_KK_0.1_2018_Tot_bak.root
mv ../../out/Reduce/b2hh_KK_0.1_2018_Tot_tmp.root ../../out/Reduce/b2hh_KK_0.1_2018_Tot.root
echo "2018 done"
