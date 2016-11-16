import ROOT
from ROOT import TFile, RooFit, RooExtendPdf, RooRealVar, RooAddPdf, RooArgList, RooExponential, gROOT, TTree, RooLandau, RooGenericPdf, RooBreitWigner
from ROOT import RooDataSet , RooArgSet, RooBinning, TPaveText, RooPolynomial, RooChebychev, RooExponential, TCanvas, RooPlot, RooFitResult, RooAddPdf, RooArgList, TColor, EColor

print "before processing the class"
gROOT.ProcessLine(".x BifurcatedCB.cxx+")
gROOT.ProcessLine(".x lhcbStyle.C+")
from ROOT import BifurcatedCB

import argparse
parser = argparse.ArgumentParser(description='fit')
parser.add_argument('bin', type=int, choices=[1,2,3,4,5,6,7,8,9],
                   help='Bins go from 1 to 9')

args = parser.parse_args()

#DEFINE THE CUTS AND INTERVALS
cuts = 'muminus_isMuon==1 &&  muplus_isMuon==1  &&  muplus_muonIDPlusBDT>-1 && muminus_muonIDPlusBDT>-1 && Bin==%d' %args.bin 

m1=400
m2=490
m3=510
m4=600 

#CHOOSE THE PDF
eopt= "BifurCB"
bkg = "expo"

#INPUT FILE
f1=TFile("/afs/cern.ch/work/j/jpriscia/KSMUMU/MC/MC_KspipiSMALL_TosTos1Tos.root","READ")
t0=f1.Get("DecayTree")

useless_file=TFile("useless_file.root","RECREATE")
t=None                                                                                                                                           
if len(cuts): t=t0.CopyTree(cuts)
else: t=t0



t=TTree()
if len(cuts): t=t0.CopyTree(cuts)
else: t=t0

#BLIND REGION
tSig=t.CopyTree("KS0_massMM>490 && KS0_massMM<510")
tSig.GetEntries()

kMass = RooRealVar("KS0_massMM", "M(K_{s}^{0})", m1,m4, "MeV/c^{2}")
kMass.setRange("left", m1,m2)
kMass.setRange("signal", m2,m3)
kMass.setRange("right", m3,m4)



######################SIGNAL  PDF########################

if eopt=="BifurCB":
     mK = RooRealVar("mK","mK",460,380,480)
     sigmaK = RooRealVar("sigmaK","sigmaK",5,2,10)
     alphaLK = RooRealVar("alphaLK","alphaLK",1.81,0.5,3)
     nLK = RooRealVar("nLK","nLK",2,0.1,10)
     alphaRK = RooRealVar("alphaRK","alphaRK",1.49,0.5,5)
     nRK = RooRealVar("nRK","nRK",2,0.1,10)
     signalK = BifurcatedCB("signalK","signalK",kMass,mK,sigmaK,alphaLK,nLK,alphaRK,nRK)


elif eopt=="polynomial":  
     indx0 = RooRealVar("k0", "indx0", 8.5,-10.,10.)
     indx1 = RooRealVar("k1", "indx1", 1.,-10.,10.)
     indx2 = RooRealVar("k2", "indx2", 7.5,-10.,10.)
     indx3 = RooRealVar("k3", "indx3", 0.5,-10.,10.)
     indx4 = RooRealVar("k4", "indx4", 0.5,-10.,10.)
     indx5 = RooRealVar("k5", "indx5", 0.5,-10.,10.)
     signalK = RooPolynomial("signalK", "signalK", kMass, RooArgList(indx0,indx1,indx2,indx3,indx4,indx5))
   

elif eopt=="landau":
     mean = RooRealVar ("mean", "mean", 460., 450., 500.)
     sigma = RooRealVar("sigma", "sigma", 2.5, 0., 15.)
     signalK = RooLandau("signalK","signalK", kMass, mean,sigma)
  
  
elif eopt=="breitWigner":
     meanB = RooRealVar ("meanB", "meanB", 460., 450., 470.)
     sigmaB = RooRealVar ("sigmaB", "sigmaB", 10., 5., 30.)
     signalK = RooBreitWigner("signalK","signalK", kMass, meanB,sigmaB)
     
  
elif eopt=="powerLaw":
     mean3 = RooRealVar ("mean3", "mean3", 460., 450., 500.)
     indx = RooRealVar("indx","indx",4.,0.,10.)
     signalK = RooGenericPdf("signalK","1.0/pow((kMass-mean3),indx)",RooArgList(kMass,mean3,indx)) 
    

elif eopt=="nPoly":
     indN =RooRealVar ("indN","indN",10.0,1.,50.)
     signalK = RooGenericPdf("signalK","1/(kMass^indN)",RooArgList(kMass,indN))
  

elif eopt=="lorentz":
     ind1 =RooRealVar ("ind1","ind1",0.1,-5.,5.)
     ind2=RooRealVar ("ind2","ind2",250.0,1.,2000.)
     ind3=RooRealVar ("ind3","ind3",465.0,1.,1000.)
     ind4=RooRealVar ("ind4","ind4",0.1,-5.,5.)
     signalK("signalK","ind1+ind2/(1+((kMass-ind3)/ind4)^2)",RooArgList(kMass,ind1,ind2,ind3,ind4)) 
  
else: print 'signal not defined'

######################BKG  PDF########################  

if bkg=='expo': 
     slopeK =  RooRealVar("slopeK", "slopeK",   -0.000002,-0.05,-0.0000001)
     ChebK = RooExponential("ChebK", "ChebK", kMass,slopeK)
  

elif bkg=='cheb': 
     slopeK = RooRealVar("slopeK", "slopeK", 0.5,-0.1, 0.8)
     ChebK = RooChebychev("ChebK", "ChebK", kMass, RooArgList(slopeK))
  
else: print 'bkg not defined'




######################EVENTS AND MODEL########################  

NSig = RooRealVar ("NSig","NSig",700,0,10000)
NCombBkg = RooRealVar("NCombBkg","NCombBkg",0.00000000001,0,100)

model = RooAddPdf("model","model",RooArgList(signalK,ChebK),RooArgList(NSig,NCombBkg))

data = RooDataSet("data","data", t, RooArgSet(kMass))
rf =  model.fitTo(data,RooFit.Range("left,right"),RooFit.Extended(),RooFit.Save())

######################PLOT#################################

kFrame = kMass.frame()
data.plotOn(kFrame,RooFit.Binning(m4-m1))
model.plotOn(kFrame,RooFit.Components("signalK"),RooFit.LineStyle(9),RooFit.LineWidth(2),RooFit.LineColor(2), RooFit.Range("left,right"),RooFit.NormRange("left,right"))
model.plotOn(kFrame,RooFit.Components("ChebK"),RooFit.LineStyle(9),RooFit.LineWidth(2), RooFit.LineColor(4), RooFit.Range("left,right"),RooFit.NormRange("left,right"))
model.plotOn(kFrame,RooFit.Range("left,right"),RooFit.NormRange("left,right"))
model.plotOn(kFrame,RooFit.Name("sigReg"),RooFit.Range("signal"),RooFit.NormRange("left,right"), RooFit.LineColor(3))

kCanvas = TCanvas("kCanvas", "kCanvas", 800,600)
kFrame.Draw()


######################EXTRAPOLATION IN SIGNAL REGION################################# 

pars = rf.floatParsFinal()
n = pars.find("NSig").getVal()
dn =pars.find("NSig").getError()

argset = RooArgSet(kMass)
xtra_int = model.createIntegral(argset,RooFit.NormSet(argset), RooFit.Range("signal")) 
full_int = model.createIntegral(argset,RooFit.NormSet(argset), RooFit.Range("signal,left,right")) 


print " events_from_fit  = ",  xtra_int.getVal()* n/full_int.getVal() 
print " err_events_from_fit  = ",  xtra_int.getVal()* dn/full_int.getVal()
print "number of events in sidebands: ", tSig.GetEntries()
