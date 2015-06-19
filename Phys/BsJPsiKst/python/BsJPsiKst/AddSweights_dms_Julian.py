from ROOT import *
from math import *
import os
import sys
import time
from Urania import *
AccessPackage("Bs2MuMu")
from smartpyROOT import *
from PDF_2013_Asym import *
from OurSites import NTUPLE_PATH

timeZero = time.time()

massB = SignalMass("signal")
bkgmodel = FullBackground("Bkg")
#bkgmodel.make()

def computeWeights(filename,  WEIGHT_CAT):	
	my_file = TFile(filename,"update")
	my_tree = my_file.Get("DecayTree")
	my_dataset = RooDataSet("data","data",my_tree,RooArgSet(Mass))

	gROOT.ProcessLine("struct MyStruct{Float_t sWFloat;};")
	gROOT.ProcessLine("struct MyStruct2{Float_t cor_sWFloat;};")
	from ROOT import MyStruct
	from ROOT import MyStruct2
	nd = RooRealVar("nBd","nBd", 0.5*(my_tree.GetEntries()),my_tree.GetEntries())
	ns = RooRealVar("nBs","nBs", 0.,0.5*(my_tree.GetEntries()))
	nbkg = RooRealVar("n_bkg","n_bkg", 0.,my_tree.GetEntries())

	my_model = RooAddPdf("model","model",RooArgList(massB.sigBs,massB.sigBd,bkgmodel.massbkg),RooArgList(ns,nd,nbkg))

	sWValue = MyStruct()
	cor_sWValue = MyStruct2()
	sWeights_Bs_F = "sWeights_" +WEIGHT_CAT+"/F"
	sWBranch = my_tree.Branch("sWeights_"+WEIGHT_CAT, AddressOf(sWValue,'sWFloat'),"sWeights_"+WEIGHT_CAT+"/F") 
	cor_sWBranch = my_tree.Branch("cor_sWeights_"+WEIGHT_CAT, AddressOf(cor_sWValue,'cor_sWFloat'), "cor_sWeights_"+WEIGHT_CAT+"/F") 
#############
	yield_cat=0
	if(WEIGHT_CAT=="Bs"): yield_cat=0
	else: yield_cat=1
    
	fitres =my_model.fitTo(my_dataset,RooFit.Save(),RooFit.NumCPU(8))
	
	yieldNames = ["nBs","nBd","n_bkg"]
	
	sData = RooStats.SPlot("sData","An SPlot",my_dataset,my_model,RooArgList(ns,nd,nbkg))
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

    
	return 0    

import sys
neim = sys.argv[1]
print neim
wcat = sys.argv[2]
print wcat

out  = computeWeights(neim, wcat)

#BREAK
#"2011p_826_861.root"

#f = TFile("~/NTuplesFast/Carlos_newsel/" + neim)
#t = f.Get("DecayTree")
#f2 = TFile("~/NTuplesFast/Carlos_NS_sw/" + neim)#, "recreate")
#t2 = t.CopyTree("B0_MM >= " +str(Mass.getMin()) + " && B0_MM <= " + str(Mass.getMax()))
#t2.Write()
#f2.Close()
#out  = computeWeights(f2.GetName(), wcat)

##Here:  2 4251 5259.316
##.____. -0.0254009310542
##Here:  0 4252 5274.822

## *** Break *** segmentation violation
##    __boot()



