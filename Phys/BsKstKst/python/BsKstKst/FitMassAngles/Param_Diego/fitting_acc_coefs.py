from ROOT import *
from math import *
from graph_tools import *

import cPickle, os
acc_coef_file = open(os.environ["PWD"] + "/acceptance_coefs_lessbins_v2.dct",'r')
acc_coef_list = cPickle.load(acc_coef_file)

masses, masses_err = [], []
c1_th_val, c1_th_errhi, c1_th_errlo = [], [], []
c2_th_val, c2_th_errhi, c2_th_errlo = [], [], []
c3_th_val, c3_th_errhi, c3_th_errlo = [], [], []
c4_th_val, c4_th_errhi, c4_th_errlo = [], [], []
cy_th_val, cy_th_errhi, cy_th_errlo = [], [], []

for i in range(len(acc_coef_list)-1):
    mlo = acc_coef_list[i]["mass_bin"][0]
    mhi = acc_coef_list[i+1]["mass_bin"][0]
    masses.append(0.5*(mlo+mhi))
    masses_err.append(0.25*(mhi-mlo))

mlo = acc_coef_list[len(acc_coef_list)-1]["mass_bin"][0]
mhi = 1700
masses.append(0.5*(mlo+mhi))
masses_err.append(0.5*(mhi-mlo))

 
for bin in acc_coef_list:
#     mlo = bin["mass_bin"][0]
#     mhi = bin["mass_bin"][1]

#     masses.append(0.5*(mlo+mhi))
#     masses_err.append(0.5*(mhi-mlo))
    c1_th_val.append(bin["coefs"]["c1_th"])
    c2_th_val.append(bin["coefs"]["c2_th"])
    c3_th_val.append(bin["coefs"]["c3_th"])
    c4_th_val.append(bin["coefs"]["c4_th"])
    cy_th_val.append(bin["coefs"]["cy_th"])

    if not bin["coefs_errhi"]["c1_th"]*bin["coefs_errlo"]["c1_th"]:
        c1_th_errhi.append(bin["coefs_errhi"]["c1_th"] - bin["coefs_errlo"]["c1_th"])
        c1_th_errlo.append(bin["coefs_errhi"]["c1_th"] - bin["coefs_errlo"]["c1_th"])
    else:
        c1_th_errhi.append(bin["coefs_errhi"]["c1_th"])
        c1_th_errlo.append(abs(bin["coefs_errlo"]["c1_th"]))
    

    if not bin["coefs_errhi"]["c2_th"]*bin["coefs_errlo"]["c2_th"]:
        c2_th_errhi.append(bin["coefs_errhi"]["c2_th"] - bin["coefs_errlo"]["c2_th"])
        c2_th_errlo.append(bin["coefs_errhi"]["c2_th"] - bin["coefs_errlo"]["c2_th"])
    else:
        c2_th_errhi.append(bin["coefs_errhi"]["c2_th"])
        c2_th_errlo.append(abs(bin["coefs_errlo"]["c2_th"]))

    if not bin["coefs_errhi"]["c3_th"]*bin["coefs_errlo"]["c3_th"]:
        c3_th_errhi.append(bin["coefs_errhi"]["c3_th"] - bin["coefs_errlo"]["c3_th"])
        c3_th_errlo.append(bin["coefs_errhi"]["c3_th"] - bin["coefs_errlo"]["c3_th"])
    else:
        c3_th_errhi.append(bin["coefs_errhi"]["c3_th"])
        c3_th_errlo.append(abs(bin["coefs_errlo"]["c3_th"]))

    if not bin["coefs_errhi"]["c4_th"]*bin["coefs_errlo"]["c4_th"]:
        c4_th_errhi.append(bin["coefs_errhi"]["c4_th"] - bin["coefs_errlo"]["c4_th"])
        c4_th_errlo.append(bin["coefs_errhi"]["c4_th"] - bin["coefs_errlo"]["c4_th"])
    else:
        c4_th_errhi.append(bin["coefs_errhi"]["c4_th"])
        c4_th_errlo.append(abs(bin["coefs_errlo"]["c4_th"]))

    if not bin["coefs_errhi"]["cy_th"]*bin["coefs_errlo"]["cy_th"]:
        cy_th_errhi.append(bin["coefs_errhi"]["cy_th"] - bin["coefs_errlo"]["cy_th"])
        cy_th_errlo.append(bin["coefs_errhi"]["cy_th"] - bin["coefs_errlo"]["cy_th"])
    else:
        cy_th_errhi.append(bin["coefs_errhi"]["cy_th"])
        cy_th_errlo.append(abs(bin["coefs_errlo"]["cy_th"]))



c1_th_g = assymGraph(masses,c1_th_val,masses_err,c1_th_errlo,exh=masses_err,eyh=c1_th_errhi,title="c1_th_vs_mass")
c2_th_g = assymGraph(masses,c2_th_val,masses_err,c2_th_errlo,exh=masses_err,eyh=c2_th_errhi,title="c2_th_vs_mass")
c3_th_g = assymGraph(masses,c3_th_val,masses_err,c3_th_errlo,exh=masses_err,eyh=c3_th_errhi,title="c3_th_vs_mass")
c4_th_g = assymGraph(masses,c4_th_val,masses_err,c4_th_errlo,exh=masses_err,eyh=c4_th_errhi,title="c4_th_vs_mass")
cy_th_g = assymGraph(masses,cy_th_val,masses_err,cy_th_errlo,exh=masses_err,eyh=cy_th_errhi,title="cy_th_vs_mass")


err_func1 = TF1("err_func1","[3]+[0]*TMath::Erf([1]*(x-[2]))",700,1750)
err_func2 = TF1("err_func2","[3]+[0]*TMath::Erf([1]*(x-[2]))",700,1750)
err_func3 = TF1("err_func3","[3]+[0]*TMath::Erf([1]*(x-[2]))",700,1750)
err_func4 = TF1("err_func4","[3]+[0]*TMath::Erf([1]*(x-[2]))",700,1750)
err_func5 = TF1("err_func5","[3]+[0]*TMath::Erf([1]*(x-[2]))",700,1750)


cv = TCanvas()
cv.Divide(3,2)
cv.cd(1)
err_func1.SetParameter(2,1200)
err_func1.SetParameter(0,-0.08)
err_func1.SetParameter(1,0.01)
err_func1.SetParameter(3,-0.1)
c1_th_g.Fit("err_func1")
c1_th_g.Draw("AP")
cv.cd(2)
err_func2.SetParameter(2,1200)
err_func2.SetParameter(0,-0.08)
err_func2.SetParameter(1,0.01)
err_func2.SetParameter(3,-0.1)
c2_th_g.Fit("err_func2")
c2_th_g.Draw("AP")
cv.cd(3)
err_func3.SetParameter(2,1200)
err_func3.SetParameter(0,0.08)
err_func3.SetParameter(1,0.01)
err_func3.SetParameter(3,-0.1)
c3_th_g.Fit("err_func3")
c3_th_g.Draw("AP")
cv.cd(4)
err_func4.SetParameter(2,1200)
err_func4.SetParameter(0,0.08)
err_func4.SetParameter(1,0.01)
err_func4.SetParameter(3,-0.1)
c4_th_g.Fit("err_func4")
c4_th_g.Draw("AP")

cv.cd(5)
err_func5.SetParameter(2,1200)
err_func5.SetParameter(0,0.08)
err_func5.SetParameter(1,0.01)
err_func5.SetParameter(3,0.1)
cy_th_g.Fit("err_func5")
cy_th_g.Draw("AP")
