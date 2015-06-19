from ROOT import *
from os import system as shell, environ
from Urania import *
AccessPackage("Bs2MuMu")
from merger import *
from Urania import PDG

tempf = "/tmp/" + user + "/"

#tuple = os.environ["HOME"] + "/vol5/Bs_Jpsi_Kst_2013/MagUpAndDown3500GeVReco14s20r1dv33r4_1019pb_StrippingBetaSBs2JpsiKstarWideLine_2011_DOCA_withcuts_oldGL.root"### Update!!
#tuple = "/afs/cern.ch/user/d/diegoms/vol5/Bs_Jpsi_Kst_2013/MC/2012-4000GeV-MagUpAndDown-Nu2.5-Pythia8_Sim08a_Digi13_Trig0x409f0045_Reco14a_s20_dv33r4_WideLine_BDTG_BdJpsiKst.root"
tuple = "Tuple_InjectedMC.root"#/home/galaceos/cmtuser/URANIA/URANIA_HEAD/Phys/BsJPsiKst/ntuples/BdJpsiKpi_MC_BDTG_2012_selected.root"
#out_tuple = "/afs/cern.ch/user/d/diegoms/vol5/Bs_Jpsi_Kst_2013/MC/Bd_2012.root"
out_tuple = "MC_forInjection.root"#/home/galaceos/cmtuser/URANIA/URANIA_HEAD/Phys/BsJPsiKst/ntuples/BdJpsiKpi_MC_BDTG_2012_selected_with_cosines.root"
shell("mkdir " + tempf)

### Use only trueid filtered events

shell(environ["SIMPLETOOLSROOT"] +"/"+ environ["CMTCONFIG"] + "/SimpleToolsColumnMaker.exe " + tuple + " DecayTree  'cos(B0_ThetaK)' "+  " helcosthetaK " + tempf + "Bd.root")
shell(environ["SIMPLETOOLSROOT"] +"/"+ environ["CMTCONFIG"] + "/SimpleToolsColumnMaker.exe " +tempf + "Bd.root" + " DecayTree/DecayTree  'cos(B0_ThetaL)' "+  " helcosthetaL " + out_tuple)
#shell("mv " + tempf + "Bd2.root " + out_tuple)
