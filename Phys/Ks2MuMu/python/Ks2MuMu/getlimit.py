# Provide functions to get the limit after the main fit is done

from ROOT import *
from ROOT import RooStats as rst
from ROOT import RooFit as rf

import numpy as np
import math

# Minimum and maximum values for the CL and the BR
MINBR   = 0#0
MAXBR   = 10#4
MINPROB = 0.8
MAXPROB = 1.#1.05

def graphFromHist( hist ):
    '''
    Build a TGraph object from a TH1
    '''
    xvals, yvals = getHistVals( hist )
    return TGraph(len(xvals), np.array(xvals), np.array(yvals))

def getGraphVals( graph ):
    '''
    Store the x and y values from a TGraph into two lists
    '''
    x = Double(0.)
    y = Double(0.)
    xvals, yvals = [], []
    for i in xrange( graph.GetN() ):
        graph.GetPoint( i, x, y )
        xvals.append( 1*x )
        yvals.append( 1*y )
    return xvals, yvals

def getHistVals( hist ):
    '''
    Return two lists with the x and y values from a TH1 object
    '''
    xvals = []
    yvals = []
    for i in xrange(hist.GetNbinsX()):
        xvals.append(hist.GetXaxis().GetBinCenter(i + 1))
        yvals.append(hist.GetBinContent(i + 1))
    return xvals, yvals

def limitPlot( profile, write = True ):
    '''
    Return two histograms, one containing the probability and the other the cumulative of 
    '''
    
    hist = profile.Clone()
    hist.SetNameTitle('Probability', 'Probability')
    hist.GetXaxis().SetTitle( 'B(K_{S}^{0}#rightarrow#mu^{+}#mu^{-})' )
    hist.SetLineColor(kBlack)

    for i in xrange(hist.GetNbinsX()):
        cnt = hist.GetBinContent(i+1)
        cnt = math.exp( -cnt )
        hist.SetBinContent(i + 1, cnt)

    if write:
        hist.Write('Probability_NotNormalized')
    hist.Scale(1./hist.GetSumOfWeights())
    if write:
        hist.Write('Probability_Normalized')
    
    hcum = hist.GetCumulative()
    hcum.SetNameTitle('CL', 'CL')
    hcum.GetYaxis().SetRangeUser( MINPROB, MAXPROB )
    hcum.GetXaxis().SetRangeUser( MINBR, MAXBR )
    if write:
        hcum.Write()
    
    return hist, hcum

def getXfromY( hist, *args ):
    '''
    Get the x value for a given set of y values from a histogram
    '''
    xvals, yvals = getHistVals( hist )
    res = np.interp(args, yvals, xvals)
    return res

def removePointsBefore( val, graph ):
    '''
    Remove points before a certain value (to be used when drawing areas)
    '''
    x  = Double( 0 )
    y  = Double( 0 )
    ip = []
    for i in xrange( graph.GetN() ):
        graph.GetPoint( i, x, y )
        if x < val:
            ip.append( i )
    ip.reverse()
    for i in ip[1:]:
        graph.RemovePoint( 0 )

def removePointsAfter( val, graph ):
    '''
    Remove points after a certain value (to be used when drawing areas)
    '''
    x  = Double( 0 )
    y  = Double( 0 )
    ip = []
    for i in xrange( graph.GetN() ):
        graph.GetPoint( i, x, y )
        if x > val:
            ip.append( i )
    ip.reverse()
    for i in ip:
        graph.RemovePoint( i )

def addPoint( graph, x, y, at_start = False ):
    '''
    Add a point to a TGraph object
    '''
    if at_start:
        xvals, yvals = getGraphVals( graph )
        xvals = [x] + xvals
        yvals = [y] + yvals
        for i, (x, y) in enumerate(zip(xvals, yvals)):
            graph.SetPoint( i, x, y )
    else:
        graph.SetPoint( graph.GetN(), x, y )

def limitMCMC( workspace, poi, nuis_pars, results ):
    '''
    Get the limit using the MCMC bayesian method
    '''

    print '--- Starting to calculate MCMC limit'

    data = workspace.data('ALL')

    mc = rst.ModelConfig()
    mc.SetWorkspace(workspace)
    mc.SetPdf(workspace.pdf('MainModel'))
    mc.SetParametersOfInterest(RooArgSet(poi))
    mc.SetNuisanceParameters(nuis_pars)

    print '--- Configuration done'

    ph = rst.ProposalHelper()
    ph.SetVariables(results.floatParsFinal())
    ph.SetCovMatrix(results.covarianceMatrix())
    ph.SetUpdateProposalParameters(1)
    ph.SetCacheSize(100)
    pf = ph.GetProposalFunction()

    sp = rst.SequentialProposal(0.1)
    
    mcmc = rst.MCMCCalculator(data, mc)
    mcmc.SetProposalFunction(sp)
    mcmc.SetNumIters(10000)
    mcmc.SetNumBurnInSteps(50)
    mcmc.SetIntervalType(rst.MCMCInterval.kShortest)

    for cl in (95, 90):
        mcmc.SetConfidenceLevel(float(cl)/100)
        interval = mcmc.GetInterval()

        scl = str(cl)

        c_int = TCanvas('MCMCplot_' + scl)
        plot = rst.MCMCIntervalPlot(interval)
        plot.Draw()

        c_nuis = TCanvas('MCMCplot_NuisPars_' + scl)
        lst = mc.GetNuisanceParameters()
        n = lst.getSize()
        ny = TMath.CeilNint(TMath.Sqrt(n))
        nx = TMath.CeilNint(float(n)/ny)
        c_nuis.Divide(nx, ny)

        it = mc.GetNuisanceParameters().createIterator()
        ipad = 1
        nuis = it.Next()
        while nuis:
            c_nuis.cd(ipad)
            plot.DrawChainScatter(poi, nuis)
            ipad += 1
            nuis = it.Next()

        for c in (c_int, c_nuis):
            c.Write()

        print '--- ' + scl + ' % CL limits: [', interval.LowerLimit(), interval.UpperLimit(), ' ]'


def limitNLL( nll, var, nbins = 200, cname = 'Profile' ):
    '''
    Get the limit using the -logL profile of < var >
    '''

    print '--- Start to get limit from NLL'

    pl = nll.createProfile(RooArgSet(var))
    fr = var.frame( rf.Bins( nbins ), rf.Title( '' ) )
    pl.plotOn(fr, rf.ShiftToZero())
    c_pl = TCanvas( cname, cname )
    fr.Draw()
    fr.Write( cname + 'Frame' )
    c_pl.Write()

    print '\n--- Creating histogram'
    hist = pl.createHistogram('Profile', var,
                              rf.Binning(nbins), rf.Extended(False), rf.Scaling(False))
    hist.SetNameTitle('ProfileAsTH1', 'ProfileAsTH1')
    hist.Write()

    hist, hcum = limitPlot( hist )

    x95, x90 = getXfromY(hcum, 0.95, 0.90)
    
    whole = cosmetics(hcum, 'ALL')
    c_cum = whole[0]
    c_cum.SetNameTitle( cname + '_Cum', cname + '_Cum' )
    hcum.Draw()
    c_cum.Write()

    print '\n*** Limits ***'
    print '--- 95 % CL limit:', x95
    print '--- 90 % CL limit:', x90

    return whole

def cosmetics( hcum, cat ):
    '''
    Format the limit plot
    '''
    
    hcum.GetYaxis().SetRangeUser( MINPROB, MAXPROB )
    hcum.GetXaxis().SetRangeUser( MINBR, MAXBR )

    c = TCanvas( 'Lim_' + cat, 'Lim' + cat )
    hcum.GetYaxis().SetNdivisions( 505 )
    hcum.GetXaxis().SetNdivisions( 504 )
    hcum.GetYaxis().SetTitle( 'CL' )
    hcum.GetXaxis().SetTitle( 'B(K_{S}^{0}#rightarrow#mu^{+}#mu^{-}) #times10^{9}' )
    hcum.GetXaxis().SetTitleOffset( 1. )
    hcum.Draw('C')

    x95, x90 = getXfromY( hcum, 0.95, 0.9 )

    hcumfill90 = graphFromHist(hcum)
    removePointsAfter( x90, hcumfill90 )
    addPoint( hcumfill90, x90, 0.9 )
    addPoint( hcumfill90, x90, 0 )
    hcumfill90.SetPoint( hcumfill90.GetN(), x90, 0 )
    hcumfill90.SetFillColor(kViolet)
    hcumfill90.SetFillStyle(3001)
    hcumfill90.Draw('][FSAME')

    hcumfill95 = graphFromHist(hcum)
    removePointsAfter( x95, hcumfill95 )
    removePointsBefore( x90, hcumfill95 )
    addPoint( hcumfill95, x95, 0.95 )
    addPoint( hcumfill95, x90, 0.90, at_start = True )
    addPoint( hcumfill95, x90, 0, at_start = True )
    hcumfill95.SetPoint( hcumfill95.GetN(), x95, 0 )
    hcumfill95.SetFillStyle(3001)
    hcumfill95.SetFillColor(kAzure)
    hcumfill95.Draw('][FSAME')

    line95_h = TLine( MINBR, 0.95, x95, 0.95 )
    line90_h = TLine( MINBR, 0.90, x90, 0.90 )
    line95_v = TLine( x95, MINPROB, x95, 0.95 )
    line90_v = TLine( x90, MINPROB, x90, 0.90 )
    for line in ( line95_h, line90_h, line95_v, line90_v ):
        line.SetLineColor(kRed)
        line.SetLineStyle(kDotted)
        line.SetLineWidth( 2 )
        line.Draw('SAME')
    lines = line95_h, line90_h, line95_v, line90_v

    if cat in ( 'TIS', 'TOS2' ):
        text = TPaveText( 0.2, 0.8, 0.5, 0.9, 'NDC' )
    else:
        text = TPaveText( 0.6, 0.7, 0.9, 0.8, 'NDC' )
    text.SetFillColor( kWhite )
    text.SetBorderSize( 0 )
    text.AddText( 'LHCb Preliminary' )
    text.Draw()

    c.Update()

    print '-- Limit at 95 % CL:', x95
    print '-- Limit at 90 % CL:', x90
    
    '''
    c.Print( c.GetName() + '.pdf' )
    c.Print( c.GetName() + '.png' )
    c.Print( c.GetName() + '.C' )
    '''

    return c, hcumfill95, hcumfill90, hcum, lines, text

def makePlots( cat ):
    '''
    Function called when executing this as a main file
    '''

    print ' === Category:', cat, '==='
    
    f = TFile( 'BRprofile_' + cat + '.root' )
    #f = TFile( 'BRprofile_BkgSyst_' + cat + '.root' )
    #f = TFile( 'BRprofile_BkgSyst_FixExpo_' + cat + '.root' )
    
    profile = f.Get('ProfileAsTH1')
    profile = profile.Clone()
    profile.SetDirectory(0)
    f.Close()
    hist, hcum = limitPlot(profile, write = False)
    whole = cosmetics(hcum, cat)

    return whole

if __name__ == '__main__':
    
    CATEGORIES = [
        'TOS1_TOS2', 
        #    'TOS1',
        #    'TOS2',
        #    'TIS',
        #    'TOS1_TOS2_TIS'
        ]

    gROOT.ProcessLine( '.x lhcbStyle.C' )
    dic = {}
    for c in CATEGORIES:
        dic[c] = makePlots( c )

# Before fixing the bkg
#-- Limit at 95 % CL: 1.01224293745
#-- Limit at 90 % CL: 0.801961330842
# With a fix bkg
#-- Limit at 95 % CL: 0.929570925746
#-- Limit at 90 % CL: 0.736793568356
# After including bkg syst from fixing bkg
#-- Limit at 95 % CL: 1.02693511533
#-- Limit at 90 % CL: 0.812523509376
