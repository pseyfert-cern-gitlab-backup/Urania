from ROOT import *
from math import *
from polarization import AngularPDF
gStyle.SetPalette(1)    #Color Palette
import os
os.sys.path.append(os.environ["BS2MUMUROOT"] + "/python/Bs2MuMu/")
from triggerclass import *
from smartpyROOT import *
from scipy import random as rnd
#f = TFile("/tmp/alvarezc/BdJPsiKstMC_GL_v3.root")
#f = TFile("/afs/cern.ch/user/d/diegoms/vol5/BdJPsiKstMC_nopt_v3.root")

#f = TFile("/scratch10/Ntuples_BsJpsiKst/BdJPsiKstMC_nopt_v3.root")
#f = TFile("/afs/cern.ch/user/d/diegoms/vol5/BsJpsiKstTot.root")
#f = TFile("/scratch10/Ntuples_BsJpsiKst/BsJpsiKstMU.root")

f = TRFIOFile("/castor/cern.ch/user/d/diegoms/BsJpsiKst/BdJpsiKstTotMC11_v2.root")
#f = TFile("/afs/cern.ch/user/d/diegoms/vol5/BdJpsiKstTotMC11_v2_pionp.root")
#f = TFile("/afs/cern.ch/user/d/diegoms/vol5/BsjpsikstMC11_pionp.root")
#t2 = f.Get("T")

t2 = f.Get("T/T")
#t2 = f.Get("T")


 

#BREAK


cuts ="dDsig>13 && mu1ips>5 && mu2ips>5 && Bips<5 && DOCA<0.3 && p1ips>2 && k1ips>2 && JPsiChi2<9 && KstChi2<9 && Vchi2<25 && abs(JPsiMass-3096.916)<60 && PIDk>6 && PIDpi<-6 "
#     cuts += "&& Bmass_JC>5150 && Bmass_JC<5800"
cuts += "&& abs(Bmass_JC-5279.5)<25"
#cuts += "&& abs(Bmass_JC-5366.3)<25"
cuts += "&& kaon_pt>500 && pion_pt>500"
cuts += "&& abs(Mjpsik-5279)>60"
#cuts += "&& abs(KstMass-896)<40"# && KstMass>896"
#cuts += "&& KstMass>(896-40)"# && KstMass<896"
#cuts += "&& KstMass>856 && KstMass >1200"
#cuts += "&& KstMass > 1000"


trigger = "L0Decision==1 && Hlt1Decision==1 && Hlt2Decision==1"

cuts += " && "+ trigger


f2=TFile("/tmp/wwwmc.root","recreate")
t=t2.CopyTree(cuts+"&& GL11sb.>0.2")
BREAK
## def pionw(x):
##     if x < 19000: return -0.0552197 + 0.000113333*x + -4.16072e-09*x*x + 5.67158e-14*x*x*x
##     return 1.
## ch2 = []

## ch = channelData(fromRootToListDic(t))

## for entry in ch:
##     p2 = entry["p1p2"]
##     p3 = entry["p1p3"]
##     p1 = entry["p1p1"]
##     p = vector(p1,p2,p3) 
##     p = vmod(p)
##     x = rnd.random()
##     if x > pionw(p): continue
##     ch2.append(entry)

## ch2 = channelData(ch2)
## ch2.save("~/vol5/BsjpsikstMC11_pionp")
## BREAK
fit = AngularPDF()


#Apa2 = 0.2397
#Ape2 = 0.1601
#A02 = 1.-Apa2-Ape2
#dpa = 2.501

### Dec file B*s* jpsi kst
Hp = 0.685
Hz = 0.714
Hm = 0.143
pHp = 3.14
pHm = -0.72

_Hp = complex(Hp *cos(pHp), Hp*sin(pHp))
_Hm = complex(Hm *cos(pHm), Hm*sin(pHm))
_Hz = complex(Hz, 0)
## Define pHz 0.0

_a1 = 1./sqrt(2) *(_Hp + _Hm)
_a2 = 1./sqrt(2) *(_Hp - _Hm)
suma =  .714**2 + .143**2 +.685**2

Apa2 = (_a1*_a1.conjugate()).real/suma
Ape2 = (_a2*_a2.conjugate()).real/suma #0.1601
A02 = 1.-Apa2-Ape2
dpa = atan(_a1.imag/_a1.real) + pi

#BREAK
fit.A02.setVal(A02)
fit.A02.setConstant(kTRUE)
fit.x.setVal(Apa2/(1-A02))
fit.x.setConstant(kTRUE)
fit.cdpa.setVal(cos(dpa))
fit.cdpa.setConstant(kTRUE)
fit.c1_psi.setVal(-0.522)#
fit.c2_psi.setVal(-0.723)#
fit.c3_psi.setVal(-0.190)#
fit.c4_psi.setVal(0.208)#
fit.y.setVal(1e-05)

fit.c1_psi.setConstant(0)
fit.c2_psi.setConstant(0)
fit.c3_psi.setConstant(0)
fit.c4_psi.setConstant(0)
fit.y.setConstant(0)
fit.c1_theta.setConstant(1)
fit.c2_theta.setVal(-0.178)
fit.c2_theta.setConstant(0)

fit.c1_phi.setVal(0.090)
fit.c2_phi.setVal(2.0)
fit.c3_phi.setVal(0.090)

fit.c1_phi.setConstant(0)
fit.c2_phi.setConstant(0)
fit.c3_phi.setConstant(0)

fit.c4_phi.setVal(0)
fit.c5_phi.setVal(0)
fit.c6_phi.setVal(0)
fit.c4_phi.setConstant(1)
fit.c5_phi.setConstant(1)
fit.c6_phi.setConstant(1)




s_a = 10
## Fit Polinomios


dataset = RooDataSet("data","data",t,RooArgSet(fit.CPsi,fit.CTheta,fit.Phi))
# dataset = RooDataSet("data","data",t,RooArgSet(fit.CPsi))


fitres = fit.sigmodel.fitTo(dataset)

nbins = 9

cv3 = TCanvas()
cv3.SetFillColor(0)
cv3.Divide(2,2)

cv3.cd(1)
cpsif = fit.CPsi.frame()
RooAbsData.plotOn(dataset,cpsif,RooFit.Binning(nbins))
fit.sigmodel.plotOn(cpsif)
cpsif.Draw()

cv3.cd(2)
cthf = fit.CTheta.frame()
RooAbsData.plotOn(dataset,cthf,RooFit.Binning(nbins))
fit.sigmodel.plotOn(cthf)
cthf.Draw()

cv3.cd(3)
cphif = fit.Phi.frame()
RooAbsData.plotOn(dataset,cphif,RooFit.Binning(nbins))
fit.sigmodel.plotOn(cphif)
cphif.Draw()

BREAK
mod = fit.sigmodel

h3 = TH3F("B","B", 5,-1,1,20,-1,1,20,-pi,pi)
h4 = mod.fillHistogram(h3,RooArgList(fit.CPsi,fit.CTheta,fit.Phi))
h5 = TH3F("A","A", 20,-1,1,20,-1,1,20,-pi,pi)

for i in range(h3.GetNbinsX()):
    for j in range(h3.GetNbinsY()):
        for k in range(h3.GetNbinsZ()):
            h5.SetBinContent(i+1,j+1,k+1, 0)

for entry in t: h5.Fill(entry.CPsi,entry.CTheta,entry.PhiP)

N=0
for i in range(h3.GetNbinsX()):
    for j in range(h3.GetNbinsY()):
        for k in range(h3.GetNbinsZ()):
            if h5.GetBinContent(i+1,j+1,k+1) == 0: N+=1
            num = h5.GetBinContent(i+1,j+1,k+1)
            den = h3.GetBinContent(i+1,j+1,k+1)
            h5.SetBinContent(i+1,j+1,k+1, num*1./den)
            h5.SetBinError(i+1,j+1,k+1, sqrt(num)*1./den)
            #print "i, j, k, numerador, denominador, ratio, error = ", i+1, j+1, k+1, num, den, num*1./den, sqrt(num)*1./den
#faccBd = TFile("Histo_ACC_MC10.root", "recreate")

faccBs = TFile("Histo_ACC_MC10_Bs.root", "recreate")
h5.Write()
#faccBd.Close()
faccBs.Close()
            
            
#h5.Divide(h3)
#BREAK

#fitres = fit.sigmodel.fitTo(dataset,RooFit.Minos(1),RooFit.Save())
#fitres = fit.sigmodel.fitTo(dataset,RooFit.Minos(0),RooFit.Save())




# cv3 = TCanvas()
# cv3.SetFillColor(0)
# cpsif = fit.CPsi.frame()
# RooAbsData.plotOn(dataset,cpsif)
# model.plotOn(cpsif)
# cpsif.Draw()

cv4 = TCanvas()
cv4.SetFillColor(0)
proj2d = fit.sigmodel.createProjection(RooArgSet(fit.CTheta))
histo = proj2d.createHistogram("histo2d",fit.CPsi,RooFit.YVar(fit.Phi))
histo.Draw("COL")


#### BS

##   EXT PARAMETER                  PARABOLIC         MINOS ERRORS        
##   NO.   NAME      VALUE            ERROR      NEGATIVE      POSITIVE   
##    1  c1_phi       7.31919e-02   1.11033e-02  -1.11888e-02   1.12203e-02
##    2  c1_psi      -5.02248e-01   3.16384e-02  -4.15707e-02   4.17283e-02
##    3  c2_phi       2.10633e+00   9.17033e-02  -9.06006e-02   9.29867e-02
##    4  c2_psi      -5.77800e-01   1.18153e-01  -6.57562e-02   6.72453e-02
##    5  c2_theta    -1.77624e-01   2.41345e-02  -2.31959e-02   2.36586e-02
##    6  c3_phi       2.24757e-01   1.56538e-01  -1.58414e-01   1.57365e-01
##    7  c3_psi      -3.93354e-01   1.30832e-01  -1.38689e-01   1.37649e-01
##    8  c4_psi       4.24607e-02   1.29461e-01  -7.37160e-02   7.24649e-02
##    9  y            1.05613e-08   1.11464e-03   at limit      1.10933e-03
##                                  WARNING -   - ABOVE PARAMETER IS AT LIMIT.
##                                ERR DEF= 0.5
## [#1] INFO:Minization -- RooMinuit::optimizeConst: deactivating const optimization
## [#1] INFO:Plotting -- RooAbsReal::plotOn(sigmodel) plot on CPsi integrates over variables (CTheta,PhiP)
## [#1] INFO:NumericIntegration -- RooRealIntegral::init(sigmodel_Int[CTheta,PhiP]_Norm[CPsi,CTheta,PhiP]) using numeric integrator RooAdaptiveIntegratorND to calculate Int(CTheta,PhiP)
## [#1] INFO:Plotting -- RooAbsReal::plotOn(sigmodel) plot on CTheta integrates over variables (CPsi,PhiP)
## [#1] INFO:NumericIntegration -- RooRealIntegral::init(sigmodel_Int[CPsi,PhiP]_Norm[CPsi,CTheta,PhiP]) using numeric integrator RooAdaptiveIntegratorND to calculate Int(CPsi,PhiP)




############ 1/2  HIGH Kst mass  (for delta_s studies)

##   EXT PARAMETER                  PARABOLIC         MINOS ERRORS        
##   NO.   NAME      VALUE            ERROR      NEGATIVE      POSITIVE   
##    1  c1_phi       8.75255e-02   1.65895e-02  -1.65079e-02   1.65493e-02
##    2  c1_psi      -5.42884e-01   5.80968e-02  -5.83296e-02   6.19648e-02
##    3  c2_phi       2.04403e+00   1.14118e-01  -1.09540e-01   1.18134e-01
##    4  c2_psi      -6.93260e-01   9.27583e-02  -8.86425e-02   9.59909e-02
##    5  c2_theta    -1.70516e-01   3.31690e-02  -3.26308e-02   3.36284e-02
##    6  c3_phi       9.68671e-02   1.89592e-01  -1.91521e-01   1.91996e-01
##    7  c3_psi      -6.50562e-02   1.83292e-01  -2.00662e-01   1.85398e-01
##    8  c4_psi       1.77464e-01   1.00925e-01  -1.03909e-01   9.65560e-02
##    9  y            1.29461e-09   1.46527e-02   at limit      7.37018e-03
##                                  WARNING -   - ABOVE PARAMETER IS AT LIMIT.


### The other half

##                     EDM=6.08824e-05    STRATEGY= 1      ERROR MATRIX ACCURATE 
##   EXT PARAMETER                  PARABOLIC         MINOS ERRORS        
##   NO.   NAME      VALUE            ERROR      NEGATIVE      POSITIVE   
##    1  c1_phi       9.31952e-02   1.65186e-02  -1.65665e-02   1.64792e-02
##    2  c1_psi      -4.90963e-01   5.47108e-02  -6.03983e-02   6.13235e-02
##    3  c2_phi       1.99703e+00   1.03280e-01  -9.86131e-02   1.09018e-01
##    4  c2_psi      -7.51628e-01   8.03778e-02  -8.83247e-02   9.19185e-02
##    5  c2_theta    -1.85196e-01   3.22660e-02  -3.17965e-02   3.27824e-02
##    6  c3_phi       7.87408e-02   1.75136e-01  -1.78507e-01   1.75684e-01
##    7  c3_psi      -3.51750e-01   1.72091e-01  -2.04777e-01   1.99094e-01
##    8  c4_psi       2.37775e-01   8.74781e-02  -9.95465e-02   9.62854e-02
##    9  y            2.30511e-03   5.30688e-03   at limit      6.39508e-03
##                                ERR DEF= 0.5                    EDM=6.08824e-05    STRATEGY= 1      ERROR MATRIX ACCURATE 
##   EXT PARAMETER                  PARABOLIC         MINOS ERRORS        
##   NO.   NAME      VALUE            ERROR      NEGATIVE      POSITIVE   
##    1  c1_phi       9.31952e-02   1.65186e-02  -1.65665e-02   1.64792e-02
##    2  c1_psi      -4.90963e-01   5.47108e-02  -6.03983e-02   6.13235e-02
##    3  c2_phi       1.99703e+00   1.03280e-01  -9.86131e-02   1.09018e-01
##    4  c2_psi      -7.51628e-01   8.03778e-02  -8.83247e-02   9.19185e-02
##    5  c2_theta    -1.85196e-01   3.22660e-02  -3.17965e-02   3.27824e-02
##    6  c3_phi       7.87408e-02   1.75136e-01  -1.78507e-01   1.75684e-01
##    7  c3_psi      -3.51750e-01   1.72091e-01  -2.04777e-01   1.99094e-01
##    8  c4_psi       2.37775e-01   8.74781e-02  -9.95465e-02   9.62854e-02
##    9  y            2.30511e-03   5.30688e-03   at limit      6.39508e-03
##                                ERR DEF= 0.5
