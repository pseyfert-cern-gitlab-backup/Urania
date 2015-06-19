#!/bin/sh
if [ $# -ne 9 ]; then
  echo "Usage: `basename $0` <gangaJobsDir> <uraniaVersion> <platform> <trackName> <magPol> <stripVersion> <startIndex> <endIndex> <fileSuffix>"
  exit 1
fi

GANGAJOBSDIR=$1
URANIAVERSION=$2
PLATFORM=$3
PART_NAME=$4
MAG_POL=$5
STRIP_VER=$6
START_INDEX=$7
END_INDEX=$8
FILESUFFIX=$9

. /data/lhcb/sw/scripts/lbsetup-cvmfs.sh
if [[ "$PLATFORM" != "" && "$PLATFORM" != "$CMTCONFIG" ]]; then
  . LbLogin.sh -c $PLATFORM
fi
SetupUrania $URANIAVERSION

# source the file that specifies the input ganga job IDs,
# datatype and ganga directory
FNAME_CONF=$CALIBDATASCRIPTSROOT/jobs/Stripping${STRIP_VER}/configureGangaJobs.sh
if [ -f $FNAME_CONF ]; then
    . $FNAME_CONF
else
    echo "Failed to find config file $FNAME_CONF. Ensure that all script arguments are correct"
    exit 1
fi

# disable printout of verbose information
VERBOSE=0

for (( n = $START_INDEX; n <= $END_INDEX; n++ )); 
do
    ###=================================================###
    #  Assign variables dependent on field orientation    #
    if [ $MAG_POL == Up ]
    then
	DATA=${GANGAJOBSDIR}/${CALIBDATA_JIDS_UP}/*/output/PID_${n}_${FILESUFFIX}.root
    elif [ $MAG_POL == Down ]
    then
        DATA=${GANGAJOBSDIR}/${CALIBDATA_JIDS_DOWN}/*/output/PID_${n}_${FILESUFFIX}.root
    else
        echo "Invalid magnet polarity. Expected 'Up' or 'Down', got $MAG_POL"
        exit 1  
    fi
    ###=================================================###

    MYDATA=$(eval ls ${DATA})
    echo "Particle name: ${PART_NAME}"
    echo "Magnet polarity: ${MAG_POL}"
    echo "Stripping version: ${STRIP_VER}"
    echo "File suffix: ${FILESUFFIX}"
    echo "Data: ${MYDATA}"
    echo "Verbose: ${VERBOSE}"

    OUT_DIR=/data/lhcb/users/hunt/CalibData_${CALIBDATATYPE}/Mag${MAG_POL}/$PART_NAME
    echo "Output directory: ${OUT_DIR}"
    mkdir -p ${OUT_DIR}

    CALIBAPPDIR=$CALIBDATASCRIPTSROOT/$CMTCONFIG

    # perform the Lam0 mass fits
    echo "Performing Lam0 mass fits for index $n" 
    $CALIBAPPDIR/Lam0Fit.exe $PART_NAME $MAG_POL $STRIP_VER $CALIBDATATYPE $n $OUT_DIR $VERBOSE $MYDATA
    sleep 2

    if [ $PART_NAME == P ]; then

        # merge the LowP and HiP proton samples
	echo "Merging proton lines for index $n" 
	$CALIBAPPDIR/MergeProtonLines.exe $OUT_DIR $PART_NAME Plus $MAG_POL $STRIP_VER $OUT_DIR $n
	sleep 2

        # merge the LowP and HiP antiproton samples
	echo "Merging antiproton lines for index $n" 
	$CALIBAPPDIR/MergeProtonLines.exe $OUT_DIR $PART_NAME Minus $MAG_POL $STRIP_VER $OUT_DIR $n
	sleep 2
    fi

    # merge the h+ and h- samples
    echo "Merging h+ and h- samples for index $n" 
    $CALIBAPPDIR/MergeCharges.exe Lam0 $OUT_DIR $PART_NAME $MAG_POL $STRIP_VER $OUT_DIR $n 
    sleep 2

done
