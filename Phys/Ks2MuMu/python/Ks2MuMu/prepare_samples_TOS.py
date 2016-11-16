from ROOT import *
from fiducial import *


fmmA = TFile("ks2mmm1fbA.root")
tmA = fmmA.Get("T")
fmmB = TFile("ks2mmm1fbB.root")
tmB = fmmB.Get("T")
#BREAK
massW = "Bmass<480"
extra = " && !mv_Offline"

ffa = TFile("TrainS_FOR_A_marchTOS.root","recreate")
tfa = tmB.CopyTree(massW + aa + tos + aa + traintos + extra )
tfa.Write()
ffa.Close()

ffa = TFile("TrainS_FOR_B_marchTOS.root","recreate")
tfa = tmA.CopyTree(massW +  aa + tos + aa  + traintos+ extra)
tfa.Write()
ffa.Close()

ffa = TFile("TrainB_FOR_A_marchTOS.root","recreate")
tfa = tmB.CopyTree("Bmass>500 && Bmass<1000" +aa + tos + aa + fiducial + aa + dll+ extra)#aa + traintos )
#tfa = tpB.CopyTree(mass + "&& " + traintos)
tfa.Write()
ffa.Close()

ffa = TFile("TrainB_FOR_B_marchTOS.root","recreate")
tfa = tmA.CopyTree("Bmass>500 && Bmass<1000" + aa + tos + aa+ fiducial + aa + dll+ extra)#aa  + traintos)
tfa.Write()
ffa.Close()





