#!/bin/tcsh
if ( -e /afs/cern.ch/sw/lcg/external/neurobayes/11.11/ ) then
  setenv NEUROBAYES /afs/cern.ch/sw/lcg/external/neurobayes/11.11/${CMTCONFIG}
else if ( -e ~/work/NeuroBayes/ ) then
  setenv NEUROBAYES ~/work/NeuroBayes/
endif
setenv PHIT_LICENCE_PATH $NEUROBAYES/../../license

# SLC6
#if ( -e /afs/cern.ch/sw/lcg/external/gcc/4.7.1/x86_64-slc6/ ) then
#  source /afs/cern.ch/sw/lcg/external/gcc/4.7.1/x86_64-slc6/setup.csh
#  setenv ROOTSYS /afs/cern.ch/sw/lcg/app/releases/ROOT/5.34.07/x86_64-slc6-gcc46-opt/root
#endif
# SLC5
if ( -e /afs/cern.ch/sw/lcg/external/gcc/4.7.1/x86_64-slc5/ ) then
  source /afs/cern.ch/sw/lcg/external/gcc/4.7.1/x86_64-slc5/setup.csh
  setenv ROOTSYS /afs/cern.ch/sw/lcg/app/releases/ROOT/5.34.07/x86_64-slc5-gcc46-opt/root
endif

setenv LD_LIBRARY_PATH $ROOTSYS/lib:${LD_LIBRARY_PATH}:${NEUROBAYES}/lib
setenv PATH $ROOTSYS/bin:$PATH
