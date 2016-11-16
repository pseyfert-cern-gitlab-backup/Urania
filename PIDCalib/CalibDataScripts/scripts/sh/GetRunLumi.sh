#!/bin/sh

if [ $# -lt 7 ]; then
  echo "Usage: `basename $0` <getRunLumiPath> <configVersion> <recoVersion> " \
"<stripVersion> <lumiBlock_MagDown (pb-1)> " \
"<lumiBlock_MagUp (pb-1)> <fileSuffix> (<outputDir='.'>)"
  echo "Example: \"$HOME/cmtuser/Urania_v2r1/PIDCalib/CalibDataScripts/python/getRunLumi.py\" " \
"\"Collision12\" \"14\" \"20\" 32 34 \"dst_k_and_pi\""
  exit 1
fi

# Set the script arguments
APP=$1
CONFIGVERSION=$2
RECOVERSION=$3
STRIPVERSION=$4
LUMIBLOCK_DOWN=$5
LUMIBLOCK_UP=$6
FILESUFFIX=$7
OUTPUTDIR="$8"

. /data/lhcb/sw/scripts/lbsetup-cvmfs-osagnostic.sh
EXITCODE=$?
if [ $EXITCODE -ne 0 ]; then
  exit $EXITCODE
fi

# set VOMS and CA certificates directories
export X509_CERT_DIR=/cvmfs/grid.cern.ch/etc/grid-security/certificates
export X509_VOMS_DIR=/cvmfs/grid.cern.ch/etc/grid-security/vomsdir

if [[ "$PLATFORM" != "" && "$PLATFORM" != "$CMTCONFIG" ]]; then
  . LbLogin.sh -c $PLATFORM
  EXITCODE=$?
  if [ $EXITCODE -ne 0 ]; then
    exit $EXITCODE
  fi
fi
. SetupProject.sh LHCbDirac ROOT pyanalysis
EXITCODE=$?
if [ $EXITCODE -ne 0 ]; then
  exit $EXITCODE
fi

echo "*********************************"
echo ""

# run the application
python $APP $CONFIGVERSION "/Reco${RECOVERSION}/Stripping${STRIPVERSION}" \
    $LUMIBLOCK_DOWN $LUMIBLOCK_UP $FILESUFFIX $OUTPUTDIR
exit $?
