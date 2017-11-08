from ROOT import *

cats = ['TOS1_', 'TOS2_', 'TIS_']
bins = xrange(3, 10)

f = TFile( 'FitPlots_' + ''.join( cats )[:-1] + '.root' )

for c in cats:
    for b in bins:
        canvas = f.Get( c + str( b ) )
        canvas.Print( 'plots/' + canvas.GetName() + '.pdf' )
