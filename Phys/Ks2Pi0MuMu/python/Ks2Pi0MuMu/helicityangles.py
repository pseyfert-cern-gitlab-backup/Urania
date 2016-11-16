from ROOT import *
f = TFile("kspi0mm_MC.root")
t = f.Get("T")
kPaula = TColor.GetColor("#ff99cc")
f = TFile("bkgMini.root")
t = f.Get("BenderKspi0mumuSignal/BenderKspi0mumuSignal")
#BREAK
from SomeUtils.alyabar import *
from Urania import PDG

h = TH1F("A","A", 100, 400, 600)
hb = TH1F("B","B", 100, 400, 600)
hbVC = TH1F("BVC","BVC", 100, 400, 600)

href = TH1F("A","A", 100, 400, 600)
hpi0 = TH1F("pi0", "pi0", 100, 100, 170)
hTh1 = TH1F("c1","c1", 100, -1,1)
hTh2 = TH1F("c2","c2", 100, -1,1)
hPhi = TH1F("phi","phi", 100, -pi,pi)

for entry in t:
#    if entry.mo1 != 310 : continue
#    if entry.mo2 != 310 : continue
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
    
    PV = vector(entry.PV1,entry.PV2,entry.PV3)
    SV = vector(entry.SV1,entry.SV2,entry.SV3)
    flight = vunit(SV-PV)
    pdm = pmu1 + pmu2
    xu = vcross(vector(0,1,0),flight)
    yu = vcross(flight,xu)
    pdmx_prime = vdot(pdm, xu)
    pdmy_prime = vdot(pdm, yu)
    pdmz_prime = vdot(pdm, flight)

    p0 = pg1 + pg2
    p0z_prime = vdot(p0, flight)  ### DMS option: just project and live with it
    p0z_primeVC = sqrt(vdot(p0,p0) -pdmy_prime**2 -pdmx_prime**2)   ### VC option: preserve the absolute value of the momentum

    pm_prime = vector(pdmx_prime, pdmy_prime, pdmz_prime)
    p0_prime = vector(-pdmx_prime, -pdmy_prime, p0z_prime)
    MKsb = sqrt(IM2 ( pm_prime,  p0_prime, Mmumu, PDG.pi0.mass))# Mpizero))
    hb.Fill(MKsb)
    p0_prime = vector(-pdmx_prime, -pdmy_prime, p0z_primeVC)
    MKsb = sqrt(IM2 ( pm_prime,  p0_prime, Mmumu, PDG.pi0.mass))# Mpizero))
    hbVC.Fill(MKsb)

    
    ### Helicity angles now. For the moment I use uncorrected momenta
    PG1 = TLorentzVector(pg1[0],pg1[1],pg1[2], vmod(pg1))
    PG2 = TLorentzVector(pg2[0],pg2[1],pg2[2], vmod(pg2))
    
    PM1 = TLorentzVector(pmu1[0],pmu1[1],pmu1[2], sqrt(vdot(pmu1,pmu1) + PDG.muon.mass**2))
    PM2 = TLorentzVector(pmu2[0],pmu2[1],pmu2[2], sqrt(vdot(pmu2,pmu2) + PDG.muon.mass**2))

    cTh1, cTh2, Phi = HelicityAngles(PG1,PG2,PM1,PM2)

    hTh1.Fill(cTh1)
    hTh2.Fill(cTh2)
    hPhi.Fill(Phi)

c = TCanvas()
c.Divide(2,2)
c.cd(1)
hTh1.Draw()
c.cd(2)
hTh2.Draw()
c.cd(3)
hPhi.Draw()
