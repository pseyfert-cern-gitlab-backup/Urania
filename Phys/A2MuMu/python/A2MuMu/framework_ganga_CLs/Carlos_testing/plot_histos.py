from ROOT import *

toyData_test = 'data_test.root'
toyData_HPT = 'data_HPT.root'
Amass = 9000.
PRESCALE = 1
NBINS = 400
mvar = "Bmass"
massrange = {'min':8500, 'max':11000}
mass = RooRealVar(mvar,mvar,massrange["min"],massrange["max"])

#def estimateSigma0(inputmass):
#       slope = 0.00235
#       y0 = 3.73
#       sigma0 = inputmass*slope + y0
#       return sigma0

#gROOT.ProcessLine(".L $URANIAROOT/src/RooIpatia2.cxx+")

#Y1ipa_m = RooRealVar("Y1ipa_m","Y1ipa_m", 9.48427e+03)
#Y1l = RooRealVar("Y1l","Y1l",-1.15770e+00)
#ipa_s = RooRealVar("ipa_s","ipa_s",9.13177e+01)
#zeta = RooRealVar("zeta","zeta",2.5e-4)
#beta = RooRealVar("beta","beta",-2.48578e-03)
#a = RooRealVar("a","a",1.6)
#a2 = RooRealVar("a2","a2",100.)
#n = RooRealVar("n","n",1) ## leaving just n parameter of left tail free
#n2 = RooRealVar("n2","n2",1) ## remove right tail
#Y1ipatia = RooIpatia2("Y1ipatia","Y1ipatia", mass, Y1l, zeta, beta, ipa_s, Y1ipa_m, a, n, a2, n2)
#Y1sigma0= RooRealVar("Y1sigma0","Y1sigma0",estimateSigma0(9.48427e+03))
#Y1mean0= RooRealVar("Y1mean0","Y1mean0",0)
#Y1res0 = RooGaussian("Y1reso0","Y1reso0",mass,Y1mean0,Y1sigma0)
#Y1ipa2 = RooFFTConvPdf("Y1ipa2","Y1ipa2",mass, Y1ipatia, Y1res0)
#f1 = RooRealVar("f1","f1",7.29373e-01)
#f2 = RooRealVar("f2","f2",1.51016e-01)
#f3 = RooRealVar("f3","f3", 8.41275e-01)

#Y2ipa_m = RooRealVar("Y2ipa_m","Y2ipa_m",1.00466e+04)
#Y2l = RooRealVar("Y2l","Y2l",-1.19982e+00)
#Y2ipatia = RooIpatia2("Y2ipatia","Y2ipatia", mass, Y2l, zeta, beta, ipa_s, Y2ipa_m, a, n, a2, n2)
#Y2sigma0= RooRealVar("Y2sigma0","Y2sigma0",estimateSigma0(1.00466e+04))
#Y2mean0= RooRealVar("Y2mean0","Y2mean0",0)
#Y2res0 = RooGaussian("Y2reso0","Y2reso0",mass,Y2mean0,Y2sigma0)
#Y2ipa2 = RooFFTConvPdf("Y2ipa2","Y2ipa2",mass, Y2ipatia, Y2res0)
#Y12 = RooAddPdf("Y12","Y12",Y1ipa2,Y2ipa2,f1)

#Y3ipa_m = RooRealVar("Y3ipa_m","Y3ipa_m",1.03806e+04)
#Y3l = RooRealVar("Y3l","Y3l",-1.25112e+00 )
#Y3ipatia = RooIpatia2("Y3ipatia","Y3ipatia", mass, Y3l, zeta, beta, ipa_s, Y3ipa_m, a, n, a2, n2)
#Y3sigma0= RooRealVar("Y3sigma0","Y3sigma0",estimateSigma0(1.03806e+04))
#Y3mean0= RooRealVar("Y3mean0","Y3mean0",0)
#Y3res0 = RooGaussian("Y3reso0","Y3reso0",mass,Y3mean0,Y3sigma0)
#Y3ipa2 = RooFFTConvPdf("Y3ipa2","Y3ipa2",mass, Y3ipatia, Y3res0)
#Ypsilons = RooAddPdf("Ypsilons","Ypsilons",Y3ipa2,Y12,f2)

#indx = RooRealVar("indx", "indx", -1.26176e-04)
#exp1 = RooExponential("exp1","exp1", mass,indx)
#nbkg = RooRealVar("nbkg","nbkg",0, 10.e6/float(PRESCALE))
#bkgpdf = RooAddPdf("_bkg","_bkg", Ypsilons,exp1,f3)
#Aipa_m = RooRealVar("Aipa_m","Aipa_m",Amass)
#Aipatia = RooIpatia2("Aipatia","Aipatia", mass, Y1l, zeta, beta, ipa_s, Aipa_m, a, n, a2, n2)
#Asigma0= RooRealVar("Asigma0","Asigma0",estimateSigma0(Amass))
#Amean0= RooRealVar("Amean0","Amean0",0)
#Ares0 = RooGaussian("Areso0","Areso0",mass,Amean0,Asigma0)
#Aipa2 = RooFFTConvPdf("Aipa2","Aipa2",mass, Aipatia, Ares0)
#nsig = RooRealVar("nA","nA",0., 1.e5)
#model_test = RooAddPdf("model_test", "model_test", RooArgList(Aipa2,bkgpdf),RooArgList(nsig,nbkg))
#model_HPT = RooAddPdf("model_HPT", "model_HPT", RooArgList(Aipa2,bkgpdf),RooArgList(nsig,nbkg))

c = TCanvas()
c.SetGrid()
c.Divide(1,2)
c.cd(1)
f_test = TFile(toyData_test)
data_test = f_test.Get('genData')
fr_test = mass.frame()
data_test.plotOn(fr_test, RooFit.Binning(NBINS), RooFit.LineWidth(1), RooFit.MarkerSize(0.2), RooFit.MarkerColor(kBlue), RooFit.LineColor(kBlue))
#model_test.fitTo(data_test, RooFit.Extended(kTRUE), RooFit.Minos(0), RooFit.Offset(kTRUE))
#model_test.plotOn(fr_test)
fr_test.Draw()
dGraph = TGraph(1)
tLegend = TLegend(0.7,0.7,0.85,0.85)
tLegend.SetFillStyle(0)
tLegend.SetBorderSize(0)
tLegend.AddEntry(dGraph,'Unbinned pT case','')
tLegend.Draw('same')
##
c.cd(2)
f_HPT = TFile(toyData_HPT)
data_HPT = f_HPT.Get('genData')
fr_HPT = mass.frame()
data_HPT.plotOn(fr_HPT, RooFit.Binning(NBINS), RooFit.LineWidth(1), RooFit.MarkerSize(0.2), RooFit.MarkerColor(kRed), RooFit.LineColor(kRed))
#model_HPT.fitTo(data_HPT, RooFit.Extended(kTRUE), RooFit.Minos(0), RooFit.Offset(kTRUE))
#model_HPT.plotOn(fr_HPT)
fr_HPT.Draw()
tLegend2 = TLegend(0.7,0.7,0.85,0.85)
tLegend2.SetFillStyle(0)
tLegend2.SetBorderSize(0)
tLegend2.AddEntry(dGraph,'High pT bin case','')
tLegend2.Draw('same')
##
dummy = raw_input('Press any key...')
c.Print('data_'+str(Amass)+'.pdf')
f_test.Close()
f_HPT.Close()
