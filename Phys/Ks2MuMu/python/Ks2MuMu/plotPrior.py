from ROOT import *
import priormcmc1 as PRIOR

gROOT.ProcessLine( '.x lhcbStyle.C' )

BR_ = RooRealVar( 'BR', 'B(K_{S}^{0}#rightarrow#mu^{+}#mu^{-}) #times10^{9}', 0., 0., 30 )
gROOT.ProcessLine('.L $URANIAROOT/src/RooAmorosoPdf.cxx++')
prior = RooAmorosoPdf('PRIOR', 'PRIOR' , BR_, PRIOR.offset, PRIOR.theta, PRIOR.alpha, PRIOR.beta)

def getYwithX( graph, val ):
    
    x, y = Double( 0. ), Double( 0. )
    yold = 1*y

    for i in xrange(graph.GetN()):
        graph.GetPoint( i, x, y )

        if x > val:
            return abs(y+yold)/2., yold

        yold = 1*y

c = TCanvas()

fr = BR_.frame()
prior.plotOn( fr, RooFit.Name( 'pdf' ), RooFit.LineColor( kOrange+4 ) )
fr.GetYaxis().SetTitle( 'Projection of the prior' )
fr.GetYaxis().SetDecimals()
fr.GetYaxis().SetLabelSize( 0 )
fr.GetYaxis().SetTitleOffset( 0.75 )
fr.Draw()

graph = fr.getCurve( 'pdf' )

line95 = TLine( 6.9, 0, 6.9, getYwithX( graph, 6.9 )[1] )
line90 = TLine( 5.8, 0, 5.8, getYwithX( graph, 5.8 )[0] )

for el in [ line95, line90 ]:
    el.SetLineStyle( kDashed )

marker95 = TMarker( 6.9, getYwithX( graph, 6.9 )[1], 1 )
marker90 = TMarker( 5.8, getYwithX( graph, 5.8 )[0], 1 )

marker90.SetMarkerStyle( 20 )
marker90.SetMarkerColor( kMagenta )
marker95.SetMarkerStyle( 20 )
marker95.SetMarkerColor( kBlue )

line90.SetLineColor( kMagenta )

line95.SetLineColor( kBlue )

marker90.Draw('SAME')
marker95.Draw('SAME')
line90.Draw('SAME')
line95.Draw('SAME')

tp = TPaveText( 0.6, 0.8, 0.9, 0.9, 'NDC' )
tp.AddText( 'LHCb Simulation' )
tp.SetFillColor( kWhite )
tp.SetBorderSize( 0 )
tp.Draw()

c.Update()
c.Print( 'Prior.pdf' )
