from ROOT import *
from sympy import *



t=TFile("BsJpsiKK_MC_BDTG_2012_selected.root")
f=t.Get("DecayTree")
Sum = 0
for i in range(int(f.GetEntries())):
    f.GetEntry(i)
    x = f.Norm_weights
    Sum = Sum + x
    print Sum


