from array import array
import sys
import os
import time
import math
from collections import defaultdict, namedtuple
import numpy as np
import gc

from ROOT import TFile, TTree, TCanvas, TGraphAsymmErrors, TH2D
from ROOT import kFALSE, kTRUE, kDashed
from ROOT import RooFit, RooRealVar, RooArgList, RooArgSet, RooDataSet, RooFormulaVar, RooExponential, RooGaussian, RooAddPdf, RooCBShape, RooCategory, RooSimultaneous, RooDataHist, RooMsgService

from TrackCalib.Utils import *

import resource
def using(point=""):
    usage=resource.getrusage(resource.RUSAGE_SELF)
    return '''%s: usertime=%s systime=%s mem=%s mb
           '''%(point,usage[0],usage[1],
                (usage[2]*resource.getpagesize())/1000000.0 )


def Fit(method, mode, WGProduct, year, simVer="Sim09b", polarity = "", verbose=True, variables="", variables2D="", binning="", simpleFit=False, simFit=True, matchCrit = "", binnedFit = False, nBins = 100):

    # start printout
    print '##########################################################'
    print '#               Welcome to TrackEff Fitter               #'
    print '#                    Running on %s                     #' %mode.ljust(4)
    print '#                   Using %s method                    #' %method.ljust(4)
    print '##########################################################'

    # load the the input tuple
    inputPath = "tuples/"

    #create results path if not existing
    outputPath = ""
    if matchCrit == "":
        outputPath = "results/"+year
        if WGProduct: outputPath +="_WG"
        if polarity != "": outputPath +="_" + polarity
        if mode=="MC": outputPath +="/"+simVer
    else:
        outputPath = "results/"+year
        if WGProduct: outputPath +="_WG"
        if polarity != "": outputPath +="_" + polarity
        outputPath +="_tight"
        if mode=="MC": outputPath +="/"+simVer
    if not os.path.exists(outputPath):
        if verbose: InfoMsgList("Creating new folder for results:", outputPath)
        os.makedirs(outputPath)
    else: InfoMsgList("Output path used:", outputPath)


    #set options
    plot_mass   = True
    plot_eff    = True
    simple_fit  = simpleFit
    n_cores     = 8
    if mode == "Data" and "50ns" not in year and "5TeV" not in year:
        binnedFit = True
        if verbose: WarnMsg( "Large dataset, using binned fit!")

    #for verbose output, write log file
    #if opts.verbose:
    #    print "Writing log file to", "output_"+opts.mode+"_"+opts.method+".log"
    #    log_file = open("output_"+opts.mode+"_"+opts.method+".log","w")
    #    sys.stdout = log_file


    #set the mode
    data = True if mode == "Data" else False

    #create the default variable/bin border dictionary
    bin_dict = {"P"         : [ 5000., 10000., 20000., 40000., 100000., 200000. ],
                "ETA"       : [ 1.9, 3.2, 4.9 ],
                "Mother_ETA": [ 1.9, 2.4, 2.8, 3.0, 3.2, 3.6, 4.0, 4.5, 4.9 ],
                "nSPDHits"  : [ 0, 100, 200, 300, 400, 450 ],
                "nPVs"      : [ 0.5, 1.5, 2.5, 3.5, 4.5, 5.5 ]
               }

    #default list of variables used
    var_list = [ i for i in sorted(bin_dict.keys()) ]

    #default set of 2D variable combinations
    var_dict_2D = {
            "P-ETA":    ["P","ETA"],
            }

    #check if custom binning is defined, overwrite respective defaults
    if binning != "":
        bin_custom = binning
        bin_custom = bin_custom.split(';')


        for var_string in bin_custom:
            tmpvar = var_string.split(':')
            tmpbin = tmpvar[1].split(',')
            tmpbinlist = [float(i) for i in tmpbin]

            #fill dictionary
            bin_dict[tmpvar[0]] = tmpbinlist
        if verbose: InfoMsgList("Custom binning scheme used:", bin_dict)

    #check if custom variables are requested, use instead of defaults
    if variables != "":
        var_custom = variables
        var_custom = var_custom.split(',')

        var_list = var_custom
        if verbose: InfoMsgList("Custom set of variables requested:", var_list)

    #check if custom 2D variables are requested, use instead of defaults
    if "P" not in var_list or "ETA" not in var_list: var_dict_2D = {}
    if variables2D != "":
        var_dict_2D = {}
        var_custom2D = variables2D
        var_custom2D = var_custom2D.split(',')

        #decompose 2D var in subvars
        for string2D in var_custom2D:
            tmpvar = string2D.split('-')
            var_dict_2D[string2D] = [tmpvar[0],tmpvar[1]]

        if verbose: InfoMsgList( "Custom set of 2D variables requested:", var_dict_2D)

    #check if binning for all variables available, else throw error and remove it
    for i in var_list:
        if i not in bin_dict.keys():
            WarnMsg('No binning given for custom variable ' + i +', it will be ignored!')
            var_list.remove(i)

    #split the list into multiplicity and remaining variables
    var_mult = []
    var_rem = []
    for i in var_list:
        if i.startswith("n") or i.startswith("M"):
            var_mult.append(i)
        else: var_rem.append(i)
    #also add missing variables from 2D set
    for key, varl in var_dict_2D.iteritems():
        for var in varl:
            if var not in var_rem:
                var_rem.append(var)

    #disable ROOFit info printouts, when not in verbose mode
    if not verbose:
        RooMsgService.instance().setGlobalKillBelow(RooFit.WARNING)

    ########################END OF ARGUMENT PARSING#########################

    InfoMsg(using("Before file read-in"))

    #read input trees
    if matchCrit == "":
        if mode == "MC": inputFileName = inputPath+"trackEffTuple_"+mode+"_"+year+"_"+simVer
        else: inputFileName = inputPath+"trackEffTuple_"+mode+"_"+year
        if WGProduct:   inputFileName += "_WG"
        inputFileName += ".root"
    else:
        if mode == "MC": inputFileName = inputPath+"trackEffTuple_"+mode+"_"+year+"_"+simVer+"_tight"
        else: inputFileName = inputPath+"trackEffTuple_"+mode+"_"+year + "_tight"
        if WGProduct:   inputFileName += "_WG"
        inputFileName += ".root"


    infile = TFile(inputFileName)
    if verbose:
        InfoMsg("Using " + inputFileName + " as an input for fitting.")
    dummyfile = TFile("dummy.root","RECREATE")
    dummyfile.cd()
    cuts = "Mother_ETA > 0 "
    if (polarity == "MagDown"): cuts += " && Polarity == -1"
    elif (polarity == "MagUp"): cuts += " && Polarity == 1"
    if verbose: InfoMsg("Appling additional cut on plus and minus trees: " + cuts )
    treePlus    = infile.Get("TrackEffTreePlus"+method).CopyTree(cuts,"",long(18.e6),0)
    treeMinus   = infile.Get("TrackEffTreeMinus"+method).CopyTree(cuts,"",long(18.e6),0)
    InfoMsg(using("Trees read"))
    sampleSize = treePlus.GetEntries()+treeMinus.GetEntries()
    InfoMsg( "Sample size: "+str(sampleSize) )

    # ----------------------------------------------------
    # -- RooFit stuff: This constructs an exponential background and a single / double CB
    # ----------------------------------------------------

    JpsiMass = RooRealVar("J_psi_1S_M","Mass of J/psi",2625., 3575.,"MeV/c^{2}")
    JpsiMass.setBins(nBins)
    if method == "Velo":
        JpsiMass.setRange(2925.,3275.)

    meanCB  = RooRealVar("meanCB","meanCB for CB",3094.0, 3090.0,3115.0)
    sigma   = RooRealVar("sigma","sigma for gauss",30.0, 5.0, 100.0)
    sigma2  = RooRealVar("sigma2","sigma 2 for gauss",70.0, 15.0, 185.0)
    sigma3  = RooRealVar("sigma3","sigma 3 for gauss",10.0, 1.0, 150.0)
    fracCB  = RooRealVar("fracCB","crystal ball fraction", 0.5, 0., 1.)
    fracCB2 = RooRealVar("fracCB2","crystal ball fraction 2", 0.5, 0., 1.)

    alpha   = RooRealVar("alpha", "alpha for CB", 1.0, 0., 15.0)
    n       = RooRealVar("n", "n for CB", 1.0, 0., 15.0)

    tau     = RooRealVar("tau","decay constant of exp",-0.0005,-0.01, 0.01)
    tauF    = RooRealVar("tauF","decay constant of exp fail",-0.0005,-0.01, 0.01)

    signal_yield        = RooRealVar("signal_yield","Yield of signal", 0.5*sampleSize, 0.0, sampleSize)
    background_yield    = RooRealVar("background_yield","Yield of background", 0.5*sampleSize, 0.0, sampleSize)

    myExpo          = RooExponential("myExpo","exponential background",JpsiMass,tau)
    mySingleGauss1  = RooGaussian("mySingleGauss1","single Gauss 1", JpsiMass, meanCB, sigma)
    mySingleGauss2  = RooGaussian("mySingleGauss2","single Gauss 2", JpsiMass, meanCB, sigma2)
    mySingleGauss3  = RooGaussian("mySingleGauss3","single Gauss 3", JpsiMass, meanCB, sigma3)
    myGaussSum      = RooAddPdf("myGaussSum", "Gauss sum", RooArgList(mySingleGauss1, mySingleGauss2), RooArgList(fracCB))
    myCB            = RooCBShape("myCB", "crystal ball", JpsiMass, meanCB, sigma, alpha, n)
    myCB2           = RooCBShape("myCB2", "crystal ball 2", JpsiMass, meanCB, sigma2, alpha, n)
    myCBsum         = RooAddPdf("myCBsum", "CB sum", RooArgList(myCB, myCB2), RooArgList(fracCB))
    myGaussCB       = RooAddPdf("myGaussCB", "Gauss + CB", RooArgList(mySingleGauss1, myCB2), RooArgList(fracCB))

    if simple_fit:
        totalShape  = RooAddPdf("totalShape", "total pdf", RooArgList(myGaussSum, myExpo), RooArgList(signal_yield, background_yield))
    else:
        totalShape = RooAddPdf("totalShape", "total pdf", RooArgList(myCBsum, myExpo), RooArgList(signal_yield, background_yield))

    #some definitions for sim. fit
    sigma2F         = RooRealVar("sigma2F","sigma 2 for gauss fail",70.0, 15.0, 185.0)
    fracCBF         = RooRealVar("fracCBF","crystal ball fraction fail", 0.5, 0., 1.)
    myExpoP         = RooExponential("myExpoP","exponential background pass",JpsiMass,tau)
    myCBP           = RooCBShape("myCBP", "crystal ball pass", JpsiMass, meanCB, sigma, alpha, n)
    myCB2P          = RooCBShape("myCB2P", "crystal ball 2 pass", JpsiMass, meanCB, sigma2, alpha, n)
    myCBsumP        = RooAddPdf("myCBsumP", "CB sum pass", RooArgList(myCBP, myCB2P), RooArgList(fracCB))
    myExpoF         = RooExponential("myExpoF","exponential background fail",JpsiMass,tauF)
    myCBF           = RooCBShape("myCBF", "crystal ball fail", JpsiMass, meanCB, sigma, alpha, n)
    #myCB2F          = RooCBShape("myCB2F", "crystal ball 2 fail", JpsiMass, meanCB, sigma2F, alpha, n)
    #myCBsumF        = RooAddPdf("myCBsumF", "CB sum fail", RooArgList(myCBF, myCB2F), RooArgList(fracCBF))
    myCB2F          = RooCBShape("myCB2F", "crystal ball 2 fail", JpsiMass, meanCB, sigma2, alpha, n)
    myCBsumF        = RooAddPdf("myCBsumF", "CB sum fail", RooArgList(myCBF, myCB2F), RooArgList(fracCB))

    mySingleGauss1F = RooGaussian("mySingleGauss1F","single Gauss 1 failed", JpsiMass, meanCB, sigma)
    mySingleGauss2F = RooGaussian("mySingleGauss2F","single Gauss 2 failed", JpsiMass, meanCB, sigma2)
    mySingleGauss3F = RooGaussian("mySingleGauss3F","single Gauss 3 failed", JpsiMass, meanCB, sigma3)
    myGaussSumF     = RooAddPdf("myGaussSumF", "Gauss sum failed", RooArgList(mySingleGauss1F, mySingleGauss2F), RooArgList(fracCB))

    efficiency_sig  = RooRealVar("efficiency_sig","signal efficiency",0.,1.)
    efficiency_bkg  = RooRealVar("efficiency_bkg","background efficiency",0.,1.)
    f_pass          = RooFormulaVar("f_pass", "pass fraction", "@0*@1", RooArgList(signal_yield,efficiency_sig))
    f_fail          = RooFormulaVar("f_fail", "fail fraction", "@0*(1.-@1)", RooArgList(signal_yield,efficiency_sig))
    f_pass_bkg      = RooFormulaVar("f_pass_bkg", "pass fraction bkg.", "@0*@1", RooArgList(background_yield,efficiency_bkg))
    f_fail_bkg      = RooFormulaVar("f_fail_bkg", "fail fraction bkg.", "@0*(1.-@1)", RooArgList(background_yield,efficiency_bkg))

    if simple_fit:
        totalShapeP = RooAddPdf("totalShapeP", "total pdf pass", RooArgList(myGaussSum, myExpoP), RooArgList(f_pass, f_pass_bkg))
        totalShapeF = RooAddPdf("totalShapeF", "total pdf fail", RooArgList(myGaussSumF, myExpoF), RooArgList(f_fail, f_fail_bkg))
    else:
        totalShapeP = RooAddPdf("totalShapeP", "total pdf pass", RooArgList(myCBsumP, myExpoP), RooArgList(f_pass, f_pass_bkg))
        totalShapeF = RooAddPdf("totalShapeF", "total pdf fail", RooArgList(myCBsumF, myExpoF), RooArgList(f_fail, f_fail_bkg))

    if simFit:
        InfoMsg("Simultaneous fit active!")
        #define category for sim. fit
        sample          = RooCategory("sample","sample")
        sample.defineType("pass")
        sample.defineType("fail")
        #build sim. PDF
        simPDF          = RooSimultaneous("simPDF","simultaneous PDF",sample)
        simPDF.addPdf(totalShapeP,"pass")
        simPDF.addPdf(totalShapeF,"fail")

    #additional variables needed
    matched         = RooRealVar("matched","matched", 0, 1)
    weight          = RooRealVar("weight","weight", 0., 100.)
    totCandidates   = RooRealVar("totCandidates","totCandidates", 0.,100.)

    #variables for the efficiency binning

    #create variables set for muplus/minus
    var_muplus_dict = {}
    var_muminus_dict = {}
    for i in var_rem:
        var_muplus_dict[i] = RooRealVar("muplus_"+i, "muplus_"+i, min(bin_dict[i]), 2*max(bin_dict[i]))
        var_muminus_dict[i] = RooRealVar("muminus_"+i, "muminus_"+i, min(bin_dict[i]), 2*max(bin_dict[i]))

    #create global variables
    var_global_dict = {}
    for i in var_mult:
        var_global_dict[i] = RooRealVar(i, i, min(bin_dict[i]), 2*max(bin_dict[i]))

    #define cuts for association
    Match   = "matched == 1"
    Fail    = "matched == 0"

    #RooArgSet to include all variables
    plusArgSet  = RooArgSet(JpsiMass, weight, matched)
    minusArgSet = RooArgSet(JpsiMass, weight, matched)
    for i in var_rem:
        plusArgSet.add(var_muplus_dict[i])
        minusArgSet.add(var_muminus_dict[i])
    for i in var_mult:
        plusArgSet.add(var_global_dict[i])
        minusArgSet.add(var_global_dict[i])

    ###################################################
    #create datasets
    ###################################################

    InfoMsg("Started creating datasets!")
    InfoMsg(using("Datasets"))

    #deactivate unused branches to reduce dataset size
    treePlus.SetBranchStatus("*",0)
    treeMinus.SetBranchStatus("*",0)
    treePlus.SetBranchStatus("J_psi_1S_M",1)
    treePlus.SetBranchStatus("matched",1)
    treePlus.SetBranchStatus("weight",1)
    treeMinus.SetBranchStatus("J_psi_1S_M",1)
    treeMinus.SetBranchStatus("matched",1)
    treeMinus.SetBranchStatus("weight",1)
    for var in var_muplus_dict.keys():
        treePlus.SetBranchStatus("muplus_"+var,1)
    for var in var_muminus_dict.keys():
        treeMinus.SetBranchStatus("muminus_"+var,1)
    for var in var_global_dict.keys():
        treePlus.SetBranchStatus(var,1)
        treeMinus.SetBranchStatus(var,1)

    #global datasets
    #plusDataSet  = RooDataSet("plusDataSet","plusDataSet", treePlus, plusArgSet)
    #minusDataSet = RooDataSet("minusDataSet","minusDataSet", treeMinus, minusArgSet)
    #InfoMsg(using("Plus/Minus Datasets"))
    #del treePlus, treeMinus
    gc.collect()

    if verbose:
        #print "Plus sample size:", plusDataSet.sumEntries()
        #print "Minus sample size:", minusDataSet.sumEntries()
        InfoMsgList( "Plus sample size:", treePlus.GetEntries())
        InfoMsgList( "Minus sample size:", treeMinus.GetEntries())

    #global datasets, always created
    #plusDataSetAssoc    = RooDataSet("plusDataSetAssoc","plusDataSetAssoc", plusDataSet, RooArgSet(JpsiMass, weight, matched), Match )
    #minusDataSetAssoc   = RooDataSet("minusDataSetAssoc","minusDataSetAssoc", minusDataSet, RooArgSet(JpsiMass, weight, matched), Match )
    #plusDataSetFail     = RooDataSet("plusDataSetFail","plusDataSetFail", plusDataSet, RooArgSet(JpsiMass, weight, matched), Fail )
    #minusDataSetFail    = RooDataSet("minusDataSetFail","minusDataSetFail", minusDataSet, RooArgSet(JpsiMass, weight, matched), Fail )
    plusDataSetAssoc    = RooDataSet("plusDataSetAssoc","plusDataSetAssoc", treePlus, RooArgSet(JpsiMass, weight, matched), Match )
    minusDataSetAssoc   = RooDataSet("minusDataSetAssoc","minusDataSetAssoc", treeMinus, RooArgSet(JpsiMass, weight, matched), Match )
    plusDataSetFail     = RooDataSet("plusDataSetFail","plusDataSetFail", treePlus, RooArgSet(JpsiMass, weight, matched), Fail )
    minusDataSetFail    = RooDataSet("minusDataSetFail","minusDataSetFail", treeMinus, RooArgSet(JpsiMass, weight, matched), Fail )
    InfoMsg(using("Plus/Minus fail/match Datasets"))

    #merge plus and minus sets, apply weight;
    if binnedFit:
        #fullDataSettmp = RooDataSet("fullDataSettmp", "fullDataSettmp", RooArgSet(JpsiMass, weight), RooFit.Import(plusDataSet), RooFit.WeightVar("weight"))
        #fullDataSet2 = RooDataSet("fullDataSet2", "fullDataSet2", RooArgSet(JpsiMass, weight), RooFit.Import(minusDataSet), RooFit.WeightVar("weight"))
        fullDataSettmp = RooDataSet("fullDataSettmp", "fullDataSettmp", RooArgSet(JpsiMass, weight), RooFit.Import(treePlus), RooFit.WeightVar("weight"))
        fullDataSet2 = RooDataSet("fullDataSet2", "fullDataSet2", RooArgSet(JpsiMass, weight), RooFit.Import(treeMinus), RooFit.WeightVar("weight"))
        fullDataSettmp.append(fullDataSet2)
        fullDataSet = RooDataHist("fullDataSet","fullDataSet",RooArgSet(JpsiMass),fullDataSettmp)
        del fullDataSet2
        gc.collect()
        InfoMsg(using("Full Dataset"))

        fullDataSetMatchtmp = RooDataSet("fullDataSetMatchtmp", "fullDataSetMatchtmp", RooArgSet(JpsiMass, weight), RooFit.Import(plusDataSetAssoc), RooFit.WeightVar("weight"))
        fullDataSetMatch2 = RooDataSet("fullDataSetMatch2", "fullDataSetMatch2", RooArgSet(JpsiMass, weight), RooFit.Import(minusDataSetAssoc), RooFit.WeightVar("weight"))
        fullDataSetMatchtmp.append(fullDataSetMatch2)
        fullDataSetMatch = RooDataHist("fullDataSetMatch","fullDataSetMatch",RooArgSet(JpsiMass),fullDataSetMatchtmp)
        del fullDataSetMatch2
        gc.collect()
        InfoMsg(using("Matched Dataset"))

        fullDataSetFailtmp = RooDataSet("fullDataSetFailtmp", "fullDataSetFailtmp", RooArgSet(JpsiMass, weight), RooFit.Import(plusDataSetFail), RooFit.WeightVar("weight"))
        fullDataSetFail2 = RooDataSet("fullDataSetFail2", "fullDataSetFail2", RooArgSet(JpsiMass, weight), RooFit.Import(minusDataSetFail), RooFit.WeightVar("weight"))
        fullDataSetFailtmp.append(fullDataSetFail2)
        fullDataSetFail = RooDataHist("fullDataSetFail","fullDataSetFail",RooArgSet(JpsiMass),fullDataSetFailtmp)
        del fullDataSetFail2
        gc.collect()
        InfoMsg(using("Failed Dataset"))

        if verbose:
            InfoMsgList("Full sample size:"           , fullDataSet.sumEntries() )
            InfoMsgList("Full matched sample size:"   , fullDataSetMatch.sumEntries() )
            InfoMsgList("Full failed sample size:"    , fullDataSetFail.sumEntries() )

        if simFit:
            fullDataSetCombTmp = RooDataSet("fullDataSetCombTmp", "fullDataSetCombTmp", RooArgSet(JpsiMass, weight), RooFit.Index(sample), RooFit.Import("pass",fullDataSetMatchtmp), RooFit.Import("fail",fullDataSetFailtmp), RooFit.WeightVar("weight") )
            fullDataSetComb = RooDataHist("fullDataSetComb", "fullDataSetComb", RooArgSet(JpsiMass, sample), fullDataSetCombTmp)
            del fullDataSettmp, fullDataSetMatchtmp, fullDataSetFailtmp, fullDataSetCombTmp
            gc.collect()

    #merge plus and minus sets, apply weight;
    else:
        #fullDataSet = RooDataSet("fullDataSettmp", "fullDataSettmp", RooArgSet(JpsiMass, weight), RooFit.Import(plusDataSet), RooFit.WeightVar("weight"))
        #fullDataSet2 = RooDataSet("fullDataSet2", "fullDataSet2", RooArgSet(JpsiMass, weight), RooFit.Import(minusDataSet), RooFit.WeightVar("weight"))
        fullDataSet = RooDataSet("fullDataSettmp", "fullDataSettmp", RooArgSet(JpsiMass, weight), RooFit.Import(treePlus), RooFit.WeightVar("weight"))
        fullDataSet2 = RooDataSet("fullDataSet2", "fullDataSet2", RooArgSet(JpsiMass, weight), RooFit.Import(treeMinus), RooFit.WeightVar("weight"))
        fullDataSet.append(fullDataSet2)

        fullDataSetMatch = RooDataSet("fullDataSetMatchtmp", "fullDataSetMatchtmp", RooArgSet(JpsiMass, weight), RooFit.Import(plusDataSetAssoc), RooFit.WeightVar("weight"))
        fullDataSetMatch2 = RooDataSet("fullDataSetMatch2", "fullDataSetMatch2", RooArgSet(JpsiMass, weight), RooFit.Import(minusDataSetAssoc), RooFit.WeightVar("weight"))
        fullDataSetMatch.append(fullDataSetMatch2)

        fullDataSetFail = RooDataSet("fullDataSetFailtmp", "fullDataSetFailtmp", RooArgSet(JpsiMass, weight), RooFit.Import(plusDataSetFail), RooFit.WeightVar("weight"))
        fullDataSetFail2 = RooDataSet("fullDataSetFail2", "fullDataSetFail2", RooArgSet(JpsiMass, weight), RooFit.Import(minusDataSetFail), RooFit.WeightVar("weight"))
        fullDataSetFail.append(fullDataSetFail2)

        if verbose:
            InfoMsgList( "Full sample size:"           , fullDataSet.sumEntries())
            InfoMsgList( "Full matched sample size:"   , fullDataSetMatch.sumEntries() )
            InfoMsgList( "Full failed sample size:"    , fullDataSetFail.sumEntries() )

        if simFit:
            fullDataSetComb = RooDataSet("fullDataSetComb", "fullDataSetComb", RooArgSet(JpsiMass, weight), RooFit.Index(sample), RooFit.Import("pass",fullDataSetMatch), RooFit.Import("fail",fullDataSetFail), RooFit.WeightVar("weight") )
    gc.collect()

    #create datasets for all vars and bins
    dataset_dict        = {}
    dataset_dict_match  = {}
    dataset_dict_fail   = {}
    dataset_dict_comb   = {}

    #loop over variables
    for var in var_rem:
        dataset_dict[var]       = []
        dataset_dict_match[var] = []
        dataset_dict_fail[var]  = []
        dataset_dict_comb[var]  = []

        if verbose:
            InfoMsgList( "Creating datasets for variable",var)

        #loop over bins
        for bins in range(len(bin_dict[var])-1):
            #tmpdatasetplus       = RooDataSet("plusDataSet"+var+str(bins),"plusDataSet"+var+str(bins), plusDataSet,
            tmpdatasetplus       = RooDataSet("plusDataSet"+var+str(bins),"plusDataSet"+var+str(bins), treePlus,
                                              RooArgSet(JpsiMass, weight, matched, var_muplus_dict[var]),
                                              "muplus_"+var+" > "+str(bin_dict[var][bins])+" && muplus_"+var+" < "+str(bin_dict[var][bins+1]) )

            #tmpdatasetminus      = RooDataSet("minusDataSet"+var+str(bins),"minusDataSet"+var+str(bins), minusDataSet,
            tmpdatasetminus      = RooDataSet("minusDataSet"+var+str(bins),"minusDataSet"+var+str(bins), treeMinus,
                                              RooArgSet(JpsiMass, weight, matched, var_muminus_dict[var]),
                                              "muminus_"+var+" > "+str(bin_dict[var][bins])+" && muminus_"+var+" < "+str(bin_dict[var][bins+1]) )

            #tmpdatasetplusMatch  = RooDataSet("plusDataSetAssoc"+var+str(bins),"plusDataSetAssoc"+var+str(bins), plusDataSet,
            tmpdatasetplusMatch  = RooDataSet("plusDataSetAssoc"+var+str(bins),"plusDataSetAssoc"+var+str(bins), treePlus,
                                              RooArgSet(JpsiMass, weight, matched, var_muplus_dict[var]),
                                              Match+" && muplus_"+var+" > "+str(bin_dict[var][bins])+" && muplus_"+var+" < "+str(bin_dict[var][bins+1]) )

            #tmpdatasetminusMatch = RooDataSet("minusDataSetAssoc"+var+str(bins),"minusDataSetAssoc"+var+str(bins), minusDataSet,
            tmpdatasetminusMatch = RooDataSet("minusDataSetAssoc"+var+str(bins),"minusDataSetAssoc"+var+str(bins), treeMinus,
                                              RooArgSet(JpsiMass, weight, matched, var_muminus_dict[var]),
                                              Match+" && muminus_"+var+" > "+str(bin_dict[var][bins])+" && muminus_"+var+" < "+str(bin_dict[var][bins+1]) )

            #tmpdatasetplusFail   = RooDataSet("plusDataSetFail"+var+str(bins),"plusDataSetFail"+var+str(bins), plusDataSet,
            tmpdatasetplusFail   = RooDataSet("plusDataSetFail"+var+str(bins),"plusDataSetFail"+var+str(bins), treePlus,
                                              RooArgSet(JpsiMass, weight, matched, var_muplus_dict[var]),
                                              Fail+" && muplus_"+var+" > "+str(bin_dict[var][bins])+" && muplus_"+var+" < "+str(bin_dict[var][bins+1]) )

            #tmpdatasetminusFail  = RooDataSet("minusDataSetFail"+var+str(bins),"minusDataSetFail"+var+str(bins), minusDataSet,
            tmpdatasetminusFail  = RooDataSet("minusDataSetFail"+var+str(bins),"minusDataSetFail"+var+str(bins), treeMinus,
                                              RooArgSet(JpsiMass, weight, matched, var_muminus_dict[var]),
                                              Fail+" && muminus_"+var+" > "+str(bin_dict[var][bins])+" && muminus_"+var+" < "+str(bin_dict[var][bins+1]) )

            if binnedFit:
                tmpFullSetMatchTmp = RooDataSet("tmpFullSetMatchTmp", "tmpFullSetMatchTmp", RooArgSet(JpsiMass, weight), RooFit.Import(tmpdatasetplusMatch), RooFit.WeightVar("weight"))
                tmpFullSetMatch2 = RooDataSet("tmpFullSetMatch2", "tmpFullSetMatch2", RooArgSet(JpsiMass, weight), RooFit.Import(tmpdatasetminusMatch), RooFit.WeightVar("weight"))
                tmpFullSetMatchTmp.append(tmpFullSetMatch2)
                tmpFullSetMatch = RooDataHist("tmpFullSetMatch","tmpFullSetMatch",RooArgSet(JpsiMass),tmpFullSetMatchTmp)

                tmpFullSetFailTmp = RooDataSet("tmpFullSetFailTmp", "tmpFullSetFailTmp", RooArgSet(JpsiMass, weight), RooFit.Import(tmpdatasetplusFail), RooFit.WeightVar("weight"))
                tmpFullSetFail2 = RooDataSet("tmpFullSetFail2", "tmpFullSetFail2", RooArgSet(JpsiMass, weight), RooFit.Import(tmpdatasetminusFail), RooFit.WeightVar("weight"))
                tmpFullSetFailTmp.append(tmpFullSetFail2)
                tmpFullSetFail = RooDataHist("tmpFullSetFail","tmpFullSetFail",RooArgSet(JpsiMass),tmpFullSetFailTmp)

                tmpFullSetTmp = RooDataSet("tmpFullSetTmp", "tmpFullSetTmp", RooArgSet(JpsiMass, weight), RooFit.Import(tmpdatasetplus), RooFit.WeightVar("weight"))
                tmpFullSet2 = RooDataSet("tmpFullSet2", "tmpFullSet2", RooArgSet(JpsiMass, weight), RooFit.Import(tmpdatasetminus), RooFit.WeightVar("weight"))
                tmpFullSetTmp.append(tmpFullSet2)
                tmpFullSet = RooDataHist("tmpFullSet","tmpFullSet",RooArgSet(JpsiMass),tmpFullSetTmp)

                if simFit:
                    tmpFullSetCombTmp = RooDataSet("tmpDataSetCombTmp", "tmpDataSetCombTmp", RooArgSet(JpsiMass, weight), RooFit.Index(sample), RooFit.Import("pass",tmpFullSetMatchTmp), RooFit.Import("fail",tmpFullSetFailTmp), RooFit.WeightVar("weight") )
                    tmpFullSetComb = RooDataHist("tmpDataSetComb", "tmpDataSetComb", RooArgSet(JpsiMass, sample), tmpFullSetCombTmp)

            else:
                tmpFullSetMatch = RooDataSet("tmpFullSetMatch", "tmpFullSetMatch", RooArgSet(JpsiMass, weight), RooFit.Import(tmpdatasetplusMatch), RooFit.WeightVar("weight"))
                tmpFullSetMatch2 = RooDataSet("tmpFullSetMatch2", "tmpFullSetMatch2", RooArgSet(JpsiMass, weight), RooFit.Import(tmpdatasetminusMatch), RooFit.WeightVar("weight"))
                tmpFullSetMatch.append(tmpFullSetMatch2)

                tmpFullSetFail = RooDataSet("tmpFullSetFail", "tmpFullSetFail", RooArgSet(JpsiMass, weight), RooFit.Import(tmpdatasetplusFail), RooFit.WeightVar("weight"))
                tmpFullSetFail2 = RooDataSet("tmpFullSetFail2", "tmpFullSetFail2", RooArgSet(JpsiMass, weight), RooFit.Import(tmpdatasetminusFail), RooFit.WeightVar("weight"))
                tmpFullSetFail.append(tmpFullSetFail2)

                tmpFullSet = RooDataSet("tmpFullSet", "tmpFullSet", RooArgSet(JpsiMass, weight), RooFit.Import(tmpdatasetplus), RooFit.WeightVar("weight"))
                tmpFullSet2 = RooDataSet("tmpFullSet2", "tmpFullSet2", RooArgSet(JpsiMass, weight), RooFit.Import(tmpdatasetminus), RooFit.WeightVar("weight"))
                tmpFullSet.append(tmpFullSet2)

                if simFit:
                    tmpFullSetComb = RooDataSet("tmpDataSetComb", "tmpDataSetComb", RooArgSet(JpsiMass, weight), RooFit.Index(sample), RooFit.Import("pass",tmpFullSetMatch), RooFit.Import("fail",tmpFullSetFail), RooFit.WeightVar("weight") )

            dataset_dict[var].append(tmpFullSet)
            dataset_dict_match[var].append(tmpFullSetMatch)
            dataset_dict_fail[var].append(tmpFullSetFail)
            if simFit:
                dataset_dict_comb[var].append(tmpFullSetComb)
                del tmpFullSetMatch, tmpFullSetFail, tmpFullSet

    for var in var_mult:
        dataset_dict[var]       = []
        dataset_dict_match[var] = []
        dataset_dict_fail[var]  = []
        dataset_dict_comb[var]  = []

        if verbose:
            InfoMsgList( "Creating datasets for variable",var)

        #loop over bins
        for bins in range(len(bin_dict[var])-1):
            #tmpdatasetplus       = RooDataSet("plusDataSet"+var+str(bins),"plusDataSet"+var+str(bins), plusDataSet,
            tmpdatasetplus       = RooDataSet("plusDataSet"+var+str(bins),"plusDataSet"+var+str(bins), treePlus,
                                              RooArgSet(JpsiMass, weight, matched, var_global_dict[var]),
                                              var+" > "+str(bin_dict[var][bins])+" && "+var+" < "+str(bin_dict[var][bins+1]) )

            #tmpdatasetminus      = RooDataSet("minusDataSet"+var+str(bins),"minusDataSet"+var+str(bins), minusDataSet,
            tmpdatasetminus      = RooDataSet("minusDataSet"+var+str(bins),"minusDataSet"+var+str(bins), treeMinus,
                                              RooArgSet(JpsiMass, weight, matched, var_global_dict[var]),
                                              var+" > "+str(bin_dict[var][bins])+" && "+var+" < "+str(bin_dict[var][bins+1]) )

            #tmpdatasetplusMatch  = RooDataSet("plusDataSetAssoc"+var+str(bins),"plusDataSetAssoc"+var+str(bins), plusDataSet,
            tmpdatasetplusMatch  = RooDataSet("plusDataSetAssoc"+var+str(bins),"plusDataSetAssoc"+var+str(bins), treePlus,
                                              RooArgSet(JpsiMass, weight, matched, var_global_dict[var]),
                                              Match+" && "+var+" > "+str(bin_dict[var][bins])+" && "+var+" < "+str(bin_dict[var][bins+1]) )

            #tmpdatasetminusMatch = RooDataSet("minusDataSetAssoc"+var+str(bins),"minusDataSetAssoc"+var+str(bins), minusDataSet,
            tmpdatasetminusMatch = RooDataSet("minusDataSetAssoc"+var+str(bins),"minusDataSetAssoc"+var+str(bins), treeMinus,
                                              RooArgSet(JpsiMass, weight, matched, var_global_dict[var]),
                                              Match+" && "+var+" > "+str(bin_dict[var][bins])+" && "+var+" < "+str(bin_dict[var][bins+1]) )

            #tmpdatasetplusFail   = RooDataSet("plusDataSetFail"+var+str(bins),"plusDataSetFail"+var+str(bins), plusDataSet,
            tmpdatasetplusFail   = RooDataSet("plusDataSetFail"+var+str(bins),"plusDataSetFail"+var+str(bins), treePlus,
                                              RooArgSet(JpsiMass, weight, matched, var_global_dict[var]),
                                              Fail+" && "+var+" > "+str(bin_dict[var][bins])+" && "+var+" < "+str(bin_dict[var][bins+1]) )

            #tmpdatasetminusFail  = RooDataSet("minusDataSetFail"+var+str(bins),"minusDataSetFail"+var+str(bins), minusDataSet,
            tmpdatasetminusFail  = RooDataSet("minusDataSetFail"+var+str(bins),"minusDataSetFail"+var+str(bins), treeMinus,
                                              RooArgSet(JpsiMass, weight, matched, var_global_dict[var]),
                                              Fail+" && "+var+" > "+str(bin_dict[var][bins])+" && "+var+" < "+str(bin_dict[var][bins+1]) )

            if binnedFit:
                tmpFullSetMatchTmp = RooDataSet("tmpFullSetMatchTmp", "tmpFullSetMatchTmp", RooArgSet(JpsiMass, weight), RooFit.Import(tmpdatasetplusMatch), RooFit.WeightVar("weight"))
                tmpFullSetMatch2 = RooDataSet("tmpFullSetMatch2", "tmpFullSetMatch2", RooArgSet(JpsiMass, weight), RooFit.Import(tmpdatasetminusMatch), RooFit.WeightVar("weight"))
                tmpFullSetMatchTmp.append(tmpFullSetMatch2)
                tmpFullSetMatch = RooDataHist("tmpFullSetMatch","tmpFullSetMatch",RooArgSet(JpsiMass),tmpFullSetMatchTmp)

                tmpFullSetFailTmp = RooDataSet("tmpFullSetFailTmp", "tmpFullSetFailTmp", RooArgSet(JpsiMass, weight), RooFit.Import(tmpdatasetplusFail), RooFit.WeightVar("weight"))
                tmpFullSetFail2 = RooDataSet("tmpFullSetFail2", "tmpFullSetFail2", RooArgSet(JpsiMass, weight), RooFit.Import(tmpdatasetminusFail), RooFit.WeightVar("weight"))
                tmpFullSetFailTmp.append(tmpFullSetFail2)
                tmpFullSetFail = RooDataHist("tmpFullSetFail","tmpFullSetFail",RooArgSet(JpsiMass),tmpFullSetFailTmp)

                tmpFullSetTmp = RooDataSet("tmpFullSetTmp", "tmpFullSetTmp", RooArgSet(JpsiMass, weight), RooFit.Import(tmpdatasetplus), RooFit.WeightVar("weight"))
                tmpFullSet2 = RooDataSet("tmpFullSet2", "tmpFullSet2", RooArgSet(JpsiMass, weight), RooFit.Import(tmpdatasetminus), RooFit.WeightVar("weight"))
                tmpFullSetTmp.append(tmpFullSet2)
                tmpFullSet = RooDataHist("tmpFullSet","tmpFullSet",RooArgSet(JpsiMass),tmpFullSetTmp)

                if simFit:
                    tmpFullSetCombTmp = RooDataSet("tmpDataSetCombTmp", "tmpDataSetCombTmp", RooArgSet(JpsiMass, weight), RooFit.Index(sample), RooFit.Import("pass",tmpFullSetMatchTmp), RooFit.Import("fail",tmpFullSetFailTmp), RooFit.WeightVar("weight") )
                    tmpFullSetComb = RooDataHist("tmpDataSetComb", "tmpDataSetComb", RooArgSet(JpsiMass, sample), tmpFullSetCombTmp)

            else:
                tmpFullSetMatch = RooDataSet("tmpFullSetMatch", "tmpFullSetMatch", RooArgSet(JpsiMass, weight), RooFit.Import(tmpdatasetplusMatch), RooFit.WeightVar("weight"))
                tmpFullSetMatch2 = RooDataSet("tmpFullSetMatch2", "tmpFullSetMatch2", RooArgSet(JpsiMass, weight), RooFit.Import(tmpdatasetminusMatch), RooFit.WeightVar("weight"))
                tmpFullSetMatch.append(tmpFullSetMatch2)

                tmpFullSetFail = RooDataSet("tmpFullSetFail", "tmpFullSetFail", RooArgSet(JpsiMass, weight), RooFit.Import(tmpdatasetplusFail), RooFit.WeightVar("weight"))
                tmpFullSetFail2 = RooDataSet("tmpFullSetFail2", "tmpFullSetFail2", RooArgSet(JpsiMass, weight), RooFit.Import(tmpdatasetminusFail), RooFit.WeightVar("weight"))
                tmpFullSetFail.append(tmpFullSetFail2)

                tmpFullSet = RooDataSet("tmpFullSet", "tmpFullSet", RooArgSet(JpsiMass, weight), RooFit.Import(tmpdatasetplus), RooFit.WeightVar("weight"))
                tmpFullSet2 = RooDataSet("tmpFullSet2", "tmpFullSet2", RooArgSet(JpsiMass, weight), RooFit.Import(tmpdatasetminus), RooFit.WeightVar("weight"))
                tmpFullSet.append(tmpFullSet2)

                if simFit:
                    tmpFullSetComb = RooDataSet("tmpDataSetComb", "tmpDataSetComb", RooArgSet(JpsiMass, weight), RooFit.Index(sample), RooFit.Import("pass",tmpFullSetMatch), RooFit.Import("fail",tmpFullSetFail), RooFit.WeightVar("weight") )

            dataset_dict[var].append(tmpFullSet)
            dataset_dict_match[var].append(tmpFullSetMatch)
            dataset_dict_fail[var].append(tmpFullSetFail)
            if simFit:
                dataset_dict_comb[var].append(tmpFullSetComb)
                del tmpFullSetMatch, tmpFullSetFail, tmpFullSet

    if verbose:
        InfoMsg( "All 1D datasets created!" )

    for var2D in var_dict_2D.keys():
        dataset_dict[var2D]        = []
        dataset_dict_match[var2D]  = []
        dataset_dict_fail[var2D]   = []
        dataset_dict_comb[var2D]   = []

        if verbose:
            InfoMsgList( "Creating datasets for 2D variables",var2D )

        #loop over bins in 2D variables
        for bin_var1 in range((len(bin_dict[var_dict_2D[var2D][0]])-1)):
            for bin_var2 in range((len(bin_dict[var_dict_2D[var2D][1]])-1)):
                #tmpdatasetplus       = RooDataSet("plusDataSet"+var2D+str(bin_var1)+str(bin_var2),"plusDataSet"+var2D+str(bin_var1)+str(bin_var2), plusDataSet,
                tmpdatasetplus       = RooDataSet("plusDataSet"+var2D+str(bin_var1)+str(bin_var2),"plusDataSet"+var2D+str(bin_var1)+str(bin_var2), treePlus,
                                                  RooArgSet(JpsiMass, weight, matched, var_muplus_dict[var_dict_2D[var2D][0]], var_muplus_dict[var_dict_2D[var2D][1]]),
                                                  "muplus_"+var_dict_2D[var2D][0]+" > "+str(bin_dict[var_dict_2D[var2D][0]][bin_var1])+" && muplus_"+var_dict_2D[var2D][0]+" < "+str(bin_dict[var_dict_2D[var2D][0]][bin_var1+1])
                                                  +"&& muplus_"+var_dict_2D[var2D][1]+" > "+str(bin_dict[var_dict_2D[var2D][1]][bin_var2])+" && muplus_"+var_dict_2D[var2D][1]+" < "+str(bin_dict[var_dict_2D[var2D][1]][bin_var2+1]))

                #tmpdatasetminus      = RooDataSet("minusDataSet"+var2D+str(bin_var1)+str(bin_var2),"minusDataSet"+var2D+str(bin_var1)+str(bin_var2), minusDataSet,
                tmpdatasetminus      = RooDataSet("minusDataSet"+var2D+str(bin_var1)+str(bin_var2),"minusDataSet"+var2D+str(bin_var1)+str(bin_var2), treeMinus,
                                                  RooArgSet(JpsiMass, weight, matched, var_muminus_dict[var_dict_2D[var2D][0]], var_muminus_dict[var_dict_2D[var2D][1]]),
                                                  "muminus_"+var_dict_2D[var2D][0]+" > "+str(bin_dict[var_dict_2D[var2D][0]][bin_var1])+" && muminus_"+var_dict_2D[var2D][0]+" < "+str(bin_dict[var_dict_2D[var2D][0]][bin_var1+1])
                                                  +"&& muminus_"+var_dict_2D[var2D][1]+" > "+str(bin_dict[var_dict_2D[var2D][1]][bin_var2])+" && muminus_"+var_dict_2D[var2D][1]+" < "+str(bin_dict[var_dict_2D[var2D][1]][bin_var2+1]))

                #tmpdatasetplusMatch  = RooDataSet("plusDataSetAssoc"+var2D+str(bin_var1)+str(bin_var2),"plusDataSetAssoc"+var2D+str(bin_var1)+str(bin_var2), plusDataSet,
                tmpdatasetplusMatch  = RooDataSet("plusDataSetAssoc"+var2D+str(bin_var1)+str(bin_var2),"plusDataSetAssoc"+var2D+str(bin_var1)+str(bin_var2), treePlus,
                                                  RooArgSet(JpsiMass, weight, matched, var_muplus_dict[var_dict_2D[var2D][0]], var_muplus_dict[var_dict_2D[var2D][1]]),
                                                  Match+" && muplus_"+var_dict_2D[var2D][0]+" > "+str(bin_dict[var_dict_2D[var2D][0]][bin_var1])+" && muplus_"+var_dict_2D[var2D][0]+" < "+str(bin_dict[var_dict_2D[var2D][0]][bin_var1+1])
                                                  +"&& muplus_"+var_dict_2D[var2D][1]+" > "+str(bin_dict[var_dict_2D[var2D][1]][bin_var2])+" && muplus_"+var_dict_2D[var2D][1]+" < "+str(bin_dict[var_dict_2D[var2D][1]][bin_var2+1]))

                #tmpdatasetminusMatch = RooDataSet("minusDataSetAssoc"+var2D+str(bin_var1)+str(bin_var2),"minusDataSetAssoc"+var2D+str(bin_var1)+str(bin_var2), minusDataSet,
                tmpdatasetminusMatch = RooDataSet("minusDataSetAssoc"+var2D+str(bin_var1)+str(bin_var2),"minusDataSetAssoc"+var2D+str(bin_var1)+str(bin_var2), treeMinus,
                                                  RooArgSet(JpsiMass, weight, matched, var_muminus_dict[var_dict_2D[var2D][0]], var_muminus_dict[var_dict_2D[var2D][1]]),
                                                  Match+" && muminus_"+var_dict_2D[var2D][0]+" > "+str(bin_dict[var_dict_2D[var2D][0]][bin_var1])+" && muminus_"+var_dict_2D[var2D][0]+" < "+str(bin_dict[var_dict_2D[var2D][0]][bin_var1+1])
                                                  +"&& muminus_"+var_dict_2D[var2D][1]+" > "+str(bin_dict[var_dict_2D[var2D][1]][bin_var2])+" && muminus_"+var_dict_2D[var2D][1]+" < "+str(bin_dict[var_dict_2D[var2D][1]][bin_var2+1]))

                #tmpdatasetplusFail   = RooDataSet("plusDataSetFail"+var2D+str(bin_var1)+str(bin_var2),"plusDataSetFail"+var2D+str(bin_var1)+str(bin_var2), plusDataSet,
                tmpdatasetplusFail   = RooDataSet("plusDataSetFail"+var2D+str(bin_var1)+str(bin_var2),"plusDataSetFail"+var2D+str(bin_var1)+str(bin_var2), treePlus,
                                                  RooArgSet(JpsiMass, weight, matched, var_muplus_dict[var_dict_2D[var2D][0]], var_muplus_dict[var_dict_2D[var2D][1]]),
                                                  Fail+" && muplus_"+var_dict_2D[var2D][0]+" > "+str(bin_dict[var_dict_2D[var2D][0]][bin_var1])+" && muplus_"+var_dict_2D[var2D][0]+" < "+str(bin_dict[var_dict_2D[var2D][0]][bin_var1+1])
                                                  +"&& muplus_"+var_dict_2D[var2D][1]+" > "+str(bin_dict[var_dict_2D[var2D][1]][bin_var2])+" && muplus_"+var_dict_2D[var2D][1]+" < "+str(bin_dict[var_dict_2D[var2D][1]][bin_var2+1]))

                #tmpdatasetminusFail  = RooDataSet("minusDataSetFail"+var2D+str(bin_var1)+str(bin_var2),"minusDataSetFail"+var2D+str(bin_var1)+str(bin_var2), minusDataSet,
                tmpdatasetminusFail  = RooDataSet("minusDataSetFail"+var2D+str(bin_var1)+str(bin_var2),"minusDataSetFail"+var2D+str(bin_var1)+str(bin_var2), treeMinus,
                                                  RooArgSet(JpsiMass, weight, matched, var_muminus_dict[var_dict_2D[var2D][0]], var_muminus_dict[var_dict_2D[var2D][1]]),
                                                  Fail+" && muminus_"+var_dict_2D[var2D][0]+" > "+str(bin_dict[var_dict_2D[var2D][0]][bin_var1])+" && muminus_"+var_dict_2D[var2D][0]+" < "+str(bin_dict[var_dict_2D[var2D][0]][bin_var1+1])
                                                  +"&& muminus_"+var_dict_2D[var2D][1]+" > "+str(bin_dict[var_dict_2D[var2D][1]][bin_var2])+" && muminus_"+var_dict_2D[var2D][1]+" < "+str(bin_dict[var_dict_2D[var2D][1]][bin_var2+1]))

                if binnedFit:
                    tmpFullSetMatchTmp = RooDataSet("tmpFullSetMatchTmp", "tmpFullSetMatchTmp", RooArgSet(JpsiMass, weight), RooFit.Import(tmpdatasetplusMatch), RooFit.WeightVar("weight"))
                    tmpFullSetMatch2 = RooDataSet("tmpFullSetMatch2", "tmpFullSetMatch2", RooArgSet(JpsiMass, weight), RooFit.Import(tmpdatasetminusMatch), RooFit.WeightVar("weight"))
                    tmpFullSetMatchTmp.append(tmpFullSetMatch2)
                    tmpFullSetMatch = RooDataHist("tmpFullSetMatch","tmpFullSetMatch",RooArgSet(JpsiMass),tmpFullSetMatchTmp)

                    tmpFullSetFailTmp = RooDataSet("tmpFullSetFailTmp", "tmpFullSetFailTmp", RooArgSet(JpsiMass, weight), RooFit.Import(tmpdatasetplusFail), RooFit.WeightVar("weight"))
                    tmpFullSetFail2 = RooDataSet("tmpFullSetFail2", "tmpFullSetFail2", RooArgSet(JpsiMass, weight), RooFit.Import(tmpdatasetminusFail), RooFit.WeightVar("weight"))
                    tmpFullSetFailTmp.append(tmpFullSetFail2)
                    tmpFullSetFail = RooDataHist("tmpFullSetFail","tmpFullSetFail",RooArgSet(JpsiMass),tmpFullSetFailTmp)

                    tmpFullSetTmp = RooDataSet("tmpFullSetTmp", "tmpFullSetTmp", RooArgSet(JpsiMass, weight), RooFit.Import(tmpdatasetplus), RooFit.WeightVar("weight"))
                    tmpFullSet2 = RooDataSet("tmpFullSet2", "tmpFullSet2", RooArgSet(JpsiMass, weight), RooFit.Import(tmpdatasetminus), RooFit.WeightVar("weight"))
                    tmpFullSetTmp.append(tmpFullSet2)
                    tmpFullSet = RooDataHist("tmpFullSet","tmpFullSet",RooArgSet(JpsiMass),tmpFullSetTmp)

                    if simFit:
                        tmpFullSetCombTmp = RooDataSet("tmpDataSetCombTmp", "tmpDataSetCombTmp", RooArgSet(JpsiMass, weight), RooFit.Index(sample), RooFit.Import("pass",tmpFullSetMatchTmp), RooFit.Import("fail",tmpFullSetFailTmp), RooFit.WeightVar("weight") )
                        tmpFullSetComb = RooDataHist("tmpDataSetComb", "tmpDataSetComb", RooArgSet(JpsiMass, sample), tmpFullSetCombTmp)

                else:
                    tmpFullSetMatch = RooDataSet("tmpFullSetMatch", "tmpFullSetMatch", RooArgSet(JpsiMass, weight), RooFit.Import(tmpdatasetplusMatch), RooFit.WeightVar("weight"))
                    tmpFullSetMatch2 = RooDataSet("tmpFullSetMatch2", "tmpFullSetMatch2", RooArgSet(JpsiMass, weight), RooFit.Import(tmpdatasetminusMatch), RooFit.WeightVar("weight"))
                    tmpFullSetMatch.append(tmpFullSetMatch2)

                    tmpFullSetFail = RooDataSet("tmpFullSetFail", "tmpFullSetFail", RooArgSet(JpsiMass, weight), RooFit.Import(tmpdatasetplusFail), RooFit.WeightVar("weight"))
                    tmpFullSetFail2 = RooDataSet("tmpFullSetFail2", "tmpFullSetFail2", RooArgSet(JpsiMass, weight), RooFit.Import(tmpdatasetminusFail), RooFit.WeightVar("weight"))
                    tmpFullSetFail.append(tmpFullSetFail2)

                    tmpFullSet = RooDataSet("tmpFullSet", "tmpFullSet", RooArgSet(JpsiMass, weight), RooFit.Import(tmpdatasetplus), RooFit.WeightVar("weight"))
                    tmpFullSet2 = RooDataSet("tmpFullSet2", "tmpFullSet2", RooArgSet(JpsiMass, weight), RooFit.Import(tmpdatasetminus), RooFit.WeightVar("weight"))
                    tmpFullSet.append(tmpFullSet2)

                    if simFit: tmpFullSetComb = RooDataSet("tmpDataSetComb", "tmpDataSetComb", RooArgSet(JpsiMass, weight), RooFit.Index(sample), RooFit.Import("pass",tmpFullSetMatch), RooFit.Import("fail",tmpFullSetFail), RooFit.WeightVar("weight") )

                dataset_dict[var2D].append(tmpFullSet)
                dataset_dict_match[var2D].append(tmpFullSetMatch)
                dataset_dict_fail[var2D].append(tmpFullSetFail)
                if simFit:
                    dataset_dict_comb[var2D].append(tmpFullSetComb)
                    del tmpFullSetMatch, tmpFullSetFail, tmpFullSet

    if verbose: InfoMsg( "All 2D datasets created!" )

    InfoMsg( "Finished creating datasets!" )
    ###################################################
    #perform fits
    ###################################################

    #global fit, always done

    #create outputfile
    outfileFull = TFile(outputPath+"/trackEff_"+mode+"_Full_"+method+"_method.root","RECREATE")

    if not simFit:
        #fit to matched candidates
        signal_yield.setVal(0.2*fullDataSetMatch.sumEntries())
        background_yield.setVal(0.8*fullDataSetMatch.sumEntries())
        meanCB.setConstant(kFALSE)
        sigma.setConstant(kFALSE)
        sigma2.setConstant(kFALSE)
        sigma3.setConstant(kFALSE)
        fracCB.setConstant(kFALSE)
        fracCB2.setConstant(kFALSE)
        alpha.setConstant(kFALSE)
        n.setConstant(kFALSE)

        FullFrameMatch = JpsiMass.frame( RooFit.Title("m_{J/#psi} matched") )

        fullDataSetMatch.plotOn(FullFrameMatch)
        totalShape.fitTo(fullDataSetMatch, RooFit.NumCPU(n_cores), RooFit.Extended(kTRUE), RooFit.SumW2Error(kTRUE))
        totalShape.plotOn(FullFrameMatch)
        totalShape.paramOn(FullFrameMatch)

        #get the fit results
        m_sig_full = signal_yield.getVal()
        m_bkg_full = background_yield.getVal()
        match_tot = fullDataSetMatch.sumEntries()

        if plot_mass:
            cFullMatch = TCanvas("m_{J/#psi} matched")
            FullFrameMatch.Draw()
            cFullMatch.Write()

        #fit to failed candidates
        #signal_yield.setVal(0.02*fullDataSetFail.sumEntries())
        #background_yield.setVal(0.98*fullDataSetFail.sumEntries())
        signal_yield.setVal(0.2*fullDataSet.sumEntries())
        background_yield.setVal(0.8*fullDataSet.sumEntries())
        meanCB.setConstant(kTRUE)
        sigma.setConstant(kTRUE)
        sigma2.setConstant(kTRUE)
        sigma3.setConstant(kTRUE)
        fracCB.setConstant(kTRUE)
        fracCB2.setConstant(kTRUE)
        alpha.setConstant(kTRUE)
        n.setConstant(kTRUE)

        FullFrameFail = JpsiMass.frame( RooFit.Title("m_{J/#psi} failed") )

        #fullDataSetFail.plotOn(FullFrameFail)
        fullDataSet.plotOn(FullFrameFail)
        #totalShape.fitTo(fullDataSetFail, RooFit.Extended(kTRUE))
        totalShape.fitTo(fullDataSet, RooFit.NumCPU(n_cores), RooFit.Extended(kTRUE), RooFit.SumW2Error(kTRUE))
        totalShape.plotOn(FullFrameFail)
        totalShape.paramOn(FullFrameFail)

        #get the fit results
        f_sig_full = signal_yield.getVal()
        f_bkg_full = background_yield.getVal()
        #fail_tot = fullDataSetFail.sumEntries()
        fail_tot = fullDataSet.sumEntries()


        if plot_mass:
            cFullFail = TCanvas("m_{J/#psi} failed")
            FullFrameFail.Draw()
            cFullFail.Write()

        #n_bkg = m_bkg_full + f_bkg_full
        #n_tot = match_tot + fail_tot
        n_bkg = f_bkg_full
        n_tot = fail_tot
        eff, errup, errdown = calcEffAndError(n_tot, match_tot, n_bkg, m_bkg_full)
        #if data: eff, errup, errdown = calcEffAndError(n_tot, match_tot, n_bkg, m_bkg_full)
        #else : eff, errup, errdown = calcEffAndErrorNoBkg(f_sig_full, m_sig_full)

    if simFit:
        if mode == "Data":
            signal_yield.setVal(0.2*fullDataSet.sumEntries())
            background_yield.setVal(0.8*fullDataSet.sumEntries())
        else:
            signal_yield.setVal(0.99*fullDataSet.sumEntries())
            background_yield.setVal(0.01*fullDataSet.sumEntries())
        meanCB.setConstant(kFALSE)
        sigma.setConstant(kFALSE)
        sigma2.setConstant(kFALSE)
        sigma3.setConstant(kFALSE)
        fracCB.setConstant(kFALSE)
        fracCB2.setConstant(kFALSE)
        alpha.setConstant(kFALSE)
        n.setConstant(kFALSE)
        simPDF.fitTo(fullDataSetComb, RooFit.NumCPU(n_cores), RooFit.Extended(kTRUE), RooFit.SumW2Error(kTRUE) )

        #plot
        #pass
        plot_full_pass = JpsiMass.frame( RooFit.Title("m_{J/#psi} matched") )
        fullDataSetComb.plotOn(plot_full_pass, RooFit.Cut("sample==sample::pass"))
        simPDF.plotOn( plot_full_pass, RooFit.Slice(sample,"pass"), RooFit.ProjWData(RooArgSet(sample),fullDataSetComb) )
        if simpleFit: simPDF.plotOn( plot_full_pass, RooFit.Slice(sample,"pass"), RooFit.Components("myGaussSum"), RooFit.ProjWData(RooArgSet(sample),fullDataSetComb), RooFit.LineStyle(kDashed) )
        else: simPDF.plotOn( plot_full_pass, RooFit.Slice(sample,"pass"), RooFit.Components("myCBsumP"), RooFit.ProjWData(RooArgSet(sample),fullDataSetComb), RooFit.LineStyle(kDashed) )
        simPDF.paramOn(plot_full_pass)
        cSimPass = TCanvas("m_{J/#psi}, passed sim.")
        plot_full_pass.Draw()
        cSimPass.Write()
        #fail
        plot_full_fail = JpsiMass.frame( RooFit.Title("m_{J/#psi} failed") )
        fullDataSetComb.plotOn(plot_full_fail, RooFit.Cut("sample==sample::fail"))
        simPDF.plotOn( plot_full_fail, RooFit.Slice(sample,"fail"), RooFit.ProjWData(RooArgSet(sample),fullDataSetComb) )
        if simpleFit: simPDF.plotOn( plot_full_fail, RooFit.Slice(sample,"fail"), RooFit.Components("myGaussSumF"), RooFit.ProjWData(RooArgSet(sample),fullDataSetComb), RooFit.LineStyle(kDashed) )
        else: simPDF.plotOn( plot_full_fail, RooFit.Slice(sample,"fail"), RooFit.Components("myCBsumF"), RooFit.ProjWData(RooArgSet(sample),fullDataSetComb), RooFit.LineStyle(kDashed) )
        simPDF.paramOn(plot_full_fail)
        cSimFail = TCanvas("m_{J/#psi}, failed sim.")
        plot_full_fail.Draw()
        cSimFail.Write()

        InfoMsg( "Integrated efficiency: "  + str(efficiency_sig.getVal()) + " " + str(efficiency_sig.getErrorHi()) + " " + str(efficiency_sig.getErrorLo()))
        InfoMsg( "Sim. fit done!")
        eff = efficiency_sig.getVal()
        errup = efficiency_sig.getErrorHi()
        errdown = -efficiency_sig.getErrorLo()

    outfileFull.Write()
    outfileFull.Close()

    #####################################
    #fit in defined variables
    for var in var_list:
        InfoMsgList( "Starting fits in", var)
        InfoMsgList( " using bins ", len(bin_dict[var])-1)

        #create outputfile
        tmpoutfile = TFile(outputPath+"/trackEff_"+mode+"_"+var+"_"+method+"_method.root","RECREATE")
        tmpoutfile.cd()

        #lists for efficiencies and errors
        eff_list_tmp = []
        errU_list_tmp = []
        errD_list_tmp = []


        #loop over all bins
        for bins in range(len(bin_dict[var])-1):
            InfoMsgList( "Started fit in", var)
            InfoMsgList( " bin ", bins+1)

            #get datasets
            tmpDataSetMatch = dataset_dict_match[var][bins]
            tmpDataSetFail  = dataset_dict_fail[var][bins]
            if simFit: tmpDataSetComb  = dataset_dict_comb[var][bins]
            tmpDataSet      = dataset_dict[var][bins]

            if not simFit:
                #fit to matched candidates
                signal_yield.setVal(0.2*tmpDataSetMatch.sumEntries())
                background_yield.setVal(0.8*tmpDataSetMatch.sumEntries())
                #let shape parameters float again
                meanCB.setConstant(kFALSE)
                sigma.setConstant(kFALSE)
                sigma2.setConstant(kFALSE)
                sigma3.setConstant(kFALSE)
                fracCB.setConstant(kFALSE)
                fracCB2.setConstant(kFALSE)
                alpha.setConstant(kFALSE)
                n.setConstant(kFALSE)
                #reset shape parameters to original values
                sigma.setVal(30.)
                sigma2.setVal(70.)
                sigma2F.setVal(70.)
                fracCB.setVal(0.5)
                fracCBF.setVal(0.5)
                alpha.setVal(1.)
                n.setVal(1.)
                tau.setVal(-.0005)

                tmpFrameMatch = JpsiMass.frame( RooFit.Title("m_{J/#psi} matched, "+str(bin_dict[var][bins])+" < "+var+" < "+str(bin_dict[var][bins+1])) )

                tmpDataSetMatch.plotOn(tmpFrameMatch)
                totalShape.fitTo(tmpDataSetMatch, RooFit.NumCPU(n_cores), RooFit.Extended(kTRUE), RooFit.SumW2Error(kTRUE))
                totalShape.plotOn(tmpFrameMatch)
                totalShape.paramOn(tmpFrameMatch)

                #get the fit results
                m_sig_tmp = signal_yield.getVal()
                m_bkg_tmp = background_yield.getVal()
                match_tmp = tmpDataSetMatch.sumEntries()

                if plot_mass:
                    ctmpMatch = TCanvas("m_{J/#psi} matched, "+str(bin_dict[var][bins])+" < "+var+" < "+str(bin_dict[var][bins+1]))
                    tmpFrameMatch.Draw()
                    #tmpFrameMatch.Write()
                    ctmpMatch.Write()

                #fit to failed candidates
                signal_yield.setVal(0.2*tmpDataSet.sumEntries())
                #signal_yield.setVal(0.02*tmpDataSetFail.sumEntries())
                background_yield.setVal(0.8*tmpDataSet.sumEntries())
                #background_yield.setVal(0.98*tmpDataSetFail.sumEntries())
                meanCB.setConstant(kTRUE)
                sigma.setConstant(kTRUE)
                sigma2.setConstant(kTRUE)
                sigma3.setConstant(kTRUE)
                fracCB.setConstant(kTRUE)
                fracCB2.setConstant(kTRUE)
                alpha.setConstant(kTRUE)
                n.setConstant(kTRUE)

                tmpFrameFail = JpsiMass.frame( RooFit.Title("m_{J/#psi} full, "+str(bin_dict[var][bins])+" < "+var+" < "+str(bin_dict[var][bins+1])) )

                tmpDataSet.plotOn(tmpFrameFail)
                #tmpDataSetFail.plotOn(tmpFrameFail)
                totalShape.fitTo(tmpDataSet, RooFit.NumCPU(n_cores), RooFit.Extended(kTRUE))
                #totalShape.fitTo(tmpDataSetFail, RooFit.NumCPU(n_cores), RooFit.Extended(kTRUE), RooFit.SumW2Error(kTRUE))
                totalShape.plotOn(tmpFrameFail)
                totalShape.paramOn(tmpFrameFail)

                #get the fit results
                f_sig_tmp = signal_yield.getVal()
                f_bkg_tmp = background_yield.getVal()
                full_tmp = tmpDataSet.sumEntries()
                #full_tmp = tmpDataSetFail.sumEntries()

                if plot_mass:
                    ctmpFail = TCanvas("m_{J/#psi} full, "+str(bin_dict[var][bins])+" < "+var+" < "+str(bin_dict[var][bins+1]))
                    tmpFrameFail.Draw()
                    ctmpFail.Write()

                del tmpFrameMatch
                del tmpFrameFail
                del ctmpFail
                del ctmpMatch
                #calculate efficiency and errors
                eff_tmp, errup_tmp, errdown_tmp = calcEffAndError(full_tmp, match_tmp, f_bkg_tmp, m_bkg_tmp)
                #if data: eff_tmp, errup_tmp, errdown_tmp = calcEffAndError(full_tmp, match_tmp, f_bkg_tmp, m_bkg_tmp)
                #else : eff_tmp, errup_tmp, errdown_tmp = calcEffAndErrorNoBkg(f_sig_tmp+m_sig_tmp, m_sig_tmp)

            if simFit:

                #set parameters to reasonable/original values
                if mode == "Data":
                    signal_yield.setVal(0.2*tmpDataSet.sumEntries())
                    background_yield.setVal(0.8*tmpDataSet.sumEntries())
                else:
                    signal_yield.setVal(0.99*tmpDataSet.sumEntries())
                    background_yield.setVal(0.01*tmpDataSet.sumEntries())
                meanCB.setConstant(kFALSE)
                sigma.setConstant(kFALSE)
                sigma2.setConstant(kFALSE)
                sigma3.setConstant(kFALSE)
                fracCB.setConstant(kFALSE)
                fracCB2.setConstant(kFALSE)
                alpha.setConstant(kFALSE)
                n.setConstant(kFALSE)
                sigma.setVal(30.)
                sigma2.setVal(70.)
                sigma2F.setVal(70.)
                fracCB.setVal(0.5)
                fracCBF.setVal(0.5)
                alpha.setVal(1.)
                n.setVal(1.)
                tau.setVal(-.0005)
                tauF.setVal(-.0005)

                simPDF.fitTo(tmpDataSetComb, RooFit.NumCPU(n_cores), RooFit.Extended(kTRUE), RooFit.SumW2Error(kTRUE) )

                #plot
                #pass
                plot_tmp_pass = JpsiMass.frame( RooFit.Title("m_{J/#psi} matched, "+str(bin_dict[var][bins])+" < "+var+" < "+str(bin_dict[var][bins+1])) )
                tmpDataSetComb.plotOn(plot_tmp_pass, RooFit.Cut("sample==sample::pass"))
                simPDF.plotOn( plot_tmp_pass, RooFit.Slice(sample,"pass"), RooFit.ProjWData(RooArgSet(sample),tmpDataSetComb) )
                simPDF.plotOn( plot_tmp_pass, RooFit.Slice(sample,"pass"), RooFit.Components("myCBsumP"), RooFit.ProjWData(RooArgSet(sample),tmpDataSetComb), RooFit.LineStyle(kDashed) )
                simPDF.paramOn(plot_tmp_pass)
                cTmpPass = TCanvas("m_{J/#psi} matched, "+str(bin_dict[var][bins])+" < "+var+" < "+str(bin_dict[var][bins+1]))
                plot_tmp_pass.Draw()
                cTmpPass.Write()
                #fail
                plot_tmp_fail = JpsiMass.frame( RooFit.Title("m_{J/#psi} failed, "+str(bin_dict[var][bins])+" < "+var+" < "+str(bin_dict[var][bins+1])) )
                tmpDataSetComb.plotOn(plot_tmp_fail, RooFit.Cut("sample==sample::fail"))
                simPDF.plotOn( plot_tmp_fail, RooFit.Slice(sample,"fail"), RooFit.ProjWData(RooArgSet(sample),tmpDataSetComb) )
                simPDF.plotOn( plot_tmp_fail, RooFit.Slice(sample,"fail"), RooFit.Components("myCBsumF"), RooFit.ProjWData(RooArgSet(sample),tmpDataSetComb), RooFit.LineStyle(kDashed) )
                simPDF.paramOn(plot_tmp_fail)
                cTmpFail = TCanvas("m_{J/#psi} failed, "+str(bin_dict[var][bins])+" < "+var+" < "+str(bin_dict[var][bins+1]))
                plot_tmp_fail.Draw()
                cTmpFail.Write()

                InfoMsg( "Efficiency: "  + str(efficiency_sig.getVal()) + " " + str(efficiency_sig.getErrorHi()) + " " + str(efficiency_sig.getErrorLo()))
                InfoMsg( "Sim. fit done!")
                eff_tmp = efficiency_sig.getVal()
                errup_tmp = efficiency_sig.getErrorHi()
                errdown_tmp = -efficiency_sig.getErrorLo()

            del tmpDataSetMatch
            del tmpDataSetFail
            if simFit: del tmpDataSetComb
            del tmpDataSet

            #add to lists
            eff_list_tmp += [eff_tmp]
            errU_list_tmp += [errup_tmp]
            errD_list_tmp += [errdown_tmp]

            InfoMsg("Fit in " + var + " bin " +  str(bins+1) + " done!")

        #create x-axis coordinates for efficiency plot
        x_pD = [ (bin_dict[var][i+1] - bin_dict[var][i])/2. for i in range(len(bin_dict[var])-1) ]
        x_pU = x_pD
        x_p  = [ bin_dict[var][i]+x_pD[i] for i in range(len(bin_dict[var])-1) ]

        #create TGraph for efficiency
        graph_tmp = TGraphAsymmErrors(len(bin_dict[var])-1)
        for i in range(len(bin_dict[var])-1):
            graph_tmp.SetPoint(i, x_p[i], eff_list_tmp[i])
            graph_tmp.SetPointEXlow(i, x_pD[i])
            graph_tmp.SetPointEXhigh(i, x_pU[i])
            graph_tmp.SetPointEYlow(i, errD_list_tmp[i])
            graph_tmp.SetPointEYhigh(i, errU_list_tmp[i])
        graph_tmp.SetName("Efficiency "+var)
        graph_tmp.SetTitle("Efficiency "+var)

        if plot_eff:
            graph_tmp.Draw()
            graph_tmp.Write()

        tmpoutfile.Write()
        tmpoutfile.Close()
        del tmpoutfile

        InfoMsgList( "Fits done in", var)

    for var2D in var_dict_2D.keys():
        InfoMsg( '2D efficiencies requested in ' + var2D + '!')
        InfoMsg( "Starting fits in"  + str(var_dict_2D[var2D][0] ) + "and"
        + str(var_dict_2D[var2D][1]) +", using"
        + str( len(bin_dict[var_dict_2D[var2D][0]])-1) + "x"
        + str(len(bin_dict[var_dict_2D[var2D][1]])-1) + "bins.")

        #create outputfile
        tmpoutfile = TFile(outputPath+"/trackEff_"+mode+"_"+var2D+"_"+method+"_method.root","RECREATE")

        var1_coords    = np.asarray(bin_dict[var_dict_2D[var2D][0]])
        var2_coords  = np.asarray(bin_dict[var_dict_2D[var2D][1]])
        #create TH2D for efficiency
        eff_2d = TH2D("eff_"+var2D,"eff_"+var2D,len(bin_dict[var_dict_2D[var2D][0]])-1, var1_coords,len(bin_dict[var_dict_2D[var2D][1]])-1, var2_coords)


        #loop over all bins
        for bin_var1 in range(len(bin_dict[var_dict_2D[var2D][0]])-1):
            for bin_var2 in range(len(bin_dict[var_dict_2D[var2D][1]])-1):
                InfoMsg( "Started fit in " + str(var_dict_2D[var2D][0])+ " bin "
                + str(bin_var1+1) + "," + str(var_dict_2D[var2D][1]) + " bin " + str(bin_var2+1))

                bins = bin_var1*(len(bin_dict[var_dict_2D[var2D][1]])-1) + bin_var2
                #get datasets
                tmpDataSetMatch = dataset_dict_match[var2D][bins]
                tmpDataSetFail  = dataset_dict_fail[var2D][bins]
                if simFit: tmpDataSetComb  = dataset_dict_comb[var2D][bins]
                tmpDataSet      = dataset_dict[var2D][bins]

                if not simFit:
                    #fit to matched candidates
                    signal_yield.setVal(0.2*tmpDataSetMatch.sumEntries())
                    background_yield.setVal(0.8*tmpDataSetMatch.sumEntries())
                    #let shape parameters float
                    meanCB.setConstant(kFALSE)
                    sigma.setConstant(kFALSE)
                    sigma2.setConstant(kFALSE)
                    sigma3.setConstant(kFALSE)
                    fracCB.setConstant(kFALSE)
                    fracCB2.setConstant(kFALSE)
                    alpha.setConstant(kFALSE)
                    n.setConstant(kFALSE)
                    #reset shape parameters
                    sigma.setVal(30.)
                    sigma2.setVal(70.)
                    fracCB.setVal(0.5)
                    alpha.setVal(1.)
                    n.setVal(1.)
                    tau.setVal(-.0005)

                    tmpFrameMatch = JpsiMass.frame( RooFit.Title("m_{J/#psi} matched, "+var_dict_2D[var2D][0]+" bin "+ str(bin_var1+1)+ ", "+var_dict_2D[var2D][1]+" bin "+ str(bin_var2+1) ) )

                    tmpDataSetMatch.plotOn(tmpFrameMatch)
                    totalShape.fitTo(tmpDataSetMatch, RooFit.NumCPU(n_cores), RooFit.Extended(kTRUE), RooFit.SumW2Error(kTRUE))
                    totalShape.plotOn(tmpFrameMatch)
                    totalShape.paramOn(tmpFrameMatch)

                    #get the fit results
                    m_sig_tmp = signal_yield.getVal()
                    m_bkg_tmp = background_yield.getVal()
                    match_tmp = tmpDataSetMatch.sumEntries()

                    if plot_mass:
                        ctmpMatch = TCanvas("m_{J/#psi} matched, "+var_dict_2D[var2D][0]+" bin "+ str(bin_var1+1)+ ", "+var_dict_2D[var2D][1]+" bin "+ str(bin_var2+1) )
                        tmpFrameMatch.Draw()
                        #tmpFrameMatch.Write()
                        ctmpMatch.Write()

                    #fit to failed candidates
                    signal_yield.setVal(0.2*tmpDataSet.sumEntries())
                    background_yield.setVal(0.8*tmpDataSet.sumEntries())
                    #signal_yield.setVal(0.02*tmpDataSetFail.sumEntries())
                    #background_yield.setVal(0.98*tmpDataSetFail.sumEntries())
                    meanCB.setConstant(kTRUE)
                    sigma.setConstant(kTRUE)
                    sigma2.setConstant(kTRUE)
                    sigma3.setConstant(kTRUE)
                    fracCB.setConstant(kTRUE)
                    fracCB2.setConstant(kTRUE)
                    alpha.setConstant(kTRUE)
                    n.setConstant(kTRUE)

                    tmpFrameFail = JpsiMass.frame( RooFit.Title("m_{J/#psi} full, "+var_dict_2D[var2D][0]+" bin "+ str(bin_var1+1)+ ", "+var_dict_2D[var2D][1]+" bin "+ str(bin_var2+1) ))

                    tmpDataSet.plotOn(tmpFrameFail)
                    #tmpDataSetFail.plotOn(tmpFrameFail)
                    totalShape.fitTo(tmpDataSet, RooFit.NumCPU(n_cores), RooFit.Extended(kTRUE), RooFit.SumW2Error(kTRUE))
                    #totalShape.fitTo(tmpDataSetFail, RooFit.NumCPU(n_cores), RooFit.Extended(kTRUE), RooFit.SumW2Error(kTRUE))
                    totalShape.plotOn(tmpFrameFail)
                    totalShape.paramOn(tmpFrameFail)

                    #get the fit results
                    f_sig_tmp = signal_yield.getVal()
                    f_bkg_tmp = background_yield.getVal()
                    full_tmp = tmpDataSet.sumEntries()

                    if plot_mass:
                        ctmpFail = TCanvas("m_{J/#psi} full, "+var_dict_2D[var2D][0]+" bin "+ str(bin_var1+1)+ ", "+var_dict_2D[var2D][1]+" bin "+ str(bin_var2+1) )
                        tmpFrameFail.Draw()
                        ctmpFail.Write()

                    del tmpFrameMatch
                    del tmpFrameFail

                    #calculate efficiency and errors
                    eff_tmp, errup_tmp, errdown_tmp = calcEffAndError(full_tmp, match_tmp, f_bkg_tmp, m_bkg_tmp)
                    #if data: eff_tmp, errup_tmp, errdown_tmp = calcEffAndError(full_tmp, match_tmp, f_bkg_tmp, m_bkg_tmp)
                    #else : eff_tmp, errup_tmp, errdown_tmp = calcEffAndErrorNoBkg(f_sig_tmp+m_sig_tmp, m_sig_tmp)


                if simFit:

                    #set parameters to reasonable/original values
                    if mode == "Data":
                        signal_yield.setVal(0.2*tmpDataSet.sumEntries())
                        background_yield.setVal(0.8*tmpDataSet.sumEntries())
                    else:
                        signal_yield.setVal(0.99*tmpDataSet.sumEntries())
                        background_yield.setVal(0.01*tmpDataSet.sumEntries())
                    meanCB.setConstant(kFALSE)
                    sigma.setConstant(kFALSE)
                    sigma2.setConstant(kFALSE)
                    sigma3.setConstant(kFALSE)
                    fracCB.setConstant(kFALSE)
                    fracCB2.setConstant(kFALSE)
                    alpha.setConstant(kFALSE)
                    n.setConstant(kFALSE)
                    sigma.setVal(30.)
                    sigma2.setVal(70.)
                    fracCB.setVal(0.5)
                    alpha.setVal(1.)
                    n.setVal(1.)
                    tau.setVal(-.0005)
                    tauF.setVal(-.0005)

                    simPDF.fitTo(tmpDataSetComb, RooFit.NumCPU(n_cores), RooFit.Extended(kTRUE), RooFit.SumW2Error(kTRUE) )

                    #plot
                    #pass
                    plot_tmp_pass = JpsiMass.frame( RooFit.Title("m_{J/#psi} matched, "+var_dict_2D[var2D][0]+" bin "+ str(bin_var1+1)+ ", "+var_dict_2D[var2D][1]+" bin "+ str(bin_var2+1) ) )
                    tmpDataSetComb.plotOn(plot_tmp_pass, RooFit.Cut("sample==sample::pass"))
                    simPDF.plotOn( plot_tmp_pass, RooFit.Slice(sample,"pass"), RooFit.ProjWData(RooArgSet(sample),tmpDataSetComb) )
                    simPDF.plotOn( plot_tmp_pass, RooFit.Slice(sample,"pass"), RooFit.Components("myCBsumP"), RooFit.ProjWData(RooArgSet(sample),tmpDataSetComb), RooFit.LineStyle(kDashed) )
                    simPDF.paramOn(plot_tmp_pass)
                    cTmpPass = TCanvas("m_{J/#psi} matched, "+var_dict_2D[var2D][0]+" bin "+ str(bin_var1+1)+ ", "+var_dict_2D[var2D][1]+" bin "+ str(bin_var2+1))
                    plot_tmp_pass.Draw()
                    cTmpPass.Write()
                    #fail
                    plot_tmp_fail = JpsiMass.frame( RooFit.Title("m_{J/#psi} failed, "+var_dict_2D[var2D][0]+" bin "+ str(bin_var1+1)+ ", "+var_dict_2D[var2D][1]+" bin "+ str(bin_var2+1) ) )
                    tmpDataSetComb.plotOn(plot_tmp_fail, RooFit.Cut("sample==sample::fail"))
                    simPDF.plotOn( plot_tmp_fail, RooFit.Slice(sample,"fail"), RooFit.ProjWData(RooArgSet(sample),tmpDataSetComb) )
                    simPDF.plotOn( plot_tmp_fail, RooFit.Slice(sample,"fail"), RooFit.Components("myCBsumF"), RooFit.ProjWData(RooArgSet(sample),tmpDataSetComb), RooFit.LineStyle(kDashed) )
                    simPDF.paramOn(plot_tmp_fail)
                    cTmpFail = TCanvas("m_{J/#psi} failed, "+var_dict_2D[var2D][0]+" bin "+ str(bin_var1+1)+ ", "+var_dict_2D[var2D][1]+" bin "+ str(bin_var2+1))
                    plot_tmp_fail.Draw()
                    cTmpFail.Write()
                    InfoMsg( "Efficiency: "  + str(efficiency_sig.getVal()) + " " + str(efficiency_sig.getErrorHi()) + " " + str(efficiency_sig.getErrorLo()))
                    InfoMsg( "Sim. fit done!")

                    eff_tmp = efficiency_sig.getVal()
                    errup_tmp = efficiency_sig.getErrorHi()
                    errdown_tmp = -efficiency_sig.getErrorLo()

                del tmpDataSetMatch
                del tmpDataSetFail
                if simFit: del tmpDataSetComb
                del tmpDataSet

                #calculate average of up/down errors, as TH2D does not support asymmetric errors
                err_avg = 0.5*(errup_tmp + errdown_tmp)

                #fill histogram
                eff_2d.SetBinContent(bin_var1+1,bin_var2+1, eff_tmp)
                eff_2d.SetBinError(bin_var1+1,bin_var2+1, err_avg)

                InfoMsg("Fit in " + str(var_dict_2D[var2D][0]) + " bin " + str(bin_var1+1) + "," + str(var_dict_2D[var2D][1]) + " bin " + str(bin_var2+1) +" done!")

        eff_2d.SetName("Efficiency "+var2D)
        eff_2d.SetTitle("Efficiency "+var2D)

        if plot_eff:
            eff_2d.Draw()
            eff_2d.Write()

        tmpoutfile.Write()
        tmpoutfile.Close()
        del tmpoutfile

        InfoMsg( "2D Fits in " + str( var_dict_2D[var2D][0]) + " and " + str(var_dict_2D[var2D][1]) + " done!")

    InfoMsg( "All fits done!")

    #if verbose:
    #    sys.stdout = sys.__stdout__
    #    log_file.close()
