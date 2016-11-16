from ROOT import *
from math import *
import os
import sys
import time
from Urania import *
recoverTree()
AccessPackage("Bs2MuMu")
from smartpyROOT import *
from PDF_2013_Asym import *
from OurSites import NTUPLE_PATH
from parameters import KpiBins23 as Kpibins
import Lb_params
import ipa_params

timeZero = time.time()

import sys
ibin = int(sys.argv[2])
binname = "_" + str(Kpibins[ibin])+ "_" + str(Kpibins[ibin+1])
neim = sys.argv[1] + binname + ".root"
print neim
wcat = sys.argv[3]
print wcat

massB = SignalMass("signal")
massB.ipa_lambda.setVal(ipa_params.Bin[ibin]["l"])
massB.ipa_lambda.setConstant(1)#ipa_params.Bin[ibin]["l"])
massB.a1_cb.setVal(ipa_params.Bin[ibin]["a"])
massB.a1_cb.setConstant(1)
massB.a2_cb.setVal(ipa_params.Bin[ibin]["a2"])
massB.a2_cb.setConstant(1)
massB.ncb1.setVal(ipa_params.Bin[ibin]["n"])
massB.ncb1.setConstant(1)
massB.ncb2.setVal(ipa_params.Bin[ibin]["n2"])
massB.ncb2.setConstant(1)

bkgmodel = FullBackground("Bkg")
LAMBDA = 0
#bkgmodel.make()

#BREAK


#### TODO: Move the following lines to PDF_Asym  ######
gROOT.ProcessLine(".L $URANIAROOT/src/RooAmorosoPdf.cxx++")


class LambdaDecay:
	def __init__(self, name = "Lambda"):
		self.name = name
		self.theta = RooRealVar(name + "theta",name + "theta",-200, -1000,-1)
		self.alpha = RooRealVar(name + "alpha",name + "alpha",1, 0.1, 10)
		self.offset = RooRealVar(name + "mean",name + "mean", 5600, 5450, 8000)
		self.mean = self.offset
		self.beta = RooRealVar(name + "beta", name + "beta", 2,-7,7)
		self.mass_model = RooAmorosoPdf(name + "mass_model", name+ "mass_model" ,Mass, self.offset, self.theta, self.alpha, self.beta)
	def set(self, var, value):
		getattr(self, var).setVal(value)
		getattr(self, var).setConstant(kTRUE)

LbpKmodel = LambdaDecay("Lb2JpsipK")
Lbppimodel = LambdaDecay("Lb2Jpsippi")

for key in Lb_params.LbpK[ibin].keys():
	LbpKmodel.set(key,Lb_params.LbpK[ibin][key])
	Lbppimodel.set(key,Lb_params.Lbppi[ibin][key])

##############################################
weightMC = RooRealVar("wMC","wMC", -10000, 10000)
def computeWeights(filename,  WEIGHT_CAT, plot = 1):	
	my_file = TFile(filename,"update")
	my_tree = my_file.Get("DecayTree")
	my_dataset = RooDataSet("data","data",my_tree,RooArgSet(Mass, weightMC),"100000000000000 > 0", "wMC")

	gROOT.ProcessLine("struct MyStruct{Float_t sWFloat;};")
	gROOT.ProcessLine("struct MyStruct2{Float_t cor_sWFloat;};")
	from ROOT import MyStruct
	from ROOT import MyStruct2
	nd = RooRealVar("nBd","nBd", 0.5*(my_tree.GetEntries()),my_tree.GetEntries())
	ns = RooRealVar("nBs","nBs", 0.,0.5*(my_tree.GetEntries()))
	nbkg = RooRealVar("n_bkg","n_bkg", 0.,my_tree.GetEntries())
	
	nLbK = RooRealVar("nLbK","nLbK", 0.,0.5*(my_tree.GetEntries())*LAMBDA)
	nLbpi = RooRealVar("nLbpi","nLbpi", 0.,0.5*(my_tree.GetEntries())*LAMBDA)
	nLbK.setConstant(not LAMBDA)
	nLbpi.setConstant(not LAMBDA)
	
	my_model = RooAddPdf("model","model",RooArgList(massB.sigBs,massB.sigBd,bkgmodel.massbkg, LbpKmodel.mass_model, Lbppimodel.mass_model),RooArgList(ns,nd,nbkg, nLbK, nLbpi))

	sWValue = MyStruct()
	cor_sWValue = MyStruct2()
	sWeights_Bs_F = "sWeights_" +WEIGHT_CAT+"/F"
	sWBranch = my_tree.Branch("sWeights_"+ WEIGHT_CAT, AddressOf(sWValue,'sWFloat'),"sWeights_"+WEIGHT_CAT+"/F") 
	cor_sWBranch = my_tree.Branch("cor_sWeights_"+  WEIGHT_CAT, AddressOf(cor_sWValue,'cor_sWFloat'), "cor_sWeights_"+WEIGHT_CAT+"/F") 
#############
	yield_cat=0
	if(WEIGHT_CAT=="Bs"): yield_cat=0
	else: yield_cat=1
    
	fitres =my_model.fitTo(my_dataset,RooFit.Save(),RooFit.NumCPU(8))
	if plot:
		renorm = 1./my_dataset.tree().GetEntries()
		fr = Mass.frame()
		my_dataset.plotOn(fr)
		my_model.plotOn(fr, RooFit.LineColor(kBlack))
		massB.sigBd.plotOn(fr,RooFit.LineColor(kGreen), RooFit.LineStyle(kDashed), RooFit.Normalization(nd.getVal()*renorm))
		massB.sigBs.plotOn(fr, RooFit.LineColor(kRed), RooFit.LineStyle(kDotted), RooFit.Normalization(ns.getVal()*renorm))
		bkgmodel.massbkg.plotOn(fr, RooFit.LineColor(kBlue), RooFit.Normalization(nbkg.getVal()*renorm))
		LbpKmodel.mass_model.plotOn(fr, RooFit.LineColor(kMagenta),RooFit.Normalization(nLbK.getVal()*renorm))
		Lbppimodel.mass_model.plotOn(fr, RooFit.LineColor(kCyan), RooFit.Normalization(nLbpi.getVal()*renorm))
		fr.Draw()
		fr.SaveAs(filename.replace(".root","mass_plot.root"))
			 
	yieldNames = ["nBs","nBd","n_bkg", "nLbK","nLbpi"]
	print "(00)"
	print "LbK", nLbK.getVal(), nLbK.getError()
	print "Lbpi", nLbpi.getVal(), nLbpi.getError()

	sData = RooStats.SPlot("sData","An SPlot",my_dataset,my_model,RooArgList(ns,nd,nbkg, nLbK,nLbpi))
	#return sData, my_dataset,my_model, my_file, ns, nd, nbkg
## Extracting sWeights:
	sWList = []
	corrFactor=0.
	sumW=0.
	sumSqW=0.
    
	for nPar in range(len(yieldNames)): sWList.append([])
	for entry in range(int(my_tree.GetEntries())):
		my_tree.GetEntry(entry)
		for yName in range(len(yieldNames)):
		
			#print "Here: ", yName, entry, my_tree.B0_MM
			www = sData.GetSWeight(entry,yieldNames[yName])
			#print ".____.", www
			sWList[yName].append(www)
               
## Filling the branch:
            
		sWValue.sWFloat = sWList[yield_cat][entry]
		sWBranch.Fill()
		
		sumW += sWList[yield_cat][entry]
		sumSqW+= (sWList[yield_cat][entry])**2
        
##################################
        
	corrFactor=sumW/sumSqW
	print "corrFactor=sumW/sumSqW= ",corrFactor 
	for entry in range(int(my_tree.GetEntries())):
		cor_sWValue.cor_sWFloat = corrFactor*sWList[yield_cat][entry]
		cor_sWBranch.Fill()
	print '\nElapsed time: ' + str(time.time()-timeZero) + ' s.'
	my_tree.Write("",TObject.kOverwrite)
	my_file.Close()

    
	return 0#fr, my_dataset, my_model

#"2011p_826_861.root"

#f = TFile("~/NTuplesFast/Carlos_newsel/" + neim)
#t = f.Get("DecayTree")
f2 = TFile(NTUPLE_PATH + neim)#, "recreate")
#t2 = t.CopyTree("B0_MM >= " +str(Mass.getMin()) + " && B0_MM <= " + str(Mass.getMax()))
#t2.Write()
f2.Close()
out  = computeWeights(f2.GetName(), wcat)

##Here:  2 4251 5259.316
##.____. -0.0254009310542
##Here:  0 4252 5274.822

## *** Break *** segmentation violation
##    __boot()
