from ROOT import *
f = TFile("/home3/veronika.chobanova/Kspi0/kspi0mumu_ntupleMC12_Up_V0_1_GL.root")
t = f.Get("T")
kPaula = TColor.GetColor("#ff99cc")
#f = TFile("bkgMini.root")
#t = f.Get("BenderKspi0mumuSignal/BenderKspi0mumuSignal")
#BREAK
from SomeUtils.alyabar import *
from Urania import PDG
fh = TFile("Masshistos_nopi0.root", "recreate")
h = TH1F("A","A", 100, 400, 600)
hb = TH1F("B","B", 100, 400, 600)
hbVC = TH1F("BVC","BVC", 100, 400, 600)
phantom = TH1F("phantom","phantom", 100, 400, 600)
plist = range(5,9) + [8.1 + 0.1*i for i in range(19)] + range(10,16)
plist.sort()
h_phantom = {}
for p in plist:
    h_phantom[p] = TH1F(str(p),str(p), 100, 400, 600)
href = TH1F("ref","ref", 100, 400, 600)
hDTF = TH1F("DTF","DTF", 100, 400, 600)
hDTFcl = TH1F("DTFcl","DTFcl", 100, 400, 600)
hpi0 = TH1F("pi0", "pi0", 100, 100, 170)
#BREAK
for entry in t:
    if entry.mo1 != 310 : continue
    if entry.mo2 != 310 : continue
     
    #if not entry.mc_pi0_px: continue
    pmu1 = vector(entry.mu1p1, entry.mu1p2, entry.mu1p3)
    pmu2 = vector(entry.mu2p1, entry.mu2p2, entry.mu2p3)
    Mmumu = sqrt(IM2(pmu1,pmu2, PDG.muon.mass, PDG.muon.mass)) ## IM2 = invariant mass squared
    
    PV = vector(entry.PV1,entry.PV2,entry.PV3)
    SV = vector(entry.SV1,entry.SV2,entry.SV3)
    flight = vunit(SV-PV)
    pdm = pmu1 + pmu2
    xu = vcross(vector(0,1,0),flight)
    yu = vcross(flight,xu)
    pdmx_prime = vdot(pdm, xu)
    pdmy_prime = vdot(pdm, yu)
    pdmz_prime = vdot(pdm, flight)

   
    pm_prime = vector(pdmx_prime, pdmy_prime, pdmz_prime)
  
    for mypz in plist:
        p0_prime = vector(-pdmx_prime, -pdmy_prime, 1000*mypz)
        MKsb = sqrt(IM2 ( pm_prime,  p0_prime, Mmumu, PDG.pi0.mass))# Mpizero))
        h_phantom[mypz].Fill(MKsb)
        if(mypz==8.9):
            print "reached the chosen pz"
            hbVC.Fill(MKsb)
    ##hDTF.Fill(entry.Ksmass_DTF)
    ##hDTFcl.Fill(entry.Ksmass_DTF_classic)

c = TCanvas()
h_phantom[plist[0]].Draw()
for p in plist[1:]:
    h_phantom[p].SetLineColor(int(p*10))
    print p, h_phantom[p].GetRMS()
    h_phantom[p].Draw("same")

##Write missing: hwhatever.Write()
hbVC.Write()
