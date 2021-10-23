#!/bin/bash
hostname
cd ${B2HH_OUT}/MassModels/CrossFeed
echo $ROOTSYS
${lbRunDaVinciOld} ${B2HH_SRC}/MassModels/CrossFeed/create -d $1 -b $2 -f $3 -c $4 -y $5 -m $6 -F $7

