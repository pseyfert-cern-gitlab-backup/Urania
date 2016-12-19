################################################################################
# Package: UraniaSys
################################################################################
gaudi_subdir(UraniaSys v6r0)

gaudi_depends_on_subdirs(Math/MCLimit
Math/SomeUtils 
Phys/A2MuMu
Phys/B2CCtuples
Phys/Bs2JpsiKs
Phys/Bs2JpsiPhiParams
Phys/Bs2MuMu
Phys/Bs2MuMuParams
Phys/BsJPsiKst
Phys/BsKstKst
Phys/Ks2MuMu
Phys/Ks2Pi0MuMu
Phys/Lambdab2Jpsippi
Phys/Urania
Phys/BsDsMuNuForRDS
PhysFit/B2DXFitters
PhysFit/P2VV
PhysFit/RooPhysFitter
PhysFit/SomeMassModels
PIDCalib/CalibDataScripts
PIDCalib/PIDPerfScripts
PIDCalib/PIDPerfTools
RootTools/LHCbStyle
RootTools/SimpleTools)

gaudi_env(SET GAUDI_home .)
