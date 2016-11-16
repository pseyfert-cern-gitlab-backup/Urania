#! /usr/bin/env python

"""pyROOT settings for Marco's thesis
"""
from ROOT import gROOT, gStyle, TFile, TGraph, TGraphErrors, TStyle, gROOT, TColor, kGreen, kRed, kBlue, kYellow, kMagenta, kCyan

MarcoStyle = TStyle("MarcoStyle","Marco's ROOT style")

font = 132  # Nice font for my thesis
font = 62   #default

def set_palette(name='default', ncontours=999, style=gStyle):
    """Set a color palette from a given RGB list
    stops, red, green and blue should all be lists of the same length
    see set_decent_colors for an example
    http://ultrahigh.org/2007/08/20/making-pretty-root-color-palettes/
    """
    from array import array
    
    if name == "gray" or name == "grayscale":
        stops = [0.00, 0.34, 0.61, 0.84, 1.00]
        red   = [1.00, 0.84, 0.61, 0.34, 0.00]
        green = [1.00, 0.84, 0.61, 0.34, 0.00]
        blue  = [1.00, 0.84, 0.61, 0.34, 0.00]
    elif name == "marco":
        stops = [0.00, 0.34, 0.61, 0.84, 1.00]
        red   = [1.00, 0.84, 0.61, 0.34, 0.00]
        green = [1.00, 0.84, 0.61, 0.34, 0.00]
        blue  = [1.00, 0.84, 0.61, 0.34, 0.00]
    else:
        # default palette, looks cool
        stops = [0.00, 0.34, 0.61, 0.84, 1.00]
        red   = [0.00, 0.00, 0.87, 1.00, 0.51]
        green = [0.00, 0.81, 1.00, 0.20, 0.00]
        blue  = [0.51, 1.00, 0.12, 0.00, 0.00]

    s = array('d', stops)
    r = array('d', red)
    g = array('d', green)
    b = array('d', blue)

    npoints = len(s)
    TColor.CreateGradientColorTable(npoints, s, r, g, b, ncontours)
    style.SetNumberContours(ncontours)
    


## use plain black on white colors
#MarcoStyle.SetFillColor(0)
MarcoStyle.SetFrameBorderMode(0)
MarcoStyle.SetFrameFillColor(0)
MarcoStyle.SetCanvasBorderMode(0)
MarcoStyle.SetPadBorderMode(0)
MarcoStyle.SetPadColor(0)
MarcoStyle.SetCanvasColor(0)
MarcoStyle.SetTitleColor(1)
MarcoStyle.SetTitleFillColor(0)
MarcoStyle.SetStatColor(0)
MarcoStyle.SetLegendBorderSize(1)
set_palette(style = MarcoStyle)

## set the paper & margin sizes
MarcoStyle.SetPaperSize(20,26)
MarcoStyle.SetPadTopMargin(0.05)
MarcoStyle.SetPadRightMargin(0.05) ## increase for colz plots!!
MarcoStyle.SetPadBottomMargin(0.14)
MarcoStyle.SetPadLeftMargin(0.14)

## use large Times-Roman fonts
#MarcoStyle.SetTextFont(font)
MarcoStyle.SetTextSize(0.08)
#MarcoStyle.SetLabelFont(font,"x")
#MarcoStyle.SetLabelFont(font,"y")
#MarcoStyle.SetLabelFont(font,"z")
MarcoStyle.SetLabelSize(0.05,"x")
MarcoStyle.SetLabelSize(0.05,"y")
MarcoStyle.SetLabelSize(0.05,"z")
#MarcoStyle.SetTitleFont(font,"x")
#MarcoStyle.SetTitleFont(font,"y")
#MarcoStyle.SetTitleFont(font,"z")
MarcoStyle.SetTitleSize(0.05,"x")
MarcoStyle.SetTitleSize(0.05,"y")
MarcoStyle.SetTitleSize(0.05,"z")

## use bold lines and markers
##MarcoStyle.SetMarkerStyle(1)
##MarcoStyle.SetMarkerColor(2)
MarcoStyle.SetMarkerSize(1)
MarcoStyle.SetHistLineWidth(4)
MarcoStyle.SetLineStyleString(2,"[12 12]") ## postscript dashes
MarcoStyle.SetLineStyleString(11,"55 15")
MarcoStyle.SetLineStyleString(12,"28 18")
MarcoStyle.SetLineWidth(2)

## by default, only display statistics box:
MarcoStyle.SetOptStat(0000)  ## show only nent, mean, rms
MarcoStyle.SetOptTitle(0)
MarcoStyle.SetOptFit(0)

## look of the statistics box:
MarcoStyle.SetStatBorderSize(1)
#MarcoStyle.SetStatFont(font)
MarcoStyle.SetStatFontSize(0.05)
MarcoStyle.SetStatX(0.99)
MarcoStyle.SetStatY(0.99)
MarcoStyle.SetStatColor(0)

## put tick marks on top and RHS of plots
##MarcoStyle.SetPadTickX(1)
##MarcoStyle.SetPadTickY(1)

gROOT.SetStyle("MarcoStyle")
gROOT.ForceStyle()


# definition of colors to use for selection plots

mu_rob = kBlue-7
mu_std = kCyan-6

jpsik_rob = kRed-7
jpsik_std = kMagenta-6

hh_rob = kGreen-7
hh_std = kYellow-6


def GetLeafLabel(tree):
    """Get a sorted list of the leaf names of tree"""
    l = []
    for leaf  in tree.GetListOfLeaves():
        l.append( leaf.GetName() )

    l.sort()
    return l

def FindKeyword(list_keywd, list_label):
    """find keyword of list_keywd in list and print item that fit"""

    for item in list_label:
        for keywd in list_keywd:
            if item.find( str(  keywd ) ) != -1: print item


def GetTree(TFile, tree_label):
    
    try: tree = TFile.Get( str( tree_label ) )
    except AttributeError:
        print 'TFile ', TFile.Name(), ' has no tree ', tree_label
        exit()

    found = False        
    while not( found ):
        try: tree = tree.Get( str( tree_label ) )
        except AttributeError: found = True 
    return tree

def GetTGraph_from_leaves( tree, abscissa, ordinate ):
    """"""
    from array import array

    abscissa_array = array('d')
    ordinate_array = array('d')
    
    for i in range(tree.GetEntries()):
        tree.GetEntry(i)
        
        abscissa_array.append( getattr(tree, abscissa ) )
        ordinate_array.append( getattr(tree, ordinate ) )

    return TGraph( min( len(abscissa_array), len(ordinate_array) ), abscissa_array, ordinate_array)

def GetTGraph_with_P( tree, labels_P, ordinate , channel):
    """Return a TGraph with the momentum modulus P in abscisse and (ordinate) in ordinates. The momentum decomposition is given by entries in ( channel) dictionary. The three entries labels are provided as a list (labels_P)"""
    from array import array

    P_array = array('d')
    ordinate_array = array('d')

    for i in range(tree.GetEntries()):
        tree.GetEntry(i)
        ordinate_array.append( getattr(tree, ordinate ) )
        p1 = getattr( tree, channel[labels_P[0]] )
        p2 = getattr( tree, channel[labels_P[1]] )
        p3 = getattr( tree, channel[labels_P[2]] )
        mod_p = sqrt( p1*p1 + p2*p2 + p3*p3 )
        P_array.append( mod_p )

    return TGraph(min( len(P_array), len(ordinate_array) ), P_array, ordinate_array)
