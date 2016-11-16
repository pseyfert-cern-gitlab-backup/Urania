# Code to get the plots for the BR limit from the likelihood profile

from ROOT import *
from copy import deepcopy
from math import exp
from numpy import array

gROOT.ProcessLine( '.x lhcbStyle.C' )

#ifile = TFile( 'ToyMCstudy10k.root' )
#PLOTS = [7,9]
#ifile = TFile( 'ToyMCstudy30k.root' )
#PLOTS = [2,3,4,6,10,13,14,17,18,19]
ifile = TFile( 'ToyMCstudy90k.root' )
PLOTS = [0,1,3,4,5,6,7,8,9,11,13,14,16,17]
'''
for el in canvas.GetListOfPrimitives():
    if el.GetName() == 'nll_MainModel_TIS_data_with_constr_Profile[BR]_Norm[BR]':
        profile = deepcopy( el )
'''

def HistFromRooCurve( name, curve, xvals, yvals ):
    bounds = array(xvals + [xvals[-1] + 0.001])
    hist = TH1D( name, name, len( xvals ), bounds )
    for i, y in enumerate( yvals ):
        hist.SetBinContent( i + 1, y )
    return hist

def MakeLimitPlot( curve ):
    # Last point is 0 don't know why
    npoints = curve.GetN() - 1

    xvals, yvals = [], []
    for i in xrange( npoints ):
        x = Double( 0. )
        y = Double( 0. )
        curve.GetPoint( i, x, y )
        xvals.append( 1.*x )
        yvals.append( exp( -y ) )
    
    hist = HistFromRooCurve( 'BRlimit', curve, xvals, yvals )
    hist.GetXaxis().SetTitle( 'BR(K_{S}^{0}#rightarrow#mu^{+}#mu^{-})' )
    hist.Scale( 1./hist.GetSumOfWeights() )
    hist.SetLineColor(kBlue)
    hcum = hist.GetCumulative()
    return hist, hcum

def GetXfromY( y, hist ):
    xvals = [ hist.GetBinCenter( i + 1 ) for i in xrange( hist.GetNbinsX() ) ]
    yvals = [ hist.GetBinContent( i + 1 ) for i in xrange( hist.GetNbinsX() ) ]
    i = 0
    while y > yvals[ i ]:
        i += 1
    return hist.GetBinLowEdge( i + 1 )

def DrawOneToy( ifile, numb ):

    def GetBinFromX( x, hist):
        xvals = [ hist.GetBinLowEdge( i + 1 ) for i in xrange( hist.GetNbinsX() ) ]
        i = 0
        while x > xvals[ i ]:
            i += 1
        return i

    profile = ifile.Get( 'ProfileFrame_' + str( numb ) )
    profile = profile.getCurve( 'nll_MainModel_hmaster_with_constr_Profile[BR]_Norm[BR]' )

    MINBR   = 0.
    MAXBR   = 30.
    MINPROB = 0.8
    MAXPROB = 1.05

    hist, hcum = MakeLimitPlot( profile )
    hist.GetXaxis().SetRange( 1, hist.GetNbinsX() )

    hcum.GetYaxis().SetRangeUser( MINPROB, MAXPROB )
    hcum.GetXaxis().SetRangeUser( MINBR, MAXBR )

    name = 'Prob_' + str( numb )
    c = TCanvas( name, name )
    c.Divide( 1, 2 )
    c.cd(1)
    hist.Draw()
    c.cd(2)
    hcum.Draw()

    x95 = GetXfromY( 0.95, hcum )
    x90 = GetXfromY( 0.90, hcum )

    hcumfill90 = hcum.Clone()
    hcumfill90.GetXaxis().SetRange( GetBinFromX( MINBR, hcumfill90 ), GetBinFromX( x90, hcumfill90 ) )
    hcumfill90.SetFillColor(kViolet)
    hcumfill90.SetFillStyle(3001)
    hcumfill90.Draw('][SAME')

    hcumfill95 = hcum.Clone()
    hcumfill95.GetXaxis().SetRange( GetBinFromX( x90, hcumfill95 ) + 1, GetBinFromX( x95, hcumfill95 ) )
    hcumfill95.SetFillStyle(3001)
    hcumfill95.SetFillColor(kAzure)
    hcumfill95.Draw('][SAME')

    line95_h = TLine( MINBR, 0.95, x95, 0.95 )
    line90_h = TLine( MINBR, 0.90, x90, 0.90 )
    line95_v = TLine( x95, MINPROB, x95, 0.95 )
    line90_v = TLine( x90, MINPROB, x90, 0.90 )
    for line in ( line95_h, line90_h, line95_v, line90_v ):
        line.SetLineColor(kRed)
        line.SetLineStyle(kDotted)
        line.SetLineWidth( 2 )
        line.Draw('SAME')
    c.Update()

    return c, x90, x95

def GetMeanSigma( dic ):
    m = 0
    for i, evt in dic.iteritems():
        m += evt
    m /= float( len( dic ) )
    
    s2 = 0
    for i, evt in dic.iteritems():
        s2 += (m - evt)**2
    n = len( dic )
    from math import sqrt
    return m, sqrt( s2/(n-1) )

cdic  = {}
lim90 = {}
lim95 = {}

gROOT.SetBatch(1)
for i in PLOTS:
    c, x90, x95 = DrawOneToy( ifile, i )
    cdic[ i ]  = c
    lim90[ i ] = x90
    lim95[ i ] = x95
gROOT.SetBatch(0)

print '-- 90 limit:', GetMeanSigma( lim90 )
print '-- 95 limit:', GetMeanSigma( lim95 )
