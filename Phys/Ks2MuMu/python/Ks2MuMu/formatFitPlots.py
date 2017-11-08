from ROOT import *
from collections import *
from copy import deepcopy

#gROOT.ProcessLine( '.x lhcbStyle.C' )
gStyle.SetTextFont(132)
gStyle.SetTextSize(0.06)
gROOT.SetBatch()

CATEGORIES = OrderedDict( [
        ( 'TOS1', range( 3, 10 ) ),
        ( 'TOS2', range( 3, 10 ) ),
        ( 'TIS' , range( 3, 10 ) ),
        ( 'TOS1_TOS2_TIS', range( 3, 10 ) )
        ] )

gStyle.SetOptTitle(0)

def makePlots( cat, bins ):
    print '-- Category:', cat
    ifile  = TFile( 'FitPlots_' + cat + '.root' )
    if cat == 'TOS1_TOS2_TIS':
        folder = 'ALL'
    else:
        folder = cat
    cat = cat.split( '_' )
    for c in cat:
        formatPlots( ifile, c, bins, folder )

def formatPlots( ifile, cat, bins, folder ):
    for i in bins:
        ic = ifile.Get( cat + '_' + str(i) )
        c = TCanvas( ic.GetName(), '' )
        ic.Copy( c )
        c.SetTitle( '' )
        name = folder + 'fitPlots/'
        if folder == 'ALL':
            name += folder
        name += c.GetName()
        
        for i, l in enumerate(ic.GetListOfPrimitives()):
            c.cd(i+1)
            l.Draw()

        c.cd(1)
        tp = TPaveText( 0.6, 0.8, 0.9, 0.9, 'NDC' )
        tp.AddText( 'LHCb Preliminary' )
        
        tp.SetFillColor( kWhite )
        tp.SetBorderSize( 0 )
        tp.Draw()
        
        c.Draw()
        c.cd(1).SetLogy()
        c.Update()

        c.Print( name + '.pdf' )
        c.Print( name + '.png' )
        c.Print( name + '.eps' )
        c.Print( name + '.C' )

for c, b in CATEGORIES.iteritems():
    makePlots( c, b )
