#!/bin/bash
cd ${B2HH_SRC}/AccSignal
source ${setup_LCG_std}

command="${B2HH_SRC}/AccSignal/fitAcc -C $1 -b $2 -y $3 -m $4 -n $5 -f $6 -F"


if [[ $7 == '1' ]]; then
    command+=" -D"
fi
if [[ $8 == '1' ]]; then 
    command+=" -T" 
fi   
if [[ $9 == '1' ]]; then 
    command+=" -W" 
fi   
if [[ ${10} == '1' ]]; then 
    command+=" -V" 
fi   

echo $command
${command}


#         ${B2HH_SRC}/AccSignal/fitAcc -C $1 -b $2 -y $3 -m $4 -n $5 -f $6 -F -D -T 
#     else
#         ${B2HH_SRC}/AccSignal/fitAcc -C $1 -b $2 -y $3 -m $4 -n $5 -f $6 -F -D
#     fi
# else 
#     if [[ $8 == '1' ]]; then    
#         ${B2HH_SRC}/AccSignal/fitAcc -C $1 -b $2 -y $3 -m $4 -n $5 -f $6 -F -T
#     else
#         ${B2HH_SRC}/AccSignal/fitAcc -C $1 -b $2 -y $3 -m $4 -n $5 -f $6 -F
#     fi
# fi
