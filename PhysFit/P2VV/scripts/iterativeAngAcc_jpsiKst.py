#! /usr/bin/env python

########################################################################################################################
## Configuration ##
###################
import argparse
parser = argparse.ArgumentParser()
parser.add_argument('--iterNum',      default = 1,     type=int, help='iteration number')
parser.add_argument('--KpiBin',       default = 1,     type=int, help='choose Kpi bin {1,2,3,4} ')
parser.add_argument('--MCProd',       default = '3fb', type=str, help='choose mc sample ( 2011/2012 )')
parser.add_argument('--kaonSign',     default = 'pos', type=str, help='choose kaon sign ( pos/neg )')

parser.add_argument('--physPars',     default = '',            help='physics prameters')
parser.add_argument('--Bweights',     default = 'Bs',          help='choose reald data weights Bs/Bd')
parser.add_argument('--rewSteps',     default = 'phys_Kpimom', help='reweghting steps order')
parser.add_argument('--KpimomRew',    default = 'vertical',    help='Kpi momentum reweighting approach (vertical/horizontal)')
parser.add_argument('--Bmom2DRew',    action = 'store_true',   help='2 dimentional Bmom reweighting switch')
parser.add_argument('--eqStatBins',   action = 'store_true',   help='2 dimentional Bmom reweighting switch')

parser.add_argument('--reduced',       action = 'store_true',  help='run on a reduced sample for testing')
parser.add_argument('--makePlots',     action = 'store_true',  help='switch on/off plotting')
parser.add_argument('--verbose',       action = 'store_true',  help='verbose option for more info')
# parser.add_argument('--statOnPlots',  action = = 'store_true', help='legend or stats in plots')
opts = parser.parse_args()

# sanity checks of parser options
assert opts.kaonSign in ['pos','neg'], 'P2VV - ERROR: --kaonSign must be pos/neg'
assert opts.KpiBin in [1,2,3,4], 'P2VV - ERROR: --KpiBin 1/2/3/4'
assert opts.MCProd in ['2011','2012','3fb'], 'P2VV - ERROR: --MCProd must be 2011/2012/3fb'

# reweightng features control
iterNumb              = opts.iterNum
RewApproach           = opts.KpimomRew
equalStatBins         = opts.eqStatBins
MCProd                = opts.MCProd
mergePer              = True if opts.MCProd == '3fb' else False
kaonSign              = opts.kaonSign
KpiBin                = opts.KpiBin
weights               = opts.Bweights
reweightBmomentum     = 'Bmom'   in opts.rewSteps
reweightMkpi          = 'mKpi'   in opts.rewSteps
reweightPhysics       = 'phys'   in opts.rewSteps
reweightKpimom        = 'Kpimom' in opts.rewSteps
twoDimensionalBmomRew = opts.Bmom2DRew
KpimomWeightsOnly     = True
mKpiBins              = 100
BmomBins              = 200
KpimomBins            = 10 # per dimention
physWeightName        = 'phys'
mKpiWeightsName       = 'mKpi'
KmomentaWeightsName   = 'Kpimom'
BmomentumWeightsName  = 'Bmom'
delIntermediateMoms   = False
scaleWeightsToNumEntr = True
reduced               = opts.reduced
makePlots             = opts.makePlots
verbose               = opts.verbose

# make Kpi bins
KpiBinBounds   = [826, 861, 896, 931, 966]
KpiBins = []
for boundIdx in range( len(KpiBinBounds) -1 ):
    KpiBins += [ [KpiBinBounds[boundIdx], KpiBinBounds[boundIdx +1]] ]
binL, binH = KpiBins[KpiBin-1][0], KpiBins[KpiBin-1][1]

# csp factors
CSP = {'1':0.9681, '2':0.9312, '3': 0.9519, '4':0.9881}

###########################################################################################################
## specify inputs ##
####################

# input dataset tamplates
dataSetsPath     = '/project/bfys/vsyropou/data/Bs2JpsiKst/'
templateMCpath   = lambda per, sign, KpiBin: dataSetsPath +'MC/Bd_monte_carlo/'+\
                 'P2VVDataSet_Bs2JpsiKst_%s_Sim08_Reco14_%sKaons_%s_%s_KpiBin_131214.root'%(per,sign,binL,binH)
templateDataPath = lambda per, sign, KpiBin, weights: dataSetsPath + 'RealData/second_round/' +\
                   'P2VVDataSet_Bs2JpsiKst_%s_Reco14_%sKaons_%s_%s_KpiBin_141315_%sWeights.root'%(per,sign,binL,binH,weights)

# efficiency moments script
eff_moms_script = '/project/bfys/vsyropou/repos/p2vv/scripts/computeAngEffMoments_jpsiKst.py '

# source distribution
mcTupleName = 'Bs2JpsiKst'
if mergePer:           monteCarloData = [ templateMCpath(per,kaonSign,KpiBin) for per in [2011,2012] ]
elif MCProd == '2011': monteCarloData = templateMCpath(MCProd,kaonSign,KpiBin)
elif MCProd == '2012': monteCarloData = templateMCpath(MCProd,kaonSign,KpiBin)

# target distribution
sDataName = 'Bs2JpsiKst'
if mergePer:           dataPath = [ templateDataPath(per,kaonSign,KpiBin,weights) for per in [2011,2012] ]
elif MCProd == '2011': dataPath = templateDataPath(2011,kaonSign,KpiBin,weights)
elif MCProd == '2012': dataPath = templateDataPath(2012,kaonSign,KpiBin,weights)

# print data inputs
if verbose:
    if mergePer:
        print 'P2VV - INFO: Source distribution files:\n %s\n %s'%(monteCarloData[0],monteCarloData[1])
        print 'P2VV - INFO: Target distribution files:\n %s\n %s'%(dataPath[0],dataPath[1])
    else:
        print 'P2VV - INFO:\n  Source distribution file: %s. \n  Target distribution file: %s.'%(monteCarloData,monteCarloData[0],dataPath)

from ROOT import TFile
if mergePer:
    # merge real data
    dataSets = [ TFile.Open(path).Get(sDataName) for path in dataPath ]
    exp      = dataSets[0].numEntries() + dataSets[1].numEntries()
    dataSets[0].append( dataSets[1] )
    target = dataSets[0]
    assert exp == target.numEntries(), 'P2VV - ERROR: Unexpected number of target events. Events are lost during merging.' 

    # merge monte carlo data
    dataSets_mc = [ TFile.Open(path).Get(mcTupleName) for path in monteCarloData ]
    exp = dataSets_mc[0].numEntries() + dataSets_mc[1].numEntries()
    dataSets_mc[0].append( dataSets_mc[1] )
    monteCarloData = dataSets_mc[0]
    assert exp == monteCarloData.numEntries(), 'P2VV - ERROR: Unexpected number of source events. Events are lost during merging.'

    del dataSets, dataSets_mc
else:
    target = TFile.Open(dataPath).Get(sDataName)
    monteCarloData = TFile.Open(dataPath).Get(mcTupleName)

print 'P2VV - INFO: Target (real data):'
target.Print()
print 'P2VV - INFO: Source (monte carlo data):'
monteCarloData.Print()

# angluar acceptance baseline filename
outputEffMomentsBaselineName = 'Sim08_hel_%sKaons_bin%s_Basis_constr_%s_iter'%(kaonSign,KpiBin,iterNumb)

# source generating physics parameters
## TODO: update parameters dictionary
from P2VV.Utilities.MCReweighting import parValuesMcSim08_jpsiKst as monteCarloParameters

# target physics parameters
dataParameters = opts.physPars if opts.physPars\
    else dataSetsPath + 'fitResults/%s_%sKaons_3fb_mergeAccPer_allKpiBins_AcpZero.par'%(weights,kaonSign)

###########################################################################################################################
## Begin iterative procedure  ##
################################
from P2VV.Utilities.MCReweighting import ( TwoDimentionalVerticalReweighting, OneDimentionalVerticalReweighting,
                                           MatchJpsiKstPhysics, combineMoments,
                                           compareDistributions, cleanP2VVPlotStash, WeightedDataSetsManager
                                       )
from P2VV.RooFitWrappers import RooObject
from P2VV import RooFitDecorators
from math import pi, sqrt
import os, gc

# define workspace
ws = RooObject( workspace = 'iterativeProcedure' ).ws()

# build MC pdf, initialise physics matching class
print 'P2VV - INFO: Start reweighting, iteration Number (%s): MCProd/mergePeriods = %s/%s'%(iterNumb,MCProd,mergePer)
PhysicsReweight = MatchJpsiKstPhysics( monteCarloData, 
                                       KaonSign = kaonSign, 
                                       cspValues = CSP,                                       
                                       kpiBin = KpiBin, 
                                       Reduced = reduced, 
                                       Verbose = verbose )

# manage the weighted datasets
mcDataMngr = WeightedDataSetsManager( source = PhysicsReweight.getDataSet() )
mcDataMngr['saveIntermediateDatasets'] = True if makePlots else False
mcDataMngr['iterationNumber']          = iterNumb
source = lambda: mcDataMngr.getDataSet()

# get observables
angles     = [ ws[o] for o in ['helcosthetaK','helcosthetaL','helphi'] ]
muMomenta  = [ ws[o] for o in [ '%s_%s' % ( part, comp ) for part in ['muplus','muminus'] for comp in ('P','PX','PY','PZ') ]    ]
KpiMomenta = [ ws[o] for o in [ '%s_%s' % ( part, comp ) for part in ['Kplus','piminus']   for comp in ('P','PX','PY','PZ') ]    ]
Bmomenta   = [ ws['B_P'], ws['B_Pt'] ]
KpiMass    = [ ws['mdau2']]

# match physics
if reweightPhysics:
    PhysicsReweight.setDataSet( source() )
    physWeights = PhysicsReweight.calculateWeights( iterNumb, dataParameters )

    # append physics weights
    mcDataMngr.appendWeights( physWeightName, physWeights,
                              combWithPrevious = True,
                              scale            = scaleWeightsToNumEntr
                          )

# match Kpi momenta
if reweightKpimom and RewApproach == 'vertical':
    rewVars = filter(lambda n: n.endswith('_P'), map(lambda n: n.GetName(),KpiMomenta) )
    KpiMomWeights, plots = TwoDimentionalVerticalReweighting( source(), target, 2*[KpimomBins], rewVars,
                                                              equalStatBins = equalStatBins,
                                                              combWeights   = not KpimomWeightsOnly,
                                                              xCheckPlots   = True,
                                                              canvSufix     = '_'.join([MCProd,kaonSign,'bin%s'%KpiBin,'rew%s'%iterNumb])
                                                          )
    # append kinematic weights
    mcDataMngr.appendWeights( KmomentaWeightsName, KpiMomWeights,
                              combWithPrevious = False,
                              scale = scaleWeightsToNumEntr
                          )
elif reweightKpimom and RewApproach == 'horizontal':
    KpimomentaReweight = MatchWeightedDistributions( outTree        = target,      # Target: Distribution to be matched with
                                                    reweightVars   = ['Kminus_P'], # Variables that enter the transformation
                                                    inWeightName   = mcDataMngr.getWeightName(),
                                                    outWeightName  = sWeightsName,
                                                    observables    = angles + time + truetime,
                                                    nonObsVars     = muMomenta + KpiMomenta + Bmomenta + KpiMass,
                                                    nBins          = 1000           # preceision of the transformation
                                                    )

    KpimomentaReweight.reweight( iterNumb, source() )
    KmomentaWeightsName = 'hor' + KmomentaWeightsName
    mcDataMngr.setDataSet( KpimomentaReweight.getDataSet(),  KmomentaWeightsName )
print 'P2VV - INFO: Finished reweighting'

# write weighted dataset to file
outFileName = templateMCpath('',kaonSign,KpiBin).split('/')[-1].split('.root')[0].replace('__','_') + '_rew_%s.root'%iterNumb
outFile     = TFile.Open(outFileName,'RECREATE')
mcDataMngr.getDataSet('Kpimom').Write()
outFile.Close()
print 'P2VV - INFO: Wrote re-weighted datasets to file %s.'%outFileName

# plot data after each reweighting step
if makePlots:
    # build dataset with combined weights
    mcDataMngr.getCombinedDataSet( ['phys','Kpimom'] )

    from P2VV.Load import LHCbStyle
    from ROOT import TCanvas, kGreen, RooAbsData
    from math import pi
    plot_dataSets = [ target ] + [mcDataMngr.getDataSet(k) for k in [ 'initSource','phys','phys_Kpimom'] ]
    plot_vars     = angles + filter( lambda v: v.GetName().endswith('_P'), muMomenta + KpiMomenta )

    plot_canvSuf  =  '_'.join([MCProd,kaonSign,'bin%s'%KpiBin,'rew%s'%iterNumb])
    plot_canvs    = [ TCanvas('%s_%s'%(v.GetName(),plot_canvSuf),'%s_%s'%(v.GetName(),plot_canvSuf)) for v in plot_vars ]

    plot_opts = dict(DataError = RooAbsData.SumW2, XErrorSize = 0. )
    plot_bins = 20
    frames = []
    for obs, canv, yRange, xRange, xTitle in zip( plot_vars,
                                                  plot_canvs,
                                                  3 * [(0,30)] + 2 * [(0,60)] + 2 * [(0,50)],
                                                  2 * [(-1,1)] + [(-pi,pi)] + 2 *[(0,15e4)] + [(0,7e4)] + [(0,5e4)],
                                                  map(lambda o: o.GetTitle(), plot_vars),
                                              ):
        frame = obs.frame( Bins = plot_bins, Range = (xRange[0],xRange[1]) )
        frames += [frame]

        for data, scale, color in zip(  plot_dataSets,
                                        map(lambda d: target.sumEntries() / d.sumEntries(), plot_dataSets ),
                                       [1, 2, kGreen +3, 4],
                                   ):

            data.plotOn(frame, MarkerColor = color, Rescale = scale, **plot_opts)
            frame.SetAxisRange( yRange[0], yRange[1], 'Y' )
            frame.SetTitle('')
            frame.SetXTitle(xTitle)
            canv.cd()
            frame.Draw()

    # plot weights
    mcDataMngr.plotWeights('phys',name = plot_canvSuf )
    mcDataMngr.plotWeights('phys',name = plot_canvSuf )

    mcDataMngr.plotWeights('Kpimom',name = plot_canvSuf, Range = (0,2) )
    mcDataMngr.plotWeights('Kpimom',name = plot_canvSuf, Range = (0,2) )

    # print canvas
    for c in plot_canvs:
        c.Print(c.GetName() + '.pdf')

# Call script for angular efficiency moments.
import subprocess, shlex
eff_moms_opts = '--data-path %s --data-name %s --kaonSign %s --KpiBin bin%s --runPeriod %s --chanell %s --outMomsSufix %s'\
                %(outFileName, mcDataMngr.getDataSet().GetName(), +1 if kaonSign=='pos' else -1,KpiBin, MCProd, weights, iterNumb)
cmd = shlex.split( eff_moms_script + eff_moms_opts )

print '\nP2VV - INFO: Calling %s, with arguments:'%eff_moms_script
for arg in range(1,len(cmd),2):
    print '  ', cmd[arg], cmd[arg+1]
subprocess.call(cmd, stdin = None, stdout = None, stderr = subprocess.STDOUT)

# save memory
cleanP2VVPlotStash()
mcDataMngr.clear()
gc.collect()
