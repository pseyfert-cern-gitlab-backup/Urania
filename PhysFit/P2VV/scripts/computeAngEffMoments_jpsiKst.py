#!/usr/bin/env python

import argparse
parser = argparse.ArgumentParser()
parser.add_argument( '--runPeriod', type=str, default = None )
parser.add_argument( '--kaonSign',  type=str, default = None )
parser.add_argument( '--KpiBin',    type=str, default = None )
parser.add_argument( '--chanell',   type=str, default = 'Bd' )

parser.add_argument( '--data-path',    type=str, default = None )
parser.add_argument( '--data-name',    type=str, default = None )
parser.add_argument( '--outMomsSufix', default = None )

parser.add_argument( '--override-fitAcc-with' )
parser.add_argument( '--override-constr-with' )

parser.add_argument( '--readMoms',         action = 'store_true'  )
parser.add_argument( '--readMoms-path',    type=str, default = '' )
parser.add_argument( '--fitData',          action = 'store_true'  )
parser.add_argument( '--noPlots',          action = 'store_false' )
parser.add_argument( '--plotFast',         action = 'store_true'  )
parser.add_argument( '--plotPeriods',      action = 'store_true'  )
parser.add_argument( '--mergePeriods',     action = 'store_true'  )
parser.add_argument( '--doMapping',        action = 'store_true'  )
options = parser.parse_args()

# sanity checks of the parced options
assert options.chanell,  'P2VV - ERROR: Specidy chanell [Bd/Bs].'
assert options.kaonSign in ['pos','neg'], 'P2VV - ERROR: Kaon sign must be specified as neg or pos.'
assert options.KpiBin and ( 'bin' in options.KpiBin or 'all' in options.KpiBin),  'P2VV - ERROR: Kpi bin  must be specified bin{1,4} / all.'
assert options.runPeriod or options.mergePeriods, 'P2VV - ERROR: Run period must be specified as 2011/2012.'

if options.readMoms: assert options.readMoms_path, 'P2VV - ERROR: Provide path to read moments from (--readMoms-path)'
if options.readMoms_path: options.readMoms = True
if options.mergePeriods: options.runPeriod = None

# Dump some important options
job_id_str = '_%s_%s_%s_'%(options.runPeriod, options.KpiBin, str(options.kaonSign).replace('+','p').replace('-','m') )
print '\nParsed options:'
print 30*'-'
print 'Merge periods: %s'%options.mergePeriods
print 'Run Period   : %s'%options.runPeriod
print 'Kaon Sign    : %s'%options.kaonSign
print 'Kpi Bin      : %s'%options.KpiBin
print 'Read Moments : %s, from: %s'%(options.readMoms,options.readMoms_path)
print 'Input data   : %s'%options.data_path
print '\n'

###########################################################################################################################################
## set script parameters ##
###########################

# job parameters
MCProd           = 'Sim08' if options.mergePeriods else 'Sim08_%s'%options.runPeriod 
mergePeriods     = options.mergePeriods
kaonSign         = options.kaonSign
KpiMassBinBounds = [ 896 - 70, 896 - 35, 896, 896 + 35, 896 + 70 ]
KpiMassBin       = options.KpiBin
readMoms         = options.readMoms
readMomsPath     = options.readMoms_path
KpiMassRange     = [ KpiMassBinBounds[int(options.KpiBin[-1])-1], KpiMassBinBounds[int(options.KpiBin[-1])] ] if not options.KpiBin == 'all' \
                   else [ KpiMassBinBounds[0], KpiMassBinBounds[-1] ]
fitData       = options.fitData  # this is to  check if the acc. is really positive
numCPU        = 4
makePlots     = options.noPlots
plotFast      = options.plotFast
plot2DEff     = True if makePlots else False
plotEffProj   = True if ( not plotFast and makePlots ) else False
plotAccDivide = False # Divide data 2D histograms by generated pdf
plotPeriods   = True if options.plotPeriods and (not plotFast) and makePlots else False 
trueAngles    = False
transAngles   = False
incSWave      = False 
normPdf       = True
trigger       = ''
addInvPdf     = False
addAccWeight  = False
weightVar     = '' # 'wKin' # 'sWeights_ipatia'
doSelection   = False
customSel     = False
parFileIn     = '' # '../it6/fitPars.par'
outMomsSufix = '_reweighted_%s'%options.outMomsSufix if options.outMomsSufix else ''

momentsFile = '%s_%s_%sKaons_%s%s'   % ( MCProd, 'trans' if transAngles else 'hel', kaonSign, KpiMassBin, outMomsSufix )
plotsFile   = '%s_%s_%sKaons_%s%s'   % ( MCProd, 'trans' if transAngles else 'hel', kaonSign, KpiMassBin, outMomsSufix )
dataSetFile = '' # '%s_%s_UB_UT_%s_BkgCat050_KK30.root' % ( MCProd, 'trans' if transAngles else 'hel', tResModel if tResModel else 'trueTime' )

# input dataset
inputPath = '/project/bfys/vsyropou/data/Bs2JpsiKst/MC/%s_monte_carlo/'%options.chanell
if not options.data_path:
    nTupleName = 'Bs2JpsiKst'
    nTupleFile = inputPath + 'P2VVDataSet_Bs2JpsiKst_%s_Sim08_Reco14_%sKaons_%s_%s_KpiBin_131214.root'\
                 %(MCProd.split('_')[1] if not mergePeriods else '', kaonSign, KpiMassRange[0], KpiMassRange[1] )
else:
    nTupleFile = options.data_path
    nTupleName = options.data_name

# transversity amplitudes
from P2VV.Utilities.MCReweighting import parValuesMcSim08_jpsiKst as mcPars
ampsToUse = [ 'A0', 'Apar', 'Aperp', 'AS' ]
A0Mag2Val    = mcPars['A0Mag2']
AperpMag2Val = mcPars['AperpMag2']
AparMag2Val  = mcPars['AparMag2']

A0PhVal    = mcPars['A0Phase']
AperpPhVal = mcPars['AperpPhase']
AparPhVal  = mcPars['AparPhase']
    
ASPhase = mcPars['ASPhase']
f_S     = mcPars['f_S']
C_SP    = mcPars['C_SP']

###########################################################################################################################################
## end job parametersation ##
#############################

KKMassStates = dict( [ ('bin%d' % i, i) for i in range(6) ] )
if incSWave :
    SWaveAmps = dict(  f_S = dict(  bin0 = 0.445  if MCProd == 'real' else 0.
                                  , bin1 = 0.064  if MCProd == 'real' else 0.
                                  , bin2 = 0.0087 if MCProd == 'real' else 0.
                                  , bin3 = 0.0089 if MCProd == 'real' else 0.
                                  , bin4 = 0.045  if MCProd == 'real' else 0.
                                  , bin5 = 0.210  if MCProd == 'real' else 0.
                                 )
                     , ASOddPhase = dict(  bin0 = +0.80 if MCProd == 'real' else 0.
                                         , bin1 = +2.32 if MCProd == 'real' else 0.
                                         , bin2 = +0.46 if MCProd == 'real' else 0.
                                         , bin3 = -0.36 if MCProd == 'real' else 0.
                                         , bin4 = -0.68 if MCProd == 'real' else 0.
                                         , bin5 = -0.82 if MCProd == 'real' else 0.
                                        )
                     , C_SP = dict(  bin0 = 0.966 if MCProd == 'real' else 1.
                                   , bin1 = 0.956 if MCProd == 'real' else 1.
                                   , bin2 = 0.926 if MCProd == 'real' else 1.
                                   , bin3 = 0.926 if MCProd == 'real' else 1.
                                   , bin4 = 0.956 if MCProd == 'real' else 1.
                                   , bin5 = 0.966 if MCProd == 'real' else 1.
                                  )
                    )
else :
    SWaveAmps = { }

# plot options
if transAngles : angleNames = ( 'cos(#psi_{tr})',  'cos(#theta_{tr})',  '#phi_{tr}' )
else           : angleNames = ( 'cos(#theta_{K})', 'cos(#theta_{#mu})', '#phi_{h}'  )
numBins         = ( 20, 20, 20 )
lineWidth       = 2
markStyle       = 8
markSize        = 0.4

###########################################################################################################################################
## create variables and read data ##
####################################

# import RooFit wrappers
from P2VV.Load import RooFitOutput

# workspace
from P2VV.RooFitWrappers import RooObject
ws = RooObject(workspace = 'ws').ws()

# angular functions
if transAngles :
    from P2VV.Parameterizations.AngularFunctions import JpsiKstTransversityAngles as AngleFuncs
    angleFuncs = AngleFuncs( cpsi = 'trcospsi', ctheta = 'trcostheta', phi = 'trphi' )
else :
    from P2VV.Parameterizations.AngularFunctions import JpsiKstHelicityAngles as AngleFuncs
    angleFuncs = AngleFuncs( cpsi = 'helcosthetaK', ctheta = 'helcosthetaL', phi = 'helphi' )
    
# variables in PDF
from P2VV.RooFitWrappers import RealVar
angles    = [ angleFuncs.angles['cpsi'], angleFuncs.angles['ctheta'], angleFuncs.angles['phi'] ]
if weightVar :
    weight = RealVar( weightVar, Title = 'Signal weight', Observable = True, Value = 1. )

obsSet = angles
if weightVar : obsSet.append(weight)

KpiMass = RealVar('mdau2', Title = 'KpiMass', MinMax = KpiMassRange)
obsSet += [KpiMass]

# read ntuple
cuts = ''
if doSelection : # just in case you need it
    cuts = '' # trackChiSqCuts + ' && ' + massCuts + ' && ' + timeCuts + ' && ' + tagCuts

readDataOpts = { }
if cuts      : readDataOpts['ntupleCuts'] = cuts
if weightVar : readDataOpts['WeightVar']  = ( weightVar, True )

from P2VV.Utilities.DataHandling import readData
if not mergePeriods or options.data_path:
    data = readData( nTupleFile, dataSetName = nTupleName, NTuple = False, observables = obsSet, **readDataOpts )
else:
    readDataOpts['ImportIntoWS'] = False
    nTupleFiles = [nTupleFile.replace('__','_201%s_'%p) for p in [1,2]]    
    dataSets = [ readData( File, dataSetName = nTupleName, NTuple = False, observables = obsSet, **readDataOpts ) for File in nTupleFiles ]
    dataSets[0].append( dataSets[1] )
    del dataSets[1]    
    data = dataSets[0]

###########################################################################################################################################
## build the B_s -> J/psi phi signal time, angular and tagging PDF ##
#####################################################################

if normPdf :
    # transversity amplitudes
    from P2VV.Parameterizations.DecayAmplitudes import JpsiVPolarSWaveFrac_AmplitudeSet as Amplitudes
    amplitudes = Amplitudes(  A0Mag2 = A0Mag2Val, 
                              AperpMag2 = AperpMag2Val,
                              AparPhase = AparPhVal - A0PhVal,
                              AperpPhase = AperpPhVal - A0PhVal,
                              f_S = 0., 
                              ASPhase = 0., 
                              C_SP = 1.,
                              ASParameterization = ''
                           )

# Flip sing in Im(AiAj), This is important!!
if kaonSign=='neg':
    from P2VV.RooFitWrappers import ConstVar
    angFuncSumCoefs = {}

    invertSign = lambda k0, k1: (k0=='Aperp' or k1 =='Aperp') and k0 != k1

    for key in [('A0', 'A0'), ('Aperp', 'Aperp'), ('Apar', 'Apar'),
                ('A0', 'Apar') , ('A0', 'Aperp'), ('Apar', 'Aperp'),
                ('A0', 'AS') , ('Apar', 'AS'), ('Aperp', 'AS'), ('AS', 'AS')
            ]:

        angFuncSumCoefs[key] = ConstVar( Name = 'minus',  Value = -1 ) if invertSign(key[0],key[1]) else ConstVar( Name = 'plus',  Value = +1 )

# build angular terms from PY combinations 
from P2VV.Parameterizations.AngularPDFs import Amplitudes_AngularPdfTerms
pdfTerms = Amplitudes_AngularPdfTerms( AmpNames = ampsToUse, 
                                       Amplitudes = amplitudes, 
                                       AngFunctions = angleFuncs.functions,
                                       AngTermsSumCoef = angFuncSumCoefs if kaonSign=='neg' else ''
                                       )


# build pdf
pdf = pdfTerms.buildSumPdf('AngularPDF')

intSet  = [ ]
normSet = angleFuncs.angles.values()

if parFileIn :
    # read parameter values from file
    from P2VV.Parameterizations.FullPDFs import PdfConfiguration
    pdfConfig = PdfConfiguration()
    pdfConfig.readParametersFromFile( filePath = parFileIn )
    pdfConfig.setParametersInPdf(pdf)

# print PDF, data, variables and parameters
print '\nData set:'
data.Print()

if normPdf :
    print '\nPDF:'
    pdf.Print()
    print '\nIntegration set for PDF:'
    for var in intSet : print var.GetName(),
    print '\n\nNormalization set for PDF:'
    for var in normSet : print var.GetName(),
    print '\nVariables in PDF:'
    for var in pdf.getObservables(data) : var.Print()
    print '\nParameters in PDF:'
    for par in pdf.getParameters(data) : par.Print()
    print

else :
    print '\nUsing uniform angular PDF'
    print

if addInvPdf and normPdf:
    print 'adding inverse pdf value weights to dataset'
    from ROOT import RooArgSet, RooArgList, RooFormulaVar, RooConstVar, TFile
    rooIntSet  = RooArgSet( var._var for var in intSet  )
    rooNormSet = RooArgSet( var._var for var in normSet )

    pdfInt = pdf.createIntegral( rooIntSet, rooNormSet )
    nEvents = RooConstVar( 'nEvents', 'Number of events', data.sumEntries() )
    effWeightList = RooArgList( nEvents, pdfInt )
    effWeight = RooFormulaVar( 'effWeight', 'Efficiency weight', '1./@0/@1', effWeightList )

    data.addColumn(effWeight)

    invPdf_file = TFile.Open('effWeight_real_data_%s_%s.root'%(kaonSign,KpiMassBin),'recreate')
    data.Write()
    invPdf_file.Close()    

    assert False

###########################################################################################################################################
## compute angular efficiency moments ##
########################################

# moments builder with angular functions from physics PDF
from P2VV.Utilities.DataMoments import RealMomentsBuilder, normalizeMoments
if normPdf :
    from P2VV.RooFitWrappers import RealEffMoment
    physMoments = RealMomentsBuilder( Moments = ( RealEffMoment( Name = func.GetName(), BasisFunc = func,Norm = 1., PDF = pdf
                                                                , IntSet = intSet, NormSet = normSet )\
                                                  for complexFunc in angleFuncs.functions.itervalues() for func in complexFunc if func
                                                )
                                    )

else :
    from P2VV.RooFitWrappers import RealMoment
    physMoments = RealMomentsBuilder( Moments = ( RealMoment( Name = func.GetName(), BasisFunc = func, Norm = 1. )\
                                                  for complexFunc in angleFuncs.functions.itervalues() for func in complexFunc if func
                                                )
                                    )
physMoments.initCovariances()

# moments builder with angular basis functions
from P2VV.Utilities.DataMoments import angularMomentIndices
indices_label = '_'.join([KpiMassBin, kaonSign]) + '%s'%( '_%s'%options.runPeriod if not (mergePeriods or '3fb' in options.runPeriod) else '')
indicesConf   = angularMomentIndices(indices_label, angleFuncs, 'jpsiKst')
indices       = indicesConf['indices']
constrainAcc  = indicesConf['constrain']
constrainType = 'Integral'
fitAcceptance = indicesConf['fit']
constEffCoefs = False if fitAcceptance else True
print 'P2VV - INFO: Acceptance configuration: %s. Constrain: %s. Fit: %s. '%(indices_label,constrainAcc,fitAcceptance)

# compute moments from data set
if not readMoms:
    
    basisMoments = RealMomentsBuilder()
    if normPdf :        basisMoments.appendPYList( angleFuncs.angles, indices, PDF = pdf, IntSet = intSet, NormSet = normSet )
    else :
        basisMoments.appendPYList( angleFuncs.angles, indices )

    basisMoments.initCovariances()

    from math import sqrt, pi
    PDFInt = 1. if normPdf else 8. * pi

    physMoments.compute(data)
    basisMoments.compute(data)

    print 'P2VV - INFO: Dumping normalization weights:' 
    physMoments.Print(  Scale = PDFInt / 16. / sqrt(pi)                         )
    physMoments.write(  momentsFile + '_Phys',  Scale = PDFInt / 16. / sqrt(pi) )
    normalizeMoments( momentsFile + '_Phys', momentsFile + '_Phys_norm', printMoms = False )
 
    print 'P2VV - INFO: Dumping basis moments BEFORE constraining - fiting:' 
    basisMoments.Print( Scale = PDFInt /  2. / sqrt(pi)         )
    basisMoments.write( momentsFile + '_Basis', Scale = PDFInt  )

###########################################################################################################################################
## Constrained and / or fit acceptance, multiply pdf wit it and write basis moments ##
######################################################################################

# But first make some plots before multipling with the acceptance
if plotAccDivide:
    from ROOT import TCanvas
    canvKL_div   = TCanvas('cosThK_cosThL_div', 'contKL_div',   900,600)
    canvKphi_div = TCanvas('cosThK_phi_div',    'contKphi_div', 900,600)
    canvLphi_div = TCanvas('cosThL_phi_div',    'contLphi_div', 900,600)
    
    from P2VV.Utilities.Plotting import plot2DacceptanceDivide
    canvList = plot2DacceptanceDivide( [canvKL_div,canvKphi_div,canvLphi_div], pdf, data, nbins = 20)

if makePlots and normPdf:
    from P2VV.Load import LHCbStyle
    from P2VV.Utilities.Plotting import plot
    from ROOT import TCanvas, kBlue, kRed, kGreen, kBlack

    # plot pdf on data with and w/o eff 
    timeAnglesCanv = TCanvas( 'timeAnglesCanv', 'Lifetime and Decay Angles' )
    for ( pad, obs, nBins, plotTitle, xTitle )\
            in zip(  timeAnglesCanv.pads( 2, 2 )
                   , obsSet[ 0 : 3 ]
                   , numBins
                   , [ var.GetTitle() for var in obsSet[ 0 : 3 ] ]
                   , angleNames
                  ) :
        plot(  pad, obs, data, None if plotFast else pdf , xTitle = xTitle
             , frameOpts   = dict( Bins = nBins, Title = plotTitle                )
             , dataOpts    = dict( MarkerStyle = markStyle, MarkerSize = markSize )
             , pdfOpts     = None if plotFast else dict( LineColor = kBlue, LineWidth = lineWidth       )
            )

# multiply PDF with angular efficiency and/or fit it
comonAccArgs = dict ( ConstCoefs = constEffCoefs, ConstainAcc = constrainAcc, ConstainType = constrainType )
if readMoms:
    basisMoments = RealMomentsBuilder()
    basisMoments.appendPYList( angleFuncs.angles, indices, PDF = pdf, IntSet = intSet, NormSet = normSet )

    # use this to check if the written moments file are indeed positive
    #print 'P2VV - INFO: Reading moments from file %s'%(readMomsPath + momentsFile + '_Basis_constr')
    print 'P2VV - INFO: Reading moments from file %s'%(readMomsPath )
    #basisMoments.read(readMomsPath + momentsFile + '_Basis_constr')
    basisMoments.read(readMomsPath)
    basisMoments.Print()

    # print 'P2VV - INFO: Multipliyng pdf with %s'%(readMomsPath + momentsFile + '_Basis_constr')
    print 'P2VV - INFO: Multipliyng pdf with %s'%(readMomsPath)
    pdf      = basisMoments.multiplyPDFWithEff( pdf, **comonAccArgs )
    # print 'P2VV - INFO: Building pdf terms from basis moments: %s'%(readMomsPath + momentsFile + '_Basis_constr')
    print 'P2VV - INFO: Building pdf terms from basis moments: %s'%(readMomsPath )
    effTerms = basisMoments.buildPDFTerms() #Scale = 1. /  2. / sqrt(pi) )
    effFunc  = effTerms.buildAddition('effFunc')

else: 
    print 'P2VV - INFO: Multipliyng pdf with basis moments: %s'%(momentsFile + '_Basis')
    basisMoments.Print( Scale = PDFInt /  2. / sqrt(pi) )
    pdf = basisMoments.multiplyPDFWithEff( pdf, **comonAccArgs )

    # fit and constrain acceptance
    if fitAcceptance:
        assert not constEffCoefs, 'P2VV - WARNING: efficiency parameters are ConstVars check flag configuration again.'
        for par in pdf.getParameters(data):
            if 'effC' in par.GetName():
                par.setConstant(0)
            else: par.setConstant()

        print '\nP2VV - INFO: Fitting acceptance.'
        accFitResult = pdf.fitTo(data, Minimizer = 'Minuit2', NumCPU = numCPU, Offset = True, Optimize = 2, Strategy = 0, SumW2Error=False, Save = True)
        from P2VV.Utilities.DataMoments import writeConstrainedMoms
        
        # dump fitted acceptance and write
        print '\nP2VV - INFO: Dumping and writing fitted and constrained basis moments. (constr/fit flags) = (%s, %s):'%(constrainAcc,fitAcceptance)
        writeConstrainedMoms(momentsFile + '_Basis_constr', basisMoments, accFitResult, PrintMoments = True )
        
        # build acceptance function and set the fitted acc parameters to the acc function
        print 'P2VV - INFO: Building pdf terms from basis moments and setting the fitted acceptance parameters to the eff. function.'
        effTerms = basisMoments.buildPDFTerms()
        effFunc = effTerms.buildAddition('effFunc')

        for coef in filter(lambda var: 'C_p2vvab' in var.GetName(), ws.allVars()):
            name = 'effC_' + ''.join( coef.GetName().split('_')[2][i] for i in [0,2,3] )
            val = accFitResult.floatParsFinal().find(name).getVal()
            coef.setVal(val)

    # constrain but do not fit the acceptance and write
    elif constrainAcc and not fitAcceptance:
        print 'P2VV - INFO: Building constrained pdf terms from basis moments: (constr/fit flags) = (%s, %s):'%(constrainAcc,fitAcceptance)
        effTerms = basisMoments.buildPDFTerms()
        effFunc = effTerms.buildAddition('effFunc')
        basisMoments.write( momentsFile + '_Basis_constr', Scale = PDFInt  )
        basisMoments.Print() #Scale = PDFInt /  2. / sqrt(pi) )

    # no special treatment of the acceptance, just write the output
    else:
        print 'P2VV - INFO: Building pdf terms from basis moments: (constr/fit flags) = (%s, %s):'%(constrainAcc,fitAcceptance)
        effTerms = basisMoments.buildPDFTerms()
        effFunc = effTerms.buildAddition('effFunc')
        basisMoments.write( momentsFile + '_Basis_constr', Scale = PDFInt  )
        basisMoments.Print( Scale = PDFInt /  2. / sqrt(pi) )

# generate data for mapping
if options.doMapping:
    print 'P2VV - INFO: Generating data for mapping.'
    from ROOT import TFile, RooArgSet

    genData = pdf.generate(RooArgSet(*angles), 1000000 )
    
    f = TFile.Open('mapping_dataSet_%s_%s_%s.root'%(MCProd,kaonSign,KpiMassBin),'recreate')
    genData.Write()
    f.Close()

    import sys
    sys.exit()

###########################################################################################################################################
## # continue with plotting: plot  pdf with eff on data ##
##########################################################
if makePlots and normPdf :
    # plot efficiency PDF
    from P2VV.Utilities.Plotting import _P2VVPlotStash
    global _P2VVPlotStash
    for it in range(3) :
        pdf.plotOn( _P2VVPlotStash[ -it - 1 ], Name = 'effPdf', LineColor = kRed, LineWidth = lineWidth )
        timeAnglesCanv.cd( 3 - it )
        _P2VVPlotStash[ -it - 1 ].Draw()
    timeAnglesCanv.Update()

# plot 2D projections of the efficiency function
if makePlots and plot2DEff:
    from P2VV.Utilities.Plotting import plot2DefficiencyFunc
    
    from ROOT import TCanvas
    canvKL   = TCanvas('cosThK_cosThL', 'contKL',   900,600)
    canvKphi = TCanvas('cosThK_phi',    'contKphi', 900,600)
    canvLphi = TCanvas('cosThL_phi',    'contLphi', 900,600)

    plot2DefficiencyFunc( [canvKL, canvKphi, canvLphi], effFunc, angles, \
                          nbins = 20 if plotAccDivide else 100, surfStyle = 'Lego2' if plotAccDivide else 'Surf4' )

    for canv in [canvKL, canvKphi, canvLphi]:
        canv.Print('canv_%s_%s_%s_%sKaons_%s.pdf'%( canv.GetName(),MCProd, 'trans' if transAngles else 'hel', kaonSign, KpiMassBin ))

# plot efficiency projections
if makePlots and normPdf and not plotFast:
    from ROOT import RooArgSet
    from math import pi
    ctkSet = RooArgSet( angles[1], angles[2] )
    ctlSet = RooArgSet( angles[0], angles[2] )
    phiSet = RooArgSet( angles[0], angles[1] )
    effFuncCtk = effFunc.createIntegral( ctkSet, RooArgSet() )
    effFuncCtl = effFunc.createIntegral( ctlSet, RooArgSet() )
    effFuncPhi = effFunc.createIntegral( phiSet, RooArgSet() )
    effCanv = TCanvas( 'effCanv', 'Efficiency' )

    for ( pad, obs, func, norm, xTitle, yScale, xScale )\
            in zip(  effCanv.pads( 2, 2 )
                   , obsSet[ 0 : 3 ]
                   , [ effFuncCtk, effFuncCtl, effFuncPhi ]
                   , [ 1. / 4. / pi, 1. / 4. / pi, 1. / 4. ]
                   , angleNames
                     , [ ( -1, 2 ), ( -1., 2. ), ( -1., 2. ) ] 
                     , [ ( -1, 1 ),    ( -1, 1 ),    ( -pi, pi )  ] 
                  ) :
        plot(  pad, obs, None, func, addPDFs = [ effFunc ]
             , frameOpts    = dict( Range = (xScale[0],xScale[1]) )
             #, yScale      = yScale
             , pdfOpts     = dict( LineColor = kBlue, LineWidth = 2, Normalization = norm )
             , addPDFsOpts = [ dict( LineColor = kRed,  LineWidth = 2 ) ]
            ) 

# draw a tag on the canvas
if makePlots and normPdf and not plotFast:
    from ROOT import TPaveText
    tag = TPaveText(.05,.1,.95,.8, 'BRNDC');
    tag.SetFillColor(0)
    tag.AddText('%s_%s_%sKaons_%s' % ( MCProd, 'trans' if transAngles else 'hel', kaonSign, KpiMassBin ) )
    timeAnglesCanv.cd(4)
    tag.Draw()
    effCanv.cd(4)
    tag.Draw()

    # print canvases to file
    effCanv.Print('canv_%s_%s_%s_%sKaons_%s.pdf'%( effCanv.GetName(),MCProd, 'trans' if transAngles else 'hel', kaonSign, KpiMassBin ))
if makePlots:timeAnglesCanv.Print('canv_%s_%s_%s_%sKaons_%s.pdf'%( timeAnglesCanv.GetName(),MCProd, 'trans' if transAngles else 'hel', kaonSign, KpiMassBin ))

# superimpose data periods (remove this soon)
if makePlots and  plotPeriods and '2011' in MCProd:
    # if '2011' in MCProd:
    otherDataFile = inputPath + 'P2VVDataSet_Bs2JpsiKst_2012_Sim08_Reco14_%sKaons_%s_%s_KpiBin_291014.root'%( kaonSign, KpiMassRange[0], KpiMassRange[1] )
    otherMomsFile = 'Sim08_%s_%s_%sKaons_%s_%sKpiRange' % ( 2012, 'trans' if transAngles else 'hel', kaonSign, KpiMassRange[0],KpiMassRange[1] )
    
    from ROOT import TFile
    otherData = TFile.Open(otherDataFile).Get(nTupleName)
    norm = float(data.sumEntries()) / float(otherData.sumEntries()) 

    canvPer = TCanvas('periods','periods')
    for ( pad, obs, nBins, plotTitle, xTitle )\
            in zip(  canvPer.pads( 2, 2 )
                   , obsSet[ 0 : 3 ]
                   , numBins
                   , [ var.GetTitle() for var in obsSet[ 0 : 3 ] ]
                   , angleNames
                  ) :
        plot(  pad, obs, data, None, xTitle = xTitle
             , frameOpts   = dict( Bins = nBins, Title = plotTitle, Name = obs.GetName() + '_per' )
             , dataOpts    = dict( MarkerStyle = markStyle, MarkerSize = markSize )
            )

    from P2VV import RooFitDecorators
    for it in range(3) :
        otherData.plotOn(_P2VVPlotStash[ -it - 1 ], MarkerColor = kRed, MarkerSize = 0.5, Rescale = norm )
        canvPer.cd( 3 - it )
        _P2VVPlotStash[ -it - 1 ].Draw()
    canvPer.Update()
    canvPer.Print('canv_%s_%s_%s_%sKaons_%s_per.pdf'%( canv.GetName(),MCProd, 'trans' if transAngles else 'hel', kaonSign, KpiMassBin ))

###########################################################################################################################################
## fit data to check biases in translation  ##
##############################################
if fitData:
    for par in pdf.getParameters(data):
        if 'effC' in par.GetName() or par.GetName() == 'A0Phase':
            par.setConstant()
        else: 
            par.setConstant(0)
    pdf.fitTo(data, Minimizer = 'Minuit2', NumCPU = numCPU, Offset = True, Optimize = 2, Strategy = 0, SumW2Error=data.isWeighted())
    compare = dict( A0Mag2     = A0Mag2Val,
                    AperpMag2  = AperpMag2Val,
                    AparPhase  = AparPhVal,
                    AperpPhase = AperpPhVal)
    _diff = lambda name: ws[name].getVal() - compare[name]
    _pull = lambda name: _diff(name) / ws[name].getError()
    print 'grep_hook_Fit' + job_id_str
    print 'grep_hook_Fit' + job_id_str
    for parName in compare.keys():
        print '%23s : %4f  (%2f)'%('grep_hook_Fit' + job_id_str + parName,_diff(parName),_pull(parName))

###########################################################################################################################################
## translate c_ijk to xi_nwrite data set to file ##
###################################################
if not readMoms:
    angFuncNames = [ 
        'Re_ang_A0_A0',
        'Re_ang_Aperp_Aperp',
        'Re_ang_Apar_Apar',
        'Re_ang_AS_AS',     
        'Re_ang_A0_Apar',   
        'Im_ang_A0_Aperp',  
        'Im_ang_Apar_Aperp',
        'Re_ang_A0_AS',     
        'Re_ang_Apar_AS',   
        'Im_ang_Aperp_AS',  
    ]
    
    from ROOT import RooP2VVAngleBasis, RooArgSet
    angFuncConponents      = lambda angFuncName: filter( lambda c: isinstance(c,RooP2VVAngleBasis), ws[angFuncName].getComponents() ) 
    angFuncCompIntegral    = lambda angFunc: angFunc.createIntegral( RooArgSet(*angles), RooArgSet()).getVal()
    # angFuncCompIntegral    = lambda angFunc: angFunc.createProjection( RooArgSet([a._var for a in angles]), RooArgSet([a._var for a in angles]) ).getVal()
    angFuncCompslIntegrals = lambda angFuncName: [ angFuncCompIntegral(subInt) for subInt in angFuncConponents(angFuncName) ]
    angFuncIntegral        = lambda angFuncName: sum(angFuncCompslIntegrals(angFuncName))
    
    norm  = physMoments.coefficients()['Re_ang_A0_A0'][0] 
    xi    = lambda name: round( physMoments.coefficients()[name][0] / norm, 4 )
    
    my_norm =  angFuncIntegral('Re_ang_A0_A0')
    my_xi = lambda name: round( angFuncIntegral(name) / my_norm, 4 )
    
    xi_er = lambda name: round( physMoments.coefficients()[name][1] / norm, 4 )
    sign  = lambda name: round( (my_xi(name) - xi(name)) / xi_er(name) , 2 )
    
    print '\n{0}\n{0}\n{1}'.format('grep_hook_xi', 'grep_hook_xi' + job_id_str + 'Fit:%s__Constr:%s'%(fitAcceptance,constrainAcc) ) 

    for name in angFuncNames:
        print '%24s: %+3f   %+3f  +/- %3f (%s)'%('grep_hook_xi_' + name.split('ang_')[1], \
                                                 my_xi(name), \
                                                 xi(name),\
                                                 xi_er(name), \
                                                 sign(name) )
    
###########################################################################################################################################
## add efficiency weights column to data set ##
###############################################

if addAccWeight:
    print 'adding efficiency weights to dataset'
    from ROOT import RooArgSet, RooArgList, RooFormulaVar, RooConstVar
    rooIntSet  = RooArgSet( var._var for var in intSet  )
    rooNormSet = RooArgSet( var._var for var in normSet )

    effPdf = effTerms.buildSumPdf('effPdf')
    effInt = effPdf.createIntegral( rooIntSet, rooNormSet )
    accWeight = RooFormulaVar( 'accWeight', 'Acceptance weight', '1./@0', RooArgList(effInt) )

    data.addColumn(accWeight)
    
    from ROOT import RooRealVar
    data = data.reduce( Cut = 'accWeight<1000' )
    
    sw = 0.
    for event in data: sw += event.find('accWeight').getVal()
    scale = RooRealVar( 'scale', 'scale ', float( data.numEntries() ) / sw )
    accWeight_norm = RooFormulaVar( 'accWeight_norm', 'Acceptance weight', '(1./@0)*@1', RooArgList(effInt,scale) )
    
    data.addColumn(accWeight_norm)
    
    from ROOT import TFile
    f = TFile.Open('effWeight_mote_carlo_%s_%s.root'%(kaonSign,KpiMassBin),'recreate')
    data.Write()
    f.Close()

    # eff weighted real data
    real_data_path = '/project/bfys/vsyropou/data/Bs2JpsiKst/RealData/second_round/'
    templ_real_data_path = lambda per: real_data_path + 'P2VVDataSet_Bs2JpsiKst_%s_Reco14_%sKaons_%s_%s_KpiBin_141315_BdWeights.root'%(per,kaonSign,KpiMassRange[0],KpiMassRange[1])
    nTupleFiles = [ templ_real_data_path(per) for per in [2011,2012] ]
    dataSets = [ readData( File, dataSetName = nTupleName, NTuple = False, observables = obsSet, **readDataOpts ) for File in nTupleFiles ]
    dataSets[0].append( dataSets[1] )
    real_data = dataSets[0]
    assert False
    real_data.addColumn(accWeight)

    real_data = real_data.reduce( Cut = 'accWeight<1500' )

    sw = 0.
    for event in real_data: sw += event.find('accWeight').getVal()
    scale = RooRealVar( 'scale', 'scale ', float( real_data.numEntries() ) / sw )
    accWeight_norm = RooFormulaVar( 'accWeight_norm', 'Acceptance weight', '(1./@0)*@1', RooArgList(effInt,scale) )
    real_data.addColumn(accWeight_norm)

    f = TFile.Open('effWeight_real_data_%s_%s.root'%(kaonSign,KpiMassBin),'recreate')
    real_data.Write()
    f.Close()    

###########################################################################################################################################
## write data set to file ##
############################

if dataSetFile :
    print 'converting dataset to n-tuple'
    from ROOT import TFile, TObject
    dataFile = TFile.Open( dataSetFile, 'RECREATE' )
    nTuple = data.buildTree( Name = nTupleName, Title = nTupleName, WeightName = weightVar, RooFitFormat = False )
    print 'writing n-tuple to file %s' % dataSetFile
    dataFile.Write( dataSetFile, TObject.kOverwrite )
    dataFile.Close()

