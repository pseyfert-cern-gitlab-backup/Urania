from ROOT import *
f = TFile("kspi0mm_MC.root")
t = f.Get("T")

#f = TFile("bkgMini.root")
#t = f.Get("BenderKspi0mumuSignal/BenderKspi0mumuSignal")
#BREAK
from SomeUtils.alyabar import *
from Urania import PDG
#BREAK
ha = TH1F("A","A",100,0,0.005)
hb = TH1F("B","B",100,0,0.005)
hc = TH1F("C","C",100,0,0.005)


for entry in t:
    if entry.mo1 != 310 : continue
    if entry.mo2 != 310 : continue
    pmu1 = vector(entry.mu1p1, entry.mu1p2, entry.mu1p3)
    pmu2 = vector(entry.mu2p1, entry.mu2p2, entry.mu2p3)
    pg1 = vector(entry.g1p1, entry.g1p2, entry.g1p3)
    pg2 = vector(entry.g2p1, entry.g2p2, entry.g2p3)
    PV = vector(entry.PV1, entry.PV2, entry.PV3)
    SV = vector(entry.SV1, entry.SV2, entry.SV3)
    EV1 = vector(entry.g1e1, entry.g1e2, entry.g1e3)
    EV2 = vector(entry.g2e1, entry.g2e2, entry.g2e3)
    dir1a = EV1 - PV
    ha.Fill(ACO(dir1a,pg1))
    dir1b = EV1 - SV
    hb.Fill(ACO(dir1b,pg1))
    hc.Fill(ACO(EV1,pg1))
    dir2a = EV2 - PV
    ha.Fill(ACO(dir2a,pg2))
    dir2b = EV2 - SV
    hb.Fill(ACO(dir2b,pg2))
    hc.Fill(ACO(EV2,pg2))
ha.SetLineWidth(3)
ha.Draw()
hb.SetLineColor(kRed)
hb.Draw("same")
hc.SetLineColor(kBlack)
hc.SetFillColor(kBlack)
hc.Draw("same")


    
