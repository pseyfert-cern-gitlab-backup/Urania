#!/usr/bin/env python

from ROOT import *
from math import *
import os,sys

decay = sys.argv[1]

names = { "DsPi"       : "BsDsPi"
         ,"BsMuMu"     : "BsMuMu"
         ,"BdPiMuNu"   : "BdPiMuNu"
         ,"BsKMuNu"    : "BsKMuNu"
         ,"LbPMuNu"    : "LbPMuNu"
         ,"BuPiMuMu"   : "BuPiMuMu"
         ,"BcJpsiMuNu" : "BcJpsiMuNu" 
         ,"Comb"       : "CombBkg"
        }

path = "/afs/cern.ch/user/r/rvazquez/RemoveCombBkg/DaVinciDev_v42r3/"

files = { "DsPi"       : "photonControl.root"
         ,"BsMuMu"     : "TestsigMC16.root" 
         ,"BdPiMuNu"   : "Testpimunu.root"
         ,"BsKMuNu"    : "Testkmunu.root"
         ,"LbPMuNu"    : "Testlambda.root"
         ,"BuPiMuMu"   : "Testpimumu.root"
         ,"BcJpsiMuNu" : "Testbc.root"
         ,"Comb"       : "TestcombLowPT.root"
        }

trees = { "DsPi"       : "B2DsMuNuTuple/" 
         ,"BsMuMu"     : ""
         ,"BdPiMuNu"   : ""
         ,"BsKMuNu"    : ""
         ,"LbPMuNu"    : ""
         ,"BuPiMuMu"   : ""
         ,"BcJpsiMuNu" : "" 
         ,"Comb"       : ""
        }

minranges = { "DsPi"       : 5100.
             ,"BsMuMu"     : 5250.
             ,"BdPiMuNu"   : 4900.
             ,"BsKMuNu"    : 4900.
             ,"LbPMuNu"    : 4900.
             ,"BuPiMuMu"   : 4900.          
             ,"BcJpsiMuNu" : 4900.       
             ,"Comb"       : 4900.
           }

maxranges = { "DsPi"       : 5600.
             ,"BsMuMu"     : 5500.
             ,"BdPiMuNu"   : 6000.
             ,"BsKMuNu"    : 6000.
             ,"LbPMuNu"    : 6000. 
             ,"BuPiMuMu"   : 6000.
             ,"BcJpsiMuNu" : 6000.
             ,"Comb"       : 6000. 
            }

f = TFile(path+files[decay])
t = f.Get(trees[decay]+"DecayTree")

nen = t.GetEntries()
print "Running over %s entries" %(nen)

from numpy import zeros as z
Bs_MM = z(1)
det = z(1)
bdt = z(1)

t.SetBranchAddress("Bs_MM", Bs_MM)
t.SetBranchAddress("det", det)
if(decay != "DsPi"):
  t.SetBranchAddress("bdt", bdt)

hTot = TH1F("mass","Bs mass",100, minranges[decay], maxranges[decay])
hNeg = TH1F("mass","Bs mass",100, minranges[decay], maxranges[decay])
hPos = TH1F("mass","Bs mass",100, minranges[decay], maxranges[decay])

for i in range(nen):
  t.GetEntry(i)
  Bs_MM[0] = Bs_MM
  det[0] = det
  if(decay != "DsPi" or decay != "Comb"):
    #if(bdt>0.5):
    hTot.Fill(Bs_MM[0])
  else:
    hTot.Fill(Bs_MM[0])
  if(det<0): 
    if(decay != "DsPi" or decay != "Comb"):
      #if(bdt>0.5):
      hNeg.Fill(Bs_MM[0])
    else:
      hNeg.Fill(Bs_MM[0])
  if(det>0): 
    if(decay != "DsPi" or decay != "Comb"):
      #if(bdt>0.5):
      hPos.Fill(Bs_MM[0])
    else:
      hPos.Fill(Bs_MM[0])

cPos = TCanvas("cPos","cPos")
hPos.GetXaxis().SetTitle("Mass (MeV)")
hPos.SetMinimum(0)
hPos.Draw()
cPos.SaveAs(names[decay]+"Pos.pdf")

cNeg = TCanvas("cNeg","cNeg")
hNeg.GetXaxis().SetTitle("Mass (MeV)")
hNeg.SetMinimum(0)
hNeg.Draw()
cNeg.SaveAs(names[decay]+"Neg.pdf")

cTot = TCanvas("cTot","cTot")
hTot.GetXaxis().SetTitle("Mass (MeV)")
hTot.SetMinimum(0)
hTot.Draw()
cTot.SaveAs(names[decay]+"Tot.pdf")

