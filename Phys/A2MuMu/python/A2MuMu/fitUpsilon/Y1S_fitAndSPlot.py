from ROOT import *
import sys
sys.path.append("..")
import CutsList
import OurSites
gROOT.SetBatch()


#tupleName = "A1/A1"
tupleName = "A1"
#tupleName = "Upsilon/Upsilon"
inputTuples = {
        'DATA2011': OurSites.MY_TUPLE_PATH + "RealData_2011_s21r1_Erasmus_v10r3_976pb.root",
        'DATA2012': OurSites.MY_TUPLE_PATH + "RealData_2012_s21_Erasmus_v10r3_1991pb.root",
        'Y1MC2011': OurSites.MY_TUPLE_PATH + "Upsilon_1S_MC_2011.root",
        'Y1MC2012': OurSites.MY_TUPLE_PATH + "Upsilon_1S_MC_2012.root",
        'Y2MC2011': OurSites.MY_TUPLE_PATH + "Upsilon_2S_MC_2011.root",
        'Y2MC2012': OurSites.MY_TUPLE_PATH + "Upsilon_2S_MC_2012.root",
        'Y3MC2011': OurSites.MY_TUPLE_PATH + "Upsilon_3S_MC_2011.root",
        'Y3MC2012': OurSites.MY_TUPLE_PATH + "Upsilon_3S_MC_2012.root",
        'A8MC2011': OurSites.MY_TUPLE_PATH + "A1MuMu_MC_2011_mumu8GeV_rwY1S.root",
        'A8MC2012': OurSites.MY_TUPLE_PATH + "A1MuMu_MC_2012_mumu8GeV_rwY1S.root",
        'A10MC2011': OurSites.MY_TUPLE_PATH + "A1MuMu_MC_2011_mumu10GeV_rwY1S.root",
        'A10MC2012': OurSites.MY_TUPLE_PATH + "A1MuMu_MC_2012_mumu10GeV_rwY1S.root",
        'A12MC2011': OurSites.MY_TUPLE_PATH + "A1MuMu_MC_2011_mumu12GeV_rwY1S.root",
        'A12MC2012': OurSites.MY_TUPLE_PATH + "A1MuMu_MC_2012_mumu12GeV_rwY1S.root",
        }
momrange = {"min": sys.argv[1], "max": sys.argv[2]} ## read momentum range in log10
resultfname = sys.argv[3]
sample = sys.argv[4]
option = sys.argv[5]

outfileBaseName="./FIT_PLOTS/" + sample + '_' + option

fixParsFromFile = 1
if "Allpt" in option:
    fixParsFromFile = 0


for samplename in inputTuples.keys():
    if samplename in sample:
        inputTuple = inputTuples[samplename]
        print "Adding tuple {0}".format(samplename)
        ChosenSample = samplename

isMC = 1
UNBINNED = 1
EXTENDED = 0
DOSPLOT = 0
#NBINS = 560 #whole sample
NBINS = 160 #MC 10 pT bins
PRESCALE = 1
PLOTREBIN = 1

CentralMass = {'Y1': 9468, 'Y2': 10023, 'Y3': 10355, 'A8': 8000, 'A10': 10000, 'A12': 12000}

for particle in CentralMass.keys():
       if particle in sample: massrange = {'min': CentralMass[particle]-1068, 'max': CentralMass[particle]+282}
#else:    massrange = {"min": 8400, "max":9750} ##mass range for data to minimize contribution of Y2S #FIXME the lower bound should be the same, but probably the bkgr model should be different

mvar = "Bmass"
selectPartOfTheDataSample = '!(evtNum%{0})'.format(PRESCALE)
massrangeCut = 'Bmass>{0} && Bmass<{1}'.format(massrange["min"], massrange["max"])
momrangeCut = 'log10(Bpt)>{0} && log10(Bpt)<{1}'.format(momrange["min"], momrange["max"]) ## the momentum is in log10

print "will fit with the following momentum cut: ", momrangeCut
print "selecting 1/", PRESCALE, " of the given sample"

cut = CutsList.PreSelection  + '&&'  + selectPartOfTheDataSample+"&&"+massrangeCut+"&&"+momrangeCut
if isMC:
    if "Y1" in sample: cut = cut + "&&" + CutsList.truthMatching['Y']
    if "Y2" in sample: cut = cut + "&&" + CutsList.truthMatching['Y2']
    if "Y3" in sample: cut = cut + "&&" + CutsList.truthMatching['Y3']
tag = "_prescale{0}_momrange{1}_{2}".format(PRESCALE,momrange["min"], momrange["max"])

outfileName = outfileBaseName + tag + ".root"
f = TFile(outfileName, "recreate")

t2 = TChain(tupleName)
t2.Add(inputTuple)

print 'copying tree with cut ', cut
t = t2.CopyTree(cut)
print 'before cut : ', t2.GetEntries(), ", after cut : ", t.GetEntries()

mass = RooRealVar(mvar,mvar,massrange["min"],massrange["max"])
Y1Sweight = RooRealVar('wEtaPtAsY1S','wEtaPtAsY1S',0.,100.)#FIXME
if UNBINNED:
       data = RooDataSet("data", "data", t, RooArgSet(mass, Y1Sweight),"", 'wEtaPtAsY1S')#FIXME
       print "t entries", t.GetEntries()
       print "data entries", data.numEntries()
else:
       histo = TH1F('h'+mvar,'h'+ mvar,NBINS,massrange["min"], massrange["max"])
       for entry in t:
              var = getattr(entry, mvar)
              histo.Fill(var)
       rooHist = RooDataHist('h'+mvar, 'h'+mvar, RooArgList(mass), histo)



###### DEFINE PDF
gROOT.ProcessLine(".L $URANIAROOT/src/RooIpatia2.cxx+")

ipa_s = RooRealVar("ipa_s","ipa_s", 59., 10.,200.)
for particle in CentralMass.keys():
       if particle in sample: ipa_m = RooRealVar("ipa_m","ipa_m",CentralMass[particle], CentralMass[particle]-60,CentralMass[particle]+60)
beta = RooRealVar("beta","beta",0.,-0.1, 0.1)
zeta = RooRealVar("zeta","zeta",2.5e-4)
l = RooRealVar("l","l",-1.25,-6,-1.)
#a = RooRealVar("a","a",1.58,1.0,10.0)
a = RooRealVar("a","a",1.4)
n = RooRealVar("n","n",1.,0.1,50) #leaving just n parameter of left tail free
n2 = RooRealVar("n2","n2",0) ## remove right tail
a2 = RooRealVar("a2","a2",100.)
ipatia = RooIpatia2("ipatia","ipatia",mass,l,zeta,beta,ipa_s,ipa_m,a,n,a2,n2)
sigma0= RooRealVar("sigma0","sigma0",25, 15, 40)
mean0= RooRealVar("mean0","mean0",0)
res0 = RooGaussian("reso0","reso0",mass,mean0,sigma0)
ipa2 = RooFFTConvPdf("ipa2","ipa2",mass, ipatia,res0)
sigPDF = ipa2

# non convoluted Ipathia:
#a = RooRealVar("a","a",1.58,1.3,1.9)
#n = RooRealVar("n","n",1.,0.1,50)
#n2 = RooRealVar("n2","n2",1,0.1,10.) ## keep right tail
#a2 = RooRealVar("a2","a2",100.)
#ipatia = RooIpatia2("ipatia","ipatia",mass,l,zeta,beta,ipa_s,ipa_m,a,n,a2,n2)
#sigPDF = ipatia


if fixParsFromFile:
    import simplejson as json
    def importResultFile(tag):
        resultfile = open('./FIT_RESULTS/fitParResults_{0}.py'.format(tag),'r')
        sample = json.load(resultfile)
        return sample

    fixedPars = importResultFile(ChosenSample + "_Allpt")

    val = {}
    err = {}
    (minpt, maxpt,
           val['a'], err['a'],
           val['a2'], err['a2'],
           val['n'], err['n'],
           val['n2'], err['n2'],
           val['l'], err['l'],
           val['zeta'], err['zeta'],
           val['beta'], err['beta'],
           val['ipa_s'], err['ipa_s'],
           val['ipa_m'], err['ipa_m'],
           val['sigma0'], err['sigma0'],
           chi2) = fixedPars[0]


    if "lfree" in option:
        variablesToBeFixed = {'a':a, 'a2':a2, 'n':n, 'n2':n2, 'zeta':zeta, 'beta':beta, 'ipa_m':ipa_m, 'sigma0':sigma0}
    if 'lfixed' in option:
        variablesToBeFixed = {'a':a, 'a2':a2, 'n':n, 'n2':n2, 'l':l, 'zeta':zeta, 'beta':beta, 'ipa_m':ipa_m, 'sigma0':sigma0}

    for vname, variable in variablesToBeFixed.items():
        variable.setVal(val[vname])
        variable.setConstant()

#FIXME I fix only l by hand since it is totally correlated with ipa_s
if 'Allpt' in option:
    l.setConstant()

if EXTENDED:
    nY1 = RooRealVar("nY1","nY1",0, 2.e6/float(PRESCALE))
    Y1sig = RooExtendPdf("Y1","Y1",sigPDF,nY1)
else:
    Y1sig = sigPDF

if isMC:
       model = Y1sig
else:
       indx = RooRealVar("indx", "indx", 0.,-1.,1.)
       bkg = RooExponential("bkg","bkg", mass,indx)
       if EXTENDED:
           nbkg = RooRealVar("nbkg","nbkg",0, 1.e6/float(PRESCALE))
           bkgpdf = RooExtendPdf("bkg","bkg",bkg,nbkg)
       else:
           bkgpdf = bkg
       model = RooAddPdf("model","model",RooArgList(Y1sig, bkgpdf))


### fitting
fr = mass.frame()
if UNBINNED:
       data.plotOn(fr, RooFit.Binning(NBINS), RooFit.LineWidth(1), RooFit.MarkerSize(0.2))
else:
       rooHist.plotOn(fr, RooFit.Binning(NBINS), RooFit.LineWidth(1), RooFit.MarkerSize(0.2))

if EXTENDED:
        model.fitTo(data,RooFit.Extended(kTRUE), RooFit.Minos(1), RooFit.Offset(kTRUE), RooFit.SumW2Error(kTRUE))#FIXME
else:
        model.fitTo(data,RooFit.Extended(kFALSE), RooFit.Minos(1), RooFit.Offset(kTRUE), RooFit.SumW2Error(kTRUE))#FIXME

### splot of data
if DOSPLOT and EXTENDED and not isMC:
       ### fix all parameters before splotting
       params = [a2, a, n, n2, ipa_s, ipa_m, beta, zeta, l, indx]
       for param in params:
              param.setConstant()


       sData = RooStats.SPlot("sData","an SPlot", data, model, RooArgList(nY1, nbkg))
       print "created sWeights"
       gROOT.ProcessLine(\
              "struct MyStruct{\
              Float_t sWFloat;\
              };")
       from ROOT import MyStruct
       sWValue = MyStruct()
       sWBranch = t.Branch("sW_Y1", AddressOf(sWValue, 'sWFloat'), "sW_Y1/F")
       print "created sweight branch"



       for i in range(t.GetEntries()):
              sWValue.sWFloat = sData.GetSWeight(i,"nY1")
              sWBranch.Fill()
       print "sWeight branch added"
       newcanv = TCanvas()
       sWh = TH1F()
       t.Draw("sW_Y1>>sWh")
       sWh.Print("sWeight.pdf")
       t.Write("",TObject.kOverwrite)
       print "sWeights tuple written"
       f.Write()




### plotting

print "...now plotting"
plotnamebase = outfileBaseName + tag

model.plotOn(fr)
canvas = TCanvas()
fr.Draw()
canvas.Print(plotnamebase + ".pdf")
canvas.SetLogy()
canvas.Print(plotnamebase + "_logy.pdf")

hpull = fr.pullHist()
frpull = mass.frame()
frpull.addPlotable(hpull,"P")
pullCanvas = TCanvas()
frpull.Draw()
pullCanvas.Print(plotnamebase+"_pull.pdf")

hresid = fr.residHist()
frresid = mass.frame()
frresid.addPlotable(hresid,"P")
residCanvas = TCanvas()
frresid.Draw()
residCanvas.Print(plotnamebase+"_resid.pdf")

### printing out fit results
from os import system as shell
print "a : ", momrange["min"], momrange["max"], a.getVal(), a.getError()
print "a2 : ", momrange["min"], momrange["max"], a2.getVal(), a2.getError()
print "n : ", momrange["min"], momrange["max"], n.getVal(), n.getError()
print "n2 : ", momrange["min"], momrange["max"], n2.getVal(), n2.getError()
print "l : ", momrange["min"], momrange["max"], l.getVal(), l.getError()
print "zeta : ", momrange["min"], momrange["max"], zeta.getVal(), zeta.getError()
print "beta : ", momrange["min"], momrange["max"], beta.getVal(), beta.getError()
print "ipa_s : ", momrange["min"], momrange["max"], ipa_s.getVal(), ipa_s.getError()
print "ipa_m : ", momrange["min"], momrange["max"], ipa_m.getVal(), ipa_m.getError()
if not isMC: print "indx : ", momrange["min"], momrange["max"], indx.getVal(), indx.getError()
print "chi2 = ", fr.chiSquare()


import os.path
import simplejson as json
if os.path.exists(resultfname):
    resultfile = open(resultfname,'r')
    results = json.load(resultfile)
    print results
    #resultfile.close()
else:
    results = []

results.append(
            (float(momrange["min"]), float(momrange["max"]),
            a.getVal(), a.getError(),
            a2.getVal(), a2.getError(),
            n.getVal(), n.getError(),
            n2.getVal(), n2.getError(),
            l.getVal(), l.getError(),
            zeta.getVal(), zeta.getError(),
            beta.getVal(), beta.getError(),
            ipa_s.getVal(), ipa_s.getError(),
            ipa_m.getVal(), ipa_m.getError(),
            sigma0.getVal(), sigma0.getError(),
            fr.chiSquare()
            ))

resultfile2 = open(resultfname,'w+')
resultfile2.write(json.dumps(results))
resultfile2.close()

shell('rm {0}'.format(outfileName))

