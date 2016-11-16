from ROOT import *
from math import *
from python_utils import *
import os
from paula_style import *

gStyle.SetOptStat(0)

tos = 1
nbins= 5
nbins_2d = 100


CTh1 = RooRealVar("cos_ThetaK","cos_ThetaK",-1.,1.)
CTh2 = RooRealVar("cos_ThetaL","cos_ThetaL",-1.,1.)
Phi = RooRealVar("B_s0_Phi","Phi",-pi,pi)
m1 = RooRealVar("Kst_M","Kst_M",896-150,896+150)
m2 = RooRealVar("Kstb_M","Kstb_M",896-150,896+150)
CTh1.SetNameTitle("CosTheta1","cos#theta_{1}")
CTh2.SetNameTitle("CosTheta2","cos#theta_{2}")
Phi.SetNameTitle("Phi","#varphi")
m1.SetNameTitle("P1_mass","m(K^{+} #pi^{-}) (MeV/c^{2})")
m2.SetNameTitle("P2_mass","m(K^{-} #pi^{+}) (MeV/c^{2})")


gROOT.ProcessLine(".x ${BSKSTKSTROOT}/src/Acceptance_2D/Acceptance.cxx+")
#gROOT.ProcessLine(".x ${BSKSTKSTROOT}/src/Acceptance_2D/Acceptance4D.cxx+")

# Phi.setVal(0)
# Phi.setConstant(1)
m1.setMin(896-150)
m1.setMax(896+150)
m2.setMin(896-150)
m2.setMax(896+150)

Phi.setMin(-pi)
Phi.setMax(pi)
# Phi.setMin(0)
# Phi.setMax(2*pi)

path = os.environ["BSKSTKSTROOT"] + "/options/Acceptance_5D/"

if tos: filename = path+"acceptance_coef_2D_TOS_latest_one.root"#2D_m1c1.root"
else :  filename = path+"acceptance_coef_2D_NOTOS_latest_one.root"#2D_m1c1.root"
treename = "acc5D"
bname = "coeffs"
fin = TFile(filename)
tin = fin.Get(treename)
acc_c1m1 = Acceptance("acceptance_c1m1","acceptance_c1m1",CTh1,m1,tin,bname)
acc_c2m2 = Acceptance("acceptance_c2m2","acceptance_c2m2",CTh2,m2,tin,bname)
#acc = Acceptance4D("acceptance","acceptance",CTh1,CTh2,Phi,m1,m2,tin,bname)
acc = RooProduct("acceptance","acceptance",RooArgList(acc_c1m1,acc_c2m2))

#plot2d
c1 = TCanvas("2d","2d",800,800)
histo_acc_c1m1 = acc_c1m1.createHistogram("histo_acc_c1m1",CTh1,RooFit.Binning(nbins_2d),RooFit.YVar(m1,RooFit.Binning(nbins_2d)))
histo_acc_c1m1.GetZaxis().SetRangeUser(0,43e-3)
histo_acc_c1m1.Draw("colz")


#BREAK
# acceptances_from_MC_TISTOS.root
# if tos: ntrig = "tos"
# else: ntrig = "notos"
# faccmc = TFile("acceptances_from_MC_TISTOS.root")
# hc1acc = faccmc.Get("hc1acc_"+ntrig)
# hc2acc = faccmc.Get("hc2acc_"+ntrig)
# hphacc = faccmc.Get("hphacc_"+ntrig)
# hm1acc = faccmc.Get("hm1acc_"+ntrig)
# hm2acc = faccmc.Get("hm2acc_"+ntrig)


#BREAK
## Plots 1D
fout = TFile("Bs2KstKst_Real2011_strip17_MC11a_cuts_v4r2_GL_2012_pi_cuts_weighted.root")
tout = fout.Get("T")
if tos: cuts = " ((L0Tos) & (Hlt1Tos) & (Hlt2Tos)) && abs(B_mass-5366.3)<30"
else: cuts = " !((L0Tos) & (Hlt1Tos) & (Hlt2Tos))  && abs(B_mass-5366.3)<30"
ftr = TFile("trash.root","recreate")
tout_trig = tout.CopyTree(cuts)

weight = RooRealVar("weight","weight",0.,10e9)
data_trig = RooDataSet("data_trig","data_trig",tout_trig,RooArgSet(CTh1,CTh2,m1,m2,weight),"1","weight")

int_val = acc.createIntegral(RooArgSet(CTh1,CTh2,m1,m2)).getVal()

cv2 = TCanvas()
cv2.Divide(2,2)
cv2.cd(1)
fc1 = CTh1.frame()
data_trig.plotOn(fc1,RooFit.Binning(nbins))
acc.plotOn(fc1,RooFit.Normalization(data_trig.sumEntries()*2./nbins/int_val))
fc1.GetYaxis().SetTitle("Acceptance")
fc1.Draw()

cv2.cd(2)
fc2 = CTh2.frame()
data_trig.plotOn(fc2,RooFit.Binning(nbins))
acc.plotOn(fc2,RooFit.Normalization(data_trig.sumEntries()*2./nbins/int_val))
fc2.GetYaxis().SetTitle("Acceptance")
fc2.Draw()

cv2.cd(3)
fm1 = m1.frame()
data_trig.plotOn(fm1,RooFit.Binning(nbins))
acc.plotOn(fm1,RooFit.Normalization(data_trig.sumEntries()*300./nbins/int_val))
fm1.GetYaxis().SetTitle("Acceptance")
fm1.Draw()

cv2.cd(4)
fm2 = m2.frame()
data_trig.plotOn(fm2,RooFit.Binning(nbins))
acc.plotOn(fm2,RooFit.Normalization(data_trig.sumEntries()*300./nbins/int_val))
fm2.GetYaxis().SetTitle("Acceptance")
fm2.Draw()

# if not tos:
#     weight = RooRealVar("weight","weight",0.,1e9)
#     data_trigb = RooDataSet("data_trigb","data_trigb",tout_trig,RooArgSet(CTh1,CTh2,m1,m2,weight),"1","weight")
    
#     cv2.cd(1)
#     fc1 = CTh1.frame()
#     data_trigb.plotOn(fc1,RooFit.Binning(nbins))
#     acc.plotOn(fc1,RooFit.Normalization(data_trigb.sumEntries()*2./nbins/int_val))
#     fc1.GetYaxis().SetTitle("Acceptance")
#     fc1.Draw()
    
#     cv2.cd(2)
#     fc2 = CTh2.frame()
#     data_trigb.plotOn(fc2,RooFit.Binning(nbins))
#     acc.plotOn(fc2,RooFit.Normalization(data_trigb.sumEntries()*2./nbins/int_val))
#     fc2.GetYaxis().SetTitle("Acceptance")
#     fc2.Draw()

#BREAK
#### Print coeffs
if tos: coeffilename = path+"acceptance_coef_2D_TOS_latest_one.dct"
else:  coeffilename = path+"acceptance_coef_2D_NOTOS_latest_one.dct"

coeffile = open(coeffilename,"r")

import cPickle
coeffsdict = cPickle.load(coeffile)
coeffs_val = coeffsdict["coeffs_val"]
coeffs_err = coeffsdict["coeffs_err"]

outtable = "\\begin{tabular}{c|c}\n"
outtable += "Coefficient & Value \\\\\n"
outtable += "\\hline\n"
for i in range(len(coeffs_val)):
    for j in range(len(coeffs_val[0])):
        val = "%0.3f"%coeffs_val[i][j]
        err = "%0.3f"%coeffs_err[i][j]
        if ((i+j)==0):
            outtable += "$c^{"+str(i)+str(j)+"}$ & "+val+" $\pm$ "+err+" \\\\\n"
        else:
            signif = abs(coeffs_val[i][j]/coeffs_err[i][j])
            signiftext = "%0.3f"%signif
            outtable += "$c^{"+str(i)+str(j)+"}$ & "+val+" $\pm$ "+err+" & "+signiftext +" $\sigma$ \\\\\n"
outtable += "\\end{tabular}"

print outtable


## Correlation
corr_plot = TH2D("c_mass_corr","c_mass_corr",5,0,5,3,0,3)
for i in range(len(coeffs_val)):
    for j in range(len(coeffs_val[0])):
        corr_plot.SetBinContent(j+1,i+1,coeffs_val[i][j])
        corr_plot.SetBinError(j+1,i+1,coeffs_err[i][j])

cv3 = TCanvas()
corr_plot.Draw("colz")




