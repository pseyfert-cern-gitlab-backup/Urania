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
WEIGHT_CAT= "Bs"
YEAR =2012
timeZero = time.time()


WEIGHT_CAT== "Bs"

if (YEAR==2011):

        pathTuple = NTUPLE_PATH + "2011diego20131115.root"
        print "sWeights extraction for Bs2JpsiKst data."
        os.system("cp "+pathTuple+" ./test_data2011_sWeights_"+WEIGHT_CAT+".root") 
        fx=TFile("junk2011p.root","recreate") 

        Mmax = 5450.
        cuts = "B0_MM>5150. && B0_MM<"+str(Mmax)
        f11 = TFile("./test_data2011_sWeights_"+WEIGHT_CAT+".root","update") 
        t2_11 = f11.Get("DecayTree")
        t11=t2_11.CopyTree(cuts)
else:

        pathTuple = NTUPLE_PATH + "2012diego20131118.root"
        os.system("cp "+pathTuple+" ./test_data2012_sWeights_"+WEIGHT_CAT+".root") 
        fx=TFile("junk2012p.root","recreate") 

        Mmax = 5450.
        cuts = "B0_MM>5150. && B0_MM<"+str(Mmax)
        f12 = TFile("./test_data2012_sWeights_"+WEIGHT_CAT+".root","update") 
        t2_12 = f12.Get("DecayTree")
        t12=t2_12.CopyTree(cuts)


samplename = "sample"
cat =  RooCategory(samplename, samplename)
if (YEAR==2011):

    cat.defineType("2011")
    mass2011 = SignalMass("2011")
    nd_2011 = RooRealVar("nBd_2011","nBd_2011", 0.5*(t11.GetEntries()),t11.GetEntries())
    ns_2011 = RooRealVar("nBs_2011","nBs_2011", 0.,0.5*(t11.GetEntries()))
    nbkg_2011 = RooRealVar("n_bkg_2011","n_bkg_2011", 0.,t11.GetEntries())

    bkgmodel_2011 = FullBackground("Bkg_2011")
    bkgmodel_2011.make()

    model11 = RooAddPdf("model11","model11",RooArgList(mass2011.sigBs,mass2011.sigBd,bkgmodel_2011.model),RooArgList(ns_2011,nd_2011,nbkg_2011))
    dataset11 = RooDataSet("data11","data11",t11,RooArgSet(Mass))
    
elif (YEAR==2012):

    cat.defineType("2012")
    mass2012 = SignalMass("2012")
    nd_2012 = RooRealVar("nBd_2012","nBd_2012", 0.5*(t12.GetEntries()),t12.GetEntries())
    ns_2012 = RooRealVar("nBs_2012","nBs_2012", 0.,0.5*(t12.GetEntries()))
    nbkg_2012 = RooRealVar("n_bkg_2012","n_bkg_2012", 0.,t12.GetEntries())

    bkgmodel_2012 = FullBackground("Bkg_2012")
    bkgmodel_2012.make()

    model12 = RooAddPdf("model12","model12",RooArgList(mass2012.sigBs,mass2012.sigBd,bkgmodel_2012.model),RooArgList(ns_2012,nd_2012,nbkg_2012))
    dataset12 = RooDataSet("data12","data12",t12,RooArgSet(Mass))
    
    print "t12 entries :   ",t12.GetEntries()
    print "t12 - dataset12 ", t12.GetEntries()-dataset12.sumEntries()
else:
    "check your ntuples"




def computeWeights(my_file, my_dataset, my_tree, my_model):
        
    gROOT.ProcessLine("struct MyStruct{Float_t sWFloat;};")
    gROOT.ProcessLine("struct MyStruct2{Float_t cor_sWFloat;};")
    from ROOT import MyStruct
    from ROOT import MyStruct2
    
    
    sWValue = MyStruct()
    cor_sWValue = MyStruct2()
    sWeights_Bs_F = "sWeights_" +WEIGHT_CAT+"/F"
    sWBranch = my_tree.Branch("sWeights_"+WEIGHT_CAT, AddressOf(sWValue,'sWFloat'),"sWeights_"+WEIGHT_CAT+"/F") 
    cor_sWBranch = my_tree.Branch("cor_sWeights_"+WEIGHT_CAT, AddressOf(cor_sWValue,'cor_sWFloat'), "cor_sWeights_"+WEIGHT_CAT+"/F") 
#############
    minos = 0
    yield_cat=0
    if(WEIGHT_CAT=="Bs"):
     yield_cat=0
    else:
     yield_cat=1

    fitres =my_model.fitTo(my_dataset,RooFit.Minos(minos),RooFit.Save(),RooFit.NumCPU(8))

    yieldNames = ["nBs_"+str(YEAR),"nBd_"+str(YEAR),"n_bkg_"+str(YEAR)]
    if YEAR== 2012:

        sData = RooStats.SPlot("sData","An SPlot",my_dataset,my_model,RooArgList(ns_2012,nd_2012,nbkg_2012))
    else:
        sData = RooStats.SPlot("sData","An SPlot",my_dataset,my_model,RooArgList(ns_2011,nd_2011,nbkg_2011))
## Extracting sWeights:
    sWList = []
    corrFactor=0.
    sumW=0.
    sumSqW=0.
        
    for nPar in range(len(yieldNames)):
        sWList.append([])
        print '\nExtracting sWeights...'
    for entry in range(int(my_tree.GetEntries())):
        for yName in range(len(yieldNames)):
            sWList[yName].append(sData.GetSWeight(entry,yieldNames[yName]))
               
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



if (YEAR==2011):
    my_int = computeWeights(my_file = f11, my_dataset= dataset11, my_tree=t11, my_model = model11)
    os.system('rm junk2011p.root')
else:
    my_int = computeWeights(my_file = f12, my_dataset= dataset12, my_tree=t12, my_model = model12)
    os.system('rm junk2012p.root')
