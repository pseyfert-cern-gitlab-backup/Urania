'''
from ROOT import *
from os import *
import getSelEff as E
E.getBsmmEff()
'''

from ROOT import *
from os import *
import GaudiKernel.SystemOfUnits as units
from efficiencyRatio import *

#for hte 1fb paper
fTrMap=TFile("$TAU23MUROOT/params/TrackingEffMap_Mc10-stp13b_v2_2011_chi4.root")
hRatio2011 = fTrMap.Get("Ratio")

# Create a new histogram with the spectrum from the MC
hSpectrumMC = hRatio2011.Clone("SpectrumMC")
hSpectrumMC.Reset()
year = "2011"
t=TCanvas()

def getDsOverTau():

    eTau, erTau = getEffTau(t)
    eDs,erDs = getEffDs(t)

    R_tot=eDs/eTau
    eR_tot=sqrt((erDs/eDs)**2+(erTau/eTau)**2)
    print "Ds / tau tot: ",R_tot," +- ",eR_tot

    return R_tot, eR_tot


def getEffTau(tc):

    fBs2mm = TFile("/afs/cern.ch/project/lbcern/vol2/albrecht/Bs2mm/JA_ntuples/tau23mu/mctru_tau23mu_mud_BDTv3e2_flatV4.root")
    tsm = fBs2mm.Get("Tau23Mu")

    for entry in tsm:
        p=getattr(tsm,"p0_p")/1000.
        eta=getattr(tsm,"p0_eta")
        hSpectrumMC.Fill(p, eta)
    

    tc.cd(1)
    hSpectrumMC.DrawNormalized("colz")

    R_mu1 = totalEfficiencyRatioFromSpectrum(hSpectrumMC, year)
    eR_mu1 = totalStatErrorFromSpectrum(hSpectrumMC, year)        
    print "mu1 : ",R_mu1," +- ",eR_mu1

    hSpectrumMC.Reset()
  
    for entry in tsm:
        p=getattr(tsm,"p1_p")/1000.
        eta=getattr(tsm,"p1_eta")
        hSpectrumMC.Fill(p, eta)


    tc.cd(2)
    hSpectrumMC.DrawNormalized("colz")
    R_mu2 = totalEfficiencyRatioFromSpectrum(hSpectrumMC, year)
    eR_mu2 = totalStatErrorFromSpectrum(hSpectrumMC, year)        
    print "mu2 : ",R_mu2," +- ",eR_mu2


    hSpectrumMC.Reset()
  
    for entry in tsm:
        p=getattr(tsm,"p2_p")/1000.
        eta=getattr(tsm,"p2_eta")
        hSpectrumMC.Fill(p, eta)


    tc.cd(3)
    hSpectrumMC.DrawNormalized("colz")
    R_mu3 = totalEfficiencyRatioFromSpectrum(hSpectrumMC, year)
    eR_mu3 = totalStatErrorFromSpectrum(hSpectrumMC, year)        
    print "mu3 : ",R_mu3," +- ",eR_mu3


    R_tot=R_mu1*R_mu2*R_mu3
    eR_tot=sqrt((eR_mu1/R_mu1)**2+(eR_mu2/R_mu2)**2+(eR_mu3/R_mu3)**2)
    print "tot: ",R_tot," +- ",eR_tot

    return R_tot, eR_tot


def getEffDs(tc):

    f = TFile("/afs/cern.ch/project/lbcern/vol2/albrecht/Bs2mm/JA_ntuples/tau23mu/mctru_ds2phipi_mud_BDTv3e2_flatV4.root")
    tsm = f.Get("Ds2PhiPi")

    for entry in tsm:
        p=getattr(tsm,"p0_p")/1000.
        eta=getattr(tsm,"p0_eta")
        hSpectrumMC.Fill(p, eta)
    
    tc.cd(1)
    hSpectrumMC.DrawNormalized("colz")
    R_mu1 = totalEfficiencyRatioFromSpectrum(hSpectrumMC, year)
    eR_mu1 = totalStatErrorFromSpectrum(hSpectrumMC, year)        
    print "mu1 : ",R_mu1," +- ",eR_mu1

    hSpectrumMC.Reset()
    for entry in tsm:
        p=getattr(tsm,"p1_p")/1000.
        eta=getattr(tsm,"p1_eta")
        hSpectrumMC.Fill(p, eta)
  

    tc.cd(2)
    hSpectrumMC.DrawNormalized("colz")
    R_mu2 = totalEfficiencyRatioFromSpectrum(hSpectrumMC, year)
    eR_mu2 = totalStatErrorFromSpectrum(hSpectrumMC, year)        
    print "mu2 : ",R_mu2," +- ",eR_mu2

    hSpectrumMC.Reset()
    for entry in tsm:
        p=getattr(tsm,"p2_p")/1000.
        eta=getattr(tsm,"p2_eta")
        hSpectrumMC.Fill(p, eta)
  
    tc.cd(3)
    hSpectrumMC.DrawNormalized("colz")
    R_k = totalEfficiencyRatioFromSpectrum(hSpectrumMC, year)
    eR_k = totalStatErrorFromSpectrum(hSpectrumMC, year)        
    print "k : ",R_k," +- ",eR_k

    R_tot=R_mu1*R_mu2*R_k
    eR_tot=sqrt((eR_mu1/R_mu1)**2+(eR_mu2/R_mu2)**2+(eR_k/R_k)**2)
    print "tot: ",R_tot," +- ",eR_tot

    return R_tot, eR_tot


def getEffBsJPsiPhi(tc):

    f = TFile(environ["HOME"] +"/NTuples/smearMC_2011EPS/v4_noSMEAR_STDPARTICLES_dbg_10k_Bs2JPsiPhi_sm0.0.root")
    tsm = f.Get("Bs2JPsiPhi/Bs2JPsiPhi")

    for entry in tsm:
        p=getattr(tsm,"mu1ptot")/1000.
        eta=getattr(tsm,"mu1_eta")
        hSpectrumMC.Fill(p, eta)
    
    tc.cd(1)
    hSpectrumMC.DrawNormalized("colz")
    R_mu1 = totalEfficiencyRatioFromSpectrum(hSpectrumMC, year)
    eR_mu1 = totalStatErrorFromSpectrum(hSpectrumMC, year)        
    print "mu1 : ",R_mu1," +- ",eR_mu1

    hSpectrumMC.Reset()
    for entry in tsm:
        p=getattr(tsm,"mu2ptot")/1000.
        eta=getattr(tsm,"mu2_eta")
        hSpectrumMC.Fill(p, eta)
  
    tc.cd(2)
    hSpectrumMC.DrawNormalized("colz")
    R_mu2 = totalEfficiencyRatioFromSpectrum(hSpectrumMC, year)
    eR_mu2 = totalStatErrorFromSpectrum(hSpectrumMC, year)        
    print "mu2 : ",R_mu2," +- ",eR_mu2

    hSpectrumMC.Reset()
    for entry in tsm:
        p=getattr(tsm,"k1ptot")/1000.
        eta=getattr(tsm,"k1_eta")
        hSpectrumMC.Fill(p, eta)
  
    R_k1 = totalEfficiencyRatioFromSpectrum(hSpectrumMC, year)
    eR_k1 = totalStatErrorFromSpectrum(hSpectrumMC, year)        
    print "k1 : ",R_k1," +- ",eR_k1

    tc.cd(3)
    hSpectrumMC.DrawNormalized("colz")
    hSpectrumMC.Reset()
    for entry in tsm:
        p=getattr(tsm,"k2ptot")/1000.
        eta=getattr(tsm,"k2_eta")
        hSpectrumMC.Fill(p, eta)
  
    tc.cd(4)
    hSpectrumMC.DrawNormalized("colz")
    R_k2 = totalEfficiencyRatioFromSpectrum(hSpectrumMC, year)
    eR_k2 = totalStatErrorFromSpectrum(hSpectrumMC, year)        
    print "k2 : ",R_k2," +- ",eR_k2

    R_tot=R_mu1*R_mu2*R_k1*R_k2
    eR_tot=sqrt((eR_mu1/R_mu1)**2+(eR_mu2/R_mu2)**2+(eR_k1/R_k1)**2+(eR_k2/R_k2)**2)
    print "tot: ",R_tot," +- ",eR_tot

    return R_tot, eR_tot


def getEffBhh(tc=0):

    fBs2mm = TFile(environ["HOME"] +"/NTuples/smearMC_2011EPS/v4_dbg_10k_B2Kpi_sm0.root")
    tsm = fBs2mm.Get("B2hh/B2hh")

    for entry in tsm:
        p=getattr(tsm,"mu1ptot")/1000.
        eta=getattr(tsm,"mu1_eta")
        hSpectrumMC.Fill(p, eta)
    
    #tc.cd()
    #hSpectrumMC.Draw("colz")
    tc.cd(1)
    hSpectrumMC.DrawNormalized("colz")
    R_mu1 = totalEfficiencyRatioFromSpectrum(hSpectrumMC, year)
    eR_mu1 = totalStatErrorFromSpectrum(hSpectrumMC, year)        
    print "mu1 : ",R_mu1," +- ",eR_mu1

    hSpectrumMC.Reset()
  
    for entry in tsm:
        p=getattr(tsm,"mu2ptot")/1000.
        eta=getattr(tsm,"mu2_eta")
        hSpectrumMC.Fill(p, eta)
  
    tc.cd(2)
    hSpectrumMC.DrawNormalized("colz")
    R_mu2 = totalEfficiencyRatioFromSpectrum(hSpectrumMC, year)
    eR_mu2 = totalStatErrorFromSpectrum(hSpectrumMC, year)        
    print "mu2 : ",R_mu2," +- ",eR_mu2

    R_tot=R_mu1*R_mu2
    eR_tot=sqrt((eR_mu1/R_mu1)**2+(eR_mu2/R_mu2)**2)
    print "tot: ",R_tot," +- ",eR_tot

    return R_tot, eR_tot
