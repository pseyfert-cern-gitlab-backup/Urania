# Code to get the plots for the BR limit from the likelihood profile

from ROOT import *
from copy import deepcopy
from math import exp
from numpy import array, interp

gROOT.ProcessLine( '.x lhcbStyle.C' )

CATEGORIES = [
    'TOS1_TOS2', 
#    'TOS1',
#    'TOS2',
#    'TIS',
#    'TOS1_TOS2_TIS'
    ]

def GetGraphVals( graph ):
    x = Double(0.)
    y = Double(0.)
    xvals, yvals = [], []
    for i in xrange( graph.GetN() ):
        graph.GetPoint( i, x, y )
        xvals.append( 1*x )
        yvals.append( 1*y )
    return xvals, yvals

def MakeLimitPlot( curve ):
    xvals, yvals = [], []
    # First and last point values are 0 (the y value is the same as the next/previous point)
    npoints = curve.GetN() - 1
    for i in xrange( 2, npoints ):
        x = Double( 0. )
        y = Double( 0. )
        curve.GetPoint( i, x, y )
        xvals.append( 1.*x )
        yvals.append( exp( -y ) )
    
    graph = TGraph( len(xvals), array(xvals), array(yvals)/sum(yvals) )
    graph.GetXaxis().SetTitle( 'B(K_{S}^{0}#rightarrow#mu^{+}#mu^{-})' )
    
    graph.SetLineColor(kBlue)
    
    ycvals = array(yvals)
    for i in xrange(1, len(ycvals)):
        ycvals[ i ] += ycvals[ i - 1 ]
    
    gcum = TGraph( len(xvals), array(xvals), ycvals/sum(yvals) )

    return graph, gcum

def GetXfromY( graph, *args ):
    xvals, yvals = GetGraphVals( graph )
    import numpy
    xvals = numpy.array(xvals)
    yvals = numpy.array(yvals)
    res   = numpy.interp(args, yvals, xvals)
    return res

def RemovePointsBefore( val, graph ):
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

def RemovePointsAfter( val, graph ):
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
    if at_start:
        xvals, yvals = GetGraphVals( graph )
        xvals = [x] + xvals
        yvals = [y] + yvals
        for i, (x, y) in enumerate(zip(xvals, yvals)):
            graph.SetPoint( i, x, y )
    else:
        graph.SetPoint( graph.GetN(), x, y )

#gStyle.SetOptStat(0)
gROOT.ProcessLine( '.x lhcbStyle.C' )
MINBR   = 0#0
MAXBR   = 4#30
MINPROB = 0.8
MAXPROB = 1.#1.05

def makePlots( cat ):

    print ' === Category:', cat, '==='
    
    f = TFile( 'BRprofile_' + cat + '.root' )
    #f = TFile( 'BRprofile_BkgSyst_' + cat + '.root' )
    #f = TFile( 'BRprofile_BkgSyst_FixExpo_' + cat + '.root' )
    canvas = f.Get( 'Profile' )
    names = ['nll_MainModel_TIS_data_with_constr_Profile[BR]_Norm[BR]',
             'nll_MainModel_TOS1_data_with_constr_Profile[BR]_Norm[BR]',
             'nll_MainModel_TOS2_data_with_constr_Profile[BR]_Norm[BR]']
    for el in canvas.GetListOfPrimitives():
        if el.GetName() in names:
            profile = deepcopy( el )

    hist, hcum = MakeLimitPlot( profile )
    #hist.GetXaxis().SetRange( 1, hist.GetNbinsX() )

    hcum.GetYaxis().SetRangeUser( MINPROB, MAXPROB )
    hcum.GetXaxis().SetRangeUser( MINBR, MAXBR )

    c = TCanvas( 'Lim_' + cat, 'Lim' + cat )
    #c.Divide( 1, 2 )
    #c.cd(1)
    #hist.Draw()
    #c.cd(2)
    hcum.GetYaxis().SetNdivisions( 505 )
    hcum.GetXaxis().SetNdivisions( 504 )
    hcum.GetYaxis().SetTitle( 'CL' )
    hcum.GetXaxis().SetTitle( 'B(K_{S}^{0}#rightarrow#mu^{+}#mu^{-}) #times10^{9}' )
    hcum.GetXaxis().SetTitleOffset( 1. )
    hcum.Draw()

    x95, x90 = GetXfromY( hcum, 0.95, 0.9 )

    hcumfill90 = hcum.Clone()
    RemovePointsAfter( x90, hcumfill90 )
    addPoint( hcumfill90, x90, 0.9 )
    addPoint( hcumfill90, x90, 0 )
    hcumfill90.SetPoint( hcumfill90.GetN(), x90, 0 )
    hcumfill90.SetFillColor(kViolet)
    hcumfill90.SetFillStyle(3001)
    hcumfill90.Draw('][FSAME')

    hcumfill95 = hcum.Clone()
    RemovePointsAfter( x95, hcumfill95 )
    RemovePointsBefore( x90, hcumfill95 )
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
    #canvas.Draw()

    print '-- Limit at 95 % CL:', x95
    print '-- Limit at 90 % CL:', x90

    '''
    c.Print( c.GetName() + '.pdf' )
    c.Print( c.GetName() + '.png' )
    c.Print( c.GetName() + '.C' )
    '''

    return c, hcumfill95, hcumfill90, hcum, lines, text

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
