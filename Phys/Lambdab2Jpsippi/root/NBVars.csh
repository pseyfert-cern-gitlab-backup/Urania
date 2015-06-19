#!/bin/tcsh
if ( -e /afs/cern.ch/sw/lcg/external/neurobayes/11.11/ ) then
  setenv NEUROBAYES /afs/cern.ch/sw/lcg/external/neurobayes/11.11/${CMTCONFIG}
else if ( -e NeuroBayes ) then
  setenv NEUROBAYES $PWD/NeuroBayes
endif
setenv PHIT_LICENCE_PATH $NEUROBAYES/../../license
if ( -e /afs/cern.ch/sw/lcg/external/gcc/4.7.1/x86_64-slc5/ ) then
  source /afs/cern.ch/sw/lcg/external/gcc/4.7.1/x86_64-slc5/setup.csh
  setenv ROOTSYS /afs/cern.ch/sw/lcg/app/releases/ROOT/5.32.02/x86_64-slc5-gcc43-opt/root
endif
setenv LD_LIBRARY_PATH $ROOTSYS/lib:${LD_LIBRARY_PATH}:${NEUROBAYES}/lib
setenv PATH $ROOTSYS/bin:$PATH
