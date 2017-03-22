#!/bin/sh
# -*- mode: python; coding: utf-8 -*-
# vim: ft=python:sw=4:tw=78:expandtab 
# --------------------------------------------------------------------------- 
# @file BootstrapMC.py
#
# @brief Tool to "bootstrap" or "resample"
#        a MC sample 
#
# @author Vincenzo Battista
# @date 2017-02-08
#
# --------------------------------------------------------------------------- 
# This part is run by the shell. It does some setup which is convenient to save
# work in common use cases.
# make sure the environment is set up properly
""":"
if test -n "$CMTCONFIG" \
         -a -f $B2DXFITTERSROOT/$CMTCONFIG/libB2DXFittersDict.so \
     -a -f $B2DXFITTERSROOT/$CMTCONFIG/libB2DXFittersLib.so; then
    # all ok, software environment set up correctly, so don't need to do 
    # anything
    true
else
    if test -n "$CMTCONFIG"; then
    # clean up incomplete LHCb software environment so we can run
    # standalone
        echo Cleaning up incomplete LHCb software environment.
        PYTHONPATH=`echo $PYTHONPATH | tr ':' '\n' | \
            egrep -v "^($User_release_area|$MYSITEROOT/lhcb)" | \
            tr '\n' ':' | sed -e 's/:$//'`
        export PYTHONPATH
        LD_LIBRARY_PATH=`echo $LD_LIBRARY_PATH | tr ':' '\n' | \
            egrep -v "^($User_release_area|$MYSITEROOT/lhcb)" | \
            tr '\n' ':' | sed -e 's/:$//'`
        export LD_LIBRARY_PATH
        exec env -u CMTCONFIG -u B2DXFITTERSROOT "$0" "$@"
    fi
    # automatic set up in standalone build mode
    if test -z "$B2DXFITTERSROOT"; then
        cwd="$(pwd)"
        # try to find from where script is executed, use current directory as
        # fallback
        tmp="$(dirname $0)"
        tmp=${tmp:-"$cwd"}
        # convert to absolute path
        tmp=`readlink -f "$tmp"`
        # move up until standalone/setup.sh found, or root reached
        while test \( \! -d "$tmp"/standalone \) -a -n "$tmp" -a "$tmp"\!="/"; do
            tmp=`dirname "$tmp"`
        done
        if test -d "$tmp"/standalone; then
            cd "$tmp"/standalone
            . ./setup.sh
        else
            echo `basename $0`: Unable to locate standalone/setup.sh
            exit 1
        fi
        cd "$cwd"
        unset tmp
        unset cwd
    fi
fi

# figure out which custom allocators are available
# prefer jemalloc over tcmalloc
for i in libjemalloc libtcmalloc; do
    for j in `echo "$LD_LIBRARY_PATH" | tr ':' ' '` \
        /usr/local/lib /usr/lib /lib; do
        for k in `find "$j" -name "$i"'*.so.?' | sort -r`; do
            if test \! -e "$k"; then
            continue
        fi
        echo adding $k to LD_PRELOAD
        if test -z "$LD_PRELOAD"; then
            export LD_PRELOAD="$k"
            break 3
        else
            export LD_PRELOAD="$LD_PRELOAD":"$k"
            break 3
        fi
    done
    done
done

# set batch scheduling (if schedtool is available)
schedtool="`which schedtool 2>/dev/zero`"
if test -n "$schedtool" -a -x "$schedtool"; then
    echo "enabling batch scheduling for this job (schedtool -B)"
    schedtool="$schedtool -B -e"
else
    schedtool=""
fi

# set ulimit to protect against bugs which crash the machine: 3G vmem max,
# no more then 8M stack
ulimit -v $((3072 * 1024))
ulimit -s $((   8 * 1024))

# trampoline into python
exec $schedtool /usr/bin/time -v env python -O "$0" - "$@"
"""
__doc__ = """ real docstring """
# -----------------------------------------------------------------------------
# Load necessary libraries
# -----------------------------------------------------------------------------
#"
import B2DXFitters
import ROOT
from ROOT import RooFit

from ROOT import *
from B2DXFitters import *
from B2DXFitters import WS
from B2DXFitters.WS import WS

from optparse import OptionParser
from math     import pi, log
from  os.path import exists
import os, sys, gc

import array
from array import array
import math

gROOT.SetBatch()

#------------------------------------------------------------------------------
#------------------------------------------------------------------------------
#------------------------------------------------------------------------------
def BootstrapMC(configName,
                inputWorkspace,
                inputFile,
                outputWorkspace,
                outputFile,
                seed,
                decay,
                sample,
                mode,
                year,
                hypo,
                merge,
                preselection,
                maxcand,
                randIndex,
                modifyAsymmBefore,
                modifyAsymmAfter,
                debug):

    myconfigfilegrabber = __import__(configName,fromlist=['getconfig']).getconfig
    myconfigfile = myconfigfilegrabber()

    print "=========================================================="
    print "BOOTSTRAPMC IS RUNNING WITH THE FOLLOWING CONFIGURATION OPTIONS"
    for option in myconfigfile :
        print option, " = ", myconfigfile[option]
    print "=========================================================="

    RooAbsData.setDefaultStorageType(RooAbsData.Tree)

    RooAbsReal.defaultIntegratorConfig().setEpsAbs(1e-7)
    RooAbsReal.defaultIntegratorConfig().setEpsRel(1e-7)
    RooAbsReal.defaultIntegratorConfig().getConfigSection('RooIntegrator1D').setCatLabel('extrapolation','Wynn-Epsilon')
    RooAbsReal.defaultIntegratorConfig().getConfigSection('RooIntegrator1D').setCatLabel('maxSteps','1000')
    RooAbsReal.defaultIntegratorConfig().getConfigSection('RooIntegrator1D').setCatLabel('minSteps','0')
    RooAbsReal.defaultIntegratorConfig().getConfigSection('RooAdaptiveGaussKronrodIntegrator1D').setCatLabel('method','21Points')
    RooAbsReal.defaultIntegratorConfig().getConfigSection('RooAdaptiveGaussKronrodIntegrator1D').setRealValue('maxSeg', 1000)

    from B2DXFitters.MDFitSettingTranslator import Translator
    mdt = Translator(myconfigfile,"MDSettings",False)
    MDSettings = mdt.getConfig()
    MDSettings.Print("v")

    ws = RooWorkspace("intWork","intWork")

    print ""
    print "========================================="
    print "Get input workspace"
    print str(inputWorkspace)
    print "from"
    print str(inputFile)
    print "========================================="
    print ""
    InputWorkspace = GeneralUtils.LoadWorkspace(TString(inputFile), TString(inputWorkspace), debug)

    print ""
    print "========================================="
    print "Create output workspace"
    print str(outputWorkspace)
    print "========================================="
    
    OutputWorkspace = RooWorkspace(outputWorkspace, outputWorkspace)

    print ""
    print "========================================="
    print "Create output file"
    print str(outputFile)
    print "========================================="
    
    OutputFile = TFile.Open(outputFile,"RECREATE")

    print ""
    print "========================================="
    print "Get dataset from:"
    print str(inputWorkspace)
    print "========================================="
    print ""

    modeTS = TString(mode)
    sampleTS = TString(sample)
    yearTS = TString(year)
    hypoTS = TString(hypo)
    decayTS = TString(decay)

    datasetTS = TString("dataSetMC_")+decayTS+TString("_")
    print "Dataset name prefix:"
    print datasetTS.Data()
    
    if merge == "pol" or merge == "both":
        sampleTS = TString("both")
    if merge == "year" or merge == "both":
        yearTS = TString("run1")

    sam = WS(ws, RooCategory("sample","sample"))
    
    from B2DXFitters.mdfitutils import getObservables as getObservables
    observ = getObservables(MDSettings, InputWorkspace, False, debug)
    data_temp = GeneralUtils.GetDataSet(InputWorkspace, observ, sam, datasetTS, sampleTS, modeTS, yearTS, hypoTS, merge, debug )
    if preselection != "":
        print "Applying following preselection to reduce dataset:"
        print preselection
        InputData_temp = RooDataSet(data_temp.GetName(), data_temp.GetTitle(), data_temp, data_temp.get(), preselection)
        print "Entries:"
        print "...before cut: " + str(data_temp.sumEntries())
        print "...after cut: " + str(InputData_temp.sumEntries())
    else:
        print "No additional preselection"
        InputData_temp = data_temp

    dataName = InputData_temp.GetName()
    InputData_temp.SetName( dataName+"_input" )
    print "Reduced dataset:"
    InputData_temp.Print("v")
    InputData_temp = WS(ws, InputData_temp)

    if modifyAsymmBefore:
        from B2DXFitters.utils import ModifyAsymmetry as ModifyAsymmetry
        InputData = ModifyAsymmetry(ws, InputData_temp, myconfigfile, dataName+"_input_asymmCorrected")
    else:
        InputData = WS(ws, InputData_temp)

    nCand = InputData.numEntries()
    if int(maxcand) > 0:
        max = int(maxcand)
    else:
        max = nCand
        
    print ""
    print "========================================="
    print "Start bootstrapping of"
    print max
    print "events with seed"
    print seed
    print "========================================="
    print ""

    OutputData_temp = WS(ws, RooDataSet(dataName+"_temp",
                                        InputData.GetTitle(),
                                        InputData.get()) )

    indexGen = TRandom3(int(seed))

    if randIndex:
        randIdx = WS(ws, RooRealVar("randIdx", "Random index", -1e+12, 1e+12 ) )
        randIdxSet = WS(ws, RooArgSet(randIdx) )
        randIdxData = WS(ws, RooDataSet("randIdxData", "randIdxData", randIdxSet) ) 
        
    print "Looping over "+str(max)+" candidates..."
    for cand in range(0, max):

        if cand % 50000 == 0:
            print "Filling row "+str(cand)+"..."

        randCand = int( indexGen.Integer( int(nCand) ) )
        theCand = InputData.get( randCand )
        OutputData_temp.add( theCand )

        if randIndex:
            randIdxSet.find("randIdx").setVal( randCand )
            randIdxData.add( randIdxSet )

    if randIndex:
        OutputData_temp.merge( randIdxData )
        OutputData_temp.SetTitle(dataName)
        
    print "Bootstrapping done!"
    print "New dataset entries:"
    print OutputData_temp.numEntries()
    print "New dataset:"
    OutputData_temp.Print("v")

    if modifyAsymmAfter:
        from B2DXFitters.utils import ModifyAsymmetry as ModifyAsymmetry
        OutputData = ModifyAsymmetry(ws, OutputData_temp, myconfigfile, dataName)
    else:
        OutputData = OutputData_temp

    OutputData.SetName(dataName)
    OutputData = WS(ws, OutputData)

    print ""
    print "========================================="
    print "Save output workspace"
    print str(outputWorkspace)
    print "in"
    print str(outputFile)
    print "========================================="
    print ""
    
    getattr(OutputWorkspace, 'import')(OutputData.get())
    getattr(OutputWorkspace, 'import')(OutputData)
    OutputWorkspace.Print("v")
    OutputWorkspace.writeToFile(outputFile)

    tree = OutputData.tree()
    tree.SaveAs("TheTestTree.root")
    
#-----------------------------------------------------------------------------

_usage = '%prog [options]'

parser = OptionParser( _usage )

parser.add_option( '--configName',
                   dest = 'configName',
                   default = 'MyConfigFile',
                   help = 'configuration file name'
                   )
parser.add_option( '--inputWorkspace',
                   dest = 'inputWorkspace',
                   default = 'workspace',
                   help = 'input workspace to take the input dataset from'
                   )
parser.add_option( '--inputFile',
                   dest = 'inputFile',
                   default = 'MyInputFile.root',
                   help = 'input workspace to take the input workspace/dataset from'
                   )
parser.add_option( '--outputWorkspace',
                   dest = 'outputWorkspace',
                   default = 'workspace',
                   help = 'output workspace to save the bootstrapped dataset'
                   )
parser.add_option( '--outputFile',
                   dest = 'outputFile',
                   default = 'MyOutputFile.root',
                   help = 'output workspace to save the output workspace/dataset'
                   )
parser.add_option( '--seed',
                   dest = 'seed',
                   default = 193627,
                   help = 'seed for generation'
                   )
parser.add_option( '--decay',
                   dest = 'decay',
                   metavar = 'DECAY',
                   default = 'Bd2DPi',
                   help = 'Decay channel'
                   )
parser.add_option( '-p', '--pol','--polarity',
                   dest = 'pol',
                   metavar = 'POL',
                   default = 'down',
                   help = 'Sample: choose up or down '
                   )
parser.add_option( '-m', '--mode',
                   dest = 'mode',
                   metavar = 'MODE',
                   default = 'kkpi',
                   help = 'Mode: choose all, kkpi, kpipi, pipipi, nonres, kstk, phipi, 3modeskkpi'
                   )
parser.add_option( '--merge',
                   dest = 'merge',
                   default = "",
                   help = 'for merging magnet polarities use: --merge pol, for merging years of data taking use: --merge year, for merging both use: --merge both'
                   )
parser.add_option( '--year',
                   dest = 'year',
                   default = "",
                   help = 'year of data taking can be: 2011, 2012, run1')
parser.add_option( '--hypo',
                   dest = 'hypo',
                   default = "",
                   help = 'bachelor mass hypothesys (leave empty if not used)')
parser.add_option( '--preselection',
                   dest = 'preselection',
                   default = "",
                   help = 'additional preselection to apply on dataset'
                   )
parser.add_option( '--maxcand',
                   dest = 'maxcand',
                   default = "-1",
                   help = 'maximum number of candidates (if <0 take all candidates)')
parser.add_option( '--randIndex',
                   action = 'store_true',
                   dest = 'randIndex',
                   default = False,
                   help = 'store all random cand numbers used in bootstrapping'
                   )
parser.add_option( '--modifyAsymmBefore',
                   action = 'store_true',
                   dest = 'modifyAsymmBefore',
                   default = False,
                   help = 'modify asymmetries between pairs of selected categories before bootstrapping'
                   )
parser.add_option( '--modifyAsymmAfter',
                   action = 'store_true',
                   dest = 'modifyAsymmAfter',
                   default = False,
                   help = 'modify asymmetries between pairs of selected categories after bootstrapping'
                   )
parser.add_option( '-d', '--debug',
                   action = 'store_true',
                   dest = 'debug',
                   default = False,
                   help = 'print debug information while processing'
                   )

# -----------------------------------------------------------------------------

if __name__ == '__main__' :
    (options, args) = parser.parse_args()

    if len(args) > 0 :
        parser.print_help()
        exit(-1)

    config = options.configName
    last = config.rfind("/")
    directory = config[:last+1]
    configName = config[last+1:]
    p = configName.rfind(".")
    configName = configName[:p]

    import sys
    sys.path.append(directory)
    
    BootstrapMC(configName,
                options.inputWorkspace,
                options.inputFile,
                options.outputWorkspace,
                options.outputFile,
                options.seed,
                options.decay,
                options.pol,
                options.mode,
                options.year,
                options.hypo,
                options.merge,
                options.preselection,
                options.maxcand,
                options.randIndex,
                options.modifyAsymmBefore,
                options.modifyAsymmAfter,
                options.debug)

# -----------------------------------------------------------------------------
