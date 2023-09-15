#!/bin/bash
cd ${B2HH_SRC}/AccSignal
source ${setup_LCG_std}

command="${B2HH_SRC}/AccSignal/makeRatio -C $1 -b $2 -y $3 -m $4 -n $5 -f $6"

if [[ $7 == '1' ]]; then
    command+=" -D"
fi

if [[ $8 == '1' ]]; then    
    command+=" -T"
fi

if [[ $9 == 1 ]]; then
    command+=" -W"
fi
if [[ ${10} == 1 ]]; then
    command+=" -V"
fi
echo ${command}
${command}
${command} -MC


#         ${B2HH_SRC}/AccSignal/makeRatio -C $1 -b $2 -y $3 -m $4 -n $5 -f $6 -D -T
#     else
#         ${B2HH_SRC}/AccSignal/makeRatio -C $1 -b $2 -y $3 -m $4 -n $5 -f $6 -D
#     fi
# else 
#     if [[ $8 == '1' ]]; then    
#         ${B2HH_SRC}/AccSignal/makeRatio -C $1 -b $2 -y $3 -m $4 -n $5 -f $6 -T
#         ${B2HH_SRC}/AccSignal/makeRatio -C $1 -b $2 -y $3 -m $4 -n $5 -f $6 -T -MC
#     else
#         ${B2HH_SRC}/AccSignal/makeRatio -C $1 -b $2 -y $3 -m $4 -n $5 -f $6 
#         ${B2HH_SRC}/AccSignal/makeRatio -C $1 -b $2 -y $3 -m $4 -n $5 -f $6 -MC
#     fi
# fi
