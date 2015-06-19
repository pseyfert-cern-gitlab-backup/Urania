#!/bin/env python
from PIDPerfScripts.RunRangeFuncs import *
from PIDPerfScripts.startscreen import *
from GaudiPython import gbl

import ROOT
ROOT.gSystem.Load('libRooStats.so')

import sys
import optparse
   
## def usage():
##     print ' --------------------------------------------------------------------------------------------------'
##     print ' Andrew Powell (a.powell1@physics.ox.ac.uk) February 6, 2013'
##     print ' '
##     print ' PerformMultiTrackCalib - Run PID calibration for an n-body final state:'
##     print ' Typical usage:'
##     print " python PerformMultiTrackCalib.py                                                                  "
##     print ' --------------------------------------------------------------------------------------------------'
##     sys.exit(' ')

if '__main__' == __name__:

    start()

    usage = """python %prog <stripVersion> <magPol> <refFilename> <refTree> <outputFilename> <track> (<track_2> ...)

Perform the PID calibration for a given:

    a) stripping version, <stripVersion> (e.g. '20')
    b) magnet polarity <magPol> ('MagUp' or 'MagDown')
    c) reference (i.e. signal) sample <refTree>, located in file <refFilename>

The per-event PID efficiencies will be stored in the ROOT file <outputFilename>.

The remaining argument, <track>, specifies the reference track, and takes the form [<trackName>, <trackType>, <pidCut>], where <trackName> is the name of the reference track in the TTree, <trackType> is the type of track and <pidCut> is the PID cut to evaluate for that track.

Valid track types are: 'K', 'Pi', 'P' or 'Mu'. To use the 'MuonUnBiased' hadron samples for muon misID studies, the following tracks types should be used instead: 'K_MuonUnBiased', 'Pi_MuonUnBiased' or 'P_MuonUnBiased'.

If the reference sample contains multiple final-state tracks, the remaining tracks can be specified as additional arguments.

e.g. %prog '20' 'MagUp' '$HOME/MyAnalysis/MySignalSample.root' 'SignalTree' 'MyPIDResults.root' '[Kaon,K,DLLK>4.0]' '[Pion,Pi,DLLK<4.0]'
"""
    
    parser = optparse.OptionParser(usage)
    parser.add_option("-w", "--sWeights", dest="sWeights",
                      action="store_true", default=False,
                      help="this option should be used to include sWeights")
    parser.add_option("-i", "--inputDir", dest="inputDir", metavar="DIR",
                      help="directory containing the performance histograms (default: current directory)")
    addGroup = optparse.OptionGroup(parser, "Further options")
    addGroup.add_option("-q", "--quiet", dest="verbose", action="store_false", default=True,
                        help="suppresses the printing of verbose information")
    addGroup.add_option("-p", "--momVarName", dest="momVarName", metavar="NAME",
                        default="P", help="Name of the momentum variable in the reference sample (default: %default)")
    addGroup.add_option("-e", "--etaVarName", dest="etaVarName", metavar="NAME",
                        default="TRACK_Eta", help="Name of the eta variable in the reference sample (default: %default)")
    addGroup.add_option("-n", "--nTracksVarName", dest="nTracksVarName", metavar="NAME",
                        default="nTracks", help="Name of the 'nTracks' variable in the reference sample (default: %default)")
    addGroup.add_option("-W", "--sWeightVarName", dest="sWeightVarName", metavar="NAME",
                        default="nsig_sw", help="Name of the 'sWeights' variable in the reference sample (default: %default)")
    addGroup.add_option("-P", "--printFreq", dest="printFreq", metavar="NUM", type="int", default=100,
                        help="Frequency with which to print information about reference sample entries (only used when printing verbose information, default: %default)")
                        
    parser.add_option_group(addGroup)

    opts, args = parser.parse_args()
    if len(args) < 6:
        parser.error("Expected at least six arguments, got %d" %len(args))
    
    StripVersion=args[0]
    CheckStripVer(StripVersion)
    
    MagPolarity=args[1]
    CheckMagPol(MagPolarity)
    
    fname_Ref = args[2]
    tname_Ref = args[3]
    fname_out = args[4]

    trackArgs = args[5:]

    trackList = []
    trackTypes = []
    for arg in trackArgs:
        trackName = None
        trackType = None
        DLLCut = None
        if not arg.startswith("[") or not arg.endswith("]"):
            parser.error("Invalid track variable string '%s'" %arg)
        trackInfo=arg[1:-1].split(",")
        if len(trackInfo) != 3:
            parser.error("Invalid track variable string '%s'" %arg)
        trackName = trackInfo[0].strip()
        trackType = trackInfo[1].strip()
        DLLCut = trackInfo[2].strip().replace("/", "_div_")

        CheckPartType(trackType)
        
        if trackType not in trackTypes:
            trackTypes.append(trackType)
        trackList.append((trackName,trackType,DLLCut))
        
    if opts.verbose:
        print '===================================='
        print "Stripping version: %s" %StripVersion
        print "Magnet polarity: %s" %MagPolarity
        print "Reference sample (filename): %s (%s)" %(tname_Ref, fname_Ref)
        print "Output filename: %s" %fname_out
        for i, v in enumerate(trackList):
            print "Track name, type and PID cut (track %d): %s" %(i, str(v))
        print '===================================='
        
    #=============================================================================
    # Source reference sample TTree
    #=============================================================================
   ##  f_Ref = ROOT.TFile.Open('$PIDPERFSCRIPTSROOT/scripts/root/'
##                             'B2DX/Ref_K0SPiPi_DD_S20_DOWN.root')
    
##     f_Ref = ROOT.TFile.Open('$HOME/CalibTests/Ref_K0SPiPi_DD_S20_DOWN.root')
##     t_Ref = f_Ref.Get('TTT')
    f_Ref = ROOT.TFile.Open(fname_Ref)
    if not f_Ref or f_Ref.IsZombie():
        print "ERROR: Failed to open file %s for reading" %fname_Ref
        sys.exit(1)
    t_Ref = f_Ref.Get(tname_Ref)
    if not t_Ref:
        print "ERROR: Failed to retrieve TTree %s from file %s" %(tname_Ref, fname_Ref)
        sys.exit(1)

    #=============================================================================
    # Create instance of MultiTrackCalibTool
    #=============================================================================
    CalibTool = gbl.MultiTrackCalibTool("CalibTool", t_Ref, fname_out, "RECREATE", 
                                        opts.verbose, opts.printFreq)
    
    #=============================================================================
    # Declare the name in the reference TTree for the various binning variables
    #=============================================================================
    CalibTool.SetTrackMomVarName(opts.momVarName)#'P')
    CalibTool.SetTrackEtaVarName(opts.etaVarName)#''TRACK_Eta')
    CalibTool.SetTrackNTrackVarName(opts.nTracksVarName)#'nTracks')
    
    #=============================================================================
    # Declare the name in the reference TTree for the sWeight variable
    #=============================================================================
    if not opts.sWeights: opts.sWeightVarName=""
    CalibTool.SetSWeightVarName(opts.sWeightVarName)#'nsig_sw')

    #=============================================================================
    # Obtain Performance histogram for each track under consideration,
    # declare the name in the reference TTree of each track to be considered and
    # the PID performance histogram to be associated with it
    #=============================================================================    
    #
    # Open files containing performance histograms for each track type to consider
    #
    perfFiles = {}
    for trackType in trackTypes:
        
        fname = "PerfHists_{part}_Strip{strp}_{pol}_3D.root".format(part=trackType,
                                                                    strp=StripVersion, pol=MagPolarity)
        if opts.inputDir is not None:
            fname = "%s/%s" %(opts.inputDir, fname)

        f_Perf = ROOT.TFile.Open(fname)
        if not f_Perf or f_Perf.IsZombie():
            print "ERROR: Failed to open file %s for reading" %fname
            #del CalibTool
            sys.exit(1)
        perfFiles[trackType]=f_Perf

    #
    # For each reference track, retrieve the performance histogram
    #
    for trackName, trackType, DLLCut in trackList:
        f_Perf = perfFiles[trackType]
        # need to add particle name to DLL cut apparently
        histname="%s_%s_All" %(trackType, DLLCut)
        PerfHist=f_Perf.Get(histname)
        if not PerfHist:
            print "ERROR: Failed to retrieve histogram %s from file %s" %(histname,
                                                                          f_Perf.GetName())
            #del CalibTool
            sys.exit(1)
        CalibTool.DeclareSignalTrackAndPerfHist(trackName, PerfHist)

    #=============================================================================
    # Ensure the reference sample tracks reside with the bin ranges of the 
    # declared PID performance histograms
    #=============================================================================
    CalibTool.SetRefDataInPerfHistLimits();

    #=============================================================================
    # Calculate the per track event efficiencies
    #=============================================================================
    CalibTool.Calculate();
  
    #=============================================================================
    # Calculate the naive average event efficiency and associated error
    #=============================================================================
    NaiveResult = CalibTool.CalculateNaiveAverage();
    print 'Naive event efficiency and error: (%.3f +/- %.3f)%%' %(100*NaiveResult.first, 100*NaiveResult.second) 

    if opts.sWeights: 
      NaiveResultWeight = CalibTool.CalculateNaiveWeightAverage();
      print 'Naive event efficiency and error (Weighted): (%.3f +/- %.3f)%%' %(100*NaiveResultWeight.first,
                                                                               100*NaiveResultWeight.second) 
    
    CalibTool.Write()
    #del CalibTool
    CalibTool=None

