#!/run/bash python

from ROOT import *

f_Gauss = TFile("DsMass_WithSWeighted_Dsst_Gaussian.root","READ")
f_1CB = TFile("DsMass_WithSWeighted_Dsst_1CB.root","READ")
f_2CB = TFile("DsMass_WithSWeighted_Dsst_2CB.root","READ")

wG = f_Gauss.Get("DecayTree")
w1CB = f_1CB.Get("DecayTree")
w2CB = f_2CB.Get("DecayTree")

histQ2_G = TH1F("Q2_G", "Q2_G", 80, -4000000, 14000000)
histQ2_CB = TH1F("Q2_CB", "Q2_CB", 80, -4000000, 14000000)
histQ2_2CB = TH1F("Q2_2CB", "Q2_2CB", 80, -4000000, 14000000)
histEmu_G = TH1F("Emu_G", "Emu_G", 80, 0, 4000)
histEmu_CB = TH1F("Emu_CB", "Emu_CB", 80, 0, 4000)
histEmu_2CB = TH1F("Emu_2CB", "Emu_2CB", 80, 0, 4000)
histMCORR_G = TH1F("MCORR_G", "MCORR_G", 80, 3000, 8000)
histMCORR_CB = TH1F("MCORR_CB", "MCORR_CB", 80, 3000, 8000)
histMCORR_2CB = TH1F("MCORR_2CB", "MCORR_2CB", 80, 3000, 8000)

Gentries = wG.GetEntries()
CBentries = w1CB.GetEntries()
DCBentries = w2CB.GetEntries()

from numpy import zeros as z
q2_G = z(1,dtype=float)
Bs_0_MCORR_G = z(1,dtype=float)
Emu_G = z(1,dtype=float)
sigw_G = z(1,dtype=float)

q2_CB = z(1,dtype=float)
Bs_0_MCORR_CB = z(1,dtype=float)
Emu_CB = z(1,dtype=float)
sigw_CB = z(1,dtype=float)

q2_2CB = z(1,dtype=float)
Bs_0_MCORR_2CB = z(1,dtype=float)
Emu_2CB = z(1,dtype=float)
sigw_2CB = z(1,dtype=float)

wG.SetBranchAddress("q2",q2_G)
wG.SetBranchAddress("Emu",Emu_G)
wG.SetBranchAddress("Bs_0_MCORR",Bs_0_MCORR_G)
wG.SetBranchAddress("sigw",sigw_G)

w1CB.SetBranchAddress("q2",q2_CB)
w1CB.SetBranchAddress("Emu",Emu_CB)
w1CB.SetBranchAddress("Bs_0_MCORR",Bs_0_MCORR_CB)
w1CB.SetBranchAddress("sigw",sigw_CB)

w2CB.SetBranchAddress("q2",q2_2CB)
w2CB.SetBranchAddress("Emu",Emu_2CB)
w2CB.SetBranchAddress("Bs_0_MCORR",Bs_0_MCORR_2CB)
w2CB.SetBranchAddress("sigw",sigw_2CB)

for i in range(Gentries):
  wG.GetEntry(i)
  histQ2_G.Fill(q2_G,sigw_G)
  histEmu_G.Fill(Emu_G,sigw_G)
  histMCORR_G.Fill(Bs_0_MCORR_G,sigw_G)
  
for i in range(Gentries):
  w1CB.GetEntry(i)
  histQ2_CB.Fill(q2_CB,sigw_CB)
  histEmu_CB.Fill(Emu_CB,sigw_CB)
  histMCORR_CB.Fill(Bs_0_MCORR_CB,sigw_CB)

for i in range(Gentries):
  w2CB.GetEntry(i)
  histQ2_2CB.Fill(q2_2CB,sigw_2CB)
  histEmu_2CB.Fill(Emu_2CB,sigw_2CB)
  histMCORR_2CB.Fill(Bs_0_MCORR_2CB,sigw_2CB)  

c1 = TCanvas()
histQ2_G.SetMarkerStyle(8)
histQ2_CB.SetMarkerStyle(8)
histQ2_2CB.SetMarkerStyle(8)
histQ2_CB.SetMarkerColor(2)
histQ2_2CB.SetMarkerColor(3)
histQ2_2CB.GetXaxis().SetTitle("Q2 (MeV^{2}")
histQ2_2CB.Draw()
histQ2_G.Draw('same')
histQ2_CB.Draw('same')
l1 = TLegend(0.1,0.75,0.25,0.9)
l1.AddEntry(histQ2_G,"Gaussian")
l1.AddEntry(histQ2_CB,"Single CB")
l1.AddEntry(histQ2_2CB,"Double CB")
l1.Draw()
c1.SaveAs("Q2.pdf")

c2 = TCanvas()
histEmu_G.SetMarkerStyle(8)
histEmu_CB.SetMarkerStyle(8)
histEmu_2CB.SetMarkerStyle(8)
histEmu_CB.SetMarkerColor(2)
histEmu_2CB.SetMarkerColor(3)
histEmu_2CB.GetXaxis().SetTitle("Emu (MeV)")
histEmu_2CB.Draw()
histEmu_G.Draw('same')
histEmu_CB.Draw('same')
l2 = TLegend(0.1,0.75,0.25,0.9)
l2.AddEntry(histEmu_G,"Gaussian")
l2.AddEntry(histEmu_CB,"Single CB")
l2.AddEntry(histEmu_2CB,"Double CB")
l2.Draw()
c2.SaveAs("Emu.pdf")

c3 = TCanvas()
histMCORR_G.SetMarkerStyle(8)
histMCORR_CB.SetMarkerStyle(8)
histMCORR_2CB.SetMarkerStyle(8)
histMCORR_CB.SetMarkerColor(2)
histMCORR_2CB.SetMarkerColor(3)
histMCORR_2CB.GetXaxis().SetTitle("Corrected Mass (MeV)")
histMCORR_2CB.Draw()
histMCORR_G.Draw('same')
histMCORR_CB.Draw('same')
l3 = TLegend(0.1,0.75,0.25,0.9)
l3.AddEntry(histMCORR_G,"Gaussian")
l3.AddEntry(histMCORR_CB,"Single CB")
l3.AddEntry(histMCORR_2CB,"Double CB")
l3.Draw()
c3.SaveAs("MCORR.pdf")
