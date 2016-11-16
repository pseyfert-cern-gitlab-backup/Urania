from ROOT import *
f = TFile("KsMuMu_MC11_ntuples.root")
#f = TFile("MC10_BKPi_Stp17_cernTuple.root")
t = f.Get("Ksmumu")
#t = f.Get("B2hh/B2hh")
from SomeUtils.alyabar import *

h0 = TH1F("IP0", "IP0", 100,0.,.5)
h = TH1F("IP", "IP", 100,0.,.5)
hS = TH1F("IPSlope", "IPSlope", 100,0.,.5)
hP = TH1F("IPP", "IPP", 100,0.,.5)
hpe = TH1F("IPprime", "IPprime", 100,0.,.5)

h0.SetLineColor(kRed)

for i in range(1000):# in t:
    t.GetEntry(i)
    PV = vector(t.PV1_r, t.PV2_r, t.PV3_r)
    SV = vector(t.SV1, t.SV2, t.SV3)
    p1 = vector(t.mu1p1,t.mu1p2,t.mu1p3)
    p1mc = vector(t.mc_mu1_px,t.mc_mu1_py,t.mc_mu1_pz)
    p2 = vector(t.mu2p1,t.mu2p2,t.mu2p3)
    p2mc = vector(t.mc_mu2_px,t.mc_mu2_py,t.mc_mu2_pz)

    Bp = p1 + p2
    Bpmc = p1mc + p2mc

    h.Fill(t.Bip_r)
    h0.Fill(dpr(PV,SV,Bpmc))
    hpe.Fill(dpr(PV,SV,Bp))





