from ROOT import *
from array import array
from math import *
from sys import *
#from bisect import *
from time import *

print 'Initializing...'
if len(argv) == 1:
    argv.append(100)
    argv.append(8000)
    argv.append(1000)
signalValue = int(argv[1])
peakMass = int(argv[2])
toyExperiments = int(argv[3])
massMin = 7000
massMax = 13000
filename = " ~/vol5/a1_things/tuples/a1mumu_MDST.root"
outfname = "out/"
treename = "OppoSignDecayTree/DecayTree"
massname = "X_MM"

print 'Opening files...'
file = TFile(filename)
tree = file.Get(treename)
maxEntries = tree.GetEntries()

print 'Creating fit data...'
mass = RooRealVar(massname,"mass",massMin,massMax)
massData = RooDataSet("massData","Mass data", tree, RooArgSet(mass))

print 'Creating fit models...'
references = {}
sigmaZero = RooConstVar('sigmaZero','sigmaZero',1.3233)
sigmaOne  = RooConstVar('sigmaOne', 'sigmaOne',6.14825e-3)
cutZero = RooConstVar('cutZero','cutZero',6.67603e-1)
cutOne  = RooConstVar('cutOne', 'cutOne',8.9638e-4)
def addReferences(objs):
    for obj in objs:
        references[obj.GetName()] = obj
def pdfBack():
    name = 'background'
    n = RooConstVar(name+"Exponent",name+"Exponent",-1.35647e-4)
    addReferences([n])
    return RooExponential(name,name,mass,n)
def pdfSignal(name,muVal):
    mu = RooConstVar(name+"Mu",name+"Mu",muVal)
    sigma = RooFormulaVar(name+"Sigma",name+"Sigma",sigmaZero.GetName()+'+('+sigmaOne.GetName()+'*'+mu.GetName()+')',RooArgList(sigmaZero,sigmaOne,mu))
    cut = RooFormulaVar(name+"Cut",name+"Cut",cutZero.GetName()+'+('+cutOne.GetName()+'*'+mu.GetName()+')',RooArgList(cutZero,cutOne,mu))
    exponent = RooConstVar(name+"Exponent",name+"Exponent",1)
    addReferences([mu,sigma,cut,exponent])
    return RooCBShape(name,name,mass,mu,sigma,cut,exponent)
def pdfAdd(pdfs):
    numbernames = []
    for pdf in pdfs:
        numbernames.append(pdf.GetName()+"Number")
    pdfList = RooArgList()
    numberList = RooArgList()
    name = ""
    for i in range(len(pdfs)):
        pdf = pdfs[i]
        pdfNumber = RooRealVar(numbernames[i],numbernames[i],1,0,maxEntries)
        pdfList.add(pdf)
        numberList.add(pdfNumber)
        addReferences([pdf,pdfNumber])
        name = name + pdf.GetName()
    addReferences([pdfList,numberList])
    return RooAddPdf(name,name,pdfList,numberList)
model = pdfAdd([pdfBack(), pdfSignal('upsilonOne',9.44233e3), pdfSignal('upsilonTwo',1.00011e4), pdfSignal('upsilonThree',1.03331e4), pdfSignal('peak',peakMass)])
signalVar = references['peakNumber']
signalVar.setConstant(kTRUE)
signalVar.setVal(0)
model.fitTo(massData,RooFit.Minos(kTRUE))
references['upsilonOneNumber'].setConstant(kTRUE)
references['upsilonTwoNumber'].setConstant(kTRUE)
references['upsilonThreeNumber'].setConstant(kTRUE)

def calcDLL(dataSet):
    NLLVar = model.createNLL(dataSet)
    signalVar.setVal(0)
    nullNLL = NLLVar.getVal()
    signalVar.setVal(signalValue)
    testNLL = NLLVar.getVal()
    DLL = testNLL - nullNLL
    del NLLVar
    return DLL

fake = model.generate(RooArgSet(mass),massData.numEntries())
observedDLL = calcDLL(fake)
testDLLs = []
nullDLLs = []

def doExperiment():
    signalVar.setVal(0)
    nullExperiment = model.generate(RooArgSet(mass),massData.numEntries())
    signalVar.setVal(signalValue)
    testExperiment = model.generate(RooArgSet(mass),massData.numEntries())

    testDLLs.append(calcDLL(testExperiment))
    nullDLLs.append(calcDLL(nullExperiment))

    del nullExperiment
    del testExperiment

initTime = clock()
for i in range(toyExperiments+1):
    doExperiment()
    deltaTime = clock() - initTime
    fraction = (toyExperiments+1)/float(i+1) - 1
    ETL = str(int(deltaTime * fraction * 10) / 10.0)
    print 'Done experiment '+str(i)+' of '+str(toyExperiments)+' (ETL '+ETL+' s)'

testDLLs.sort()
nullDLLs.sort()

clb  = float(bisect(nullDLLs,observedDLL)) / len(nullDLLs)
clbs = float(bisect(testDLLs,observedDLL)) / len(testDLLs)
cls  = clbs/clb

out = open(outfname + "CLM" + str(peakMass) + "S" + str(signalValue),'w')
def outw(val):
    out.write(str(val)+'\n')
outw(peakMass)
outw(signalValue)
outw(clb)
outw(clbs)
outw(cls)
out.close()

a = TH1F('a','Null',40,min(nullDLLs+testDLLs),max(nullDLLs+testDLLs))
b = TH1F('b','Test',40,min(nullDLLs+testDLLs),max(nullDLLs+testDLLs))
for i in range(len(nullDLLs)):
    a.Fill(nullDLLs[i])
    b.Fill(testDLLs[i])
canvas = TCanvas()
canvas.Divide(2,1)
canvas.cd(1)
a.Draw()
canvas.cd(2)
b.Draw()
