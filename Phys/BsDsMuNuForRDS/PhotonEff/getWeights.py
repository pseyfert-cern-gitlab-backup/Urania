#!/usr/bin/env python

from ROOT import *
from math import *

def getBin(gammaP, gammaPT):
  """ Get the bin number in which the photon falls """
  binNumber = -1
  
  if gammaP < binsP[1]: 
    if gammaPT < binsPT[1]:
      binNumber = 0
    if gammaPT > binsPT[1] and gammaPT < binsPT[2]:
      binNumber = 1
    if gammaPT > binsPT[2]:
      binNumber = 2

  if gammaP > binsP[1] and gammaP < binsP[2]:
    if gammaPT < binsPT[1]:
      binNumber = 3
    if gammaPT > binsPT[1] and gammaPT < binsPT[2]:
      binNumber = 4
    if gammaPT > binsPT[2]:
      binNumber = 5

  if gammaP > binsP[2]:
    if gammaPT < binsPT[1]:
      binNumber = 6
    if gammaPT > binsPT[1] and gammaPT < binsPT[2]:
      binNumber = 7
    if gammaPT > binsPT[2]:
      binNumber = 8

  return binNumber


FileNum = TFile('BsMassForPhotonEff_WithSWeighted_Num_Fixed.root','r')
TreeNum = FileNum.Get("DecayTree")

FileDen = TFile('BsMassForPhotonEff_WithSWeighted_Den_Fixed.root','r')
TreeDen = FileDen.Get("DecayTree")

binsP = [0,3800,6500,100000]
binsPT = [0,400,600,10000]

nentriesNum = TreeNum.GetEntries()
nentriesDen = TreeDen.GetEntries()
histosDen = {}
histosNum = {}
print "Total number of entries num = %s, and den = %s" %(nentriesNum,nentriesDen) 

for i in range(nentriesNum):
  TreeNum.GetEntry(i)
  sigden = TreeNum.sigden
  signum = TreeNum.signum
  gammaP = TreeNum.Gamma_P
  gammaPT = TreeNum.Gamma_PT
  mDsGPi = TreeNum.MassDsGPi
  mDsG = TreeNum.MassDsG
  theBin = getBin(gammaP, gammaPT)
  if theBin < 0:
    print "ERROR: Not able to find the correct bin"
    continue
  try:
    histosNum[theBin].Fill(mDsGPi-mDsG+2112,signum)
  except:
    histosNum[theBin] = TH1F("h"+str(theBin),"h"+str(theBin),100,5250,5500)
    histosNum[theBin].Fill(mDsGPi-mDsG+2112,signum)

for i in range(nentriesDen):
  TreeDen.GetEntry(i)
  gammaPT = TreeDen.Gamma_PT
  gammaP = TreeDen.Gamma_P
  sigden = TreeDen.sigden
  theBin = getBin(gammaP, gammaPT)
  if theBin < 0:
    print "ERROR: Not able to find the correct bin"
    continue
  try:
    histosDen[theBin].Fill(gammaPT,sigden)
  except:
    histosDen[theBin] = TH1F("h"+str(theBin),"h"+str(theBin),100,0,10000)
    histosDen[theBin].Fill(gammaPT,sigden)

cNum = {}
cDen = {}

for key in histosNum.keys():
  cNum[key] = TCanvas()
  histosNum[key].Draw()
  cNum[key].SaveAs("num_bin"+str(key)+".pdf")

for key in histosDen.keys():
  cDen[key] = TCanvas()
  histosDen[key].Draw()
  cDen[key].SaveAs("den_bin"+str(key)+".pdf")

totDen = 0
totNum = 0
out = open("PhotonEff_Fixed.txt","w")
for key in histosNum.keys(): 
  print "in bin = %s, number of photons = %s" %(key, histosNum[key].GetSumOfWeights())
  print "in bin = %s, number of denominator = %s" %(key, histosDen[key].GetSumOfWeights())
  totNum += histosNum[key].GetSumOfWeights() 
  totDen += histosDen[key].GetSumOfWeights()
  print "in bin = %s, eff = %s" %(key, histosNum[key].GetSumOfWeights()/histosDen[key].GetSumOfWeights())
  out.write(str(key)+" "+str(histosNum[key].GetSumOfWeights()/histosDen[key].GetSumOfWeights())+"\n")
out.close() 
print totNum, totDen
