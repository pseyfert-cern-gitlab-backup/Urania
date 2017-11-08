from ROOT import *
from copy import deepcopy
from math import exp
from numpy import array

f = TFile( 'BRprofile_old.root' )
canvas = f.Get( 'Profile' )
for el in canvas.GetListOfPrimitives():
    if el.GetName() == 'nll_MainModel_TIS_data_with_constr_Profile[BR]_Norm[BR]':
        profile = deepcopy( el )

x = Double( 0. )
y = Double( 0. )

npoints = profile.GetN() - 1

from math import exp
xvals, yvals = [], []
for i in xrange( npoints ):
    profile.GetPoint( i, x, y )
    xvals.append( 1*x )
    yvals.append( exp( -y ) )
    profile.SetPoint( i, xvals[ -1 ], yvals[ -1 ] )

norm = sum( yvals )
for i, (x, y) in enumerate( zip( xvals, yvals ) ):
    profile.SetPoint( i, x, y/norm )
    yvals[ i ] = y/norm

for i in xrange(1,len(yvals)):
    yvals[ i ] += yvals[ i - 1 ]

for i in xrange( 1, npoints ):
    profile.SetPoint( i, xvals[ i ], yvals[ i ] )
    
c = TCanvas()
profile.Draw()

'''
hist, hcum = MakeLimitPlot( profile )

c = TCanvas( 'Prob', 'Prob' )
c.Divide( 1, 2 )
c.cd(1)
hist.Draw()
c.cd(2)
hcum.Draw()
line95 = TLine( 0., 0.95, 0.03, 0.95 )
line90 = TLine( 0., 0.90, 0.03, 0.90 )
for line in ( line95, line90 ):
    line.SetLineColor(kRed)
    line.Draw('SAME')
canvas.Draw()
'''
