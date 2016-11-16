from ROOT import *
from Urania import *
AccessPackage("Bs2MuMu")
from XTuple import *
f = TFile("KsPiPi_MinBiasData_TriggerUnbiased_ntuple.root")
t = f.Get("Kspipi")

tup = XTuple("Joban",["evt/F", "AP_pt/F","AP_alpha/F", "time/F"])
i = 0
for entry in t:
    
    tup.fillItem("AP_pt",entry.AP_pt)
    tup.fillItem("AP_alpha",entry.AP_alpha)
    tup.fillItem("time",entry.Blife_ps)
    tup.fillItem("evt",i)
    i += 1
    tup.fill()


tup.close()

