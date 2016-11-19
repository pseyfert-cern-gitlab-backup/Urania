import TruthCuts, HistPlotters
import BsDsMuNuForRDS.DataRetrieval as DataRetrieval

c  = DataRetrieval.getProcessedChain('MC_Signal', 'MagDown')
#c2 = DataRetrieval.getProcessedChain('MC_LbLcDs', 'MagDown')
#g  = HistPlotters.makeROC(t1=c, t2=c2, scanVar='mu_iso_MinBDT_Long',
#                          cutDir='>', bkgName = 'B2CC', cut1=TruthCuts.isSignal,
#                          cut2=TruthCuts.isDoubleCharm)
#HistPlotters.plotROC(g)

listOfBkgs = ['MC_LbLcDs', 'MC_BdDstDs', 'MC_BsDsDs', 'MC_BuD0Ds']

#for bkg in listOfBkgs:
    #c2 = DataRetrieval.getProcessedChain(bkg, 'MagDown')
    #g  = HistPlotters.makeROC(t1=c, t2=c2, scanVar='mu_iso_MinBDT_Long',
    #                          cutDir='>', bkgName = bkg, cut1=TruthCuts.isSignal,
    #                          cut2=TruthCuts.isDoubleCharm, sigName = 'MC_Signal')
    #HistPlotters.plotROC(g)

listOfBkgs.append('MC_Signal')
color = 1
hList = []
for species in listOfBkgs:
    c = DataRetrieval.getProcessedChain(species, 'MagDown')
    cut = TruthCuts.isSignal
    if not species == 'MC_Signal':
        cut = TruthCuts.isDoubleCharm
    h = HistPlotters.makeHist(chain=c, xKey='mu_iso_MinBDT_Long', name=species, lineColour = color,
                              zeroYaxis=True, cutString = cut, normalise=True, )
    h.SetTitle(species)
    color+=1
    hList.append(h)
    
HistPlotters.plotHist(hist=hList, setLegend=True, setLog=True,
                      legendPositions=(0.15, 0.2, 0.4, 0.52), plotNameOpts='WithTruthMatching')    
hList = []
color=1
for species in listOfBkgs:
    c = DataRetrieval.getProcessedChain(species, 'MagDown')
    cut = '1'
    #if not species == 'MC_Signal':
    #    cut = TruthCuts.isDoubleCharm
    h = HistPlotters.makeHist(chain=c, xKey='mu_iso_MinBDT_Long', name=species, lineColour = color,
                              zeroYaxis=True, cutString = cut, normalise=True, )
    h.SetTitle(species)
    color+=1
    hList.append(h)
    
HistPlotters.plotHist(hist=hList, setLegend=True, setLog=True,
                      legendPositions=(0.15, 0.2, 0.4, 0.52), plotNameOpts='NoTruthMatching')

                                        
