from ROOT import *
from math import *
from graph_tools import *
gROOT.ProcessLine(".x ~/Usefulthings/lhcbStyle.C")
import cPickle


filein_res = open("results_Bs_acc_anal.dct")
results = cPickle.load(filein_res)

filein_plots = TFile("results_Bs_acc_anal.root")

mass = [[],[],[]]
fL = [[],[],[]]
fpa = [[],[],[]]

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

cv1 = TCanvas()
Npwave_g.SetLineColor(kRed)
Npwave_g.SetMarkerColor(kRed)
Nswave_g.SetLineColor(1)
Nswave_g.SetMarkerColor(1)
Ndwave_g.SetLineColor(kBlue)
Ndwave_g.SetMarkerColor(kBlue)
Npwave_g.Draw("AP")
Nswave_g.Draw("P")
Ndwave_g.Draw("P")


cv2 = TCanvas()
fL_g.SetLineColor(kRed)
fL_g.SetMarkerColor(kRed)
fpa_g.SetLineColor(kBlue)
fpa_g.SetMarkerColor(kBlue)
fL_g.Draw("AP")
fpa_g.Draw("P")
