from ROOT import *
import sys
#Amass = 9000
#Nsig = 50
if sys.argv[1:]: Amass   = float(sys.argv[1])
if sys.argv[2:]: Nsig    = float(sys.argv[2])
if sys.argv[3:]: toyData = str(sys.argv[3])
if sys.argv[4:]: TOYS    = int(sys.argv[4])
from SomeUtils.UnbinnedCLs import LimitCalculator
#import OurSites
#gROOT.SetBatch()
gROOT.ProcessLine(".x $LHCBSTYLEROOT/src/lhcbStyle.C")

tupleName = "A1"
#basedir = "/scratch19/mborsato/TEMP/"
#inputTuple = "/scratch19/mborsato/RealData_2011_s21r1_Erasmus_v11r2_975pb_A1_MVA.root"
#print 'input tuple : ', inputTuple

#outfileBaseName="./FIT_PLOTS/" + 'DATA2011'
#massrange = {'min':5500, 'max':15000}
massrange = {'min':8500, 'max':11000}

#TOYS = 1000
fixParsFromFile = 0
UNBINNED = 0
NBINS = 400
PRESCALE = 1.
UBDT_CUT = [1., 0.6] # flag, cut value

CentralMass = {'Y1': 9460.30, 'Y2': 10023.5, 'Y3': 10355.2, 'A8': 8000., 'A10': 10000., 'A12': 12000.} # Numbers updated!

mvar = "Bmass"
if UBDT_CUT[0]: selectPartOfTheDataSample = '!(evtNum%{0}) && UBDT>{1}'.format(PRESCALE, UBDT_CUT[1])
else          : selectPartOfTheDataSample = '!(evtNum%{0})'.format(PRESCALE)
massrangeCut = 'Bmass>{0} && Bmass<{1}'.format(massrange["min"], massrange["max"])
print "selecting 1/", PRESCALE, " of the given sample"

TriggerDecisions = 'V0_l0phys_dec==1 && V0_l1phys_dec==1 && V0_l2phys_dec==1'
PreSelectionCut  = 'PIDmu1>0. && PIDmu2>0. && PIDk1<10. && PIDk2<10. && log10(Blife_ps)<-1.'
PreSelection = PreSelectionCut + ' && ' + TriggerDecisions
cut = PreSelection  + '&&'  + selectPartOfTheDataSample+"&&"+massrangeCut
tag = "_data_prescale{0}_massrange{1}_{2}".format(PRESCALE,massrange["min"], massrange["max"])

#outfileName = outfileBaseName + tag + ".root"
#f = TFile(outfileName, "recreate")

#t2 = TChain(tupleName)
#t2.Add(inputTuple)

#print 'copying tree with cut ', cut
#t = t2.CopyTree(cut)
#print 'before cut : ', t2.GetEntries(), ", after cut : ", t.GetEntries()

mass = RooRealVar(mvar,mvar,massrange["min"],massrange["max"])

#if UNBINNED:
#       data = RooDataSet("data", "data", t, RooArgSet(mass))
#       print "t entries", t.GetEntries()
#       print "data entries", data.numEntries()
#else:
#       histo = TH1F('h'+mvar,'h'+ mvar,NBINS,massrange["min"], massrange["max"])
#       for entry in t:
#              var = getattr(entry, mvar)
#              histo.Fill(var)
#       rooHist = RooDataHist('h'+mvar, 'h'+mvar, RooArgList(mass), histo)

def estimateSigma0(inputmass):
       slope = 0.00235
       y0 = 3.73
       sigma0 = inputmass*slope + y0
       return sigma0

###### DEFINE PDF
gROOT.ProcessLine(".L $URANIAROOT/src/RooIpatia2.cxx+")

Y1ipa_m = RooRealVar("Y1ipa_m","Y1ipa_m", 9.48427e+03)#CentralMass['Y1'], CentralMass['Y1']-30,CentralMass['Y1']+30)
Y1l = RooRealVar("Y1l","Y1l",-1.15770e+00)#-1.30,-2,-1.)
ipa_s = RooRealVar("ipa_s","ipa_s",9.13177e+01)# 70., 40., 100.)
zeta = RooRealVar("zeta","zeta",2.5e-4)
beta = RooRealVar("beta","beta",-2.48578e-03)#-1.7e-3,-2.5e-3, -0.1e-3)
a = RooRealVar("a","a",1.6)
a2 = RooRealVar("a2","a2",100.)
n = RooRealVar("n","n",1) #leaving just n parameter of left tail free
n2 = RooRealVar("n2","n2",1) ## remove right tail
Y1ipatia = RooIpatia2("Y1ipatia","Y1ipatia", mass, Y1l, zeta, beta, ipa_s, Y1ipa_m, a, n, a2, n2)
Y1sigma0= RooRealVar("Y1sigma0","Y1sigma0",estimateSigma0(9.48427e+03))
Y1mean0= RooRealVar("Y1mean0","Y1mean0",0)
Y1res0 = RooGaussian("Y1reso0","Y1reso0",mass,Y1mean0,Y1sigma0)
Y1ipa2 = RooFFTConvPdf("Y1ipa2","Y1ipa2",mass, Y1ipatia, Y1res0)
#nY1 = RooRealVar("nY1","nY1",0., 10.e7/float(PRESCALE))
#Y1sig = RooExtendPdf("Y1","Y1",Y1ipa2,nY1)
f1 = RooRealVar("f1","f1",7.29373e-01)#0,1)
f2 = RooRealVar("f2","f2",1.51016e-01)#0,1)
f3 = RooRealVar("f3","f3", 8.41275e-01)#0,1)

Y2ipa_m = RooRealVar("Y2ipa_m","Y2ipa_m",1.00466e+04)#CentralMass['Y2'], CentralMass['Y2']-60,CentralMass['Y2']+60)
Y2l = RooRealVar("Y2l","Y2l",-1.19982e+00)#-1.25,-3,-1.)
Y2ipatia = RooIpatia2("Y2ipatia","Y2ipatia", mass, Y2l, zeta, beta, ipa_s, Y2ipa_m, a, n, a2, n2)
Y2sigma0= RooRealVar("Y2sigma0","Y2sigma0",estimateSigma0(1.00466e+04))
Y2mean0= RooRealVar("Y2mean0","Y2mean0",0)
Y2res0 = RooGaussian("Y2reso0","Y2reso0",mass,Y2mean0,Y2sigma0)
Y2ipa2 = RooFFTConvPdf("Y2ipa2","Y2ipa2",mass, Y2ipatia, Y2res0)
#nY2 = RooRealVar("nY2","nY2",0., 10.e6/float(PRESCALE))
#Y2sig = RooExtendPdf("Y2","Y2",Y2ipa2,nY2)
Y12 = RooAddPdf("Y12","Y12",Y1ipa2,Y2ipa2,f1)

Y3ipa_m = RooRealVar("Y3ipa_m","Y3ipa_m",1.03806e+04)#CentralMass['Y3'], CentralMass['Y3']-60,CentralMass['Y3']+60)
Y3l = RooRealVar("Y3l","Y3l",-1.25112e+00 )#-1.3,-2,-1.)
Y3ipatia = RooIpatia2("Y3ipatia","Y3ipatia", mass, Y3l, zeta, beta, ipa_s, Y3ipa_m, a, n, a2, n2)
Y3sigma0= RooRealVar("Y3sigma0","Y3sigma0",estimateSigma0(1.03806e+04))
Y3mean0= RooRealVar("Y3mean0","Y3mean0",0)
Y3res0 = RooGaussian("Y3reso0","Y3reso0",mass,Y3mean0,Y3sigma0)
Y3ipa2 = RooFFTConvPdf("Y3ipa2","Y3ipa2",mass, Y3ipatia, Y3res0)
#nY3 = RooRealVar("nY3","nY3",0., 10.e6/float(PRESCALE))
#Y3sig = RooExtendPdf("Y3","Y3",Y3ipa2,nY3)
Ypsilons = RooAddPdf("Ypsilons","Ypsilons",Y3ipa2,Y12,f2)

indx = RooRealVar("indx", "indx", -1.26176e-04)#-0.001,-1.e-3,0.)
exp1 = RooExponential("exp1","exp1", mass,indx)
#indx2 = RooRealVar("indx2", "indx2", -0.001,-1.,0.)
#exp2 = RooExponential("exp2","exp2", mass,indx2)
nbkg = RooRealVar("nbkg","nbkg",0, 10.e6/float(PRESCALE))
bkgpdf = RooAddPdf("_bkg","_bkg", Ypsilons,exp1,f3)
#
#Amass = 9000
Aipa_m = RooRealVar("Aipa_m","Aipa_m",Amass)
Aipatia = RooIpatia2("Aipatia","Aipatia", mass, Y1l, zeta, beta, ipa_s, Aipa_m, a, n, a2, n2)
Asigma0= RooRealVar("Asigma0","Asigma0",estimateSigma0(Amass))
Amean0= RooRealVar("Amean0","Amean0",0)
Ares0 = RooGaussian("Areso0","Areso0",mass,Amean0,Asigma0)
Aipa2 = RooFFTConvPdf("Aipa2","Aipa2",mass, Aipatia, Ares0)
nsig = RooRealVar("nA","nA",0., 1.e5)
model = RooAddPdf("model", "model", RooArgList(Aipa2,bkgpdf),RooArgList(nsig,nbkg))

## ## ### fitting
## fr = mass.frame()
## if UNBINNED:
##     data.plotOn(fr, RooFit.Binning(NBINS), RooFit.LineWidth(1), RooFit.MarkerSize(0.2))
##     model.fitTo(data,RooFit.Extended(kTRUE), RooFit.Minos(0), RooFit.Offset(kTRUE))
## else:
##     rooHist.plotOn(fr, RooFit.Binning(NBINS), RooFit.LineWidth(1), RooFit.MarkerSize(0.2))
##     model.fitTo(rooHist,RooFit.Extended(kTRUE), RooFit.Minos(0), RooFit.Offset(kTRUE))
##     model.plotOn(fr)
## fr.Draw()
## #BREAK

RooRandom.randomGenerator().SetSeed(int(Amass))
#f = TFile("data_HPT.root")
f = TFile(toyData) # we pass the name as an argument here
#data = model.generateBinned(RooArgSet(mass))
#data.Write()
#f.Close()
#BREAK

data = f.Get("genData") #model.generateBinned(RooArgSet(mass))
CL = LimitCalculator(nsig,nbkg, RooArgSet(mass), model, 5.46413e+04, binned = True)

## cla = CL.ConfidenceLevelsClassic(data,Nsig, NToys = TOYS)
## ndll1 = list(CL.nullDLLs)
## tdll1 = list(CL.testDLLs)
## b = CL.ConfidenceLevels(data,Nsig, NToys = TOYS)
## ndll2 = list(CL.nullDLLs)
## tdll2 = list(CL.testDLLs)
#print cla, b
#dc = {}
dc = {}
#for Nsig in range(50, 110,5):
dc[Nsig] = CL.ConfidenceLevelsClassic(data,Nsig, NToys = TOYS)
       
#dc["clas"] = cla
#dc["free"] = b
import cPickle
#cPickle.dump(dc, file("output_" + str(Amass),"w"))
cPickle.dump(dc, file("output.nsig","w"))

## ### plotting

## print "...now plotting"
## plotnamebase = outfileBaseName + tag

## model.plotOn(fr, RooFit.LineWidth(1))

## hpull = fr.pullHist()
## frpull = mass.frame()
## frpull.addPlotable(hpull,"P")
## pullCanvas = TCanvas('c2','c2',1200,400)
## frpull.Draw()
## pullCanvas.Print(plotnamebase+"_pull.pdf")

## hresid = fr.residHist()
## frresid = mass.frame()
## frresid.addPlotable(hresid,"P")
## residCanvas = TCanvas('c3','c3',1200,400)
## frresid.Draw()
## residCanvas.Print(plotnamebase+"_resid.pdf")

## model.plotOn(fr, RooFit.LineWidth(1), RooFit.LineColor(2), RooFit.Components('A'), RooFit.Normalization(1000))
## model.plotOn(fr, RooFit.LineWidth(1), RooFit.LineColor(4), RooFit.Components('Y1'), RooFit.LineStyle(2))
## model.plotOn(fr, RooFit.LineWidth(1), RooFit.LineColor(4), RooFit.Components('Y2'), RooFit.LineStyle(3))
## model.plotOn(fr, RooFit.LineWidth(1), RooFit.LineColor(4), RooFit.Components('Y3'), RooFit.LineStyle(4))
## canvas = TCanvas('c1','c1',1200,400 )
## fr.Draw()
## canvas.Print(plotnamebase + ".pdf")
## canvas.SetLogy()
## canvas.Print(plotnamebase + "_logy.pdf")

