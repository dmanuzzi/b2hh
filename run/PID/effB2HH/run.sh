#!/bin/bash
hostname
#source ${setup_LCG_new}
cd ${B2HH_OUT}/PID/effB2HH
${lbRunDaVinciStd} ${B2HH_SRC}/PID/effB2HH/effB2HH -x "binP_$1" -y "binETA_$2" -z "binPHI_$3" -t "binSPD_$4"\
                                -f "$5" -c "$6" -m "$7" -Y "$8" \
                                -n "$9" -C "$9" -b "${10}" "${11}"
