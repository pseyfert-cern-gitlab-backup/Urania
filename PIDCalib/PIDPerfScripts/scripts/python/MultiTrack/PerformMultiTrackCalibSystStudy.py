#!/bin/env python
from PIDPerfScripts.startscreen import *
from GaudiPython import gbl

import ROOT
ROOT.gSystem.Load('libRooStats.so')
from math import sqrt
from array import array
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
    
    usage = """python %prog <stripVersion> <magPol> <partName> <pidVar> <outputFilename>

Perform the PID calibration systematic study for a given:

    a) stripping version, <stripVersion> (e.g. '20')
    b) magnet polarity <magPol> ('MagUp' or 'MagDown')
    c) particle type <partName> ('K', 'P', 'Pi' or 'Mu')
    d) PID cut variable <pidVar> (e.g. 'DLLK')
    
The per-event PID efficiencies and systematics study plot will be stored in the ROOT file <outputFilename>.
It is possible to append to an existing output file rather than recreate the file by specifying the associated optional argument.
The names of the output TTree containing the per-event PID efficiencies and the PID systematics study plot contain the particle type and DLL variable, so the various systematics results should not overwrite one another.

Valid track types are: 'K', 'Pi', 'P' or 'Mu'.

e.g. %prog '20' 'MagUp' 'K' 'DLLK' 'PIDSystResults_Kaon_DLLK.root'

IMPORTANT: If using muon and/or 'MuonUnbiased' calibration samples, the option '-m' must be used.
"""

    parser = optparse.OptionParser(usage)
    parser.add_option("-m", "--isMuon", dest="isMuon",
                      action="store_true", default=False,
                      help="this option should be used for the muon calibration")
    parser.add_option("-i", "--inputDir", dest="inputDir", metavar="DIR",
                      help="directory containing the performance histograms (default: current directory)")
    parser.add_option("-a", "--appendOutput", dest="appendOutput", action="store_true",
                      default=False, help="open the output ROOT file in 'UPDATE' mode, rather than 'RECREATE'")
    ## parser.add_option("-s", "--savePIDEffs", dest="savePIDEffs", action="store_true",
##                       default=False, help="store the per-event PID efficiencies in the output file")
    addGroup = optparse.OptionGroup(parser, "Further options")
    addGroup.add_option("-q", "--quiet", dest="verbose", action="store_false", default=True,
                        help="suppresses the printing of verbose information")

    opts, args = parser.parse_args()
    if len(args) < 5:
        parser.error("Expected at least five arguments, got %d" %len(args))

    StripVersion=args[0]
    MagPolarity=args[1]
    if MagPolarity not in ("MagDown", "MagUp"):
        parser.error("Expected 'MagDown' or 'MagUp' for magnet polarity, got %s" %MagPolarity)
    PartName=args[2]
    if PartName not in ("K", "Pi", "P", "Mu"):
        parser.error("Expected 'K', 'Pi', 'P' or 'Mu' for particle name, got %s" %PartName)

    DLLVar=args[3].strip()
    fname_out = args[4]

    if opts.verbose:
        print '===================================='
        print "Stripping version: %s" %StripVersion
        print "Magnet polarity: %s" %MagPolarity
        print "Particle name: %s" %PartName
        print "Output filename: %s" %fname_out
        print "PID variable: %s" %DLLVar
        print '===================================='
    
    #=============================================================================
    # Source reference sample TTree
    #=============================================================================
    Strip2Reco = {'13b'  : 10,
                  '15'   : 11,
                  '17'   : 12,
                  '20'   : 14,
                  '20r1' : 14
                  }
    
    fname_ref_prefix = "$CALIBREFDATASTORE" if not opts.isMuon else "$MUONCALIBREFDATASTORE"
    fname_ref = '%s/Reco%d_DATA/%s/Ref_%s_%s_Strip%s.root' %(fname_ref_prefix,
                                                             Strip2Reco[StripVersion],
                                                             MagPolarity,
                                                             PartName,
                                                             MagPolarity,
                                                             StripVersion)
    tname_ref = 'CalibPID'
    
    f_Ref = ROOT.TFile.Open(fname_ref)
    if not f_Ref or f_Ref.IsZombie():
        print "ERROR: Failed to open file %s for reading" %fname_ref
        sys.exit(1)
    t_Ref = f_Ref.Get(tname_ref)
    if not t_Ref:
        print "ERROR: Failed to retrieve TTree %s from file %s" %(tname_ref,
                                                                  fname_ref)
        sys.exit(1)
        
    #=============================================================================
    # Open the files containing the performance histograms and 'true' performance values
    #=============================================================================
    MuonPostFix=""
    if opts.isMuon and PartName in ("K", "Pi", "P"):
        MuonPostFix="_MuonUnbiased"
    fname_perf = "PerfHists_%s%s_Strip%s_%s_Syst_%s.root" %(PartName,MuonPostFix,StripVersion,MagPolarity,DLLVar)
    fname_true = "PerfHists_%s%s_Strip%s_%s_OneBin_%s.root" %(PartName,MuonPostFix,StripVersion,MagPolarity,DLLVar)
    if opts.inputDir is not None:
        fname_perf = "%s/%s" %(opts.inputDir, fname_perf)
        fname_true = "%s/%s" %(opts.inputDir, fname_true)

    f_Perf = ROOT.TFile.Open(fname_perf)
    if not f_Perf or f_Perf.IsZombie():
        print "ERROR: Failed to open file %s for reading" %fname_perf
        sys.exit(1)
    f_true = ROOT.TFile.Open(fname_true)
    if not f_true or f_true.IsZombie():
        print "ERROR: Failed to open file %s for reading" %fname_true
        sys.exit(1)
        
    #=============================================================================
    # Create TGraph variables
    #=============================================================================
    x     = []
    x_err = []
    y     = []
    y_err = []
        
    #=============================================================================
    # Loop over the different DLL cuts
    #=============================================================================
    f_Perf.cd()
    hnames = [key.GetName() for key in ROOT.gDirectory.GetListOfKeys() if key.GetName().startswith(PartName+"_"+DLLVar) and key.GetName().endswith("_All")]

    for iname, hname in enumerate(hnames):        
            
        #=============================================================================
        # Obtain Performance histograms
        #=============================================================================
        PerfHist = f_Perf.Get(hname)
        if not PerfHist:
            print "ERROR: Failed to retrieve histogram %s from file %s" %(hname,
                                                                          fname_Perf)
            sys.exit(1)
        
        #=============================================================================
        # Create instance of MultiTrackCalibTool
        #=============================================================================
        openmode = "RECREATE" if not opts.appendOutput else "UPDATE"
        # only open the file in RECREATE mode the first time
        if iname!=0:
            openmode="UPDATE"

        print "================================================"
        print "Evaluating efficiencies for PID cut %d" %iname
        print "================================================"

        CalibTool = gbl.MultiTrackCalibTool("SystTool_%s" %(hname[0:-4]), t_Ref,
                                            fname_out, openmode)
        # ROOT.SetOwnership(CalibTool, False)
        #ROOT.SetOwnership(CalibTool, True)

        #=============================================================================
        # Declare the name in the reference TTree for the various binning variables
        #=============================================================================
        CalibTool.SetTrackEtaVarName('TRACK_Eta')
        CalibTool.SetTrackMomVarName('P')
        CalibTool.SetTrackNTrackVarName('nTracks')

        #=============================================================================
        # Declare the name in the reference TTree of each track to be considered and
        # the PID performance histogram to be associated with 
        #=============================================================================
        CalibTool.DeclareSignalTrackAndPerfHist(PartName, PerfHist);

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

        #=============================================================================
        # Compare with 'true' efficiency 
        #=============================================================================        
        h_true = f_true.Get(hname)
        if not h_true:
            print "ERROR: Failed to retrieve histogram %s from file %s" %(hname,
                                                                          fname_true)
            #del CalibTool
            sys.exit(1)
        
        print 'True event efficiency and error: (%.3f +/- %.3f)%%' %(100*h_true.GetBinContent(1,1,1),
                                                                     100*h_true.GetBinError(1,1,1))        
        print 'Difference %.4f%%' %(100*(NaiveResult.first-h_true.GetBinContent(1,1,1)))

        #=============================================================================
        # Enter into TGraph arrays
        #=============================================================================

        s_dllCut = hname[len(DLLVar)+len(PartName)+2:-4]
        dllCut = None
        try:
            dllCut = float(s_dllCut)
        except ValueError:
            print "ERROR: Invalid PID cut value %s" %s_dllCut
            #del CalibTool
            sys.exit(1)
        
        x.append(dllCut)
        x_err.append(0)
        y.append(100*(NaiveResult.first-h_true.GetBinContent(1,1,1)))
        y_err.append(100*sqrt(pow(NaiveResult.second,2) + pow(h_true.GetBinError(1,1,1),2)))

        #if opts.savePIDEffs:
        CalibTool.Write()
        
        #CalibTool.CloseFile()
        #CalibTool.Delete()
        #del CalibTool
        del CalibTool
        CalibTool=None
        
    #=============================================================================
    # Create TGraph
    #=============================================================================
    xarr = array('f',x)
    yarr = array('f',y)
    xarr_err = array('f',x_err)
    yarr_err = array('f',y_err)
    
    f_out = ROOT.TFile(fname_out, 'UPDATE')
    graph = ROOT.TGraphErrors(len(x), xarr, yarr, xarr_err, yarr_err)
    graph.SetName("SysPlot_%s_%s" %(PartName, DLLVar))
    graph.Draw()

    #======================================================================
    # Open file to write TGraph
    #======================================================================
    graph.Write()
    
    #======================================================================
    # Close file
    #======================================================================
    f_out.Close()
