alias cmake=/cvmfs/lhcb.cern.ch/lib/contrib/CMake/3.3.2/Linux-x86_64/bin/cmake
source LbLogin.sh -c x86_64-slc6-gcc49-opt
source SetupProject.sh LCGCMT 84 ROOT Boost GSL
export CC=/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_84/gcc/4.9.3/x86_64-slc6/bin/gcc
export CXX=/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_84/gcc/4.9.3/x86_64-slc6/bin/g++
export LXPLUSHACK=1
export LXPLUS_BOOST_DIRS=/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_84/Boost/1.59.0_python2.7/x86_64-slc6-gcc49-opt/include/boost-1_59/
export LXPLUS_BOOST_LIB_1=/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_84/Boost/1.59.0_python2.7/x86_64-slc6-gcc49-opt/lib/libboost_serialization-gcc49-mt-1_59.so
export LXPLUS_BOOST_LIB_2=/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_84/Boost/1.59.0_python2.7/x86_64-slc6-gcc49-opt/lib/libboost_filesystem-gcc49-mt-1_59.so
export LXPLUS_BOOST_LINK=/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_84/Boost/1.59.0_python2.7/x86_64-slc6-gcc49-opt/lib/
