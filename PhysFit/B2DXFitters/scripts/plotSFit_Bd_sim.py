#!/usr/bin/env python
# --------------------------------------------------------------------------- #
#                                                                             #
#   Python script to plot the Bd -> D pi time models                          #
#                                                                             #
#   Example usage:                                                            #
#      python plotBs2DsPiTimeModelsOnData.py WS_Time_DsPi.root                #
#                                                                             #
#   Author: Eduardo Rodrigues                                                 #
#   Date  : 01 / 06 / 2011                                                    #
#   Author: Agnieszka Dziurda                                                 #
#   Author: Vladimir Vava Gligorov                                            #
#                                                                             #
# --------------------------------------------------------------------------- #

# -----------------------------------------------------------------------------
# settings for running without GaudiPython
# -----------------------------------------------------------------------------
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

# set ulimit to protect against bugs which crash the machine: 2G vmem max,
# no more then 8M stack
ulimit -v $((2048 * 1024))
ulimit -s $((   8 * 1024))

# trampoline into python
exec $schedtool /usr/bin/time -v env python -O -- "$0" "$@"
"""
__doc__ = """ real docstring """
# -----------------------------------------------------------------------------
# Load necessary libraries
# -----------------------------------------------------------------------------
#"
from B2DXFitters import *
from ROOT import *

from ROOT import RooFit
from optparse import OptionParser
from math     import pi, log
from  os.path import exists
import os, sys, gc
gROOT.SetBatch()
#gROOT.ProcessLine(".x ../root/.rootlogon.C")

# MODELS
signalModelOnly = True

# PLOTTING CONFIGURATION
plotData  =  True
plotModel =  True

#------------------------------------------------------------------------------
def plotDataSet(dataset, frame, bin) :
    dataset.plotOn(frame,RooFit.Binning(bin),
                   RooFit.DataError(RooAbsData.SumW2),
                   RooFit.Name("dataSetCut"))

#------------------------------------------------------------------------------
def plotFitModel(model, frame, wksp, myconfigfile, log, sample, debug) :
    if debug :
        model.Print('t')
        frame.Print('v')

    fr = model.plotOn(frame,
                      RooFit.LineColor(kBlue+3),
                      RooFit.Name("FullPdf"))

    if "Acceptance" in myconfigfile.keys():
        var = []
        tacc_list = RooArgList()
        numKnots = myconfigfile["Acceptance"]["knots"].__len__()
        for i in range(0,numKnots+1):
            varName = "var%d"%(int(i+1))
            var.append(wksp.var(varName))
            print "[INFO] Load %s with value %0.3lf"%(var[i].GetName(),var[i].getValV())
            tacc_list.add(var[i])

        varAdd = RooAddition(wksp.obj("var%d"%(numKnots+2)))
        print "[INFO] Load %s with value %0.3lf"%(varAdd.GetName(),varAdd.getValV())
        tacc_list.add(varAdd)

    elif "ResolutionAcceptance" in myconfigfile.keys():
        #Create acceptance
        var = []
        tacc_list = RooArgList()
        numKnots = myconfigfile["ResolutionAcceptance"]["Signal"]["Acceptance"]["KnotPositions"].__len__()
        print "[INFO] Number of knots: "+str(numKnots)
        for i in range(0,numKnots+1):
            if i!=6:
                varName = "acc"+sample+"_SplineAccCoeff%d"%(int(i))
                var.append(wksp.obj(varName))
                print "[INFO] Load %s with value %0.3lf"%(var[i].GetName(),var[i].getValV())
            else:
                var.append( RooConstVar("one","one",1.0) )
                print "[INFO] Load one as coefficient no. 6"
                            
            tacc_list.add(var[i])

        varName = "acc"+sample+"_SplineAccCoeff%d"%(int(numKnots+1))
        var.append(wksp.obj(varName))
        print "[INFO] Load %s with value %0.3lf"%(var[numKnots+1].GetName(),var[numKnots+1].getValV())
        tacc_list.add(var[numKnots+1])

        #Create binning
        binning = RooBinning(time.getMin(), time.getMax(), 'splineBinning')
        for kn in myconfigfile["ResolutionAcceptance"]["Signal"]["Acceptance"]["KnotPositions"]:
            binning.addBoundary(kn)
        binning.removeBoundary(time.getMin())
        binning.removeBoundary(time.getMax())
        binning.removeBoundary(time.getMin())
        binning.removeBoundary(time.getMax())
        oldBinning, lo, hi = time.getBinning(), time.getMin(), time.getMax()
        time.setBinning(binning, 'splineBinning')
        time.setBinning(oldBinning)
        time.setRange(lo, hi)

    spl = RooCubicSplineFun("splinePdf", "splinePdf", time, "splineBinning", tacc_list)
    if log:
        rel = 200
    else:
        #rel = 1000
        rel = 200
        
    fr = spl.plotOn(frame, RooFit.LineColor(kRed),  RooFit.Normalization(rel, RooAbsReal.Relative),RooFit.Name("sPline"))
    fr = model.plotOn(frame,
                          RooFit.LineColor(kBlue+3), RooFit.Name("FullPdf"))
            
#------------------------------------------------------------------------------
#------------------------------------------------------------------------------

def getDescription(decay):

    happystar = "#lower[-0.95]{#scale[0.5]{(}}#lower[-0.8]{#scale[0.5]{*}}#lower[-0.95]{#scale[0.5]{)}}"
    happystar2 = "#lower[-0.65]{#scale[0.6]{*}}"
    happypm   = "#lower[-0.95]{#scale[0.6]{#pm}}"
    happymp   = "#lower[-0.95]{#scale[0.6]{#mp}}"
    happystarpm = "#lower[-0.95]{#scale[0.6]{*#pm}}"
    happyplus = "#lower[-0.95]{#scale[0.6]{+}}"
    happymin  = "#lower[-1.15]{#scale[0.7]{-}}"
    happy0   = "#lower[-0.85]{#scale[0.6]{0}}"

    from B2DXFitters import TLatexUtils    
    if decay == "Bs2DsPi":
        desc = "B_{s}#kern[-0.7]{"+happy0+"}#rightarrow D_{s}#kern[-0.3]{"+happymin+"}#kern[0.1]{#pi"+happyplus+"}"
    elif decay == "Bs2DsK":
        desc = "B_{s}#kern[-0.7]{"+happy0+"} #rightarrow D_{s}#kern[-0.3]{"+happymp+"}#kern[0.1]{K"+happypm+"}"
    elif decay == "Bs2DsstPi":
        desc = "B_{s}#kern[-0.7]{"+happy0+"}#rightarrow D_{s}#kern[-0.3]{"+happystar+happymin+"}#kern[0.1]{#pi"+happyplus+"}"
    elif decay == "Bs2DsstK":
        desc = "B_{s}#kern[-0.7]{"+happy0+"} #rightarrow D_{s}#kern[-0.3]{"+happystar+happymp+"}#kern[0.1]{K"+happypm+"}"
    elif decay == "Bd2DPi":
        desc = "B_{d}#kern[-0.7]{"+happy0+"} #rightarrow D#kern[-0.3]{"+happymp+"}#kern[0.1]{#pi"+happypm+"}"
    else:
        desc = "Signal" 

    return desc

#------------------------------------------------------------------------------
def legends(model, frame):
    stat = frame.findObject('data_statBox')
    prefix = 'Sig' if signalModelOnly else 'Tot'
    if not stat: stat = frame.findObject('%sEPDF_tData_statBox' % prefix)
    if stat :
        stat.SetTextSize(0.025)
    pt = frame.findObject('%sEPDF_t_paramBox' % prefix)
    if pt :
        pt.SetTextSize(0.02)
    # Legend of EPDF components
    leg = TLegend(0.56, 0.42, 0.87, 0.62)
    leg.SetFillColor(0)
    leg.SetTextSize(0.02)
    comps = model.getComponents()

    if signalModelOnly :
        pdfName = 'SigEPDF_t'
        pdf = comps.find(pdfName)
        curve = frame.findObject(pdfName + '_Norm[time]')
        if curve : leg.AddEntry(curve, pdf.GetTitle(), 'l')
        return leg, curve
    else :
        pdf1 = comps.find('SigEPDF_t')
        pdfName = 'TotEPDF_t_Norm[time]_Comp[%s]' % 'SigEPDF_t'
        curve1 = frame.findObject(pdfName)
        if curve1 : leg.AddEntry(curve1, pdf1.GetTitle(), 'l')
        pdf = comps.find('Bd2DKEPDF_t')
        pdfName = 'TotEPDF_t_Norm[time]_Comp[%s]' % 'Bd2DKEPDF_t'
        curve2 = frame.findObject(pdfName)
        if curve2 : leg.AddEntry(curve2, pdf.GetTitle(), 'l')
        pdf = comps.find('CombBkgEPDF_t')
        pdfName = 'TotEPDF_t_Norm[time]_Comp[%s]' % 'CombBkgEPDF_t'
        curve3 = frame.findObject(pdfName)
        if curve3 : leg.AddEntry(curve3, pdf.GetTitle(), 'l')
        pdfName = 'TotEPDF_t_Norm[time]_Comp[%s]' % 'CombBkgEPDF_t,Bd2DKEPDF_t'
        curve4 = frame.findObject(pdfName)
        if curve4 :
            leg.AddEntry(curve4, 'All but %s' % pdf1.GetTitle(), 'f')
            curve4.SetLineColor(0)
        pdfName = 'TotEPDF_t_Norm[time]'
        pdf = comps.find('TotEPDF_t')
        curve5 = frame.findObject(pdfName)
        #if curve5 : leg.AddEntry(curve5, pdf.GetTitle(), 'l')
        if curve5 : leg.AddEntry(curve5, 'Model (signal & background) EPDF', 'l')
        return leg, curve4

#------------------------------------------------------------------------------
_usage = '%prog [options] <filename>'

parser = OptionParser(_usage)

parser.add_option('-w', '--workspace',
                   dest = 'wsname',
                   metavar = 'WSNAME',
                   default = 'workspace',
                   help = 'RooWorkspace name as stored in ROOT file'
)

parser.add_option( '-s', '--sufix',
                   dest = 'sufix',
                   metavar = 'SUFIX',
                   default = '',
                   help = 'Add sufix to output'
                   )

parser.add_option( '--plotLabel',
                   dest = 'plotLabel',
                   metavar = 'PLOTLABEL',
                   default = 'LHCb',
                   help = 'Plot label'
                   )

parser.add_option( '--sample',
                   dest = 'sample',
                   metavar = 'SAMPLE',
                   default = '2011OS',
                   help = 'category to plot'
                   )

parser.add_option( '--configName',
                    dest = 'configName',
                    default = 'Bs2DsPiConfigForNominalDMSFit')

parser.add_option( '--bin',
                   dest = 'bin',
                   default = 148,
                   help = 'set number of bins'
                   )

parser.add_option( '--logscale', '--log',
                   dest = 'log',
                   action = 'store_true',
                   default = False,
                   help = 'log scale of plot'
                   )
parser.add_option( '--legend',
                   dest = 'legend',
                   action = 'store_true',
                   default = False,
                   help = 'plot legend on the plot'
                   )

parser.add_option( '-v', '--variable', '--var',
                   dest = 'var',
                   default = 'BeautyTime',
                   help = 'set observable '
                   )

parser.add_option( '--outdir',
                   dest = 'outdir',
                   default = '',
                   help = 'directory to save plots'
                   )

parser.add_option( '--dataSetToPlot',
                   dest = 'dataSetToPlot',
                   default = 'dataSet_time_weighted',
                   help = 'name of RooDataSet to plot'
                   )

parser.add_option( '--pdfToPlot',
                   dest = 'pdfToPlot',
                   default = 'time_signal',
                   help = 'name of pdf to plot'
                   )

parser.add_option( '--debug',
                   dest = 'debug',
                   action = 'store_true',
                   default = False,
                   help = 'verbose output'
                   )

#------------------------------------------------------------------------------

if __name__ == '__main__' :
    (options, args) = parser.parse_args()

    if len(args) != 1 :
        parser.print_help()
        exit(-1)

    FILENAME = (args[ 0 ])
    if not exists(FILENAME) :
        parser.error('ROOT file "%s" not found! Nothing plotted.' % FILENAME)
        parser.print_help()

    RooAbsReal.defaultIntegratorConfig().setEpsAbs(1e-13)
    RooAbsReal.defaultIntegratorConfig().setEpsRel(1e-13)
    RooAbsReal.defaultIntegratorConfig().getConfigSection('RooAdaptiveGaussKronrodIntegrator1D').setCatLabel('method','21Points')
    RooAbsReal.defaultIntegratorConfig().getConfigSection('RooAdaptiveGaussKronrodIntegrator1D').setRealValue('maxSeg', 1000)
    # since we have finite ranges, the RooIntegrator1D is best suited to the job
    RooAbsReal.defaultIntegratorConfig().method1D().setLabel('RooAdaptiveGaussKronrodIntegrator1D')
    
    from ROOT import kYellow, kMagenta, kOrange, kCyan, kGreen, kRed, kBlue, kDashed, kBlack
    from ROOT import RooRealVar, RooStringVar, RooFormulaVar, RooProduct
    from ROOT import RooCategory, RooMappedCategory, RooConstVar
    from ROOT import RooArgSet, RooArgList, RooGaussian, RooTruthModel, RooDecay
    from ROOT import RooAddPdf, RooProdPdf, RooExtendPdf, RooGenericPdf, RooAbsReal
    from ROOT import RooFit, FitMeTool, TGraph, TPad, gStyle
    from ROOT import CombBkgPTPdf
    from ROOT import RooBlindTools

    gROOT.SetStyle('Plain')
    #gROOT.SetBatch(False)

    bin = int(options.bin)
    log = options.log
    leg = options.legend
    v = options.var
    varTS = TString(v)
    sample = options.sample

    config = options.configName
    last = config.rfind("/")
    directory = config[:last+1]
    configName = config[last+1:]
    p = configName.rfind(".")
    configName = configName[:p]

    import sys
    sys.path.append(directory)

    myconfigfilegrabber = __import__(configName,fromlist=['getconfig']).getconfig
    myconfigfile = myconfigfilegrabber()

    print "=========================================================="
    print "PREPARING WORKSPACE IS RUNNING WITH THE FOLLOWING CONFIGURATION OPTIONS"
    for option in myconfigfile :
        if option == "constParams" :
            for param in myconfigfile[option] :
                print param, "is constant in the fit"
        else :
            print option, " = ", myconfigfile[option]
    print "=========================================================="

    sfx = options.sufix
    out = options.outdir

    sufixTS = TString(sfx)
    outTS = TString(out)

    f = TFile(FILENAME)

    w = f.Get(options.wsname)
    if not w :
        parser.error('Workspace "%s" not found in file "%s"! Nothing plotted.' %\
                      (options.wsname, FILENAME))
    else:
        print "Workspace content:"
        w.Print("v")

    f.Close()
    time = w.var(varTS.Data())
    time.setBins(bin) 
    #time.setRange(0.4,15)
    timeDown = time.getMin()
    timeUp = time.getMax()
    #time.setRange(timeDown,timeUp)   
 
    modelPDF = w.obj(options.pdfToPlot) 
    if modelPDF:
        print modelPDF.GetName()
    dataset_temp  = w.data(options.dataSetToPlot)
    dataset = dataset_temp.reduce( "sample==sample::"+sample ) 
    if dataset:
        print dataset.GetName()

    if not (modelPDF and dataset) :
        w.Print('v')
        exit(1)

    
    canvas = TCanvas("canvas", "canvas", 2000, 1200)
    pad1 = canvas.GetPad(0)
    pad1.SetPad(.03, .03, 1.0, 1.0)
    pad1.cd()
    pad1.SetBorderMode(0)
    pad1.SetBorderSize(-1)
    pad1.SetFillStyle(0)
    pad1.SetTickx(0);
    pad1.SetBottomMargin(0.30)
    pad1.SetLeftMargin(0.17)
    pad1.SetTopMargin(0.05)
    pad1.SetRightMargin(0.05)
    pad1.Draw()
    pad1.cd()

    time = w.var(varTS.Data())
    frame_t = time.frame()
    frame_t.SetTitle('')
 
    frame_t.GetXaxis().SetLabelSize( 0.055 )
    frame_t.GetYaxis().SetLabelSize( 0.048 )
    frame_t.GetXaxis().SetLabelFont( 132 )
    frame_t.GetYaxis().SetLabelFont( 132 )
    frame_t.GetXaxis().SetLabelOffset( 0.009 )
    frame_t.GetYaxis().SetLabelOffset( 0.007 )
    
    frame_t.GetXaxis().SetTitleSize( 0.06 )
    frame_t.GetYaxis().SetTitleSize( 0.06 )
    frame_t.GetYaxis().SetNdivisions(512)
    
    frame_t.GetXaxis().SetTitleOffset( 1.0 )
    frame_t.GetYaxis().SetTitleOffset( 1.9 )
    unit = "ps"
    frame_t.GetYaxis().SetTitle((TString.Format("#font[132]{Candidates / ( " +
                                                    "{0:0.2f}".format(time.getBinWidth(1))+" "+
                                                    unit+")}") ).Data())
    
    if not log and dataset.numEntries() > 30000:
        frame_t.GetYaxis().SetNdivisions(508)
        frame_t.GetYaxis().SetTitleOffset( 1.20 )
        frame_t.GetYaxis().SetRangeUser(1.5,frame_t.GetMaximum()*1.1)

    if plotData:
        plotDataSet(dataset, frame_t, bin)
    
    print '##### modelPDF is'
    print modelPDF
    if plotModel :
        plotFitModel(modelPDF, frame_t, w, myconfigfile, log, sample, options.debug)

    #doPulls = plotData and plotModel

    if log:
        gStyle.SetOptLogy(1)
        frame_t.GetYaxis().SetTitleOffset( 1.10 )
        frame_t.GetYaxis().SetRangeUser(1.5,frame_t.GetMaximum()*1.5)
        pad1.SetLogy()

    #legend = TLegend( 0.57, 0.68, 0.80, 0.90 )
    legend = TLegend( 0.52, 0.70, 0.75, 0.90 )
    legend.SetTextSize(0.06)
    legend.SetTextFont(12)
    legend.SetFillColor(0)
    legend.SetShadowColor(0)
    legend.SetBorderSize(0)
    legend.SetTextFont(132)
    legend.SetHeader(options.plotLabel) # L_{int}=1.0 fb^{-1}")

    gr = TGraphErrors(1);
    gr.SetName("gr");
    gr.SetLineColor(kBlack);
    gr.SetLineWidth(2);
    gr.SetMarkerStyle(20);
    gr.SetMarkerSize(1.3);
    gr.SetMarkerColor(kBlack);
    #gr.Draw("P");
    legend.AddEntry(gr,"Data","lep");

    myconfigfilegrabber = __import__(configName,fromlist=['getconfig']).getconfig
    myconfigfile = myconfigfilegrabber()

    #decay = TString(myconfigfile["Decay"])
    #descTS = TString(getDescription(myconfigfile["Decay"]))
    decay = TString(myconfigfile["Decay"])
    descTS = TString(getDescription(myconfigfile["Decay"]))
    frame_t.GetXaxis().SetTitle('#font[132]{Decay time #it{t} [ps]}')
    l1 = TLine()
    l1 = TLine()
    l1.SetLineColor(kBlue+3)
    l1.SetLineWidth(4)
    legend.AddEntry(l1, "Fit", "L")
    l2 = TLine()
    l2.SetLineColor(kRed)
    l2.SetLineWidth(4)
    legend.AddEntry(l2, "Efficiency", "L")
    
               
    frame_t.Draw()
    if leg:
        legend.Draw("same")
    
    #sufixTS = TString(sfx)
    if sufixTS != "":
        sufixTS = TString("_")+sufixTS

    #outTS = TString(out)
    head = TString("time_")
    if log:
        head = head+TString("log_")
    
    nameCanPdf = outTS+head+decay+sufixTS+TString(sample)+TString(".pdf")
    nameCanPng = outTS+head+decay+sufixTS+TString(sample)+TString(".png")
    nameCanRoot = outTS+head+decay+sufixTS+TString(sample)+TString(".root")
    nameCanC = outTS+head+decay+sufixTS+TString(sample)+TString(".C")
    nameCanEps = outTS+head+decay+sufixTS+TString(sample)+TString(".eps")


    canvas.Print(nameCanPdf.Data())
    canvas.Print(nameCanPng.Data())
    canvas.Print(nameCanRoot.Data())
    canvas.Print(nameCanC.Data())
    canvas.Print(nameCanEps.Data())

    #Do also plots by splitting in final states
    qf = w.obj("BacCharge")
    time = w.var("BeautyTime")
    time.setBins(75)
    time.SetTitle("t [ps]")

    splitCat = { "ChargeTagDecSplits" : { "titles" : ["d=1",
                                                      "d=-1",
                                                      "D^{-}#pi^{+}",
                                                      "D^{+}#pi^{-}",
                                                      "D^{-}#pi^{+}, d=1",
                                                      "D^{+}#pi^{-}, d=1",
                                                      "D^{-}#pi^{+}, d=-1",
                                                      "D^{+}#pi^{-}, d=-1"],
                                          "cuts" : ["TagDecOS==1",
                                                    "TagDecOS==-1",
                                                    "BacCharge==1",
                                                    "BacCharge==-1",
                                                    "BacCharge==+1 && (TagDecOS==1 || TagDecSS==1)",
                                                    "BacCharge==-1 && (TagDecOS==1 || TagDecSS==1)",
                                                    "BacCharge==+1 && (TagDecOS==-1 || TagDecSS==-1)",
                                                    "BacCharge==-1 && (TagDecOS==-1 || TagDecSS==-1)"]
                                          }
                 }
    
                 
    for tag in splitCat.iterkeys():

        frameUList = []
        for title in range(0, splitCat[tag]["titles"].__len__()):
            frameUList.append( time.frame(ROOT.RooFit.Title(splitCat[tag]["titles"][title] )) )
            frameUList[title].SetTitle(splitCat[tag]["titles"][title])
            frameUList[title].GetXaxis().SetLabelSize( 0.06 )
            frameUList[title].GetYaxis().SetLabelSize( 0.08 )
            frameUList[title].GetXaxis().SetLabelFont( 132 )
            frameUList[title].GetYaxis().SetLabelFont( 132 )
            frameUList[title].GetXaxis().SetLabelOffset( 0.006 )
            frameUList[title].GetYaxis().SetLabelOffset( 0.004 )
            frameUList[title].GetXaxis().SetLabelColor( kWhite)
            frameUList[title].GetXaxis().SetTitleColor( kWhite)
            frameUList[title].GetXaxis().SetTitleSize( 0.06 )
            frameUList[title].GetYaxis().SetTitleSize( 0.08 )
            frameUList[title].GetYaxis().SetNdivisions(512)
            frameUList[title].GetXaxis().SetTitleOffset( 1.1 )
            frameUList[title].GetYaxis().SetTitleOffset( 1.1 )

        frameBList = []
        for title in range(0, splitCat[tag]["titles"].__len__()):
            frameBList.append( time.frame() )
            frameBList[title].SetTitle("")
            frameBList[title].GetYaxis().SetTitle("")
            frameBList[title].GetYaxis().SetTitleSize(0.09)
            frameBList[title].GetYaxis().SetTitleOffset(0.26)
            frameBList[title].GetYaxis().SetTitleFont(132)
            frameBList[title].GetYaxis().SetNdivisions(106)
            frameBList[title].GetYaxis().SetLabelSize(0.20)
            frameBList[title].GetYaxis().SetLabelOffset(0.006)
            frameBList[title].GetXaxis().SetTitleSize(0.25)
            frameBList[title].GetXaxis().SetTitleFont(132)
            frameBList[title].GetXaxis().SetTitleOffset(0.60)
            frameBList[title].GetXaxis().SetNdivisions(5)
            frameBList[title].GetYaxis().SetNdivisions(5)
            frameBList[title].GetXaxis().SetLabelSize(0.25)
            frameBList[title].GetXaxis().SetLabelFont( 132 )
            frameBList[title].GetYaxis().SetLabelFont( 132 )
            frameBList[title].GetYaxis().SetRangeUser(-5.0, 5.0)
            frameBList[title].GetXaxis().SetTitle('#font[132]{#tau(B_{d}#rightarrow D#pi) [ps]}')
            
        dataList = []
        for cut in range(0, splitCat[tag]["cuts"].__len__()):
            dataList.append( dataset.reduce(splitCat[tag]["cuts"][cut]) )

        frm=0
        for data in dataList:
            data.plotOn(frameUList[frm], ROOT.RooFit.MarkerSize(0.1))
            frm = frm+1

        frm=0
        for data in dataList:
            modelPDF.plotOn(frameUList[frm], ROOT.RooFit.ProjWData(data), ROOT.RooFit.LineWidth(1))
            frm = frm+1

        canvSplit = TCanvas("canv"+tag)
        canvSplit.Divide(2,4)
        padUList = []
        padBList = []
        pullHistList = []
        for pad in range(1,9):
            canvSplit.cd(pad)

            padUList.append( TPad("upperPad", "upperPad", .005, .15, 1.0, 1.0) )
            padUList[pad-1].SetBorderMode(0)
            padUList[pad-1].SetBorderSize(-1)
            padUList[pad-1].SetFillStyle(0)
            padUList[pad-1].SetTickx(0);
            padUList[pad-1].SetBottomMargin(0.34)
            padUList[pad-1].SetLeftMargin(0.07)
            padUList[pad-1].SetTopMargin(0.05)
            padUList[pad-1].SetRightMargin(0.05)
            padUList[pad-1].Draw()
            padUList[pad-1].cd()
            frameUList[pad-1].Draw()

            pullHistList.append( frameUList[pad-1].pullHist() )
            pullHistList[pad-1].SetMaximum(3.5)
            pullHistList[pad-1].SetMinimum(-3.5)
            pullHistList[pad-1].setYAxisLimits(-5.0, 5.0)
            pullHistList[pad-1].SetMarkerSize(0.05)
            frameBList[pad-1].addPlotable(pullHistList[pad-1],"P")
            
            canvSplit.cd(pad)
            
            padBList.append( TPad("lowerPad", "lowerPad", .005, .07, 1.0, .45) )
            padBList[pad-1].SetBorderMode(0)
            padBList[pad-1].SetFillStyle(0)
            padBList[pad-1].SetBottomMargin(0.50)
            padBList[pad-1].SetLeftMargin(0.07)
            padBList[pad-1].SetRightMargin(0.05)
            padBList[pad-1].SetTickx(0)
            padBList[pad-1].SetLogy(0)
            padBList[pad-1].Draw()
            padBList[pad-1].cd()
            frameBList[pad-1].Draw()
            
        canvSplit.SaveAs(outTS.Data()+"chargeSplit_"+tag+"_"+sample+".pdf")

#------------------------------------------------------------------------------