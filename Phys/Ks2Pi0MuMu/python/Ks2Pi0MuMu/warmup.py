#!/usr/bin/env python
import os, sys
import optparse
#import TMVA_cut_conf4 as TMVA_cut
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

#from OurSites import *
#from OurSites import MY_TUPLE_PATH as MY_PATH

AccessPackage("Bs2MuMu")

from smartpyROOT import *
from triggerclass import * 

variables = TMVA_cut.variables_cont

mycutSig = TMVA_cut.mycutSig_nopi0 
mycutBkg = TMVA_cut.mycutBkg_nopi0 

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

MY_TUPLE_PATH = "./"
MY_PATH = "./"

def split(filename, treename, sample, mc, tistos):
    fullpath = filename

    f = TFile(fullpath, "update")
    t = f.Get(treename)

    f1_name = fullpath.replace('.root', '_1.root')
    f2_name = fullpath.replace('.root', '_2.root')

    if(int(sample)==0):
        cuts = mycutBkg + "&& abs(mc1)==13 && abs(mc2)==13 && mo1==310 && mo2 == 310 && rmo1key==rmo2key"*int(float(mc)) + "&&KS_l0phys_tis && KS_l1phys_tis && KS_l2phys_tis"*int(float(tistos))
    else:
        cuts = mycutBkg + "&& abs(mc1)==13 && abs(mc2)==13 && mo1==310 && mo2 == 310 && rmo1key==rmo2key"*int(float(mc)) + "&&V0_l0phys_tis && V0_l1phys_tis && V0_l2phys_tis"*int(float(tistos))
    
    f1 = TFile(f1_name, "recreate")
    t1 = t.CopyTree("(evt%2) && " + cuts)#&&KS_l0phys_tis && KS_l1phys_tis && KS_l2phys_tis")
    t1.Write()
    f1.Close()
    
    f2 = TFile(f2_name, "recreate")
    t2 = t.CopyTree("!(evt%2) && " + cuts)#&&KS_l0phys_tis && KS_l1phys_tis && KS_l2phys_tis")
    t2.Write()
    f2.Close()

    f.Close()
    f1.Close()
    f2.Close()

#    angles_and_masses(f1_name, treename, sample)
#    angles_and_masses(f2_name, treename, sample)

def angles_and_masses(filename, treename, sample):
    SAMPLE = int(float(sample))
    fullpath = filename

    f = TFile(fullpath, "update")
 
    t = f.Get(treename)
    print "t=",t

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

    i=0
    
    for entry in t:
        i+=1
        print i
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
    parser.add_option('-i', '--input', dest='input', help='input root file', default='./Data_2016_PARTIAL.root')
    parser.add_option('-t', '--tree', dest='tree', help='name of the ROOT tree inside the ROOT file', default='Ks2pizeromm_as_V0/Ks2pizeromm_as_V0')
    parser.add_option('-s', '--sample', dest="sample", help='input sample - 0 with pi0, 1 without pi0 (V0)', default=1)    
    parser.add_option('-m', '--mc', dest="mc", help='input type - 1 for MC, 0 for data', default=0)    
    parser.add_option('-c', '--tistos', dest="tistos", help='tistos events - 0 without cut, 1 with cut', default=1)
    
    (options, args) = parser.parse_args()

    tree_head, tree_sep, tree_tail = options.tree.partition("/")
    
    angles_and_masses(options.input, options.tree, options.sample)
    print "ANGLES DONE"
    split(options.input, tree_head, options.sample, options.mc, options.tistos)
    print "SPLITTING DONE"
#angles_and_masses("K3pi_stp.root", "T", 0 )#, optio
#angles_and_masses("/scratch19/Kspi0/Gorda_FULL_2.root", "BenderKspi0mumuSignal", 0 )#, optio
#    angles_and_masses(options.input, options.tree, options.sample)

if __name__ == "__main__":
    main() 
