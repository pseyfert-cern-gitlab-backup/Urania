#!/bin/bash

# top level ganga directory containing the job subdirectories
##export GANGAJOBSDIR=/data/lhcb/users/hunt/gangadir_calib/workspace/huntp/LocalXML

# top level directory where the calibration samples should be stored
export CALIBDATADIR=/data/lhcb/users/malde

#export CALIBDATADIR=/home/malde

# Datatype (e.g. 2011 or 2012)
export CALIBDATATYPE=2012

# Ganga job IDs (as space separated list)
# NB. Can be looped over in bash as 'for i in $JIDS; do ...',
# or in python as 'jids=os.getenv("JIDS").split()
export CALIBDATA_JIDS_DOWN="319"
export CALIBDATA_JIDS_UP="320"
