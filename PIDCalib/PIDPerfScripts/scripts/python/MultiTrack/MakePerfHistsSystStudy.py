#!/bin/env python
from PIDPerfScripts.DataFuncs import *
from PIDPerfScripts.PerfCalcFuncs import *
from PIDPerfScripts.startscreen import *

import ROOT
ROOT.gSystem.Load('libRooStats.so')

import sys
#import getopt
import optparse

## def usage():
##     print ' --------------------------------------------------------------------------------------------------'
##     print ' Andrew Powell (a.powell1@physics.ox.ac.uk) January 24, 2013'
##     print ' '
##     print ' MakePerfHistsRunRange - Make performance histograms for a given:'
##     print ' a) Field polarity (MagUp/MagDown)'
##     print ' b) Stripping version (19/20/etc)'
##     print ' c) Run range (If full run range is desired, pass --minRun=None and --maxRun=None) '
##     print ' d) List of PID cuts (Format: [DLLA > a, DLLB < b, ...])'
##     print ' e) Particle type (From K, Pi or P)'
##     print ' Typical usage:'
##     print " python MakePerfHistsRunRange.py --magPolarity=MagUp                 "
##     print "                                 --stripVersion=20                   "
##     print "                                 --minRun=114205                     "
##     print "                                 --maxRun=115863                     "
##     print "                                 --pidCuts='[DLLK > -6.0, DLLK > -4.0, DLLK > -2.0, DLLK > 0.0,  DLLK > 2.0, DLLK > 4.0, DLLK > 6.0]'"
##     print "                                 --partName=K                         "
##     print ' --------------------------------------------------------------------------------------------------'
##     sys.exit(' ')
      
if '__main__' == __name__:

    start()

    usage = """%prog [options] <stripVersion> <magPol> <partName> <pidVar> <minPIDCut> <nPIDCuts> <pidCutInterval>

Make performance histograms for systematics studies for a given:

    a) stripping version, <stripVersion> (e.g. '20')
    b) magnet polarity <magPol> ('MagUp' or 'MagDown')
    c) particle type <partName> ('K', 'P', 'Pi' or 'Mu')
    d) PID cut variable <pidVar>, INCLUDING the inequality (e.g. 'DLLK>' or 'DLLpK<')
    e) initial PID cut <initPIDCut>
    f) total number of PID cuts <nPIDCuts>
    g) PID cut interval <pidCutInterval>

This script scans over a range of cut values of <pidVar>, starting from <initPIDCut>, increasing by <pidCutInterval> each time until <nPIDCuts> have been evaluated.

There are two sets of performance histograms created by this script (each stored to separate files)
The first uses the standard binning, whilst the second uses a single bin in each variable in the binning scheme.
Both these sets of histograms are used as input to the script 'PerformMultiTrackCalibSystStudy.py'.

Note that only one DLL variable can be scanned using this script.
If you need to apply additional requirements (e.g. requiring 'IsMuon'), then these additional requirements can be specified in the appropriate optional argument.

For a full list of optional arguments, do: '%prog -h'.

e.g. %prog --minRun=114205 --maxRun=114287 '20' 'MagUp' 'K' 'DLLK>' -- '-4.0' '5' '2.0'

NB. If any positional arguments are negative, they must be preceeded by '--'.

IMPORTANT: For muon 'unbiased' calibration samples, the option '-m' must be used.
"""
    
    parser = optparse.OptionParser(usage)
    parser.add_option('-x', '--minRun', dest="runMin", metavar="NUM",
                      help="the minimum run number to process (if applicable)")
    parser.add_option('-y', '--maxRun', dest="runMax", metavar="NUM",
                      help="the maximum run number to process (if applicable)")
    parser.add_option("-m", "--isMuon", dest="isMuon",
                      action="store_true", default=False,
                      help="this option should be used for the muon calibration")
    parser.add_option("-e", "--extraCuts", dest="extraCuts", metavar="CUTS",
                      help="Consider these CUTS in addition to the PID variable being scanned")
    parser.add_option("-o", "--outputDir", dest="outputDir", metavar="DIR",
                      help="save the performance histograms to this directory (default: current directory)")
    
    addGroup = optparse.OptionGroup(parser, "Further options")
    addGroup.add_option("-q", "--quiet", dest="verbose", action="store_false", default=True,
                      help="suppresses the printing of verbose information")                 
    parser.add_option_group(addGroup)
    
    # mandatory arguments are:
    # 1) stripping version
    # 2) magnet polarity
    # 3) particle name
    # 4) one or more PID cuts

    opts, args = parser.parse_args()

    if len(args)!=7:
        parser.error("Expected 7 mandatory arguments, got %d" %len(args))      
  
    StripVersion=args[0]
            
    # set the magnet polarity
    MagPolarity=args[1]
    if MagPolarity not in ("MagDown", "MagUp"):
        parser.error("Expected 'MagDown' or 'MagUp' for magnet polarity, got %s" %MagPolarity)     

    # set the particle name
    PartName=args[2]
    if PartName not in ("K","Pi","P","Mu"):
        parser.error("Expected 'K', 'Pi', 'P' or 'Mu' for particle name, got %s" %PartName)

    # set the DLL cut variable (+ inequality)
    DLLVar=args[3].strip()
    if not DLLVar.endswith(("<",">")):
        parser.error("Invalid PID variable string '%s'. Please ensure that the variable name is succeeded by '>' or '<'" %DLLVar)

    # set the initial DLL cut
    try:
        float(args[4])
    except ValueError:
        parser.error("Parameter '%s' is not a floating-point number" %args[4])
    DLLStart=args[4]

    try:
        int(args[5])
    except ValueError:
        parser.error("Parameter '%s' is not an integer" %args[5])
    DLLnSteps=args[5]

    try:
        float(args[6])
    except ValueError:
        parser.error("Parameter '%s' is not an integer" %args[5])
    DLLStepSize=args[6]

    RunMin = opts.runMin
    RunMax = opts.runMax
    
    if RunMin is not None:
        try:
            int(RunMin)
        except ValueError:
            parser.error("argument to --minRun ('%s') is not an integer'" %RunMin)
            
        if RunMax is None:
            parser.error("Min run was specified as %s, but no max run was given" %RunMin)

    if RunMax is not None:
        try:
            int(RunMax)
        except ValueError:
            parser.error("argument to --maxRun ('%s') is not an integer'" %RunMax)
        if RunMin is None:
            parser.error("Max run was specified as %s, but no min run was given" %RunMax)
        
  ##   try:
##         opts, args = getopt.getopt(sys.argv[1:],'v:p:x:y:c:n',
##                                    ['stripVersion=',
##                                     'magPolarity=',
##                                     'minRun=',
##                                     'maxRun=',
##                                     'pidCuts=',
##                                     'partName='])
##     except getopt.GetoptError:
##         usage()
##     if len(opts) != 6:
##         usage()
##     for o,p in opts:
##         if o in ['-v', '--stripVersion']:
##             StripVersion = p
##             print 'StripVersion :',StripVersion
##         elif o in ['-p', '--magPolarity']:
##             MagPolarity = p
##             print 'MagPolarity  :',MagPolarity
##         elif o in ['-x', '--minRun']:
##             RunMin = (p if p!='None' else None)
##             print 'RunMin       :',RunMin
##         elif o in ['-y', '--maxRun']:
##             RunMax = (p if p!='None' else None)
##             print 'RunMax       :',RunMax
##         elif o in ['-c', '--pidCuts']:
##             DLLCuts = p[1:-1].split(',')
##             print 'DLLCuts      :',DLLCuts
##         elif o in ['-n', '--partName']:
##             PartName = p
##             print 'PartName     :',PartName

    #======================================================================
    # Check DLL Cuts etc.
    #======================================================================
    if opts.verbose:
        print '========== Requested data samples =========='
        print "Stripping version: %s" %StripVersion
        print "Magnet polarity: %s" %MagPolarity
        print "Particle name: %s" %PartName
        print "PID variable: %s" %DLLVar
        print "Minimum PID cut value: %s" %DLLStart
        print "Number of PID cuts to scan: %s" %DLLnSteps
        print "PID cut interval: %s" %DLLStepSize
        if opts.extraCuts is not None:
            print "Extra PID requirements: %s" %opts.extraCuts
        print "Muon calibration?: %s" %opts.isMuon
        print '===================================='

    #=============================================================================
    # Declare Binning Schema (RooBinnings) - 'OneBin' binning
    #=============================================================================

    minMom = 5000
    if opts.isMuon : minMom = 3000
      
    Mom_Bin_OneBin = ROOT.RooBinning(minMom,100000,'P')
    Eta_Bin_OneBin = ROOT.RooBinning(1.5,5,'ETA')
    nTrk_Bin_OneBin = ROOT.RooBinning(0,500,"nTrack");

    BinSchema_OneBin = gbl.std.vector('RooBinning*')()
    BinSchema_OneBin.push_back(Mom_Bin_OneBin)
    #if not opts.isMuon :
    BinSchema_OneBin.push_back(Eta_Bin_OneBin)
    BinSchema_OneBin.push_back(nTrk_Bin_OneBin)

    #=============================================================================
    # Declare Binning Schema (RooBinnings) - 'OneBin' binning
    #=============================================================================
    Mom_Bin=ROOT.RooBinning(Mom_Bin_OneBin, 'P')
    Eta_Bin=ROOT.RooBinning(Eta_Bin_OneBin, 'ETA')
    nTrk_Bin=ROOT.RooBinning(nTrk_Bin_OneBin, 'nTrack')

    if opts.isMuon :
      Mom_Bin.addBoundary(6000);
      Mom_Bin.addBoundary(8000);
      Mom_Bin.addBoundary(10000);
      Mom_Bin.addBoundary(12000);
      Mom_Bin.addBoundary(14500);
      Mom_Bin.addBoundary(17500);
      Mom_Bin.addBoundary(21500);
      Mom_Bin.addBoundary(27000);
      Mom_Bin.addBoundary(32000);
      Mom_Bin.addBoundary(40000);
      Mom_Bin.addBoundary(60000);
      Mom_Bin.addBoundary(70000);
    else :
      Mom_Bin.addBoundary(9300);            #R1 Kaon Threshold
      Mom_Bin.addBoundary(15600);           #R2 Kaon Threshold
      Mom_Bin.addUniform(15, 19000, 100000);
    
    Eta_Bin.addUniform(4, 1.5, 5);
    nTrk_Bin.addBoundary(50);
    nTrk_Bin.addBoundary(200);
    nTrk_Bin.addBoundary(300);

    BinSchema = gbl.std.vector('RooBinning*')()
    BinSchema.push_back(Mom_Bin)
    #if not opts.isMuon :
    BinSchema.push_back(Eta_Bin)
    BinSchema.push_back(nTrk_Bin)
    
    if opts.verbose:
        print('========== Binning Schema ==========')
        for binning in BinSchema:
            binning.Print()
        print('====================================')
        print('========== "OneBin" Binning Schema ==========')
        for binning in BinSchema_OneBin:
            binning.Print()
        print('====================================')


    #======================================================================
    # Make the list of DLL cuts
    #======================================================================
    minCut = float(DLLStart)
    nCuts = int(DLLnSteps)
    stepSize = float(DLLStepSize)
    DLLCuts=[]
    for iCut in range(nCuts):
        cutval = minCut+(stepSize*iCut)
        DLLCut = "%s%f" %(DLLVar, cutval) if not opts.extraCuts else "(%s%f)&&(%s)" %(
            DLLVar, cutval, opts.extraCuts)
        DLLCuts.append(DLLCut)
    
    #======================================================================
    # Final list of plots
    #======================================================================
    Plots = GetPerfPlotList(MakePerfPlotsList, 
                            StripVersion,
                            MagPolarity,
                            PartName,
                            DLLCuts,
                            '',#'Charge==Charge::Positive && '+PartName+'_P<100000',
                            BinSchema,
                            RunMin,
                            RunMax,
                            opts.isMuon,
                            opts.verbose)

    #======================================================================
    # Final list of plots ('OneBin')
    #======================================================================
    Plots_OneBin = GetPerfPlotList(MakePerfPlotsList, 
                                   StripVersion,
                                   MagPolarity,
                                   PartName,
                                   DLLCuts,
                                   '',#'Charge==Charge::Positive && '+PartName+'_P<100000',
                                   BinSchema_OneBin,
                                   RunMin,
                                   RunMax,
                                   opts.isMuon,
                                   opts.verbose)
    
    #======================================================================
    # Make Weighted Average
    #======================================================================
    MakeAveragePlotList(Plots)
    if opts.verbose:
        print 'Plots:', Plots

    MakeAveragePlotList(Plots_OneBin)
    if opts.verbose:
        print 'Plots ("OneBin"):', Plots_OneBin
    
    #======================================================================
    # Open file to write TH1Fs to
    #======================================================================
    MuonPostFix = ""
    if opts.isMuon and PartName in ("K", "Pi", "P"):
        MuonPostFix="_MuonUnbiased"

    DLLSuffix=DLLVar[0:-1].replace('/', '_div_')
    fname = "PerfHists_%s%s_Strip%s_%s_Syst_%s.root" %(PartName,MuonPostFix,
                                                       StripVersion,
                                                       MagPolarity, DLLSuffix)
    fname_onebin = "PerfHists_%s%s_Strip%s_%s_OneBin_%s.root" %(PartName,
                                                                MuonPostFix,
                                                                StripVersion,
                                                                MagPolarity,
                                                                DLLSuffix)
    if opts.outputDir is not None:
        fname = "%s/%s" %(opts.outputDir, fname)
        fname_onebin = "%s/%s" %(opts.outputDir, fname_onebin)

    print "Saving performance histograms to %s" %fname    
    print "Saving 'OneBin' performance histograms to %s" %fname_onebin  

    f_Out = ROOT.TFile(fname, "RECREATE")
    ## f_Out = ROOT.TFile('PerfHists_'+PartName+'_Strip'+StripVersion+'_'+MagPolarity+'_OneBin.root',
    ##                        'RECREATE')
    
    for iPlot in Plots:
        iPlot[-1].Write()

    f_Out_OneBin = ROOT.TFile(fname_onebin, "RECREATE")
    for iPlot in Plots_OneBin:
        iPlot[-1].Write()
        
    #======================================================================
    # Close files
    #======================================================================
    f_Out.Close()
    f_Out_OneBin.Close()
