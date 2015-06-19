setenv NEUROBAYES /afs/cern.ch/sw/lcg/external/neurobayes/11.11/${CMTCONFIG}
setenv PHIT_LICENCE_PATH /afs/cern.ch/sw/lcg/external/neurobayes/license
source /afs/cern.ch/sw/lcg/external/gcc/4.3.5/x86_64-slc5/setup.csh
setenv ROOTSYS /afs/cern.ch/sw/lcg/app/releases/ROOT/5.32.02/x86_64-slc5-gcc43-opt/root
setenv LD_LIBRARY_PATH $ROOTSYS/lib:${LD_LIBRARY_PATH}:${NEUROBAYES}/lib
setenv PATH $ROOTSYS/bin:$PATH
