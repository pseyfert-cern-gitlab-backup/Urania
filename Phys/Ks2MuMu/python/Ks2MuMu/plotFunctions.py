import ROOT as rt
import ROOT.RooFit as rf

def makePullPlot( roovar, dataSet, nbins, pdf, limits = False ):
    
    ranges = {}
    if limits:
        for el in limits:
            b = roovar.getBinningPtr( el )
            ranges[ el ] = ( b.lowBound(), b.highBound() )
    else:
        limits = [ 'model' ]
        ranges[ 'model' ] = ( roovar.getMin(), roovar.getMax() )
    
    # Creates the environment for the pull plot
    pullFrame = roovar.frame( rf.Title( '' ) )
    dataSet.plotOn( pullFrame, rf.Name( 'pullHist' ), rf.Binning( nbins ) )
    pullHist = pullFrame.getHist( 'pullHist' )

    curves = {}
    for lim in limits:
        pdf.plotOn( pullFrame, rf.Name( lim ), rf.Range( lim ), rf.NormRange('FULL') )
        curves[ lim ] = pullFrame.getCurve( lim )
        
    xbin = rt.Double( 0. )
    vbin = rt.Double( 0. )
    
    errList, distList = [], []
    points2Del = []
    for ib in xrange( pullHist.GetN() ):
        
        pullHist.GetPoint( ib, xbin, vbin )

        accept = False
        for kw, el in ranges.iteritems():
            graphPdf   = curves[ kw ]
            vmin, vmax = el
            if vmin <= xbin and xbin < vmax:
                accept = True
                break
    
        if accept:
            fcn = graphPdf.Eval( xbin )

            # The error is set according to its position respect to the expectation from the pdf
            eup, edw = pullHist.GetErrorYhigh( ib ), pullHist.GetErrorYlow( ib )
            dist = float(vbin - fcn)

            err = pullHist.GetErrorY( ib )
            '''
            if dist >= 0:
                err = edw
            else:
                err = eup
                '''
            if dist >= 0:
                pullHist.SetPoint( ib, xbin, dist/edw )
                pullHist.SetPointEYhigh( ib, eup/edw )
                pullHist.SetPointEYlow( ib, 1. )
            else:
                pullHist.SetPoint( ib, xbin, dist/eup )
                pullHist.SetPointEYhigh( ib, 1. )
                pullHist.SetPointEYlow( ib, edw/eup )

            errList.append( max( err, eup, edw ) )
            distList.append( dist )
        else:
            points2Del.append( ib )
    
    points2Del.reverse()
    for el in points2Del:
        pullHist.RemovePoint( el )

    pullFrame.SetMaximum( +5 )
    pullFrame.SetMinimum( -5 )

    pullFrame.GetXaxis().SetTitle( '' )
    pullFrame.GetYaxis().SetTitle( '' )

    for el in limits:
        pullFrame.remove( el )

    return pullFrame
