from ROOT import *
from Urania import *
AccessPackage("Bs2MuMu")
from smartpyROOT import *
from triggerclass import *

f = TFile("www.root)
t = f.Get("DecayTree/DecayTree")
t2 = t.CopyTree("runNumber<88000")
ch = channelData(fromRootToListDic(t2))
print ch.getKeys()
