#!/bin/sh
# -*- mode: python; coding: utf-8 -*-
# vim: ft=python:sw=4:tw=78:expandtab
# --------------------------------------------------------------------------- 
# @file fitShapes.py
#
# @brief Obtain shapes
#
# @author Vincenzo Battista
# @date 2016-03-31
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

gROOT.SetBatch()

#------------------------------------------------------------
def makeCanvas(dataset,
               model,
               var,
	       result,
	       min,
	       max,
	       bins,
               text,
	       title,
	       Xtitle,
	       logScale,
	       save):
    
        #Create canvas
        canv = TCanvas("canv_"+dataset.GetName(),"Canvas of "+dataset.GetTitle(), 1200, 1000)
        canv.Divide(1,2)
        
        #Setup upper pad
        canv.cd(1)
        pad1 = canv.GetPad(1)
        pad1.cd()
        pad1.SetPad(.050, .22, 1.0, 1.0)
        pad1.SetBorderMode(0)
        pad1.SetBorderSize(-1)
        pad1.SetFillStyle(0)
        pad1.SetTickx(0)
	if logScale:
		pad1.SetLogy()

        frame_top = makeTopFrame(var,title,min,max,bins)
        dataset.plotOn(frame_top)
        model.plotOn(frame_top,RooFit.LineStyle(1),RooFit.LineColor(4))

	#Build pull histogram and get chi2/ndof
        pullHist = frame_top.pullHist()
        if None != result:
		#Fitted parameters: compute ndof properly
                chi2ndof = frame_top.chiSquare(result.floatParsFinal().getSize())
	else:
	        #No fit: ndof only given by binning
		chi2ndof = frame_top.chiSquare(0)
	chi2ndof = round(chi2ndof,2)
	
	#Plot other pdf components (if any)
	if model.InheritsFrom("RooAddPdf"):
		pdflist = model.pdfList()
		print "List of PFDs to plot:"
		pdflist.Print("v")
		print "Plotting component:"
		for pdf in range(0,pdflist.getSize()):
			print pdflist[pdf].GetName()
			model.plotOn(frame_top,RooFit.Components(pdflist[pdf].GetName()),RooFit.LineStyle(2),RooFit.LineColor(2))

        frame_top.Draw()

	#Add some text
        lhcbtext = makeText(0.07)
        lhcbtext.DrawTextNDC(0.9,0.8,text)

	chi2text = makeText(0.05)
	chi2text.DrawLatexNDC(0.6,0.7,"#chi^{2}/ndof="+str(chi2ndof))
        
        pad1.Update()
        pad1.Draw()

        #Setup lower pad
        canv.cd(2)
        pad2 = canv.GetPad(2)
        pad2.cd()
        pad2.SetPad(.050, .005, 1.0, .3275)
        pad2.cd()
        pad2.SetBorderMode(0)
        pad2.SetBorderSize(-1)
        pad2.SetFillStyle(0)
        pad2.SetBottomMargin(0.35)
        pad2.SetTickx(0)
	pad2.SetGridx()
	pad2.SetGridy()
        pad2.SetLogy(0)
        
        gStyle.SetOptLogy(0)
        
        frame_bot = makeBottomFrame(var,Xtitle,min,max,bins)
        frame_bot.addPlotable(pullHist,"P")
        frame_bot.Draw()
        
        pad2.Update()
        pad2.Draw()
        canv.Update()

	canv.SaveAs(save)

#------------------------------------------------------------
def makeTopFrame(var,title,min,max,bins):
        frame_top = var.frame(min,max,bins)
        frame_top.SetTitle(title)
        frame_top.GetXaxis().SetLabelSize( 0.05 )
        frame_top.GetYaxis().SetLabelSize( 0.038 )
        frame_top.GetXaxis().SetLabelFont( 132 )
        frame_top.GetYaxis().SetLabelFont( 132 )
        frame_top.GetXaxis().SetLabelOffset( 0.006 )
        frame_top.GetYaxis().SetLabelOffset( 0.006 )
        frame_top.GetXaxis().SetLabelColor( kWhite)
        frame_top.GetXaxis().SetTitleSize( 0.05 )
        frame_top.GetYaxis().SetTitleSize( 0.045 )
        frame_top.GetYaxis().SetTitleOffset( 0.02 )
        frame_top.GetYaxis().SetNdivisions(512)
        frame_top.GetXaxis().SetTitleOffset( 1.00 )
        frame_top.GetYaxis().SetTitleOffset( 1.15 )
        
        return frame_top

#------------------------------------------------------------
def makeBottomFrame(var,Xtitle,min,max,bins):
        frame_bot = var.frame(min,max,bins)
        frame_bot.SetTitle("")
        frame_bot.GetYaxis().SetTitle("")
        frame_bot.GetXaxis().SetTitle(Xtitle)
        frame_bot.GetYaxis().SetTitleSize(0.06)
        frame_bot.GetYaxis().SetTitleOffset(0.26)
        frame_bot.GetYaxis().SetTitleFont(132)
        frame_bot.GetYaxis().SetNdivisions(106)
        frame_bot.GetYaxis().SetLabelSize(0.1)
        frame_bot.GetYaxis().SetLabelOffset(0.016)
        frame_bot.GetXaxis().SetTitleSize(0.13)
        frame_bot.GetXaxis().SetTitleFont(132)
        frame_bot.GetXaxis().SetTitleOffset(1.00)
        frame_bot.GetXaxis().SetNdivisions(5)
        frame_bot.GetYaxis().SetNdivisions(5)
        frame_bot.GetYaxis().SetRangeUser(-5,5)
        frame_bot.GetXaxis().SetLabelSize(0.10)
        frame_bot.GetXaxis().SetLabelFont( 132 )
        frame_bot.GetYaxis().SetLabelFont( 132 )
        
        return frame_bot

#------------------------------------------------------------
def makeText(size):
        text = TLatex()
        text.SetTextFont(132)
        text.SetTextColor(1)
        text.SetTextSize(size)
        text.SetTextAlign(132)
        
        return text

#------------------------------------------------------------
def BuildExponentialPDF(workOut, obs, nickname, pdfDict, debug):

        #Build parameters
        varName = obs.GetName()
        typemode = "E"
        samplemode = nickname

        cB = WS(workOut, RooRealVar(typemode+"_"+varName+"_cB_"+samplemode,
                                    typemode+"_"+varName+"_cB_"+samplemode,
                                    *pdfDict["cB"]))

        #Build PDF
        pdf = BasicMDFitPdf.buildExponentialPDF(obs,
						workOut,
						samplemode,
						typemode,
						debug)
        
        return WS(workOut, pdf)

#------------------------------------------------------------
def BuildExponentialPlusConstantPDF(workOut, obs, nickname, pdfDict, debug):

	#Build parameters
	varName = obs.GetName()
	typemode = "EplusC"
	samplemode = nickname
	
	cB = WS(workOut, RooRealVar(typemode+"_"+varName+"_cB_"+samplemode,
				    typemode+"_"+varName+"_cB_"+samplemode,
				    *pdfDict["cB"]))
	
	fracExpo = WS(workOut, RooRealVar(typemode+"_"+varName+"_fracExpo_"+samplemode,
					  typemode+"_"+varName+"_fracExpo_"+samplemode,
					  *pdfDict["fracExpo"]))

	#Build PDF
	pdf = Bd2DhModels.buildExponentialPlusConstantPDF(obs,
							  workOut,
							  samplemode,
							  typemode,
							  debug)
	
	return pdf
        
#------------------------------------------------------------
def BuildGaussPDF(workOut, obs, nickname, pdfDict, debug):

        #Build parameters
        varName = obs.GetName()
        typemode = "G"
        samplemode = nickname
	shiftMean = pdfDict["shiftMean"]

        mean = WS(workOut, RooRealVar(typemode+"_"+varName+"_mean_"+samplemode,
                                      typemode+"_"+varName+"_mean_"+samplemode,
                                      *pdfDict["mean"]))

        sigma = WS(workOut, RooRealVar(typemode+"_"+varName+"_sigma_"+samplemode,
                                       typemode+"_"+varName+"_sigma_"+samplemode,
                                       *pdfDict["sigma"]))

        #Build PDF
        pdf = BasicMDFitPdf.buildGaussPDF(obs,
					  workOut,
					  samplemode,
					  typemode,
					  shiftMean,
					  debug)
        
        return WS(workOut, pdf)

#------------------------------------------------------------
def BuildDoubleGaussPDF(workOut, obs, nickname, pdfDict, debug):

        #Build parameters
        varName = obs.GetName()
        typemode = "DG"
        samplemode = nickname
        sameMean = pdfDict["sameMean"]
        
        mean = WS(workOut, RooRealVar("Signal_"+varName+"_mean_"+samplemode if sameMean else typemode+"_"+varName+"_mean_"+samplemode,
                                      "Signal_"+varName+"_mean_"+samplemode if sameMean else typemode+"_"+varName+"_mean_"+samplemode,
                                      *pdfDict["mean"]))
        
        sigma1 = WS(workOut, RooRealVar(typemode+"_"+varName+"_sigma1_"+samplemode,
                                        typemode+"_"+varName+"_sigma1_"+samplemode,
                                        *pdfDict["sigma1"]))

        sigma2 = WS(workOut, RooRealVar(typemode+"_"+varName+"_sigma2_"+samplemode,
                                        typemode+"_"+varName+"_sigma2_"+samplemode,
                                        *pdfDict["sigma2"]))
        
        frac = WS(workOut, RooRealVar(typemode+"_"+varName+"_frac_"+samplemode,
                                      typemode+"_"+varName+"_frac_"+samplemode,
                                      *pdfDict["frac"]))

        #Build PDF
        pdf = BasicMDFitPdf.buildDoubleGaussPDF(obs,
						workOut,
						samplemode,
						typemode,
						False,
						sameMean,
						False,
						debug)
        
        return WS(workOut, pdf)
        
#------------------------------------------------------------
def BuildCrystalBallPDF(workOut, obs, nickname, pdfDict, debug):

        #Build parameters
        varName = obs.GetName()
        typemode = "CB"
        samplemode = nickname

        mean = WS(workOut, RooRealVar(typemode+"_"+varName+"_mean_"+samplemode,
                                      typemode+"_"+varName+"_mean_"+samplemode,
                                      *pdfDict["mean"]))
        alpha = WS(workOut, RooRealVar(typemode+"_"+varName+"_alpha_"+samplemode,
                                       typemode+"_"+varName+"_alpha_"+samplemode,
				       *pdfDict["sigma"]))
        n = WS(workOut, RooRealVar(typemode+"_"+varName+"_n_"+samplemode,
                                   typemode+"_"+varName+"_n_"+samplemode,
				   *pdfDict["n"]))
        sigma = WS(workOut, RooRealVar(typemode+"_"+varName+"_sigma_"+samplemode,
                                       typemode+"_"+varName+"_sigma_"+samplemode,
                                       *pdfDict["sigma"]))

        #Build PDF
        pdf = BasicMDFitPdf.buildCrystalBallPDF(obs,
						workOut,
						samplemode,
						typemode,
						debug)
        
        return WS(workOut, pdf)

#------------------------------------------------------------
def BuildCrystalBallPlusExponentialPDF(workOut, obs, nickname, pdfDict, debug):

	#Build parameters
	varName = obs.GetName()
	typemode = "CBplusE"
	samplemode = nickname
	shiftMean = pdfDict["shiftMean"]

	mean = WS(workOut, RooRealVar(typemode+"_"+varName+"_mean_"+samplemode,
				      typemode+"_"+varName+"_mean_"+samplemode,
				      *pdfDict["mean"]))
	alpha = WS(workOut, RooRealVar(typemode+"_"+varName+"_alpha_"+samplemode,
				       typemode+"_"+varName+"_alpha_"+samplemode,
				       *pdfDict["alpha"]))
	n = WS(workOut, RooRealVar(typemode+"_"+varName+"_n_"+samplemode,
				   typemode+"_"+varName+"_n_"+samplemode,
				   *pdfDict["n"]))
	sigmaCB = WS(workOut, RooRealVar(typemode+"_"+varName+"_sigmaCB_"+samplemode,
					 typemode+"_"+varName+"_sigmaCB_"+samplemode,
					 *pdfDict["sigmaCB"]))
	if shiftMean:
		meanGshift = WS(workOut, RooRealVar(typemode+"_"+varName+"_shift_"+samplemode,
						    typemode+"_"+varName+"_shift_"+samplemode,
						    *pdfDict["shift"]))

	cB = WS(workOut, RooRealVar(typemode+"_"+varName+"_cB_"+samplemode,
				    typemode+"_"+varName+"_cB_"+samplemode,
				    *pdfDict["cB"]))

	fracExpo = WS(workOut, RooRealVar(typemode+"_"+varName+"_fracExpo_"+samplemode,
					  typemode+"_"+varName+"_fracExpo_"+samplemode,
					  *pdfDict["fracExpo"]))

	#Build PDF
	pdf = Bd2DhModels.buildCrystalBallPlusExponentialPDF(obs,
							     workOut,
							     samplemode,
							     typemode,
							     shiftMean,
							     debug)
	
	return WS(workOut, pdf)
	
#------------------------------------------------------------
def BuildCrystalBallPlusGaussianPDF(workOut, obs, nickname, pdfDict, debug):

	#Build parameters
	varName = obs.GetName()
	typemode = "CBplusG"
	samplemode = nickname
	shiftMean = pdfDict["shiftMean"]
	
	mean = WS(workOut, RooRealVar(typemode+"_"+varName+"_mean_"+samplemode,
				      typemode+"_"+varName+"_mean_"+samplemode,
				      *pdfDict["mean"]))
	alpha = WS(workOut, RooRealVar(typemode+"_"+varName+"_alpha_"+samplemode,
				       typemode+"_"+varName+"_alpha_"+samplemode,
				       *pdfDict["alpha"]))
	n = WS(workOut, RooRealVar(typemode+"_"+varName+"_n_"+samplemode,
				   typemode+"_"+varName+"_n_"+samplemode,
				   *pdfDict["n"]))
	sigmaCB = WS(workOut, RooRealVar(typemode+"_"+varName+"_sigmaCB_"+samplemode,
					 typemode+"_"+varName+"_sigmaCB_"+samplemode,
					 *pdfDict["sigmaCB"]))
	if shiftMean:
		meanGshift = WS(workOut, RooRealVar(typemode+"_"+varName+"_shift_"+samplemode,
						    typemode+"_"+varName+"_shift_"+samplemode,
						    *pdfDict["shift"]))
	sigmaG = WS(workOut, RooRealVar(typemode+"_"+varName+"_sigmaG_"+samplemode,
					typemode+"_"+varName+"_sigmaG_"+samplemode,
					*pdfDict["sigmaG"]))
	frac = WS(workOut, RooRealVar(typemode+"_"+varName+"_fracG_"+samplemode,
				      typemode+"_"+varName+"_fracG_"+samplemode,
				      *pdfDict["fracG"]))

	#Build PDF
	pdf = Bd2DhModels.buildCrystalBallPlusGaussianPDF(obs,
							  workOut,
							  samplemode,
							  typemode,
							  shiftMean,
							  False,
							  debug)

	return WS(workOut, pdf)

#------------------------------------------------------------
def BuildDoubleCrystalBallPDF(workOut, obs, nickname, pdfDict, debug):

        #Build parameters
        varName = obs.GetName()
        typemode = "DCB"
        samplemode = nickname
	sameMean = pdfDict["sameMean"]
        
        mean = WS(workOut, RooRealVar("Signal_"+varName+"_mean_"+samplemode if sameMean else typemode+"_"+varName+"_mean_"+samplemode,
                                      "Signal_"+varName+"_mean_"+samplemode if sameMean else typemode+"_"+varName+"_mean_"+samplemode,
                                      *pdfDict["mean"]))
        alpha1 = WS(workOut, RooRealVar(typemode+"_"+varName+"_alpha1_"+samplemode,
                                        typemode+"_"+varName+"_alpha1_"+samplemode,
					*pdfDict["alpha1"]))
        alpha2 = WS(workOut, RooRealVar(typemode+"_"+varName+"_alpha2_"+samplemode,
                                        typemode+"_"+varName+"_alpha2_"+samplemode,
					*pdfDict["alpha2"]))
        n1 = WS(workOut, RooRealVar(typemode+"_"+varName+"_n1_"+samplemode,
                                    typemode+"_"+varName+"_n1_"+samplemode,
                                    *pdfDict["n1"]))
        n2 = WS(workOut, RooRealVar(typemode+"_"+varName+"_n2_"+samplemode,
                                    typemode+"_"+varName+"_n2_"+samplemode,
                                    *pdfDict["n2"]))
        sigma1 = WS(workOut, RooRealVar(typemode+"_"+varName+"_sigma1_"+samplemode,
                                        typemode+"_"+varName+"_sigma1_"+samplemode,
                                        *pdfDict["sigma1"]))
        sigma2 = WS(workOut, RooRealVar(typemode+"_"+varName+"_sigma2_"+samplemode,
                                        typemode+"_"+varName+"_sigma2_"+samplemode,
                                        *pdfDict["sigma2"]))
        frac = WS(workOut, RooRealVar(typemode+"_"+varName+"_frac_"+samplemode,
                                      typemode+"_"+varName+"_frac_"+samplemode,
                                      *pdfDict["frac"]))
        
        #Build PDF
        pdf = BasicMDFitPdf.buildDoubleCrystalBallPDF(obs,
						      workOut,
						      samplemode,
						      typemode,
						      False,
						      sameMean,
						      debug)
        
        return WS(workOut, pdf)

#------------------------------------------------------------
def BuildJohnsonSUPDF(workOut, obs, nickname, pdfDict, debug):

        #Build parameters
        varName = obs.GetName()
        typemode = "J"
        samplemode = nickname

        mean = WS(workOut, RooRealVar(typemode+"_"+varName+"_mean_"+samplemode,
                                      typemode+"_"+varName+"_mean_"+samplemode,
                                      *pdfDict["mean"]))
        sigmaVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_sigma_"+samplemode,
                                          typemode+"_"+varName+"_sigma_"+samplemode,
                                          *pdfDict["sigma"]))
        nuVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_nu_"+samplemode,
                                       typemode+"_"+varName+"_nu_"+samplemode,
                                       *pdfDict["nu"]))
        tauVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_tau_"+samplemode,
                                        typemode+"_"+varName+"_tau_"+samplemode,
                                        *pdfDict["tau"]))

        #Build PDF
        pdf = Bd2DhModels.buildJohnsonSUPDF(obs,
                                            workOut,
                                            samplemode,
                                            typemode,
                                            False,
                                            debug)
        
        return WS(workOut, pdf)
        
#------------------------------------------------------------
def BuildJohnsonSUPlusGaussianPDF(workOut, obs, nickname, pdfDict, debug):

        #Build parameters
        varName = obs.GetName()
        typemode = "JplusG"
        samplemode = nickname
	sameMean = pdfDict["sameMean"]
	
	meanJ = WS(workOut, RooRealVar(typemode+"_"+varName+"_meanJ_"+samplemode,
				       typemode+"_"+varName+"_meanJ_"+samplemode,
				       *pdfDict["meanJ"]))
        sigmaJVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_sigmaJ_"+samplemode,
                                           typemode+"_"+varName+"_sigmaJ_"+samplemode,
                                           *pdfDict["sigmaJ"]))
        nuJVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_nuJ_"+samplemode,
                                        typemode+"_"+varName+"_nuJ_"+samplemode,
                                        *pdfDict["nuJ"]))
        tauJVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_tauJ_"+samplemode,
                                         typemode+"_"+varName+"_tauJ_"+samplemode,
                                         *pdfDict["tauJ"]))
        meanGshift = WS(workOut, RooRealVar(typemode+"_"+varName+"_meanGshift_"+samplemode,
					    typemode+"_"+varName+"_meanGshift_"+samplemode,
					    *pdfDict["meanGshift"]))
        sigmaGVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_sigmaG_"+samplemode,
                                           typemode+"_"+varName+"_sigmaG_"+samplemode,
                                           *pdfDict["sigmaG"]))
        fracGVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_frac_"+samplemode,
                                          typemode+"_"+varName+"_frac_"+samplemode,
                                          *pdfDict["frac"]))
        
        #Build PDF
        pdf = Bd2DhModels.buildJohnsonSUPlusGaussianPDF(obs,
							workOut,
							samplemode,
							typemode,
							sameMean,
							False,
							debug)
        
        return WS(workOut, pdf)

#------------------------------------------------------------
def BuildJohnsonSUPlusGaussianPlusExponentialPDF(workOut, obs, nickname, pdfDict, debug):

	#Build parameters
	varName = obs.GetName()
	typemode = "JplusGplusExpo"
	samplemode = nickname
	sameMean = pdfDict["sameMean"]
	
	meanJ = WS(workOut, RooRealVar(typemode+"_"+varName+"_meanJ_"+samplemode,
				       typemode+"_"+varName+"_meanJ_"+samplemode,
				       *pdfDict["meanJ"]))
	sigmaJVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_sigmaJ_"+samplemode,
					   typemode+"_"+varName+"_sigmaJ_"+samplemode,
					   *pdfDict["sigmaJ"]))
	nuJVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_nuJ_"+samplemode,
					typemode+"_"+varName+"_nuJ_"+samplemode,
					*pdfDict["nuJ"]))
	tauJVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_tauJ_"+samplemode,
					 typemode+"_"+varName+"_tauJ_"+samplemode,
					 *pdfDict["tauJ"]))
	meanGshift = WS(workOut, RooRealVar(typemode+"_"+varName+"_meanGshift_"+samplemode,
					    typemode+"_"+varName+"_meanGshift_"+samplemode,
					    *pdfDict["meanGshift"]))
	sigmaGVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_sigmaG_"+samplemode,
					   typemode+"_"+varName+"_sigmaG_"+samplemode,
					   *pdfDict["sigmaG"]))
        cBVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_cB_"+samplemode,
                                       typemode+"_"+varName+"_cB_"+samplemode,
                                       *pdfDict["cB"]))
	relFracSignalVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_relFracSignal_"+samplemode,
                                                  typemode+"_"+varName+"_relFracSignal_"+samplemode,
                                                  *pdfDict["relFracSignal"]))
        fracExpoVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_fracExpo_"+samplemode,
                                             typemode+"_"+varName+"_fracExpo_"+samplemode,
                                             *pdfDict["fracExponential"]))
	
	#Build PDF
	pdf = Bd2DhModels.buildJohnsonSUPlusGaussianPlusExponentialPDF(obs,
								       workOut,
								       samplemode,
								       typemode,
								       sameMean,
								       debug)
	
	return WS(workOut, pdf)

#------------------------------------------------------------
def BuildJohnsonSUPlus2GaussianPDF(workOut, obs, nickname, pdfDict, debug):
        
	#Build parameters
        varName = obs.GetName()
        typemode = "Jplus2G"
        samplemode = nickname
	sameMean = pdfDict["sameMean"]
        
	meanJ = WS(workOut, RooRealVar(typemode+"_"+varName+"_meanJ_"+samplemode,
                                       typemode+"_"+varName+"_meanJ_"+samplemode,
                                       *pdfDict["meanJ"]))
        sigmaJVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_sigmaJ_"+samplemode,
                                           typemode+"_"+varName+"_sigmaJ_"+samplemode,
                                           *pdfDict["sigmaJ"]))
        nuJVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_nuJ_"+samplemode,
                                        typemode+"_"+varName+"_nuJ_"+samplemode,
                                        *pdfDict["nuJ"]))
        tauJVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_tauJ_"+samplemode,
                                         typemode+"_"+varName+"_tauJ_"+samplemode,
                                         *pdfDict["tauJ"]))
        meanG1shift = WS(workOut, RooRealVar(typemode+"_"+varName+"_meanG1shift_"+samplemode,
					     typemode+"_"+varName+"_meanG1shift_"+samplemode,
					     *pdfDict["meanG1shift"]))
        meanG2shift = WS(workOut, RooRealVar(typemode+"_"+varName+"_meanG2shift_"+samplemode,
					     typemode+"_"+varName+"_meanG2shift_"+samplemode,
					     *pdfDict["meanG2shift"]))
        sigma1GVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_sigma1G_"+samplemode,
                                            typemode+"_"+varName+"_sigma1G_"+samplemode,
                                            *pdfDict["sigma1G"]))
        sigma2GVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_sigma2G_"+samplemode,
                                            typemode+"_"+varName+"_sigma2G_"+samplemode,
                                            *pdfDict["sigma2G"]))
        frac1GVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_frac1G_"+samplemode,
                                           typemode+"_"+varName+"_frac1G_"+samplemode,
                                           *pdfDict["frac1G"]))
        frac2GVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_frac2G_"+samplemode,
                                           typemode+"_"+varName+"_frac2G_"+samplemode,
                                           *pdfDict["frac2G"]))

        #Build PDF
        pdf = Bd2DhModels.buildJohnsonSUPlus2GaussianPDF(obs,
							 workOut,
							 samplemode,
							 typemode,
							 sameMean,
							 debug)

        return WS(workOut, pdf)

#------------------------------------------------------------
def BuildIpatiaPDF(workOut, obs, nickname, pdfDict, debug):

	#Build parameters
	varName = obs.GetName()
	typemode = "Ipatia"
	samplemode = nickname

	lVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_l_"+samplemode,
				      typemode+"_"+varName+"_l_"+samplemode,
				      *pdfDict["l"]))
	zetaVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_zeta_"+samplemode,
					 typemode+"_"+varName+"_zeta_"+samplemode,
					 *pdfDict["zeta"]))
	fbVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_fb_"+samplemode,
				       typemode+"_"+varName+"_fb_"+samplemode,
				       *pdfDict["fb"]))
	meanVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_mean_"+samplemode,
					 typemode+"_"+varName+"_mean_"+samplemode,
					 *pdfDict["mean"]))
	sigmaVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_sigma_"+samplemode,
					  typemode+"_"+varName+"_sigma_"+samplemode,
					  *pdfDict["sigma"]))
	a1Var = WS(workOut, RooRealVar(typemode+"_"+varName+"_a1_"+samplemode,
				       typemode+"_"+varName+"_a1_"+samplemode,
				       *pdfDict["a1"]))
	n1Var = WS(workOut, RooRealVar(typemode+"_"+varName+"_n1_"+samplemode,
				       typemode+"_"+varName+"_n1_"+samplemode,
				       *pdfDict["n1"]))
	a2Var = WS(workOut, RooRealVar(typemode+"_"+varName+"_a2_"+samplemode,
				       typemode+"_"+varName+"_a2_"+samplemode,
				       *pdfDict["a2"]))
	n2Var = WS(workOut, RooRealVar(typemode+"_"+varName+"_n2_"+samplemode,
				       typemode+"_"+varName+"_n2_"+samplemode,
				       *pdfDict["n2"]))

	#Build PDF
	pdf = BasicMDFitPdf.buildIpatiaPDF(obs,
					   workOut,
					   samplemode,
					   typemode,
					   False,
					   False,
					   debug)

	return WS(workOut, pdf)

#------------------------------------------------------------
def BuildIpatiaPlusExponentialPDF(workOut, obs, nickname, pdfDict, debug):

	#Build parameters
	varName = obs.GetName()
	typemode = "IpatiaPlusExponential"
	samplemode = nickname
	
	lVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_l_"+samplemode,
				      typemode+"_"+varName+"_l_"+samplemode,
				      *pdfDict["l"]))
	zetaVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_zeta_"+samplemode,
					 typemode+"_"+varName+"_zeta_"+samplemode,
					 *pdfDict["zeta"]))
	fbVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_fb_"+samplemode,
				       typemode+"_"+varName+"_fb_"+samplemode,
				       *pdfDict["fb"]))
	meanVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_mean_"+samplemode,
					 typemode+"_"+varName+"_mean_"+samplemode,
					 *pdfDict["mean"]))
	sigmaVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_sigma_"+samplemode,
					  typemode+"_"+varName+"_sigma_"+samplemode,
					  *pdfDict["sigma"]))
	a1Var = WS(workOut, RooRealVar(typemode+"_"+varName+"_a1_"+samplemode,
				       typemode+"_"+varName+"_a1_"+samplemode,
				       *pdfDict["a1"]))
	n1Var = WS(workOut, RooRealVar(typemode+"_"+varName+"_n1_"+samplemode,
				       typemode+"_"+varName+"_n1_"+samplemode,
				       *pdfDict["n1"]))
	a2Var = WS(workOut, RooRealVar(typemode+"_"+varName+"_a2_"+samplemode,
				       typemode+"_"+varName+"_a2_"+samplemode,
				       *pdfDict["a2"]))
	n2Var = WS(workOut, RooRealVar(typemode+"_"+varName+"_n2_"+samplemode,
				       typemode+"_"+varName+"_n2_"+samplemode,
				       *pdfDict["n2"]))
	cBVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_cB_"+samplemode,
				       typemode+"_"+varName+"_cB_"+samplemode,
				       *pdfDict["cB"]))
	fracVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_frac_"+samplemode,
					 typemode+"_"+varName+"_frac_"+samplemode,
					 *pdfDict["frac"]))

	#Build PDF
	pdf = Bd2DhModels.buildIpatiaPlusExponentialPDF(obs,
							workOut,
							samplemode,
							typemode,
							debug)
	
	return WS(workOut, pdf)

#------------------------------------------------------------
def BuildIpatiaPlusGaussianPDF(workOut, obs, nickname, pdfDict, debug):

	#Build parameters
	varName = obs.GetName()
	typemode = "IpatiaPlusGaussian"
	samplemode = nickname

	lVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_l_"+samplemode,
				      typemode+"_"+varName+"_l_"+samplemode,
				      *pdfDict["l"]))
	zetaVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_zeta_"+samplemode,
					 typemode+"_"+varName+"_zeta_"+samplemode,
					 *pdfDict["zeta"]))
	fbVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_fb_"+samplemode,
				       typemode+"_"+varName+"_fb_"+samplemode,
				       *pdfDict["fb"]))
	meanVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_mean_"+samplemode,
					 typemode+"_"+varName+"_mean_"+samplemode,
					 *pdfDict["mean"]))
	sigmaIVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_sigmaI_"+samplemode,
					   typemode+"_"+varName+"_sigmaI_"+samplemode,
					   *pdfDict["sigmaI"]))
	sigmaGVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_sigmaG_"+samplemode,
					   typemode+"_"+varName+"_sigmaG_"+samplemode,
					   *pdfDict["sigmaG"]))
	a1Var = WS(workOut, RooRealVar(typemode+"_"+varName+"_a1_"+samplemode,
				       typemode+"_"+varName+"_a1_"+samplemode,
				       *pdfDict["a1"]))
	n1Var = WS(workOut, RooRealVar(typemode+"_"+varName+"_n1_"+samplemode,
				       typemode+"_"+varName+"_n1_"+samplemode,
				       *pdfDict["n1"]))
	a2Var = WS(workOut, RooRealVar(typemode+"_"+varName+"_a2_"+samplemode,
				       typemode+"_"+varName+"_a2_"+samplemode,
				       *pdfDict["a2"]))
	n2Var = WS(workOut, RooRealVar(typemode+"_"+varName+"_n2_"+samplemode,
				       typemode+"_"+varName+"_n2_"+samplemode,
				       *pdfDict["n2"]))
	fracVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_fracI_"+samplemode,
					 typemode+"_"+varName+"_fracI_"+samplemode,
					 *pdfDict["fracI"]))

	#Build PDF
	pdf = Bd2DhModels.buildIpatiaPlusGaussianPDF(obs,
						     workOut,
						     samplemode,
						     typemode,
						     False,
						     False,
						     debug)
	
	return WS(workOut, pdf)

#------------------------------------------------------------
def BuildIpatiaPlusJohnsonSUPDF(workOut, obs, nickname, pdfDict, debug):

	#Build parameters
	varName = obs.GetName()
	typemode = "IpatiaPlusJohnsonSU"
	samplemode = nickname

	lVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_l_"+samplemode,
				      typemode+"_"+varName+"_l_"+samplemode,
				      *pdfDict["l"]))
	zetaVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_zeta_"+samplemode,
					 typemode+"_"+varName+"_zeta_"+samplemode,
					 *pdfDict["zeta"]))
	fbVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_fb_"+samplemode,
				       typemode+"_"+varName+"_fb_"+samplemode,
				       *pdfDict["fb"]))
	meanVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_mean_"+samplemode,
					 typemode+"_"+varName+"_mean_"+samplemode,
					 *pdfDict["mean"]))
	sigmaIVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_sigmaI_"+samplemode,
					   typemode+"_"+varName+"_sigmaI_"+samplemode,
					   *pdfDict["sigmaI"]))
	sigmaJVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_sigmaJ_"+samplemode,
					   typemode+"_"+varName+"_sigmaJ_"+samplemode,
					   *pdfDict["sigmaJ"]))
	a1Var = WS(workOut, RooRealVar(typemode+"_"+varName+"_a1_"+samplemode,
				       typemode+"_"+varName+"_a1_"+samplemode,
				       *pdfDict["a1"]))
	n1Var = WS(workOut, RooRealVar(typemode+"_"+varName+"_n1_"+samplemode,
				       typemode+"_"+varName+"_n1_"+samplemode,
				       *pdfDict["n1"]))
	a2Var = WS(workOut, RooRealVar(typemode+"_"+varName+"_a2_"+samplemode,
				       typemode+"_"+varName+"_a2_"+samplemode,
				       *pdfDict["a2"]))
	n2Var = WS(workOut, RooRealVar(typemode+"_"+varName+"_n2_"+samplemode,
				       typemode+"_"+varName+"_n2_"+samplemode,
				       *pdfDict["n2"]))
	nuVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_nu_"+samplemode,
				       typemode+"_"+varName+"_nu_"+samplemode,
				       *pdfDict["nu"]))
	tauVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_tau_"+samplemode,
					typemode+"_"+varName+"_tau_"+samplemode,
					*pdfDict["tau"]))
	fracVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_fracI_"+samplemode,
					 typemode+"_"+varName+"_fracI_"+samplemode,
					 *pdfDict["fracI"]))

	#Build PDF
	pdf = Bd2DhModels.buildIpatiaPlusJohnsonSUPDF(obs,
						      workOut,
						      samplemode,
						      typemode,
						      False,
						      False,
						      debug)
	
	return WS(workOut, pdf)
	
#------------------------------------------------------------
def BuildIpatiaGaussConvPDF(workOut, obs, nickname, pdfDict, debug):
        
        #Build parameters
        varName = obs.GetName()
        typemode = "IpatiaGaussConv"
        samplemode = nickname

        lVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_l_"+samplemode,
                                      typemode+"_"+varName+"_l_"+samplemode,
                                      *pdfDict["l"]))
        zetaVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_zeta_"+samplemode,
                                         typemode+"_"+varName+"_zeta_"+samplemode,
                                         *pdfDict["zeta"]))
        fbVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_fb_"+samplemode,
                                       typemode+"_"+varName+"_fb_"+samplemode,
                                       *pdfDict["fb"]))
        meanVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_mean_"+samplemode,
                                         typemode+"_"+varName+"_mean_"+samplemode,
                                         *pdfDict["mean"]))
        sigmaIVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_sigmaI_"+samplemode,
                                           typemode+"_"+varName+"_sigmaI_"+samplemode,
                                           *pdfDict["sigmaI"]))
        sigmaGVar = WS(workOut, RooRealVar(typemode+"_"+varName+"_sigmaG_"+samplemode,
                                           typemode+"_"+varName+"_sigmaG_"+samplemode,
                                           *pdfDict["sigmaG"]))
        a1Var = WS(workOut, RooRealVar(typemode+"_"+varName+"_a1_"+samplemode,
                                       typemode+"_"+varName+"_a1_"+samplemode,
                                       *pdfDict["a1"]))
        n1Var = WS(workOut, RooRealVar(typemode+"_"+varName+"_n1_"+samplemode,
                                       typemode+"_"+varName+"_n1_"+samplemode,
                                       *pdfDict["n1"]))
        a2Var = WS(workOut, RooRealVar(typemode+"_"+varName+"_a2_"+samplemode,
                                       typemode+"_"+varName+"_a2_"+samplemode,
                                       *pdfDict["a2"]))
        n2Var = WS(workOut, RooRealVar(typemode+"_"+varName+"_n2_"+samplemode,
                                       typemode+"_"+varName+"_n2_"+samplemode,
                                       *pdfDict["n2"]))

        #Build PDF
        pdf = Bd2DhModels.buildIpatiaGaussConvPDF(obs,
                                                  workOut,
                                                  samplemode,
                                                  typemode,
						  False,
						  False,
						  False,
                                                  debug)
        
        return WS(workOut, pdf)
        
#------------------------------------------------------------
def BuildRooKeysPdf(workOut, obs, nickname, pdfDict, data, debug):

	#Build parameters
	rho = pdfDict["Rho"]
	mirror = pdfDict["Mirror"]

	if mirror == "MirrorBoth":
		pdf = RooKeysPdf(nickname+"_"+str(obs.GetName())+"_RooKeysPdf_all",
				 nickname+"_"+str(obs.GetName())+"_RooKeysPdf_all",
				 obs,
				 data,
				 RooKeysPdf.MirrorBoth,
				 rho)
	elif mirror == "NoMirror":
		pdf = RooKeysPdf(nickname+"_"+str(obs.GetName())+"_RooKeysPdf_all",
				 nickname+"_"+str(obs.GetName())+"_RooKeysPdf_all",
				 obs,
				 data,
				 RooKeysPdf.NoMirror,
				 rho)
	else:
		print "ERROR: mirror mode "+str(mirror)+" not currently handled"
		exit(-1)

	return WS(workOut, pdf)

#------------------------------------------------------------
def TakeInputPdf(workOut, pdfDict):
	name = pdfDict["InputPdf"]
	pdf = workOut.pdf(name)
	return WS(workOut, pdf)
		
#------------------------------------------------------------
#------------------------------------------------------------
#------------------------------------------------------------
def fitShapes( debug,
	       configName,
	       inputFile,
	       outputFile,
	       workData,
	       workOut,
	       save,
	       initial,
	       variable,
	       component,
	       mode,
	       sample,
	       year,
	       merge,
	       hypo,
	       binned,
	       superimpose,
	       logScale,
	       outputplotdir):

	# Tune integrator configuration
	RooAbsReal.defaultIntegratorConfig().setEpsAbs(1e-7)
	RooAbsReal.defaultIntegratorConfig().setEpsRel(1e-7)
	RooAbsReal.defaultIntegratorConfig().getConfigSection('RooIntegrator1D').setCatLabel('extrapolation','WynnEpsilon')
	RooAbsReal.defaultIntegratorConfig().getConfigSection('RooIntegrator1D').setCatLabel('maxSteps','1000')
	RooAbsReal.defaultIntegratorConfig().getConfigSection('RooIntegrator1D').setCatLabel('minSteps','0')
	RooAbsReal.defaultIntegratorConfig().getConfigSection('RooAdaptiveGaussKronrodIntegrator1D').setCatLabel('method','21Points')
	RooAbsReal.defaultIntegratorConfig().getConfigSection('RooAdaptiveGaussKronrodIntegrator1D').setRealValue('maxSeg', 1000)
	# Since we have finite ranges, the RooIntegrator1D is best suited to the job
	RooAbsReal.defaultIntegratorConfig().method1D().setLabel('RooIntegrator1D')
	
	# Get the configuration file
	myconfigfilegrabber = __import__(configName,fromlist=['getconfig']).getconfig
	myconfigfile = myconfigfilegrabber()

	print "=========================================================="
	print "FITSHAPES IS RUNNING WITH THE FOLLOWING CONFIGURATION OPTIONS"
	for option in myconfigfile :
		if option == "constParams" :
			for param in myconfigfile[option] :
				print param, "is constant in the fit"
		else :
			print option, " = ", myconfigfile[option]
	print "=========================================================="

	RooAbsData.setDefaultStorageType(RooAbsData.Tree)

	from B2DXFitters.MDFitSettingTranslator import Translator

	from B2DXFitters.mdfitutils import getExpectedValue as getExpectedValue
	from B2DXFitters.mdfitutils import getExpectedYield as getExpectedYield
	from B2DXFitters.mdfitutils import setConstantIfSoConfigured as setConstantIfSoConfigured
	from B2DXFitters.mdfitutils import getObservables  as getObservables
	from B2DXFitters.mdfitutils import readVariables as readVariables
	from B2DXFitters.mdfitutils import getSigOrCombPDF as getSigOrCombPDF
	from B2DXFitters.mdfitutils import getType as getType
	from B2DXFitters.mdfitutils import getPDFNameFromConfig as getPDFNameFromConfig
	from B2DXFitters.mdfitutils import getPIDKComponents as getPIDKComponents
	from B2DXFitters.mdfitutils import setBs2DsXParameters as setBs2DsXParameters

	mdt = Translator(myconfigfile,"MDSettings",False)

	MDSettings = mdt.getConfig()
	MDSettings.Print("v")

	print ""
	print "========================================="
	print "Get input workspace "+str(workData)+" from:"
	print str(inputFile)
	print "========================================="
	print ""
	workspace = GeneralUtils.LoadWorkspace(TString(inputFile), TString(workData), debug)

	print ""
	print "========================================="
	print "Get output workspace "+str(workOut)+" from:"
	print str(outputFile)
	print "========================================="
	print ""
	if initial != "":
		workspaceOut = GeneralUtils.LoadWorkspace(TString(initial),TString(workOut),debug)
	else:
		workspaceOut = RooWorkspace(workOut,workOut)

	print ""
	print "========================================="
	print "Get input observables from:"
	print str(workData)
	print "========================================="
	print ""
	observables = getObservables(MDSettings, workspace, False, debug)
	if "Beauty" in variable:
		obs = observables.find(MDSettings.GetMassBVarOutName().Data())
		obs.setRange(*myconfigfile["BasicVariables"]["BeautyMass"]["Range"])
		obs.SetTitle(myconfigfile["AxisTitle"][variable][hypo])
		obs = WS(workspaceOut, obs)
	elif "Charm" in variable:
		obs = observables.find(MDSettings.GetMassDVarOutName().Data())
		obs.setRange(*myconfigfile["BasicVariables"]["CharmMass"]["Range"])
		obs.SetTitle(myconfigfile["AxisTitle"][variable][hypo])
		obs = WS(workspaceOut, obs)
	else:
		print "ERROR: "+variable+" is not currently handled"
		exit(-1)

	print ""
	print "========================================="
	print "Get dataset from:"
	print str(workData)
	print "========================================="
	print ""

	modeTS = TString(mode)
        sampleTS = TString(sample)
        yearTS = TString(year)
        hypoTS = TString(hypo)
	
	datasetTS = TString(myconfigfile["dataSetPrefix"][component])
	if "Comb" in component:
		datasetTS = datasetTS+TString(variable)+TString("_")

	print "Component:"
	print component
	print "Dataset name prefix:"
	print datasetTS.Data()
		
	if merge == "pol" or merge == "both":
                sampleTS = TString("both")
        if merge == "year" or merge == "both":
                yearTS = TString("run1")

        sam = WS(workspaceOut, RooCategory("sample","sample"))

	if "Signal" in component or "Comb" in component:
		dataSet = GeneralUtils.GetDataSet(workspace, observables, sam, datasetTS, sampleTS, modeTS, yearTS, hypoTS, merge, debug )
		dataSet.SetName(dataSet.GetName()+"_"+component+"_"+sampleTS.Data()+"_"+modeTS.Data()+"_"+yearTS.Data()+"_"+hypoTS.Data()+"Hypo")
	else:
		dataSet = GeneralUtils.GetDataSet(workspace, observables, sam, datasetTS, sampleTS, TString(""), yearTS, hypoTS, merge, debug )
		dataSet.SetName(dataSet.GetName()+"_"+component+"_"+sampleTS.Data()+"_"+yearTS.Data()+"_"+hypoTS.Data()+"Hypo")
        if debug:
                print "Dataset entries:"
		print dataSet.sumEntries()
		print "Sample categories"
		sam.Print("v")

	nbins = myconfigfile["pdfList"][component][hypo][variable]["Bins"]
	minFit = myconfigfile["pdfList"][component][hypo][variable]["Min"]
	maxFit = myconfigfile["pdfList"][component][hypo][variable]["Max"]
	obs.setRange(minFit, maxFit)
	obs.setUnit( myconfigfile["pdfList"][component][hypo][variable]["Unit"] ) 
	if binned:
		obs.setBins(nbins)
		dataHist = TH1F("dataHist","dataHist",nbins,minFit,maxFit)
		dataSet.fillHistogram(dataHist,RooArgList(obs))
		dataSet = RooDataHist(dataSet.GetName(),dataSet.GetTitle(),RooArgList(obs),dataHist,1.0)

	if None == workspaceOut.data(dataSet.GetName()):
		dataSet = WS(workspaceOut, dataSet)
	
	print ""
	print "========================================="
	print "Build PDF to fit dataset:"
	print str(dataSet.GetName())
	print "========================================="
	print ""

	nickname = dataSet.GetName()
        doFit = True
	pdfDict = myconfigfile["pdfList"][component][hypo][variable]
	pdfType = myconfigfile["pdfList"][component][hypo][variable]["PDF"]
	title = myconfigfile["pdfList"][component][hypo][variable]["Title"]
	Xtitle = myconfigfile["AxisTitle"][variable][hypo]

	if "JohnsonSUPlus2Gaussian" in pdfType:
		pdf = BuildJohnsonSUPlus2GaussianPDF(workspaceOut, obs, nickname, pdfDict, debug)
        elif "JohnsonSUPlusGaussianPlusExponential" in pdfType:
                pdf = BuildJohnsonSUPlusGaussianPlusExponentialPDF(workspaceOut, obs, nickname, pdfDict, debug)
	elif "JohnsonSUPlusGaussian" in pdfType:
		pdf = BuildJohnsonSUPlusGaussianPDF(workspaceOut, obs, nickname, pdfDict, debug)
	elif "IpatiaGaussConv" in pdfType:
		pdf = BuildIpatiaGaussConvPDF(workspaceOut, obs, nickname, pdfDict, debug)
	elif "IpatiaPlusExponential" in pdfType:
		pdf = BuildIpatiaPlusExponentialPDF(workspaceOut, obs, nickname, pdfDict, debug)
	elif "IpatiaPlusGaussian" in pdfType:
		pdf = BuildIpatiaPlusGaussianPDF(workspaceOut, obs, nickname, pdfDict, debug)
	elif "IpatiaPlusJohnsonSU" in pdfType:
		pdf = BuildIpatiaPlusJohnsonSUPDF(workspaceOut, obs, nickname, pdfDict, debug)
	elif "Ipatia" in pdfType:
		pdf = BuildIpatiaPDF(workspaceOut, obs, nickname, pdfDict, debug)
	elif "CrystalBallPlusExponential" in pdfType:
		pdf = BuildCrystalBallPlusExponentialPDF(workspaceOut, obs, nickname, pdfDict, debug)
	elif "CrystalBallPlusGaussian" in pdfType:
		pdf = BuildCrystalBallPlusGaussianPDF(workspaceOut, obs, nickname, pdfDict, debug)
        elif "DoubleGaussian" in pdfType:
                pdf = BuildDoubleGaussPDF(workspaceOut, obs, nickname, pdfDict, debug)
	elif "Gaussian" in pdfType:
		pdf = BuildGaussPDF(workspaceOut, obs, nickname, pdfDict, debug)
	elif "DoubleCrystalBall" in pdfType:
		pdf = BuildDoubleCrystalBallPDF(workspaceOut, obs, nickname, pdfDict, debug)
	elif "CrystalBall" in pdfType:
		pdf = BuildCrystalBallPDF(workspaceOut, obs, nickname, pdfDict, debug)
	elif "ExponentialPlusConstant" in pdfType:
		pdf = BuildExponentialPlusConstantPDF(workspaceOut, obs, nickname, pdfDict, debug)
	elif "Exponential" in pdfType:
		pdf = BuildExponentialPDF(workspaceOut, obs, nickname, pdfDict, debug)
	elif "JohnsonSU" in pdfType:
		pdf = BuildJohnsonSUPDF(workspaceOut, obs, nickname, pdfDict, debug)
	elif "RooKeysPdf" in pdfType:
		pdf = BuildRooKeysPdf(workspaceOut, obs, nickname, pdfDict, dataSet, debug)
		doFit = False
	elif "TakeInputPdf" in pdfType:
		pdf = TakeInputPdf(workspaceOut, pdfDict)
	else:
		print "ERROR: "+pdfType+" pdf not currently handled"
		exit(-1)

        if doFit and not superimpose:
                print ""
                print "========================================="
                print "Fit PDF:"
                print str(pdf.GetName())
                print "to dataset:"
                print str(dataSet.GetName())
                print "========================================="
                print ""
                
                fitResult = WS(workspaceOut, pdf.fitTo(dataSet,
                                                       RooFit.Range(minFit,maxFit),
                                                       RooFit.Save(1),
                                                       RooFit.Optimize(2),
                                                       RooFit.Strategy(2),
                                                       RooFit.Verbose(False),
                                                       RooFit.Timer(True),
						       RooFit.Minimizer("Minuit2", "migrad"),
                                                       RooFit.Offset(True))
                               )
                
                fitResult.SetName("FitTo_"+dataSet.GetName())
                fitResult.SetTitle("Fit to "+dataSet.GetTitle())
                
                print ""
                print "========================================="
                print "Fit done. Summarizing results:"
                print "========================================="
                print ""
                
                fitResult.Print("v")
                fitResult.covarianceMatrix().Print("v")
                fitResult.correlationMatrix().Print("v")
        else:
                fitResult = None
                
        print ""
        print "========================================="
        print "Saving plot"
        print "========================================="
        print ""
                
	text = "LHCb simulation"
	if "Comb" in component:
		text = "LHCb"

	namefile = outputplotdir+"Template_"+nickname+"_"+str(variable)
	if binned:
		namefile += "_binned"
	if superimpose:
		namefile += "_noFit"
	if logScale:
		namefile += "_logScale"
	namefile += ".pdf"

	makeCanvas(dataSet,
		   pdf,
		   obs,
                   fitResult,
		   minFit,
		   maxFit,
		   nbins,
		   text,
		   title,
		   Xtitle,
		   logScale,
		   namefile)

	if save:
		print ""
		print "========================================="
		print "Saving output workspace"
		print "========================================="
		print ""

		if debug:
			workspaceOut.Print()
			
		workspaceOut.SaveAs(outputFile)

	print ""
	print "========================================="
	print "Pretty-print fit results"
	print "========================================="
	print ""
	from B2DXFitters import FitResultGrabberUtils
	if None != fitResult:
		FitResultGrabberUtils.PrintLatexTable(fitResult)
	

#------------------------------------------------------------
_usage = '%prog [options]'

parser = OptionParser( _usage )

parser.add_option( '-d', '--debug',
		   action = 'store_true',
		   dest = 'debug',
		   default = False,
		   help = 'print debug information while processing'
		   )
parser.add_option( '--save',
		   action = 'store_true',
		   dest = 'save',
		   default = False,
		   help = 'save output workspace to file'
		   )
parser.add_option( '--configName',
		   dest = 'configName',
		   default = 'MyConfigFile',
		   help = 'configuration file name'
		   )
parser.add_option( '--inputFile',
		   dest = 'inputFile',
		   default = 'MyInputFile.root',
		   help = 'input file containing workspace with MC/data samples to fit'
		   )
parser.add_option( '--workData',
		   dest = 'workData',
		   default = 'workspace',
		   help = 'workspace containing MC/data samples to fit'
		   )
parser.add_option( '--workOut',
		   dest = 'workOut',
		   default = 'workOut',
		   help = 'workspace to store fit results, pdfs, observables'
		   )
parser.add_option( '--variable',
		   dest = 'variable',
		   default = 'BeautyMass',
		   help = 'observable name'
		   )
parser.add_option( '--component',
		   dest = 'component',
		   default = 'Bd2DPi',
		   help = 'component name to fit'
		   )
parser.add_option( '-m', '--mode',
		   dest = 'mode',
		   metavar = 'MODE',
		   default = 'KPiPi',
		   help = 'mode: choose all, KKPi, KPiPi, PiPiPi, nonres, kstk, phipi, 3modeskkpi'
		   )
parser.add_option( '-p', '--pol','--polarity',
		   dest = 'pol',
		   metavar = 'POL',
		   default = 'down',
		   help = 'Sample: choose up or down '
		   )
parser.add_option( '--year',
		   dest = 'year',
		   default = '2011',
		   help = 'year of data taking can be: 2011, 2012, run1')
parser.add_option( '--merge',
		   dest = 'merge',
		   default = 'both',
		   help = 'for merging magnet polarities use: --merge pol, for merging years of data taking use: --merge year, for merging both use: --merge both'
		   )
parser.add_option( '--hypo',
		   dest = 'hypo',
		   default = 'Bd2DPi',
		   help = 'bachelor mass hypothesys')
parser.add_option( '--binned',
		   action = 'store_true',
		   dest = 'binned',
		   default = False,
		   help = 'performed binned maximum likelihood fit (faster)'
		   )
parser.add_option( '--superimpose',
		   action = 'store_true',
		   dest = 'superimpose',
		   default = False,
		   help = 'plot PDF on data without fitting (use initial parameters)'
		   )
parser.add_option( '--logScale',
		   action = 'store_true',
		   dest = 'logScale',
		   default = False,
		   help = 'use log scale for vertical axis'
		   )
parser.add_option( '--outputFile',
		   dest = 'outputFile',
		   default = 'MyOutputFile.root',
		   help = 'output file to store fit results')
parser.add_option( '--outputplotdir',
		   dest = 'outputplotdir',
		   default = 'MyOutputDir',
		   help = 'output directory to store plots'
		   )
parser.add_option( '--initial',
		   dest = 'initial',
		   default = '',
		   help = 'file to take the output workspace from (if it exists)'
		   )
#------------------------------------------------------------
if __name__ == '__main__' :
	( options, args ) = parser.parse_args()
	
	if len( args ) > 0 :
		parser.print_help()
		exit( -1 )
		
	config = options.configName
       	last = config.rfind("/")
	directory = config[:last+1]
	configName = config[last+1:]
	p = configName.rfind(".")
	configName = configName[:p]
	
	import sys
	sys.path.append(directory)
	
	print "Config file name: "+configName
	print "Directory: "+directory
	
	fitShapes( options.debug,
		   configName,
		   options.inputFile,
		   options.outputFile,
		   options.workData,
		   options.workOut,
		   options.save,
		   options.initial,
		   options.variable,
		   options.component,
		   options.mode,
		   options.pol,
		   options.year,
		   options.merge,
		   options.hypo,
		   options.binned,
		   options.superimpose,
		   options.logScale,
		   options.outputplotdir)
	
