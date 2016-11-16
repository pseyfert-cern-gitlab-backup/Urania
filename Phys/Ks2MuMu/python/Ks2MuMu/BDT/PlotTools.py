#////////////////////////////////////////////////////////////////
#//                                                            //
#//  Python modules                                            //
#//                                                            //
#// ---------------------------------------------------------- //
#//                                                            //
#//  AUTHOR: Miguel Ramos Pernas                               //
#//  e-mail: miguel.ramos.pernas@cern.ch                       //
#//                                                            //
#//  Last update: 06/06/2016                                   //
#//                                                            //
#// ---------------------------------------------------------- //
#//                                                            //
#//  Description:                                              //
#//                                                            //
#//  This module implements different tools to generate plots  //
#//  using Root objects.                                       //
#//                                                            //
#// ---------------------------------------------------------- //
#////////////////////////////////////////////////////////////////


from ROOT import ( TCanvas, TLegend, TPaveText, gStyle,
                   TGraph, TGraphErrors, TH1,
                   TH1F, TH1D,
                   TH2F, TH2D,
                   kBlue, kRed, kOrange, kGreen, kMagenta, kCyan )
from array import array
import sys


#_______________________________________________________________________________
# Calculates the minimum distance between values in an iterable object
def CalcMinDist( lst ):
    lst = sorted( set( lst ) )
    lst = [ abs( lst[ i - 1 ] - lst[ i ] ) for i in xrange( 1, len( lst ) ) ]
    return min( lst )

#_______________________________________________________________________________
# Returns the histogram constructor given the type as a string
def HistFromType( tp, dim = 1 ):
    if tp not in ( 'float', 'double', 'int' ):
        print 'ERROR: Histogram type', tp, 'not known'
        return
    if dim == 1:
        if tp == 'float':
            return TH1F
        elif tp == 'double':
            return TH1D
        else:
            return TH1I
    elif dim == 2:
        if tp == 'float':
            return TH2F
        elif tp == 'double':
            return TH2D
        else:
            return TH2I
    else:
        print 'ERROR: Histogram dimension', dim, 'not allowed'

#_______________________________________________________________________________
# This function creates a 1-D adaptive binning histogram given a name, the
# minimum occupancy value and a list. Adding a list of weights is also possible.
def MakeAdaptiveBinnedHist( name, minocc, values, weights = False, **kwargs ):

    ''' These are the options that can be passed to the function '''
    if 'title' in kwargs: title = kwargs[ 'title' ]
    else: title = name
    if 'vmin' in kwargs:
        vmin   = kwargs[ 'vmin' ]
        values = [ val for val in values if val >= vmin ]
    if 'vmax' in kwargs:
        vmax   = kwargs[ 'vmax' ]
        values = [ val for val in values if val < vmax ]
    else:
        vmax   = max( values ) + CalcMinDist( values )/2.
    if 'xtitle' in kwargs: xtitle = kwargs[ 'xtitle' ]
    else: xtitle = name
    if 'ytitle' in kwargs: ytitle = kwargs[ 'ytitle' ]
    else: ytitle = 'Entries'
    if 'htype' in kwargs: histcall = HistFromType( kwargs[ 'htype' ] )
    else: histcall = TH1D
    
    ''' Calculates the array of weights '''
    length = len( values )
    if weights:
        sw    = float( sum( weights ) )
        nbins = int( sw )/minocc
    else:
        weights = length*[ 1. ]
        sw      = float( length )
        nbins   = length/minocc
    
    ''' If the occupancy requested is too big, an error message is displayed '''
    if nbins == 0:
        print 'ERROR: Occupancy requested is too big:', minocc
    
    ''' Creates a list with the values and the weights joint and sorts it by the values '''
    values = zip( values, weights )
    values.sort()
    
    ''' Fills the bins with the data '''
    binlist = tuple( [ vmax, 0 ] for i in xrange( nbins ) )
    idat, swpb = 0, 0
    for idf, ib in enumerate( binlist ):
        swpb = sw/( nbins - idf )
        while ib[ 1 ] < swpb and idat < length:
            val, wgt = values[ idat ]
            if val < ib[ 0 ]:
                ib[ 0 ] = val
            ib[ 1 ] += wgt
            idat += 1
        sw -= ib[ 1 ]
    while idat < length:
        binlist[ -1 ][ 0 ], binlist[ -1 ][ 1 ] = values[ idat ]
        idat += 1

    ''' To create the Root histogram, an array of doubles has to be created, with the minimum
    value for the bins '''
    bins = array( 'd', ( nbins + 1 )*[ 0. ] )
    for i, ib in enumerate( binlist ):
        bins[ i ] = ib[ 0 ]
    bins[ -1 ] = vmax
    
    hist = histcall( name, title, nbins, bins )
    hist.GetXaxis().SetTitle( xtitle )
    hist.GetYaxis().SetTitle( ytitle )

    return hist

