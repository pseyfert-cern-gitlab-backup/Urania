#!/usr/bin/env python
# --------------------------------------------------------------------------- 
# @file plotAsymmetry.py
#
# @brief Plotter for asymmetries
#
# @author Vincenzo Battista
# @date 2017-03-21
#
# Script to plot folded/unfolded asymmetries
# The input can be:
# -sWeighted data
# -Monte Carlo
# -Toy sample
# -Analytical shape (either fixed or to be fitted)
# -basically whatever...
#
# The number of components to plot is arbitrary and it's defined
# in the configfile
#
# --------------------------------------------------------------------------- 
# This file is used as both a shell script and as a Python script.
""":"
# This part is run by the shell. It does some setup which is convenient to save
# work in common use cases.

# make sure the environment is set up properly
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
#"
# -----------------------------------------------------------------------------
# Load necessary libraries
# -----------------------------------------------------------------------------
import B2DXFitters
import ROOT
from ROOT import RooFit
from ROOT import *

from B2DXFitters import *
from B2DXFitters import WS
from B2DXFitters.WS import WS

from optparse import OptionParser
import array
from array import array
import os, sys

gStyle.SetOptStat(0)
gROOT.SetBatch(True)

# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
def plotAsymmetry(configName,
                  outputplotdir,
                  nickname,
                  debug):
    
    myconfigfilegrabber = __import__(configName,fromlist=['getconfig']).getconfig
    myconfigfile = myconfigfilegrabber()

    from B2DXFitters.MDFitSettingTranslator import Translator
    mdt = Translator(myconfigfile,"MDSettings",False)
    MDSettings = mdt.getConfig()
    MDSettings.Print("v")

    print "=========================================================="
    print "PLOTASYMMETRY IS RUNNING WITH THE FOLLOWING CONFIGURATION OPTIONS"
    for option in myconfigfile :
        print option, " = ", myconfigfile[option]
    print "=========================================================="
    
    RooAbsData.setDefaultStorageType(RooAbsData.Tree)
    
    legend = TLegend(*myconfigfile["Plot"]["Legend"])

    asymmdict = None

    if "Samples" in myconfigfile.keys():

        sampledict = {}
        asymmdict = {}
        
        for comp in myconfigfile["Samples"].iterkeys():
            print "======================="
            print "Taking input sample for:"
            print comp
            print "======================="

            sampledict[comp] = {}

            if "Tree" in myconfigfile["Samples"][comp].iterkeys():
                sampledict[comp]["File"] = {}
                sampledict[comp]["File"] = TFile.Open( myconfigfile["Samples"][comp]["File"] )
                sampledict[comp]["Tree"] = {}
                sampledict[comp]["Tree"] = sampledict[comp]["File"].Get( myconfigfile["Samples"][comp]["Tree"] )
                sampledict[comp]["Tree"].SetName(comp+"Tree")
            elif "Workspace" and "Dataset" in myconfigfile["Samples"][comp].iterkeys():
                sampledict[comp]["Workspace"] = {}
                sampledict[comp]["Workspace"] = GeneralUtils.LoadWorkspace(TString(myconfigfile["Samples"][comp]["File"]), TString(myconfigfile["Samples"][comp]["Workspace"]), debug)
                sampledict[comp]["Tree"] = {}
                sampledict[comp]["Tree"] = sampledict[comp]["Workspace"].data( myconfigfile["Samples"][comp]["Dataset"] ).tree()
                sampledict[comp]["Tree"].SetName(comp+"Tree")
            elif "Workspace" and "Dataprefix" and "Decay" and "Sample" and "Mode" and "Year" and "Hypo" and "Merge" in myconfigfile["Samples"][comp].iterkeys():
                merge = myconfigfile["Samples"][comp]["Merge"]
                modeTS = TString(myconfigfile["Samples"][comp]["Mode"])
                sampleTS = TString(myconfigfile["Samples"][comp]["Sample"])
                yearTS = TString(myconfigfile["Samples"][comp]["Year"])
                hypoTS = TString(myconfigfile["Samples"][comp]["Hypo"])
                decayTS = TString(myconfigfile["Samples"][comp]["Decay"])
                datasetTS = TString(myconfigfile["Samples"][comp]["Dataprefix"])+decayTS+TString("_")

                if merge == "pol" or merge == "both":
                    sampleTS = TString("both")
                if merge == "year" or merge == "both":
                    yearTS = TString("run1")

                sam = RooCategory("sample","sample")
                sampledict[comp]["Workspace"] = {}
                sampledict[comp]["Workspace"] = GeneralUtils.LoadWorkspace(TString(myconfigfile["Samples"][comp]["File"]), TString(myconfigfile["Samples"][comp]["Workspace"]), debug)
                from B2DXFitters.mdfitutils import getObservables as getObservables
                observ = getObservables(MDSettings, sampledict[comp]["Workspace"], False, debug)
                sampledict[comp]["Tree"] = {}
                sampledict[comp]["Tree"] = GeneralUtils.GetDataSet(sampledict[comp]["Workspace"], observ, sam, datasetTS, sampleTS, modeTS, yearTS, hypoTS, merge, debug ).tree()
                sampledict[comp]["Tree"].SetName(comp+"Tree")
            else:
                print "ERROR: need to specify a Tree name or a Workspace/Dataset name in the configuration file!"
                exit(-1)

        if debug:
            print "Input samples dictionary:"
            print sampledict
    
        for comp in sampledict.iterkeys():
            print "======================="
            print "Building asymmetry plot for:"
            print comp
            print "======================="

            asymmdict[comp] = {}

            obs = myconfigfile["Samples"][comp]["Observable"]

            asymmdict[comp]["Category1"] = None
            asymmdict[comp]["Category2"] = None
            asymmdict[comp]["Asymmetry"] = None
            asymmdict[comp]["Normalisation"] = None
        
            if "Folding" in myconfigfile.keys():

                print "Producing folded asymmetry plots..."
                
                if type(myconfigfile["Plot"]["Bins"]) is list:
                    print "ERROR: cannot use variable bin size with folded asymmetries"
                    exit(-1)

                obs = "("+obs+")%"+myconfigfile["Folding"]["Modulo"]
                asymmdict[comp]["Category1"] = TH1F(comp+"_cat1",
                                                    "",
                                                    myconfigfile["Plot"]["Bins"],
                                                    myconfigfile["Plot"]["Range"][0],
                                                    myconfigfile["Folding"]["Modulo"])
                asymmdict[comp]["Category2"] = TH1F(comp+"_cat2",
                                                    "",
                                                    myconfigfile["Plot"]["Bins"],
                                                    myconfigfile["Plot"]["Range"][0],
                                                    myconfigfile["Folding"]["Modulo"])
                asymmdict[comp]["Asymmetry"] = TH1F(comp+"_asymm",
                                                "",
                                                    myconfigfile["Plot"]["Bins"],
                                                    myconfigfile["Plot"]["Range"][0],
                                                    myconfigfile["Folding"]["Modulo"])
                asymmdict[comp]["Normalisation"] = TH1F(comp+"_norm",
                                                        "",
                                                        myconfigfile["Plot"]["Bins"],
                                                        myconfigfile["Plot"]["Range"][0],
                                                        myconfigfile["Folding"]["Modulo"])
            else:

                print "Producing non-folded asymmetry plots..."
                
                if type(myconfigfile["Plot"]["Bins"]) is list:

                    print "Using variable bin size..."
                    
                    binning = array('d',myconfigfile["Plot"]["Bins"])
                    asymmdict[comp]["Category1"] = TH1F(comp+"_cat1",
                                                        "",
                                                        binning.__len__()-1,
                                                        binning)
                    asymmdict[comp]["Category2"] = TH1F(comp+"_cat2",
                                                        "",
                                                        binning.__len__()-1,
                                                        binning)
                    asymmdict[comp]["Asymmetry"] = TH1F(comp+"_asymm",
                                                        "",
                                                        binning.__len__()-1,
                                                        binning)
                    asymmdict[comp]["Normalisation"] = TH1F(comp+"_norm",
                                                            "",
                                                            binning.__len__()-1,
                                                            binning)
                else:
                    asymmdict[comp]["Category1"] = TH1F(comp+"_cat1",
                                                        "",
                                                        myconfigfile["Plot"]["Bins"],
                                                        myconfigfile["Plot"]["Range"][0],
                                                        myconfigfile["Plot"]["Range"][1])
                    asymmdict[comp]["Category2"] = TH1F(comp+"_cat2",
                                                        "",
                                                        myconfigfile["Plot"]["Bins"],
                                                        myconfigfile["Plot"]["Range"][0],
                                                        myconfigfile["Plot"]["Range"][1])
                    asymmdict[comp]["Asymmetry"] = TH1F(comp+"_asymm",
                                                        "",
                                                        myconfigfile["Plot"]["Bins"],
                                                        myconfigfile["Plot"]["Range"][0],
                                                        myconfigfile["Plot"]["Range"][1])
                    asymmdict[comp]["Normalisation"] = TH1F(comp+"_norm",
                                                            "",
                                                            myconfigfile["Plot"]["Bins"],
                                                            myconfigfile["Plot"]["Range"][0],
                                                            myconfigfile["Plot"]["Range"][1])
            

            cat1def = myconfigfile["Samples"][comp]["Category1"]
            cat2def = myconfigfile["Samples"][comp]["Category2"]

            if "Weight" in myconfigfile["Samples"][comp].keys():
                cat1def = myconfigfile["Samples"][comp]["Weight"]+"*("+cat1def+")"
                cat2def = myconfigfile["Samples"][comp]["Weight"]+"*("+cat2def+")"

            if debug:
                print "Plotting "+obs+" with cut "+cat1def
            sampledict[comp]["Tree"].Draw(obs+">>"+comp+"_cat1",cat1def,"goff")
            if debug:
                print "Plotting "+obs+" with cut "+cat2def
            sampledict[comp]["Tree"].Draw(obs+">>"+comp+"_cat2",cat2def,"goff")

            if debug:
                print "Entries:"
                print "...category 1: "+str(asymmdict[comp]["Category1"].GetEntries())
                print "...category 2: "+str(asymmdict[comp]["Category2"].GetEntries())
            
            asymmdict[comp]["Category1"].Sumw2()
            asymmdict[comp]["Category2"].Sumw2()
            asymmdict[comp]["Asymmetry"].Sumw2()
            asymmdict[comp]["Normalisation"].Sumw2()
            asymmdict[comp]["Asymmetry"].Add(asymmdict[comp]["Category1"], asymmdict[comp]["Category2"], 1.0, -1.0)
            asymmdict[comp]["Normalisation"].Add(asymmdict[comp]["Category1"], asymmdict[comp]["Category2"], 1.0, 1.0)
            #asymmdict[comp]["Asymmetry"].Divide( asymmdict[comp]["Normalisation"] )
            asymmdict[comp]["Asymmetry"].Divide( asymmdict[comp]["Asymmetry"], asymmdict[comp]["Normalisation"], 1., 1., "B" )
            asymmdict[comp]["Asymmetry"].GetXaxis().SetTitle( myconfigfile["Plot"]["TitleX"] )
            asymmdict[comp]["Asymmetry"].GetYaxis().SetTitle( myconfigfile["Plot"]["TitleY"] )
            asymmdict[comp]["Asymmetry"].GetXaxis().SetTitleSize(0.07)
            asymmdict[comp]["Asymmetry"].GetXaxis().SetLabelSize(0.06)
            asymmdict[comp]["Asymmetry"].GetYaxis().SetTitleSize(0.07)
            asymmdict[comp]["Asymmetry"].GetYaxis().SetLabelSize(0.06)
            asymmdict[comp]["Asymmetry"].GetYaxis().SetTitleOffset(0.65)
            asymmdict[comp]["Asymmetry"].GetXaxis().SetTitleOffset(0.5)
            asymmdict[comp]["Asymmetry"].SetLineColor(myconfigfile["Samples"][comp]["Color"])
            asymmdict[comp]["Asymmetry"].SetLineWidth(myconfigfile["Samples"][comp]["Width"])

            legend.AddEntry(asymmdict[comp]["Asymmetry"], myconfigfile["Samples"][comp]["Legend"], "L") 

            
    fundict = None
            
    if "Functions" in myconfigfile.keys():

        fundict = {}
        
        for func in myconfigfile["Functions"].iterkeys():

            print "======================="
            print "Building asymmetry function for:"
            print func
            print "======================="

            fundict[func] = {}
            fundict[func]["Function"] = None
            
            if "Folding" in myconfigfile.keys():

                print "Producing folded asymmetry plots..."
                
                fundict[func]["Function"] = TF1(func+"_fun",
                                                myconfigfile["Functions"][func]["Expression"],
                                                myconfigfile["Plot"]["Range"][0],
                                                myconfigfile["Folding"]["Modulo"])
            else:

                print "Producing non-folded asymmetry plots..."
                
                fundict[func]["Function"] = TF1(func+"_fun",
                                                myconfigfile["Functions"][func]["Expression"],
                                                myconfigfile["Plot"]["Range"][0],
                                                myconfigfile["Plot"]["Range"][1])

            if "FitTo" in myconfigfile["Functions"].keys():
                asymmdict[comp]["Asymmetry"].Fit(fundict[func]["Function"], "MRNWL")

            fundict[func]["Function"].GetXaxis().SetTitle( myconfigfile["Plot"]["TitleX"] )
            fundict[func]["Function"].GetYaxis().SetTitle( myconfigfile["Plot"]["TitleY"] )
            fundict[func]["Function"].GetXaxis().SetTitleSize(0.07)
            fundict[func]["Function"].GetXaxis().SetLabelSize(0.06)
            fundict[func]["Function"].GetYaxis().SetTitleSize(0.07)
            fundict[func]["Function"].GetYaxis().SetLabelSize(0.06)
            fundict[func]["Function"].GetYaxis().SetTitleOffset(0.65)
            fundict[func]["Function"].GetXaxis().SetTitleOffset(0.5)
            fundict[func]["Function"].SetLineColor(myconfigfile["Functions"][func]["Color"])
            fundict[func]["Function"].SetLineWidth(myconfigfile["Functions"][func]["Width"])
            
            legend.AddEntry(fundict[func]["Function"], myconfigfile["Functions"][func]["Legend"], "L")

        if debug:
            print "Input function dictionary:"
            print fundict

    if asymmdict != None or fundict != None:

        print "======================="
        print "Making plot"
        print "======================="

        canv = TCanvas("canv", "canv", 1600, 800)
        canv.cd()

        count = 0
        if asymmdict != None:
            for comp in asymmdict.iterkeys():
                if count == 0:
                    asymmdict[comp]["Asymmetry"].Draw("EP")
                else:
                    asymmdict[comp]["Asymmetry"].Draw("EPSAME")
                count = count+1

        if fundict != None:
            for func in fundict.iterkeys():
                fundict[func]["Function"].Draw("SAME")

        legend.Draw("SAME")

        if "Label" in myconfigfile.keys():
            txt = TLatex()
            txt.SetTextFont(132)
            txt.SetTextColor(1)
            txt.SetTextSize(0.06)
            txt.SetTextAlign(12)
            txt.SetNDC(kTRUE)
            txt.DrawLatex(myconfigfile["Label"]["X"], myconfigfile["Label"]["Y"], myconfigfile["Label"]["Text"] )

        if "Folding" in myconfigfile.keys():
            canv.SaveAs(outputplotdir+"AsymmetryPlot_"+nickname+"_Folded.pdf")
        else:
            canv.SaveAs(outputplotdir+"AsymmetryPlot_"+nickname+".pdf")

        
# -----------------------------------------------------------------------------

_usage = '%prog [options]'

parser = OptionParser( _usage )

parser.add_option( '--configName',
                   dest = 'configName',
                   default = 'MyConfigFile',
                   help = 'configuration file name'
                   )
parser.add_option( '--outputplotdir',
                   dest = 'outputplotdir',
                   default = '',
                   help = 'directory for output plots'
                   )
parser.add_option( '--nickname',
                   dest = 'nickname',
                   default = '',
                   help = 'nickname to label output plot'
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

    plotAsymmetry(configName,
                  options.outputplotdir,
                  options.nickname,
                  options.debug)

# -----------------------------------------------------------------------------
