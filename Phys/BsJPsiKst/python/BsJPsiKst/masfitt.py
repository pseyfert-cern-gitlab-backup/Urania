from ROOT import *
from math import *


#f = TFile("/tmp/alvarezc/BdJPsiKstMC_GL_v3.root")
f = TFile("/afs/cern.ch/user/d/diegoms/vol5/BdJPsiKstMC_nopt_v3.root")
#f = TFile("/afs/cern.ch/user/d/diegoms/vol5/BdJpsiKstTotMC11_v2.root")
#f = TFile("/afs/cern.ch/user/d/diegoms/vol5/BdJpsiKstTotMC11_v2_pionp.root")
#t2 = f.Get("T")

f = TFile("~/vol5/OL_2011_GL.root")
t2 = f.Get("T")

ncb = RooRealVar("ncb","ncb",1)

a1b_cb = RooRealVar("a1b_cb","a1b_cb",2.8, 0.5,3.5)
a2b_cb = RooRealVar("a2b_cb","a2b_cb",2.8, 0.5,3.5)
a2_cb = RooRealVar("a2_cb","a2_cb",-2.3, -6,-0.5)
a1_cb = RooRealVar("a1_cb","a1_cb",-2.3, -6,-0.5)
ncb2 = RooRealVar("ncb2","ncb2",2,1,40)

## cuts ="dDsig>13 && mu1ips>5 && mu2ips>5 && Bips<5 && DOCA<0.3 && p1ips>2 && k1ips>2 && JPsiChi2<9 && KstChi2<9 && Vchi2<25 && abs(JPsiMass-3096.916)<60 && PIDk>6 && PIDpi<-6 "
## #     cuts += "&& B0_MM>5150 && B0_MM<5800"
## #cuts += "&& abs(B0_MM-5279.5)<25"
## #cuts += "&& abs(B0_MM-5366.3)<25"
## cuts += "&& kaon_pt>500 && pion_pt>500"
## cuts += "&& abs(Mjpsik-5279)>60"
## cuts += "&& abs(KstMass-896)<40"# && KstMass>896"
## #cuts += "&& KstMass>(896-40)"# && KstMass<896"
## #cuts += "&& KstMass>856 && KstMass >1200"
## #cuts += "&& KstMass > 1000"


## trigger = "L0Decision==1 && Hlt1Decision==1 && Hlt2Decision==1"

## cuts += " && "+ trigger
cuts = "muplus_MINIPCHI2 > 25 && muminus_MINIPCHI2 > 25 && Kplus_MINIPCHI2 > 4 && piminus_MINIPCHI2 > 4  && Kplus_PT > 500 && piminus_PT>500 && piminus_PIDK<-6 && Kplus_PIDK > 6 && J_psi_1S_FDCHI2_TOPPV > 169 &&  J_psi_1S_LOKI_DOCA_1_2<0.3"
cuts += "&&  J_psi_1S_ENDVERTEX_CHI2 < 9 && B0_IPCHI2_OWNPV < 25"

cuts += "&& abs(Mjpsik-5279)>60"
cuts += "&& abs(Kst_892_0_MM-896)<70"
cuts += "&& Kplus_ID >0"    

f2=TFile("/tmp/nada.root","recreate")
t=t2.CopyTree(cuts+"&& GLsb>0.2")

#Mass = RooRealVar("B0_MM","B0_MM",5150, 5350)
Mass = RooRealVar("B0_MM","B0_MM",5150, t.GetMaximum("B0_MM"))

mean1 = RooRealVar("mean1","mean1",5279, 5276,5283)
sigma1 = RooRealVar("sigma1","sigma1", 5.,10.)

delta_s = RooRealVar("delta_s", "delta_s", 2.,1.,15.)
delta_m = RooRealVar("delta_m", "delta_m", 5366.3-5279)
sigma2 = RooFormulaVar("sigma2","sigma2", "sigma1 + delta_s" ,RooArgList(sigma1,delta_s) )
mean2 = RooFormulaVar("mean2","mean2", "mean1 + delta_m" ,RooArgList(mean1,delta_m) )
sigb11a  = RooCBShape("SigmodelB11a","SigmodelB11a", Mass, mean1, sigma1, a1_cb, ncb2)
sigb11b  = RooCBShape("SigmodelB11b","SigmodelB11b", Mass, mean1, sigma1, a1b_cb, ncb)
sigb12a  = RooCBShape("SigmodelB12a","SigmodelB12a", Mass, mean1, sigma2, a2_cb, ncb2)
sigb12b  = RooCBShape("SigmodelB12b","SigmodelB12b", Mass, mean1, sigma2, a2b_cb, ncb)
f05 = RooRealVar("f05","f05",0.5)#, 0., 1.)

sigb12  = RooAddPdf("SigmodelB12","SigmodelB12", sigb12a, sigb12b, f05)
sigb11  = RooAddPdf("SigmodelB11","SigmodelB11", sigb11a, sigb11b, f05)
#sigb12b  = RooCBShape("SigmodelB12b","SigmodelB12", Mass, mean1, sigma2, a2b_cb, ncb)
sigb21  = RooCBShape("SigmodelB21","SigmodelB21", Mass, mean2, sigma1, a1_cb, ncb)
sigb22  = RooCBShape("SigmodelB22","SigmodelB22", Mass, mean2, sigma2, a2_cb, ncb)
fsmres = RooRealVar("f small res","f small res",0.5, 0., 1.)
sigBd  = RooAddPdf("SigmodelB1","SigmodelB1", sigb11, sigb12, fsmres)
sigBs  = RooAddPdf("SigmodelB2","SigmodelB2", sigb21, sigb22, fsmres)

#SigBs = RooProdPdf("Bs pdf", "Bs pdf",RooArgList(AngBs.sigmodel,sigB2))
#SigBd = RooProdPdf("Bd pdf", "Bd pdf",RooArgList(AngBd.sigmodel,sigB1))

fBs = RooRealVar("fBs","fBs", 1e-02,1e-03,.1)
kbkg = RooRealVar("k","k",-1e-03,-1,0)
massbkg = RooExponential("bkg", "Exponential background pdf", Mass, kbkg)
nd = RooRealVar("nBd","nBd", 0.5*t.GetEntries(),t.GetEntries())
ns = RooFormulaVar("nBs","nBs", "fBs*nBd",RooArgList(fBs,nd))
nbkg = RooRealVar("n nbkg","n bkg", 0.,0.1*t.GetEntries())
model = RooAddPdf("jmmodel","jmmodel",RooArgList(sigBs,sigBd,massbkg),RooArgList(ns,nd,nbkg))


dataset = RooDataSet("data","data",t,RooArgSet(Mass))
model.fitTo(dataset, RooFit.Minos(kTRUE))
fr = Mass.frame()
dataset.plotOn(fr)

model.plotOn(fr)
fr.Draw()


## 2011 KID > 0
