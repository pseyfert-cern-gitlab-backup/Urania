################################################################################
# Package: PIDPerfScripts
################################################################################
gaudi_subdir(PIDPerfScripts v6r2p2)

gaudi_depends_on_subdirs(PIDCalib/PIDPerfTools)

find_package(Boost)
find_package(ROOT)

gaudi_install_python_modules()

gaudi_env(SET CALIBDATASTORE castorlhcb.cern.ch//castor/cern.ch/grid/lhcb/user/s/smalde/CalibData
          SET CALIBDATAURLPROTOCOL root
          SET CALIBDATAURLQUERY svcClass=lhcbuser
          SET CALIBREFDATASTORE castorlhcb.cern.ch//castor/cern.ch/grid/lhcb/user/p/phunt/CalibData
          SET MUONCALIBDATASTORE castorlhcb.cern.ch//castor/cern.ch/grid/lhcb/user/s/smalde/CalibData
          SET MUONCALIBREFDATASTORE castorlhcb.cern.ch//castor/cern.ch/grid/lhcb/user/p/phunt/CalibData)

