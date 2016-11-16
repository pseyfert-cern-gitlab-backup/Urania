import argparse
parser = argparse.ArgumentParser()
parser.add_argument( '--sigWeight',  default = 'Bs', type=str )
parser.add_argument( '--flipPhi', action = 'store_true' )
parser.add_argument( '--kaonSign' )
options = parser.parse_args()

wghtArg = options.sigWeight
assert wghtArg in ['Bs','Bd'], 'P2VV - ERROR: Wrong sWeight speicifier. Choose either Bs or Bd.'

# input dataset paths
simulation  = False
prodDate    = '250615'
inPath      = '/data/bfys/vsyropou/Bs2JpsiKst/DiegosUnrefinedTuples/RealData/NewLbBkgModels_ForApproval/%s'%( 'flipPhi/' if options.flipPhi else '')
dataSetName = 'Bs2JpsiKst'

# output paths
outPath     = './' #'/project/bfys/vsyropou/PhD/workdir/jpsiKstFit/data/comb_test/'
if not simulation:
    outFileName = 'P2VVDataSet_Bs2JpsiKst_3fb_Reco14_%sKaons_allKpiBins_%s_%sWeights.root'%(options.kaonSign if options.kaonSign else 'all',prodDate,wghtArg)
else:
    outFileName = 'P2VVDataSet_Bs2JpsiKst_3fb_Sim08_Reco14_%sKaons_allKpiBins_%s.root'%(options.kaonSign if options.kaonSign else 'all',prodDate)
outDataName = 'Bs2JpsiKst'


# bin bounds and datasets dictionary
KpiBinBounds   = [826, 861, 896, 931, 966]
# dataSetPaths = { '_'.join([str(p),str(s),'bin%s'%boundIdx]) : inPath + 'P2VVDataSet_Bs2JpsiKst_%s%s_Reco14_%sKaons_%s_KpiBin_%s_%s.root'%
#                  ( p, '_Sim08' if simulation else '', s, '%s_%s'%( KpiBinBounds[boundIdx], KpiBinBounds[boundIdx +1] ), prodDate, '%sWeights'%wghtArg ) \
#                  for s in ['pos','neg'] for p in [2011,2012] for boundIdx in range( len(KpiBinBounds) -1 ) }
# appendToDataSetKey = '2011_neg_bin1'


if not options.kaonSign:
    dataSetPaths = { '_'.join([str(p),str(s)]) : inPath + 'P2VVDataSet_Bs2JpsiKst_%s%s_Reco14_%sKaons_allKpiBins_%s%s.root'%
                     ( p, '_Sim08' if simulation else '', s, prodDate, '_%sWeights'%wghtArg if not simulation else '') for s in ['pos','neg'] for p in [2011,2012]  }
    appendToDataSetKey = '2011_neg'
else:
    dataSetPaths = { str(p) : inPath + 'P2VVDataSet_Bs2JpsiKst_%s%s_Reco14_%sKaons_allKpiBins_%s%s.root'%
                     ( p, '_Sim08' if simulation else '', options.kaonSign, prodDate, '_%sWeights'%wghtArg if not simulation else '' )  for p in [2011,2012]  }
    appendToDataSetKey = '2011'

# read datasets into a combined dataset
print 'P2VV - INFO: Will merge these datasets:'
for v in dataSetPaths.values(): print v

from ROOT import TFile, RooDataSet, RooFit, RooArgSet
dataSets = {}
count, events = 1,0
for key, path in dataSetPaths.iteritems(): dataSets[key] = TFile.Open(path,'READ').Get(dataSetName)

print 'P2VV - INFO: Combining the following datasets:'
print appendToDataSetKey, '(%s/%s)'%(count,len(dataSets.keys())) 
dataSets[appendToDataSetKey].Print()
combinedDataSet = dataSets[appendToDataSetKey]
events += combinedDataSet.numEntries()
print
dataSets.pop(appendToDataSetKey)
for key, dataSet in dataSets.iteritems(): 
    print key, '(%s/%s)'%(count,len(dataSets.keys())) 
    dataSet.Print()
    print
    combinedDataSet.append(dataSet)
    count  += 1
    events += dataSet.numEntries()
print
print 'P2VV - INFO: Combined dataset: Expected entries: %s'%events
combinedDataSet.Print()

outFile = TFile.Open(outPath + outFileName,'recreate')
combinedDataSet.Write()
outFile.Close()
del outFile

print 'P2VV - INFO: Wrote dataset to file: %s'%outPath + outFileName
