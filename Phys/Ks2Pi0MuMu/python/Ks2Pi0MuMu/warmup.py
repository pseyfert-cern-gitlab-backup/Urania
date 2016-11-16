#!/usr/bin/env python
import os, sys
import optparse
import TMVA_cut

from ROOT import *
from Urania import *  
from random import *
from math import sqrt
import time   # time accounting
import getopt # command line parser

from SomeUtils.alyabar import *
from SomeUtils.NewKarlen import *
from SomeUtils.someFunctions import *
from SomeUtils.TMVAoperators import *

from OurSites import *
from OurSites import MY_TUPLE_PATH as MY_PATH

AccessPackage("Bs2MuMu")

from smartpyROOT import *
from triggerclass import * 

variables = TMVA_cut.variables_cont


gROOT.ProcessLine(
"struct MyStruct {\
   Float_t     structcTh1;\
   Float_t     structcTh2;\
   Float_t     structPhi;\
   Float_t     structK_dec_angle;\
   Float_t     structXi;\
   Float_t     structAlpha;\
   Float_t     structMmumu;\
   Float_t     structM_V0;\
   Float_t     structM_VC;\
};" );

def split(filename, treename, data):
    fullpath = MY_TUPLE_PATH + filename

    f = TFile(fullpath, "update")
    t = f.Get(treename)
    
    f1_name = fullpath.replace('.root', '_1.root')
    f2_name = fullpath.replace('.root', '_2.root')
    
    f1 = TFile(f1_name, "recreate")
    t1 = t.CloneTree(0)
    
    f2 = TFile(f2_name, "recreate")
    t2 = t.CloneTree(0)
    
    for entry in t:
        if int(float(data)) == 0:
            if entry.mo1 != 310 : continue
            if entry.mo2 != 310 : continue
            ## if not entry.mc_pi0_px : continue
            ## if not entry.mc_Gamma_px : continue
            ## if not entry.mc_gamma_px : continue
            ##if entry.mc_gamma_pz < 0: continue
            if(entry.mc_gamma_ez < 0): continue
            if(entry.mc_Gamma_ez < 0): continue
            ## if(entry.mc_g1_ez != entry.mc_gamma_ez and entry.mc_g1_ez != entry.mc_Gamma_ez): continue
            ## if(entry.mc_g2_ez != entry.mc_gamma_ez and entry.mc_g2_ez != entry.mc_Gamma_ez): continue                                   

        rand = randint(0,1)
        if rand == 0:
            t1.Fill()
        else:
            t2.Fill()

    #t.Write("",TObject.kOverwrite)
    f1.Write()
    f2.Write()

    f1.Close()
    f2.Close()
    f.Close()

def angles_and_masses(filename, treename, sample):
    SAMPLE = int(float(sample))
    fullpath = MY_TUPLE_PATH + filename
        
    f = TFile(fullpath, "update")
 
    t = f.Get(treename)

    mystruct = MyStruct()
    
    branch_cTh1 = t.Branch("cTh1", AddressOf(mystruct, "structcTh1"), "cTh1/F")
    branch_cTh2 = t.Branch("cTh2", AddressOf(mystruct, "structcTh2"), "cTh2/F")
    branch_Phi = t.Branch("Phi", AddressOf(mystruct, "structPhi"), "Phi/F")
    branch_K_dec_angle = t.Branch("K_dec_angle", AddressOf(mystruct, "structK_dec_angle"), "K_dec_angle/F")
    branch_Xi = t.Branch("Xi", AddressOf(mystruct, "structXi"), "Xi/F")
    branch_Alpha = t.Branch("Alpha", AddressOf(mystruct, "structAlpha"), "Alpha/F")
    branch_Mmumu = t.Branch("Mmumu", AddressOf(mystruct, "structMmumu"), "Mmumu/F")
    branch_M_V0 = t.Branch("M_V0", AddressOf(mystruct, "structM_V0"), "M_V0/F")
    branch_M_VC = t.Branch("M_VC", AddressOf(mystruct, "structM_VC"), "M_VC/F")

    for entry in t:

        pmu1 = vector(entry.mu1p1, entry.mu1p2, entry.mu1p3)
        pmu2 = vector(entry.mu2p1, entry.mu2p2, entry.mu2p3)
         
        PM1 = TLorentzVector(pmu1[0],pmu1[1],pmu1[2], sqrt(vdot(pmu1,pmu1) + PDG.muon.mass**2))
        PM2 = TLorentzVector(pmu2[0],pmu2[1],pmu2[2], sqrt(vdot(pmu2,pmu2) + PDG.muon.mass**2))
        
        if SAMPLE == 0:
            pg1 = vector(entry.g1p1, entry.g1p2, entry.g1p3)
            pg2 = vector(entry.g2p1, entry.g2p2, entry.g2p3)
            p0 = pg1 + pg2
  
            PG1 = TLorentzVector(pg1[0],pg1[1],pg1[2], vmod(pg1))
            PG2 = TLorentzVector(pg2[0],pg2[1],pg2[2], vmod(pg2))
            
        else:
            PG1 = TLorentzVector(0,0,0,0)
            PG2 = TLorentzVector(0,0,0,0)
            p0 = vector(0,0,0)
        
        cTh1_evt, cTh2_evt, Phi_evt = HelicityAngles(PG1,PG2,PM1,PM2)
        
        mystruct.structcTh1 = cTh1_evt
        mystruct.structcTh2 = cTh2_evt
        mystruct.structPhi = Phi_evt
        
        Mmumu = sqrt(IM2(pmu1,pmu2, PDG.muon.mass, PDG.muon.mass)) 
        mystruct.structMmumu = Mmumu
        
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
        
        if SAMPLE == 0:
            p0z_primeVC = psqrt(vdot(p0,p0) -pdmy_prime**2 -pdmx_prime**2)   ### VC option: preserve the absolute value of the momentum
            p0_prime = vector(-pdmx_prime, -pdmy_prime, p0z_primeVC)
            M_VC = sqrt(IM2(pm_prime, p0_prime, Mmumu, PDG.pi0.mass))# Mpizero
            mystruct.structM_VC = M_VC
            mystruct.structM_V0 = 0
            
        if SAMPLE == 1:
            p0z_const = vector(-pdmx_prime, -pdmy_prime, 8900)
            M_V0 = sqrt(IM2(pm_prime, p0z_const, Mmumu, PDG.pi0.mass))
            mystruct.structM_V0 = M_V0
            mystruct.structM_VC = 0
        
        v1 = [vmod(p0), p0]
        v2 = [sqrt(Mmumu**2+vdot(pdm,pdm)), pdm]
        
        mystruct.structK_dec_angle = angleToflight(v1,v2)
        
        BigPi = vcross(pdm, p0)
        mystruct.structXi = ACO(flight, BigPi)
        
        mystruct.structAlpha = ACO(flight, pdm+p0)        
        
        branch_cTh1.Fill()
        branch_cTh2.Fill()
        branch_Phi.Fill()
        branch_K_dec_angle.Fill()
        branch_Xi.Fill()
        branch_Alpha.Fill()
        branch_Mmumu.Fill()
        branch_M_V0.Fill()
        branch_M_VC.Fill()
        
    t.Write("",TObject.kOverwrite)
        
    f.Write()
    f.Close()


def main():
    parser = optparse.OptionParser()
    parser.add_option('-i', '--input', dest='input', help='input root file', default='./kspi0mm_DTFMC12_Strip_2.root')
    parser.add_option('-t', '--tree', dest='tree', help='name of the ROOT tree inside the ROOT file', default='BenderKspi0mumuSignal')
    parser.add_option('-s', '--sample', dest="sample", help='input sample - 0 with pi0, 1 without pi0 (V0)', default=1)    
    parser.add_option('-d', '--data', dest="data", help='input type - 0 for MC, 1 for data', default=0)    
    
    (options, args) = parser.parse_args()
    
    angles_and_masses(options.input, options.tree, options.sample)    
    split(options.input, options.tree, options.data)

if __name__ == "__main__":
    main() 
