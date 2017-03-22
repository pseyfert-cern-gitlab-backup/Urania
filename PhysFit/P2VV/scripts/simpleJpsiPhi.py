###########################################################################################################################################
## set script parameters ##
###########################

from math import pi

from P2VV.Parameterizations.FullPDFs import PdfConfiguration
class Bs2JpsiphiSimpleConfig( PdfConfiguration ) :
        def __init__( self, **kwargs ) :
            
            self['KKMassBinBounds'] = [ 990., 1020. - 12., 1020. - 4., 1020., 1020. + 4., 1020. + 12., 1050. ] 
            self['CSPValues']       = [ 0.870, 0.927, 0.906, 0.949, 0.974, 0.985 ] 
            self['parNamePrefix']   = "SimpleFitConfig"
            self['externalConstr']  = []
            self['CSPprefix']  = "mKK_KKMassBinning"
            from math import pi
            self["obsDict"]=dict(
                    time = ('time','Decay time',              'ps',1.0,0.0,14.0)
                    , cpsi      = ( 'helcosthetaK',         'cos(#theta_{K})',         '',          5.,    -1.,     +1.      )   
                    , ctheta    = ( 'helcosthetaL',         'cos(#theta_{#mu})',       '',          5.,    -1.,     +1.      )
                    , phi       = ( 'helphi',               '#phi_{h}',                'rad',       0.,    -pi,     +pi      ) 
                    , KKMass    = ( 'mKK',                'm(K^{+}K^{-})',           'MeV/c^{2}', 1020.,   990.,   1050.   )     
                    , KKMassCat = ( 'KKMassCat',            'KK mass category',        {'bin%s'%b : b  for b in range(6) }                                   )   
                    , iTagOS    = ( 'iTagOS',               'OS flavour tag',          '',0.,-1.0,1.0)  
                    , timeRes   = ( 'sigmat',               '#sigma(t)',               'ps',        0.01,   0.0001,  0.12    )   
                    )
            self["splitParams"]=dict()
            self["splitParams"]["KKMassCat"]=['ASOddPhase','f_S']
pdfConfig = Bs2JpsiphiSimpleConfig()

dataSetFile = '/project/bfys/sbenson/Jpsiphi-MC/veronika_21-12/veronikaDataset_0p5pi_0.root'

# fit options
fitRange = ''
fitOpts = dict(  NumCPU    = 8
               , Optimize  = 2
               , Minimizer = 'Minuit2'
               , Strategy  = 1
               , Save = True
               , Offset    = True
              )

###########################################################################################################################################
## build PDF ##
###############

# workspace
from P2VV.RooFitWrappers import RooObject
ws = RooObject(workspace = 'JpsiphiWorkspace').ws()

# read data set from file
from P2VV.Utilities.DataHandling import readData
dataSet = readData(filePath = dataSetFile ,dataSetName = "GenLevel" ,NTuple = False )

# build PDF
from P2VV.Parameterizations.FullPDFs import Bs2JpsiphiSimple_PdfBuilder as PdfBuilder
pdfBuild = PdfBuilder( **pdfConfig )
pdf = pdfBuild.pdf()

fitData = dataSet

# get observables and parameters in PDF
pdfObs  = pdf.getObservables(fitData)
pdfPars = pdf.getParameters(fitData)

pdfPars.find("SimpleFitConfig_dGamma").setVal(-0.08)
pdfPars.find("SimpleFitConfig_dGamma").setConstant(True)
pdfPars.find("SimpleFitConfig_phiCP").setVal(0.8)
pdfPars.find("SimpleFitConfig_phiCP").setConstant(True)
pdfPars.find("SimpleFitConfig_AparPhase").setVal(-4.7)
pdfPars.find("SimpleFitConfig_AparPhase").setConstant(True)
pdfPars.find("SimpleFitConfig_AperpPhase").setVal(-4.7)
pdfPars.find("SimpleFitConfig_AperpPhase").setConstant(True)

###########################################################################################################################################
## fit data ##
##############
# print parameters
print 120 * '='
print 'Simple: fit data:'
fitData.Print()
print 'Simple: observables in PDF:'
pdfObs.Print('v')
print 'Simple: parameters in PDF:'
pdfPars.Print('v')
print 'Simple: constraints in PDF:'
for constr in pdf.ExternalConstraints() : constr.Print()

# fit data
print 120 * '='

fitResult = pdf.fitTo( fitData
        , **fitOpts
        )
from P2VV.Imports import parNames, parValues
print 'Simple: parameters:'
fitResult.PrintSpecial( text = True, LaTeX = True, normal = True, ParNames = parNames, ParValues = parValues )
print 'Simple: correlation matrix:'
fitResult.correlationMatrix().Print()
print 'Simple: covariance matrix:'
fitResult.covarianceMatrix().Print()
