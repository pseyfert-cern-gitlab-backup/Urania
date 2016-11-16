from ROOT import *
from Urania import *
from Urania import PDG
AccessPackage("Bs2MuMu")
from triggerclass import *
from smartpyROOT import *
from SomeUtils.alyabar import *
import TMVA_cut
from SomeUtils.TMVAoperators import *
from OurSites import MY_TUPLE_PATH as MY_PATH

#fname = MY_PATH + "KsPi0MM_dataL0Tis_GL_1"
#fname = MY_PATH + "KsPi0MM_dataL0Tis_GL_2"
#fname = MY_PATH + "kspi0mm_DTFMC12_Strip_GL_1"
fname = MY_PATH + "kspi0mm_DTFMC12_Strip_GL_2"


ch = channelData(fname)

#tup = RTuple("fit_sample",["evt/F", "M/F", "GL/F", "Mmumu/F"] + glkeys + ["LF_time/F"])
glBDT = TMVAoperatorFlat(os.environ["KS2PI0MUMUROOT"] + "/operators/BDT.C","BDT",TMVA_cut.variables_BDT,os.environ["KS2PI0MUMUROOT"] + "/operators/uf_BDT" )
glBDTG = TMVAoperatorFlat(os.environ["KS2PI0MUMUROOT"] + "/operators/BDTG.C","BDTG",TMVA_cut.variables_BDT,os.environ["KS2PI0MUMUROOT"] + "/operators/uf_BDTG")
#BREAK
for entry in ch:
    pmu1 = vector(entry['mu1p1'], entry['mu1p2'], entry['mu1p3'])
    pmu2 = vector(entry['mu2p1'], entry['mu2p2'], entry['mu2p3'])
    pg1 = vector(entry['g1p1'], entry['g1p2'], entry['g1p3'])
    pg2 = vector(entry['g2p1'], entry['g2p2'], entry['g2p3'])
    Mpizero = sqrt(IM2(pg1,pg2, 0, 0)) ## IM2 = invariant mass squared
    Mmumu = sqrt(IM2(pmu1,pmu2, PDG.muon.mass, PDG.muon.mass)) ## IM2 = invariant mass squared
     
    PV = vector(entry['PV1'],entry['PV2'],entry['PV3'])
    SV = vector(entry['SV1'],entry['SV2'],entry['SV3'])
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
    entry["Mmumu"] = Mmumu
    entry["M_VC"] = MKsb
    entry["VCGLBDTG"] = glBDTG(entry)
    entry["VCGLBDT"] = glBDT(entry)
    

#tup.close()
ch.save(fname + "_fitPlane")
t, f = getTuple(fname + "_fitPlane")
