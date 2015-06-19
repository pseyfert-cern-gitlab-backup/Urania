#!/bin/tcsh

if ( -e /afs/cern.ch/sw/lcg/external/neurobayes/3.7.0/ ) then
  setenv NEUROBAYES /afs/cern.ch/sw/lcg/external/neurobayes/3.7.0/${CMTCONFIG}
else if ( -e NeuroBayes ) then
  setenv NEUROBAYES $PWD/NeuroBayes
endif
setenv PHIT_LICENCE_SERVER lcgapp09:16820
setenv PHIT_LICENCE_PATH $NEUROBAYES/../../license
# /afs/cern.ch/sw/lcg/external/gcc/4.6.3/${CMTCONFIG} /afs/cern.ch/sw/lcg/app/releases/ROOT/5.34.03/${CMTCONFIG}/root
if ( -e /afs/cern.ch/sw/lcg/external/gcc/4.6.3/${CMTCONFIG} ) then
  source /afs/cern.ch/sw/lcg/external/gcc/4.6.3/${CMTCONFIG}/setup.csh
  setenv ROOTSYS /afs/cern.ch/sw/lcg/app/releases/ROOT/5.34.09/${CMTCONFIG}/root
endif
setenv LD_LIBRARY_PATH $ROOTSYS/lib:${LD_LIBRARY_PATH}:${NEUROBAYES}/lib
setenv PATH $ROOTSYS/bin:$PATH
