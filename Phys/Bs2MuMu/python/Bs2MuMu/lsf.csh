#!/bin/csh
source $LBSCRIPTS_HOME/LbConfiguration/scripts/LbLogin.csh


SetupUrania --dev-dir ~/vol5/
python -V
python $BS2MUMUROOT/python/Bs2MuMu/combinelimits_2012.py $1 
