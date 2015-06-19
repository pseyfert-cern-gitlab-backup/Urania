#!/bin/sh
source /data/lhcb/sw/scripts/lbsetup.sh
SetupErasmus v6r0

for (( n= 0; n < $4; n++ )); 
do
    echo $1 $2 $3 $4" : " $n
    $PIDPERFSCRIPTSROOT/$CMTCONFIG/B2DX_EvtData.exe $1 $2 $3 $n
    sleep 3
done

