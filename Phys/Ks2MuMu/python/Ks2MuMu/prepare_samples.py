from ROOT import *
from fiducial import *

fpipiA = TFile("~/vol5/ks/ks2pipi1fbA.root")
tpA = fpipiA.Get("T")
fpipiB = TFile("~/vol5/ks/ks2pipi1fbB.root")
tpB = fpipiB.Get("T")

fmmA = TFile("ks2mmm1fbA.root")
tmA = fmmA.Get("T")
fmmB = TFile("ks2mmm1fbB.root")
tmB = fmmB.Get("T")
BREAK
massW = "abs(Bmass-497.614)<15"

ffa = TFile("TrainS_FOR_A_marchTIS.root","recreate")
tfa = tpB.CopyTree(massW + "&& L0Tis && Hlt1Tis && Hlt2Tis &&" + fiducial)
tfa.Write()
ffa.Close()

ffa = TFile("TrainS_FOR_B_marchTIS.root","recreate")
tfa = tpA.CopyTree(massW + "&& L0Tis && Hlt1Tis && Hlt2Tis &&" + fiducial)
tfa.Write()
ffa.Close()

ffa = TFile("TrainB_FOR_A_marchTIS.root","recreate")
tfa = tmB.CopyTree("Bmass>500 && Bmass>1100 && L0Tis && Hlt1Tis && Hlt2Tis &&" + fiducial + aa + dll)
#tfa = tpB.CopyTree(mass + "&& " + fiducial)
tfa.Write()
ffa.Close()

ffa = TFile("TrainB_FOR_B_marchTIS.root","recreate")
tfa = tmA.CopyTree("Bmass>500 && Bmass>1100 && L0Tis && Hlt1Tis && Hlt2Tis && " + fiducial+ aa + dll)
tfa.Write()
ffa.Close()





