from ROOT import *
from math import *
import os
import sys
import time
from Urania import *
recoverTree()
AccessPackage("Bs2MuMu")
from smartpyROOT import *

from PDF_2013_Asym_toys import *
from parameters import KpiBins4 as Kpibins
from Lb_yields import Lb_yield_PosNeg as Lb_yield, Lb_yield_PosNeg_err as Lb_yieldErr
from parameters_toys import mass_params as massParams
from parameters_toys import yields_toys_bins_Poissonized as yieldsBinsPoisson
from parameters_toys import yields_toys_bins_True as yieldsBinsTrue

#from mass_params import paramsMC as Lb_massPar
from mass_params import paramsDATA as massParamsDATA, paramsMC as massParamsMC, paramsMC as Lb_massPar

gROOT.ProcessLine(".L lhcbStyle.C")

debug = True

gRandom = TRandom3()
seed = 0 # see http://root.cern.ch/root/html/TRandom3.html#TRandom3:SetSeed
gRandom.SetSeed(seed)

if not seed == 0:
    for i in range(0,20):
        print "fitMassAddsWeights_OneExp.py::WARNING:: Random seed is constant !!!!"

# -----------------------------------------
# Declare the structure to create the TTree
gROOT.ProcessLine( "struct MyStructF{ Float_t afloat; };" )
gROOT.ProcessLine( "struct MyStructI{ Int_t anInt; };" )
    

# ------ Input args ----------
tupleSource   = str(sys.argv[1]) # string to tag the source of ntuples: 'Toys' or 'Data' 
_USE_GRID_    = int(sys.argv[2]) # bool to tag if we are on the grid or not (files location)
include_Lb    = str(sys.argv[3]) # str to tag Lb bkg is included: 'Lb' or 'noLb'
inPutTag      = str(sys.argv[4]) # string to tag the name of the InPutFile
outPutTag     = str(sys.argv[5]) # string to tag the name of the OutPutFile

if tupleSource != 'Data':
    iexp          = int(sys.argv[6]) # int to tag the nbr of the experiment
    nonZeroACPs   = int(sys.argv[7]) # int to flag if we generate the ACPs with non zero values
    ACPset        = "set_noCP"
    if nonZeroACPs:
        ACPset    = str(sys.argv[8]) # string to tag the set of ACPs

nCPUs = 1
if not _USE_GRID_:
    nCPUs = 8

ExpTag = ""
TreeName = "DecayTree"
if tupleSource != 'Data':        
    ExpTag = "_Exp%s"%iexp
    TreeName = "genTree"

l_years = ["2011","2012"]
l_signs = ["neg","pos"]
l_bins = []
for ibin in range(len(Kpibins)-1):
    l_bins.append(ibin)

l_speciesName = ["Bs","Bd","Combi"]
if include_Lb=='Lb':
    l_speciesName.append("Lb2JpsipK")
    l_speciesName.append("Lb2JpsipPi")

# ----------------------------------------------------------------------------------------------------------------------
# ----------------------------------------------------------------------------------------------------------------------
# ------ Fit dataset, draw fit projection, compute sWeights, and store fit results with pulls and errors  --------------
# ----------------------------------------------------------------------------------------------------------------------
# ----------------------------------------------------------------------------------------------------------------------
def runFit(year="2011",sign="pos",ibin=-1,nbins = 45):
    
        # -- Bs and Bd
        massB = SignalMassIpatia("signal", year, ibin, sign, True)
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
        bkgmodel.kbkg.setVal(massParams["Combi"][year][sign][ibin]["k"])

        # -- Lb peaking bkgs
        LbpKmodel = LambdaDecay("Lb2JpsipK")
        Lbppimodel = LambdaDecay("Lb2JpsipPi")
        
        for key in massParams["Lb2JpsipK"][year][sign][ibin].keys():
            LbpKmodel.set(key,massParams["Lb2JpsipK"][year][sign][ibin][key])

        for key in massParams["Lb2JpsipPi"][year][sign][ibin].keys():
            Lbppimodel.set(key,massParams["Lb2JpsipPi"][year][sign][ibin][key])
                
        LbKconst_Mean = 0
        Lbpiconst_Mean = 0
        LbKconst_Sigma = 0
        Lbpiconst_Sigma = 0
        for year in l_years:
            for sign in l_signs:
                LbKconst_Mean += (Lb_yield["LbK"][year][sign][ibin])
                Lbpiconst_Mean += (Lb_yield["Lbpi"][year][sign][ibin])
                LbKconst_Sigma += (Lb_yieldErr["LbK"][year][sign][ibin]*Lb_yieldErr["LbK"][year][sign][ibin])
                Lbpiconst_Sigma += (Lb_yieldErr["Lbpi"][year][sign][ibin]*Lb_yieldErr["Lbpi"][year][sign][ibin])

        LbKconst_Sigma = sqrt(LbKconst_Sigma)
        Lbpiconst_Sigma = sqrt(Lbpiconst_Sigma)
        
        nEvts = {}
        nEvtsTrue = {}
        if tupleSource == 'Data':    
            dataSet = Datasets[tupleSource][ibin]
            # -- Set yields and models 
            for name in l_speciesName:
                nEvts[name] = yields[tupleSource][name]
        else:   
            dataSet = Datasets[tupleSource][ibin]
            # -- Random gauss mu for the Gaussian constraints on Lb yields in the Toys
            LbKconst_Mean = gRandom.Gaus(LbKconst_Mean,LbKconst_Sigma)
            Lbpiconst_Mean = gRandom.Gaus(Lbpiconst_Mean,Lbpiconst_Sigma)
            # -- Set yields and models 
            for name in l_speciesName:
                nEvts[name] = yields[tupleSource][name][ibin]
                nEvtsTrue[name] = 0 
                for year in l_years:
                    for sign in l_signs:
                        nEvtsTrue[name] += yieldsBinsTrue[ACPset][name][year][sign][ibin]

        # -- Parameters 
        nd = RooRealVar("nBd","nBd",        nEvts["Bd"],        0., 10*nEvts["Bd"])
        ns = RooRealVar("nBs","nBs",        nEvts["Bs"],        0., 100*nEvts["Bs"])
        nbkg = RooRealVar("nCombi","nCombi",nEvts["Combi"],     0., 100*nEvts["Combi"])

        
        if(include_Lb=='Lb'):
            if tupleSource != "Data":
                nLbpK = RooRealVar("nLbpK","nLbpK", nEvts["Lb2JpsipK"], 0., 10*nEvts["Lb2JpsipK"])
                nLbpi = RooRealVar("nLbpi","nLbpi", nEvts["Lb2JpsipPi"],0., 10*nEvts["Lb2JpsipPi"])
            else:
                nLbpK = RooRealVar("nLbpK","nLbpK", LbKconst_Mean, 0., 10*nEvts["Lb2JpsipK"])
                nLbpi = RooRealVar("nLbpi","nLbpi", Lbpiconst_Mean,0., 10*nEvts["Lb2JpsipPi"])
                 
            # -- Gaussian constraints on Lb yields
            LbKconst=RooGaussian("LbKconst","LbKconst",nLbpK,RooFit.RooConst(LbKconst_Mean),RooFit.RooConst(LbKconst_Sigma))
            Lbpiconst=RooGaussian("Lbpiconst","Lbpiconst",nLbpi,RooFit.RooConst(Lbpiconst_Mean),RooFit.RooConst(Lbpiconst_Sigma))


        if(include_Lb=='Lb'):
            fit_model = RooAddPdf("model","model",RooArgList(massB.sigBs,massB.sigBd,bkgmodel.massbkg,
                                                             LbpKmodel.mass_model,Lbppimodel.mass_model),
                                  RooArgList(ns,nd,nbkg,nLbpK,nLbpi))
        else: 
            fit_model = RooAddPdf("model","model",RooArgList(massB.sigBs,massB.sigBd,bkgmodel.massbkg),RooArgList(ns,nd,nbkg))

        argList = fit_model.getParameters(dataSet)
        argList.setRealValue("sigmaBdsignal", massParamsDATA["Bd"][ibin]["ipa_s"])
        argList.setRealValue("meanBdsignal", massParamsDATA["Bd"][ibin]["ipa_m"])
        argList.setRealValue("ipatia_lambdaBd", massParamsDATA["Bd"][ibin]["l"])
        argList.setRealValue("a1_cbBdsignal", massParamsDATA["Bd"][ibin]["a"])
        argList.setRealValue("a2_cbBdsignal", massParamsDATA["Bd"][ibin]["a2"])
        argList.setRealValue("ncb1Bdsignal", massParamsDATA["Bd"][ibin]["n"])
        argList.setRealValue("ncb2Bdsignal", massParamsDATA["Bd"][ibin]["n2"])

        # -- Bs Ipatia params
        argList.setRealValue("sigmaBssignal", massParamsDATA["Bs"][ibin]["ipa_s"])
        argList.setRealValue("meanBssignal", massParamsDATA["Bs"][ibin]["ipa_m"])
        argList.setRealValue("ipatia_lambdaBs", massParamsDATA["Bs"][ibin]["l"])
        argList.setRealValue("a1_cbBssignal", massParamsDATA["Bs"][ibin]["a"])
        argList.setRealValue("a2_cbBssignal", massParamsDATA["Bs"][ibin]["a2"])
        argList.setRealValue("ncb1Bssignal", massParamsDATA["Bs"][ibin]["n"])
        argList.setRealValue("ncb2Bssignal", massParamsDATA["Bs"][ibin]["n2"])

        if(include_Lb=='Lb'):
            # -- Lb Amoroso params
            argList.setRealValue("Lb2JpsipKtheta", massParamsMC["Lb2JpsipK"][ibin]["theta"])
            argList.setRealValue("Lb2JpsipKalpha", massParamsMC["Lb2JpsipK"][ibin]["alpha"])
            argList.setRealValue("Lb2JpsipKmean", massParamsMC["Lb2JpsipK"][ibin]["mean"])
            argList.setRealValue("Lb2JpsipKbeta", massParamsMC["Lb2JpsipK"][ibin]["beta"])

            argList.setRealValue("Lb2Jpsippitheta", massParamsMC["Lb2JpsipPi"][ibin]["theta"])
            argList.setRealValue("Lb2Jpsippialpha", massParamsMC["Lb2JpsipPi"][ibin]["alpha"])
            argList.setRealValue("Lb2Jpsippimean", massParamsMC["Lb2JpsipPi"][ibin]["mean"])
            argList.setRealValue("Lb2Jpsippibeta", massParamsMC["Lb2JpsipPi"][ibin]["beta"])

            # -- Lb yields
            if not tupleSource == "Data":
                argList.setRealValue("nLbpK", LbKconst_Mean)
                argList.setRealValue("nLbpi", Lbpiconst_Mean)
            else:
                argList.setRealValue("nLbpK", LbKconst_Mean)
                argList.setRealValue("nLbpi", Lbpiconst_Mean)

        if debug:
            argSet = fit_model.getParameters(dataSet)
            argSet.Print()
            iter = argSet.iterator()
            for iarg in range(0, argSet.getSize()):
                arg = iter.Next()
                parVal = argSet.getRealValue(arg.GetName())
                print "Parameter :",arg.GetName()," with initial value :",parVal

        # ------ Fit to data ----------
        if(include_Lb=='Lb'):
            fitResult = fit_model.fitTo(dataSet,RooFit.Save(),RooFit.NumCPU(nCPUs),RooFit.Minos(False),
                                        RooFit.SumW2Error(kTRUE),RooFit.ExternalConstraints(RooArgSet(LbKconst,Lbpiconst)))
        else:
            fitResult = fit_model.fitTo(dataSet,RooFit.Save(),RooFit.NumCPU(nCPus),RooFit.Minos(False),RooFit.SumW2Error(kFALSE))


        # ----------------------------------------------------------------------------------------------------------------------
        # ----------------------------------------------------------------------------------------------------------------------
        # ------ Fit projection ----------
        # ----------------------------------------------------------------------------------------------------------------------
        # ----------------------------------------------------------------------------------------------------------------------
            
        cv = TCanvas()
        cv.SetFillColor(0)

        fr = Mass.frame()
        fr.SetName("B0_MM")
        dataSet.plotOn(fr,RooFit.Binning(nbins))
        fit_model.plotOn(fr, RooFit.LineColor(kBlue))
        
        renorm = 1./dataSet.tree().GetEntries()
        massB.sigBd.plotOn(fr,RooFit.LineColor(kGreen), RooFit.LineStyle(2), RooFit.Normalization(nd.getVal()*renorm))
        massB.sigBs.plotOn(fr, RooFit.LineColor(kRed), RooFit.LineStyle(3), RooFit.Normalization(ns.getVal()*renorm))
        bkgmodel.massbkg.plotOn(fr, RooFit.LineColor(kBlack), RooFit.LineStyle(7), RooFit.Normalization(nbkg.getVal()*renorm))
        if(include_Lb=='Lb'):
            LbpKmodel.mass_model.plotOn(fr, RooFit.LineColor(kMagenta), RooFit.LineStyle(4), RooFit.Normalization(nLbpK.getVal()*renorm))
            Lbppimodel.mass_model.plotOn(fr, RooFit.LineColor(kCyan), RooFit.LineStyle(6), RooFit.Normalization(nLbpi.getVal()*renorm))
        
        leg = TLegend(0.65,0.28,0.92,0.63)
        leg.SetName("legend")
        leg.SetFillColor(kWhite)
        leg.SetLineColor(kWhite)
        leg.AddEntry(fr.findObject("h_%s"%(dataSet.GetName())),"Data", "PLE")
        leg.AddEntry(fr.findObject("%s_Norm[%s]"%(fit_model.GetName(),Mass.GetName())),"Total PDF","L") 
        leg.AddEntry(fr.findObject("%s_Norm[%s]"%(massB.sigBd.GetName(),Mass.GetName())),"B^{0}_{d} signal", "L")
        leg.AddEntry(fr.findObject("%s_Norm[%s]"%(massB.sigBs.GetName(),Mass.GetName())),"B^{0}_{s} signal", "L")
        leg.AddEntry(fr.findObject("%s_Norm[%s]"%(bkgmodel.massbkg.GetName(),Mass.GetName())),"Combinatorial bkg", "L")
        leg.AddEntry(fr.findObject("%s_Norm[%s]"%(LbpKmodel.mass_model.GetName(),Mass.GetName())),"#Lambda_{b} #rightarrow J/#psi pK", "L")
        leg.AddEntry(fr.findObject("%s_Norm[%s]"%(Lbppimodel.mass_model.GetName(),Mass.GetName())),"#Lambda_{b} #rightarrow J/#psi p#pi", "L")
        
        fr.addObject(leg)
        
        prelim = printMyLHCb("R", "Prelim")
        prelim.SetName("textBox")
        fr.addObject(prelim)
        

        fr.SetMinimum(0)
        fr.SetMaximum(500)
        fr.SetTitle("")
        fr.SetXTitle("M(J/#psi K#pi) [MeV/c^{2}]")
        binWidth = round(10*float((Mass.getMax() - Mass.getMin())/float(nbins)))/10
        fr.SetYTitle("Candidates / (%s MeV/c^{2})"%binWidth)

        fr.Draw()

        if _USE_GRID_:
            if tupleSource == "Data":
                cv.SaveAs("massPlot_%s_%s_%s_AllYearsSigns_%s_%s.root"%(tupleSource,inPutTag,outPutTag,
                                                                        Kpibins[ibin],Kpibins[ibin+1]))
                cv.SaveAs("massPlot_%s_%s_%s_AllYearsSigns_%s_%s.pdf"%(tupleSource,inPutTag,outPutTag,
                                                                       Kpibins[ibin],Kpibins[ibin+1]))
                fr.SaveAs("massPlot_%s_%s_%s_AllYearsSigns_%s_%s.root"%(tupleSource,inPutTag,outPutTag,
                                                                        Kpibins[ibin],Kpibins[ibin+1]))
            else:
                cv.SaveAs("massPlot_%s_%s_%s%s_AllYearsSigns_%s_%s.root"%(tupleSource,inPutTag,outPutTag,ExpTag,
                                                                          Kpibins[ibin],Kpibins[ibin+1]))
                cv.SaveAs("massPlot_%s_%s_%s%s_AllYearsSigns_%s_%s.pdf"%(tupleSource,inPutTag,outPutTag,ExpTag,
                                                                         Kpibins[ibin],Kpibins[ibin+1]))
                fr.SaveAs("massPlot_%s_%s_%s%s_AllYearsSigns_%s_%s.root"%(tupleSource,inPutTag,outPutTag,ExpTag,
                                                                          Kpibins[ibin],Kpibins[ibin+1]))
        else:
            if tupleSource == "Data":
                cv.SaveAs("%s/massPlot_%s_%s_%s_AllYearsSigns_%s_%s.root"%(fitResDir,
                                                                           tupleSource,inPutTag,outPutTag,
                                                                           Kpibins[ibin],Kpibins[ibin+1]))
                cv.SaveAs("%s/massPlot_%s_%s_%s_AllYearsSigns_%s_%s.pdf"%(fitResDir,
                                                                          tupleSource,inPutTag,outPutTag,
                                                                          Kpibins[ibin],Kpibins[ibin+1]))
                fr.SaveAs("%s/massPlot_%s_%s_%s_AllYearsSigns_%s_%s.root"%(fitResDir,
                                                                           tupleSource,inPutTag,outPutTag,
                                                                           Kpibins[ibin],Kpibins[ibin+1]))
            else:
                cv.SaveAs("%s/massPlot_%s_%s_%s%s_AllYearsSigns_%s_%s.root"%(fitResDir,
                                                                             tupleSource,inPutTag,outPutTag,ExpTag,
                                                                             Kpibins[ibin],Kpibins[ibin+1]))
                cv.SaveAs("%s/massPlot_%s_%s_%s%s_AllYearsSigns_%s_%s.pdf"%(fitResDir,
                                                                            tupleSource,inPutTag,outPutTag,ExpTag,
                                                                            Kpibins[ibin],Kpibins[ibin+1]))
                fr.SaveAs("%s/massPlot_%s_%s_%s%s_AllYearsSigns_%s_%s.root"%(fitResDir,
                                                                             tupleSource,inPutTag,outPutTag,ExpTag,
                                                                             Kpibins[ibin],Kpibins[ibin+1]))


        # ----------------------------------------------------------------------------------------------------------------------
        # ----------------------------------------------------------------------------------------------------------------------
        # ------ Compute SWeights ----------
        # ----------------------------------------------------------------------------------------------------------------------
        # ----------------------------------------------------------------------------------------------------------------------
        if(include_Lb=='Lb'): prlist = [nd,ns,nbkg,nLbpK,nLbpi]
        else:                 prlist = [nd,ns,nbkg]

        inputFile = TFile("%s.root"%(inputFile_name_loc))
        inputTree = inputFile.Get(TreeName)

        if _USE_GRID_:
            thisOutputFileName = "%s_AllYearsSigns_%s_%s_AddedsWeights.root"%(outputFile_name,Kpibins[ibin],Kpibins[ibin+1])
        else:
            thisOutputFileName = "%s_AllYearsSigns_%s_%s_AddedsWeights.root"%(outputFile_name_loc,Kpibins[ibin],Kpibins[ibin+1])
        outputFile = TFile(thisOutputFileName,"recreate")
        selectionCut = ""
        if tupleSource != 'Data':
            selectionCut += "KpiBin==%s && iExp==%s"%(ibin,iexp)
        else:
            selectionCut += "Kst_892_0_MM > %s && Kst_892_0_MM < %s"%(Kpibins[ibin],Kpibins[ibin+1])
            
        outputTree = inputTree.CopyTree(selectionCut)
        print"",outputTree.GetEntries()
        
        if(include_Lb=='Lb'): sData = RooStats.SPlot("sData","An SPlot",dataSet,fit_model,RooArgList(ns,nd,nbkg,nLbpK,nLbpi))
        else:                 sData = RooStats.SPlot("sData","An SPlot",dataSet,fit_model,RooArgList(ns,nd,nbkg))

        sWeightList = []
        CorrsWeightList = []
        sWeightBranchs = []
        CorrsWeightBranchs = []
        for iSpecie in range(len(prlist)):
            sWeightList.append( MyStructF() )
            CorrsWeightList.append( MyStructF() )
            if tupleSource == "Data":
                iSpecieName = prlist[iSpecie].GetName()
            else:
                iSpecieName = prlist[iSpecie].GetName()[1:]
            sWeightBranchs.append(outputTree.Branch( "sWeights_"+iSpecieName, AddressOf(sWeightList[iSpecie],'afloat'), 
                                                     "sWeights_"+iSpecieName+"/F" ))
            CorrsWeightBranchs.append(outputTree.Branch( "cor_sWeights_"+iSpecieName, AddressOf(CorrsWeightList[iSpecie],'afloat'), 
                                                         "cor_sWeights_"+iSpecieName+"/F" ))
                
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

        inputFile.Close()

        # ----------------------------------------------------------------------------------------------------------------------
        # ----------------------------------------------------------------------------------------------------------------------
        # Store the fit results
        # ----------------------------------------------------------------------------------------------------------------------
        # ----------------------------------------------------------------------------------------------------------------------
        if tupleSource != "Data":

            if _USE_GRID_:
                OutPutFileName = "massFitResults_%s_%s_%s%s_AllYearsSigns_%s_%s.root"%(tupleSource,inPutTag,outPutTag,ExpTag,
                                                                                       Kpibins[ibin],Kpibins[ibin+1])
            else:
                OutPutFileName = "%s/massFitResults_%s_%s_%s%s_AllYearsSigns_%s_%s.root"%(fitResDir,
                                                                                          tupleSource,inPutTag,outPutTag,ExpTag,
                                                                                          Kpibins[ibin],Kpibins[ibin+1])
                
            outf = TFile(OutPutFileName,"RECREATE")
            outt = TTree("rfr","Mass Fit Tree")

            # ----------------------------------------------------------------------------------------------------------------------
            # Defnitions of the numbers of stored values per fitted parameter
            nv = 6 # 6 values for each parameter: initial value, fitted value, fitted error, fitted error high, fitted error low, pull
            strl = [ "_genVal", "_fitVal", "_err", "_errHi", "_errLo", "_pull" ] 

            # ----------------------------------------------------------------------------------------------------------------------
            # Decalaration of the list containing the values in the branchs ("emptied" and filled for each pseudo-experiment) 
            nexp = 1
            parlist = []

            # First make the tree structure with the names of the branches, 
            # as well as the type of the data stored in the leaves (int, float, double, etc)
            print""
            print"Creation of the Mass fit tree structure..."
            parlist.append( MyStructI() )
            outt.Branch("iExp", AddressOf(parlist[0],'anInt'), "iExp/I" )

            parlist.append( MyStructI() )
            outt.Branch("fitStatus", AddressOf(parlist[1],'anInt'), "fitStatus/I" )

            # Second loop over the event species to add a branch for their generated yield values
            for iSpecie in range(0, len(l_speciesName)):
                parlist.append( MyStructF() )
                outt.Branch("n%s_true"%(l_speciesName[iSpecie]), AddressOf(parlist[iSpecie + 2],'afloat'), 
                            "n%s_true/F"%(l_speciesName[iSpecie]))

            # Then loop over the free parameters in the fit
            for par in range( 0, fitResult.floatParsFinal().getSize() ):
                param = fitResult.floatParsFinal().at(par)

                # And loop over the different values we want to store for each fitted parameter
                for ii in range(0,nv):
                    parlist.append( MyStructF() )
                    outt.Branch( param.GetName()+strl[ii], AddressOf(parlist[nv*par + ii + len(l_speciesName) + 2],'afloat'),
                                 param.GetName()+strl[ii]+"/F" )

            # Loop again to get the correlations between the fitted parameters 
            for par_i in range( 0, fitResult.floatParsFinal().getSize() ):
                param_i = fitResult.floatParsFinal().at(par_i)
                for par_j in range( 0, fitResult.floatParsFinal().getSize() ):
                    param_j = fitResult.floatParsFinal().at(par_j)
                    parlist.append( MyStructF() )
                    outt.Branch( "Corr_"+param_i.GetName()+"_"+param_j.GetName(), 
                                 AddressOf(parlist[nv*fitResult.floatParsFinal().getSize() + 
                                                   fitResult.floatParsFinal().getSize()*par_i + par_j + 
                                                   len(l_speciesName) + 2],'afloat'), 
                                 "Corr_"+param_i.GetName()+"_"+param_j.GetName()+"/F" )

            branches = outt.GetListOfBranches()

            # Now fill the tree...
            print""
            print"Filling the tree now..."
            for iter in range(0,nexp): #loop on the pseudo-experiments

                # Fill the information on the number of the considered pseudo-experiment
                parlist[0].anInt = iter+1

                # Fill the information on the fit status
                print"fitResult.covQual() = ",fitResult.covQual()
                parlist[1].anInt = int(fitResult.covQual())

                # Fill the actual number of events in the fitted dataset
                for iSpecie in range(0, len(l_speciesName)):
                    parlist[iSpecie + 2].afloat = nEvtsTrue["%s"%l_speciesName[iSpecie]] 

                # Fill the fitted parameters values (gen, fit, err, errHi, errLo)
                for par in range( 0, fitResult.floatParsFinal().getSize() ): #loop on the fitted parameters

                    if debug: print ""
                    if debug: print "At param:", fitResult.floatParsInit().at(par).GetName()
                    val_ini = fitResult.floatParsInit().at(par).getVal() 
                    val_fit = fitResult.floatParsFinal().at(par).getVal() 
                    err     = fitResult.floatParsFinal().at(par).getError()   # Gaussian error given by HESSE
                    errHi   = fitResult.floatParsFinal().at(par).getErrorHi() # Asymm error high given by MINOS
                    errLo   = fitResult.floatParsFinal().at(par).getErrorLo() # Asymm error low given by MINOS
                    if debug: print "   val_ini = %s"%(val_ini)
                    if debug: print "   val_fit = %s"%(val_fit)
                    if debug: print "   err     = %s"%(err)
                    if debug: print "   errHi   = %s"%(errHi)
                    if debug: print "   errLo   = %s"%(errLo)

                    pull = -99999.            
                    if not err==0.:
                        YieldTrueVal = -99.9
                        YieldTag = False
                        for name in l_speciesName:
                            if name == "Lb2JpsipK":
                                yieldName = "nLbpK"
                            elif name == "Lb2JpsipPi":
                                yieldName = "nLbpi"
                            else:
                                yieldName = "n%s"%(name)
                            if fitResult.floatParsInit().at(par).GetName() == yieldName and YieldTag == False:
                                YieldTag = True
                                YieldTrueVal = nEvtsTrue[name]
                        if YieldTag:
                            if debug: print "   true yield =",YieldTrueVal
                            delta = (val_fit - YieldTrueVal)
                            if fitResult.floatParsFinal().at(par).hasAsymError():
                                if delta < 0.0: pull = delta/errHi
                                else:           pull = -delta/errLo
                            else: pull = delta/err

                        else:
                            delta = (val_fit - val_ini)
                            if fitResult.floatParsFinal().at(par).hasAsymError():
                                if delta < 0.0: pull = delta/errHi
                                else:           pull = -delta/errLo
                            else: pull = delta/err
                    else:
                        pull = 0.

                    if debug: print "   pull    = %s"%(pull)

                    parlist[nv*par + 0 + len(l_speciesName) + 2].afloat = val_ini
                    parlist[nv*par + 1 + len(l_speciesName) + 2].afloat = val_fit
                    parlist[nv*par + 2 + len(l_speciesName) + 2].afloat = err
                    parlist[nv*par + 3 + len(l_speciesName) + 2].afloat = errHi
                    parlist[nv*par + 4 + len(l_speciesName) + 2].afloat = errLo
                    parlist[nv*par + 5 + len(l_speciesName) + 2].afloat = pull        

                # Fill the correlation branches
                for par_i in range( 0, fitResult.floatParsFinal().getSize() ):
                    param_i = fitResult.floatParsFinal().at(par_i)
                    for par_j in range( 0, fitResult.floatParsFinal().getSize() ):
                        param_j = fitResult.floatParsFinal().at(par_j)
                        parlist[nv*fitResult.floatParsFinal().getSize() + 
                                fitResult.floatParsFinal().getSize()*par_i + 
                                par_j + len(l_speciesName) + 2].afloat = float(fitResult.correlation(param_i,param_j))

                # Fill the TTree and go to the next pseudo-experiment
                outt.Fill()

            outf.Write()
            outf.Close()

        return 0

# ----------------------------------------------------------------------------------------------------------------------
# ----------------------------------------------------------------------------------------------------------------------
# ---- Retrieve the datasets ----
# ----------------------------------------------------------------------------------------------------------------------
# ----------------------------------------------------------------------------------------------------------------------
def getDataSet(filename,year="",sign="",ibin=-1):

        print "Retrieving dataSet from file: %s"%filename
        file = TFile(filename)
        dummyTree = file.Get(TreeName)
        dummyfile = TFile("dummyTmp_File.root","recreate")
        
        selectionCut = ""
        if tupleSource != 'Data':
            selectionCut += "KpiBin==%s && iExp==%s"%(ibin,iexp)
        else:
            selectionCut += "Kst_892_0_MM > %s && Kst_892_0_MM < %s"%(Kpibins[ibin],Kpibins[ibin+1])
            
        print selectionCut
        tree = dummyTree.CopyTree(selectionCut)

        # ------ DataSet (imported from tree) ----------
        # -- Bs and Bd to JpsiKK or Jpsipipi are substracted when applying wMC!
        weightMC = RooRealVar("wMC","wMC", -10000, 10000)
        l_addVars = []
        if tupleSource != 'Data':
            for name in l_speciesName:
                if   name == "Lb2JpsipK":  sigTag = RooRealVar("sigLbpK","sigLbpK",-10, 10)
                elif name == "Lb2JpsipPi": sigTag = RooRealVar("sigLbppi","sigLbppi",-10, 10)
                else:                      sigTag = RooRealVar("sig%s"%name,"sig%s"%name,-10, 10)
                l_addVars.append(sigTag)

        data = RooDataSet("data","data", tree, RooArgSet(Mass, weightMC, *l_addVars), "", "wMC")
        print"Retrieved datatset:",data.Print()

        if tupleSource != 'Data':
            for name in l_speciesName:
                if   name == "Lb2JpsipK":  yields[tupleSource][name][ibin] = data.sumEntries("sigLbpK>=1")
                elif name == "Lb2JpsipPi": yields[tupleSource][name][ibin] = data.sumEntries("sigLbppi>=1")
                else:                      yields[tupleSource][name][ibin] = data.sumEntries("sig%s>=1"%name)

                print "yield %s = %s"%(name, yields[tupleSource][name][ibin])
        else:
            yields[tupleSource]["Bd"]         = 0.97*tree.GetEntries()
            yields[tupleSource]["Bs"]         = 0.01*yields[tupleSource]["Bd"]
            yields[tupleSource]["Combi"]      = 0.01*yields[tupleSource]["Bd"]
            if include_Lb=='Lb':
                yields[tupleSource]["Lb2JpsipK"]  = 0.003*yields[tupleSource]["Bd"]
                yields[tupleSource]["Lb2JpsipPi"] = 0.003*yields[tupleSource]["Bd"]

        file.Close()
        dummyfile.Close()
        os.system("rm dummyTmp_File.root")
        
        return data


# ----------------------------------------------------------------------------------------------------------------------
# ----------------------------------------------------------------------------------------------------------------------
# ------------------------------------------------ STARTING POINT ------------------------------------------------------
# ----------------------------------------------------------------------------------------------------------------------
# ----------------------------------------------------------------------------------------------------------------------

yields = {}
for dataType in ("Data","Toys"):
    yields[dataType] = {}
    if dataType == "Toys":
        for name in l_speciesName:
            yields[dataType][name] = {}

# ------------------ Retrieve the data ntuple ----------------
baseDir = "/zfs_lhcb/Bs2JpsiKst/%s"%(tupleSource)

inputDir = "%s/Tuples/"%(baseDir)
outputDir = "%s/splitTuples/"%(baseDir)
os.system("mkdir %s"%outputDir)

fitResDir = "%s/fitResults/"%(baseDir)
os.system("mkdir %s"%fitResDir)

inputFile_name = ""
Datasets = {}
if tupleSource=="Data":
    inputFile_name = "data_BsJPsiKst_wMC_1112_reduced"
    outputFile_name = "data_BsJPsiKst_wMC_1112_reduced_%s"%(outPutTag)
    if _USE_GRID_:
        inputFile_name_loc = inputFile_name
    else:
        inputFile_name_loc ="%s/%s"%(inputDir, inputFile_name)
        outputFile_name_loc = "%s/%s"%(outputDir, outputFile_name)
        
    Datasets[tupleSource] = {}
    for ibin in l_bins:
        Datasets[tupleSource][ibin] = getDataSet("%s.root"%(inputFile_name_loc),"","",ibin)        
else:
    inputFile_name  = "genData_%s%s"%(inPutTag,ExpTag)
    outputFile_name = "genData_%s_%s%s"%(inPutTag,outPutTag,ExpTag)
    if _USE_GRID_:
        inputFile_name_loc = inputFile_name
    else:
        inputFile_name_loc = "%s/%s/%s"%(inputDir, inPutTag, inputFile_name)
        os.system("mkdir %s/%s_%s"%(outputDir, inPutTag, outPutTag))
        outputFile_name_loc = "%s/%s_%s/%s"%(outputDir, inPutTag, outPutTag, outputFile_name)

    Datasets[tupleSource] = {}
    for ibin in l_bins:
        Datasets[tupleSource][ibin] = getDataSet("%s.root"%(inputFile_name_loc),"","",ibin)        


# ------------------ Now run the fit... ----------------------
fitRes = runFit("2011","pos",ibin)        
