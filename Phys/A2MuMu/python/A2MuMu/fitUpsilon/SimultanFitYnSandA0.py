from ROOT import *
import sys
sys.path.append("..")
import CutsList
import OurSites
gROOT.SetBatch()
from math import floor


tupleName = "A1/A1"
#tupleName = "A1"
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
        'A8MC2011': OurSites.MY_TUPLE_PATH + "A1MuMu_MC_2011_mumu8GeV.root",
        'A8MC2012': OurSites.MY_TUPLE_PATH + "A1MuMu_MC_2012_mumu8GeV.root",
        'A10MC2011': OurSites.MY_TUPLE_PATH + "A1MuMu_MC_2011_mumu10GeV.root",
        'A10MC2012': OurSites.MY_TUPLE_PATH + "A1MuMu_MC_2012_mumu10GeV.root",
        'A12MC2011': OurSites.MY_TUPLE_PATH + "A1MuMu_MC_2011_mumu12GeV.root",
        'A12MC2012': OurSites.MY_TUPLE_PATH + "A1MuMu_MC_2012_mumu12GeV.root",
        }
momrange = {"min": sys.argv[1], "max": sys.argv[2]} ## read momentum range in log10
resultfname = sys.argv[3]
option = sys.argv[4]

outfileBaseName="./FIT_PLOTS/" + 'Simultaneous' + '_' + option

fixParsFromFile = 1
if "Allpt" in option:
    fixParsFromFile = 0

isMC = 1
UNBINNED = 1
#NBINS = 560 #whole sample
NBINS = 600 #MC 10 pT bins
PRESCALE = 1
PLOTREBIN = 1

CentralMass = {'Y1': 9460.30, 'Y2': 10023.26, 'Y3': 10355.2, 'A': 12000} #PDG values --> do they correspond to gen values?
#CentralMass = {'Y1': 9460.30, 'Y2': 10023.26, 'Y3': 10355.2, 'A': 8000} #PDG values --> do they correspond to gen values?

mvar = "Bmass"
massrange = {'min': 5500, 'max': 15000}
massrangeCut = 'Bmass>{0} && Bmass<{1}'.format(massrange["min"], massrange["max"])

selectPartOfTheDataSample = '!(evtNum%{0})'.format(PRESCALE)
momrangeCut = 'log10(Bpt)>{0} && log10(Bpt)<{1}'.format(momrange["min"], momrange["max"]) ## the momentum is in log10

print "will fit with the following momentum cut: ", momrangeCut
print "selecting 1/", PRESCALE, " of the given sample"

cut = CutsList.PreSelection  + '&&'  + selectPartOfTheDataSample+"&&"+massrangeCut+"&&"+momrangeCut
tag = "_prescale{0}_momrange{1}_{2}".format(PRESCALE,momrange["min"], momrange["max"])
cut = cut + '&& mc1==-13 && mc2==13'

outfileName = outfileBaseName + tag + ".root"
f = TFile(outfileName, "recreate")

Yield2011 = {'Y1': 2.88e4/0.4, 'Y2': 1.07e4/0.4, 'Y3': 0.71e4/0.4}
MCstat2011 = {'Y1': 233168, 'Y2': 197784, 'Y3': 217383}
preScale = {}
for part in Yield2011.keys():
       ratio = MCstat2011[part]/Yield2011[part]
       preScale[part] = floor(ratio)
       print part, ratio, preScale[part]


ScaleAsDataCut = '((mo1==553 && mo2==553 && !(evtNum%{0})) || (mo1==100553 && mo2==100553 && !(evtNum%{1})) || (mo1==200553 && mo2==200553 && !(evtNum%{2})) || (mo1==36 && mo2==36))'.format(preScale['Y1'], preScale['Y2'], preScale['Y3'])

cut = cut + '&&' + ScaleAsDataCut

t2 = TChain(tupleName)
t2.Add(inputTuples['Y1MC2011'])
t2.Add(inputTuples['Y2MC2011'])
t2.Add(inputTuples['Y3MC2011'])
t2.Add(inputTuples['A12MC2011'])
#t2.Add(inputTuples['A8MC2011'])

Amass = CentralMass['A']

print 'copying tree with cut ', cut
t = t2.CopyTree(cut)
print 'before cut : ', t2.GetEntries('1'), ", after cut : ", t.GetEntries('1')
totentries = t.GetEntries('1')
inY1 = t.GetEntries('mo1==553 && mo2==553')
inY2 = t.GetEntries('mo1==100553 && mo2==100553')
inY3 = t.GetEntries('mo1==200553 && mo2==200553')
inA = t.GetEntries('mo1==36 && mo2==36')
tNoA = t.CopyTree('mo1!=36 && mo2!=36')
print 'tree with no A1 has ', tNoA.GetEntries(), ' entries'
print 'Y1, Y2, Y3 : ', inY1, inY2, inY3
print 'ratio Y1, Y2, Y3 : ', inY1/Yield2011['Y1'], inY2/Yield2011['Y2'], inY3/Yield2011['Y3']


from PlotRampUpPerEventMassErr import *
rampup = {}
rampup['Y1'] = getRampUpVal(t, 0.01, 'Bmass>{0} && Bmass<{1}'.format(CentralMass['Y1']-120, CentralMass['Y1']+120))
rampup['Y2'] = getRampUpVal(t, 0.01, 'Bmass>{0} && Bmass<{1}'.format(CentralMass['Y2']-120, CentralMass['Y2']+120))
rampup['Y3'] = getRampUpVal(t, 0.01, 'Bmass>{0} && Bmass<{1}'.format(CentralMass['Y3']-120, CentralMass['Y3']+120))
rampup['A'] = getRampUpVal(t, 0.01, 'Bmass>{0} && Bmass<{1}'.format(Amass-120, Amass+120))
print 'RAMPUP VALUES ARE ', rampup

mass = RooRealVar(mvar,'m(#mu#mu) MeV/c^{2}',massrange["min"],massrange["max"])
#Y1Sweight = RooRealVar('wEtaPtAsY1S','wEtaPtAsY1S',0.,100.)#FIXME
#data = RooDataSet("data", "data", t, RooArgSet(mass, Y1Sweight),"", 'wEtaPtAsY1S')#FIXME
data = RooDataSet("data", "data", t, RooArgSet(mass))
dataNoA = RooDataSet("dataNoA", "dataNoA", tNoA, RooArgSet(mass))
print "t entries", t.GetEntries()
print "data entries", data.numEntries()


indx = RooRealVar("indx", "indx", -0.0001)
exp1 = RooExponential("exp1","exp1", mass,indx)
databkg = exp1.generate(RooArgSet(mass), totentries/3)
data.append(databkg)
dataNoA.append(databkg)
print 'Appended ', databkg.numEntries(), ' bacgkournd events to dataset'


###### DEFINE PDF
gROOT.ProcessLine(".L $URANIAROOT/src/RooIpatia2.cxx+")

def estimateSigma0(inputmass):
       slope = 0.00235
       y0 = 3.73
       sigma0 = inputmass*slope + y0
       return sigma0

gscale_m = RooRealVar('gscale_m','gscale_m', 1.0001, 0.9995, 1.0015)

Y1pdg_m = RooRealVar('Y1pdg_m','Y1pdg_m',CentralMass['Y1'])
Y1ipa_m = RooFormulaVar("Y1ipa_m","Y1ipa_m",'Y1pdg_m*gscale_m',RooArgList(Y1pdg_m, gscale_m))
l_slope = RooRealVar('l_slope','l_slope', -1.42e-4, -2.6e-4, -0.5e-4)
#Y1l = RooRealVar("Y1l","Y1l",-1.30,-6,-1)
Y1l = RooFormulaVar('Y1l','Y1l','Y1ipa_m*l_slope',RooArgList(Y1ipa_m, l_slope))
ipa_s = RooRealVar("ipa_s","ipa_s", 60., 30., 100.)
zeta = RooRealVar("zeta","zeta",2.5e-4)
beta = RooRealVar("beta","beta",-1.7e-3,-0.1, 0.1)
#a = RooRealVar("a","a",1.4, 1, 10)
a = RooRealVar("a","a",1.6)
a2 = RooRealVar("a2","a2",200.)
n = RooRealVar("n","n",1.,0.1,50) #leaving just n parameter of left tail free
n2 = RooRealVar("n2","n2",0.) ## remove right tail
Y1ipatia = RooIpatia2("Y1ipatia","Y1ipatia", mass, Y1l, zeta, beta, ipa_s, Y1ipa_m, a, n, a2, n2)
Y1sigma0= RooRealVar("Y1sigma0","Y1sigma0", rampup['Y1'])
Y1mean0= RooRealVar("Y1mean0","Y1mean0",0)
Y1res0 = RooGaussian("Y1reso0","Y1reso0",mass,Y1mean0,Y1sigma0)
mass.setBins(3000,'cache')
Y1ipa2 = RooFFTConvPdf("Y1ipa2","Y1ipa2",mass, Y1ipatia, Y1res0)
nY1 = RooRealVar("nY1","nY1",totentries/3, 0., totentries)
Y1sig = RooExtendPdf("Y1","Y1",Y1ipa2,nY1)

Y2pdg_m = RooRealVar('Y2pdg_m','Y2pdg_m',CentralMass['Y2'])
#Y2scale_m = RooRealVar('Y2scale_m','Y2scale_m', 1.0001, 0.9995, 1.0015)
Y2ipa_m = RooFormulaVar("Y2ipa_m","Y2ipa_m",'Y2pdg_m*gscale_m',RooArgList(Y2pdg_m, gscale_m))
#Y2l = RooRealVar("Y2l","Y2l",-1.25,-6,-1.)
Y2l = RooFormulaVar('Y2l','Y2l','Y1ipa_m*l_slope',RooArgList(Y1ipa_m, l_slope))
Y2ipatia = RooIpatia2("Y2ipatia","Y2ipatia", mass, Y2l, zeta, beta, ipa_s, Y2ipa_m, a, n, a2, n2)
Y2sigma0= RooRealVar("Y2sigma0","Y2sigma0",rampup['Y2'])
Y2mean0= RooRealVar("Y2mean0","Y2mean0",0)
Y2res0 = RooGaussian("Y2reso0","Y2reso0",mass,Y2mean0,Y2sigma0)
Y2ipa2 = RooFFTConvPdf("Y2ipa2","Y2ipa2",mass, Y2ipatia, Y2res0)
nY2 = RooRealVar("nY2","nY2", totentries/3, 0., totentries)
Y2sig = RooExtendPdf("Y2","Y2",Y2ipa2,nY2)

Y3pdg_m = RooRealVar('Y3pdg_m','Y3pdg_m',CentralMass['Y3'])
#Y3scale_m = RooRealVar('Y3scale_m','Y3scale_m', 1.0001, 0.9995, 1.0015)
Y3ipa_m = RooFormulaVar("Y3ipa_m","Y3ipa_m",'Y3pdg_m*gscale_m',RooArgList(Y3pdg_m, gscale_m))
#Y3l = RooRealVar("Y3l","Y3l",-1.3,-2,-1.)
Y3l = RooFormulaVar('Y3l','Y3l','Y1ipa_m*l_slope',RooArgList(Y1ipa_m, l_slope))
Y3ipatia = RooIpatia2("Y3ipatia","Y3ipatia", mass, Y3l, zeta, beta, ipa_s, Y3ipa_m, a, n, a2, n2)
Y3sigma0= RooRealVar("Y3sigma0","Y3sigma0",rampup['Y3'])
Y3mean0= RooRealVar("Y3mean0","Y3mean0",0)
Y3res0 = RooGaussian("Y3reso0","Y3reso0",mass,Y3mean0,Y3sigma0)
Y3ipa2 = RooFFTConvPdf("Y3ipa2","Y3ipa2",mass, Y3ipatia, Y3res0)
nY3 = RooRealVar("nY3","nY3", totentries/3, 0., totentries)
Y3sig = RooExtendPdf("Y3","Y3",Y3ipa2,nY3)

Apdg_m = RooRealVar('Apdg_m','Apdg_m',CentralMass['A'])
#Ascale_m = RooRealVar('Ascale_m','Ascale_m', 1.0001, 0.9995, 1.0015)
Aipa_m = RooFormulaVar("Aipa_m","Aipa_m",'Apdg_m*gscale_m',RooArgList(Apdg_m, gscale_m))
#Al = RooRealVar("Al","Al",-1.3,-2,-1.)
Al = RooFormulaVar('Al','Al','Y1ipa_m*l_slope',RooArgList(Y1ipa_m, l_slope))
Aipatia = RooIpatia2("Aipatia","Aipatia", mass, Al, zeta, beta, ipa_s, Aipa_m, a, n, a2, n2)
Asigma0= RooRealVar("Asigma0","Asigma0",rampup['A'])
Amean0= RooRealVar("Amean0","Amean0",0)
Ares0 = RooGaussian("Areso0","Areso0",mass,Amean0,Asigma0)
Aipa2 = RooFFTConvPdf("Aipa2","Aipa2",mass, Aipatia, Ares0)
nA = RooRealVar("nA","nA", totentries/3, 0., totentries)
Asig = RooExtendPdf("A","A",Aipa2,nA)

nbkg = RooRealVar("nbkg","nbkg",totentries/3, 0, totentries)
bkgpdf = RooExtendPdf("bkg","bkg",exp1,nbkg)

#model = RooAddPdf("model","model",RooArgList(Y1sig, bkgpdf))
#model = RooAddPdf("model","model",RooArgList(Y1sig, Asig))
modelNoA = RooAddPdf("modelNoA","modelNoA",RooArgList(Y1sig, Y2sig, Y3sig, bkgpdf))
model = RooAddPdf("model","model",RooArgList(Y1sig, Y2sig, Y3sig, Asig, bkgpdf))

modelNoA.fitTo(dataNoA,RooFit.Extended(kTRUE), RooFit.Minos(0), RooFit.Offset(kTRUE))
beta.setConstant()
gscale_m.setConstant()
ipa_s.setConstant()
l_slope.setConstant()
n.setConstant()

### fitting
fr = mass.frame()
data.plotOn(fr, RooFit.Binning(NBINS), RooFit.LineWidth(1), RooFit.MarkerSize(0.2))
model.fitTo(data,RooFit.Extended(kTRUE), RooFit.Minos(0), RooFit.Offset(kTRUE))


### plotting

print "...now plotting"
plotnamebase = outfileBaseName + tag

model.plotOn(fr, RooFit.LineWidth(1))
#Y1ipa2.plotOn(fr, RooFit.LineWidth(1))

hpull = fr.pullHist()
frpull = mass.frame()
frpull.addPlotable(hpull,"P")
pullCanvas = TCanvas('c2','c2',1200,400)
frpull.Draw()
pullCanvas.Print(plotnamebase+"_pull.pdf")

hresid = fr.residHist()
frresid = mass.frame()
frresid.addPlotable(hresid,"P")
residCanvas = TCanvas('c3','c3',1200,400)
frresid.Draw()
residCanvas.Print(plotnamebase+"_resid.pdf")

model.plotOn(fr, RooFit.LineWidth(1), RooFit.LineColor(2), RooFit.Components('A'))
model.plotOn(fr, RooFit.LineWidth(1), RooFit.LineColor(4), RooFit.Components('Y1'), RooFit.LineStyle(2))
model.plotOn(fr, RooFit.LineWidth(1), RooFit.LineColor(4), RooFit.Components('Y2'), RooFit.LineStyle(3))
model.plotOn(fr, RooFit.LineWidth(1), RooFit.LineColor(4), RooFit.Components('Y3'), RooFit.LineStyle(4))
canvas = TCanvas('c1','c1',1200,400 )
fr.SetTitle('Testing {0} GeV A_{{1}}^{{0}} model in [{1}, {2}] log_{{10}}(p_{{T}}) bin'.format(Amass/1000., momrange['min'], momrange['max']))
fr.Draw()
canvas.Print(plotnamebase + ".pdf")
canvas.SetLogy()
canvas.Print(plotnamebase + "_logy.pdf")


###printing out results
print 'inY1 = ', inY1, ' , outY1 = ', nY1.getVal(), ' +- ', nY1.getError(), '  --->  ', (nY1.getVal()/inY1 -1.)*100,'% and ', (nY1.getVal() - inY1)/nY1.getError(), ' sigma away'
print 'inA = ', inA, ' , outA = ', nA.getVal(), ' +- ', nA.getError(), '  --->  ', (nA.getVal()/inA -1.)*100,'% and ', (nA.getVal() - inA)/nA.getError(), ' sigma away'


### printing out fit results
from os import system as shell
print "a : ", momrange["min"], momrange["max"], a.getVal(), a.getError()
print "a2 : ", momrange["min"], momrange["max"], a2.getVal(), a2.getError()
print "n : ", momrange["min"], momrange["max"], n.getVal(), n.getError()
print "n2 : ", momrange["min"], momrange["max"], n2.getVal(), n2.getError()
print "l_slope : ", momrange["min"], momrange["max"], l_slope.getVal(), l_slope.getError()
print "zeta : ", momrange["min"], momrange["max"], zeta.getVal(), zeta.getError()
print "beta : ", momrange["min"], momrange["max"], beta.getVal(), beta.getError()
print "ipa_s : ", momrange["min"], momrange["max"], ipa_s.getVal(), ipa_s.getError()
print "gscale_m : ", momrange["min"], momrange["max"], gscale_m.getVal(), gscale_m.getError()
print "nA : ", momrange["min"], momrange["max"], nA.getVal()/inA, nA.getError()/inA
print "nY1 : ", momrange["min"], momrange["max"], nY1.getVal()/inY1, nY1.getError()/inY1
#print "nY2 : ", momrange["min"], momrange["max"], nY2.getVal(), nY2.getError()
#print "nY3 : ", momrange["min"], momrange["max"], nY3.getVal(), nY3.getError()
#if not isMC: print "indx : ", momrange["min"], momrange["max"], indx.getVal(), indx.getError()
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
            l_slope.getVal(), l_slope.getError(),
            zeta.getVal(), zeta.getError(),
            beta.getVal(), beta.getError(),
            ipa_s.getVal(), ipa_s.getError(),
            gscale_m.getVal(), gscale_m.getError(),
            nA.getVal()/inA, nA.getError()/inA,
            nY1.getVal()/inY1, nY1.getError()/inY1,
            fr.chiSquare()
            ))

resultfile2 = open(resultfname,'w+')
resultfile2.write(json.dumps(results))
resultfile2.close()

print 'Written results to ', resultfname

shell('rm {0}'.format(outfileName))
