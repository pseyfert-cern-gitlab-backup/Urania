

# Here you specify versions for root, gcc and python.
#   For now we stay with 5.34.25 untill more tests are done with ROOT6.
#   The idea is tha we will run p2vv on the latest ROOT.
#   You are encouraged to test/try newer versions of gcc or python.
#   It is advisable to keep gcc versions of pyhton and root consistent. 
export ROOTSYS=/afs/cern.ch/work/v/vsyropou/public/workdir/repositories/root # <--- Modify this to point to your personal ROOT version. P2VV patches should be applied as well.
export LCGDIR=/afs/cern.ch/sw/lcg/releases/LCG_72a
export PATH=$ROOTSYS/bin:${LCGDIR}/Python/2.7.6/x86_64-slc6-gcc48-opt/bin:${LCGDIR}/gcc/4.8.1/x86_64-slc6/bin:$PATH
export LD_LIBRARY_PATH=$ROOTSYS/lib:${LCGDIR}/Python/2.7.6/x86_64-slc6-gcc48-opt/lib:${LCGDIR}/gcc/4.8.1/x86_64-slc6/lib64:$LD_LIBRARY_PATH
export PYTHONPATH=$ROOTSYS/lib:$PYTHONPATH
echo Using ROOT from: ${ROOTSYS}

# Here we specify p2vv
export P2VVROOT=/afs/cern.ch/work/v/vsyropou/public/workdir/repositories/p2vv-gitlab/standalone/ #  <--- Modify this such that it points to the location of your local p2vv repository.
export LD_LIBRARY_PATH=$P2VVROOT/lib:${LD_LIBRARY_PATH}
export PYTHONPATH=$P2VVROOT/python:$P2VVROOT/lib:${PYTHONPATH}
echo Using P2VV from: ${P2VVROOT}

# Here we include python packages like numpy, sympy, etc..
export PYTHONPATH=${LCGDIR}/pytools/1.8_python2.7/x86_64-slc6-gcc48-opt/:$PYTHONPATH
export PYTHONPATH=${LCGDIR}/pyanalysis/1.4_python2.7/x86_64-slc6-gcc48-opt/:$PYTHONPATH

