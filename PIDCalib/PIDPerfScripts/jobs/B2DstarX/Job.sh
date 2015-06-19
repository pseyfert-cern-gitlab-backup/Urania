#!/bin/sh
source /data/lhcb/sw/scripts/lbsetup.sh
SetupErasmus v6r1

for (( n= 0; n < $3; n++ )); 
do
    echo $1 $2 $3 $4" : " $n
    $PIDPERFSCRIPTSROOT/$CMTCONFIG/B2DstarX_EvtData.exe $1 $2 $n $4
    sleep 3
done

