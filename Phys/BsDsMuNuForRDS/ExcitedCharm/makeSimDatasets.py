from BsDsMuNuForRDS.DataRetrieval import *
from BsDsMuNuForRDS.TruthCuts import *
import sys, os
from ROOT import TFile, TTree, gROOT, gDirectory, RooStats, RooAbsData, RooArgSet
from ROOT import RooFit, RooRealVar, RooDataSet, RooArgList, RooFormulaVar
from ROOT import RooAddPdf, TCanvas, kBlue, kGreen, kRed, RooWorkspace
from numpy import zeros as z
RooWorkspace.rfimport = getattr(RooWorkspace, 'import')
RooWorkspace.rfprint  = getattr(RooWorkspace, 'Print')
gROOT.SetBatch(True)
gROOT.ProcessLine('.x ~/lhcbStyle.C')
RooAbsData.setDefaultStorageType(RooAbsData.Tree)

# myCut = "(isGamma1InCone==1 && hDsMuMassFirstG04 > 1950 && hDsMuMassFirstG04 < 2600 && MM2 > -20e6 && MM2 < 12e6 && Emu < 3.5e3 && q2 > -20e6 && q2 < 13e6 && triggerTag==1 && mu_ProbNNmu > 0.3 && Bs_0_MCORR < 8e3)"

# Some settings
dataTags  = ['MC_AllNeutrals']
polarities = ['MagUp'] #, 'MagDown']
tName    = "B2DsMuNuTuple"
preScale = 1.0

# Here will go the cut dictionary.
cutDict = {
    #'AllSpecies'  : { 'cut' : '1' }
    #,'DsstarOnly' : { 'cut' : '(%s || %s)' %(DsStarmu, DsStartau) }
    #,'DsstartauOnly' : { 'cut' : DsStartau }
    'DsstarNoFeedDown' : { 'cut' : '(%s && %s)' %(DsStarCutFull, DsGMIsBsCut) }
    }

globalCut = "(isGamma1InCone==1 && hDsMuMassFirstG04 > 1950 && hDsMuMassFirstG04 < 2600 && MM2 > -20e6 && MM2 < 12e6 && Emu < 3.5e3 && q2 > -20e6 && q2 < 13e6 && triggerTag==1 && mu_ProbNNmu > 0.3 && Bs_0_MCORR < 8e3 && Ds_0.40_nc_CL > 0.6)"

for dataTag in dataTags:
    for polarity in polarities:

        # Get the chain
        c = getProcessedChain(dataTag, polarity)
        print '-- Entries passing trigger mimicking = ', c.GetEntries('triggerTag==1')

        # Declare the combination mass parameter.
        # And also the other parameters we wish to keep or cut on.
        rv_mass     = RooRealVar("hDsMuMassFirstG04", "hDsMuMassFirstG04", 1950, 2600)
        rv_mass.setRange("AllRange", 1950, 2600)
        rv_MM2        = RooRealVar("MM2", "MM2", -20e6, 12e6)
        rv_Emu        = RooRealVar("Emu", "Emu", 0, 3.5e3)
        rv_q2         = RooRealVar("q2", "q2", -20e6, 13e6)
        rv_Bs_0_MCORR = RooRealVar("Bs_0_MCORR", "Bs_0_MCORR", 0, 15e3)

        # Apply a cut to get rid of events with no photons.
        dataSetVars = RooArgSet(rv_mass, rv_MM2, rv_Emu, rv_q2, rv_Bs_0_MCORR)

        container_mass = z(1, dtype=float)
        container_MM2  = z(1, dtype=float)
        container_Emu  = z(1, dtype=float)
        container_q2   = z(1, dtype=float)
        container_Bs_0_MCORR = z(1, dtype=float)

        c.SetBranchAddress('hDsMuMassFirstG04', container_mass)
        c.SetBranchAddress('MM2', container_MM2)
        c.SetBranchAddress('Emu', container_Emu)
        c.SetBranchAddress('q2', container_q2)
        c.SetBranchAddress('Bs_0_MCORR', container_Bs_0_MCORR)
        
        for cutName, cutSettings in cutDict.iteritems():

            # Make the empty dataset.
            rds_data = RooDataSet('rds_mass', 'rds_mass', dataSetVars)

            # Make a TEventList selection.
            theCut = '(%s && %s)' %(cutSettings['cut'], globalCut)
            c.Draw('>>eList', theCut)
            eList = gDirectory.Get('eList')

            numEntries = int(c.GetEntries()*preScale)
            for i in xrange(numEntries):
                if i%1000==0:
                    sys.stdout.write('\rProcessing event %i of %i...' %(i, numEntries))
                    sys.stdout.flush()
                    
                # Skip the events failing the cuts.
                if not eList.Contains(i): continue

                # Set the RooRealVars and populate the event in the dataset.
                c.GetEntry(i)
                rv_mass.setVal(container_mass[0])
                rv_MM2.setVal(container_MM2[0])
                rv_Emu.setVal(container_Emu[0])
                rv_q2.setVal(container_q2[0])
                rv_Bs_0_MCORR.setVal(container_Bs_0_MCORR[0])
                
                rds_data.add(dataSetVars)

            print
            print '-- Tree num entries         :', c.GetEntries()
            print '-- RDS num entries          :', rds_data.numEntries()
            
            # Save all the objects in a workspace.
            w = RooWorkspace('RDs_Workspace', 'RDs_Workspace')
            w.rfimport(rds_data)
            fNameDS = "RDs_DataSet_%s_%s_%s.root" %(dataTag, polarity, cutName)
            w.writeToFile(fNameDS)
            print '*'*100
