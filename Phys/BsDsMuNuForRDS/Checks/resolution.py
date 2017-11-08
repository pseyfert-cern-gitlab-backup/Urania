#!/usr/bin/env python

from ROOT import TFile, TTree, TH1F, TCanvas, TF1

## import ntuples
MCSignalFile = TFile('../src/DsMass_WithSWeighted_Dsst_sigmu_NoCL_CB.root')
tree = MCSignalFile.Get("DecayTree")
nentries = tree.GetEntries()
print "Total number of entries = %s" %(nentries)
wei = True


bins = 50
lmin = -0.6
lmax = 0.6
hBin1 = TH1F("hBin1","hBin1",bins,lmin,lmax)
hBin2 = TH1F("hBin2","hBin2",bins,lmin,lmax)
hBin3 = TH1F("hBin3","hBin3",bins,lmin,lmax)
hBin4 = TH1F("hBin4","hBin4",bins,lmin,lmax)
hBin5 = TH1F("hBin5","hBin5",bins,lmin,lmax)
hBin6 = TH1F("hBin6","hBin6",bins,lmin,lmax)
hBin7 = TH1F("hBin7","hBin7",bins,lmin,lmax)
hBin8 = TH1F("hBin8","hBin8",bins,lmin,lmax)
hBin9 = TH1F("hBin9","hBin9",bins,lmin,lmax)
hBin10 = TH1F("hBin10","hBin10",bins,lmin,lmax)
hBin11 = TH1F("hBin11","hBin11",bins,lmin,lmax)
hTot = TH1F("hTot","hTot",100,-5000000,12000000)

for i in range(nentries):
  tree.GetEntry(i)
  q2Reg = tree.q2Reg
  q2True = tree.q2True
  det = tree.sq
  #resFalg = tree.resFlag
  Bs_0_Hlt2XcMuXForTauB2XcMuDecision_TOS = tree.Bs_0_Hlt2XcMuXForTauB2XcMuDecision_TOS
  Bs_0_MCORR = tree.Bs_0_MCORR
  mu_PIDmu = tree.mu_PIDmu
  Ds_MM = tree.Ds_MM
  mu_iso_MinBDT_Long = tree.mu_iso_MinBDT_Long
  mu_MC_MOTHER_ID = tree.muMomID
  Ds_MC_MOTHER_ID = tree.DsMomID
  Ds_GMID = tree.DsGMID
  gID = tree.gID
  diff = (q2True-q2Reg)/q2True
  #if (Bs_0_Hlt2XcMuXForTauB2XcMuDecision_TOS==1 and Bs_0_MCORR<8000 and Bs_0_MCORR>3000 and mu_PIDmu>0.0 and Ds_MM>1940 and Ds_MM<2000 and mu_iso_MinBDT_Long>-0.5):
  #if (abs(mu_MC_MOTHER_ID) == 531 and abs(Ds_MC_MOTHER_ID) == 433):
  if (det>0 and abs(mu_MC_MOTHER_ID)==531 and abs(Ds_MC_MOTHER_ID)==433 and abs(Ds_GMID)==531 and abs(gID)==22 ):
        hTot.Fill(q2True)
        #if wei:
        #  sigw = tree.sigw 
        #  name = 'weighted'
        #else:
        #sigw = 1
        name = 'unweighted'
        if (0.0 < q2True/1000000 < 1.0):
          hBin1.Fill(diff)
        elif (1.0 < q2True/1000000 < 2.0):
          hBin2.Fill(diff)
        elif (2.0 < q2True/1000000 < 3.0):
          hBin3.Fill(diff)
        elif (3.0 < q2True/1000000 < 4.0):
          hBin4.Fill(diff)
        elif (4.0 < q2True/1000000 < 5.0):
          hBin5.Fill(diff)
        elif (5.0 < q2True/1000000 < 6.0):
          hBin6.Fill(diff)
        elif (6.0 < q2True/1000000 < 7.0):
          hBin7.Fill(diff)
        elif (7.0 < q2True/1000000 < 8.0):
          hBin8.Fill(diff)
        elif (8.0 < q2True/1000000 < 9.0):
          hBin9.Fill(diff)
        elif (9.0 < q2True/1000000 < 10.0):
          hBin10.Fill(diff)
        elif (10.0 < q2True/1000000 < 11.0):
          hBin11.Fill(diff)

c1 = TCanvas()
c1.Divide(4,3)
c1.cd(1)
hBin1.Draw()
c1.cd(2)
hBin2.Draw()
c1.cd(3)
hBin3.Draw()
c1.cd(4)
hBin4.Draw()
c1.cd(5)
hBin5.Draw()
c1.cd(6)
hBin6.Draw()
c1.cd(7)
hBin7.Draw()
c1.cd(8)
hBin8.Draw()
c1.cd(9)
hBin9.Draw()
c1.cd(10)
hBin10.Draw()
c1.cd(11)
hBin11.Draw()
c1.SaveAs("resolution.pdf")

c = TCanvas()
hTot.Draw()
c.SaveAs("q2true.pdf")
