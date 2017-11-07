from ROOT import TFile, TEfficiency, TH1D, TH2D, gROOT, Math, TFeldmanCousins
from ROOT import TCanvas, TLatex, TLegend, kRed, kGreen
import numpy as np
from math import *
import math
from array import array


############# Return tree from file #############

def returnTree(filename, foldername, tuplename, option = ""):

    file = TFile.Open( filename, option )
    if foldername == ""   : tree = file.Get( tuplename )
    else                  : tree = file.Get( foldername+"/"+tuplename )
    tree.SetDirectory(gROOT)

    del file

    return tree


############# calculate efficiency and uncertainties from signal in matched and failed (error propagation) #############

def calcEffAndErrorGauss(match_sig, fail_sig, matchE_sig, failE_sig, debug=True):

    #calculate efficiency
    eff = match_sig/(match_sig + fail_sig)

    #calculate error from gaussian propagation (match/fail orthogonal)
    err = sqrt( (matchE_sig * (1. - eff))**2 + (matchE_fail * eff)**2 )

    return eff, err


############# calculate efficiency and uncertainties from signal without background / matched and failed (Jeroen) #############

def calcEffAndErrorNoBkg(n_tot, match_tot, CL=0.6827, debug=True):

    pEff = TEfficiency()
    pEff.SetStatisticOption(TEfficiency.kFFC)

    eff = 0. if n_tot == 0. else match_tot/n_tot
    lowerLimit = pEff.FeldmanCousins( int(n_tot), int(match_tot), CL, False)
    upperLimit = pEff.FeldmanCousins( int(n_tot), int(match_tot), CL, True)

    if debug: InfoMsg("Total efficiency = " + str(eff) + " +" + str(upperLimit-eff) + " -" + str(eff-lowerLimit))

    return eff, upperLimit-eff, eff-lowerLimit

############# calculate efficiency and uncertainties from signal and background / matched and failed (Jeroen) #############

def calcEffAndError(n_tot, match_tot, n_bkg, match_bkg, CL=0.6827, debug=True):

    #number of sigmas calculated from CL
    sigma = Math.gaussian_quantile( 0.5*(1.0+CL), 1.0 )

    #Physical bound
    if match_bkg > n_bkg: match_bkg = n_bkg

    #background efficiency
    eff_bkg = 0. if match_bkg == 0. else match_bkg/n_bkg

    #calculate signal yield and match
    n_sig = n_tot - n_bkg
    if n_sig < 1.: n_sig = 1.
    match_sig = match_tot - match_bkg
    if match_sig < 0.: match_sig = 0.

    #Physical bound
    if match_sig > n_sig: match_sig = n_sig

    #calculate efficiency
    eff_sig = match_sig/n_sig

    ###calculate binomial uncertainties###
    err_Msig_up   = sigma*sqrt( eff_sig*(1.0-eff_sig) / n_sig )
    err_Msig_down = err_Msig_up

    #use FC for low statistics and close to boundaries
    if n_sig < 2000 and (5.*err_Msig_up+eff_sig >= 1. or -5.*err_Msig_down+eff_sig <= 0.):

        pEff = TEfficiency()
        pEff.SetStatisticOption(TEfficiency.kFFC)

        #binomial error on matched signal from FC
        err_Msig_up   = pEff.FeldmanCousins( int(n_sig), int(match_sig), CL, False ) - eff_sig
        err_Msig_down = eff_sig - pEff.FeldmanCousins( int(n_sig), int(match_sig), CL, False )

    if debug: InfoMsg("Binomial efficiency error: +" + str(err_Msig_up) + " -" + str(err_Msig_down))


    ###FC poissonian error for number of bkg###
    pPoisson = TFeldmanCousins(CL)

    #background uncertainty
    var_Nbkg_down = sigma*sqrt(n_bkg)
    var_Nbkg_up   = var_Nbkg_down

    #low background statistics
    if n_bkg < 25:
        var_Nbkg_down = n_bkg - pPoisson.CalculateLowerLimit(n_bkg,0)
        var_Nbkg_up   = pPoisson.CalculateLowerLimit(n_bkg,0) - n_bkg

    if var_Nbkg_down >= n_sig: var_Nbkg_down = n_sig - 1.

    #calculate effect of background fluctuations
    eff_bkg_up   = (match_sig + eff_bkg*var_Nbkg_up) / (n_sig + var_Nbkg_up)
    eff_bkg_down = (match_sig - eff_bkg*var_Nbkg_down) / (n_sig - var_Nbkg_down)

    if eff_bkg_down < 0.: eff_bkg_down = 0.
    err_Nbkg_up   = eff_sig - eff_bkg_up if eff_bkg_up < eff_bkg_down else eff_sig - eff_bkg_down
    err_Nbkg_down = -eff_sig - eff_bkg_down if eff_bkg_up > eff_bkg_down else -eff_sig + eff_bkg_up

    if debug: InfoMsg("Poissonian background error: +" + str(err_Nbkg_up) + " -" + str(err_Nbkg_down))


    ###Binomial error for matched bkg###
    err_Mbkg_up   = 0. if n_bkg == 0. else sigma*sqrt(1.0-eff_bkg)/n_bkg
    err_Mbkg_down = err_Mbkg_up

    #use FC for low statistics and close to boundaries
    if n_bkg < 2000 and (3./sigma*err_Mbkg_up+eff_bkg >= 1. or -3./sigma*err_Mbkg_down+eff_sig <= 0.):

        pEff = TEfficiency()
        pEff.SetStatisticOption(TEfficiency.kFFC)

        #binomial error on matched bkg from FC
        err_Mbkg_up   = pEff.FeldmanCousins( int(n_bkg), int(match_bkg), CL, False ) - eff_bkg
        err_Mbkg_down = eff_bkg - pEff.FeldmanCousins( int(n_bkg), int(match_bkg), CL, False )

    #convert to frame of signal eff.
    err_Mbkg_down = err_Mbkg_down*n_bkg/n_sig
    err_Mbkg_up   = err_Mbkg_up*n_bkg/n_sig

    if debug: InfoMsg("Binomial background error: +" + str(err_Mbkg_up) + " -"+ str(err_Mbkg_down))


    ###Add up all errors quadratically
    err_tot_down = sqrt(err_Msig_down**2 + err_Mbkg_down**2 + err_Nbkg_down**2)
    err_tot_up   = sqrt(err_Msig_up**2 + err_Mbkg_up**2 + err_Nbkg_up**2)

    if (eff_sig - err_tot_down) < 0.: err_tot_down = eff_sig
    if (eff_sig + err_tot_up) > 1.: err_tot_up = 1.-eff_sig

    if debug: InfoMsg("Total efficiency =" +  str(eff_sig) +  " +" +  str(err_tot_up) +  " -" +  str(err_tot_down))

    return eff_sig, err_tot_up, err_tot_down


# ------------------------------------------------------

# ------------------------------------------------------
def multiplicityRatio(treeData, treePlusMC, treeMinusMC, weightVar, method, min, max, plotWeights = True):

    n_bins = 200

    mcMultiplicity = TH1D("mcMultiplicity","mcMultiplicity",n_bins, min, max)
    dataMultiplicity = TH1D("dataMultiplicity","dataMultiplicity",n_bins, min, max)
    ratio = TH1D("ratio","ratio",n_bins, min, max)


#    bool use_ntracks = false;


    #draw multiplicity into histograms
    treeData.Draw(weightVar+" >> dataMultiplicity")
    treePlusMC.Draw(weightVar+" >> mcMultiplicity")
    treeMinusMC.Draw(weightVar+" >> +mcMultiplicity")

    #set square sum weights and normalise
    dataMultiplicity.Sumw2()
    dataMultiplicity.Scale( 1.0/dataMultiplicity.Integral(1,n_bins) )
    mcMultiplicity.Sumw2()
    mcMultiplicity.Scale( 1.0/mcMultiplicity.Integral(1,n_bins) )


    if plotWeights:
        c = TCanvas("c","mc mult.")
        mcMultiplicity.SetLineColor(kRed)
        mcMultiplicity.Draw("E")
        dataMultiplicity.SetLineColor(kGreen+2)
        dataMultiplicity.Draw("ESAME")
        c.Print("weighting"+method+".eps")

    #get ratio by dividing data by mc
    ratio.Sumw2()
    ratio.Divide(dataMultiplicity, mcMultiplicity)

    if plotWeights :
        c1 = TCanvas("c1","weight")
        ratio.Draw()
        c1.Print("weight.eps")
    ratio.SetDirectory(gROOT)

    return ratio

# script doing the actual plotting
def do1DPlot(path, name, title, method, datahist, mchist, data_version, mc_version, verbose = False, polarity = ""):

    plot_hist = datahist.Clone()
    plot_hist_MC = datahist.Clone()

    #read in x axis and errors to get xmin, xmax, x_size
    x_size = plot_hist.GetN()
    x_arr_buf = datahist.GetX()
    x_arr_buf.SetSize(x_size)
    arr_x = array('d', x_arr_buf)
    xU_arr_buf = datahist.GetEXhigh()
    xU_arr_buf.SetSize(x_size)
    arr_xEU = array('d', xU_arr_buf)
    xL_arr_buf = datahist.GetEXlow()
    xL_arr_buf.SetSize(x_size)
    arr_xEL = array('d', xL_arr_buf)
    xmin = arr_x[0] - arr_xEL[0]
    xmax = arr_x[x_size-1] + arr_xEU[x_size-1]

    if verbose:
        InfoMsgList("Start creating plots for", name)
        InfoMsgList("Number of bins:", x_size)


    #formating of plot layout
    datahist.SetLineColor(1)
    datahist.SetMarkerColor(1)
    datahist.SetTitle("")
    datahist.SetMarkerStyle(20)
    #Just in case somehting goes wrong: axis and options anyway taken from dedicated hist
    datahist.GetXaxis().SetTitle(title)
    datahist.GetYaxis().SetTitle("#varepsilon")
    datahist.GetXaxis().SetTitleOffset(0.5)
    datahist.GetXaxis().SetTitleSize(0.06)
    datahist.GetXaxis().SetTitleFont(132)
    datahist.GetXaxis().SetLabelSize(0.05)
    datahist.GetXaxis().SetLabelFont(132)
    datahist.GetYaxis().SetTitleSize(0.06)
    datahist.GetYaxis().SetLabelSize(0.05)
    datahist.GetYaxis().SetTitleFont(132)
    datahist.GetYaxis().SetLabelFont(132)
    datahist.GetYaxis().SetTitleOffset(0.5)
    datahist.SetMaximum(1.05)
    datahist.SetMinimum(0.85)

    mchist.SetLineColor(kRed)
    mchist.SetMarkerColor(kRed)
    mchist.SetMarkerStyle(20)


    #add LHCb bla
    tex = TLatex()
    tex.SetNDC(True)
    tex.SetTextFont(132)
    tex.SetTextSize(0.06)
    tex.SetTextAlign(33)

    method_tex = TLatex()
    method_tex.SetNDC(True)
    method_tex.SetTextFont(132)
    method_tex.SetTextSize(0.06)
    method_tex.SetTextAlign(13)

    #create Legend
    leg = TLegend(0.55,0.175,0.875,0.325)
    leg.SetBorderSize(0)
    leg.SetTextFont(132)
    leg.SetTextSize(0.045)
    leg.SetFillColor(0)
    leg.AddEntry(datahist, data_version, "PL")
    leg.AddEntry(mchist, mc_version, "PL")

    #create empty histo for axis
    hist = TH1D ("hist","hist",100,xmin,xmax)
    hist.SetMaximum(1.05)
    hist.SetMinimum(0.85)
    hist.SetTitle("")
    hist.SetMarkerStyle(20)
    hist.GetXaxis().SetTitle(title)
    hist.GetYaxis().SetTitle("#varepsilon")
    hist.GetXaxis().SetTitleOffset(0.8)
    hist.GetXaxis().SetTitleSize(0.06)
    hist.GetXaxis().SetTitleFont(132)
    hist.GetXaxis().SetLabelSize(0.05)
    hist.GetXaxis().SetLabelFont(132)
    hist.GetYaxis().SetTitleSize(0.06)
    hist.GetYaxis().SetLabelSize(0.05)
    hist.GetYaxis().SetTitleFont(132)
    hist.GetYaxis().SetLabelFont(132)
    hist.GetYaxis().SetTitleOffset(0.8)

    #create canvas
    c = TCanvas("c_"+method, "c_"+method, 10,10,1000,600)
    c.SetBottomMargin(0.15)
    c.SetRightMargin(0.11)
    c.SetLeftMargin(0.1)
    hist.Draw("AXIS")
    tex.DrawLatex(0.855, 0.875, "LHCb preliminary")
    if (polarity != ""): tex.DrawLatex(0.855, 0.775, polarity)

    method_tex.DrawLatex(0.135, 0.875, method+" method")
    leg.Draw()
    datahist.Draw("P")
    mchist.Draw("PSAME")
    c.Print(path+name+"_"+method+".eps")
    c.SaveSource(path+name+"_"+method+".C")



def do2DPlot(path, name, title, method, datahist, mchist, data_version, mc_version, verbose = False, maxError = 0.03, maxDeviation = 0.3, ignoreBins = "P-ETA:1-2,5-1"):

    plot_hist = datahist.Clone("plot_hist")
    plot_hist_MC = mchist.Clone("plot_hist_MC")

    plot_hist.Divide(plot_hist_MC)

    #formating of plot points
    plot_hist.SetLineColor(1)
    plot_hist.SetMarkerColor(1)
    plot_hist.SetTitle("")
    plot_hist.SetMarkerSize(1.5)
    plot_hist.GetXaxis().SetTitle(title[0])
    plot_hist.GetYaxis().SetTitle(title[1])
    plot_hist.GetYaxis().SetTitleOffset(0.7)
    plot_hist.GetXaxis().SetTitleSize(0.06)
    plot_hist.GetXaxis().SetTitleFont(132)
    plot_hist.GetXaxis().SetLabelSize(0.05)
    plot_hist.GetXaxis().SetLabelFont(132)
    plot_hist.GetYaxis().SetTitleSize(0.06)
    plot_hist.GetYaxis().SetLabelSize(0.05)
    plot_hist.GetYaxis().SetTitleFont(132)
    plot_hist.GetYaxis().SetLabelFont(132)
    plot_hist.GetZaxis().SetLabelSize(0.05)
    plot_hist.GetZaxis().SetLabelFont(132)
    plot_hist.Sumw2()
    plot_hist.SetMaximum(1.15)
    plot_hist.SetMinimum(0.85)

    #read the ingored bins and fill dictionary
    ignoreBins_list = ignoreBins.split(';')
    ignoreBins_dict = {}
    for bins in ignoreBins_list:
            tmpvar = bins.split(':')
            tmpbin = tmpvar[1].split(',')
            tmpbinlist = [ i.split('-') for i in tmpbin]
            #convert string to int and fill dictionary 
            ignoreBins_dict[tmpvar[0]] = [map(int,i) for i in tmpbinlist]

    for pval in xrange(plot_hist.GetNbinsX()):
        for etaval in xrange(plot_hist.GetNbinsY()):
            #check for large uncertainies, mostly due to bad fit;
            if plot_hist.GetBinError(pval+1,etaval+1) > maxError:
                WarnMsg("Bin " + str(pval+1)  +","+ str(etaval+1) + " uncertainty =" + str(plot_hist.GetBinError(pval+1,etaval+1)) + " setting to 1.0 correction with 5% uncertainty!")
                WarnMsg("If this is expected, set option -maxError or -ignoreBins accordingly")
                plot_hist.SetBinContent(pval+1,etaval+1,1.0)
                plot_hist.SetBinError(pval+1,etaval+1,0.05)
            if  (name in ignoreBins_dict.keys() ) and [pval+1, etaval+1] in ignoreBins_dict[name]:
                InfoMsg("Bin " + str(pval+1)  +","+ str(etaval+1) + " uncertainty =" + str(plot_hist.GetBinError(pval+1,etaval+1)) + " is set to 1.0 correction with 5% uncertainty!")

            #check for large deviations from 1, mostly due to bad fit
            elif abs(1.-plot_hist.GetBinContent(pval+1,etaval+1)) > maxDeviation:
                WarnMsg( "Bin " + str(pval+1) +","+ str(etaval+1) + " value =" + str(plot_hist.GetBinContent(pval+1,etaval+1)) + " seems unreasonable, setting to 1.0 correction with 5% uncertainty!")
                WarnMsg( "This might be caused by a bad fit.")
                WarnMsg("If this is expected, set option -maxDeviation accordingly")
                plot_hist.SetBinContent(pval+1,etaval+1,1.0)
                plot_hist.SetBinError(pval+1,etaval+1,0.05)

    #add LHCb bla
    tex = TLatex()
    tex.SetNDC(True)
    tex.SetTextFont(132)
    tex.SetTextSize(0.06)
    tex.SetTextAlign(33)

    method_tex = TLatex()
    method_tex.SetNDC(True)
    method_tex.SetTextFont(132)
    method_tex.SetTextSize(0.06)
    method_tex.SetTextAlign(13)

    #create Legend
    leg = TLegend(0.55,0.175,0.875,0.325)
    leg.SetBorderSize(0)
    leg.SetTextFont(132)
    leg.SetTextSize(0.045)
    leg.SetFillColor(0)
    leg.AddEntry(plot_hist, data_version, "PL")
    leg.AddEntry(plot_hist_MC, mc_version, "PL")

    #create canvas
    c = TCanvas("c_"+method, "c_"+method, 10,10,1000,600)
    c.SetBottomMargin(0.15)
    c.SetRightMargin(0.11)
    plot_hist.Draw("COLZTEXTE")
    c.SetLogx()
    tex.DrawLatex(0.875, 0.98, "LHCb preliminary")
    method_tex.DrawLatex(0.125, 0.98, method+" efficiency ratio")
    plot_hist.SetName("Ratio")
    outfile = TFile(path+"Ratio_"+method+"_"+name+".root","RECREATE")
    outfile.cd()
    plot_hist.Write()
    outfile.Write()
    outfile.Close()
    c.Print(path+"Ratio_"+method+"_"+name+".eps")

def InfoMsg(message):
    print "[INFO]\t\t" + message
    return
def InfoMsgList(message, MsgList): #Why is overloading in python soooooo sloooow
    print "[INFO]\t\t" + message, MsgList
    return

def ErrorMsg(message):
    return "\033[91m[ERROR]\t\t" + message+ "\033[0m"

def WarnMsg(message):
    print "\033[93m[WARNING]\t" + message + "\033[0m"
    return
def WarnMsgList(message, MsgList):
    print "\033[93m[WARNING]\t" + message, MsgList, "\033[0m"
    return
