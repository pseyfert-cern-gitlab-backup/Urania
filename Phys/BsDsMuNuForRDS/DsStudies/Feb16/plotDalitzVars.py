from ROOT import *
from oldHistPlotters import histDict
from HistPlotters import makeHist, plotHist
from BsDsMuNuForRDS.DataRetrieval import *
from BsDsMuNuForRDS.Selections import cutStringDsVetoes
gROOT.SetBatch()
gROOT.ProcessLine('.x ~/lhcbStyle.C')
######################################################################
## Some constants.
######################################################################
M_Dp    = 1869.57
M_Ds    = 1968.30
M_Lc    = 2286.46
M_Kstar = 891.66
M_Jpsi  = 3096.916
M_psi2S = 3686.109
M_psi3770 = 3773.15

######################################################################
## Some options.
######################################################################
numBins = 80
dataType = "data"
polarity = "up"

dataTag = 'Data_AllNeutrals'
polarity = 'MagUp'

######################################################################
inFileDir  = getPostSelDataDirectory()
inFileName = inFileDir + outPutFileNameDict[dataTag][polarity]
f = TFile(inFileName, 'read')
t = f.Get('B2DsMuNuTuple/DecayTree')
hList = []

######################################################################
#h = makeHist(chain=t, xKey='Ds_M', ykey = 'M_OSKpi', numBinsX = numBins, numBinsY = numBins)
#plotHist(hist = h,  plotNameOpts = '%s_%s' %(dataType, polarity))

plotDalitz = False
if plotDalitz:
    h = makeHist(chain=t, xKey='Ds_M', yKey = 'M_KK', numBinsX = numBins, numBinsY = numBins)
    plotHist(hist = h,  plotNameOpts = '%s_%s_preselection' %(dataType, polarity), setLog=True)

    h = makeHist(chain=t, xKey='Ds_M', yKey = 'M_KK', numBinsX = numBins, numBinsY = numBins, cutString=cutStringDsVetoes)
    plotHist(hist = h,  plotNameOpts = '%s_%s_postselection' %(dataType, polarity), setLog=True)
    
    h = makeHist(chain=t, xKey='Ds_M', yKey = 'M_OSKpi', numBinsX = numBins, numBinsY = numBins)
    plotHist(hist = h,  plotNameOpts = '%s_%s_preselection' %(dataType, polarity), setLog=True)
    
    h = makeHist(chain=t, xKey='Ds_M', yKey = 'M_OSKpi', numBinsX = numBins, numBinsY = numBins, cutString=cutStringDsVetoes)
    plotHist(hist = h,  plotNameOpts = '%s_%s_postselection' %(dataType, polarity), setLog=True)

######################################################################
# Plot data/sim comparisons
######################################################################
plotMCComparisons = True
if plotMCComparisons:

    listToCompare = ['WM_Lc_SSKasproton', 'WM_Dp_SSKaspi']
    
