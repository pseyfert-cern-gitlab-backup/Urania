from ROOT import *
from sympy import *



t=TFile("BdJpsipipi.root")
f=t.Get("DecayTree")
Sum = 0
for i in range(int(f.GetEntries())):
    f.GetEntry(i)
    x = f.Norm_weights
    Sum = Sum + x
    print Sum



# 1000
