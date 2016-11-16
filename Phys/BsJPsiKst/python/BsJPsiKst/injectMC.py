from ROOT import *
from os import *
year = "2012"
datatuple = "~/NTuplesFast/deita/data_" + year + "_sel.root"

SET_DATA_WEIGHT = 1
if SET_DATA_WEIGHT:
    system(environ["SIMPLETOOLSROOT"] +"/"+ environ["CMTCONFIG"] + "/SimpleToolsColumnMaker.exe " + datatuple  + " DecayTree " + str(1.0) +  " wMC /tmp/deita.root")
    datatuple = "/tmp/deita.root"
ch = TChain("DecayTree/DecayTree")
ch.Add("~/NTuplesFast/MC/peaking/" +year + "/MC_forInjection.root")#,1234567890,"DecayTree")

ch.Add(datatuple)
ch.Merge("~/NTuplesFast/Tuple_BsJPsiKst"+ year +".root")

