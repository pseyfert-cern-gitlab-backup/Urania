#! /usr/bin/env python

import sys, os
from Gaudi.Configuration import *#NTupleSvc
from Configurables import GaudiSequencer, DaVinci
##from StrippingConf.StrippingLine import StrippingLine#, StrippingLines
##from StrippingConf.Configuration import StrippingConf

AFS = os.environ["HOME"] + "/"#"/cmtuser/"

################################### Some General Options. Remember to check it

MC_INFO = 1 #Stores MC particle information
ONLY_MC= 1 #Forces to select Truthmatched events only
DST = 0 #Writes DST
TUP = 1 #Writes NTuple
TRIGGER = 0 #Writes basic trigger info
EXTTRIG = 0 #Writes advance trigger info

### Avoid inconsistent flags:
TRIGGER = TRIGGER or EXTTRIG
MC_INFO = MC_INFO or ONLY_MC


#Data ="MC09"#DC06" #data Type
Data = "2010"
Simulation = True
print Data

###########################
### FOR BATCH MODE ONLY ###
###########################

string = ""
args = sys.argv
for arg in args[1:]:
    if arg in ["-b","-b-"]: continue
    string += "_" + arg
    
####################################
### Names for OUTPUT NTuple, Dst ###
####################################

if TUP:
    tuplesv=["T DATAFILE='"+os.environ["BSKSTKSTROOT"]+"/NTuples/Bd2PhiKst"+string+".root' TYP='ROOT' OPT='NEW'"]
    if EXTTRIG:tuplesv+=["T2 DATAFILE='"+os.environ["BSKSTKSTROOT"]+"/NTuples/Bs2KstKst_trig"+string+".root' TYP='ROOT' OPT='NEW'"]
    NTupleSvc( Output =tuplesv)

if DST:
    dstname =  "DATAFILE='castor:" + os.environ["CASTOR_HOME"] + "/MC09BsKstar" +string+".dst' "+ "TYP='POOL_ROOTTREE' OPT='RECREATE'"
    
#################
### DATACARDS ###
#################

selection = "$B2VV_V2HHSELECTIONS/DVSelLooseBd2PhiKst0.py"  ### Now also in Installarea

datacards =  os.environ["BSKSTKSTROOT"] + "/datacards/BdPhiKst.py"

from BenderBdPhiKst import *
#from DstEnabler import *
#from ForceExecution import * ## IDEM
import BsMuMuPy.algorithms.Itemlists as Itemlists
from BsMuMuPy.algorithms.DstEnabler import *

def configure():
    ################### IMPORTING OPTIONS
    #from ROOT import IANNSvc
    
    DaVinci().EvtMax = 0    
    DaVinci().DataType = Data 
    DaVinci().Simulation = Simulation
    DaVinci().DDDBtag = 'head-20100407'
    DaVinci().CondDBtag = 'sim-20100429-vc-mu100'

    DaVinci().UserAlgorithms = []
    DaVinci().HistogramFile =os.environ["BSKSTKSTROOT"] + "/NTuples/MCtestrbH_phiKst"+string+".root"
    
    #importOptions("$DAVINCIROOT/options/PreloadUnits.opts")
    importOptions("$STDOPTS/PreloadUnits.opts")
    
    importOptions( selection )
    DaVinci().UserAlgorithms += [GaudiSequencer("Bd2PhiKstDet")]  ### Check you use the right name (or automate it)!
     
        
    if TRIGGER:
       
        DaVinci().Hlt2Requires = 'L0+Hlt1'
        #DaVinci().HltType = 'Hlt1+Hlt2'
        DaVinci().Hlt = False
        
        from Configurables import Hlt2CommissioningLinesConf
        Hlt2CommissioningLinesConf().Prescale = { 'Hlt2Forward' : 0 } 
        
        if Data == "DC06": DaVinci().ReplaceL0BanksWithEmulated = True
         
    importOptions(datacards)  ### Be sure you DO NOT import any other options file after this one. You can overload eventselector input.
    ################## END IMPORTING OPTIONS
    DaVinci().applyConf()   
    gaudi = appMgr(outputlevel=3)
    
    
  
    if DST:
        gaudi.OutStream = ["DstWriter"]
        gaudi.algorithm("DstWriter").Preload = False
        gaudi.algorithm("DstWriter").Output = dstname
        gaudi.algorithm("DstWriter").ItemList = Itemlists.DstW[Data]
        dstW = DstEnabler("DstEnabler")
        dstW.selectionLocations = []
       
        dstW.selectionLocations += ['/Event/Phys/Bd2PhiKst']
        dstW.COUNTER = {}
        dstW.COUNTER["EVT"] = 0
        for sel in dstW.selectionLocations: dstW.COUNTER[sel] = 0
  
    bs= BdPhiKst0("BdPhiKst0")      
    bs.COUNTER = {}
    bs.decayname = "[B0 -> phi(1020) K*(892)0]cc "
    bs.COUNTER["reco"]=0 
    bs.COUNTER["EVT"] = 0
    bs.COUNTER["Sel"] = 0
    bs.LookIn ="Bd2PhiKstDet"#  "Bs2KstKst"
   
    gaudi.addAlgorithm(bs)
    bs.InputLocations = ['/Event/Phys/StdNoPIDKaons' ,'/Event/Phys/StdNoPIDPions','/Event/Phys/StdLooseDetachedKst2KpiN' ] #StdLooseRobustKst2Kpi' ]#'StdLooseDetachedKst2Kpi' ]


    if DST: gaudi.addAlgorithm(dstW)
    gaudi.initialize()
  
 
    ########################
    ##COMMON ATRIBUTES ####
    ######################
   
    bs.MC_INFO = MC_INFO 
    bs.ONLY_MC= ONLY_MC 
    bs.TRIGGER = TRIGGER 
    bs.EXTTRIG = EXTTRIG
    
    bs.NTupleLUN = "T"
    bs.addedKeys = []
    bs.DST = DST
    
    bs.TUP = TUP
    #bs.IPid =2102
    if TRIGGER:
        bs.tistostool = gaudi.toolsvc().create('TriggerTisTos', interface='ITriggerTisTos')
          
            
configure()
#N =-1#30000#1000#-1 #5000000
N =-1#30000#1000#-1 #5000000

gaudi = appMgr(outputlevel=3)

gaudi.run(N)
gaudi.stop()

gaudi.finalize()

