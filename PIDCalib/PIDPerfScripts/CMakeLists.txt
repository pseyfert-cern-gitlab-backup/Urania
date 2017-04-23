################################################################################
# Package: PIDPerfScripts
################################################################################
gaudi_subdir(PIDPerfScripts v11r2)

gaudi_depends_on_subdirs(PIDCalib/PIDPerfTools)

find_package(Boost)
find_package(ROOT)
find_package(Xrootd)

gaudi_install_python_modules()

gaudi_env(SET CALIBDATAEXTRA       eoslhcb.cern.ch
	  SET CALIBDATASTORE       eos/lhcb/grid/prod/lhcb/calib/lhcb/calib/pid/CalibData
          SET CALIBDATAURLPROTOCOL root:
          SET OVERRIDECALIBDATASTORE /afs/cern.ch/user/d/dhill/Lb2LcMuNu_April17_PIDCalib/UraniaDev_v6r2p1/PIDCalib/PIDPerfScripts/Lb2LcMuNu_Test_Files/files.dat)



