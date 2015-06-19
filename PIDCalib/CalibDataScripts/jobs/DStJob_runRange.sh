#!/bin/sh
source /data/lhcb/sw/scripts/lbsetup-cvmfs.sh
SetupErasmus v8r1

PART_NAME=$1
MAG_POL=$2
STRIP_VER=$3
START_INDEX=$4
END_INDEX=$5

for (( n = $START_INDEX; n <= $END_INDEX; n++ )); 
do
    ###=================================================###
    #  Assign variables dependent on field orientation    #
    if [ $MAG_POL == Up ]
    then
        DATA=/data/lhcb/users/powell/gangadir_calib/workspace/powell/LocalXML/{122,209,246}/*/output/PID_${n}.root
    elif [ $MAG_POL == Down ]
    then
        DATA=/data/lhcb/users/powell/gangadir_calib/workspace/powell/LocalXML/{108,210,245}/*/output/PID_${n}.root
    fi
    ###=================================================###

    MYDATA=$(eval ls ${DATA})
    echo ${MAG_POL}
    echo ${MYDATA}

    OUT_DIR=${DATADISK}/CalibData_2012/Mag${MAG_POL}/$PART_NAME
    echo ${OUT_DIR}

    $CALIBDATASCRIPTSROOT/$CMTCONFIG/DStFit.exe $PART_NAME $MAG_POL $STRIP_VER $n $OUT_DIR $MYDATA
    sleep 3
    $CALIBDATASCRIPTSROOT/$CMTCONFIG/MergeCharges.exe DSt $OUT_DIR $PART_NAME $MAG_POL $STRIP_VER $OUT_DIR $n
    sleep 3

done