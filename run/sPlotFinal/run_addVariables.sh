#!/bin/bash
hostname
cd ${B2HH_SRC}/sPlotFinal
source ${setup_LCG_new}


#root -l -b -q addVariables.cpp+'("../../out/sPlotFinal/KK_0.1_201516_Tot/b2hh_sWeight.root", {"../../out/Data/tuple_merged/b2hh_2015_Up.root", "../../out/Data/tuple_merged/b2hh_2015_Down.root", "../../out/Data/tuple_merged/b2hh_2016_Up.root", "../../out/Data/tuple_merged/b2hh_2016_Down.root"}, "../../out/Reduce/b2hh_KK_0.1_201516_Tot_moreVaraibles.root")' &> logAddVariable201516 &

root -l -b -q addVariables.cpp+'("../../out/sPlotFinal/KK_0.1_2017s29r2p2_Tot/b2hh_sWeight.root", {"../../out/Data/tuple_merged/b2hh_2017s29r2p2_Up.root", "../../out/Data/tuple_merged/b2hh_2017s29r2p2_Down.root"}, "../../out/Reduce/b2hh_KK_0.1_2017s29r2p2_Tot_moreVaraibles.root")' &> logAddVariable2017 &

root -l -b -q addVariables.cpp+'("../../out/sPlotFinal/KK_0.1_2018_Tot/b2hh_sWeight.root", {"../../out/Data/tuple_merged/b2hh_2018_Up.root", "../../out/Data/tuple_merged/b2hh_2018_Down.root"}, "../../out/Reduce/b2hh_KK_0.1_2018_Tot_moreVaraibles.root")' &> logAddVariable2018 &
