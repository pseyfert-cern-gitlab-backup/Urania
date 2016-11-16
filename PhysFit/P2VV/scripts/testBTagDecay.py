###########################################################################################################################################
## script parameters ##
#######################

numEvents     =  -1 #1000000 to read dataset from file
dataFilePath  = 'testBTagDecay.root'
plotsFilePath = 'testBTagDecay.pdf'

generalTagging = True
phis         = 0.15 #0.8
lambdas      = 1.
wrongTagProb = 0.35 #0.1
###########################################################################################################################################
## build simplified B_s^0 -> J/psi phi signal PDF ##
####################################################

# dictionary for observables
observables = { }

# workspace
from P2VV.RooFitWrappers import RooObject
ws = RooObject( workspace = 'JpsiphiWorkspace' ).ws()

# B lifetime
from P2VV.Parameterizations.LifetimeParams import Gamma_LifetimeParams as LifetimeParams
lifetimeParams = LifetimeParams()

# time resolution
from P2VV.Parameterizations.TimeResolution import Truth_TimeResolution as TimeResolution
resModel = TimeResolution( time = dict( Value = 0., MinMax = ( 0., 5. ) ) )
observables['time'] = resModel.parameter('time')

# CP violation parameters
from P2VV.Parameterizations.CPVParams import LambdaAbsArg_CPParam as CPParam
lambdaCP = CPParam()
lambdaCP.parameter('phiCP').setVal(phis)
lambdaCP.parameter('lambdaCP').setVal(lambdas)

# angular functions
from P2VV.Parameterizations.AngularFunctions import JpsiphiHelicityAngles as AngleFuncs
angleFuncs = AngleFuncs()
for obsName in [ 'cpsi', 'ctheta', 'phi' ] : observables[obsName] = angleFuncs.angles[obsName]

# decay amplitudes
ampNames = [ 'A0', 'Apar', 'Aperp', 'AS' ]
from P2VV.Parameterizations.DecayAmplitudes import JpsiVPolarSWaveFrac_AmplitudeSet as Amplitudes
amplitudes = Amplitudes()
amplitudes.parameter('C_SP').setConstant(True)

# coefficients for time functions

from P2VV.Parameterizations.TimePDFs import JpsiphiBTagDecayBasisCoefficients_CPT as TimeBasisCoefs
timeBasisCoefs = TimeBasisCoefs( angleFuncs.functions, amplitudes, lambdaCP, ampNames )

# tagging observables and parameters
from P2VV.RooFitWrappers import Category, CategoryVar, FormulaVar,RealCategory
observables['iTag'] = Category ( Name = 'iTag',  Title = 'flavour tag', States = { 'B'  : 1, 'Bbar' :   -1} , Observable = True )
observables['fTag' ] = Category( Name = 'fTag',  Title = 'tagging'    , States = { 'Tag': 1, 'UTag' :    0},  Observable = True )
from P2VV.Parameterizations.FlavourTagging import WTag_TaggingParams as TaggingParams
taggingParams = TaggingParams()
taggingParams.parameter('wTag').setVal(wrongTagProb)
from P2VV.RooFitWrappers import ConstVar,RealVar
zer  = RealVar( Name = 'zer',  Value =  0 )
dilution = CategoryVar( Name = 'Dil' , Category = observables['fTag'] , Variables = [taggingParams['dilution'],zer ])
#iTag = RealCategory( 'iTag_real', observables['iTag'])
#fTag = RealCategory( 'fTag_real', observables['fTag'])
#dilution  = FormulaVar ( Name = 'dilution', Title = 'dilution formula', Formula = '@0*@1*@2' , Arguments = [fTag,taggingParams['dilution'],iTag])

# time PDF arguments
pdfArgs = dict(  time            = observables['time']
                 , tau             = lifetimeParams['MeanLifetime']
                 , dGamma          = lifetimeParams['dGamma']
                 , dm              = lifetimeParams['dM']
                 , resolutionModel = resModel['model']
                 )

if generalTagging :
    # check if there are no B/Bbar asymmetries provided (not implemented yet)
     #for par in [ 'ADilWTag', 'avgCEven', 'avgCOdd' ] :
     #   assert taggingParams[par].ClassName() == 'RooConstVar'\
     #          and abs( taggingParams[par].getVal() - ( 1. if par == 'avgCEven' else 0. ) ) < 1.e-10\
     #                 , 'no B/Bbar asymmetries implemented'

    # loop over the four time coefficients
    for comp in [ 'cosh', 'sinh', 'cos', 'sin' ] :
        if timeBasisCoefs[comp][1] :
            # multiply "odd" time coefficient by tagging factors: q*D*C_O
            from P2VV.RooFitWrappers import Product, Addition, RealCategory
            # take only opposite side events
            from P2VV.RooFitWrappers import CategoryVar
            oddCoef = Product(  Name = comp + 'Coef_odd'
                                , Arguments = [ RealCategory( 'iTag_real', observables['iTag'] )
                                                 , taggingParams['dilution']
                                                 , timeBasisCoefs[comp][1]
                                                 ]
                                )
            if timeBasisCoefs[comp][0] :
                # build sum of "even" and "odd" coefficient
                coef = Addition( Name = comp + 'Coef_evenOdd', Arguments = [ timeBasisCoefs[comp][0], oddCoef ] )
                #for i in range(10): print coef.getVal()
            else :
                # only an "odd" coefficient
                coef = oddCoef
        else :
            # only an "even" coefficient
            # however in the case, where we add CPT contributions we do not have only even coefficients
            #raise Exception( 'By addining CPT contributions we will result on not having only even terms, so you have made a mistake! : ) ')
            assert timeBasisCoefs[comp][0], 'no time-PDF coefficients found for "%s" component' % comp
            coef = timeBasisCoefs[comp][0]
        pdfArgs[ comp + 'Coef' ] = coef

else :
    # provide time coefficients and tagging arguments separately
    assert all( timeBasisCoefs[comp][ind] and not timeBasisCoefs[comp][abs(ind - 1)]\
                for comp, ind in [ ( 'cosh', 0 ), ( 'sinh', 0 ), ( 'cos', 1 ), ( 'sin', 1 ) ] )\
           , 'in the standard RooBTagDecay it is assumed that the "cosh" and "sinh" coefficients don\'t flip sign between B and Bbar and the "cos" and "sin" coefficients do'
    pdfArgs.update(
        dict(  coshCoef = timeBasisCoefs['cosh'][0]
             , sinhCoef = timeBasisCoefs['sinh'][0]
             , cosCoef  = timeBasisCoefs['cos'][1]
             , sinCoef  = timeBasisCoefs['sin'][1]
             , iTag     = observables['iTag']
             , dilution = taggingParams['dilution']
             , ADilWTag = taggingParams['ADilWTag']
             , avgCEven = taggingParams['avgCEven']
             , avgCOdd  = taggingParams['avgCOdd']
            )
    )
lifetimeParams.parameter('dGamma').setVal(0.13)
amplitudes.parameter('A0Mag2').setConstant(True)
amplitudes.parameter('ASOddPhase').setConstant(True)
amplitudes.parameter('AparPhase').setConstant(True)
amplitudes.parameter('AperpMag2').setConstant(True)
amplitudes.parameter('AperpPhase').setConstant(True)
amplitudes.parameter('f_S').setConstant(True)
lambdaCP.parameter('lambdaCP').setConstant(True)
taggingParams.parameter('wTag').setConstant(True)
lifetimeParams.parameter('dM').setConstant(True)
lifetimeParams.parameter('dGamma').setConstant(True)
lifetimeParams.parameter('Gamma').setConstant(True)
lambdaCP.parameter('phiCP').setConstant(True)

# build signal PDF
from P2VV.RooFitWrappers import BTagDecay

pdf = BTagDecay( 'sig_t_angles', **pdfArgs )
# collect python garbage
import gc
gc.collect()
# print PDF
pdf.Print()
pdf.getVariables().Print('v')

###########################################################################################################################################
## generate and fit ##
######################

# set maximum value of PDF for generating angles with accept/reject (is 0.1 a good value?!!)
pdf.setMaxVal(0.1)

from ROOT import TFile
if numEvents > 0 :
    # generate data

    if generalTagging :
        from P2VV.Load import MultiCatGen

    print 'generating %d events' % numEvents
    data = pdf.generate( [ observables[name] for name in [ 'time', 'iTag', 'cpsi', 'ctheta', 'phi' ] ], numEvents, Name = 'JpsiphiData' )
    dataFile = TFile.Open( dataFilePath, 'RECREATE' )
    dataFile.Append(data)
    from ROOT import TObject
    dataFile.Write( dataFilePath, TObject.kOverwrite )
    dataFile.Close()

else :
    # read data from file
    dataFile = TFile.Open(dataFilePath)
    data = dataFile.Get('JpsiphiData')
    print 'read %d events from file' % data.numEntries()
    dataFile.Close()

# fit data
print 'fitting data'
fitResult = pdf.fitTo( data, Minimizer = 'Minuit2', NumCPU = 8, Timer = True, Save = True, Offset = True )
print 'fit results:'
fitResult.PrintSpecial( text = True, LaTeX = False, normal = False )

###########################################################################################################################################
## plot data and PDFs ##
########################

# set LHCb plot style
from P2VV.Load import LHCbStyle
from ROOT import kFullDotLarge

# create plots
frames = [ observables['time'].frame(30), observables['time'].frame(60) ]
data.plotOn( frames[0], MarkerStyle = kFullDotLarge, MarkerSize = 0.7, LineWidth = 2 )
data.plotOn( frames[1], Asymmetry = observables['iTag'], MarkerStyle = kFullDotLarge, MarkerSize = 0.6, LineWidth = 2 )
pdf.plotOn( frames[0], LineWidth = 3 )
pdf.plotOn( frames[1], Asymmetry = observables['iTag'], LineWidth = 3 )

frames[0].GetYaxis().SetTitle( 'Candidates / (%.2g ps)' % frames[0].GetXaxis().GetBinWidth(1) )
frames[1].GetYaxis().SetTitle('B/#bar{B}-tag asymmetry')
frames[0].SetTitleOffset( 1.2, 'Y' )
frames[1].SetTitleOffset( 1.2, 'Y' )

# draw plots
from ROOT import TCanvas
canvs = [ ]
for it, frame in enumerate(frames) :
    canvs.append( TCanvas( 'canv%d' % it ) )
    canvs[-1].SetLeftMargin(0.18)
    canvs[-1].SetRightMargin(0.05)
    canvs[-1].SetBottomMargin(0.18)
    canvs[-1].SetTopMargin(0.05)
    frame.Draw()
    canvs[-1].Print( plotsFilePath + ( '(' if it == 0 else ')' if it == len(frames) - 1 else '' ) )
