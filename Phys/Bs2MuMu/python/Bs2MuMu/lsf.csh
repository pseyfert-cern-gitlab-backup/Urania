#!/bin/csh
source $LBSCRIPTS_HOME/LbConfiguration/scripts/LbLogin.csh


SetupProject Erasmus v8r1
python -V
python $BS2MUMUROOT/python/Bs2MuMu/cdf3_mc.py $1 
