#!/bin/sh
# -*- mode: python; coding: utf-8 -*-
# vim: ft=python:sw=4:tw=78:expandtab

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

RooAbsData.setDefaultStorageType(RooAbsData.Tree)
gROOT.SetBatch(True)
gStyle.SetOptStat(0)

#Input files MC Bu
treeBu = TChain("DecayTree")
'''
treeBu.Add("/eos/lhcb/wg/b2oc/TD_DPi_3fb/flavourtaggingMC/MC_Bu2D0PiFiltered_2011_PiandKHypo_magUp_S21_afterSelection_OSCombined_PID-corrected_new_reweighted_NoProdAsymm_calib_applySplineCalib.root")
treeBu.Add("/eos/lhcb/wg/b2oc/TD_DPi_3fb/flavourtaggingMC/MC_Bu2D0PiFiltered_2011_PiandKHypo_magDown_S21_afterSelection_OSCombined_PID-corrected_new_reweighted_NoProdAsymm_calib_applySplineCalib.root")
treeBu.Add("/eos/lhcb/wg/b2oc/TD_DPi_3fb/flavourtaggingMC/MC_Bu2D0PiFiltered_2012_PiandKHypo_magUp_S21_afterSelection_OSCombined_PID-corrected_new_reweighted_NoProdAsymm_calib_applySplineCalib.root")
treeBu.Add("/eos/lhcb/wg/b2oc/TD_DPi_3fb/flavourtaggingMC/MC_Bu2D0PiFiltered_2012_PiandKHypo_magDown_S21_afterSelection_OSCombined_PID-corrected_new_reweighted_NoProdAsymm_calib_applySplineCalib.root")
'''
treeBu.Add("/eos/lhcb/wg/b2oc/TD_DPi_3fb/flavourtaggingMCnoBDT/MC_Bu2D0PiFiltered_2011_PiandKHypo_magUp_S21_afterSelection_OSCombined_PID-corrected_new_calib_applySplineCalib.root")
treeBu.Add("/eos/lhcb/wg/b2oc/TD_DPi_3fb/flavourtaggingMCnoBDT/MC_Bu2D0PiFiltered_2011_PiandKHypo_magDown_S21_afterSelection_OSCombined_PID-corrected_new_reweighted_NoProdAsymm_calib_applySplineCalib.root")
treeBu.Add("/eos/lhcb/wg/b2oc/TD_DPi_3fb/flavourtaggingMCnoBDT/MC_Bu2D0PiFiltered_2012_PiandKHypo_magUp_S21_afterSelection_OSCombined_PID-corrected_new_reweighted_NoProdAsymm_calib_applySplineCalib.root")
treeBu.Add("/eos/lhcb/wg/b2oc/TD_DPi_3fb/flavourtaggingMCnoBDT/MC_Bu2D0PiFiltered_2012_PiandKHypo_magDown_S21_afterSelection_OSCombined_PID-corrected_new_reweighted_NoProdAsymm_calib_applySplineCalib.root")

#Input file MC Bd
#fileBd = TFile("/afs/cern.ch/work/v/vibattis/public/B2DX/Bd2DPi/Workspace/Nominal/work_dpi_mc_splinePreCalib.root")
fileBd = TFile("/afs/cern.ch/work/v/vibattis/public/B2DX/Bd2DPi/Workspace/Nominal/work_dpi_mc_splinePreCalib_noBDT.root")
workspace = fileBd.Get("workspace")
dataBd = workspace.data("dataSetMC_Bd2DPi_up_kpipi_2011_Bd2DPiHypo")
dataBd.append( workspace.data("dataSetMC_Bd2DPi_down_kpipi_2011_Bd2DPiHypo") )
dataBd.append( workspace.data("dataSetMC_Bd2DPi_up_kpipi_2012_Bd2DPiHypo") )
dataBd.append( workspace.data("dataSetMC_Bd2DPi_down_kpipi_2012_Bd2DPiHypo") )
treeBd = dataBd.tree()

#Make plots

print "Plotting Bu raw mistag..."
treeBu.Draw("MistagOS>>h_Bu_raw","TagDecOS!=0","goff")
h_Bu_raw = gDirectory.Get("h_Bu_raw")
h_Bu_raw.Scale( 1.0 / h_Bu_raw.GetMaximum() )
h_Bu_raw.SetLineWidth(2)
h_Bu_raw.SetLineColor(1)
h_Bu_raw.GetXaxis().SetTitle("#eta")
h_Bu_raw.SetTitle("")

print "Plotting Bu mistag after reweighting..."
treeBu.Draw("MistagOS>>h_Bu_weight","Reweight*ProdAsymmWeight*(TagDecOS!=0)","goff")
h_Bu_weight = gDirectory.Get("h_Bu_weight")
h_Bu_weight.Scale( 1.0 / h_Bu_weight.GetMaximum() )
h_Bu_weight.SetLineWidth(2)
h_Bu_weight.SetLineColor(2)
h_Bu_weight.GetXaxis().SetTitle("#eta")
h_Bu_weight.SetTitle("")

print "Plotting Bu mistag after reweighting and spline pre-calibration..."
treeBu.Draw("MistagCalibOS>>h_Bu_weight_spline","Reweight*ProdAsymmWeight*(TagDecCalibOS!=0)","goff")
h_Bu_weight_spline = gDirectory.Get("h_Bu_weight_spline")
h_Bu_weight_spline.Scale( 1.0 / h_Bu_weight_spline.GetMaximum() )
h_Bu_weight_spline.SetLineWidth(2)
h_Bu_weight_spline.SetLineColor(3)
h_Bu_weight_spline.GetXaxis().SetTitle("#eta")
h_Bu_weight_spline.SetTitle("")

print "Plotting Bd raw mistag..."
treeBd.Draw("MistagOS>>h_Bd_raw","TagDecOS_idx!=0","goff")
h_Bd_raw = gDirectory.Get("h_Bd_raw")
h_Bd_raw.Scale( 1.0 / h_Bd_raw.GetMaximum() )
h_Bd_raw.SetLineWidth(2)
h_Bd_raw.SetLineColor(4)
h_Bd_raw.GetXaxis().SetTitle("#eta")
h_Bd_raw.SetTitle("")

print "Plotting Bd mistag after spline pre-calibration..."
treeBd.Draw("MistagOSCalib>>h_Bd_spline","TagDecOSCalib_idx!=0","goff")
h_Bd_spline = gDirectory.Get("h_Bd_spline")
h_Bd_spline.Scale( 1.0 / h_Bd_spline.GetMaximum() )
h_Bd_spline.SetLineWidth(2)
h_Bd_spline.SetLineColor(5)
h_Bd_spline.GetXaxis().SetTitle("#eta")
h_Bd_spline.SetTitle("")

canv = TCanvas("canv")
canv.cd()
h_Bu_raw.Draw("HIST")
h_Bu_weight.Draw("HISTSAME")
h_Bu_weight_spline.Draw("HISTSAME")
h_Bd_raw.Draw("HISTSAME")
h_Bd_spline.Draw("HISTSAME")

leg = TLegend(0.2, 0.6, 0.5, 0.9)
leg.AddEntry(h_Bu_raw, "B_{u} raw", "L")
leg.AddEntry(h_Bu_weight, "B_{u} reweighted", "L")
leg.AddEntry(h_Bu_weight_spline, "B_{u} reweighted/spline pre-calib", "L")
leg.AddEntry(h_Bd_raw, "B_{d} raw", "L")
leg.AddEntry(h_Bd_spline, "B_{d} spline pre-calib", "L")
leg.Draw("SAME")

canv.SaveAs("plotMistag_noBDT.pdf")
