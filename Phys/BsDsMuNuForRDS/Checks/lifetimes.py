#!/usr/bin/env python

from ROOT import TFile, TTree, TH1F, TCanvas, TF1

## import ntuples
MCSignalFile = TFile('/eos/lhcb/wg/semileptonic/Bs2DsX/ProcessedTrees/MC09_DsMuNu.root')
tree = MCSignalFile.Get("B2DsMuNuTuple/DecayTree")
nentries = tree.GetEntries()

hBsLifetime = TH1F("hBs","hBs",25,0.001,0.01)
hDsLifetime = TH1F("hDs","hDs",25,0,0.003)

for i in range(nentries):
  tree.GetEntry(i)
  ## apply the Ds*MuNu selection
  resFlag = tree.resFlag
  Bs_0_Hlt2XcMuXForTauB2XcMuDecision_TOS = tree.Bs_0_Hlt2XcMuXForTauB2XcMuDecision_TOS
  Bs_0_MCORR = tree.Bs_0_MCORR
  mu_PIDmu = tree.mu_PIDmu
  Ds_MM = tree.Ds_MM
  mu_iso_MinBDT_Long = tree.mu_iso_MinBDT_Long
  #Ds_0_40_nc_mult = tree.Ds_0.40_nc_mult
  #Ds_0_40_nc_maxPt_PX = tree.Ds_0.40_nc_maxPt_PX
  #Ds_0_40_nc_maxPt_PY = tree.Ds_0.40_nc_maxPt_PY
  #Ds_0_40_nc_CL = tree.Ds_0.40_nc_CL
  BsTau = tree.Bs_0_TRUETAU
  DsTau = tree.Ds_TRUETAU
  Ds_TRUEID = tree.Ds_TRUEID
  pi_TRUEID = tree.pi_TRUEID
  pi_MC_MOTHER_ID = tree.pi_MC_MOTHER_ID
  Kpl_TRUEID = tree.Kpl_TRUEID
  Kpl_MC_MOTHER_ID = tree.Kpl_MC_MOTHER_ID
  Kmi_TRUEID = tree.Kmi_TRUEID
  Kmi_MC_MOTHER_ID = tree.Kmi_MC_MOTHER_ID
  mu_TRUEID = tree.mu_TRUEID
  mu_MC_MOTHER_ID = tree.mu_MC_MOTHER_ID
  Bs_0_TRUEID = tree.Bs_0_TRUEID
  Ds_MC_MOTHER_ID = tree.Ds_MC_MOTHER_ID
 

  if ( abs(Ds_TRUEID) == 431 and abs(pi_TRUEID) == 211 and abs(pi_MC_MOTHER_ID) == 431 and abs(Kpl_TRUEID) == 321 and abs(Kpl_MC_MOTHER_ID) == 431 and abs(Kmi_TRUEID) == 321 and abs(Kmi_MC_MOTHER_ID) == 431 and abs(mu_TRUEID) == 13 and abs(mu_MC_MOTHER_ID) == 531 and abs(Bs_0_TRUEID) == 531 and abs(Ds_MC_MOTHER_ID) == 433):
#  if (resFlag<2 and Bs_0_Hlt2XcMuXForTauB2XcMuDecision_TOS==1 and Bs_0_MCORR<8000 and Bs_0_MCORR>3000 and mu_PIDmu>0.0 and Ds_MM>1940 and Ds_MM<2000 and mu_iso_MinBDT_Long>-0.5):
    ## get the true lifetimes
    hBsLifetime.Fill(BsTau)
    hDsLifetime.Fill(DsTau)

c1 = TCanvas()
hBsLifetime.GetXaxis().SetTitle('#tau of B_{s} [ns]')
e1 = TF1("e1","expo",0.001,0.01)
hBsLifetime.Fit('e1')
tauBs = e1.GetParameter(1)
hBsLifetime.Draw()
c1.SaveAs("Bs_lifetime.pdf")

c2 = TCanvas()
hDsLifetime.GetXaxis().SetTitle('#tau of D_{s} [ns]')
e2 = TF1("e2","expo",0,0.005)
hDsLifetime.Fit('e2')
tauDs = e2.GetParameter(1)
hDsLifetime.Draw()
c2.SaveAs('Ds_lifetime.pdf')

print "Bs lifetime = %s ps from fit, 1.510 ps from PDG" %(-1*tauBs/1000.)
print "Ds lifetime = %s ps from fit, 0.500 ps from PDG" %(-1*tauDs/1000.)

