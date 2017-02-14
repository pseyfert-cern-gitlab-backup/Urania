#
# @file FitAcceptance
#
# @author Vincenzo Battista
# @date 2017/01/26
#
# @brief Fit acceptance by using cubic spline functions
#

import os, sys
import math

import os.path
from optparse import OptionParser

import ROOT
from ROOT import *
from ROOT import RooFit

import B2DXFitters
from B2DXFitters import *

gROOT.SetBatch(True)
gStyle.SetOptStat(0)

#----------------------------------------------
#----------------------------------------------
#----------------------------------------------
def FitAcceptance(configfile,
                  inputfile,
                  inputtree,
                  outputplotdir,
                  nickname,
                  LHCbText):

    if not inputfile.startswith("[") or not inputfile.endswith("]"):
        print "ERROR: inputfile argument is a list. Please check your options."
        exit(-1)

    print ""
    print "===================="
    print "Taking configuration from:"
    print configfile
    print "===================="
    print ""
    
    myconfigfilegrabber = __import__(configfile,fromlist=['getconfig']).getconfig
    myconfigfile = myconfigfilegrabber()
    
    for option in myconfigfile:
        print option, " = ", myconfigfile[option]

    if inputfile.__len__() == 1:
        print ""
        print "===================="
        print "Take input files:"
        print inputfile
        print "===================="
        print ""
        
        inputFile = TFile.Open(inputfile,"READ")
        
        print ""
        print "===================="
        print "Take input tree:"
        print inputtree
        print "===================="
        print ""
        
        inputTree = inputFile.Get(inputtree)

    elif inputfile.__len__() > 1:
        print ""
        print "===================="
        print "Build tree chain from files before any selection:"
        print inputfile
        print "Tree name:"
        print inputtree
        print "===================="
        print ""

        inputTree = TChain(inputtree)
        fileList = inputfile[1:-1].split(";")
        for file in fileList:
            print "Adding file:"
            print file
            inputTree.Add(file)
    else:
        print "ERROR: check array of input files in options!"
        exit(-1)

    print ""
    print "===================="
    print "Build time observable from:"
    print myconfigfile["Time"]["Name"]
    print "===================="
    print ""
    
    time = RooRealVar(myconfigfile["Time"]["Name"],
                      "Decay time #tau [ps]",
                      myconfigfile["Time"]["Range"][0],
                      myconfigfile["Time"]["Range"][1])
    argset = RooArgSet(time)

    print ""
    print "===================="
    print "Build other observables needed for the dataset"
    print "===================="
    print ""

    var = []
    i=0
    for obs in myconfigfile["Observables"].iterkeys():
        print "...building "+obs
        var.append( RooRealVar(obs,
                               obs,
                               myconfigfile["Observables"][obs]["Range"][0],
                               myconfigfile["Observables"][obs]["Range"][1]) )
        argset.add( var[i] )
        i = i+1
    print "List of observables:"
    print argset.Print("v")
        
    print ""
    print "===================="
    print "Build dataset with preselection:"
    print myconfigfile["Preselection"]
    print "and weight:"
    print myconfigfile["Weight"]
    print "===================="
    print ""

    print "Input tree entries: "+str(inputTree.GetEntries())
    data_temp = RooDataSet("data_temp",
                           "data_temp",
                           inputTree,
                           argset,
                           myconfigfile["Preselection"])
    print "Dataset entries: "+str(data_temp.numEntries())

    print ""
    print "===================="
    print "Apply weight:"
    print myconfigfile["Weight"]
    print "to dataset"
    print "===================="
    print ""

    arglist = RooArgList(time)
    weight = RooFormulaVar("weight","weight",myconfigfile["Weight"],arglist)
    data_temp.addColumn(weight)
    data = RooDataSet("data",
                      "data",
                      data_temp,
                      data_temp.get(),
                      "",
                      weight.GetName())
    print "Dataset sum of weights: "+str(data.sumEntries())
    
    print ""
    print "===================="
    print "Build acceptance pdf"
    print "using knots:"
    print myconfigfile["Acceptance"]["Knots"]
    print "and coefficients:"
    print myconfigfile["Acceptance"]["Coefficients"]
    print "===================="

    knots = myconfigfile["Acceptance"]["Knots"]
    coeffs = myconfigfile["Acceptance"]["Coefficients"]

    if (len(knots) != len(coeffs) or 0 >= min(len(knots), len(coeffs))):
        raise ValueError('ERROR: Spline knot position list and/or coefficient'
                         'list mismatch')
    
    #Create knot binning
    one = RooConstVar("one", "1", 1.0)
    knotbinning = RooBinning(time.getMin(), time.getMax(),
                             "knotbinning")
    for v in knots:
        knotbinning.addBoundary(v)
    knotbinning.removeBoundary(time.getMin())
    knotbinning.removeBoundary(time.getMax())
    knotbinning.removeBoundary(time.getMin())
    knotbinning.removeBoundary(time.getMax())
    oldbinning, lo, hi = time.getBinning(), time.getMin(), time.getMax()
    time.setBinning(knotbinning, "knotbinning")
    time.setBinning(oldbinning)
    time.setRange(lo, hi)

    #Create knot coefficients
    coefflist = RooArgList()
    coeff = []
    i = 0
    for v in coeffs:
        coeff.append( RooRealVar("SplineAccCoeff%u" % (i),
                                 "v_{%u}" % (i+1),
                                 v,
                                 0.,
                                 3.) )
        coefflist.add(coeff[i])
        i = i + 1

    coefflist.add(one)
    i = i + 1
    knots.append(time.getMax())
    knots.reverse()
    fudge = (knots[0] - knots[1]) / (knots[2] - knots[1])
    lastcoeff1 = RooConstVar("SplineAccCoeff%u_coeff0" % (i),
                             "SplineAccCoeff%u_coeff0" % (i), 1. - fudge)
    lastcoeff2 = RooConstVar("SplineAccCoeff%u_coeff1" % (i),
                             "SplineAccCoeff%u_coeff1" % (i), fudge)
    lastcoeffs = RooArgList(lastcoeff1, lastcoeff2)
    poly = RooPolyVar(
        "SplineAccCoeff%u" % (i),
        "v_{%u}" % (i+1),
        coefflist.at(coefflist.getSize() - 2),
        lastcoeffs)
    coefflist.add(poly)

    #Create the spline
    acc = RooCubicSplinePdf("SplineAcceptance",
                            "SplineAcceptance",
                            time,
                            "knotbinning",
                            coefflist)

    print "Acceptance PDF:"
    acc.Print("v")

    print ""
    print "===================="
    print "Run fit"
    print "===================="
    print ""

    fitresult = acc.fitTo(data,
                          RooFit.Offset(True),
                          RooFit.Minimizer("Minuit2", "migrad"),
                          RooFit.NumCPU(8),
                          RooFit.Optimize(True),
                          RooFit.Hesse(True),
                          RooFit.Save(1),
                          RooFit.Strategy(2),
                          RooFit.SumW2Error(True))

    fitresult.Print("v")

    from B2DXFitters.FitResultGrabberUtils import PlotResultMatrix
    PlotResultMatrix(fitresult, "correlation", outputplotdir+nickname+"_CorrelationMatrix.pdf")

    from B2DXFitters import FitResultGrabberUtils
    FitResultGrabberUtils.PrintLatexTable(fitresult)

    print "Saving "+fitresult.GetName()+" to file"
    fitresultFile = TFile(outputplotdir+nickname+"_fitResult.root","RECREATE")
    fitresult.Write()
    fitresultFile.Close()
              
    print ""
    print "===================="
    print "Make plot"
    print "===================="
    print ""

    canvas = TCanvas("canvas", "canvas", 1200, 1000)
    canvas.cd()

    frame_t = time.frame()
    frame_t.SetTitle("")
    frame_t.GetYaxis().SetTitle("")
    frame_t.GetXaxis().SetLabelSize( 0.06 )
    frame_t.GetYaxis().SetLabelSize( 0.035 )
    frame_t.GetXaxis().SetLabelFont( 132 )
    frame_t.GetYaxis().SetLabelFont( 132 )
    frame_t.GetXaxis().SetLabelOffset( 0.006 )
    frame_t.GetYaxis().SetLabelOffset( 0.006 )
    frame_t.GetXaxis().SetLabelColor( kWhite)
    frame_t.GetXaxis().SetTitleSize( 0.06 )
    frame_t.GetYaxis().SetTitleSize( 0.04 )
    frame_t.GetXaxis().SetTitleOffset( 1.00 )
    frame_t.GetYaxis().SetTitleOffset( 1.3 )
    frame_t.GetYaxis().SetNdivisions(508)
    frame_t.GetYaxis().SetTitleOffset( 1.23 )

    data.plotOn(frame_t)
    acc.plotOn(frame_t)
    pullHist = frame_t.pullHist()
    
    pad1 = TPad("upperPad", "upperPad", .005, .05, 1.0, 1.0)
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

    frame_t.Draw()
    lhcbtext = TLatex()
    lhcbtext.SetTextFont(132)
    lhcbtext.SetTextColor(1)
    lhcbtext.SetTextSize(0.05)
    lhcbtext.SetTextAlign(132)
    lhcbtext.DrawTextNDC(myconfigfile["LHCbText"]["X"],
                         myconfigfile["LHCbText"]["Y"],
                         LHCbText)

    chi2ndof = frame_t.chiSquare(fitresult.floatParsFinal().getSize())
    chi2ndof = round(chi2ndof,2)
    chi2text = TLatex()
    chi2text.SetTextFont(132)
    chi2text.SetTextColor(1)
    chi2text.SetTextSize(0.04)
    chi2text.SetTextAlign(132)
    chi2text.DrawLatexNDC(myconfigfile["Chi2Text"]["X"],
                          myconfigfile["Chi2Text"]["Y"],
                          "#chi^{2}/ndof="+str(chi2ndof))
    
    pad1.Update()

    canvas.cd()

    pad2 = TPad("lowerPad", "lowerPad", .005, .005, 1.0, .37)
    pad2.SetBorderMode(0)
    pad2.SetBorderSize(-1)
    pad2.SetFillStyle(0)
    pad2.SetBottomMargin(0.35)
    pad2.SetBottomMargin(0.40)
    pad2.SetLeftMargin(0.17)
    pad2.SetRightMargin(0.05)
    pad2.SetTickx(0);
    pad2.Draw()
    pad2.SetLogy(0)
    pad2.cd()
    
    frame_p = time.frame(RooFit.Title("pull_frame"))
    frame_p.SetTitle("")
    frame_p.GetYaxis().SetTitle("")
    frame_p.GetYaxis().SetTitleSize(0.09)
    frame_p.GetYaxis().SetTitleOffset(0.26)
    frame_p.GetYaxis().SetTitleFont(132)
    frame_p.GetYaxis().SetNdivisions(106)
    frame_p.GetYaxis().SetLabelSize(0.10)
    frame_p.GetYaxis().SetLabelOffset(0.006)
    frame_p.GetXaxis().SetTitleSize(0.150)
    frame_p.GetXaxis().SetTitleFont(132)
    frame_p.GetXaxis().SetTitleOffset(0.9)
    frame_p.GetXaxis().SetNdivisions(5)
    frame_p.GetYaxis().SetNdivisions(5)
    frame_p.GetXaxis().SetLabelSize(0.12)
    frame_p.GetXaxis().SetLabelFont( 132 )
    frame_p.GetYaxis().SetLabelFont( 132 )
    frame_p.GetYaxis().SetRangeUser(-5.0, 5.0)

    pullHist.SetName("pullHist")
    pullHist.SetMaximum(3.5)
    pullHist.SetMinimum(-3.5)
    pullHist.setYAxisLimits(-5.0, 5.0)
    
    frame_p.addPlotable(pullHist,"P")

    frame_p.Draw()
    pad2.Update()
    canvas.Update()
    
    canvas.SaveAs(outputplotdir+"AcceptanceFit_"+nickname+".pdf")
    
#----------------------------------------------
parser = OptionParser()

parser.add_option("--configName",
                  dest="configName",
                  type="string",
                  help="configuration file [default: %default].",
                  default="MyConfigFile.py")
parser.add_option("--inputfile",
                  dest="inputfile",
                  type="string",
                  help="list of input files [default: %default].",
                  default="[MyInputFile1.root,MyInputFile2.root]")
parser.add_option("--inputtree",
                  dest="inputtree",
                  type="string",
                  help="input tree [default: %default].",
                  default="MyDir/MyTree")
parser.add_option("--outputplotdir",
                  dest="outputplotdir",
                  type="string",
                  help="directory to store plots [default: %default].",
                  default="./")
parser.add_option("--nickname",
                  dest="nickname",
                  type="string",
                  help="nickname to label plot [default: %default].",
                  default="MyAwesomeAcceptanceFit")
parser.add_option("--LHCbText",
                  dest="LHCbText",
                  type="string",
                  help="LHCb text [default: %default].",
                  default="LHCb")

#----------------------------------------------
if __name__ == '__main__' :
    ( options, args ) = parser.parse_args()

    config = options.configName
    last = config.rfind("/")
    directory = config[:last+1]
    configfile = config[last+1:]
    p = configfile.rfind(".")
    configfile = configfile[:p]
    
    sys.path.append(directory)
    
    FitAcceptance(configfile,
                  options.inputfile,
                  options.inputtree,
                  options.outputplotdir,
                  options.nickname,
                  options.LHCbText)
