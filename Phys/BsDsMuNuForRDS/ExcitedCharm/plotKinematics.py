import sys
from ROOT import TFile, gROOT
from HistPlotters import makeHist, plotHist
gROOT.SetBatch(True)
gROOT.ProcessLine('.x ~/lhcbStyle.C')


dataType = 'Data_AllNeutrals'
polarity = 'MagDown'
fName  = 'RDs_sWeights_%s_%s.root' %(dataType, polarity)
inFile = TFile.Open(fName)
inFile.ls()
numBins = 60
t = inFile.Get('merged')

h = makeHist(chain=t, xKey='Emu', numBinsX = numBins, cutString='N_LsigR_sw')
plotHist(hist = h, plotNameOpts = '%s_%s' %(dataType, polarity), gfxType='.eps')

h = makeHist(chain=t, xKey='MM2', numBinsX = numBins, cutString='N_LsigR_sw')
plotHist(hist = h, plotNameOpts = '%s_%s' %(dataType, polarity), gfxType='.eps')
