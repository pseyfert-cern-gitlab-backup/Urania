from ROOT import *
f = TFile("~/cmtuser/local_Ks2Pi0MuMu/kspi0mm_DTFMC12_Strip_march2016_GL_1_conf2_fitPlane_conf2.root")
t = f.Get("T")
kPaula = TColor.GetColor("#ff99cc")
#f = TFile("bkgMini.root")
#t = f.Get("BenderKspi0mumuSignal/BenderKspi0mumuSignal")
#BREAK
from SomeUtils.alyabar import *
from Urania import PDG
fh = TFile("Masshistos.root", "recreate")
h = TH1F("A","A", 100, 400, 600)
hb = TH1F("B","B", 100, 400, 600)
hbVC = TH1F("BVC","BVC", 100, 400, 600)
phantom = TH1F("phantom","phantom", 100, 400, 600)
plist = range(7,15)
h_phantom = {}
for p in plist:
    h_phantom[p] = TH1F(str(p),str(p), 100, 400, 600)
href = TH1F("ref","ref", 100, 400, 600)
hDTF = TH1F("DTF","DTF", 100, 400, 600)
hDTFcl = TH1F("DTFcl","DTFcl", 100, 400, 600)
hpi0 = TH1F("pi0", "pi0", 100, 100, 170)
#BREAK
for entry in t:
    #if entry.mo1 != 310 : continue
    #if entry.mo2 != 310 : continue
    #if entry.mc_g1_ez != entry.mc_gamma_ez and entry.mc_g1_ez != entry.mc_Gamma_ez: continue
    #if entry.mc_g2_ez != entry.mc_gamma_ez and entry.mc_g2_ez != entry.mc_Gamma_ez: continue
    
    #if not entry.mc_pi0_px: continue
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

    for mypz in plist:
        p0_prime = vector(-pdmx_prime, -pdmy_prime, 1000*mypz)
        MKsb = sqrt(IM2 ( pm_prime,  p0_prime, Mmumu, PDG.pi0.mass))# Mpizero))
        h_phantom[p].Fill(MKsb)
    
    hDTF.Fill(entry.Ksmass_DTF)
    hDTFcl.Fill(entry.Ksmass_DTF_classic)

hb.SetLineColor(kBlack)
hb.SetLineWidth(3)
hb.Draw()

#h.SetLineColor(kRed)
#h.Draw("same")
#href.Draw("same")

#hbVC.SetLineColor(kPaula)
#hbVC.Draw("same")
hDTF.SetLineColor(kBlue)
hDTF.Draw("same")
#hDTFcl.SetLineColor(kCyan)
#hDTFcl.Draw("same")
#phantom.SetLineColor(kOrange)
#phantom.Draw("same")
   
hbVC.Write()

#fh.Close()    
    
    
