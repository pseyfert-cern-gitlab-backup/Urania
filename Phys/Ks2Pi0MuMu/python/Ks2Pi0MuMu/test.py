from ROOT import *
f = TFile("kspi0mm_MC.root")
t = f.Get("T")

#f = TFile("bkgMini.root")
#t = f.Get("BenderKspi0mumuSignal/BenderKspi0mumuSignal")
#BREAK
from SomeUtils.alyabar import *
from Urania import PDG

h = TH1F("A","A", 100, 400, 600)
href = TH1F("A","A", 100, 400, 600)
hpi0 = TH1F("pi0", "pi0", 100, 100, 170)
for entry in t:
    if entry.mo1 != 310 : continue
    if entry.mo2 != 310 : continue
    pmu1 = vector(entry.mu1p1, entry.mu1p2, entry.mu1p3)
    pmu2 = vector(entry.mu2p1, entry.mu2p2, entry.mu2p3)
    pg1 = vector(entry.g1p1, entry.g1p2, entry.g1p3)
    pg2 = vector(entry.g2p1, entry.g2p2, entry.g2p3)
    Mpizero = sqrt(IM2(pg1,pg2, 0, 0)) ## IM2 = invariant mass squared
    Mmumu = sqrt(IM2(pmu1,pmu2, PDG.muon.mass, PDG.muon.mass)) ## IM2 = invariant mass squared
    MKs = sqrt(IM2 ( pmu1+pmu2,  pg1 + pg2, Mmumu, PDG.pi0.mass))# Mpizero))
    h.Fill(MKs)
    href.Fill(entry.KSmass)
    hpi0.Fill( Mpizero)
h.SetLineColor(kRed)
    
    

    
   

    
    
    
