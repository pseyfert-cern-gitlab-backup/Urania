#!/bin/bash

if [ $# -ne 9 ]; then
  echo "Usage: `basename $0` <uraniaVersion> <platform> <jobID> " \
"<pickleFileName> <minSubJob> <maxSubJob> <treeList> <inputDir> " \
"<fileSuffix>"
  exit 1
fi

URANIAVERSION=$1
PLATFORM=$2
JID=$3
PKLFILE=$4
SUBID_MIN=$5
SUBID_MAX=$6
TREELIST=$7
INDIR=$8
FILESUFFIX=$9

echo $URANIAVERSION
echo $PLATFORM
echo $JID
echo $PKLFILE
echo $SUBID_MIN
echo $SUBID_MAX
echo $TREELIST
echo $INDIR
echo $FILESUFFIX
# configure the environment
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

echo "*********************************"
echo ""

# Get the name of the script

APP=$CALIBDATASCRIPTSROOT/scripts/python/chopTrees_LcfB.py

# run the application
python $APP "$JID" "$PKLFILE" "$SUBID_MIN" "$SUBID_MAX" \
  "$TREELIST" "$INDIR" "$FILESUFFIX"
exit $?
