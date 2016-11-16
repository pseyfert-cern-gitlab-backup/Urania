import argparse
parser = argparse.ArgumentParser()
parser.add_argument( '--weights',      default = 'Bs',  type = str )
parser.add_argument( '--kaonSign',     default = 'all', type = str )
parser.add_argument( '--runPeriod',    default = '3fb', type = str )
parser.add_argument( '--KpiBin',       default = 'all', type = str )

parser.add_argument( '--fit-setZeroACP',            action = 'store_true' )
parser.add_argument( '--fit-constr-ProdAssym',      action = 'store_true' )
parser.add_argument( '--fit-constr-DetAssym',       action = 'store_true' )
parser.add_argument( '--fit-constr-FloatAcc',       action = 'store_true' )
parser.add_argument( '--fit-constr-FloatAcc-Sigma', default = 1, type = float )
parser.add_argument( '--fit-SimulRunPer',           action = 'store_true' )
parser.add_argument( '--fit-flipPhi',               action = 'store_true' )
parser.add_argument( '--fit-Minos',                 action = 'store_true' )
parser.add_argument( '--fit-Minos-all',             action = 'store_true' )
parser.add_argument( '--fit-RandomPars',            action = 'store_true' )
parser.add_argument( '--fit-unblind',               action = 'store_true' )
parser.add_argument( '--fit-doNotFit',              action = 'store_true' )
parser.add_argument( '--fit-setParsInitVal',        action = 'store_true' )
parser.add_argument( '--fit-nllScanMode',           action = 'store_true' )
parser.add_argument( '--fit-NumCpu',                default = 8, type=int )

parser.add_argument( '--angAccFile',     )
parser.add_argument( '--angAcc-path',    )
parser.add_argument( '--angAcc-nameSuf', )
parser.add_argument( '--angAcc-rewNumb', )

parser.add_argument( '--ParFileIn',     default = '' )
parser.add_argument( '--ParFileOut',    default = '' )
parser.add_argument( '--writeUnBlPar',  action = 'store_true' )

parser.add_argument( '--verbose',         action = 'store_true' )
parser.add_argument( '--verbose-roofit',  action = 'store_true' )
parser.add_argument( '--plot',            action = 'store_true' )
parser.add_argument( '--plot-slices',     action = 'store_true' )
parser.add_argument( '--plot-cpComps',    action = 'store_true' )
parser.add_argument( '--plot-pWaveComps', action = 'store_true' )
parser.add_argument( '--plot-noPulls',    action = 'store_false' )
parser.add_argument( '--plot-LHCbLogo',   action = 'store_true' )
parser.add_argument( '--plot-splitCanv',  action = 'store_true' )
parser.add_argument( '--plot-canvSuffix' )
opts = parser.parse_args()

# sanity checks of parsed arguments
if opts.kaonSign in ['pos', 'neg']: opts.fit_setZeroACP = True
if opts.fit_Minos_all: opts.fit_Minos = True
if opts.weights == 'Bd': opts.fit_unblind = True 
if opts.plot_pWaveComps: opts.plot_cpComps = True
if opts.plot_slices or opts.plot_cpComps: opts.plot = True
if opts.plot: opts.fit_flipPhi = True

# supress object handling output from workspace and redirect minimization errors
from ROOT import RooMsgService, RooFit
from P2VV import RooFitDecorators

if not opts.verbose_roofit:
    _o = lambda s: getattr(RooFit,s) # TODO:  Write a decorator about that
    MsgSvc = RooMsgService.instance()
    for stream in [0,1]:
        MsgSvc.getStream(stream).removeTopic(_o('ObjectHandling'))
        MsgSvc.getStream(stream).removeTopic(_o('Minimization'))
        MsgSvc.getStream(stream).removeTopic(_o('Eval'))
    MsgSvc.addStream( _o('ERROR'),   Topic = _o('Minimization'),   OutputFile = 'minimization_err.out' )
    MsgSvc.addStream( _o('WARNING'), Topic = _o('Minimization'),   OutputFile = 'minimization_wrn.out' )
    MsgSvc.addStream( _o('ERROR'),   Topic = _o('Eval'),           OutputFile = 'evaluation_err.out'   )
    MsgSvc.addStream( _o('INFO'),    Topic = _o('ObjectHandling'), OutputFile = 'objectHandling.out'   )
    MsgSvc.Print()
    print

#####################################################################################################################
## configuration  ##
####################

# input
path = '/project/bfys/vsyropou/data/Bs2JpsiKst/'

dataSetFileName = 'P2VVDataSet_Bs2JpsiKst_3fb_Reco14_%sKaons_allKpiBins_250615_%sWeights.root'%(opts.kaonSign,opts.weights)
if not opts.fit_flipPhi:
    dataSetFile =  path + 'RealData/fourth_round_newLbModel_forAproval/' + dataSetFileName
else:
    dataSetFile = path + 'RealData/fourth_round_newLbModel_forAproval/flipPhi/' + dataSetFileName

dataSetName   = 'Bs2JpsiKst'
weightVarName = '%s_sWeight'%opts.weights

# miscelaneous
maxCorr = 0.1 # correlations grater than maxCorr are dumped after fitting
drawLegend = True

# fit configuration
from P2VV.Parameterizations.FullPDFs import Bs2JpsiKst_RunIAnalysis as PdfConfig
pdfConfig = PdfConfig()
pdfConfig['verbose'] = opts.verbose

pdfConfig['sWeights']         = opts.weights
pdfConfig['kaonSign']         = opts.kaonSign
pdfConfig['runPeriods']       = opts.runPeriod

pdfConfig['mergeAccPeriods']  = not opts.fit_SimulRunPer
pdfConfig['setZeroACP']       = opts.fit_setZeroACP

pdfConfig['phiAnglePlip']     = opts.fit_flipPhi

pdfConfig['KpiMassBinBounds'] = [ 896 - 70, 896 - 35, 896, 896 + 35, 896 + 70 ]
pdfConfig['CSPValues'] = [ 0.9681, 0.9312, 0.9519, 0.9880]
if opts.KpiBin != 'all':
    pdfConfig['KpiMassBinBounds'] = [ pdfConfig['KpiMassBinBounds'][b] for b in [int(opts.KpiBin)-1,int(opts.KpiBin)] ]
    pdfConfig['CSPValues'] = [ pdfConfig['CSPValues'][int(opts.KpiBin)-1] ]

# float angular accetance with gaussian constraints
pdfConfig['constAngEffCoefs'] = not opts.fit_constr_FloatAcc
pdfConfig['floatAngularAcc']  = opts.fit_constr_FloatAcc 
pdfConfig['angAccConstrSigma']  = opts.fit_constr_FloatAcc_Sigma

# float production / detection assymetries with gaussian constraints
if not opts.fit_constr_ProdAssym: pdfConfig['externalConstr'].pop('A_P')
if not opts.fit_constr_DetAssym:  pdfConfig['externalConstr'].pop('A_D')

# swich blidn on/off
if opts.fit_unblind: pdfConfig['blind'] = {}

# read / write fited parameters from / to file
parFileName = '%s_%sKaons_%s_%s%s%s%s%s%s.par'%(pdfConfig['sWeights'], pdfConfig['kaonSign'],
                                        '%s%s'%(pdfConfig['runPeriods'], '_mergeAccPer' if pdfConfig['mergeAccPeriods'] else ''),
                                        opts.KpiBin + 'KpiBins' if opts.KpiBin =='all' else opts.KpiBin + 'KpiBin',
                                        '_Minos' if opts.fit_Minos else '',
                                        '_Acp%s'%('Zero' if opts.fit_setZeroACP else 'Free%s'\
                                                  %('_unblind' if (opts.fit_unblind and 'Bs' in opts.weights) else '')),
                                        '_floatProdAssym' if opts.fit_constr_ProdAssym else '',
                                        '_floatDetAssym'  if opts.fit_constr_DetAssym else '',
                                        '_floatAcc'       if pdfConfig['floatAngularAcc'] else ''
)

parFileIn = ''
if not 'None' in opts.ParFileIn:
    if opts.ParFileIn : 
        parFileIn = opts.ParFileIn
    else:
        parFileIn = path + 'fitResults/%s'%parFileName

parFileOut = opts.ParFileOut if opts.ParFileOut else parFileName

# angular acceptance input
simulCats = ['kaonSign' if opts.kaonSign=='all' else '', \
             'runPeriods' if not opts.runPeriod=='3fb' else '',\
             'KpiMass' if len(pdfConfig['KpiMassBinBounds'])>1 else '' ]

if len(simulCats) == 0:
    pdfConfig['anglesEffType']   = 'weights'
    pdfConfig['angEffMomsFiles'] = opts.angAccFile if opts.angAccFile \
        else path   + '/AngularAcceptance/Sim08_%s_hel_%sKaons_%s_KpiRange_Phys_norm_moms'%(opts.runPeriod,opts.kaonSign)
    AngAccPath = pdfConfig['angEffMomsFiles']
else:
    from P2VV.Parameterizations.FullPDFs import SimulCatSettings

    KaonSigns    = [ 'pos', 'neg' ]  if pdfConfig['kaonSign'] == 'all' else [ pdfConfig['kaonSign'] ]
    KpiMassBins  = [ '%s_%s'%(pdfConfig['KpiMassBinBounds'][idx], pdfConfig['KpiMassBinBounds'][idx+1]) for idx in range(len(pdfConfig['KpiMassBinBounds'])-1) ]

    # pdfConfig['constAngEffCoefs'] = False
    pdfConfig['anglesEffType']   = 'custom_jpsiKst' 
    pdfConfig['angEffMomsFiles'] = SimulCatSettings('angAcc')

    templateAccFile = lambda bin, sign: 'Sim08_3fb_hel_%sKaons_bin%s_%sBasis_constr%s'%\
                      ( sign,
                        bin, 
                        'reweighted_%s_'%opts.angAcc_rewNumb if opts.angAcc_rewNumb else '',
                        '_%s'%opts.angAcc_nameSuf if opts.angAcc_nameSuf else '' )

    if opts.angAcc_path:
        AngAccPath = opts.angAcc_path
    else:   
        AngAccPath =  path + 'AngularAcceptance/reweighted/'

    periods  = [ '2011', '2012' ] if pdfConfig['runPeriods'] == '3fb' else [pdfConfig['runPeriods']]
    assert 'KpiMass' in simulCats, 'P2VV - WARNING: There is no point in fitting for Acp w/o simulatanous being simultaneous in Kaon sign.'
    # assert len(periods)>1,         'P2VV - WARNING: Acp Simultaneous fit in periods is not available yet.'

    for sign_x_per in ['%s%s'%(sign,per) for per in periods for sign in KaonSigns ]:
        if opts.KpiBin != 'all':
            assert len(pdfConfig['KpiMassBinBounds'])==2 and len(pdfConfig['CSPValues'])==1, 'P2VV - ERROR: Invalid configurations for Kpi bins.'
            pdfConfig['angEffMomsFiles'].addSettings( [ 'superCat' ], [ ['{%s;bin%s}'%(sign_x_per,opts.KpiBin)] ], AngAccPath + templateAccFile(opts.KpiBin,sign_x_per[:3]) )
        else:
            for b, b_lab in enumerate(KpiMassBins):
                pdfConfig['angEffMomsFiles'].addSettings( [ 'superCat' ], [ ['{%s;bin%s}'%(sign_x_per,b+1)] ], AngAccPath + templateAccFile(b+1,sign_x_per[:3]) )

print
print 'Job configuration:'
print 31*'-'
print 'Fiting for                 : %s'%opts.weights
print 'Kaons sign                 : %s'%opts.kaonSign
print 'Running period             : %s'%opts.runPeriod
print 'KpiBin number              : %s'%opts.KpiBin
print 'Unblind flag               : %s'%opts.fit_unblind
print 'Split acc for run period   : %s'%( not pdfConfig['mergeAccPeriods'] )
print 'Fix Acp Assymetries to 0   : %s'%opts.fit_setZeroACP
print 'Float Prod /Det assymetries: %s/%s'%(opts.fit_constr_ProdAssym,opts.fit_constr_DetAssym)
print 'Float Angular Aceptance    : %s'%pdfConfig['floatAngularAcc']
print 'Kpi bin bounds             : %s'%pdfConfig['KpiMassBinBounds']
print 'CSP factors                : %s'%map(lambda n: round(n,3),pdfConfig['CSPValues'])
print 'Minos errors               : %s'%opts.fit_Minos
print 'Nll scans mode             : %s'%opts.fit_nllScanMode
print 'Number of CPU cores        : %s'%opts.fit_NumCpu
print 'Offset float pars randomly : %s'%opts.fit_setParsInitVal
print 'Initial parameter values   : %s'%parFileIn
print 'Angular acceptance path    : %s'%AngAccPath
print 'Fitting Dataset            : %s'%dataSetFile
print 31*'-'
print 'Finished configuration. For verbose output use --verbose, for un-supressing roofit output use --verbose--roofit'
print

#####################################################################################################################
## read data and build pdf ##
############################

# workspace
from P2VV.RooFitWrappers import RooObject
ws = RooObject( workspace = 'JpsiKstWorkspace' ).ws()

# read data
from P2VV.Utilities.DataHandling import readData
if opts.kaonSign == 'all' and opts.runPeriod == '3fb' and opts.KpiBin == 'all' : 
    fitData = readData( filePath = dataSetFile, dataSetName = dataSetName,  NTuple = False, WeightVar = weightVarName)
else:
    fitData = readData( filePath = dataSetFile, dataSetName = dataSetName,  NTuple = False, WeightVar = weightVarName)
    
    # re-define categories and make cut strings
    cut_string = ''

    # kaon sign
    sign_x_per_cat = ws['per_x_sign']
    sign_x_per_cat.clearTypes()
    
    sign_x_per_labs = [ '%s%s'%(sign,per) for per in periods for sign in KaonSigns ]
    from itertools import product
    for idx, prod in enumerate( product( ['2011','2012'], ['pos','neg'] )):
        label = '%s%s'%(prod[1],prod[0])
        if label in sign_x_per_labs:
            sign_x_per_cat.defineType(label,idx)

    sign_cut =  ' || '.join( map(lambda lbl:'per_x_sign == per_x_sign::%s'%lbl, sign_x_per_labs ) )
    cut_string += '( %s )'%sign_cut

    # KpiBin
    if opts.KpiBin != 'all':
        KpiMassCat = ws['KpiMassCat']
        KpiMassCat.clearTypes()
        KpiMassCat.defineType('bin%s'%opts.KpiBin, int(opts.KpiBin))
        KpBin_cut = 'KpiMassCat == KpiMassCat::bin%s'%opts.KpiBin
        
        if cut_string: cut_string += ' && ( %s ) '%KpBin_cut
        else:          cut_string += '( %s )'%KpBin_cut

    # make a data slice 
    fitData = fitData.reduce(Cut = cut_string )
    print 'P2VV - INFO: Applyied cut to dataset: %s'%cut_string
    print 'P2VV - INFO: Events after cutting: %s (%s weighted)'%( fitData.numEntries(),round(fitData.sumEntries(),1) )

pdfConfig['signalData'] = fitData
pdfConfig['readFromWS'] = True

# build PDF
from P2VV.Parameterizations.FullPDFs import Bs2JpsiKst_PdfBuilder as PdfBuilder
pdfBuild = PdfBuilder( **pdfConfig )
pdf = pdfBuild.pdf()

# read parameters from file
if parFileIn:
    parameters_file = ''
    import os
    if os.path.exists( parFileIn ):
        parameters_file = parFileIn
    elif os.path.exists( parFileIn.replace('Acp','Minos_Acp') ):
        parameters_file = parFileIn.replace('Acp','Minos_Acp')
    elif opts.fit_constr_ProdAssym or opts.fit_constr_DetAssym or pdfConfig['floatAngularAcc']:
        if os.path.exists( '%s.par'%parFileIn.split('_float')[0] ):
            parameters_file = '%s.par'%parFileIn.split('_float')[0]

    if parameters_file:
        if not parameters_file == parFileIn:
            print 'P2VV - WARNING: Asked to read parameters from file but the file does not exist (%s).'%parFileIn            
            print 'P2VV - WARNING: Using another file to read input parameters (%s).'%parameters_file
        else:
            pdfConfig.readParametersFromFile( filePath = parameters_file )
            pdfConfig.setParametersInPdf(pdf)
    else:
        print 'P2VV - WARNING: Asked to read parameters from file but the file does not exist (%s).'%parFileIn

print '-' * 80 + '\n'

# override starting point and range of flaoting parameters
parameters = {}

#  Bs weights
if not opts.fit_setParsInitVal: pass
elif opts.weights == 'Bs':
    parameters.update( {
    # 'ACP0':    ( -0.05,  -0.5, +0.5, True ),
    # 'ACPpar':  ( +0.17,  -0.5, +0.5, True ),
    # 'ACPperp': ( -0.05,  -0.5, +0.5, True ),
    # 'ACPS':    ( +0.17,  -0.7, +0.7, True ),

    'ASPhase_bin1': ( +0.49, -0.5, +1.5, True ),
    'ASPhase_bin2': ( -0.51, -1.5, +0.5, True ),
    'ASPhase_bin3': ( -1.28, -1.8, -0.3, True ),
    'ASPhase_bin4': ( -1.64, -2.6, -0.6, True ),

    # 'f_S_bin1'   : (  +3.1, +2.5, +3.5, True ),
    # 'f_S_bin2'   : (  +3.1, +2.5, +3.5, True ),
    # 'f_S_bin3'   : (  +3.1, +2.5, +3.5, True ),
    # 'f_S_bin4'   : (  +3.1, +2.5, +3.5, True ),

    'AparPhase':   (  -2.7, -3.7, -1.7, True ),
    'AperpPhase':  (  +0.0, -1.0, +1.0, True ),

    # 'A0Mag2':    (  +2.9, +1.0, +4.0, True ),
    # 'AperpMag2': (  +2.9, +1.0, +4.0, True ),

    })

#  Bd weights
elif opts.weights == 'Bd':
    parameters.update( {

    # 'ACP0':    ( -0.05,  -0.5, +0.5, True ),
    # 'ACPpar':  ( +0.17,  -0.5, +0.5, True ),
    # 'ACPperp': ( -0.05,  -0.5, +0.5, True ),
    # 'ACPS':    ( +0.17,  -0.7, +0.7, True ),

    'ASPhase_bin1': (  +3.17, +2.7, +3.7, True ),
    'ASPhase_bin2': (  +2.54, +2.0, +3.0, True ),
    'ASPhase_bin3': (  +1.71, +1.2, +2.3, True ),
    'ASPhase_bin4': (  +1.39, +0.9, +1.9, True ),

    # 'f_S_bin1'   : (  +3.1, +2.5, +3.5, True ),
    # 'f_S_bin2'   : (  +3.1, +2.5, +3.5, True ),
    # 'f_S_bin3'   : (  +3.1, +2.5, +3.5, True ),
    # 'f_S_bin4'   : (  +3.1, +2.5, +3.5, True ),

    'AperpPhase': (  +2.9, +2.5, +3.5, True ),
    'AparPhase':  (  -2.9, -3.5, -2.5, True ),

    # 'A0Mag2':    (  +2.9, +1.0, +4.0, True ),
    # 'AperpMag2': (  +2.9, +1.0, +4.0, True ),

    })
    
for name, val in parameters.iteritems():
    if ws[name]:
        print 'P2VV - INFO: Overriding starting point of parameter %s:  Value: %s, Range: ( %s, %s ). Float: %s'%(name,val[0],val[1],val[2],val[3])
        ws[name].setRange(val[1],val[2])
        ws[name].setVal(val[0])

        if len( val ) == 4 and not val[3]:
            ws[name].setConstant()
print

# give parameters a random offset
if opts.fit_RandomPars:
    from ROOT import RooArgSet
    import random
    for p in RooArgSet( p for p in pdf.getParameters(fitData) if not p.isConstant() ):
        while True:
            rnd = random.uniform(-2,2)
            if rnd>1 or rnd<-1: 
                p.setVal( p.getVal() + rnd * p.getError() )
                break

# dump parameters and observables
if opts.verbose or opts.fit_nllScanMode:
    from ROOT import RooArgSet
    print 'P2VV - INFO: Observables:'
    pdf.getObservables(fitData).Print('v')
    print
    print 'P2VV - INFO: Floating parameters:'
    RooArgSet( p for p in pdf.getParameters(fitData) if not p.isConstant() ).Print('v')
    print
    print 'P2VV - INFO: Constant parameters:'
    RooArgSet( p for p in pdf.getParameters(fitData) if p.isConstant() ).Print('v')
    print

###########################################################################################################################################
## fit data ##
##############

if not opts.fit_doNotFit:
    if opts.fit_Minos and not opts.fit_Minos_all:
        from ROOT import RooArgSet
        minosPars = RooArgSet(p for p in pdf.getParameters(fitData) if ( not p.isConstant() and 'Yield' not in p.GetName()) )
    else:
        minosPars = opts.fit_Minos

    fitOpts = dict( Save  = True, 
                    Timer = True,
                    NumCPU     = opts.fit_NumCpu,
                    Minimizer  = 'Minuit2',
                    Strategy   = 2 if len(simulCats) != 0 else 1,
                    Optimize   = 2,
                    Offset     = True,
                    SumW2Error = False,
                    Hesse      = not opts.fit_nllScanMode ,
                    Minos      = minosPars,
                    PrintEvalErrors = 0
                )

    fitResult = pdf.fitTo( fitData, **fitOpts )

    # print fit result in an awesome way
    from P2VV.Imports import parNames
    if pdfConfig['sWeights'] == 'Bs':
        if opts.fit_setZeroACP:
            from P2VV.Imports import jspiKstParValues_Bs_3fb_zeroACP as jspiKstParValues
        else:
            from P2VV.Imports import jspiKstParValues_Bs_3fb_freeACP as jspiKstParValues
    else:
        if opts.fit_setZeroACP:
            from P2VV.Imports import jspiKstParValues_Bd_3fb_zeroACP as jspiKstParValues
        else:
            from P2VV.Imports import jspiKstParValues_Bd_3fb_freeACP as jspiKstParValues

    fitResult.PrintSpecial( text = True, ParNames = parNames, ParValues = jspiKstParValues )

    if pdfConfig['floatAngularAcc']:
        from ROOT import RooArgSet
        initAccPars  = RooArgSet( filter(lambda par: 'effC' in par.GetName(), fitResult.floatParsInit() ) )
        finalAccPars = RooArgSet( filter(lambda par: 'effC' in par.GetName(), fitResult.floatParsFinal() ) )

        print 'Angular acceptance pull (before_fit - after_fit) / error'
        print ' efficiency moment      calc err hesse err'
        for par in initAccPars:
            parName = par.GetName()
            initVal, finalVal = par.getVal(), finalAccPars.find(parName).getVal()
            initErr, finalErr = par.getError(), finalAccPars.find(parName).getError()
            signf = lambda error: round( (finalVal - initVal) / error, 2 )
            print '%23s  %+.3f  %+.3f'%(parName,signf(initErr),signf(finalErr))

    # more output
    if opts.verbose: 

        print 'P2VV - INFO: Float parameters:'
        RooArgSet( p for p in pdf.getParameters(fitData) if not p.isConstant() ).Print('v')
        print
        # print 'P2VV - INFO: Constant parameters:'
        # RooArgSet( p for p in pdf.getParameters(fitData) if p.isConstant() ).Print('v')
        # print

        # dumpo correlations in one collumn for quick inspection
        from itertools import combinations
        floatParNames = map(lambda par: par.GetName(),  RooArgSet( p for p in pdf.getParameters(fitData) if not p.isConstant() ) )
        for par1, par2 in combinations(floatParNames, 2):
            correlation = fitResult.correlation(par1,par2)
            if not correlation >= maxCorr: continue
            print '%20s %16s %+3f'%(par1, par2, fitResult.correlation(par1,par2) )

# write fit result to a file
if parFileOut and not opts.fit_doNotFit:
    pdfConfig.getParametersFromPdf( pdf,  fitData )
    pdfConfig.writeParametersToFile( filePath = parFileOut, Floating = True if not opts.fit_nllScanMode else None,
                                     FitStatus = ( fitResult.status(), fitResult.minNll(), fitResult.edm() ) )    

    fitResult.SetName( parFileOut.replace('.par','') )
    from ROOT import TFile
    resultFile = TFile.Open( parFileOut.replace('.par','.root'), 'recreate')
    resultFile.cd()
    fitResult.Write()
    resultFile.Close()

#################################################
## Begin plotting ##
####################
import sys
if opts.plot:
    dec = raw_input('P2VV - INFO: Asked to plot. Continue with plotting ? (yes/no):  ')
    if str(dec) not in ['yes','no']:
        dec = raw_input('P2VV - INFO: type either yes/no (last chance): ')
    if   str(dec) == 'yes':
        pass
    else:
        sys.exit( 'P2VV - INFO: Chose not to plot. Goodbye pousth !!')
else:
    sys.exit()

from ROOT import TCanvas, RooAbsData, RooArgSet
from P2VV.RooFitWrappers import SimultaneousPdf
from P2VV.Utilities.Plotting import plot
from P2VV.Load import LHCbStyle
from math import pi

# define nBins
if opts.plot_slices and 'Bs' in opts.weights:
    nBins = 10
elif (not opts.plot_slices) and 'Bs' in opts.weights:
    nBins = 20
elif opts.plot_slices and 'Bd' in opts.weights:
    nBins = 20
elif (not opts.plot_slices) and 'Bd' in opts.weights:
    nBins = 25
else:
    nBins = 25

# define range in y axis
def rangeY( nKpiBin = None ):
    return_range = None
    if opts.weights == 'Bs':
        
        if opts.plot_slices and opts.plot_cpComps:
            if nKpiBin == 1:
                return_range = [ (-15,None), (-5,None), (-4,None) ]
            elif nKpiBin == 2:
                return_range = [ (-40,None), (-15,None), (-10,None) ]
            elif nKpiBin == 3:
                return_range = [ (-10,None), (-10,None), (-10,None) ]
            elif nKpiBin == 4:
                return_range = [ (-4,None), (-4,None), (-4,None) ]

            if opts.kaonSign != 'all' and  opts.runPeriod != '3fb':
                return_range = [ (i[0]/4.,i[1])  for i in return_range]
            elif opts.kaonSign != 'all' or  opts.runPeriod != '3fb':
                return_range = [ (i[0]/2.,i[1])  for i in return_range]
        
        elif opts.kaonSign == 'all' and opts.KpiBin == 'all' and opts.runPeriod == '3fb':
            if opts.plot_cpComps and not opts.plot_LHCbLogo:
                return_range =  [ (-40,120), (-10,100), (-10,100) ]
            if opts.plot_cpComps and opts.plot_LHCbLogo:
                return_range =  [ (-40,120), (-10,120), (-10,120) ]

    elif opts.weights == 'Bd': 
        if opts.plot_slices and opts.plot_cpComps:
            return_range = [ (-750,None), (-200,None), (-200,None) ]
            
            if opts.kaonSign != 'all' and  opts.runPeriod != '3fb':
                return_range = [ (i[0]/4.,i[1])  for i in return_range]
            elif opts.kaonSign != 'all' or  opts.runPeriod != '3fb':
                return_range = [ (i[0]/2.,i[1])  for i in return_range]

        elif opts.kaonSign == 'all' and opts.KpiBin == 'all' and opts.runPeriod == '3fb':
            if opts.plot_cpComps and not opts.plot_LHCbLogo:
                return_range = [ (-2e3,None), (-1e3,10e3), (-1e3,11e3) ] 
            if opts.plot_cpComps and opts.plot_LHCbLogo:
                return_range = [ (-2e3,None), (-1e3,13e3), (-1e3,13e3) ]

    return_range = return_range if return_range else [ (None,None), (None,None), (None,None) ]
    return return_range

# LHCb label
from P2VV.Utilities.Plotting import _P2VVPlotStash
from ROOT import TPaveText, TPad

LHCbText = TPaveText( 0.75, 0.75, 0.95, 0.9, 'BRNDC')
LHCbText.SetName('LHCbLabel')
LHCbText.AddText('LHCb')
LHCbText.SetFillStyle(0)
LHCbText.SetFillColor(0)
LHCbText.SetShadowColor(0)
LHCbText.SetBorderSize(0)
LHCbText.SetTextAlign(12)
LHCbText.SetTextSize(0.072)
_P2VVPlotStash.append(LHCbText)

# make projection dataset to average over data categories
from P2VV.RooFitWrappers import Customizer
projWDataSet = []
if isinstance( pdf, SimultaneousPdf ) or isinstance( pdf, Customizer ):
    if pdf.indexCat().isFundamental() :
        projWDataSet += [ pdf.indexCat() ]
    else :
        projWDataSet += [ cat for cat in pdf.indexCat().inputCatList() ]
projectionDataSet = fitData.reduce( RooArgSet(projWDataSet) )

# plot angular terms
AddPDFs  = []
AddPDFsOpts = []
if opts.plot_cpComps:

    # configure pdf components plotting
    from P2VV.Utilities.Plotting  import PlotAngPdfComponentsToolKit
    from ROOT import kGreen
    angFuncCoefs = RooArgSet( p for p in pdf.getParameters(fitData) if (p.isConstant() and 'sum_coef' in p.GetName()) )      
    
    compPdfIndices = { 'pwave': range(1,7), 'swave':[7], 'spInterf': range(8,11) } if not opts.plot_pWaveComps else \
                     { 'odd':[4,3], 'even':[1,2] ,'swave':[7], 'spInterf': [8,9,10] }
    
    compPlotArgs = dict( LineColors = { 'pwave': 4, 'swave': kGreen + 3, 'spInterf': 2 },
                         LineStyles = { 'pwave': 9, 'swave': 3, 'spInterf': 5 },
                     ) if not opts.plot_pWaveComps else \
                   dict( LineColors = { 'odd': 4, 'even': 4, 'swave': kGreen + 3, 'spInterf': 2 },
                         LineStyles = { 'odd': 3, 'even': 9, 'swave': 6, 'spInterf': 7 },
                   )
    
    CpCompsTool = PlotAngPdfComponentsToolKit( pdf, fitData, compPdfIndices, angFuncCoefs, **compPlotArgs )

    # prepare plotting opts for the cp components
    if not opts.plot_slices:
        fracs = CpCompsTool.getFracs( KaonSigns, periods, 'all')
        print 'P2VV - INFO: Using the folowing normalization fractions for component pdfs %s, sum: %s'%( {k:round(v,4) for k,v in fracs.iteritems()}, sum(fracs.values()) )
    else: 
        fracs = { c : 0. for c in compPdfIndices.keys() }

    for key, comp_pdf in CpCompsTool['outPdfs'].iteritems():
        AddPDFs     += [ comp_pdf ]
        AddPDFsOpts += [ { 'Normalization' : ( fracs[key], 1), 
                           'ProjWData' : projectionDataSet, 
                           'LineColor' : CpCompsTool['colors'][key], 
                           'LineStyle' : CpCompsTool['styles'][key], 
                           'LineWidth' : 1 } ]

    assert len(AddPDFs) == len(AddPDFsOpts), 'P2VV - ERROR: Number of pdf components does not match with number of options provided.'

# plotting loop over categories
canvs_stash = []
for KpiBin in range( 1, ws['KpiMassCat'].numTypes()+1 ): # slices plotting loop

    Cut, Slice = None, None
    if opts.plot_slices:
        Cut = 'KpiMassCat == KpiMassCat::bin%s'%KpiBin
        Slice = (ws['KpiMassCat'],'bin%s'%KpiBin)
        
        if opts.plot_cpComps:
            fracs = CpCompsTool.getFracs( KaonSigns, periods, 'bin%s'%KpiBin)
            print 'P2VV - INFO: Using the folowing normalization fractions for component pdfs %s, sum: %s'%( {k:round(v,4) for k,v in fracs.iteritems()}, sum(fracs.values()) )
            for comp_pdf, options in zip( AddPDFs, AddPDFsOpts ):
                key = comp_pdf.GetName().split('__')[-1]
                arg = ( fracs[key], 1 ) 
                options.update( {'Slice':Slice} )
                options.update( {'Normalization': arg} )

    # prepare canvas
    cn = 'decay angles %s'%( 'bin%s'%KpiBin if opts.plot_slices else '' )
    c = TCanvas( cn, cn )
    c.Divide(2,2)
    
    # main ploting loop
    for canvas, obs, yTitle, yScale in zip(
            [ c.cd(i) for i in range(1,4) ],
            pdfBuild['obsSetP2VV'],
            [ 'Candidates / %s'%(round(2./nBins,2)), 'Candidates / %s'%(round(2./nBins,2)), 'Candidates / %s [rad^{-1}]'%(round(2*pi / nBins,2)) ], 
            rangeY( nKpiBin = KpiBin if ( opts.plot_slices and opts.plot_cpComps ) else None )
           ):

        DataOpts = { 'DataError'  : RooAbsData.SumW2  if fitData.isWeighted() else 0,
                     'MarkerSize' : 0.5,
                     'LineWidth'  : 1 }
        PdfOpts  = { 'ProjWData'  : projectionDataSet if projWDataSet else None, 
                     'LineWidth'  : 1,
                     'LineColor'  : 1}
        
        if Cut and Slice:
            DataOpts.update( {'Cut':Cut} )
            PdfOpts.update( {'Slice':Slice} )

        plot(canvas, obs, data = fitData, pdf = pdf, yTitle = yTitle, yScale = yScale, 
             plotResidHist = opts.plot_noPulls,
             frameOpts     = { 'Bins' : nBins,  'Title' : '' },
             dataOpts      = DataOpts,
             pdfOpts       = PdfOpts,
             addPDFs       = AddPDFs,
             addPDFsOpts   = AddPDFsOpts

             #yTitleSize = 0.12,  
             #yTitleOffset = 0.6, 
             #xTitleSize = 0.12,

             # yLabelSize = 0.12,  
             # yLabelOffset = 0.6, 
             # xLabelSize = 0.12,
         )

        # lhcb logo
        if all( map(lambda o: type(o)==TPad, canvas.GetListOfPrimitives()) ):
            canvas.GetListOfPrimitives()[0].cd()
        if opts.plot_LHCbLogo:
            LHCbText.Draw()

        canvas.Update()
        
        # print canvas
        plot_file_name = '%s%s%s'%( parFileOut.split('.')[0], 
                                    '_CpComp%s'%('_%s'%opts.plot_canvSuffix if opts.plot_canvSuffix else '') 
                                    if opts.plot_cpComps else '',
                                    '_bin%s_slice'%KpiBin if opts.plot_slices else '')
        if opts.plot_splitCanv:
            canvas.Print( 'canv_%s_%s.pdf'%(obs.GetName(), plot_file_name ) )

    # legend
    if drawLegend:
        labels = dict( pwave = 'p-wave', swave ='s-wave' , spInterf = 's-p waves Interference',
                       even = 'p-wave even', odd = 'p-wave odd + p-p wave Interference', total = 'total' )

        from ROOT import TLegend
        legend = TLegend( 0.1, 0.85, 0.75, 0.25)
        legend.SetName('legend')
        legend.SetFillStyle(0)
        legend.SetFillColor(0)
        legend.SetShadowColor(0)
        legend.SetBorderSize(0)
        legend.SetTextAlign(12)
        legend.SetTextSize(0.05)

        style_to_name = { str(value) : key for key, value in compPlotArgs['LineStyles'].items() + [ ('total',1)] }

        primitives = canvas.GetListOfPrimitives()[0].GetListOfPrimitives() if opts.plot_slices else canvas.GetListOfPrimitives()
        curves = filter( lambda prim: 'pdf' in prim.GetName().lower(), primitives )

        for curve in curves:
            curve_style = str(curve.GetLineStyle())
            curve_label = labels[style_to_name[curve_style]]
            curve.SetFillColor(0)
            curve.SetMarkerSize(0.001)
            legend.AddEntry(curve, curve_label)

        c.cd(4)
        legend.Draw()
        canvs_stash += [legend]

    c.Print( 'canv_%s.pdf'%(plot_file_name) )
    canvs_stash += [c]

    if not opts.plot_slices: break
