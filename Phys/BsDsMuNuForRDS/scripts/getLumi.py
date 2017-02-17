#!/usr/bin/env python

from ROOT import *

def getLumi():
   """ Method to get the luminosity from the ntuple"""

   fUp1 = TFile.Open("root://eoslhcb.cern.ch//eos/lhcb/user/r/rvazquez/RDS/TupleRDS_DataUp_1_allNeutrals_iso.root")
   fUp2 = TFile.Open("root://eoslhcb.cern.ch//eos/lhcb/user/r/rvazquez/RDS/TupleRDS_DataUp_2_allNeutrals_iso.root")
   fDown1 = TFile.Open("root://eoslhcb.cern.ch//eos/lhcb/user/r/rvazquez/RDS/TupleRDS_DataDown_1_allNeutrals_iso.root")
   fDown2 = TFile.Open("root://eoslhcb.cern.ch//eos/lhcb/user/r/rvazquez/RDS/TupleRDS_DataDown_2_allNeutrals_iso.root")

   ntUp1 = fUp1.Get("GetIntegratedLuminosity/LumiTuple")
   ntUp2 = fUp2.Get("GetIntegratedLuminosity/LumiTuple")
   ntDown1 = fDown1.Get("GetIntegratedLuminosity/LumiTuple")
   ntDown2 = fDown2.Get("GetIntegratedLuminosity/LumiTuple")

   entriesUp1 = int(ntUp1.GetEntries())
   entriesUp2 = int(ntUp2.GetEntries())
   entriesDown1 = int(ntDown1.GetEntries())
   entriesDown2 = int(ntDown2.GetEntries())

   totalLumiUp1 = 0
   totalLumiUp2 = 0
   totalLumiDown1 = 0
   totalLumiDown2 = 0

   for i in range(entriesUp1):
     ntUp1.GetEntry(i)
     totalLumiUp1 += ntUp1.IntegratedLuminosity
   for i in range(entriesUp2):
     ntUp2.GetEntry(i)
     totalLumiUp2 += ntUp2.IntegratedLuminosity
   for i in range(entriesDown1):
     ntDown1.GetEntry(i)
     totalLumiDown1 += ntDown1.IntegratedLuminosity
   for i in range(entriesDown2):
     ntDown2.GetEntry(i)
     totalLumiDown2 += ntDown2.IntegratedLuminosity 
  
   Total = totalLumiUp1+totalLumiUp2+totalLumiDown1+totalLumiDown2

   print "Lumi Up 1 = "+str(totalLumiUp1)+" pb-1"
   print "Lumi Up 2 = "+str(totalLumiUp2)+" pb-1"
   print "Lumi Up 1 = "+str(totalLumiDown1)+" pb-1"
   print "Lumi Up 2 = "+str(totalLumiDown2)+" pb-1"
   print "#"*50
   print "Total lumi = "+str(Total)+" pb-1"


if __name__ == '__main__':
  getLumi()


