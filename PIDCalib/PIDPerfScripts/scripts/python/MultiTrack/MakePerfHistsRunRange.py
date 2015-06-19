#!/bin/env python
from PIDPerfScripts.DataFuncs import *
from PIDPerfScripts.PerfCalcFuncs import *
from PIDPerfScripts.startscreen import *

import ROOT
ROOT.gSystem.Load('libRooStats.so')

import sys
#import getopt
import optparse
#import warnings

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
##     print "                                 --maxRun=114287                     "
##     print "                                 --pidCuts='[DLLK > 0.0, DLLK > 4.0 && DLLpK < 0.0]'"
##     print "                                 --partName=K                         "
##     print ' --------------------------------------------------------------------------------------------------'
##     sys.exit(' ')
      
if '__main__' == __name__:
    start()
    
    usage = """python %prog [options] <stripVersion> <magPol> <partName> <pidCut>

Make performance histograms for a given:

    a) stripping version, <stripVersion> (e.g. '20')
    b) magnet polarity <magPol> ('MagUp' or 'MagDown')
    c) particle type <partName> ('K', 'P', 'Pi' or 'Mu')
    d) PID cut <pidCut>

Multiple PID cuts can be specified if necessary, e.g. '[DLLK > 0.0, DLLK > 4.0]'. In this case, a performance histogram will be produced for each DLL cut.

For a full list of optional arguments, do: '%prog -h'.

e.g. %prog  --minRun=114205 --maxRun=114287 '20' 'MagUp' 'K' '[DLLK > 0.0, DLLK > 4.0 && DLLpK < 0.0]'

IMPORTANT: To use the 'MuonUnBiased' hadron samples for muon misID studies, one of the following particle types should be used: 'K_MuonUnBiased', 'Pi_MuonUnBiased' or 'P_MuonUnBiased'.


"""
    
    parser = optparse.OptionParser(usage)
    parser.add_option('-x', '--minRun', dest="runMin", metavar="NUM",
                      help="the minimum run number to process (if applicable)")
    parser.add_option('-y', '--maxRun', dest="runMax", metavar="NUM",
                      help="the maximum run number to process (if applicable)")
    parser.add_option("-o", "--outputDir", dest="outputDir", metavar="DIR",
                      help="save the performance histograms to this directory (default: current directory)")

    addGroup = optparse.OptionGroup(parser, "Further options")
    addGroup.add_option("-q", "--quiet", dest="verbose", action="store_false", default=True,
                      help="suppresses the printing of verbose information")                 
    addGroup.add_option("-T", "--noTables", dest="printTables", action="store_false",
                        default=True, help="disables the printing of performance tables (NB. they will still be written to a TFile)")
    
    addGroup.add_option("-l", "--latexTables", dest="latexTables", action="store_true",
                        default=False, help="print LaTeX-format tables (rather than ASCII)")
    addGroup.add_option("-t", "--tableFilename", dest="tabFile", metavar="FILE",
                      help="if this option is used, the tables will printed to the specified FILE rather than being printed to the screen")
    addGroup.add_option("-M", "--allow-missing", dest="allowMissing", action="store_true",
                        default=False, help="Allow missing calibration subsamples. N.B. You should only use this option if requested to do so by the PIDCalib authors") 
    parser.add_option_group(addGroup)
    
    # mandatory arguments are:
    # 1) stripping version
    # 2) magnet polarity
    # 3) particle name
    # 4) one or more PID cuts

    opts, args = parser.parse_args()

    if len(args)!=4:
        parser.error("Expected four arguments, got %d" %len(args))
        
    StripVersion = None
    MagPolarity = None
    PartName = None
    DLLCuts = []
    RunMin = None
    RunMax = None
    
    StripVersion=args[0]
    CheckStripVer(StripVersion)
    
    # set the magnet polarity
    MagPolarity=args[1]
    CheckMagPol(MagPolarity)
        
    # set the particle name
    PartName=args[2]
    CheckPartType(PartName)
      
    # set the PID cuts
    DLLCuts = args[3]
    
    if DLLCuts.startswith("["):
        if not DLLCuts.endswith("]"):
            parser.error("Invalid DLL cut string %s" %DLLCuts)
        DLLCuts = DLLCuts[1:-1].split(',')
    elif DLLCuts.startswith("("):
        if not DLLCuts.endswith(")"):
            parser.error("Invalid DLL cut string %s" %DLLCuts)
        DLLCuts = DLLCuts[1:-1].split(',')
    else:
        DLLCuts = (DLLCuts,)
   
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
        
    #======================================================================
    # Check DLL Cuts etc.
    #======================================================================
    if opts.verbose:
        print '========== Requested data samples =========='
        print "Stripping version: %s" %StripVersion
        print "Magnet polarity: %s" %MagPolarity
        print "Particle name: %s" %PartName
        for icut, cut in enumerate(DLLCuts):
            print "PID cut %d: %s" %(icut,cut)
	print '===================================='

    #=============================================================================
    # Declare Binning Schema (RooBinnings)
    #=============================================================================

    minMom = 5000
    if IsMuonUnBiased(PartName) : minMom = 3000

    Mom_Bin = ROOT.RooBinning(minMom, 100000, 'P')
    Eta_Bin = ROOT.RooBinning(1.5, 5, 'ETA')
    nTrk_Bin = ROOT.RooBinning(0, 500, "nTrack");

    if IsMuonUnBiased(PartName) : 
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
    BinSchema.push_back(Eta_Bin)
    BinSchema.push_back(nTrk_Bin)

    if opts.verbose:
        print('========== Binning Schema ==========')
        for binning in BinSchema:
            binning.Print()
        print('====================================')

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
                            opts.verbose,
                            opts.allowMissing)
    
    #======================================================================
    # Make Weighted Average
    #======================================================================
    MakeAveragePlotList(Plots)
    if opts.verbose:
        print 'Plots:', Plots
    
    #======================================================================
    # Open file to write TH1Fs to
    #======================================================================
 
    fname = "PerfHists_{part}_Strip{strp}_{pol}_3D.root".format(part=PartName,
                                                                strp=StripVersion,
                                                                pol=MagPolarity)
    if opts.outputDir is not None:
        fname = "%s/%s" %(opts.outputDir, fname)

    print "Saving performance histograms to %s" %fname
    f_Out = ROOT.TFile.Open(fname, "RECREATE")
    if not f_Out:
        raise IOError("Failed to open file %s for writing" %fname)
    
    for iPlot in Plots:
        iPlot[-1].Write()

    #======================================================================
    # Create PIDTable for each PID cut and print to screen
    #======================================================================
    if opts.printTables:
        for i in range(len(Plots)):
            plot=Plots[i][-1]
            pidTable = gbl.PIDTable(plot, Mom_Bin, Eta_Bin, nTrk_Bin)
            tabName=plot.GetName()
            tabHeader = "PID Table for histogram %s" %tabName
            if opts.tabFile is None:
                print tabHeader
                pidTable.PrintTable(gbl.cout, opts.latexTables)
            else:
                appMode = "w" if i==0 else "a"
                os = open(opts.tabFile, appMode)
                os.write(tabHeader+'\n')
                os.close()
                os = gbl.fstream(opts.tabFile,gbl.fstream.out|gbl.fstream.app)
                pidTable.PrintTable(os, opts.latexTables)
                
    #======================================================================
    # Close file
    #======================================================================
    f_Out.Close()
