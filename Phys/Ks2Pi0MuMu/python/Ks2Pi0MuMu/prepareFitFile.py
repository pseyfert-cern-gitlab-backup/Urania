from ROOT import *
from Urania import *
from Urania import PDG
AccessPackage("Bs2MuMu")
from triggerclass import *
from smartpyROOT import *
from SomeUtils.alyabar import *
import TMVA_cut
##import TMVA_cut_conf4
from SomeUtils.TMVAoperators import *
from OurSites import MY_TUPLE_PATH as MY_PATH
import os, sys

SAMPLE =  0#int(float(sys.argv[1]))

print SAMPLE

while SAMPLE != 0 and SAMPLE != 1:
    SAMPLE = int(float(raw_input("Please provide an argument of 0 (with pi0) or 1 (no pi0):")))
    print SAMPLE
    
#fname = MY_PATH + "TIS_GL_1"
#fname = MY_PATH + "TIS_GL_2"
#fname = MY_PATH + "kspi0mm_DTFMC12_Strip_GL_1"
#fname = MY_PATH + "kspi0mm_DTFMC12_Strip_GL_2"
fname = "/scratch18/Kspi0/MC12_Sim09_K3pi_FULL_Up"
#BREAK
tname = "BenderKspi0mumuSignal/BenderKspi0mumuSignal"
ch = channelData(fname, name2 = tname)
fname = "/scratch18/Kspi0/MC12_Sim09_K3pi_FULL_Down"
ch += channelData(fname, name2 = tname)
ch = channelData(ch)
#tup = RTuple("fit_sample",["evt/F", "M/F", "GL/F", "Mmumu/F"] + glkeys + ["LF_time/F"])
#UNCOMMENT glBDT = TMVAoperatorFlat(os.environ["KS2PI0MUMUROOT"] + "/operators/BDT.C","BDT",TMVA_cut.variables_BDT,os.environ["KS2PI0MUMUROOT"] + "/operators/uf_BDT" )
#UNCOMMENT glBDTG = TMVAoperatorFlat(os.environ["KS2PI0MUMUROOT"] + "/operators/BDTG.C","BDTG",TMVA_cut.variables_BDT,os.environ["KS2PI0MUMUROOT"] + "/operators/uf_BDTG")

for entry in ch:
    #if entry['mo1'] != 310 : continue
    #if entry['mo2'] != 310 : continue
    ## if not entry['mc_pi0_px'] : continue
    ## if not entry['mc_Gamma_px'] : continue
    #if not entry.mc_Gamma_py : continue
    #if not entry.mc_Gamma_pz : continue
    ## if not entry['mc_gamma_px'] : continue
    #if not entry.mc_gamma_py : continue
    ## if entry['mc_gamma_pz'] < 0: continue
    #if(entry['mc_gamma_ez'] < 0): continue
    #if(entry['mc_Gamma_ez'] < 0): continue

    pmu1 = vector(entry['mu1p1'], entry['mu1p2'], entry['mu1p3'])
    pmu2 = vector(entry['mu2p1'], entry['mu2p2'], entry['mu2p3'])
    Mmumu = sqrt(IM2(pmu1,pmu2, PDG.muon.mass, PDG.muon.mass)) ## IM2 = invariant mass squared
    Mpipi = sqrt(IM2(pmu1,pmu2, PDG.piplus.mass, PDG.piplus.mass))
    PV = vector(entry['PV1'],entry['PV2'],entry['PV3'])
    SV = vector(entry['SV1'],entry['SV2'],entry['SV3'])
    flight = vunit(SV-PV)
    
    pdm = pmu1 + pmu2
    xu = vcross(vector(0,1,0),flight)
    yu = vcross(flight,xu)
    pdmx_prime = vdot(pdm, xu)
    pdmy_prime = vdot(pdm, yu)
    pdmz_prime = vdot(pdm, flight)
    pm_prime = vector(pdmx_prime, pdmy_prime, pdmz_prime)

    entry["Mmumu"] = Mmumu
    entry["Mpipi"] = Mmumu

    #UNCOMMENT entry["VCGLBDTG"] = glBDTG(entry)
    #UNCOMMENT entry["VCGLBDT"] = glBDT(entry) 
        
    if SAMPLE == 0:
        pg1 = vector(entry['g1p1'], entry['g1p2'], entry['g1p3'])
        pg2 = vector(entry['g2p1'], entry['g2p2'], entry['g2p3'])
        Mpizero = sqrt(IM2(pg1,pg2, 0, 0)) ## IM2 = invariant mass squared
        p0 = pg1 + pg2    
        #p0z_prime = vdot(p0, flight)  ### DMS option: just project and live with it
        p0z_primeVC = psqrt(vdot(p0,p0) -pdmy_prime**2 -pdmx_prime**2)   ### VC option: preserve the absolute value of the momentum
        #p0_prime = vector(-pdmx_prime, -pdmy_prime, p0z_prime)
        #MKsb = sqrt(IM2 ( pm_prime,  p0_prime, Mmumu, PDG.pi0.mass))# Mpizero))
        #hb.Fill(MKsb)
        p0_prime = vector(-pdmx_prime, -pdmy_prime, p0z_primeVC)
        MKsb = sqrt(IM2(pm_prime, p0_prime, Mmumu, PDG.pi0.mass))# Mpizero
        entry["M_VC"] = MKsb
            

    if SAMPLE == 1:
        p0z_const = vector(-pdmx_prime, -pdmy_prime, 8900)
        MK_nopi0 = sqrt(IM2(pm_prime, p0z_const, Mmumu, PDG.pi0.mass))
        entry["M_V0"] = MK_nopi0

#tup.close()
fname = "K3piFULL"
ch.save(fname + "_fitPlane_basic")
t, f = getTuple(fname + "_fitPlane_basic")
#t.Draw("M_VC:Mpipi", "mo1 ==310 && mo2 == 310 && rmo1key==rmo2key")
t.Draw("M_VC", "mo1 ==310 && mo2 == 310 && rmo1key==rmo2key && M_VC>420 && M_VC<580")
