from PIDPerfScripts.startscreen import *
from PIDPerfScripts.RunRangeFuncs import *
from PIDPerfScripts.PerfResults import *

import ROOT
#ROOT.gSystem.Load('libRooStats.so')

import sys
#import getopt
import argparse

class ShowArgumentsParser(argparse.ArgumentParser):
    def error(self, message):
        sys.stderr.write('error: %s\n\n' %message)
        parser.print_usage(sys.stderr)
        sys.stderr.write('\n'+self.description)
        sys.exit(2)

if __name__=='__main__':
    start()
    print ""

    parser = ShowArgumentsParser(
        formatter_class=argparse.RawDescriptionHelpFormatter,
        prog=os.path.basename(sys.argv[0]),
        description=("""Make histograms of PID performance and misID rate vs. """
        """momentum (alternatively vs. pt, eta or nTracks) for a given:
        a) Stripping version <stripVersion> (e.g. \"20\")
        b) magnet polarity  <magPol> (\"MagUp\" or \"MagDown\")
        c) particle type <partName> (\"K\", \"P\", \"Pi\", \"e\" or \"Mu\")
        d) DLL or ProbNN cut <pidCut>
Multiple PID cuts can be specified if necessary, e.g. \"[DLLK > 0.0, DLLK > 4.0]\".
In this case, a performance plot will be produced for each PID cut.

For a full list of arguments, do: 'python {0} -h'
e.g. python {0}  --minRun=114205 --maxRun=114287 \"20\" \"MagUp\" \"K\" \\
    \"Pi\" \"[DLLK > 0.0, DLLK > 4.0 && DLLpK < 0.0]\"
""").format(os.path.basename(sys.argv[0])),
        epilog = ("""To use the 'MuonUnBiased' hadron samples """
                  """for muon misID studies, one of the following """
                  """track types should be used instead: """
                  """\"K_MuonUnBiased\", \"Pi_MuonUnBiased\""""
                  """or \"P_MuonUnBiased\".""")
        )

    ## add the positional arguments
    parser.add_argument('stripVersion', metavar='<stripVersion>',
                        help="Sets the stripping version")
    parser.add_argument('magPol', metavar='<magPol>',
                        help="Sets the magnet polarity")
    parser.add_argument('partName', metavar='<partName>',
                        help="Sets the particle type")
    #parser.add_argument('misIDPartName', metavar='<misIDPartName>',
                        #help="Sets the misidentified particle type")
    parser.add_argument('pidCut', metavar='<pidCut>',
                        help="Sets the PID cut(s)")

    ## add the optional arguments
    parser.add_argument('-x', '--minRun', dest="runMin", metavar="NUM",
                        help="Sets the minimum run number to process (if applicable)")
    parser.add_argument('-y', '--maxRun', dest="runMax", metavar="NUM",
                        help="Sets the maximum run number to process (if applicable)")
    parser.add_argument('-c', '--cuts', dest='cuts', metavar='CUTS', default='',
                        help=("Sets the list of cuts to apply to the calibration "
                              "sample(s) prior to determine the PID efficiencies "
                              "(default: (default)s)"))
    parser.add_argument('-n', '--varName', dest='varName', metavar='NAME',
                        default='P',
                        help=("Sets the NAME of the PID performance variable "
                              "(default: %(default)s)"))
    parser.add_argument("-o", "--outputDir", dest="outputDir", metavar="DIR",
                        help="Save the performance histograms to directory DIR "
                        "(default: current directory)")

    binGroup = parser.add_argument_group("binning options")
    binGroup.add_argument("-s", "--schemeName", dest="schemeName", metavar="NAME",
                          default=None,
                          help="Sets the NAME of the binning scheme, "
                          "as defined in the module 'PIDPerfScripts.binning'. "
                          "If this option is not set, the default 'PerfPlots'"
                          "binning scheme is used.")

    binGroup.add_argument("-b", "--binSchemeFile", dest="binSchemeFile",
                          metavar="NAME", default=None,
                          help="Sets the NAME of the python file containing "
                          "user-defined binning schema. Without this option, "
                          "the script will only look for binning schema in "
                          "the 'PIDPerfScripts.binning' module")

    addGroup = parser.add_argument_group("further options")
    addGroup.add_argument("-q", "--quiet", dest="verbose", action="store_false",
                          default=True,
                          help="Suppresses the printing of verbose information")
    addGroup.add_argument("-M", "--allow-missing", dest="allowMissing",
                          action="store_true", default=False,
                          help="Allow missing calibration subsamples. "
                          "N.B. You should only use this option if requested to "
                          "do so by the PIDCalib authors")

    opts = parser.parse_args()

    StripVersion = None
    MagPolarity = None
    PartName = None
    #MisIDPartName = None
    PlotVar = None

    DLLCuts = []
    RunMin = None
    RunMax = None

    # set the stripping version
    StripVersion=opts.stripVersion
    CheckStripVer(StripVersion)

    # set the magnet polarity
    MagPolarity=opts.magPol
    CheckMagPol(MagPolarity)

    # set the particle name
    PartName=opts.partName
    CheckPartType(PartName)

    # set the misID particle name
    #MisIDPartName=opts.misIDPartName
    #CheckPartType(MisIDPartName)

    # set the plot variable
    PlotVar=opts.varName
    if not CheckCuts(opts.varName):
        parser.error("Invalid variable %s" %str(opts.varName))
    if (len(opts.cuts)>0):
        if isinstance(opts.cuts,str):
            if not CheckCuts(opts.cuts):
                parser.error("Invalid cut string %s" %str(opts.cuts))
        elif isinstance(opts.cuts,list):
            if not CheckCuts(opts.cuts.join(" ")):
                parser.error("Invalid cut string %s" %str(opts.cuts))
            
    #CheckBinVarName(PlotVar)

    # set the PID cuts
    PIDCuts = opts.pidCut

    if PIDCuts.startswith("["):
        if not PIDCuts.endswith("]"):
            parser.error("Invalid PID cut string %s" %PIDCuts)
        PIDCuts = PIDCuts[1:-1].split(',')
    elif PIDCuts.startswith("("):
        if not PIDCuts.endswith(")"):
            parser.error("Invalid PID cut string %s" %PIDCuts)
        PIDCuts = PIDCuts[1:-1].split(',')
    else:
        PIDCuts = (PIDCuts,)

    RunMin = opts.runMin
    RunMax = opts.runMax

    if RunMin is not None:
        try:
            int(RunMin)
        except ValueError:
            parser.error(
                "Argument to --minRun ('%s') is not an integer'." %RunMin)

        if RunMax is None:
            parser.error(
                "Min run was specified as %s, but no max run was given." %RunMin)

    if RunMax is not None:
        try:
            int(RunMax)
        except ValueError:
            parser.error(
                "Argument to --maxRun ('%s') is not an integer'." %RunMax)
        if RunMin is None:
            parser.error(
                "Max run was specified as %s, but no min run was given." %RunMax)

    if opts.verbose:
        print '========== Requested publication plots =========='
        print "Stripping version: {0}".format(StripVersion)
        print "Magnet polarity: {0}".format(MagPolarity)
        print "Particle name: {0}".format(PartName)
        #print "MisID particle name: {0}".format(MisIDPartName)
        print "Plot variable: {0}".format(PlotVar)
        if opts.schemeName is not None:
            print "Scheme name: {0}".format(opts.schemeName)
        if len(opts.cuts)>0:
            print "Initial cuts: {0}".format(opts.cuts)
        for icut, cut in enumerate(PIDCuts):
            print "PID cut {num:d}: {val}".format(num=icut, val=cut)
	print '===================================='

    #======================================================================
    # Get the binning scheme
    #======================================================================
    from PIDPerfScripts.binning import GetBinScheme
    if opts.binSchemeFile is not None:
        import imp
        try:
            imp.load_source('userbinning', opts.binSchemeFile)
        except IOError:
            msg="Failed to load binning scheme file '{0}'".format(
                opts.binSchemeFile)
            raise IOError(msg)
    ROOT.gSystem.Load('libRooStats.so')
    ROOT.gSystem.Load('libCintex.so')
    cintex=ROOT.Cintex
    cintex.Enable()
    if opts.schemeName is None:
        schemeName = 'PerfPlots_{IDPart}'.format(
            IDPart=PartName)
    else:
        schemeName=opts.schemeName

    BinScheme = GetBinScheme(PartName, PlotVar, schemeName)
    v_BinScheme = ROOT.vector('RooBinning*')()
    v_BinScheme.push_back(BinScheme)

    #======================================================================
    # Define dictionary to loop over
    #======================================================================
    trackDict = {
        '{IDPart}_as_{IDPart}'.format(IDPart=PartName) : {
        'TrackType' : PartName,
        'DLLCuts'   : PIDCuts,
        'Binning'   : v_BinScheme,
        'TrackCuts' : opts.cuts
        },
        }

    #======================================================================
    # Make Performance Plots
    #======================================================================
    CalcAveragePerfPlotsAndWriteToFile(trackDict,
                                       StripVersion,
                                       MagPolarity,
                                       RunMin,
                                       RunMax,
                                       opts.outputDir,
                                       opts.verbose,
                                       opts.allowMissing,
                                       schemeName)

