################################################################################
# Package: UraniaSys
################################################################################
gaudi_subdir(UraniaSys v2r2)

gaudi_depends_on_subdirs(Math/MCLimit
                         Math/SomeUtils
                         PIDCalib/CalibDataScripts
                         PIDCalib/PIDPerfScripts
                         PIDCalib/PIDPerfTools
                         Phys/A2MuMu
                         Phys/B2CCtuples
                         Phys/Bs2JpsiKs
                         Phys/Bs2JpsiPhiParams
                         Phys/Bs2MuMu
                         Phys/Bs2MuMuParams
                         Phys/BsJPsiKst
                         Phys/BsKstKst
                         Phys/Lambdab2Jpsippi
                         Phys/Urania
                         PhysFit/B2DXFitters
                         PhysFit/P2VV
                         PhysFit/RooPhysFitter
                         PhysFit/SomeMassModels
                         RootTools/LHCbStyle
                         RootTools/MoreSimpleTools
                         RootTools/SimpleTools)

gaudi_env(SET GAUDI_home .)
