from ROOT import *
from os import system as shell, environ
from Urania import *
AccessPackage("Bs2MuMu")
from merger import *
from Urania import PDG

tempf = "/tmp/" + user + "/"
year = "2012"
tuple = "~/NTuplesFast/MC/peaking/"+ year+ "/merged.root"
out_tuple = "~/NTuplesFast/MC/peaking/"+year+"/MC_forInjection.root"
shell("mkdir " + tempf)

### Use only trueid filtered events

shell(environ["SIMPLETOOLSROOT"] +"/"+ environ["CMTCONFIG"] + "/SimpleToolsColumnMaker.exe " + tuple + " DecayTree  'cos(B0_ThetaK)' "+  " helcosthetaK " + tempf + "Bd.root")
shell(environ["SIMPLETOOLSROOT"] +"/"+ environ["CMTCONFIG"] + "/SimpleToolsColumnMaker.exe " +tempf + "Bd.root" + " DecayTree/DecayTree  'cos(B0_ThetaL)' "+  " helcosthetaL " + out_tuple)
#shell("mv " + tempf + "Bd2.root " + out_tuple)
