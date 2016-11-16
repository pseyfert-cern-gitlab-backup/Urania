import ROOT
from RooFitUtils import ResidualPlot
from ROOT import TFile, RooFit, RooExtendPdf, RooRealVar, RooAddPdf, RooArgList, RooExponential, gROOT, TTree, RooLandau, RooGenericPdf,RooCBShape
from ROOT import RooDataSet , RooArgSet, RooBinning, TPaveText, RooPolynomial, RooChebychev, RooExponential, TCanvas, RooPlot, RooFitResult, RooAddPdf, RooArgList, TColor, EColor

print "before processing the class"
gROOT.ProcessLine(".x BifurcatedCB.cxx+")
gROOT.ProcessLine(".x lhcbStyle.C+")
gROOT.SetBatch()
from ROOT import BifurcatedCB

import argparse
parser = argparse.ArgumentParser(description='fit')
parser.add_argument('category', type=str, choices = ['TIS_', 'TOS1_', 'TOS2_'],
                    help='Trigger category' )
parser.add_argument('bin', type=int, choices=[0,1,2,3,4,5,6,7,8,9],
                   help='Bins go from 1 to 9')
args = parser.parse_args()
#DEFINE THE CUTS AND INTERVALS

import sys
sys.path.append('/afs/cern.ch/user/m/mramospe/UraniaDev_HEAD/Phys/Ks2MuMu/python/Ks2MuMu')
from fiducial import *
cuts = BDTplusMuID_cuts(args.category)[args.bin][ 3: ]
#cuts = 'muminus_isMuon==1 &&  muplus_isMuon==1  &&  muplus_muonIDPlusBDT>0 && muminus_muonIDPlusBDT>0'

def plot_with_residuals(canvas, frame, roovar, nbins, r_min, r_max, r_blind_min, r_blind_max):
     canvas.SetName("canvas")
     canvas.Divide(1,2)
     
     canvas_1 = canvas.cd(1)
     canvas_1.SetPad(0.01,0.28,0.99,0.99)
     frame.Draw()
     
     canvas_2 = canvas.cd(2)
     canvas_2.SetPad(0.01,0.01,0.99,0.23)
     histo = frame.getHist('sidebandsData')     
     xaxis = frame.GetXaxis()

     nbins = histo.GetN()
     xMin = xaxis.GetXmin()
     xMax = xaxis.GetXmax()
     res = ROOT.TH1F("residuals", "", nbins, xMin, xMax)
     
     prim = canvas_1.GetListOfPrimitives()

     fst=[i for i in prim if i.GetName()=='sidebandsCurve'][0]
     snd=[i for i in prim if i.GetName()=='sidebandsCurve'][1]
     xbin = ROOT.Double(0.0)
     val = ROOT.Double(0.0)
     for idx in range (nbins):
          histo.GetPoint(idx, xbin, val)
          eup, edw = histo.GetErrorYhigh(idx), histo.GetErrorYlow(idx)
          err = max(eup, edw)
          if xbin<r_blind_min:
               fcn = fst.Eval(xbin)
          elif xbin>r_blind_max:
               fcn = snd.Eval(xbin)
          else:
               fcn=0
          if fcn-val>=0:
               err = eup
          else:
               err = edw 
          res.SetBinContent(idx+1,(fcn-val)/err)
 
     res.SetMinimum(-5)
     res.SetMaximum(+5)
     res.SetNdivisions(0,"x")   # 510 for having x values also
     res.SetNdivisions(504,"y")   # axis divisions was 510
     res.SetXTitle(" ")
     res.SetYTitle(" ")
     res.SetTitle(" ")
     res.SetLabelSize(0.15,"Y")
     
     res.Draw("P")
     
     line = ROOT.TLine(r_min,-3.,r_max,-3)
     line.SetLineStyle(1)
     line.SetLineColor(2)
     line.SetLineWidth(1)
     line.Draw()
     line2 = ROOT.TLine(r_min,+3.,r_max,+3)
     line2.SetLineStyle(1)
     line2.SetLineColor(2)
     line2.SetLineWidth(1)
     line2.Draw()
     return frame,res,line,line2



#DEFINE RANGES
m1=465
m2=490
m3=510
m4=600

#CHOOSE PDF
eopt= "BifurCB"
bkg = "cheb"

#INPUT FILE
#f1=TFile("/afs/cern.ch/work/j/jpriscia/Ks0mumu_Data2012_Splitted_Res20_MuPtCutOff2500_TisTisTos_MVA_TEST.root","READ")
#f1=TFile("/afs/cern.ch/user/j/jpriscia/eos/lhcb/wg/RD/K0SMuMu/NEW/DIEGO/Ks0mumu_Data2012_Splitted_Res20_MuPtCutOff2500_TisTisTos_MVA.root","READ")
#f1=TFile("/afs/cern.ch/user/j/jpriscia/eos/lhcb/wg/RD/K0SMuMu/NEW/DIEGO/Ks0mumu_Data2012_Splitted_Res20_MuPtCutOff2500_TosTos1Tos_MVA.root","READ")
f1=TFile("../prof_mm" + args.category + str(args.bin) + '.root',"READ")
#f1=TFile("/afs/cern.ch/user/j/jpriscia/eos/lhcb/wg/RD/K0SMuMu/NEW/DIEGO/Ks0mumu_Data2012_Splitted_Res20_MuPtCutOff2500_TosTos2Tos_MVA.root","READ")
t0=f1.Get("DecayTree")

useless_file=TFile("useless_file.root","RECREATE")
t=None 
if len(cuts): t=t0.CopyTree(cuts)
else: t=t0

#tSig=t.CopyTree("KS0_massMM>490 && KS0_massMM<510")
tSig=t.CopyTree("KS0_M>490 && KS0_M<510")
tSig.GetEntries()

kMass = RooRealVar("KS0_M", "M(K_{s}^{0})", m1,m4, "MeV/c^{2}")
kMass.setRange("left", m1,m2)
kMass.setRange("signal", m2,m3)
kMass.setRange("right", m3,m4)



######################SIGNAL########################

if eopt=="BifurCB":
     #mK = RooRealVar("mK","mK",461,440,490)
     mK = RooRealVar("mK","mK", 460, 455, 465)
     sigmaK = RooRealVar("sigmaK","sigmaK", 0.9, 0.7, 1.1)
     #alphaLK = RooRealVar("alphaLK","alphaLK",1.81,0.01,3)
     #nLK = RooRealVar("nLK","nLK",2,0.01,50)
     alphaRK = RooRealVar("alphaRK","alphaRK",-0.3, -0.4, -0.2) #-1.2
     nRK = RooRealVar("nRK","nRK", 38, 5., 48)
     signalK = RooCBShape("signalK","signalK",kMass,mK,sigmaK,alphaRK,nRK)


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
     mean3 = RooRealVar ("mean3", "mean3", 400., -1., 600.)
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

if bkg=='expo': 
     slopeK =  RooRealVar("slopeK", "slopeK",   -0.000002,-0.05,-0.0000000001)
     ChebK = RooExponential("ChebK", "ChebK", kMass,slopeK)
  

elif bkg=='cheb': 
     slopeK = RooRealVar("slopeK", "slopeK", -1e-5, -1.e-4, 0.)
     ChebK = RooChebychev("ChebK", "ChebK", kMass, RooArgList(slopeK))
  
else: print 'bkg not defined'



#events and PDF


NSig = RooRealVar ("NSig","NSig",3700,0,100000)
NCombBkg = RooRealVar("NCombBkg","NCombBkg",200,0,100000)

model = RooAddPdf("model","model",RooArgList(signalK,ChebK),RooArgList(NSig,NCombBkg))

data = RooDataSet("data","data", t, RooArgSet(kMass))
rf =  model.fitTo(data,RooFit.Range("left,right"),RooFit.Extended(),RooFit.Save())
#rf =  model.fitTo(data,RooFit.Extended(),RooFit.Save())
#plotting

kFrame = kMass.frame()
data.plotOn(kFrame,RooFit.CutRange("left,right"),RooFit.Name("sidebandsData"),RooFit.Binning(m4-m1))
#data.plotOn(kFrame,RooFit.Binning(m4-m1),RooFit.Name("provaData"))
model.plotOn(kFrame,RooFit.Components("signalK"),RooFit.LineStyle(9),RooFit.LineWidth(2),RooFit.LineColor(2), RooFit.Range("left,right"),RooFit.NormRange("left,right"))
model.plotOn(kFrame,RooFit.Components("ChebK"),RooFit.LineStyle(9),RooFit.LineWidth(2), RooFit.LineColor(4), RooFit.Range("left,right"),RooFit.NormRange("left,right"))
model.plotOn(kFrame,RooFit.Name("sigReg"),RooFit.Range("signal"),RooFit.NormRange("left,right"), RooFit.LineColor(3))
model.plotOn(kFrame,RooFit.Range("left,right"),RooFit.Name("sidebandsCurve"),RooFit.NormRange("left,right"))
#model.plotOn(kFrame,RooFit.NormRange("left,right"),RooFit.Name("sidebandsCurve"))
model.plotOn(kFrame,RooFit.Name("prova"))



kCanvas = TCanvas("kCanvas", "kCanvas", 800,600)
pippo = plot_with_residuals(kCanvas, kFrame, kMass,135 ,465,600,490,510)
#sigplot = ResidualPlot("Ks->pipi CB",kFrame)
#sigplot.addResidual("sidebandsData","prova",465,600)
#sigplot.plot(yLogScale=False, residualBand=False)
#kFrame.Draw()



pars = rf.floatParsFinal()
n = pars.find("NSig").getVal()
dn =pars.find("NSig").getError()

argset = RooArgSet(kMass)
xtra_int = model.createIntegral(argset,RooFit.NormSet(argset), RooFit.Range("signal")) 
full_int = model.createIntegral(argset,RooFit.NormSet(argset), RooFit.Range("signal,left,right")) 


print " events_from_fit  = ",  xtra_int.getVal()* n/full_int.getVal() 
print " err_events_from_fit  = ",  xtra_int.getVal()* dn/full_int.getVal()
print "number of events in signal region: ", "THAT IS BLIND !!!!!!"#tSig.GetEntries()

ofile = open( 'KsMuMuResults.py', 'at+' )
ofile.write( 'class KsPiPiMisid_' + args.category + str(args.bin) + ':\n' )
for i in xrange(len(pars)):
     var = pars.at(i)
     ofile.write( '\t' + var.GetName() + ' = ' + str(var.getVal()) + '\n' )
ofile.write('\n')
ofile.close()
#raw_input('Press enter to continue')
ofile = TFile( 'OutputPlots.root', 'UPDATE' )
kCanvas.Write(args.category + str(args.bin))
ofile.Close()
