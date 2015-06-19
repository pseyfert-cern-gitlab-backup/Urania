##
from Gaudi.Configuration import *
from Configurables import CombineParticles, GaudiSequencer

testKstar = CombineParticles("testKstar")
GaudiSequencer("SeqtestKstar").Members += [testKstar ] 

#testKstar.addTool(PhysDesktop())

#from Configurables import OnOfflineTool
#testKstar.addTool(OnOfflineTool())
#testKstar.OnOfflineTool.OfflinePVRelatorName = 'GenericParticle2PVRelator__p2PVWithIP_OfflineDistanceCalculatorName_'

testKstar.InputLocations = [ "Phys/StdLooseKaons", "Phys/StdLoosePions" ]

testKstar.DecayDescriptor =  "[K*(892)0 -> K+ pi-]cc"#"J/psi(1S) -> mu+ mu-" 
testKstar.DaughtersCuts = {"K+": "(ISLONG) & (TRCHI2DOF < 5 ) & (MIPCHI2DV(PRIMARY)> 4.) & (PIDK>3)",
                           "pi-":"(ISLONG) & (TRCHI2DOF < 5 ) & (MIPCHI2DV(PRIMARY)> 4.) & (PIDK<0)"}
testKstar.CombinationCut =  "(ADAMASS('K*(892)0')<2000*MeV)"# & (AMAXDOCA('') <  0.1*mm ) "
testKstar.MotherCut = "(VFASPF(VCHI2)<9)"
