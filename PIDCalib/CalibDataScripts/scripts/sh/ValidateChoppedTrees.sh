#!/bin/sh
if [ $# -ne 3 ]; then
  echo "Usage: `basename $0` <stripVersion> <magPol> <inputDir>"
  echo "Example: \"20\" \"Down\" \"$HOME/gangadir/workspace/$USER/LocalXML\""
  exit 1
fi

STRIPVER=$1
MAGPOL=$2
INPUTDIR=$3

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


APP="${CALIBDATASCRIPTSROOT}/scripts/python/validateChoppedTrees.py"
python $APP ${STRIPVER} ${MAGPOL} ${INPUTDIR}
exit $?

