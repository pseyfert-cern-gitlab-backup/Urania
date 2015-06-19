#!/bin/bash
if [ $# -lt 9 ]; then
  echo "Usage: `basename $0` <gangaJobsDir> <uraniaVersion> <platform> <magPol> <stripVersion> <index> <fileSuffix> <verbose> <exitOnBadFit> (<subIDsToProcess=\"*\">)"
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
echo "Magnet polarity: ${MAG_POL}"
echo "Stripping version: ${STRIP_VER}"
echo "Index: ${INDEX}"
echo "File suffix: ${FILESUFFIX}"
echo "Print entries? ${PRINTENTRIES}"
echo "Exit on bad fit quality? ${EXITONBADFIT}"
echo "Subjobs to process: ${SUBIDS}"

export PYTHONPATH="/afs/cern.ch/user/t/tbird/cmtuser/Urania_v2r1/InstallArea/x86_64-slc5-gcc46-opt/python.zip:/afs/cern.ch/lhcb/software/releases/URANIA/URANIA_v2r1/InstallArea/x86_64-slc5-gcc46-opt/python.zip:/afs/cern.ch/sw/lcg/external/pyanalysis/1.4_python2.7/x86_64-slc5-gcc46-opt/lib/python2.7/site-packages:/afs/cern.ch/sw/lcg/external/pytools/1.8_python2.7/x86_64-slc5-gcc46-opt/lib/python2.7/site-packages:/afs/cern.ch/sw/lcg/app/releases/ROOT/5.34.10/x86_64-slc5-gcc46-opt/root/lib:/afs/cern.ch/lhcb/software/releases/URANIA/URANIA_v2r1/Phys/Bs2MuMu/python:/afs/cern.ch/user/t/tbird/pythonpath:/afs/cern.ch/lhcb/software/releases/LBSCRIPTS/LBSCRIPTS_v7r10p2/InstallArea/python:/afs/cern.ch/lhcb/software/releases/LBSCRIPTS/LBSCRIPTS_v7r9p2/InstallArea/python:${PYTHONPATH}"
export PATH="/afs/cern.ch/user/t/tbird/cmtuser/Urania_v2r1/InstallArea/x86_64-slc5-gcc46-opt/bin:/afs/cern.ch/lhcb/software/releases/URANIA/URANIA_v2r1/InstallArea/x86_64-slc5-gcc46-opt/bin:/afs/cern.ch/sw/lcg/external/pyanalysis/1.4_python2.7/x86_64-slc5-gcc46-opt/bin:/afs/cern.ch/sw/lcg/external/pytools/1.8_python2.7/x86_64-slc5-gcc46-opt/bin:/afs/cern.ch/sw/lcg/external/mysql/5.5.14/x86_64-slc5-gcc46-opt/bin:/afs/cern.ch/sw/lcg/app/releases/ROOT/5.34.10/x86_64-slc5-gcc46-opt/root/bin:/afs/cern.ch/sw/lcg/external/xrootd/3.2.7/x86_64-slc5-gcc46-opt/bin:/afs/cern.ch/sw/lcg/external/gccxml/0.9.0_20120309p2/x86_64-slc5-gcc46-opt/bin:/afs/cern.ch/sw/lcg/external/tcmalloc/1.7p3/x86_64-slc5-gcc46-opt/bin:/afs/cern.ch/sw/lcg/external/Python/2.7.3/x86_64-slc5-gcc46-opt/bin:/afs/cern.ch/sw/lcg/external/gcc/4.6.3/x86_64-slc5/bin:/afs/cern.ch/lhcb/software/releases/COMPAT/COMPAT_v1r18/CompatSys/x86_64-slc5-gcc46-opt/bin:/afs/cern.ch/sw/contrib/CMT/v1r20p20090520/Linux-x86_64:/afs/cern.ch/lhcb/software/releases/LBSCRIPTS/LBSCRIPTS_v7r10p2/InstallArea/scripts:/afs/cern.ch/lhcb/bin:/afs/cern.ch/sw/lcg/contrib/CMake/2.8.9/Linux-i386/bin:/afs/cern.ch/user/t/tbird/bin:/usr/sue/bin:/usr/bin:/bin:/usr/bin/X11:/afs/cern.ch/lhcb/software/releases/LBSCRIPTS/LBSCRIPTS_v7r9p2/InstallArea/scripts:/usr/lib64/qt-3.3/bin:/usr/kerberos/bin:${PATH}"
export HOME=/afs/cern.ch/user/t/tbird
export USER=tbird

set +x
echo "set +x"

# . /data/lhcb/sw/scripts/lbsetup-cvmfs-osagnostic.sh

if [[ "$PLATFORM" != "" && "$PLATFORM" != "$CMTCONFIG" ]]; then
  . LbLogin.sh -c $PLATFORM
  EXITCODE=$?
  if [ $EXITCODE -ne 0 ]; then
    exit $EXITCODE
  fi
else
  . LbLogin.sh
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

echo "PID Calib script dir: ${CALIBDATASCRIPTSROOT}"

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

OUT_DIR=$CALIBDATADIR/CalibData_${CALIBDATATYPE}/Mag${MAG_POL}/e
echo "Output directory: ${OUT_DIR}"
mkdir -p ${OUT_DIR}

CALIBAPPDIR=$CALIBDATASCRIPTSROOT/$CMTCONFIG

# perform the J/psi mass fit
echo "Performing J/psi mass fit"
echo $CALIBAPPDIR/JpsieeFit.exe "$MAG_POL" "$STRIP_VER" "$CALIBDATATYPE" "$INDEX" "$OUT_DIR" "$PRINTENTRIES" "$EXITONBADFIT" $MYDATA
$CALIBAPPDIR/JpsieeFit.exe "$MAG_POL" "$STRIP_VER" "$CALIBDATATYPE" "$INDEX" "$OUT_DIR" "$PRINTENTRIES" "$EXITONBADFIT" $MYDATA
EXITCODE=$?
if [ $EXITCODE -ne 0 ]; then
    exit $EXITCODE
fi
sleep 3

# merge the e+ and e- samples
echo "Merging e+ and e- samples"
$CALIBAPPDIR/MergeCharges.exe "Jpsi" "$OUT_DIR" "e" "$MAG_POL" "$STRIP_VER" "$OUT_DIR" "$INDEX"
EXITCODE=$?
if [ $EXITCODE -ne 0 ]; then
    exit $EXITCODE
fi
