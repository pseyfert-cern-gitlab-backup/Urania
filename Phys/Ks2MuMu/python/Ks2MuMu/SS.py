from ROOT import *
from SomeUtils.alyabar import *
import os
os.sys.path.append(os.environ["BS2MUMUROOT"] + "/python/Bs2MuMu/")
from triggerclass import *
f = TFile("MinBias_COV4.root")
t = f.Get("Kspipi")

#f2 = TFile("SSKsPiPi_MinBiasData_ntuple.root")
f2 = TFile("SSMB_COV4.root")
t2 = f2.Get("Kspipi")

h1 = TH1F("A","A", 100,0,.2)
h2 = TH1F("B","B", 100,0,.2)
#h3 = TH1F("C","C", 100,400,600)
#h4 = TH1F("D","D", 100,400,600)

## for entry in t:
##     p1 = vector(entry.mu1p1, entry.mu1p2, entry.mu1p3)
##     p2 = vector(entry.mu2p1, entry.mu2p2, entry.mu2p3)

##     p3 = vector(-entry.mu1p1, entry.mu1p2, entry.mu1p3)
##     p4 = vector(-entry.mu2p1, entry.mu2p2, entry.mu2p3)

##     h1.Fill(sqrt(IM2 (p1,p2, 139.,139)))
##     #p3 = p2
##     #p2[0] = -p2[0]
##     h2.Fill(sqrt(IM2(p3,p2, 139.,139)))
##     h3.Fill(sqrt(IM2(p1,p4, 139.,139)))
##     h4.Fill(sqrt(IM2(p3,p4, 139.,139)))

## h1.Draw()
## h1.SetLineWidth(3)
## h1.SetLineStyle(kDashed)
## h2.SetLineColor(kRed)
## h2.Draw("same")
## h3.SetLineColor(kGreen)
## h3.Draw("same")
## h4.SetLineColor(kBlue)
## h4.Draw("same")

l1,l2 = [], []

i = 0
## for entry in t:
##     p1 = vector(entry.mu1p1,entry.mu1p2,entry.mu1p3)
##     p2 = vector(entry.mu2p1,entry.mu2p2,entry.mu2p3)
##     h1.Fill(ACO(p1,p2))
##     i+=1
##     if i > 20000: break

## hz = TH1F("A","A",100,400,600)
    
## for entry in t2:
##     p1 = vector(entry.mu1p1,entry.mu1p2,entry.mu1p3)
##     p2 = vector(entry.mu2p1,entry.mu2p2,entry.mu2p3)
##     if ACO(p1,p2) < 0.02: continue
##     if entry.mu1ismu:continue
##     if entry.mu2ismu: continue
##     hz.Fill(entry.Bmass)

    
    
OS = channelData("~/vol5/ks/OSC4_TT", name2 = "Kspipi")
SS = channelData("~/vol5/ks/SSC4_TT", name2 = "Kspipi")

def addOp(ch):
    ch.addVariable("mu1pVec",["mu1p1","mu1p2","mu1p3"], vector)
    ch.addVariable("mu2pVec",["mu2p1","mu2p2","mu2p3"], vector)
    ch.addVariable("op_angle",["mu1pVec","mu2pVec"], ACO)
    return 1

addOp(SS)
addOp(OS)

def phi(v):
    return atan(v[1]/v[0])

def thetaY(v):
    return atan(v[1]/v[2])

def thetaX(v):
    return atan(v[0]/v[2])
