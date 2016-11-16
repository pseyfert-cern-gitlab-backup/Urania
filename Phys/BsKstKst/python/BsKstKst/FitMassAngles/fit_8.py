from ROOT import *
from math import *
from array import *

gSystem.Load("libRooStats")
gROOT.ProcessLine('.x $SOMEMASSMODELSROOT/src/RooPhysBkg.cxx+')
gROOT.ProcessLine('.x histos/RooErrXLin.cxx+')
gROOT.ProcessLine(".x lhcbStyle.C");

# file = TFile("histos_abraham_phi_str17.root")
# tree2 = file.Get("data")

# cuts = ["GLKsb.>0.14 && (Kplus_PIDp-Kplus_PIDK)<0. && (Kminus_PIDp-Kminus_PIDK)<0. && abs(Kstb_M-895.94)<150. && abs(Kst_M-895.94)<150. && Piplus_PIDK<-5. && Piminus_PIDK<-5. && Kplus_PIDK>5. && Kminus_PIDK>5. && Piplus_PIDp<10. && Piminus_PIDp<10."]
# #cuts = ["GLKsb.>0.224 && (Kplus_PIDp-Kplus_PIDK)<0. && (Kminus_PIDp-Kminus_PIDK)<0. && abs(Kstb_M-895.94)<100. && abs(Kst_M-895.94)<100. && Piplus_PIDK<-5. && Piminus_PIDK<-5. && Kplus_PIDK>5. && Kminus_PIDK>5. && Piplus_PIDp<10. && Piminus_PIDp<10."]

filehist = TFile("histos/histos_Lambda.root")
lambdash = filehist.Get("histo_inv_M_1")

filehistl2 = TFile("histos/histos_Lambda2.root")
lambdash2 = filehistl2.Get("histo_inv_M_1")

# file2 = TFile("resultado_8.root","RECREATE")
# file2.Close()

# for i in cuts:

#   tree = tree2.CopyTree(i)

Bmass = RooRealVar("B_s0_M","B_s0_M",5365-450,5365+450,"MeV/c^{2}")

mean_d   = RooRealVar("mean_d","mean_d",5275.-15.,5275.+15.,"MeV/c^{2}")
sigma    = RooRealVar("sigma","sigma",12.,20.,"MeV/c^{2}")
a        = RooRealVar("a","a",2.02672e+00)
f        = RooRealVar("f","f",2.69637e+00)
peak_d   = RooCBShape("peak_d", "Crystal Ball Function", Bmass, mean_d, sigma, a, f)

sigma_delta = RooRealVar("sigma_delta","sigma_delta",8.29921e+01,"MeV/c^{2}")
sigma1  = RooFormulaVar("sigma1","sigma1","sqrt(sigma*sigma+sigma_delta*sigma_delta)",RooArgList(sigma,sigma_delta))
peak_d1  = RooGaussian("peak_d1","B2PhiKst",Bmass,mean_d,sigma1)

f1 = RooRealVar("f1","f1",9.77980e-01)

peak_df  = RooAddPdf("peak_df","peak_df", RooArgList(peak_d,peak_d1), RooArgList(f1))

shift   = RooRealVar("shift","shift",87.13)

mean_s  = RooFormulaVar("mean_s","mean_d+shift",RooArgList(mean_d,shift))

peak_s  = RooCBShape("peakBs", "Crystal Ball Function", Bmass, mean_s, sigma, a, f)
peak_s1 = RooGaussian("peakBs1","B2PhiKst",Bmass,mean_s,sigma1)

peak_sf  = RooAddPdf("peak_sf","peak_sf", RooArgList(peak_s,peak_s1), RooArgList(f1))

c_bkg = RooRealVar("r_bkg","r_bkg",-0.00001,-10.,0.)
bkg = RooExponential("BkgMass","Bkg",Bmass,c_bkg)

#c_bkg = RooRealVar("r_bkg","r_bkg",-10.,10.);
#bkg = RooPolynomial("BkgMass","Bkg",Bmass,RooArgList(c_bkg))


lambdahist = RooDataHist("bckhist","bckhist",RooArgList(Bmass),lambdash)
lambdapdf  = RooHistPdf("bckpdf","bckpdf",RooArgSet(Bmass),lambdahist)

lambdahist2 = RooDataHist("bckhistl2","bckhistl2",RooArgList(Bmass),lambdash2)
lambdapdf2  = RooHistPdf("bckpdfl2","bckpdfl2",RooArgSet(Bmass),lambdahist2)

kkkst_mean  = RooRealVar("kkkst_mean", "kkkst_mean", 5220.,5265.)
kkkst_c     = RooRealVar("kkkst_c", "kkkst_c", 2.42916e-02)
kkkst_sigma = RooRealVar("kkkst_sigma", "kkkst_sigma", 6.9)
#NO.   NAME      VALUE            ERROR       STEP SIZE       VALUE
# 1  sh_c         2.42916e-02   8.73656e-04   2.69293e-05  -5.40038e-01
# 2  sh_mean      5.24712e+03   1.83267e+00   7.40543e-05  -3.60279e-01
# 3  sigma        6.90013e+00   1.68279e+00   2.43153e-04  -3.15179e-01
kkkstpdf =  RooPhysBkg("kkkstpdf","kkkstpdf",Bmass, kkkst_mean, kkkst_c, kkkst_sigma)

d0_l        = RooRealVar("d0_l","d0_l",0.,2.)
#d0_lt       = RooPolynomial("d0_lt","d0_lt",Bmass,RooArgList(d0_l))

#d0_mean     = RooRealVar("d0_mean", "d0_mean",5025,5100)
d0_mean     = RooRealVar("d0_mean", "d0_mean", 5000.,5100.)#5.04494e+03)
d0_sigma    = RooRealVar("d0_sigma", "d0_sigma",4.55491e+01)

# Use error function to simulate turn-on slope
#d0_shoulder = RooFormulaVar("d0_shoulder","0.5*(1-TMath::Erf(((Bmass-d0_mean)/d0_sigma-1)/0.5))",RooArgList(Bmass,d0_mean,d0_sigma))
#d0pdf =  RooEffProd("modelEff","model with efficiency",d0_lt,d0_shoulder)
d0pdf =  RooErrXLin("d0pdf","d0pdf",Bmass,d0_mean,d0_l,d0_sigma)

d02_mean  = RooFormulaVar("d02_mean","d0_mean-shift",RooArgList(d0_mean,shift))
d02_l     = RooRealVar("d02_l", "d02_l", 0., 2.)
d02pdf    = RooErrXLin("d02pdf","d02pdf pdf",Bmass, d02_mean, d02_l, d0_sigma)

#d0_l     = RooRealVar("d0_l","d0_l",0.,1.)
d0_l     = RooRealVar("d0_l","d0_l",5.71115e-04)
#d0_mean  = RooRealVar("d0_mean", "d0_mean", 5000.,5150.)#5.04494e+03)
d0_mean  = RooRealVar("d0_mean", "d0_mean", 5.04215e+03)
d0_sigma = RooRealVar("d0_sigma", "d0_sigma",4.71209e+01)
d0pdf    =  RooErrXLin("d0pdf","d0pdf",Bmass,d0_mean,d0_l,d0_sigma)

d02_mean  = RooFormulaVar("d02_mean","d0_mean-shift",RooArgList(d0_mean,shift))
#d02_l     = RooRealVar("d02_l", "d02_l", 0., 2.)
d02pdf    = RooErrXLin("d02pdf","d02pdf pdf",Bmass, d02_mean, d0_l, d0_sigma)

rho_mean  = RooRealVar("rho_mean", "rho_mean",5.33744e+03)
rho_sigma = RooRealVar("rho_sigma", "rho_sigma",2.02821e+01)
rho_a        = RooRealVar("rho_a","rho_a",-2.73736e-01)
rho_l     = RooRealVar("rho_l","rho_l",4.09225e+00)
rhokstpdf   = RooCBShape("rhokstpdf", "Crystal Ball Function", Bmass, rho_mean, rho_sigma, rho_a, rho_l)


# data = RooDataSet("RealOffSel","RealOffSel",tree,RooArgSet(Bmass))

n_s       = RooRealVar("n_s","N_{s}",20,0,5000)
n_d       = RooRealVar("n_d","N_{d}",200,0,1700)
n_bkg     = RooRealVar("N_{Bkg}","N_{bkg}",50,0,2000)
n_lambda  = RooRealVar("N_{lambda}","N_{lambda}",0,0,50)
n_lambda2 = RooRealVar("N_{lambda2}","N_{lambda2}",0,0,50)
n_kkkst   = RooRealVar("N_{kkkst}","N_{kkkst}",0,0,1000)
n_d0      = RooRealVar("N_{d0}","N_{d0}",100,0,400)
n_d02     = RooRealVar("N_{d02}","N_{d02}",100,0,200)
n_rhokst  = RooRealVar("N_{rhokst}","N_{rhokst}",0,0,300)

model = RooAddPdf("BmassModel","BmassModel",RooArgList(peak_df,peak_sf,bkg,lambdapdf,lambdapdf2,kkkstpdf,d0pdf,d02pdf,rhokstpdf),RooArgList(n_d,n_s,n_bkg,n_lambda,n_lambda2,n_kkkst,n_d0,n_d02,n_rhokst))
#model = RooAddPdf("BmassModel","BmassModel",RooArgList(peak_df,peak_sf,bkg,kkkstpdf,d0pdf,rhokstpdf),RooArgList(n_d,n_s,n_bkg,n_kkkst,n_d0,n_rhokst))


# data = RooDataSet("RealOffSel","RealOffSel",tree,RooArgSet(Bmass))
# resalt = model.fitTo(data,RooFit.Minos(),RooFit.Save(),RooFit.Extended())

# c=TCanvas()
# c.SetFillColor(0)
# gStyle.SetOptTitle(0)
# m=c.cd(1)
# frame = Bmass.frame()
# RooAbsData.plotOn(data,frame,RooFit.Binning(60))
# model.plotOn(frame,RooFit.Components("peak_df"),RooFit.FillStyle(1001),RooFit.FillColor(kCyan-8),RooFit.DrawOption("F"))
# model.plotOn(frame,RooFit.Components("peak_sf"),RooFit.FillStyle(3001),RooFit.FillColor(kRed),RooFit.DrawOption("F"))
# RooAbsData.plotOn(data,frame,RooFit.Binning(60))
#   model.plotOn(frame,RooFit.Components("kkkstpdf"),RooFit.LineColor(kMagenta))
#   model.plotOn(frame,RooFit.Components("d0pdf"),RooFit.LineColor(kOrange+10))
#   model.plotOn(frame,RooFit.Components("d02pdf"),RooFit.LineColor(kCyan))
#   model.plotOn(frame,RooFit.Components("BkgMass"),RooFit.LineColor(12),RooFit.LineStyle(2))
#   model.plotOn(frame,RooFit.Components("rhokstpdf"),RooFit.LineColor(kViolet-3))
#   model.plotOn(frame,RooFit.Components("shoulder"),RooFit.LineStyle(9),RooFit.LineColor(kGreen))
#   #model.plotOn(frame,RooFit.Components("bckpdf"),RooFit.LineColor(kYellow))
#   #model.plotOn(frame,RooFit.Components("bckpdfl2"),RooFit.LineColor(kGray))
#   #RooAbsData.plotOn(data,frame,RooFit.Binning(60))
#   plot=model.plotOn(frame)
#   file2 = TFile("resultado_8.root","UPDATE")
#   frame.Write(i)
#   file2.Close()

#   n_d.setVal(0.0)
#   n_d.setConstant(1)
#   resnull = model.fitTo(data,RooFit.Minos(),RooFit.Save(),RooFit.Extended())
#   frame2 = Bmass.frame()
#   RooAbsData.plotOn(data,frame2,RooFit.Binning(60))
#   model.plotOn(frame2,RooFit.Components("peak_df"),RooFit.FillStyle(1001),RooFit.FillColor(kCyan-8),RooFit.DrawOption("F"))
#   model.plotOn(frame2,RooFit.Components("peak_sf"),RooFit.FillStyle(3001),RooFit.FillColor(kRed),RooFit.DrawOption("F"))
#   RooAbsData.plotOn(data,frame2,RooFit.Binning(60))
#   model.plotOn(frame2,RooFit.Components("kkkstpdf"),RooFit.LineColor(kMagenta))
#   model.plotOn(frame2,RooFit.Components("d0pdf"),RooFit.LineColor(kOrange+10))
#   model.plotOn(frame2,RooFit.Components("d02pdf"),RooFit.LineColor(kCyan))
#   model.plotOn(frame2,RooFit.Components("BkgMass"),RooFit.LineColor(12),RooFit.LineStyle(2))
#   model.plotOn(frame2,RooFit.Components("rhokstpdf"),RooFit.LineColor(kViolet-3))
#   model.plotOn(frame2,RooFit.Components("shoulder"),RooFit.LineStyle(9),RooFit.LineColor(kGreen))
#   #model.plotOn(frame2,RooFit.Components("bckpdf"),RooFit.LineColor(kYellow))
#   #model.plotOn(frame2,RooFit.Components("bckpdfl2"),RooFit.LineColor(kGray))
#   #RooAbsData.plotOn(data,frame2,RooFit.Binning(60))
#   plot=model.plotOn(frame2)
#   file2 = TFile("resultado_8.root","UPDATE")
#   frame2.Write("nb_"+i)
#   file2.Close()

#   print "The variation of th logL is: ",resnull.minNll()-resalt.minNll()
#   print "The p-value of the null hypothesis is: ",TMath.Prob(2.*(resnull.minNll()-resalt.minNll()),1)
#   print "The significance of the signal is: ",RooStats.PValueToSignificance(TMath.Prob(2.*(resnull.minNll()-resalt.minNll()),1))
  
