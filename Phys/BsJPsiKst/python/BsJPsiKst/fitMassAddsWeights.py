from ROOT import *
from math import *
import os
import sys
from Urania import *
recoverTree()
AccessPackage("Bs2MuMu")
from smartpyROOT import *


from OurSites import NTUPLE_PATH
from PDF_2013_Asym_Simon import *
from parameters import KpiBins4 as Kpibins
from mass_params import params as massParams
from Lb_yields import Lb_yield, Lb_yieldErr

# ------ Input args ----------
ibin        = int(sys.argv[1]) # int to tag the mKpi bin
year        = str(sys.argv[2]) # string to tag the year: '2011' or '2012'
charge      = str(sys.argv[3]) # string to tag the charge of kaon: 'neg' or 'pos'
outPutTag   = str(sys.argv[4]) # string to tag the name of the OutPutFile

charge = charge[:1] + charge[len(charge):]

# ------ Retrieve the data ntuple ----------
inputFile = TFile("%s/splitNtuples/%s%s_%s_%s.root"%(NTUPLE_PATH,year,charge,Kpibins[ibin],Kpibins[ibin+1]),"read")
inputTree = inputFile.Get("DecayTree")
print"",inputTree.GetEntries()

# ------ DataSet (imported from tree) ----------
# -- Bs and Bd to JpsiKK or Jpsipipi are substracted when applying wMC!!!!
weightMC = RooRealVar("wMC","wMC", -10000, 10000)
data = RooDataSet("data","data", inputTree, RooArgSet(Mass, weightMC),"", "wMC")
data.Print()

# ------ Building fit model ----------
# -- Bs and Bd

massB = SignalMassIpatia("signal", year, ibin)
massB.ipa_lambdaBd.setConstant(True)
massB.a1_cbBd.setConstant(True)
massB.a2_cbBd.setConstant(True)
massB.ncb1Bd.setConstant(True)
massB.ncb2Bd.setConstant(True)

massB.ipa_lambdaBs.setConstant(True)
massB.a1_cbBs.setConstant(True)
massB.a2_cbBs.setConstant(True)
massB.ncb1Bs.setConstant(True)
massB.ncb2Bs.setConstant(True)

# -- Combi bkg
bkgmodel = FullBackground("Bkg")

# -- Lb peaking bkgs
LbpKmodel = LambdaDecay("Lb2JpsipK")
Lbppimodel = LambdaDecay("Lb2Jpsippi")

for key in massParams["Lb2JpsipK"][year][ibin].keys():
	LbpKmodel.set(key,massParams["Lb2JpsipK"][year][ibin][key])

for key in massParams["Lb2JpsipPi"][year][ibin].keys():
	Lbppimodel.set(key,massParams["Lb2JpsipPi"][year][ibin][key])

# ----- Combining pdfs 
nd = RooRealVar("nBd","nBd", 0.5*(inputTree.GetEntries()),inputTree.GetEntries())
ns = RooRealVar("nBs","nBs", 0.,0.5*(inputTree.GetEntries()))
nbkg = RooRealVar("nCombi","nCombi", 0.,inputTree.GetEntries())
nLbpK = RooRealVar("nLbpK","nLbpK",Lb_yield[year][ibin]["LbK"], 0.,10*Lb_yield[year][ibin]["LbK"])
nLbpi = RooRealVar("nLbpi","nLbpi",Lb_yield[year][ibin]["Lbpi"], 0.,10*Lb_yield[year][ibin]["Lbpi"]) 

# -- Gaussian constraints on Lb yields
LbKconst=RooGaussian("LbKconst","LbKconst",nLbpK,RooFit.RooConst(Lb_yield[year][ibin]["LbK"]),RooFit.RooConst(Lb_yieldErr[year][ibin]["LbK"])) ;
Lbpiconst=RooGaussian("Lbpiconst","Lbpiconst",nLbpi,RooFit.RooConst(Lb_yield[year][ibin]["Lbpi"]),RooFit.RooConst(Lb_yieldErr[year][ibin]["Lbpi"])) ;


fit_model = RooAddPdf("model","model",RooArgList(massB.sigBs,massB.sigBd,bkgmodel.massbkg,LbpKmodel.mass_model,Lbppimodel.mass_model),RooArgList(ns,nd,nbkg,nLbpK,nLbpi))

# ------ Fit to data ----------
fit_model.fitTo(data,RooFit.Save(),RooFit.NumCPU(8),RooFit.Minos(False),RooFit.SumW2Error(kTRUE),RooFit.ExternalConstraints(RooArgSet(LbKconst,Lbpiconst)))

# ------ Print output fit results ----------
prlist = [nd,ns,nbkg,nLbpK,nLbpi]

outVal = {}
outErr = {}
for thing in prlist:
	outVal[thing.GetName()] = thing.getVal()
	outErr[thing.GetName()] = thing.getError()

print outVal
print outErr

# ------ Fit projection ----------
fr = Mass.frame()
data.plotOn(fr)
fit_model.plotOn(fr, RooFit.LineColor(kBlue))

renorm = 1./data.tree().GetEntries()
massB.sigBd.plotOn(fr,RooFit.LineColor(kGreen), RooFit.LineStyle(kDashed), RooFit.Normalization(nd.getVal()*renorm))
massB.sigBs.plotOn(fr, RooFit.LineColor(kRed), RooFit.LineStyle(kDotted), RooFit.Normalization(ns.getVal()*renorm))
bkgmodel.massbkg.plotOn(fr, RooFit.LineColor(kBlack), RooFit.Normalization(nbkg.getVal()*renorm))
LbpKmodel.mass_model.plotOn(fr, RooFit.LineColor(kMagenta),RooFit.Normalization(nLbpK.getVal()*renorm))
Lbppimodel.mass_model.plotOn(fr, RooFit.LineColor(kCyan), RooFit.Normalization(nLbpi.getVal()*renorm))
fr.SetMinimum(0)

fr.Draw()
fr.SaveAs("%s/massFitResults/%s%s_%s_%s_%s.root"%(NTUPLE_PATH,year,charge,Kpibins[ibin],Kpibins[ibin+1],outPutTag))

# ------ Compute SWeights ----------
gROOT.ProcessLine( "struct MyStructF{ Float_t afloat; };" )

outputFile = TFile("%s/splitNtuples/%s%s_%s_%s_AddedsWeights.root"%(NTUPLE_PATH,year,charge,Kpibins[ibin],Kpibins[ibin+1]),"recreate")
outputTree = inputTree.CopyTree("")
print"",outputTree.GetEntries()

sData = RooStats.SPlot("sData","An SPlot",data,fit_model,RooArgList(ns,nd,nbkg, nLbpK,nLbpi))

sWeightList = []
CorrsWeightList = []
sWeightBranchs = []
CorrsWeightBranchs = []
for iSpecie in range(len(prlist)):
	sWeightList.append( MyStructF() )
	CorrsWeightList.append( MyStructF() )
	iSpecieName = prlist[iSpecie].GetName()[1:]
	sWeightBranchs.append(outputTree.Branch( "sWeights_"+iSpecieName, AddressOf(sWeightList[iSpecie],'afloat'), "sWeights_"+iSpecieName+"/F" ))
	CorrsWeightBranchs.append(outputTree.Branch( "cor_sWeights_"+iSpecieName, AddressOf(CorrsWeightList[iSpecie],'afloat'), "cor_sWeights_"+iSpecieName+"/F" ))

branches = outputTree.GetListOfBranches()
for iSpecie in range(len(prlist)):
	print"Performing sWeights computation for", prlist[iSpecie]

	sWeights = []
	corrFactor=0.
	sumW=0.
	sumSqW=0.
	for entry in range(int(outputTree.GetEntries())):
		outputTree.GetEntry(entry)
		sWeight = sData.GetSWeight(entry,prlist[iSpecie].GetName())
		sWeights.append(sWeight)
		sWeightList[iSpecie].afloat = sWeight
		sWeightBranchs[iSpecie].Fill()
		sumW += sWeight
		sumSqW += sWeight**2
                
	corrFactor = sumW/sumSqW
	print "corrFactor=sumW/sumSqW= ",corrFactor 
	for entry in range(len(sWeights)):
		CorrsWeightList[iSpecie].afloat = corrFactor*sWeights[entry]
		CorrsWeightBranchs[iSpecie].Fill()

outputTree.Write("",TObject.kOverwrite)
outputFile.Close()


