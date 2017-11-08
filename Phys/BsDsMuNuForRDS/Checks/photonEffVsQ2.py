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

## check that the reconstruction efficiency of the photon is flat in q2

## import ntuples with photon tag
MCSignalFile = TFile('../src/DsMass_WithSWeighted_Dsst_sigmu_NoCL_Cheb.root')
treeNum = MCSignalFile.Get("DecayTree")
nentriesMC = treeNum.GetEntries()

## import ntuples without photon tag
MCNoPhoton = TFile('/afs/cern.ch/user/r/rvazquez/work/MC09_DsMuNu.root')
treeDen = MCNoPhoton.Get("B2DsMuNuTuple/DecayTree")
nentriesDen = treeDen.GetEntries()

binsP = [0,3800,6500,100000]
binsPT = [0,400,600,10000]

histosNum = {}
histosDen = {}
for i in range(1,12):
  histosNum['histoBinNum'+str(i)] = TH1F("binNum"+str(i),"binNum"+str(i),20,0,120)
  histosDen['histoBinDen'+str(i)] = TH1F("binDen"+str(i),"binDen"+str(i),20,0,120)

PTBin = 3
pTMin = 0
pTMax = 0
if (PTBin == 0):
  pTMin = 75
  pTMax = 500
elif (PTBin == 1):
  pTMin = 500
  pTMax = 1000
elif (PTBin == 2):
  pTMin = 1000
  pTMax = 2000
else:
  pTMin = 0
  pTMax = 200000

nNum = 0

from numpy import zeros as z
Ds_0_40_nc_maxPt_PX = z(1)
Ds_0_40_nc_maxPt_PY = z(1)
Ds_0_40_nc_maxPt_PZ = z(1)

photonEffs = open("PhotonEff.txt","r")
eff = {}
lines = photonEffs.readlines()
for line in lines:
  eff[float(line.split()[0])] = float(line.split()[1])

## get the photon eff from MC as a crosscheck
nums = [0.,0.,0.,0.,0.,0.,0.,0.,0.]
totalone = 0

MCphotonEff = [0.,0.,0.,0.,0.,0.,0.,0.,0.]
for i in range(nentriesDen):
  treeDen.GetEntry(i)
  nLT = treeDen.nLT
  det = treeDen.sq
  q2True = treeDen.q2True
  DsMomID = treeDen.DsMomID
  DsGMID = treeDen.DsGMID
  muMomID = treeDen.muMomID
  gID = treeDen.gID
  treeDen.SetBranchAddress('Ds_0.40_nc_maxPt_PX',Ds_0_40_nc_maxPt_PX)
  treeDen.SetBranchAddress('Ds_0.40_nc_maxPt_PY',Ds_0_40_nc_maxPt_PY)
  treeDen.SetBranchAddress('Ds_0.40_nc_maxPt_PZ',Ds_0_40_nc_maxPt_PZ)
  gPT = sqrt(Ds_0_40_nc_maxPt_PX*Ds_0_40_nc_maxPt_PX+Ds_0_40_nc_maxPt_PY*Ds_0_40_nc_maxPt_PY)
  gP = sqrt(Ds_0_40_nc_maxPt_PX*Ds_0_40_nc_maxPt_PX+Ds_0_40_nc_maxPt_PY*Ds_0_40_nc_maxPt_PY+Ds_0_40_nc_maxPt_PZ*Ds_0_40_nc_maxPt_PZ)
  photonBin = getBin(gP, gPT)
  if(det>0 and abs(DsMomID)==433 and abs(DsGMID)==531 and abs(muMomID)==531 and abs(gID)==22 and gPT>pTMin and gPT<pTMax):
    nums[photonBin]+=1
    totalone+=1

print totalone
print nentriesDen
print totalone/float(nentriesDen)
for i in range(9):
  MCphotonEff[i] = float(nums[i]/nentriesDen) 
print MCphotonEff

for i in range(nentriesMC):
  treeNum.GetEntry(i)
  nLT = treeNum.nLongT
  q2True = treeNum.q2True
  sigw = treeNum.sigw
  det = treeNum.sq
  nLT = treeNum.nLongT
  DsMomID = treeNum.DsMomID
  DsGMID = treeNum.DsGMID
  muMomID = treeNum.muMomID
  gID = treeNum.gID
  treeNum.SetBranchAddress('Ds_0.40_nc_maxPt_PX',Ds_0_40_nc_maxPt_PX)
  treeNum.SetBranchAddress('Ds_0.40_nc_maxPt_PY',Ds_0_40_nc_maxPt_PY)
  treeNum.SetBranchAddress('Ds_0.40_nc_maxPt_PZ',Ds_0_40_nc_maxPt_PZ)
  gPT = sqrt(Ds_0_40_nc_maxPt_PX*Ds_0_40_nc_maxPt_PX+Ds_0_40_nc_maxPt_PY*Ds_0_40_nc_maxPt_PY)
  gP = sqrt(Ds_0_40_nc_maxPt_PX*Ds_0_40_nc_maxPt_PX+Ds_0_40_nc_maxPt_PY*Ds_0_40_nc_maxPt_PY+Ds_0_40_nc_maxPt_PZ*Ds_0_40_nc_maxPt_PZ)

  photonBin = getBin(gP, gPT)
  photonEff = eff[photonBin]

  if (det>0 and abs(DsMomID)==433 and abs(DsGMID)==531 and abs(muMomID)==531 and abs(gID)==22 and gPT>pTMin and gPT<pTMax):
    ## use the photon efficiency from data
    nNum += 1
    if 0.0 < q2True/1000000 < 1.0:
      histosNum['histoBinNum1'].Fill(nLT,sigw*photonEff)
    elif 1.0 < q2True/1000000 < 2.0:
      histosNum['histoBinNum2'].Fill(nLT,sigw*photonEff)
    elif 2.0 < q2True/1000000 < 3.0:
      histosNum['histoBinNum3'].Fill(nLT,sigw*photonEff)
    elif 3.0 < q2True/1000000 < 4.0:
      histosNum['histoBinNum4'].Fill(nLT,sigw*photonEff)
    elif 4.0 < q2True/1000000 < 5.0:
      histosNum['histoBinNum5'].Fill(nLT,sigw*photonEff)
    elif 5.0 < q2True/1000000 < 6.0:
      histosNum['histoBinNum6'].Fill(nLT,sigw*photonEff)
    elif 6.0 < q2True/1000000 < 7.0:
      histosNum['histoBinNum7'].Fill(nLT,sigw*photonEff)
    elif 7.0 < q2True/1000000 < 8.0:
      histosNum['histoBinNum8'].Fill(nLT,sigw*photonEff)
    elif 8.0 < q2True/1000000 < 9.0:
      histosNum['histoBinNum9'].Fill(nLT,sigw*photonEff)
    elif 9.0 < q2True/1000000 < 10.0:
      histosNum['histoBinNum10'].Fill(nLT,sigw*photonEff)
    elif 10.0 < q2True/1000000 < 11.0:
      histosNum['histoBinNum11'].Fill(nLT,sigw*photonEff)

h = TGraph()
for key in histosNum.keys():
  print key, int(key.strip('histoBinNum'))-1, histosNum[key].GetSumOfWeights()
  h.SetPoint(int(key.strip('histoBinNum'))-1,int(key.strip('histoBinNum')),histosNum[key].GetSumOfWeights())

nDen = 0
for i in range(nentriesDen):
  treeDen.GetEntry(i) 
  nLT = treeDen.nLT
  det = treeDen.sq
  q2True = treeDen.q2True
  DsMomID = treeDen.DsMomID
  DsGMID = treeDen.DsGMID
  muMomID = treeDen.muMomID
  gID = treeDen.gID
  treeDen.SetBranchAddress('Ds_0.40_nc_maxPt_PX',Ds_0_40_nc_maxPt_PX)
  treeDen.SetBranchAddress('Ds_0.40_nc_maxPt_PY',Ds_0_40_nc_maxPt_PY)
  treeDen.SetBranchAddress('Ds_0.40_nc_maxPt_PZ',Ds_0_40_nc_maxPt_PZ)
  gPT = sqrt(Ds_0_40_nc_maxPt_PX*Ds_0_40_nc_maxPt_PX+Ds_0_40_nc_maxPt_PY*Ds_0_40_nc_maxPt_PY)
  gP = sqrt(Ds_0_40_nc_maxPt_PX*Ds_0_40_nc_maxPt_PX+Ds_0_40_nc_maxPt_PY*Ds_0_40_nc_maxPt_PY+Ds_0_40_nc_maxPt_PZ*Ds_0_40_nc_maxPt_PZ)
  photonBin = getBin(gP, gPT)
  if(det>0 and abs(DsMomID)==433 and abs(DsGMID)==531 and abs(muMomID)==531 and abs(gID)==22 and gPT>pTMin and gPT<pTMax):
    nDen += 1
  ## cuts are performed when creating the ntuple
  #if (resFlag<2 and Bs_0_Hlt2XcMuXForTauB2XcMuDecision_TOS==1 and Bs_0_MCORR<8000 and Bs_0_MCORR>3000 and mu_PIDmu>0.0 and Ds_MM>1940 and Ds_MM<2000 and mu_iso_MinBDT_Long>-0.5):
    #if (abs(Ds_TRUEID) == 431 and abs(pi_TRUEID) == 211 and abs(pi_MC_MOTHER_ID) == 431 and abs(Kpl_TRUEID) == 321 and abs(Kpl_MC_MOTHER_ID) == 431 and abs(Kmi_TRUEID) == 321 and abs(Kmi_MC_MOTHER_ID) == 431):
      #if (abs(mu_TRUEID) == 13 and abs(mu_MC_MOTHER_ID) == 531 and abs(Ds_MC_MOTHER_ID) == 433 and abs(Bs_0_TRUEID) == 531):
    if 0.0 < q2True/1000000 < 1.0:
      histosDen['histoBinDen1'].Fill(nLT)
    elif 1.0 < q2True/1000000 < 2.0:
      histosDen['histoBinDen2'].Fill(nLT)
    elif 2.0 < q2True/1000000 < 3.0:
      histosDen['histoBinDen3'].Fill(nLT)
    elif 3.0 < q2True/1000000 < 4.0:
      histosDen['histoBinDen4'].Fill(nLT)
    elif 4.0 < q2True/1000000 < 5.0:
      histosDen['histoBinDen5'].Fill(nLT)
    elif 5.0 < q2True/1000000 < 6.0:
      histosDen['histoBinDen6'].Fill(nLT)
    elif 6.0 < q2True/1000000 < 7.0:
      histosDen['histoBinDen7'].Fill(nLT)
    elif 7.0 < q2True/1000000 < 8.0:
      histosDen['histoBinDen8'].Fill(nLT)
    elif 8.0 < q2True/1000000 < 9.0:
      histosDen['histoBinDen9'].Fill(nLT)
    elif 9.0 < q2True/1000000 < 10.0:
      histosDen['histoBinDen10'].Fill(nLT)
    elif 10.0 < q2True/1000000 < 11.0:
      histosDen['histoBinDen11'].Fill(nLT)

print "Normalizations are: With photon %s, without photon %s" %(nNum,nDen)

hDen = TGraph()
for key in histosDen.keys():
  print key, int(key.strip('histoBinDen'))-1, histosDen[key].GetSumOfWeights()
  hDen.SetPoint(int(key.strip('histoBinDen'))-1,int(key.strip('histoBinDen')),histosDen[key].GetSumOfWeights())

hRatio = TGraphErrors()
#hRatio = TGraph()
for i in range(1,12):
  den = histosDen['histoBinDen'+str(i)].GetSumOfWeights()/nDen
  num = histosNum['histoBinNum'+str(i)].GetSumOfWeights()/nNum
  try:
    errnum = sqrt(num*(1-num)/nDen)
  except:
    errnum = 0
  try:
    errden = sqrt(den*(1-den)/nNum)
  except:
    errden = 0
  err = (num/den)*sqrt((errnum/num)**2+(errden/den)**2)
  hRatio.SetPoint(i-1,i-0.5,num/den)
  hRatio.SetPointError(i-1,0.5,err)
  #hRatio.SetPoint(i-1,i,(histosDen['histoBinDen'+str(i)].GetSumOfWeights()/nDen) / (histos['histoBin'+str(i)].GetSumOfWeights()/nNum))

gStyle.SetOptFit(kTRUE)
c1 = TCanvas()
hRatio.GetXaxis().SetTitle("q2 (GeV^{2})")
hRatio.SetMarkerStyle(8)
fitfunc = TF1("f1","[0]+[1]*x",0,11)
hRatio.Fit('f1')
hRatio.Draw("AP")
c1.SaveAs("photonRatio_NoCL_"+str(PTBin)+"_Weighted_Pol1.pdf")
