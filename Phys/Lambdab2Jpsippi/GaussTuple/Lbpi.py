
from Gauss.Configuration import *

#--Generator phase, set random numbers                                                                                                                       
GaussGen = GenInit("GaussGen")

#--Number of events                                                                                                                                          
LHCbApp().EvtMax = 10000000

GaussGen.PrintFreq = 1000

GaussGen.FirstEventNumber = 1
GaussGen.RunNumber        = 1083


from Gauss.Configuration import *

Gauss().Phases = ["Generator"] 
Gauss().OutputType =  'NONE'
Gauss().Histograms =  'NONE'

from Configurables import ( Generation, 
                            StandAloneDecayTool )

Generation().SampleGenerationTool = "StandAloneDecayTool";

Generation().addTool( StandAloneDecayTool )

Generation().StandAloneDecayTool.ProductionTool = "PythiaProduction";

Generation().PileUpTool = "FixedNInteractions"

from Configurables import ToolSvc
from Configurables import EvtGenDecay

ToolSvc().addTool( EvtGenDecay )

ToolSvc().EvtGenDecay.UserDecayFile = "Lb_Jpsippi,mm=phsp,DecProdCut.dec"

Generation().StandAloneDecayTool.SignalPIDList = [ 5122 , -5122 ] 

def doMyChanges():
    from Configurables import DumpHepMCDecay
    dump = DumpHepMCDecay()
    dump.Particles = [ 5122,-5122 ]
#    ApplicationMgr().TopAlg += [ dump ]
    
    from Configurables import NTupleSvc
    NTupleSvc().Output  = [ "FILE1 DATAFILE='~/scratch/Tuple-Lbpi.root' OPT='NEW'"] 
    

    from Configurables import GaussDecayTupleTool
    
    _tuple = GaussDecayTupleTool("Lambdab",OutputLevel = 3)
    _tuple.Mother = "Lambda_b0"
    _tuple.Daughters = "p+ pi- J/psi(1S)"
#    _tuple.Daughters = "p+ pi- mu+ mu-"
#    _tuple.DeclareStable = [ 443, 321, 211, 13, 2212 ] # 443
    #_tuple.DeclareStable = [ 13, 4122, 14 ]
    _tuple.Mother      = "Lambda_b0"
    _tuple.Daughters = "p+ pi- mu+ mu-"
    _tuple.DeclareStable = [ 211, 2212, 13 ]
    ApplicationMgr().TopAlg += [ _tuple ]
           
    _tuple2 = GaussDecayTupleTool("Lambdabbar",OutputLevel = 3)
    _tuple2.Mother = "Lambda_b~0"
#    _tuple2.Daughters = "p+ pi- J/psi(1S)"
    _tuple2.Daughters = "p~- pi+ J/psi(1S)"
    _tuple2.DeclareStable = [ 443, 321, 211, 13, 2212 ] # 443
#    ApplicationMgr().TopAlg += [ _tuple2 ]

    

appendPostConfigAction(doMyChanges)
