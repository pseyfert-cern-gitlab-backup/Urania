from ROOT import *
from os import system as shell, environ
from Urania import *
AccessPackage("Bs2MuMu")
from merger import *
from Urania import PDG

tempf = "/tmp/" + user + "/"

tuple = os.environ["HOME"] + "/vol5/Bs_Jpsi_Kst_2013/MagUpAndDown3500GeVReco14s20r1dv33r4_1019pb_StrippingBetaSBs2JpsiKstarWideLine_2011_DOCA_withcuts_oldGL.root"### Update!!
out_tuple = "/afs/cern.ch/user/d/diegoms/vol5/Bs_Jpsi_Kst_2013/2011.root"
shell("mkdir " + tempf)

### Use only trueid filtered events

shell(environ["SIMPLETOOLSROOT"] +"/"+ environ["CMTCONFIG"] + "/SimpleToolsColumnMaker.exe " + tuple + " DecayTree  'cos(B0_ThetaK)' "+  " helcosthetaK " + tempf + "Bd.root")
shell(environ["SIMPLETOOLSROOT"] +"/"+ environ["CMTCONFIG"] + "/SimpleToolsColumnMaker.exe " +tempf + "Bd.root" + " DecayTree/DecayTree  'cos(B0_ThetaL)' "+  " helcosthetaL " + out_tuple)
#shell("mv " + tempf + "Bd2.root " + out_tuple)
