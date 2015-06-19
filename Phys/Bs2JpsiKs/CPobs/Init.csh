#!/bin/tcsh
if ( -e /afs/cern.ch/sw/lcg/external/neurobayes/3.16.0/x86_64-slc6-gcc44-opt ) then
  setenv NEUROBAYES /afs/cern.ch/sw/lcg/external/neurobayes/3.16.0/x86_64-slc6-gcc44-opt
endif
setenv PHIT_LICENCE_SERVER lcgapp09:16820
setenv PHIT_LICENCE_PATH $NEUROBAYES/../../license

# SLC6
if ( -e /afs/cern.ch/sw/lcg/external/gcc/4.7.1/x86_64-slc6/ ) then
  source /afs/cern.ch/sw/lcg/external/gcc/4.7.1/x86_64-slc6/setup.csh
  setenv ROOTSYS /afs/cern.ch/sw/lcg/app/releases/ROOT/5.34.18/x86_64-slc6-gcc46-opt/root
endif

# Paths
setenv LD_LIBRARY_PATH $ROOTSYS/lib:${LD_LIBRARY_PATH}:${NEUROBAYES}/lib
setenv PATH $ROOTSYS/bin:$PATH
