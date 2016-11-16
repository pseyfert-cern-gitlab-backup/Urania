from ROOT import *
from math import *
from graph_tools import *
gROOT.ProcessLine(".x ~/Usefulthings/lhcbStyle.C")
import cPickle


filein_res = open("results_2011.dct")
results = cPickle.load(filein_res)

filein_plots = TFile("results_2011.root")

mass = [[],[],[]]
fL = [[],[],[]]
fpa = [[],[],[]]
dpa = [[],[],[]]
dpe = [[],[],[]]
ds = [[],[],[]]
dd0 = [[],[],[]]
ddpa = [[],[],[]]
ddpe = [[],[],[]]

Nswave = [[],[],[]]
Npwave = [[],[],[]]
Ndwave = [[],[],[]]

for bin in results:
    mass[0].append(bin["mass_mean"])
    mass[1].append(bin["mass_err"])
    mass[2].append(bin["mass_err"])

    mass_bin_width = bin["mass_bin"][1]-bin["mass_bin"][0]
    
    fL[0].append(bin["params"]["fL_Bs"])
    fL[2].append(bin["params"]["fL_Bs_errhi"])
    fL[1].append(-1*bin["params"]["fL_Bs_errlo"])

    fpa[0].append(bin["params"]["fpa_Bs"])
    fpa[2].append(bin["params"]["fpa_Bs_errhi"])
    fpa[1].append(-1*bin["params"]["fpa_Bs_errlo"])

    dpa[0].append(bin["params"]["dpa_Bs"])
    dpa[2].append(bin["params"]["dpa_Bs_errhi"])
    dpa[1].append(-1*bin["params"]["dpa_Bs_errlo"])

#     dpe[0].append(bin["params"]["dpe_Bs"])
#     dpe[2].append(bin["params"]["dpe_Bs_errhi"])
#     dpe[1].append(-1*bin["params"]["dpe_Bs_errlo"])


    ds[0].append(bin["params"]["ds_Bs"])
    ds[2].append(bin["params"]["ds_Bs_errhi"])
    ds[1].append(-1*bin["params"]["ds_Bs_errlo"])

    ddpa[0].append(bin["params"]["ddpa_Bs"])
    ddpa[2].append(bin["params"]["ddpa_Bs_errhi"])
    ddpa[1].append(-1*bin["params"]["ddpa_Bs_errlo"])

    ddpe[0].append(bin["params"]["ddpe_Bs"])
    ddpe[2].append(bin["params"]["ddpe_Bs_errhi"])
    ddpe[1].append(-1*bin["params"]["ddpe_Bs_errlo"])

    dd0[0].append(bin["params"]["dd0_Bs"])
    dd0[2].append(bin["params"]["dd0_Bs_errhi"])
    dd0[1].append(-1*bin["params"]["dd0_Bs_errlo"])


    Nswave[0].append(bin["Nswave"]*1./mass_bin_width)
    Nswave[2].append(bin["Nswave_err"]*1./mass_bin_width)
    Nswave[1].append(bin["Nswave_err"]*1./mass_bin_width)

    Npwave[0].append(bin["Npwave"]*1./mass_bin_width)
    Npwave[2].append(bin["Npwave_err"]*1./mass_bin_width)
    Npwave[1].append(bin["Npwave_err"]*1./mass_bin_width)

    Ndwave[0].append(bin["Ndwave"]*1./mass_bin_width)
    Ndwave[2].append(bin["Ndwave_err"]*1./mass_bin_width)
    Ndwave[1].append(bin["Ndwave_err"]*1./mass_bin_width)




Npwave_g = assymGraph(mass[0],Npwave[0],mass[1],Npwave[1],mass[2],Npwave[2],title="Npwave")
Nswave_g = assymGraph(mass[0],Nswave[0],mass[1],Nswave[1],mass[2],Nswave[2],title="Nswave")
Ndwave_g = assymGraph(mass[0],Ndwave[0],mass[1],Ndwave[1],mass[2],Ndwave[2],title="Ndwave")

fL_g = assymGraph(mass[0],fL[0],mass[1],fL[1],mass[2],fL[2],title="fL")
fpa_g = assymGraph(mass[0],fpa[0],mass[1],fpa[1],mass[2],fpa[2],title="fpa")
dpa_g = assymGraph(mass[0],dpa[0],mass[1],dpa[1],mass[2],dpa[2],title="dpa")
# dpe_g = assymGraph(mass[0],dpe[0],mass[1],dpe[1],mass[2],dpe[2],title="dpe")
ds_g = assymGraph(mass[0],ds[0],mass[1],ds[1],mass[2],ds[2],title="ds")
dd0_g = assymGraph(mass[0],dd0[0],mass[1],dd0[1],mass[2],dd0[2],title="dd0")
ddpa_g = assymGraph(mass[0],ddpa[0],mass[1],ddpa[1],mass[2],ddpa[2],title="ddpa")
ddpe_g = assymGraph(mass[0],ddpe[0],mass[1],ddpe[1],mass[2],ddpe[2],title="ddpe")

cv1 = TCanvas("yields")
Npwave_g.SetLineColor(kRed)
Npwave_g.SetMarkerColor(kRed)
Nswave_g.SetLineColor(1)
Nswave_g.SetMarkerColor(1)
Ndwave_g.SetLineColor(kBlue)
Ndwave_g.SetMarkerColor(kBlue)
Npwave_g.Draw("AP")
Nswave_g.Draw("P")
Ndwave_g.Draw("P")
leg1 = cv1.BuildLegend()
leg1.SetFillColor(0)
leg1.Draw()

cv2 = TCanvas("P wave fractions")
fL_g.SetLineColor(kRed)
fL_g.SetMarkerColor(kRed)
fpa_g.SetLineColor(kBlue)
fpa_g.SetMarkerColor(kBlue)
fL_g.Draw("AP")
fpa_g.Draw("P")
leg2 = cv2.BuildLegend()
leg2.SetFillColor(0)
leg2.Draw()

cv3 = TCanvas("P wave phases")
dpa_g.SetLineColor(kRed)
dpa_g.SetMarkerColor(kRed)
# dpe_g.SetLineColor(kBlue)
# dpe_g.SetMarkerColor(kBlue)
dpa_g.Draw("AP")
# dpe_g.Draw("P")
leg3 = cv3.BuildLegend()
leg3.SetFillColor(0)
leg3.Draw()

cv4 = TCanvas("S wave phase")
ds_g.SetLineColor(kBlue)
ds_g.SetMarkerColor(kBlue)
ds_g.GetYaxis().SetTitle("#delta_{s} (rad)")
ds_g.Draw("AP")

