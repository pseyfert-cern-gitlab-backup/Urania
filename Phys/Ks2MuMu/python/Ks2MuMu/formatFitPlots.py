from ROOT import *
from collections import *
from copy import deepcopy

#gROOT.ProcessLine( '.x lhcbStyle.C' )
gStyle.SetTextFont(132)
gStyle.SetTextSize(0.06)
gROOT.SetBatch()

TO_PAPER = True

CATEGORIES = OrderedDict( [
        #( 'TOS1', range( 3, 10 ) ),
        #( 'TOS2', range( 3, 10 ) ),
        #( 'TIS' , range( 3, 10 ) ),
        ( 'TOS1_TOS2', range(0, 10) )
        ] )

gStyle.SetOptTitle(0)

def resetLabelFormat(obj, pad):
    ''' Must work with pixels '''
    xaxis = obj.GetXaxis()
    yaxis = obj.GetYaxis()

    xaxis.SetLabelFont(133) # lhcb style with precision = 3
    yaxis.SetLabelFont(133) # lhcb style with precision = 3

    chsize = 50
    
    xaxis.SetLabelSize(chsize)
    yaxis.SetLabelSize(chsize)

    yaxis.SetTitleFont(133)
    yaxis.SetTitleSize(chsize)
    
    xaxis.SetTitleOffset(1.2)
    yaxis.SetTitleOffset(1.75)
    
    yaxis.SetTitleSize(1.1*yaxis.GetTitleSize())
    xaxis.SetTitleSize(1.1*xaxis.GetTitleSize())


def makePlots( cat, bins ):
    print '-- Category:', cat
    ifile  = TFile( 'FitPlots_' + cat + '.root' )
    if cat == 'TOS1_TOS2':
        folder = 'ALL'
    else:
        folder = cat
    cat = cat.split( '_' )
    for c in cat:
        formatPlots( ifile, c, bins, folder )

from string import ascii_lowercase
label_ctr = 0
def formatPlots( ifile, cat, bins, folder ):
    global label_ctr
    for i in bins:
        ic = ifile.Get( cat + '_' + str(i) )
        c = TCanvas( ic.GetName(), '' )
        ic.Copy( c )
        c.SetTitle( '' )
        name = folder + 'fitPlots/'
        if not TO_PAPER:
            name += 'extra/'

        if folder == 'ALL':
            name += folder
        name += c.GetName()
        
        for i, pd in enumerate(ic.GetListOfPrimitives()):

            for obj in pd.GetListOfPrimitives():
                if hasattr(obj, 'SetLineWidth'):
                    obj.SetLineWidth(3)
                    
            if i == 0:
                l = pd.GetListOfPrimitives().At(1)

                xtit = l.GetXaxis().GetTitle()
                ytit = l.GetYaxis().GetTitle()

                xtit = xtit.replace('(', '[')
                xtit = xtit.replace(')', ']')
                ytit = ytit.replace('Events', 'Candidates')

                l.GetXaxis().SetTitle(xtit)
                l.GetYaxis().SetTitle(ytit)
                
            elif i == 1:
                l = pd.GetListOfPrimitives().At(1)

                l.GetYaxis().SetTitle('Pull')

            pd.SetLeftMargin(0.2)
            pd.SetBottomMargin(0.2)

            obj = pd.GetListOfPrimitives().At(1)
            resetLabelFormat(obj, pd)

            pd.Update()
            pd.Draw()

        # Pull plot
        pd.SetBottomMargin(0.3)
        pd.SetTopMargin(0.2)

        c.cd(1)
        tp = TPaveText( 0.5, 0.75, 0.9, 0.9, 'NDC' )
        #tp = TPaveText( 0.5, 0.825, 0.9, 0.9, 'NDC' )
        #tp.AddText( c.GetName() )
        #tp.AddText( 'LHCb Preliminary' )
        tp.AddText( 'LHCb' )
        #tp.AddText( 'LHCb unofficial' )
        #tp.AddText('')

        nm = c.GetName()
        ibin = str(int(nm[-1]) + 1)
        if 'TOS1' in nm:
            txt = 'TOS_{#mu} bin %s' %ibin
        else:
            txt = 'TOS_{#mu#mu} bin %s' %ibin

        '''
        if TO_PAPER:
            if '8' in nm or '9' in nm:
                txt = ascii_lowercase[label_ctr] + ') ' + txt
                label_ctr += 1
        else:
            txt = ascii_lowercase[label_ctr] + ') ' + txt
            label_ctr += 1
            '''

        tp.AddText(txt)
        
        tp.SetFillColor( kWhite )
        tp.SetBorderSize( 0 )
        tp.Draw()
        
        c.Draw()
        c.cd(1).SetLogy()
        c.SetCanvasSize(1000, 1000)
        c.Update()

        c.Print( name + '.pdf' )
        c.Print( name + '.png' )
        c.Print( name + '.eps' )
        c.Print( name + '.C' )

for c, b in CATEGORIES.iteritems():
    makePlots( c, b )
