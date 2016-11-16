#!/usr/bin/env python

import argparse
parser = argparse.ArgumentParser()
parser.add_argument( '--runPeriod',   type=int, default = 2011  )
parser.add_argument( '--kaonSign',    type=int, default = -1    )
parser.add_argument( '--sigWeight',   type=str, default = ''    )
parser.add_argument( '--KpiBin',      type=str, default = 'all' )
parser.add_argument( '--simulation', action = 'store_true'     )
parser.add_argument( '--flipPhi',    action = 'store_true'     )
options = parser.parse_args()

print '\nParsed options:'
print 30*'-'
print 'Run Period: %s'%options.runPeriod
print 'Kaon Sign : %s'%options.kaonSign
print 'Kpi Bin   : %s'%options.KpiBin
print 'Simulation: %s'%options.simulation
print 'sWeight   : %s'%(None if options.simulation else options.sigWeight)
print '\n'

####################################################################################################################################################
## configure job ##
####################################################################################################################################################
saveDataSetToLocalFolder = True   # protect official output location
delIntermidiatTree       = True    # delete temporary file
runPeriods         = [2011,2012]
prodDate           = '250615'
createAngAccNtuple = True  # add track momenta branches
minimalNtuple      = True
addKpiMassCategory = True
addKaonSignInfo    = True
addRunPeriodInfo   = True
saveOldHelAngles   = False 
applySelection     = False 
calculateHelAngles = False
oldHelAngleNames   = dict( ctheta = 'helcosthetaK', 
                           cpsi   = 'helcosthetaL', 
                           phi    = 'B0_Phi'        
                          ) 
daughterPartNames  = dict( posHad = 'Kplus'  , 
                           negHad = 'piminus',  
                           posLep = 'muplus' ,  
                           negLep = 'muminus'  ) if options.kaonSign > 0 else dict(posHad = 'piminus',
                                                                                   negHad = 'Kplus', 
                                                                                   posLep = 'muplus' , 
                                                                                   negLep = 'muminus' )



daughterPartNameSuf = dict(x='_PX', y='_PY', z='_PZ')
KpiMassBranchName  = 'Kst_892_0_MM'
KpiMassBin         = options.KpiBin
KpiMassBinBounds   = [826, 861, 896, 931, 966]
KpiMassInds        = range( len(KpiMassBinBounds) + 1 )
per_x_sign_labels  = [ '%s%s'%(s,p) for p in ['2011','2012']  for s in ['pos','neg'] ]
outDataSetName     = 'Bs2JpsiKst'
runPeriod          = options.runPeriod
kaonSign           = options.kaonSign
kaonSignStr        = 'neg' if options.kaonSign < 0 else 'pos'
dataSetKey         = str(runPeriod) + kaonSignStr + 'Kaons' + KpiMassBin
wghtArg            = options.sigWeight
if   's' in wghtArg or 'S' in wghtArg: weightName, weightVarName = 'Bs', 'cor_sWeights_Bs' 
elif 'd' in wghtArg or 'D' in wghtArg: weightName, weightVarName = 'Bd', 'cor_sWeights_Bd'
elif options.simulation: weightName, weightVarName = None, None 

# data set paths
inputPath      = '/data/bfys/vsyropou/Bs2JpsiKst/DiegosUnrefinedTuples/'
inputTreeName  = 'DecayTree'

protoTreePath  = inputPath + 'MC/high_stat/protoTree_%s_%s.root'%(kaonSignStr,runPeriod,) if options.simulation \
                 else inputPath + 'RealData/NewLbBkgModels_ForApproval/%sprotoTree_%s_%s.root'%( 'flipPhi/' if options.flipPhi else '', kaonSignStr,runPeriod)

# output paths
outputPath     = '/project/bfys/vsyropou/data/Bs2JpsiKst/RealData/' if not saveDataSetToLocalFolder else './'
# outDataSetFile = outputPath + 'P2VVDataSet_Bs2JpsiKst_%s%s_Reco14_%sKaons_%s_KpiBin_%s%s.root'\
#                  %(runPeriod,'_Sim08' if options.simulation else '',kaonSignStr, KpiMassBin, prodDate, '_%sWeights'%weightName if not options.simulation else '' )
outDataSetFile = outputPath + 'P2VVDataSet_Bs2JpsiKst_%s%s_Reco14_%sKaons_%sKpiBins_%s%s.root'\
                 %(runPeriod,'_Sim08' if options.simulation else '',kaonSignStr, KpiMassBin, prodDate, '_%sWeights'%weightName if not options.simulation else '' )

# select and rename branches
from P2VV.Load import P2VVLibrary
from ROOT import RooNumber
from math import pi

RooInf = RooNumber.infinity()
KKMin  = KpiMassBinBounds[0]
KKMax  = KpiMassBinBounds[-1]
KKVal  = KKMin + (KKMax - KKMin) / 2.

obsDict = dict( runPeriod        = ( 'runPeriod',    'run period', { 'p%s'%runPeriod : runPeriod for runPeriod in runPeriods }       ,'runPeriod'  ),
                KpiMassCat       = ( 'KpiMassCat',   'KpiMassCat', {       'bin%s'%b : b  for b in range(1,len(KpiMassBinBounds))}   ,'KpiMassCat' ),               
                kaonSign         = ( 'kaonSign',     'kaon sign',  {        'neg': -1, 'pos': 1}                                     ,'kaonSign'   ),  
                per_x_sign       = ( 'per_x_sign',   'per x sign', {  key : idx for idx, key in enumerate(per_x_sign_labels)     }   , 'per_x_sign'),
                mass             = ( 'mass',         'm(J/#psi K^{+}#pi^{-})', 'MeV/c^{2}', 5368., 5110.,  5690.,  'B0_MM'                      ), 
                Mjpsik           = ( 'mJpsiK',       'm(J/#psi K^{+}',         'MeV/c^{2}', 4594, -RooInf, RooInf, 'Mjpsik'                    ),
                Kst_892_0_MM     = ( 'mdau2',        'm(K^{+}#pi^{-})',        'MeV/c^{2}', KKVal,  KKMin,  KKMax,  'Kst_892_0_MM'              ),
                J_psi_1S_MM      = ( 'mdau1',        'm(mu^{+}#mu^{-})',       'MeV/c^{2}', 3094, -RooInf, RooInf, 'J_psi_1S_MM'               ),
                cor_sWeights_Bs  = ( 'Bs_sWeight',   'corrected Bs sWeights',  '',           0.,  -RooInf, RooInf,  'cor_sWeights_nBs'          ),
                cor_sWeights_Bd  = ( 'Bd_sWeight',   'corrected Bd sWeights',  '',           0.,  -RooInf, RooInf,  'cor_sWeights_nBd'          ),
                helcosthetaK     = ( 'helcosthetaK', 'cos(#theta_{K})',        '',           0.,    -1.,     +1. ,  oldHelAngleNames['ctheta'] ),
                helcosthetaL     = ( 'helcosthetaL', 'cos(#theta_{#mu})',      '',           0.,    -1.,     +1. ,  oldHelAngleNames['cpsi']   ),
                helphi           = ( 'helphi',       '#phi_{h}',               'rad',        0.,    -pi,     +pi ,  oldHelAngleNames['phi']    )
                )

# add branches for angEff or helicity angles calculation
if createAngAccNtuple or calculateHelAngles:
    for name in [ '%s_%s' % ( part, comp ) for part in [ 'muplus', 'muminus', 'Kplus', 'piminus' ] for comp in ( 'PX', 'PY', 'PZ', 'P' ) ] + ['B0_P', 'B0_PT']:
        obsDict[name] = ( name, name, 'MeV/c', 0.,   -RooInf, +RooInf, name )

# remove unecesessary weights 
if options.simulation: 
    for key in ['cor_sWeights_Bs', 'cor_sWeights_Bd']: obsDict.pop(key)
elif weightName == 'Bs': obsDict.pop('cor_sWeights_Bd')
elif weightName == 'Bd': obsDict.pop('cor_sWeights_Bs')

# minimal dataset for fitting
if minimalNtuple: 
    for key in ['Mjpsik','J_psi_1S_MM']: obsDict.pop(key)

#####################################################################################################################
## refine ntuple ##
#######################

# read input file
from ROOT import TFile
protoFile   = TFile.Open(protoTreePath)
protoTree   = protoFile.Get(inputTreeName)
initNumEvts = protoTree.GetEntries()
print 'P2VV - INFO: Processing tree (%s initial entries): %s'%(initNumEvts,protoTreePath)

# save old helicity angles in case you calculate new ones
if saveOldHelAngles:
    print 'P2VV - INFO: Saving old Helicity angles'
    protoTree.SetBranchStatus('*',0)
    for branch in oldHelAngleNames.values():protoTree.SetBranchStatus(branch,1)

    from ROOT import TFile
    oldHelAngFile = TFile.Open('oldHelAnglesFor_%s.root'%dataSetKey,'recreate')
    oldHelAngTree = protoTree.CloneTree()

    from ROOT import copyFloatInTree 
    for oldHelAngBranch, copyOldHelAngBranch in { oldHelAngleNames['ctheta']  : 'helcosthetaK_old',
                                                  oldHelAngleNames['cpsi']    : 'helcosthetaL_old', 
                                                  oldHelAngleNames['phi']     : 'helphi_old'        }.iteritems():
        print 'P2VV - INFO: Copying and renaming branch: %s --> %s'%(oldHelAngBranch, copyOldHelAngBranch)
        copyFloatInTree( oldHelAngTree, oldHelAngBranch, copyOldHelAngBranch )

    oldHelAngTree.Write()
    oldHelAngFile.Close()
    del oldHelAngFile

    protoTree.SetBranchStatus('*',1)
    for branch in oldHelAngleNames.values(): protoTree.SetBranchStatus(branch,0)
    print 'P2VV - INFO: Wrote old helicity angles to file: %s'%'oldHelAnglesFor_%s.root'%dataSetKey
    print 'P2VV - INFO: Continue processing main file'

intermediateFileName = 'temp_FileFor_%s.root'%dataSetKey
intermediateFile = TFile.Open(intermediateFileName, 'recreate')
intermediateTree = protoTree.CloneTree()

protoFile.Close()
del protoFile

# create new branches
from ROOT import addIntegerToTree 
if addRunPeriodInfo:   
    print 'P2VV - INFO: Adding run period (%s) info to ntuple'%runPeriod
    addIntegerToTree(intermediateTree, int(runPeriod), 'runPeriod' )

if addKaonSignInfo:
    print 'P2VV - INFO: Adding kaon sign (%+i) info to ntuple'%kaonSign
    addIntegerToTree(intermediateTree, int(kaonSign), 'kaonSign' )

if addKpiMassCategory: 
    from ROOT import addCategoryToTree, std
    print 'P2VV - INFO: Adding Kpi-mass category with indices "%s" and Kpi-mass boundaries "%s" to n-tuple' % ( KpiMassInds, KpiMassBinBounds )
    bounds = std.vector('Double_t')()
    inds   = std.vector('Int_t')()
    for bound in KpiMassBinBounds : bounds.push_back(bound)
    for ind in KpiMassInds : inds.push_back(ind)
    addCategoryToTree( intermediateTree, KpiMassBranchName, 'KpiMassCat', bounds, inds )

print 'P2VV - INFO: Adding sign_x_per category index (%+i) info to ntuple'%per_x_sign_labels.index('%s%s'%(kaonSignStr,runPeriod))
addIntegerToTree(intermediateTree, int(per_x_sign_labels.index('%s%s'%(kaonSignStr,runPeriod))), 'per_x_sign' )

# copy-rename branches
from ROOT import copyFloatInTree
for observable in obsDict.itervalues():
    if observable[-1] != observable[0]:
        if observable[-1] not in oldHelAngleNames.values():
            print 'P2VV - INFO: Copying and renaming branch: %s --> %s'%(observable[-1],observable[0])
            copyFloatInTree( intermediateTree, observable[-1], observable[0])
        else:
            if not calculateHelAngles == True:
                print 'P2VV - INFO: Copying and renaming branch: %s --> %s'%(observable[-1],observable[0])
                copyFloatInTree( intermediateTree, observable[-1], observable[0])
            else: pass 
    else: pass

if calculateHelAngles:
    print 'P2VV - INFO: Calculating helicity angles'
    from ROOT import TDatabasePDG, addHelicityAnglesToTree
    MeV = 1000 # TDatabasePDG is in MeV
    PDG = TDatabasePDG()
    Mmu = PDG.GetParticle('mu-').Mass()*MeV
    Mk  = PDG.GetParticle('K-').Mass()*MeV
    Mpi = PDG.GetParticle('pi-').Mass()*MeV
    
    posHadMass = Mk  if 'K' in daughterPartNames['posHad'] else Mpi
    negHadMass = Mpi if 'pi' in daughterPartNames['negHad'] else Mk
    lepMass    = Mmu

    sufixes = std.vector('TString')()
    for component in ['x','y','z']: sufixes.push_back(daughterPartNameSuf[component])
    
    print ' P2VV - INFO: The following associations will be made:\n '\
        ' Positive hadron branch name: %s, mass=%s \n  Negative hadron branch name: %s, mass=%s \n '\
        ' Positive lepton branch name: %s, mass=%s \n  Negative lepton branch name: %s, mass=%s \n'\
        ' Units MUST be in MeV. Check!!!'\
        %(daughterPartNames['posHad'], posHadMass, daughterPartNames['negHad'], negHadMass,\
          daughterPartNames['posLep'], lepMass, daughterPartNames['negLep'], lepMass)

    print ' Helicity angles names:\n helcosthetaK = %s \n helcosthetaL = %s \n helphi = %s'\
        %( obsDict['helcosthetaK'][0], obsDict['helcosthetaL'][0], obsDict['helphi'][0] )

    addHelicityAnglesToTree(intermediateTree, 
                            daughterPartNames['posHad'], daughterPartNames['negHad'], 
                            daughterPartNames['posLep'], daughterPartNames['negLep'],
                            posHadMass, negHadMass, lepMass, lepMass,
                            obsDict['helcosthetaK'][0], obsDict['helcosthetaL'][0], obsDict['helphi'][0],
                            sufixes, 'Double_t'
                            )
    

# close intermediate files
intermediateTree.Write()
intermediateFile.Close()
del intermediateFile
print 'P2VV - INFO: Wrote intermediate tree to file: %s'%intermediateFileName
print 'P2VV - INFO: Finished refining tree. Continuing to create RooDataSet'        

##########################################################################################
## create RooDataSet ##
##########################################################################################

# create workspace
from P2VV.RooFitWrappers import RooObject, RealVar, Category
ws = RooObject(workspace = 'JpsiphiWorkspace').ws()

# create observables
observables  = { }
for obs in obsDict.keys():
    if type( obsDict[obs][2] ) == dict or type( obsDict[obs][2] ) == list :
        observables[obs] = Category( obsDict[obs][0], Title = obsDict[obs][1], Observable = True, States = obsDict[obs][2] )
    else :
        observables[obs] = RealVar( obsDict[obs][0], Title = obsDict[obs][1], Unit = obsDict[obs][2], Observable = True
                                   , Value = obsDict[obs][3], MinMax = ( obsDict[obs][4], obsDict[obs][5] ) )
if minimalNtuple:
    observables = filter( lambda var: var.GetName().split('_')[-1] not in ['PX','PY','PZ','P','PT']  ,observables.values())

# ntuple selection string
dataSetArgs = {}
if applySelection:
    from P2VV.Imports import cutSelStringsJpsiKst as selection
    selection.pop('noSelection')
    if runPeriod == 2011: selection.pop('bdtg_2012')
    if runPeriod == 2012: selection.pop('bdtg_2011')
    dataSetArgs['ntupleCuts'] =  ' && '.join( selection.itervalues() )

# read tree into RooDataSet
from P2VV.Utilities.DataHandling import readData
outDataSet = readData( intermediateFileName, inputTreeName, 
                       NTuple       = True,
                       observables  = observables,
                       WeightVar    = ( weightName + '_sWeight',True ) if not options.simulation else '',            
                       ImportIntoWS = False,
                       **dataSetArgs
                       )
outDataSet.SetName(outDataSetName)
outDataSet.Print()
if initNumEvts != outDataSet.numEntries(): print 'P2VV -INFO: You lost %s entries due to selection cuts:'% (initNumEvts-outDataSet.numEntries()) 

# create final output file
outFile = TFile.Open(outDataSetFile, 'recreate')
outDataSet.Write()
outFile.Close()
del outFile
print 'P2VV - INFO: Wrote final dataset to file %s'%(outDataSetFile) 

if delIntermidiatTree:
    import os
    os.remove(intermediateFileName)
    print 'P2VV - INFO: Delete temporary file %s'%(intermediateFileName) 
