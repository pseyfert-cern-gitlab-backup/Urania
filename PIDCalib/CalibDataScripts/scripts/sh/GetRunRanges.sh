#!/bin/bash

if [ $# -lt 7 ]; then
  echo "Usage: `basename $0` <gangaJobsDir> <uraniaVersion> <platform> <magPol> " \
       "<stripVersion> <fileSuffix> <tupleDir> (<cuts=\"\"> <maxEntries=2e6> " \
       "<stepFrac=0.01> <minFrac=0.9>)"
  exit 1
fi

GANGAJOBSDIR=$1
shift
URANIAVERSION=$1
shift
PLATFORM=$1
shift
MAG_POL=$1
shift
STRIP_VER=$1
shift
FILESUFFIX=$1
shift
TUPLEDIR=$1
shift
CUTS=""
if [ $# -gt 0 ]; then
  CUTS=$1
  shift
fi
MAXENTRIES="1000000"
if [ $# -gt 0 ]; then
#  MAXENTRIES=$1
  shift
fi
STEPFRAC="0.01"
if [ $# -gt 0 ]; then
  STEPFRAC=$1
  shift
fi
MINFRAC="0.9"
if [ $# -gt 0 ]; then
  MINFRAC=$1
fi

echo "Input directory: ${GANGAJOBSDIR}"
echo "Urania version: ${URANIAVERSION}"
echo "Platform: ${PLATFORM}"
echo "Magnet polarity: ${MAG_POL}"
echo "Stripping version: ${STRIP_VER}"
echo "File suffix: ${FILESUFFIX}"
echo "NTuple directory: ${TUPLEDIR}"
echo "Selection cuts: ${CUTS}"
echo "Initial maxEntries: ${MAXENTRIES}"
echo "maxEntries step-size fraction: ${STEPFRAC}"
echo "maxEntries minimum remainder fraction: ${MINFRAC}"

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
    DATA=${GANGAJOBSDIR}/${CALIBDATA_JIDS_UP}/*/output/PIDCalib.root
elif [ $MAG_POL == Down ]
then
    DATA=${GANGAJOBSDIR}/${CALIBDATA_JIDS_DOWN}/*/output/PIDCalib.root
else
    echo "Invalid magnet polarity. Expected 'Up' or 'Down', got $MAG_POL"
    exit 1
fi
###=================================================###

MYDATA=$(eval ls ${DATA})
echo "Data: ${MYDATA}"

OUT_DIR="${CALIBDATASCRIPTSROOT}/jobs/Stripping${STRIP_VER}/ChopTrees"
mkdir -p ${OUT_DIR}

PKLNAME="${OUT_DIR}/$(echo $MAG_POL | sed 's/.*/\L&/')_runLimits_${FILESUFFIX}.pkl"
echo "Pickle filename: ${PKLNAME}"

APP="${CALIBDATASCRIPTSROOT}/scripts/python/getRunRanges.py"

python $APP -c "${CUTS}" -m ${MAXENTRIES} -s ${STEPFRAC} -f ${MINFRAC} \
  ${TUPLEDIR} ${PKLNAME} ${DATA}
EXITCODE=$?
if [ $EXITCODE -ne 0 ]; then
  exit $EXITCODE
fi
