#!/bin/sh
if [ $# -ne 8 ]; then
  echo "Usage: `basename $0` <gangaJobsDir> <uraniaVersion> <platform> <magPol> <stripVersion> <startIndex> <endIndex> <fileSuffix>"
  exit 1
fi

GANGAJOBSDIR=$1
URANIAVERSION=$2
PLATFORM=$3
MAG_POL=$4
STRIP_VER=$5
START_INDEX=$6
END_INDEX=$7
FILESUFFIX=$8

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
    echo "Magnet polarity: ${MAG_POL}"
    echo "Stripping version: ${STRIP_VER}"
    echo "File suffix: ${FILESUFFIX}"
    echo "Data: ${MYDATA}"
	echo "Verbose: ${VERBOSE}"

    OUT_DIR=$CALIBDATADIR/CalibData_${CALIBDATATYPE}/Mag${MAG_POL}/Mu
    echo "Output directory: ${OUT_DIR}"
    mkdir -p ${OUT_DIR}

    CALIBAPPDIR=$CALIBDATASCRIPTSROOT/$CMTCONFIG

    # perform the J/psi mass fit
    echo "Performing J/psi mass fit for index $n" 
    $CALIBAPPDIR/JpsiFit.exe $MAG_POL $STRIP_VER $CALIBDATATYPE $n $OUT_DIR $VERBOSE $MYDATA
    sleep 3

    # merge the h+ and h- samples
    echo "Merging mu+ and mu- samples for index $n" 
    $CALIBAPPDIR/MergeCharges.exe Jpsi $OUT_DIR Mu $MAG_POL $STRIP_VER $OUT_DIR $n 
    sleep 3

done
