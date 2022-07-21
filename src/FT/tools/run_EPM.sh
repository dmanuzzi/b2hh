#!/bin/bash

$VO_LHCB_SW_DIR/lib/LbLogin.sh
mode=$1
y=$2
vTag=$3
cutTag=$4
cut=$5
echo $mode $y $vTag $cutTag $cut
CMTCONFIG=x86_64-slc6-gcc8-opt
source /cvmfs/sft.cern.ch/lcg/views/LCG_97/$CMTCONFIG/setup.sh
echo `pwd`
runEPM=/home/LHCB-T3/dmanuzzi/B2HH/FT/EspressoPerformanceMonitor/build/bin/SimpleEvaluator

cd ../"$mode"_calib
outDir=EPMout_"$y"_"$vTag""$cutTag"
rm -rf $outDir
mkdir $outDir
cd $outDir
optfile=./EPM_options_"$mode"_"$y"_"$vTag""$cutTag".py
cp -f ../../tools/EPM_options_template_"$vTag".py $optfile

if [[ "$y" == "All" ]]; then
    echo ""                    >> $optfile
    echo "NumFiles = 8"        >> $optfile
    k=0
    for  Y in 2015 2016 2017 2018; do
	nfin1='"/home/LHCB-T3/dmanuzzi/B2HH/data/'$mode'/'$Y'/MagUp/B2DX_'$Y'_Up_'$mode'_sWeight_wPT.root"'
	nfin2='"/home/LHCB-T3/dmanuzzi/B2HH/data/'$mode'/'$Y'/MagDw/B2DX_'$Y'_Dw_'$mode'_sWeight_wPT.root"' 
	k=$((k+1))
	echo "RootFile_$k = $nfin1" >> $optfile
	k=$((k+1))
	echo "RootFile_$k = $nfin2" >> $optfile
    done
elif [[ "$y" == "2015and2016" ]]; then
    echo ""                    >> $optfile
    echo "NumFiles = 4"        >> $optfile
    k=0
    for  Y in 2015 2016; do
	nfin1='"/home/LHCB-T3/dmanuzzi/B2HH/data/'$mode'/'$Y'/MagUp/B2DX_'$Y'_Up_'$mode'_sWeight_wPT.root"'
	nfin2='"/home/LHCB-T3/dmanuzzi/B2HH/data/'$mode'/'$Y'/MagDw/B2DX_'$Y'_Dw_'$mode'_sWeight_wPT.root"' 
	k=$((k+1))
	echo "RootFile_$k = $nfin1" >> $optfile
	k=$((k+1))
	echo "RootFile_$k = $nfin2" >> $optfile
    done
else
    nfin1='"/home/LHCB-T3/dmanuzzi/B2HH/data/'$mode'/'$y'/MagUp/B2DX_'$y'_Up_'$mode'_sWeight_wPT.root"' 
    nfin2='"/home/LHCB-T3/dmanuzzi/B2HH/data/'$mode'/'$y'/MagDw/B2DX_'$y'_Dw_'$mode'_sWeight_wPT.root"' 
    echo ""                    >> $optfile
    echo "NumFiles = 2"        >> $optfile
    echo "RootFile_1 = $nfin1" >> $optfile
    echo "RootFile_2 = $nfin2" >> $optfile
fi


if [[ "$mode" == "Bd2Dpi" ]]; then
    echo 'CalibrationMode = "Bd"' >> $optfile
elif [[ "$mode" == "Bs2Dspi" ]]; then
    echo 'CalibrationMode = "Bs"' >> $optfile
else
    echo 'ERROR: mode unknown!!!'
fi

#echo 'Selection = "eventNumber % 2 == 0"'     >> $optfile
echo $cut >> $optfile

$runEPM $optfile

cp EspressoCalibrations.py MyCalibrations.py
cp EspressoCalibrations.py ../results/"$outDir"__EspressoCalibrations.py
cp EspressoCalibratedPerformanceTable.tex ../results/"$outDir"__EspressoCalibratedPerformanceTable.tex
