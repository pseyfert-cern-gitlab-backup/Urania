#!/bin/sh
source /afs/cern.ch/lhcb/software/releases/LBSCRIPTS/LBSCRIPTS_v7r6/InstallArea/scripts/LHCb.sh
SetupErasmus v9r0

PART_NAME=$1
MAG_POL=$2
STRIP_VER=$3
START_INDEX=$4
END_INDEX=$5
JOB_ID=$6
DATA_YEAR=$7
FILE_SUFFIX=$8

for (( n = $START_INDEX; n <= $END_INDEX; n++ )); 
do
    DATA=/afs/cern.ch/work/j/jotalora/PID_Calib/gangadir/workspace/jotalora/LocalXML/${JOB_ID}/*/output/PID_${n}_${FILE_SUFFIX}.root

    MYDATA=$(eval ls ${DATA})
    echo ${MAG_POL}
    #echo ${MYDATA}

    OUT_DIR=/afs/cern.ch/work/j/jotalora/PID_Calib/CalibData_${DATA_YEAR}/Mag${MAG_POL}/$PART_NAME
    echo ${OUT_DIR}

    $CALIBDATASCRIPTSROOT/$CMTCONFIG/JpsiFit.exe $MAG_POL $STRIP_VER $n $OUT_DIR $MYDATA
    sleep 3
    $CALIBDATASCRIPTSROOT/$CMTCONFIG/MergeCharges.exe Jpsi $OUT_DIR $PART_NAME $MAG_POL $STRIP_VER $OUT_DIR $n 
    sleep 3

done
