from ROOT import *
from os import *
datatuple = "~/vol5/Bs_Jpsi_Kst_2013/MagUpAndDown3500GeVReco14s20r1dv33r4_1019pb_StrippingBetaSBs2JpsiKstarWideLine_2011_BDTG_Loose_wCosines.root"
#datatuple = "~/vol5/Bs_Jpsi_Kst_2013/MagUpAndDown4000GeVReco14s20r0p1dv33r4_2062pb_StrippingBetaSBs2JpsiKstarWideLine_2012_BDTG_Loose_wCosines.root"
SET_DATA_WEIGHT = 1
if SET_DATA_WEIGHT:
    system(environ["SIMPLETOOLSROOT"] +"/"+ environ["CMTCONFIG"] + "/SimpleToolsColumnMaker.exe " + datatuple  + " DecayTree " + str(1.0) +  " wMC /tmp/deita.root")
    datatuple = "/tmp/deita.root"
ch = TChain("DecayTree/DecayTree")
ch.AddFile("~/vol5/MC_injection_2011_fake.root",1234567890,"DecayTree")
#ch.Add("~/LHCbS/lhcb/URANIA/URANIA_HEAD/Phys/BsJPsiKst/python/Yorgos/BdJpsipipi.root")
#ch.Add("~/LHCbS/lhcb/URANIA/URANIA_HEAD/Phys/BsJPsiKst/python/Yorgos/BsJpsipipi.root")
#ch.Add("~/LHCbS/lhcb/URANIA/URANIA_HEAD/Phys/BsJPsiKst/python/Yorgos/BsJpsiKK_MC_BDTG_2012_selected.root")
#ch.AddFile(datatuple,1234567890,"DecayTree/DecayTree")
ch.Add(datatuple)
ch.Merge("~/vol5/Tuple_BsJPsiKst2011.root")

