from ROOT import *
from math import *
from polarization import AngularPDF
gStyle.SetPalette(1)   


#f = TFile("/tmp/alvarezc/BdJPsiKstMC_GL_v3.root")
f = TFile("~diegoms/vol5/BdJPsiKstMC_nopt_v3.root")
t2 = f.Get("T/T")


cuts ="dDsig>13 && mu1ips>5 && mu2ips>5 && Bips<5 && DOCA<0.3 && p1ips>2 && k1ips>2 && JPsiChi2<9 && KstChi2<9 && Vchi2<25 && abs(JPsiMass-3096.916)<60 && PIDk>6 && PIDpi<-6 "
#     cuts += "&& Bmass_JC>5150 && Bmass_JC<5800"
cuts += "&& abs(Bmass_JC-5279.5)<25"
cuts += "&& kaon_pt>500 && pion_pt>500"
cuts += "&& abs(Mjpsik-5279)>60"
cuts += "&& abs(KstMass-896)<40"
#cuts += "&& KstMass > 1000"


trigger = "L0Decision==1 && Hlt1Decision==1 && Hlt2Decision==1"

cuts += " && "+ trigger


f2=TFile("nada.root","recreate")
t=t2.CopyTree(cuts+"&& GL11sb.>0.2")


fit = AngularPDF()



Apa2 = 0.2397
Ape2 = 0.1601
A02 = 1.-Apa2-Ape2
dpa = 2.501


fit.A02.setVal(A02)
fit.A02.setConstant(kTRUE)
fit.x.setVal(Apa2/(1-A02))
fit.x.setConstant(kTRUE)
fit.cdpa.setVal(cos(dpa))
fit.cdpa.setConstant(kTRUE)


fit.Gs.setVal(0.653)
fit.DGs.setVal(0)




## Fit Polinomios


dataset = RooDataSet("data","data",t,RooArgSet(fit.CPsi,fit.CTheta,fit.Phi))
# dataset = RooDataSet("data","data",t,RooArgSet(fit.CPsi))


fit.c1_psi.setVal(0)
fit.c2_psi.setVal(0)
fit.c3_psi.setVal(0)
fit.c4_psi.setVal(0)
fit.y.setVal(1)
fit.c1_theta.setVal(0)
fit.c2_theta.setVal(0)
fit.c1_phi.setVal(0)
fit.c2_phi.setVal(0)
fit.c3_phi.setVal(0)


fit.c1_psi.setConstant(1)
fit.c2_psi.setConstant(1)
fit.c3_psi.setConstant(1)
fit.c4_psi.setConstant(1)
fit.y.setConstant(1)
fit.c1_theta.setConstant(1)
fit.c2_theta.setConstant(1)
fit.c1_phi.setConstant(1)
fit.c2_phi.setConstant(1)
fit.c3_phi.setConstant(1)


fit.c1_psi.setVal(0)#-5.09861e-01)
fit.c2_psi.setVal(0)#-7.42080e-01)
fit.c3_psi.setVal(0)#-1.58601e-01)
fit.c4_psi.setVal(0)#1.56236e-01)
fit.y.setVal(1.)#5.90330e-03)
fit.c1_theta.setVal(0)
fit.c2_theta.setVal(0)#6.05183e-02)


fit.c4_phi.setVal(0.)
fit.c4_phi.setConstant(1)
fit.c6_phi.setVal(0.)
fit.c6_phi.setConstant(1)
fit.c5_phi.setVal(0.)
fit.c5_phi.setConstant(1)


# fit.c4_psi.setVal(0.)
# fit.c4_psi.setConstant(1)

# fit.c1_phi.setVal(0.)
# fit.c1_phi.setConstant(1)
# fit.c2_phi.setVal(0.)#2.3)
# fit.c2_phi.setConstant(kTRUE)
# fit.c3_phi.setVal(0.)#-0.3)
# fit.c3_phi.setConstant(kTRUE)


# model = RooGenericPdf("model","model","(2*A02*CPsi*CPsi+(1-A02)*(1-CPsi*CPsi))*(1+c1_psi*CPsi+c2_psi*CPsi*CPsi+c3_psi*CPsi*CPsi*CPsi+c4_psi*CPsi*CPsi*CPsi*CPsi+c5_psi*CPsi*CPsi*CPsi*CPsi*CPsi)",RooArgList(fit.CPsi,fit.A02,fit.c1_psi,fit.c2_psi,fit.c3_psi,fit.c4_psi,fit.c5_psi))

# fitres = model.fitTo(dataset)


proj2d = fit.sigmodel.createProjection(RooArgSet(fit.CPsi))
histo = proj2d.createHistogram("histo2d",fit.Phi,RooFit.YVar(fit.CTheta))
histo10 = proj2d.createHistogram("histo2d",fit.Phi,RooFit.YVar(fit.CTheta),RooFit.Binning(10))
histo10.RebinY(10)
#histo.Draw("LEGO2")
histodata = TH2F("data h","data h", 100, -1*pi, 1*pi,100,-1,1)
histodata10 = TH2F("data h 10","data h 10", 10, -1*pi, 1*pi,10,-1,1)
histomc = TH2F("mc h","mc h", 100, -1*pi, 1*pi,100,-1,1)
histomc10 = TH2F("mc h 10","mc h 10", 10, -1*pi, 1*pi,10,-1,1)
fmct= TFile("~/vol5/BdJpsiKst_mcgen.root")
tmct = fmct.Get("Bd2JPsiKstar/Bd2JPsiKstar")
for entry in t:
    histodata.Fill(entry.PhiP, entry.CTheta)
    histodata10.Fill(entry.PhiP, entry.CTheta)
    
for entry in tmct:
    histomc.Fill(entry.PhiP, entry.cTh2P)
    histomc10.Fill(entry.PhiP, entry.cTh2P)
    
#histodata.Draw("LEGO2")

hd = histodata.Clone()
hd.Divide(histo)
#hd.Draw("COL2")
#fitres = fit.sigmodel.fitTo(dataset,RooFit.Minos(1),RooFit.Save())

hd10 = histodata10.Clone()
hd10.Divide(histo10)

hm10 = histomc10.Clone()
hm10.Divide(histo10)
hm10.Scale(1e-04)
#hm10.Draw("TEXTBOX")
#BREAK
cv3 = TCanvas()
cv3.SetFillColor(0)
cv3.Divide(2,2)
cv3.cd(1)
histo.Draw("COL2")
cv3.cd(2)
histomc.Draw("COL2")
cv3.cd(3)
histodata.Draw("COL2")
cv3.cd(4)
hd.Draw("COL2")

## cv3.cd(1)
## cpsif = fit.CPsi.frame()
## RooAbsData.plotOn(dataset,cpsif)
## fit.sigmodel.plotOn(cpsif)
## cpsif.Draw()

## cv3.cd(2)
## cthf = fit.CTheta.frame()
## RooAbsData.plotOn(dataset,cthf)
## fit.sigmodel.plotOn(cthf)
## cthf.Draw()

## cv3.cd(3)
## cphif = fit.Phi.frame()
## RooAbsData.plotOn(dataset,cphif)
## fit.sigmodel.plotOn(cphif)
## cphif.Draw()


# cv3 = TCanvas()
# cv3.SetFillColor(0)
# cpsif = fit.CPsi.frame()
# RooAbsData.plotOn(dataset,cpsif)
# model.plotOn(cpsif)
## # cpsif.Draw()

##  FCN=435407 FROM MINOS     STATUS=SUCCESSFUL   2719 CALLS       21761 TOTAL
##                      EDM=3.33001e-05    STRATEGY= 1  ERROR MATRIX UNCERTAINTY   1.4 per cent
##   EXT PARAMETER                  PARABOLIC         MINOS ERRORS        
##   NO.   NAME      VALUE            ERROR      NEGATIVE      POSITIVE   
##    1  c1_phi       1.23330e-01   3.72942e-03  -3.77103e-03   3.75624e-03
##    2  c1_psi      -4.97381e-01   1.36930e-02  -1.38411e-02   1.35957e-02
##    3  c2_phi       2.31152e+00   1.84938e-02  -1.84369e-02   1.84790e-02
##    4  c2_psi      -6.25301e-01   2.10539e-02  -2.17888e-02   2.13129e-02
##    5  c2_theta    -1.82259e-01   7.33383e-03  -7.45632e-03   7.43984e-03
##    6  c3_phi      -5.77264e-01   3.41923e-02  -3.42958e-02   3.43423e-02
##    7  c3_psi      -3.27689e-01   4.40232e-02  -4.40167e-02   4.51536e-02
##    8  c4_psi       7.79382e-02   2.26524e-02  -2.30551e-02   2.36100e-02
##    9  y            3.34189e-09   1.55088e-04   at limit      1.55849e-04
##                                  WARNING -   - ABOVE PARAMETER IS AT LIMIT.
##                                ERR DEF= 0.5
## [#1] INFO:Minization -- RooMinuit::optimizeConst: deactivating const optimization
