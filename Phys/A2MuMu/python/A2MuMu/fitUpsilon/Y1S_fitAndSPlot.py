from ROOT import *
import sys
sys.path.append("..")
import CutsList
import OurSites
gROOT.SetBatch()


#tupleName = "T"
tupleName = "A1/A1"
#tupleName = "Upsilon/Upsilon"
inputTuples = {
        'DATA2011': OurSites.MY_TUPLE_PATH + "RealData_2011_s21r1_Erasmus_v11r2_975pb.root",
        'DATA2012': OurSites.MY_TUPLE_PATH + "RealData_2012_s21_Erasmus_v11r2_1990pb.root",
        #'6GeV': "/scratch19/mborsato/ToyA1_6.0GeV.root",
        #'7GeV': "/scratch19/mborsato/ToyA1_7.0GeV.root",
        #'8GeV': "/scratch19/mborsato/ToyA1_8.0GeV.root",
        #'9GeV': "/scratch19/mborsato/ToyA1_9.0GeV.root",
        #'10GeV': "/scratch19/mborsato/ToyA1_10.0GeV.root",
        #'11GeV': "/scratch19/mborsato/ToyA1_11.0GeV.root",
        #'12GeV': "/scratch19/mborsato/ToyA1_12.0GeV.root",
        #'13GeV': "/scratch19/mborsato/ToyA1_13.0GeV.root",
        }
momrange = {"min": sys.argv[1], "max": sys.argv[2]} ## read momentum range in log10
resultfname = sys.argv[3]
sample = sys.argv[4]
option = sys.argv[5]

outfileBaseName="./FIT_PLOTS/" + sample + '_' + option

#fixParsFromFile = 1
#if "Allpt" in option:
    #fixParsFromFile = 0


for samplename in inputTuples.keys():
    if samplename in sample:
        inputTuple = inputTuples[samplename]
        print "Adding tuple {0}".format(samplename)
        ChosenSample = samplename

isMC = 0
UNBINNED = 1
EXTENDED = 1
DOSPLOT = 1
#NBINS = 560 #whole sample
NBINS = 160 #MC 10 pT bins
PRESCALE = 1
PLOTREBIN = 1

CentralMass = {'Y1': 9468, 'Y2': 10023, 'Y3': 10355, 'A8': 8000, 'A10': 10000, 'A12': 12000}

for particle in CentralMass.keys():
       if particle in sample: massrange = {'min': CentralMass[particle]-1068, 'max': CentralMass[particle]+282}
if 'DATA' in sample:
       massrange = {"min": 8400, "max":9750} ##mass range for data to minimize contribution of Y2S #FIXME the lower bound should be the same, but probably the bkgr model should be different

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
print '/////////////////////////////////'
print 'Created root file in ', outfileName
print '/////////////////////////////////'

t2 = TChain(tupleName)
t2.Add(inputTuple)

print 'copying tree with cut ', cut
t = t2.CopyTree(cut)
print 'before cut : ', t2.GetEntries(), ", after cut : ", t.GetEntries()
totEntries = t.GetEntries()

mass = RooRealVar(mvar,mvar,massrange["min"],massrange["max"])
#Y1Sweight = RooRealVar('wEtaPtAsY1S','wEtaPtAsY1S',0.,100.)#FIXME
#data = RooDataSet("data", "data", t, RooArgSet(mass, Y1Sweight),"", 'wEtaPtAsY1S')#FIXME
data = RooDataSet("data", "data", t, RooArgSet(mass))
print "t entries", t.GetEntries()
print "data entries", data.numEntries()



###### DEFINE PDF
gROOT.ProcessLine(".L $URANIAROOT/src/RooIpatia2.cxx+")

ipa_s = RooRealVar("ipa_s","ipa_s", 59., 10.,200.)
for particle in CentralMass.keys():
       if particle in sample: ipa_m = RooRealVar("ipa_m","ipa_m",CentralMass[particle], CentralMass[particle]-60,CentralMass[particle]+60)
if isMC==0: ipa_m = RooRealVar("ipa_m","ipa_m",CentralMass['Y1'], CentralMass['Y1']-100,CentralMass['Y1']+100)
#beta = RooRealVar("beta","beta",-1.7e-3, -2.5e-2, -0.1e-3)
beta = RooRealVar("beta","beta",-1.7e-3)
zeta = RooRealVar("zeta","zeta",2.5e-4)
l = RooRealVar("l","l",-1.3,-6,-1.)
#a = RooRealVar("a","a",1.58,1.0,10.0)
a = RooRealVar("a","a",1.6)
n = RooRealVar("n","n",1.,0.1,30) #leaving just n parameter of left tail free
n2 = RooRealVar("n2","n2",0) ## remove right tail
a2 = RooRealVar("a2","a2",100.)
ipatia = RooIpatia2("ipatia","ipatia",mass,l,zeta,beta,ipa_s,ipa_m,a,n,a2,n2)
sigma0= RooRealVar("sigma0","sigma0",30, 20, 70)
mean0= RooRealVar("mean0","mean0",0)
mass.setBins(3000,'cache')
res0 = RooGaussian("reso0","reso0",mass,mean0,sigma0)
ipa2 = RooFFTConvPdf("ipa2","ipa2",mass, ipatia,res0)

# non convoluted Ipathia:
#a = RooRealVar("a","a",1.58,1.3,1.9)
#n = RooRealVar("n","n",1.,0.1,50)
#n2 = RooRealVar("n2","n2",1,0.1,10.) ## keep right tail
#a2 = RooRealVar("a2","a2",100.)
#ipatia = RooIpatia2("ipatia","ipatia",mass,l,zeta,beta,ipa_s,ipa_m,a,n,a2,n2)
#sigPDF = ipatia






"""
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
    if "lfreeSigma0free" in option:
        variablesToBeFixed = {'a':a, 'a2':a2, 'n':n, 'n2':n2, 'zeta':zeta, 'beta':beta, 'ipa_m':ipa_m}
    if "lfreeSigma0freeNfree" in option:
        variablesToBeFixed = {'a':a, 'a2':a2, 'n2':n2, 'zeta':zeta, 'beta':beta, 'ipa_m':ipa_m}

    for vname, variable in variablesToBeFixed.items():
        variable.setVal(val[vname])
        variable.setConstant()

"""




indx = RooRealVar("indx", "indx", 0.,-1.,1.)
bkg = RooExponential("bkg","bkg", mass,indx)
bfrac = RooRealVar("bfrac", "bfrac", 0.05,0.,1.)
model = RooAddPdf("model","model",ipa2, bkg, bfrac )





### fitting


model.fitTo(data,RooFit.Extended(kFALSE), RooFit.Minos(0), RooFit.Offset(kTRUE))#FIXME



if EXTENDED:
       nbkg = RooRealVar("nbkg","nbkg",0, totEntries/2)
       nsig = RooRealVar("nsig","nsig",0, totEntries)
       bkgpdf = RooExtendPdf("bkg","bkg",bkg,nbkg)
       sigpdf = RooExtendPdf("sig","sig",ipa2,nsig)
       modelExt = RooAddPdf("modelExt","modelExt", RooArgList(sigpdf, bkgpdf) )
       params = [a2, a, n, n2, ipa_s, ipa_m, beta, zeta, l, indx, sigma0]
       for param in params:
              param.setConstant()
       modelExt.fitTo(data,RooFit.Extended(kTRUE), RooFit.Minos(0), RooFit.Offset(kTRUE))#FIXME



### splot of data
if DOSPLOT and EXTENDED and not isMC:
       sData = RooStats.SPlot("sData","an SPlot", data, modelExt, RooArgList(nsig, nbkg))
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
              sWValue.sWFloat = sData.GetSWeight(i,"nsig")
              sWBranch.Fill()
       print "sWeight branch added"
       #newcanv = TCanvas()
       #sWh = TH1F()
       #t.Draw("sW_Y1>>sWh")
       #sWh.Print("sWeight.pdf")
       t.Write("",TObject.kOverwrite)
       print "sWeights tuple written"
       f.Write()




### plotting

print "...now plotting"
plotnamebase = outfileBaseName + tag


fr = mass.frame()
data.plotOn(fr, RooFit.Binning(NBINS), RooFit.LineWidth(1), RooFit.MarkerSize(0.2))
modelExt.plotOn(fr)
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


"""
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
"""
