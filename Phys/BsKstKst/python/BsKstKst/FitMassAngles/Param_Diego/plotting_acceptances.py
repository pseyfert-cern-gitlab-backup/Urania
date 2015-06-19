from ROOT import *
from math import *
from graph_tools import *
gStyle.SetOptTitle(0)

import cPickle, os
acc_coef_file = open(os.environ["PWD"] + "/acceptance_v5.dct",'r')
acc_coef_list = cPickle.load(acc_coef_file)

masses, masses_err = [], []
c1_th_val, c1_th_errhi, c1_th_errlo = [], [], []
c2_th_val, c2_th_errhi, c2_th_errlo = [], [], []
c3_th_val, c3_th_errhi, c3_th_errlo = [], [], []
c4_th_val, c4_th_errhi, c4_th_errlo = [], [], []
cy_th_val, cy_th_errhi, cy_th_errlo = [], [], []


funcs = []
for i in range(len(acc_coef_list)):
    bin = acc_coef_list[i]
    
    c1 = bin["coefs"]["c1_th"]
    c2 = bin["coefs"]["c2_th"]
    c3 = bin["coefs"]["c3_th"]
    c4 = bin["coefs"]["c4_th"]
    cy = bin["coefs"]["cy_th"]
    c5 = cy-(1+c1+c2+c3+c4)

    func = TF1("func_"+str(i),"[0]+[1]*x+[2]*x*x+[3]*x*x*x+[4]*x*x*x*x+[5]*x*x*x*x*x",-1,1)
    func.FixParameter(0,1)
    func.FixParameter(1,c1)
    func.FixParameter(2,c2)
    func.FixParameter(3,c3)
    func.FixParameter(4,c4)
    func.FixParameter(5,c5)

    funcs.append(func)


cv = TCanvas()
cv.SetFillColor(0)
funcs[0].Draw()
cols = [1,kBlue,kRed,kGreen,kMagenta]   
for j in range(len(funcs)):
    f=funcs[j]
    f.SetLineColor(j+1)
    f.SetNameTitle("bin_"+f.GetName()[-1],"bin_"+f.GetName()[-1])
    f.Draw("SAME")

leg = cv.BuildLegend()
leg.SetFillColor(0)
leg.Draw()

