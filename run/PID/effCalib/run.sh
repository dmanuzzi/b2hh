#!/bin/bash
hostname
cd ${B2HH_RUN}/PID/effCalib
echo `pwd`
source ${setup_LCG_new}
${B2HH_SRC}/PID/effCalib/eff -x "$1" -y "$2" -z "$3" -t "$4" -m "$5" -Y "$6" -f "$7" -c "$8" -r "$9"
