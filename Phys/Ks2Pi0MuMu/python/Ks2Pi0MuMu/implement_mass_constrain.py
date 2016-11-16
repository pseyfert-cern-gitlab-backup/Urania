from ROOT import *
from Urania import *
from Urania import PDG
AccessPackage("Bs2MuMu")
from RTuple import *
from smartpyROOT import *
from SomeUtils.alyabar import *
t, f = getTuple("test_sample")
#t, f      = getTuple("/scratch19/Kspi0/KsPi0MM_dataL0Tis_1")
kPaula = TColor.GetColor("#ff99cc")
import cPickle
GL = cPickle.load(file("./GL_data","r"))
glkeys = []
for key in GL.keys: glkeys.append(key + "/F")
tup = RTuple("fit_sample",["evt/F", "M/F", "GL/F", "Mmumu/F", "Mpipi/F","KSmass/F", "SVX/F","SVZ/F", "SVY/F"] + glkeys + ["LF_time/F"])

#BREAK
for entry in t:
    pmu1 = vector(entry.mu1p1, entry.mu1p2, entry.mu1p3)
    pmu2 = vector(entry.mu2p1, entry.mu2p2, entry.mu2p3)
    pg1 = vector(entry.g1p1, entry.g1p2, entry.g1p3)
    pg2 = vector(entry.g2p1, entry.g2p2, entry.g2p3)
    Mpizero = sqrt(IM2(pg1,pg2, 0, 0)) ## IM2 = invariant mass squared
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

    p0 = pg1 + pg2
    #p0z_prime = vdot(p0, flight)  ### DMS option: just project and live with it
    p0z_primeVC = psqrt(vdot(p0,p0) -pdmy_prime**2 -pdmx_prime**2)   ### VC option: preserve the absolute value of the momentum

    pm_prime = vector(pdmx_prime, pdmy_prime, pdmz_prime)
    #p0_prime = vector(-pdmx_prime, -pdmy_prime, p0z_prime)
    #MKsb = sqrt(IM2 ( pm_prime,  p0_prime, Mmumu, PDG.pi0.mass))# Mpizero))
    #hb.Fill(MKsb)
    p0_prime = vector(-pdmx_prime, -pdmy_prime, p0z_primeVC)
    MKsb = sqrt(IM2 ( pm_prime,  p0_prime, Mmumu, PDG.pi0.mass))# Mpizero
    tup.fillItem("evt", t.evt)
    tup.fillItem("M", MKsb)
    for key in GL.keys: tup.fillItem(key, getattr(t, key))
    tup.fillItem("LF_time", t.LF_time)
    tup.fillItem("Mmumu", Mmumu)
    tup.fillItem("Mpipi", psqrt(IM2(pmu1,pmu2, PDG.piplus.mass,PDG.piplus.mass)))
    tup.fillItem("GL", getattr(t, "GLmvasb."))
    tup.fillItem("SVX", t.SV1)
    tup.fillItem("SVY", t.SV2)
    tup.fillItem("SVZ", t.SV3)
    tup.fillItem("KSmass", t.KSmass)
    tup.fill()

tup.close()
t, f = getTuple("fit_sample")
t.Draw("SVY:SVZ", "M> 400 && M<600 && LF_time >50")
