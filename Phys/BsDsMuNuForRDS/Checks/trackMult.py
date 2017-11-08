#!/usr/bin/env python

from ROOT import *

## import ntuples
MCSignalFile = TFile('../src/DsMass_WithSWeighted_Dsst_sigmu_CB.root')
treeMC = MCSignalFile.Get("DecayTree")
nentriesMC = treeMC.GetEntries()

DataFile = TFile('../src/DsMass_WithSWeighted_Dsst_data_CB.root')
treeData = DataFile.Get("DecayTree")
nentriesData = treeData.GetEntries()

hTrackMultMC = TH1F('nTracksMC', 'nTracksMC', 20, 0, 120)
hTrackMultData = TH1F('nTracksData', 'nTracksData', 20, 0, 120)
histos = {}
histosWeighted = {}
for i in range(1,12):
  histos['histoBin'+str(i)] = TH1F("bin"+str(i),"bin"+str(i),20,0,120)
  histosWeighted['histoBinWeighted'+str(i)] = TH1F("binWeight"+str(i),"binWeight"+str(i),20,0,120)

## Fill MC histos with q2True
for i in range(nentriesMC):
  treeMC.GetEntry(i)
  nLT = treeMC.nLongT
  q2True = treeMC.q2True
  sigw = treeMC.sigw
  det = treeMC.sq
  if det>0:
    hTrackMultMC.Fill(nLT)
    if 0.0 < q2True/1000000 < 1.0:
      histos['histoBin1'].Fill(nLT,sigw)
    elif 1.0 < q2True/1000000 < 2.0:
      histos['histoBin2'].Fill(nLT,sigw)
    elif 2.0 < q2True/1000000 < 3.0:
      histos['histoBin3'].Fill(nLT,sigw)
    elif 3.0 < q2True/1000000 < 4.0:
      histos['histoBin4'].Fill(nLT,sigw)
    elif 4.0 < q2True/1000000 < 5.0:
      histos['histoBin5'].Fill(nLT,sigw)
    elif 5.0 < q2True/1000000 < 6.0:
      histos['histoBin6'].Fill(nLT,sigw)
    elif 6.0 < q2True/1000000 < 7.0:
      histos['histoBin7'].Fill(nLT,sigw)
    elif 7.0 < q2True/1000000 < 8.0:
      histos['histoBin8'].Fill(nLT,sigw)
    elif 8.0 < q2True/1000000 < 9.0:
      histos['histoBin9'].Fill(nLT,sigw)
    elif 9.0 < q2True/1000000 < 10.0:
      histos['histoBin10'].Fill(nLT,sigw)
    elif 10.0 < q2True/1000000 < 11.0:
      histos['histoBin11'].Fill(nLT,sigw)      

h = TGraph()
for key in histos.keys():
  print key, int(key.strip('histoBin'))-1, histos[key].GetSumOfWeights()
  h.SetPoint(int(key.strip('histoBin'))-1,int(key.strip('histoBin')),histos[key].GetSumOfWeights()) 

for i in range(nentriesData):
  treeData.GetEntry(i)
  nLT = treeData.nLongT
  det = treeData.sq
  if (det>0):
    hTrackMultData.Fill(nLT)

hTrackMultData.Scale(1./hTrackMultData.GetSumOfWeights())
hTrackMultMC.Scale(1./hTrackMultMC.GetSumOfWeights())

c2 = TCanvas()
hRatio = hTrackMultData.Clone("Ratio")  
hRatio.Divide(hTrackMultMC)
hRatio.SetMarkerStyle(8)
hRatio.Draw("ep")
c2.SaveAs("ratioOfTracks.pdf")

#for i in range(1,21):
#  print hRatio.GetBinContent(i)

c1 = TCanvas()
hTrackMultMC.SetLineColor(1)
hTrackMultData.SetLineColor(2)
hTrackMultMC.SetLineWidth(3)
hTrackMultData.SetLineWidth(3) 
nTrLeg = TLegend(0.7,0.7,0.9,0.9)
nTrLeg.AddEntry(hTrackMultMC,'nTracks MC')
nTrLeg.AddEntry(hTrackMultData,'nTracks Data')
hTrackMultData.Draw()
hTrackMultMC.Draw("same")
nTrLeg.Draw('same')
c1.SaveAs("nLongTracks.pdf")

def getWeight(histo, nLT):
  weight = 1
  if nLT <= 6.:
    weight = histo.GetBinContent(1)
  if 6. < nLT <= 12.:
    weight = histo.GetBinContent(2)
  if 12. < nLT <= 18.:
    weight = histo.GetBinContent(3)
  if 18. < nLT <= 24.:
    weight = histo.GetBinContent(4)
  if 24. < nLT <= 30.:
    weight = histo.GetBinContent(5)
  if 30. < nLT <= 36.:
    weight = histo.GetBinContent(6)
  if 36. < nLT <= 42.:
    weight = histo.GetBinContent(7)
  if 42. < nLT <= 48.:
    weight = histo.GetBinContent(8)
  if 48. < nLT <= 54.:
    weight = histo.GetBinContent(9)
  if 54. < nLT <= 60.:
    weight = histo.GetBinContent(10)
  if 60. < nLT <= 66.:
    weight = histo.GetBinContent(11)
  if 66. < nLT <= 72.:
    weight = histo.GetBinContent(12)
  if 72. < nLT <= 78.:
    weight = histo.GetBinContent(13)
  if 78. < nLT <= 84.:
    weight = histo.GetBinContent(14)
  if 84. < nLT <= 90.:
    weight = histo.GetBinContent(15)
  if 90. < nLT <= 96.:
    weight = histo.GetBinContent(16)
  if 96. < nLT <= 102.:
    weight = histo.GetBinContent(17)
  if 102. < nLT <= 108.:
    weight = histo.GetBinContent(18)
  if 108. < nLT <= 114.:
    weight = histo.GetBinContent(19)
  if 114. < nLT <= 120.:
    weight = histo.GetBinContent(20)
  return weight

## correct the MC with the weights from nTracks
for i in range(nentriesMC):
  treeMC.GetEntry(i)
  nLT = treeMC.nLongT
  q2True = treeMC.q2True
  sigw = treeMC.sigw
  det = treeMC.sq
  w = getWeight(hRatio, nLT)
  print sigw, w, sigw*w
  if det>0:
    if 0.0 < q2True/1000000 < 1.0:
      histosWeighted['histoBinWeighted1'].Fill(nLT,sigw*w)
    elif 1.0 < q2True/1000000 < 2.0:
      histosWeighted['histoBinWeighted2'].Fill(nLT,sigw*w)
    elif 2.0 < q2True/1000000 < 3.0:
      histosWeighted['histoBinWeighted3'].Fill(nLT,sigw*w)
    elif 3.0 < q2True/1000000 < 4.0:
      histosWeighted['histoBinWeighted4'].Fill(nLT,sigw*w)
    elif 4.0 < q2True/1000000 < 5.0:
      histosWeighted['histoBinWeighted5'].Fill(nLT,sigw*w)
    elif 5.0 < q2True/1000000 < 6.0:
      histosWeighted['histoBinWeighted6'].Fill(nLT,sigw*w)
    elif 6.0 < q2True/1000000 < 7.0:
      histosWeighted['histoBinWeighted7'].Fill(nLT,sigw*w)
    elif 7.0 < q2True/1000000 < 8.0:
      histosWeighted['histoBinWeighted8'].Fill(nLT,sigw*w)
    elif 8.0 < q2True/1000000 < 9.0:
      histosWeighted['histoBinWeighted9'].Fill(nLT,sigw*w)
    elif 9.0 < q2True/1000000 < 10.0:
      histosWeighted['histoBinWeighted10'].Fill(nLT,sigw*w)
    elif 10.0 < q2True/1000000 < 11.0:
      histosWeighted['histoBinWeighted11'].Fill(nLT,sigw*w)

hW = TGraph()
for key in histosWeighted.keys():
  print key, int(key.strip('histoBinWeighted'))-1, histosWeighted[key].GetSumOfWeights()
  hW.SetPoint(int(key.strip('histoBinWeighted'))-1,int(key.strip('histoBinWeighted')),histosWeighted[key].GetSumOfWeights())

hRatioWeight = TGraph()
for i in range(1,12):
  hRatioWeight.SetPoint(i-1,i,histosWeighted['histoBinWeighted'+str(i)].GetSumOfWeights()/histos['histoBin'+str(i)].GetSumOfWeights())

c3 = TCanvas()
h.SetMarkerStyle(8)
h.GetXaxis().SetTitle('q2 GeV^{2}')
h.GetYaxis().SetTitle('Signal Candidates')
hW.SetMarkerStyle(8)
h.SetMarkerColor(1)
hW.SetMarkerColor(2)
wleg = TLegend(0.7,0.7,0.9,0.9)
wleg.AddEntry(h,'events')
wleg.AddEntry(hW,'events Weigthed')
h.Draw("AP")
hW.Draw("P same")
wleg.Draw('same')
c3.SaveAs("eventsWeighted.pdf")

c4 = TCanvas()
line = TLine(0,1,12,1)
gStyle.SetOptFit(kTRUE)
hRatioWeight.GetXaxis().SetTitle('q2 GeV^{2}')
hRatioWeight.GetYaxis().SetTitle('ratio')
hRatioWeight.SetMarkerStyle(8)
hRatioWeight.Fit('pol1')
hRatioWeight.Draw('AP')
hRatioWeight.SetMinimum(0.8)
hRatioWeight.SetMaximum(1.2)
line.SetLineColor(2)
line.Draw()
c4.SaveAs('ratioAfterTracks.pdf')
