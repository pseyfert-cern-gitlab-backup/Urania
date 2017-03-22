protoFilePathIn = '/project/bfys/jleerdam/data/Bs2Jpsiphi/Reco14/P2VVDataSets2011Reco14_I2Mass_6KKMassBins_2TagCats_HLT2B.root'
nTupleFilePathIn = '/project/bfys/sbenson/Jpsiphi-MC/veronika_21-12/bsmumukk_f0_phi_m0.5pi_FF.root'
dataFilePathOut = '/project/bfys/sbenson/Jpsiphi-MC/veronika_21-12/veronikaDataset_m0p5pi_%s.root'
runPeriods = [2011]
KKMassBins = [ 990., 1020. - 12., 1020. - 4., 1020., 1020. + 4., 1020. + 12., 1050. ] 
removeVars = [ '' ]
selection = ''
numDataSets = 1
weightName = ''
debug=False
maxNev=''#10000

import P2VV.RooFitWrappers
from P2VV.RooFitWrappers import BinningCategory
from ROOT import TFile, RooArgSet
from ROOT import RooRealVar, RooCategory

protoFile = TFile.Open(protoFilePathIn)

nTupleFileIn = TFile.Open(nTupleFilePathIn)
protoData = protoFile.Get('JpsiKK_sigSWeight')
nTupleIn = nTupleFileIn.Get('bsmumukk')
from math import pi
obsDict = dict( 
        KKMass    = ( 'mKK',                'm(K^{+}K^{-})',           'MeV/c^{2}', 1020.,   990.,   1050.   )
        , time      = ( 'time',                 'Decay time',              'ps',        1.5,    0.0,     14.     )
        , mass      = ( 'mass',                 'm(J/#psi K^{+}K^{-})',    'MeV/c^{2}', 5368.,  5200.,   5550.   )
        , cpsi      = ( 'helcosthetaK',         'cos(#theta_{K})',         '',          0.,    -1.,     +1.      )
        , ctheta    = ( 'helcosthetaL',         'cos(#theta_{#mu})',       '',          0.,    -1.,     +1.      )
        , phi       = ( 'helphi',               '#phi_{h}',                'rad',       0.,    -pi,     +pi      )
        , wTagOS    = ( 'tagomega_os_cb', 'OS est. wrong-tag prob.', '', 0.25, 0., 0.50001 )
        , wTagSS    = ( 'tagomega_ss_cb', 'SS est. wrong-tag prob.', '', 0.25, 0., 0.50001 )
        , timeRes   = ( 'sigmat',               '#sigma(t)',               'ps',        0.01,   0.0001,  0.12    )
        , iTagOS    = ( 'iTagOS',               'OS flavour tag',          '',0.,-1.0,1.0)
        )
catDict = dict(        
        runPeriod = ( 'runPeriod',            'run period',              { "2011":2011 } )
        #, KKMassCat = ( 'KKMassCat',            'KK mass category',        { }                                   )
        #, iTagOS    = ( 'iTagOS',               'OS flavour tag',          { 'B' : +1, 'Bbar' : -1 }             )
        , tagCatOS  = ( 'tagCatP2VVOS',         'OS flavour tag',          { 'Untagged' : 0, 'Tagged' : 1 }      )
        , iTagSS    = ( 'iTagSS',               'SS flavour tag',          { 'B' : +1, 'Bbar' : -1 }             )
        , tagCatSS  = ( 'tagCatP2VVSS',         'SS flavour tag',          { 'Untagged' : 0, 'Tagged' : 1 }      )
        )
def buildObs(inputSet):
    return RooRealVar( inputSet[0], inputSet[1], inputSet[3], inputSet[4], inputSet[5], inputSet[2]).clone(inputSet[0])
def buildObsCat(inputSet):
    cat = RooCategory( inputSet[0], inputSet[1] )
    for name,val in inputSet[2].iteritems():
        cat.defineType(name,val)
    return cat.clone(inputSet[0])

obsSet = RooArgSet()
for obs in obsDict.values():
    obsSet.add(buildObs(obs))
for obs in catDict.values():
    obsSet.add(buildObsCat(obs))

if debug:
    obsSet.Print()
    import sys
    sys.exit("Dry run completed")

if runPeriods :
    rp = obsSet.find('runPeriod')
    if rp : obsSet.remove(rp)
    rp = RooCategory( 'runPeriod', 'runPeriod' )
    for per in runPeriods : rp.defineType( 'p%d' % per, per )
    obsSet.add(rp)

if KKMassBins :

    from array import array
    KKBinsArray = array( 'd', KKMassBins )
    from ROOT import RooBinning
    from ROOT import RooBinningCategory
    KKBinning = RooBinning( len(KKMassBins) - 1, KKBinsArray, 'KKMassBinning' )
    obsSet.find('mKK').setBinning( KKBinning, 'KKMassBinning' ) 
    
import os, subprocess, tempfile
tmp = tempfile.NamedTemporaryFile()
tmpFileName = os.path.realpath(tmp.name)
tmp.close()

from ROOT import RooDataSet, TObject, gROOT
nEvTot = 0
nEvDS = nTupleIn.GetEntries() / numDataSets
for it in range(numDataSets) :
    startEv = it * nEvDS
    nEv = nEvDS if it < numDataSets - 1 else nTupleIn.GetEntries() - ( numDataSets - 1 ) * nEvDS
    if maxNev: nEv = maxNev
    tmpFile = TFile.Open( tmpFileName, 'RECREATE' )
    nTupleSplit = nTupleIn.CopyTree( selection, '', nEv, startEv )
    if weightName :
        dataOut = RooDataSet( protoData.GetName(), protoData.GetTitle(), obsSet, Import = nTupleSplit, WeightVar = ( weightName, True ) )
    else :
        dataOut = RooDataSet( "GenLevel", "GenLevel", obsSet, Import = nTupleSplit )
    
    if KKMassBins :
        KKCat = RooBinningCategory( 'KKMassCat', 'KKMassCat', obsSet.find('mKK'), 'KKMassBinning')
        dataOut.addColumn(KKCat)
    tmpFile.Close()

    nEvTot += dataOut.numEntries()
    dataFileOut = TFile.Open( dataFilePathOut % it, 'RECREATE' )
    dataFileOut.Append(dataOut)
    dataFileOut.Write( dataFilePathOut % it, TObject.kOverwrite )
    dataFileOut.Close()
os.remove(tmpFileName)
print 'total number of events: %d' % nEvTot
