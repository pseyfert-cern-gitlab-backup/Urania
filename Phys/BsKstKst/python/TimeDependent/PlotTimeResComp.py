from ROOT import *
gROOT.ProcessLine('.x ../../src/TimeDependent/lhcbStyle.C')

f1 = TFile("res_binfit_wide_TIS.root")
f2 = TFile("res_binfit_wide_TOS.root")

g1_11 = f1.Get("cwide").FindObject("cwide_1").FindObject("Graph")
g2_11 = f2.Get("cwide").FindObject("cwide_1").FindObject("Graph")
g1_12 = f1.Get("cwide").FindObject("cwide_2").FindObject("Graph")
g2_12 = f2.Get("cwide").FindObject("cwide_2").FindObject("Graph")

g1_11.SetMarkerColor(kBlue)
g2_11.SetMarkerColor(kRed)
g1_12.SetMarkerColor(kBlue)
g2_12.SetMarkerColor(kRed)
g1_11.SetLineColor(kBlue)
g2_11.SetLineColor(kRed)
g1_12.SetLineColor(kBlue)
g2_12.SetLineColor(kRed)

g1_11.SetTitle("2011")
g2_11.SetTitle("2011")
g1_12.SetTitle("2012")
g2_12.SetTitle("2012")

gStyle.SetOptTitle(1)

c = TCanvas("c","c",2000,400)
c.Divide(2)
c.cd(1)
g1_11.Draw("ap")
g2_11.Draw("p")
c.cd(2)
g1_12.Draw("ap")
g2_12.Draw("p")

c.Print("time_res_comp.root")
c.Print("time_res_comp.pdf")
