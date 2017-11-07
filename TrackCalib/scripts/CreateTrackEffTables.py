from TrackCalib.Fit import *
from TrackCalib.Prepare import *
from TrackCalib.Utils import *
from TrackCalib.Plot import *
from array import array
import argparse
import sys
import os
import time
import math
from collections import defaultdict, namedtuple
import numpy as np
import ROOT

#TODO: RooFit
#TODO bad alloc

class ShowArgumentsParser(argparse.ArgumentParser):
    def error(self, message):
        sys.stderr.write('error: %s\n\n' %message)
        parser.print_usage(sys.stderr)
        sys.stderr.write('\n'+self.description)
        sys.exit(2)


if '__main__' == __name__:
    print ""
    parser = ShowArgumentsParser(
        formatter_class=argparse.RawDescriptionHelpFormatter,
        prog=os.path.basename(sys.argv[0]),
        description=("""Do the tracking efficiency fit for a given:
        a) Path to input file
        b) Method to use ("Long","T", "Velo")
        c) Data/MC
        d) Optional: Set of variables, default: P, Eta, #SPD hits, #PVs
        e) Optional: Set of 2d variables, default: P-Eta
        f) Optional: the binning scheme of set variables (<var1>:[bin list 1];<var2>:...)

        For a full list of arguments, do: 'python {0} -h'
        """).format(os.path.basename(sys.argv[0]))
        )

    ## add the positional arguments
    parser.add_argument("-v", "--verbose", action="store_true",help="increase output verbosity")

    parser.add_argument("-vROOT", "--verboseROOT", action="store_true",help="increase output verbosity and ROOT verbosity")

    parser.add_argument("-man", "--manual", action="store_true",help="manual")

    parser.add_argument("-t", "--test", action="store_true",  default = False,
                        help="Run over a smal testing sample")

    parser.add_argument('year', metavar='<year>',
                        help="Sets the year and conditions for data or MC")
    ## add the optional arguments
    parser.add_argument('-mode', metavar='<mode>', default = "", type = str,
                        help="Sets the mode to data or MC")

    #Add option for the WG produced tuples
    #parser.add_argument('-WGProduct', '--WGProduct', action="store_true", default = False,
    #                    help="Sets the mode to data produced by the WG")

    parser.add_argument('-polarity', metavar='<polarity>', default = "", type = str,
                        help="Sets the mode to be split by polarity, default merge Up and Down, options MagUp, MagDown")

    parser.add_argument('-method',metavar='<method>', default = "", type = str,
                        help="Sets the tracking efficiency method, per default all methods are used")

    parser.add_argument('-noWeight', dest='noWeight', action="store_true",  default = False,
                        help="Sets the multiplicity weight to 1 for all events")

    parser.add_argument('-weightVar', metavar='<weightVar>', default =  "nSPDHits",
                        help="Defines the weighting variable")
                        
    parser.add_argument('-maxEntries', metavar='<maxEntries>', default = 2.5e7,
                        help="Sets the maximum number of events used per method and charge. Needed to take memory consumption feasable.")

    parser.add_argument('-cuts', metavar='<cuts>', default = "", type = str,
                        help="Sets the additional cuts to be applied to the tuple")

    parser.add_argument('-matchCrit', metavar='<matchCrit>', default = "", type = str,
                        help="Sets the additional criteria to match the probe track")

    parser.add_argument('-variables', metavar='<variables>', default = "", type = str,
                        help="Sets the variables to bin tracking efficiency, default P, ETA, nPVs, nSPDHits")

    parser.add_argument('-variables2D', metavar='<variables2D>', default = "", type = str,
                        help="Sets the 2d variables to bin tracking efficiency, default P-ETA")

    parser.add_argument('-binning', metavar='<binning>', default = "", type = str,
                        help="Sets optional different binning")

    parser.add_argument('-vartitles', metavar='<vartitles>', default = "", type = str,
                        help="Sets the x-axis title of variables to plot, only needed for non-default variables")

    parser.add_argument('-simpleFit', dest='simpleFit', action="store_true",  default = False,
                        help="Simple single Gaussian fit, helpful for low statistics")

    parser.add_argument('-binnedFit', dest='binnedFit', action="store_true",  default = False,
                        help="Use binned fit, disable for small samples")

    parser.add_argument('-binsInFit', metavar='<binsInFit>', default = 100,
                        help="Sets the number of bins for the binned fit")

    parser.add_argument('-simFit', dest='simFit', action="store_false",  default = True, #type = bool,
                        help="Use a simultaneous fit to matched and failed events, default True, disable for small samples")

    parser.add_argument('-simVer', metavar='<simVer>', default = "Sim09b", type = str,
                        help="Sets the Sim version for MC, default: Sim09b")

    parser.add_argument('-maxError', metavar='<maxError>', default = 0.03,
                        help="Sets the maximum applicable error for tracking efficiencies. For no limit set to zero, default 0.03.")

    parser.add_argument('-maxDeviation', metavar='<maxDeviation>', default = 0.3,
                        help="Sets the maximum deviation of efficiencies from one. For no limit set to zero, default 0.3.")

    parser.add_argument('-ignoreBins', metavar='<ignoreBins>', default = "P-ETA:1-2,5-1", type = str,
                        help="Sets the given efficiency bins to 1 +- 5%, default P-ETA:1-2,5-1")

    #optional arguments to only execute separate algorithms
    parser.add_argument('--Prepare', dest='onlyPrepare', action='store_true',
                        help="Only execute Prepare script, adding cuts and reducing the tuple to a managable size")
    parser.set_defaults(onlyPrepare=False)
    parser.add_argument('--Fit', dest='onlyFit', action='store_true',
                        help="Only execute the fit script")
    parser.set_defaults(onlyFit=False)
    parser.add_argument('--Plot', dest='onlyPlot', action='store_true',
                        help="Only create plots, useful if you just want to update labels")
    parser.set_defaults(onlyPlot=False)

    opts = parser.parse_args()

    year = opts.year
    simVer = opts.simVer
    variables = opts.variables
    verbose = opts.verbose
    verboseROOT = opts.verboseROOT
    test = opts.test
    polarity = opts.polarity
    simpleFit = opts.simpleFit
    simFit = opts.simFit
    WGProduct = False

    if test:
        WarnMsg("Testing! Running only over small sample!")
        simpleFit = True
        simFit = False
        verbose = True
    if simpleFit:
        InfoMsg("Simple single Gaussian fit, helpful for low statistics")
    if not simFit:
        InfoMsg("Not using a simultaneous fit to matched and failed events, disable for small samples")

    #Make ROOT shut up
    ROOT.gErrorIgnoreLevel  = ROOT.kFatal
    if verbose: ROOT.gErrorIgnoreLevel = 2001 #=kWarning
    if verboseROOT:
        verbose = True
        ROOT.gErrorIgnoreLevel = 1001 #=kInfo

    #define which modes to prepare tuple/run fits, default: MC and Data
    mode_list = ["MC","Data"] if opts.mode == "" else [opts.mode]

    #define which methods to run fits and plot effs/tables, default: Long, T, and Velo
    if opts.method == "": method_list = ["Long","Velo","T"]
    else: method_list = opts.method.split(",")

    #check options for validity
    year_list = ["2015_50ns", "2015_25ns", "2015_5TeV", "2016_25ns"]
    year_string = year_list[0]
    for i in range(len(year_list)-1):
        year_string += ", "+year_list[i+1]

    if year not in year_list:
        ErrorMsg("Unknown year/condition "+year+" specified, must be one of "+year_string+"! Stopping execution.")
        exit()

    #dictionary of sim versions available for each condition
    sim_dict = {
            "2015_50ns": ["Sim08h", "Sim09b"],
            "2015_25ns": ["Sim09a", "Sim09b"],
            "2015_5TeV": ["Sim09a", "Sim09b"],
            "2016_25ns": ["Sim09a", "Sim09b"],
            }
    sim_string = sim_dict[year][0]
    for i in range(len(sim_dict[year])-1):
        sim_string += ", "+sim_dict[year][i+1]

    if "MC" in mode_list and simVer not in sim_dict[year]:
        WarnMsg("Unknown Sim version "+simVer+" specified, must be one of "+sim_string+"! Will use Sim09b as default.")
        WarnMsg("If other Sim version requested, please repeat the MC processing by specifying a valid version and setting '-mode MC'")
        simVer = "Sim09b"

    if opts.mode not in ["", "Data","MC"]:
        parser.error(ErrorMsg('Invalid mode %s given, must be "Data" or "MC"!' %opts.mode)) ### TODO: can I change it to errorMsg and exit()?

    if polarity not in ["", "MagUp","MagDown"]:
        parser.error(ErrorMsg('Invalid polarity %s given, must be "MagUp" or "MagDown"!' %opts.mode)) ### TODO: can I change it to errorMsg and exit()?

    if opts.method not in ["", "Long","T","Velo"]:
        parser.error(ErrorMsg('Invalid method %s given, must be "Long", "T" or "Velo"!' %opts.method))

    #check if only a certain step is requested

    if opts.onlyPrepare:
        #run prepare script, using additional cuts, tightening of the matched criterion, and reweighting MC
        for mode in mode_list:
            Prepare(mode, WGProduct, year, test = test, method=opts.method,variables = variables, noWeight =  opts.noWeight, matchCrit = opts.matchCrit, cuts = opts.cuts, simVer = simVer, weightVar = opts.weightVar,  verbose=verbose, maxEntries = opts.maxEntries)

    elif opts.onlyFit:
        for mode in mode_list:
            for meth in method_list:
                Fit(meth, mode, WGProduct, year, simVer=simVer, polarity = polarity, verbose=verbose, variables=variables, variables2D=opts.variables2D, binning=opts.binning, simpleFit=opts.simpleFit, simFit=opts.simFit, matchCrit = opts.matchCrit, binnedFit = opts.binnedFit, nBins = opts.binsInFit)

    elif opts.onlyPlot:
        Plot(year,  WGProduct, method=opts.method, simVer=simVer, polarity = polarity, variables=variables, vartitles=opts.vartitles, verbose=verbose, matchCrit = opts.matchCrit, maxError = opts.maxError, maxDeviation = opts.maxDeviation, ignoreBins = opts.ignoreBins)

    #if no script is specified, do the whole thing
    else:
        #run prepare script, using additional cuts, tightening of the matched criterion, and reweighting MC
        for mode in mode_list:
            Prepare(mode, WGProduct, year, test = test, method=opts.method,variables = variables, noWeight =  opts.noWeight, matchCrit = opts.matchCrit, cuts = opts.cuts, simVer = simVer, weightVar = opts.weightVar,  verbose=verbose, maxEntries = opts.maxEntries)

        for mode in mode_list:
            for meth in method_list:
                Fit(meth, mode, WGProduct, year, simVer=simVer, polarity = polarity, verbose=verbose, variables=variables, variables2D=opts.variables2D, binning=opts.binning, simpleFit=opts.simpleFit, simFit=opts.simFit, matchCrit = opts.matchCrit, binnedFit = opts.binnedFit, nBins = opts.binsInFit)

        Plot(year, WGProduct,method=opts.method, simVer=simVer, polarity = polarity, variables=variables, vartitles=opts.vartitles, verbose=verbose, matchCrit = opts.matchCrit, maxError = opts.maxError, maxDeviation = opts.maxDeviation, ignoreBins = opts.ignoreBins)
