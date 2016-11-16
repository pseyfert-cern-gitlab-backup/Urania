#!/bin/bash
if [ $# -lt 10 ]; then
  echo "Usage: `basename $0` <gangaJobsDir> <uraniaVersion> <platform> <trackName> <magPol> <stripVersion> <index> <fileSuffix> <verbose> <exitOnBadFit> (<subIDsToProcess=\"*\">)"
  echo "N.B The optional argument <subIDsToProcess> can be used to process a limited number of subjobs (i.e. when running tests)."
  echo "It should be a bash-friendly list of subjob IDs, e.g. {0,1,2,3}."
  echo "If not set, the script will default to processing all subjobs (\"*\")."
  exit 1
fi

GANGAJOBSDIR=$1
shift
URANIAVERSION=$1
shift
PLATFORM=$1
shift
PART_NAME=$1
shift
MAG_POL=$1
shift
STRIP_VER=$1
shift
INDEX=$1
shift
FILESUFFIX=$1
shift
PRINTENTRIES=$1
shift
EXITONBADFIT=$1
shift
SUBIDS="$1"
if [ -z "$SUBIDS" ]; then
    SUBIDS="*"
fi

echo "Input directory: ${GANGAJOBSDIR}"
echo "Urania version: ${URANIAVERSION}"
echo "Platform: ${PLATFORM}"
echo "Particle name: ${PART_NAME}"
echo "Magnet polarity: ${MAG_POL}"
echo "Stripping version: ${STRIP_VER}"
echo "Index: ${INDEX}"
echo "File suffix: ${FILESUFFIX}"
echo "Print entries? ${PRINTENTRIES}"
echo "Exit on bad fit quality? ${EXITONBADFIT}"
echo "Subjobs to process: ${SUBIDS}"

. /data/lhcb/sw/scripts/lbsetup-cvmfs-osagnostic.sh
EXITCODE=$?
if [ $EXITCODE -ne 0 ]; then
  exit $EXITCODE
fi
if [[ "$PLATFORM" != "" && "$PLATFORM" != "$CMTCONFIG" ]]; then
  . LbLogin.sh -c $PLATFORM
  EXITCODE=$?
  if [ $EXITCODE -ne 0 ]; then
    exit $EXITCODE
  fi
fi
. SetupProject.sh Urania $URANIAVERSION
EXITCODE=$?
if [ $EXITCODE -ne 0 ]; then
  exit $EXITCODE
fi

# source the file that specifies the input ganga job IDs,
# datatype and ganga directory
FNAME_CONF=$CALIBDATASCRIPTSROOT/jobs/Stripping${STRIP_VER}/configureGangaJobs.sh
if [ -f $FNAME_CONF ]; then
    . $FNAME_CONF
else
    echo "Failed to find config file $FNAME_CONF. Ensure that all script arguments are correct"
    exit 1
fi

###=================================================###
#  Assign variables dependent on field orientation    #
if [ $MAG_POL == Up ]
then
    DATA=${GANGAJOBSDIR}/${CALIBDATA_JIDS_UP}/${SUBIDS}/output/PID_${INDEX}_${FILESUFFIX}.root
elif [ $MAG_POL == Down ]
then
    DATA=${GANGAJOBSDIR}/${CALIBDATA_JIDS_DOWN}/${SUBIDS}/output/PID_${INDEX}_${FILESUFFIX}.root
else
    echo "Invalid magnet polarity. Expected 'Up' or 'Down', got $MAG_POL"
    exit 1  
fi
###=================================================###

MYDATA=$(eval ls ${DATA})
echo "Data: ${MYDATA}"

OUT_DIR=$CALIBDATADIR/CalibData_${CALIBDATATYPE}/Mag${MAG_POL}/$PART_NAME
echo "Output directory: ${OUT_DIR}"
mkdir -p ${OUT_DIR}

CALIBAPPDIR=$CALIBDATASCRIPTSROOT/$CMTCONFIG

# perform the D* mass fit
echo "Performing IncLc mass fit" 
$CALIBAPPDIR/IncLcFit.exe "$PART_NAME" "$MAG_POL" "$STRIP_VER" "$CALIBDATATYPE" \
    "$INDEX" "$OUT_DIR" "$PRINTENTRIES" "$EXITONBADFIT" $MYDATA
EXITCODE=$?
if [ $EXITCODE -ne 0 ]; then
  exit $EXITCODE
fi
sleep 3

# merge the h+ and h- samples
echo "Merging h+ and h- samples" 
$CALIBAPPDIR/MergeCharges.exe "IncLc" "$OUT_DIR" "P" "$MAG_POL" \
    "$STRIP_VER" "$OUT_DIR" "$INDEX"
EXITCODE=$?
if [ $EXITCODE -ne 0 ]; then
  exit $EXITCODE
fi
