##########################################
### Fit Toy dataset produced with Foam ###
##########################################
import os
from P2VV.RooFitWrappers import *
ws = RooObject( workspace = 'fit_toy').ws()

from math import pi
time      = RealVar( 'time'        , Title = 'Decay time'       , Unit =  'ps', Value =  1., MinMax = ( 0., 14.) )
cpsi      = RealVar( 'helcosthetaK', Title = 'cos(#theta_{K})'  , Unit =   '' , Value = 0.5, MinMax = (-1., +1.) )   
ctheta    = RealVar( 'helcosthetaL', Title = 'cos(#theta_{#mu})', Unit =   '' , Value = 0.5, MinMax = (-1., +1.) )
phi       = RealVar( 'helphi'      , Title = '#phi_{h}'         , Unit = 'rad', Value =  0., MinMax = (-pi, +pi) ) 

from P2VV.Utilities.DataHandling import readData
input_file = '/user/egovorko/p2vv-git/p2vv/scripts/FoamDataSet.root'
dataSet    = readData( filePath = input_file, dataSetName = "toyDataSet", NTuple = False )

from toy_generation import pdf
## Fit options
fitOpts = dict(  NumCPU    = 8
               , Optimize  = 2
               , Minimizer = 'Minuit2'
               , Strategy  = 1
               , Save      = True
              )

fitResult = pdf.fitTo( dataSet, **fitOpts )
from P2VV.Imports import parNames, parValues
print 'Simple: parameters:'
fitResult.PrintSpecial( text = True, LaTeX = True, normal = True, ParNames = parNames, ParValues = parValues )
print 'Simple: correlation matrix:'
fitResult.correlationMatrix().Print()
print 'Simple: covariance matrix:'
fitResult.covarianceMatrix().Print()


__canvases = []
# Plot fit result
def plot_res(data, prefix = ''):
    nBins = 100
    from ROOT import kDashed, kRed, kGreen, kBlue, kBlack
    from ROOT import TCanvas
    res_canvas = TCanvas('%sres_canvas' % prefix, '%sres_canvas' % prefix, 600, 530)
    __canvases.append(res_canvas)
    from P2VV.Utilities.Plotting import plot
    frames = plot(  res_canvas, time, pdf = pdf, data = dataSet
                  , dataOpts  = dict( MarkerSize = 0.8, MarkerColor = kBlack, Binning = nBins )
                  , pdfOpts   = dict( LineWidth = 2 )
                  , frameOpts = dict( Title = 'Toy Fit' )
                  , plotResidHist = True
                  # , components = { 'sig*'  : dict( LineColor = kBlue,  LineStyle = kDashed ) })
    
    frames[1].GetXaxis().SetTitle('')
    frames[0].GetYaxis().SetTitle('Candidates / (%3.2f MeV/c^2)' % ((time.getMax() - time.getMin()) / float(nBins)))

plot_res(dataSet)