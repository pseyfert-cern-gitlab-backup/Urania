######################################
### Simple Toy generator with Foam ###
######################################

# Declare workspace
from P2VV.RooFitWrappers import *
ws = RooObject(workspace = 'JpsiphiWorkspace').ws()

from math import pi
time      = RealVar( 'time'        , Title = 'Decay time'       , Unit =  'ps', Value =  1., MinMax = ( 0., 14.) )
cpsi      = RealVar( 'helcosthetaK', Title = 'cos(#theta_{K})'  , Unit =   '' , Value = 0.5, MinMax = (-1., +1.) )   
ctheta    = RealVar( 'helcosthetaL', Title = 'cos(#theta_{#mu})', Unit =   '' , Value = 0.5, MinMax = (-1., +1.) )
phi       = RealVar( 'helphi'      , Title = '#phi_{h}'         , Unit = 'rad', Value =  0., MinMax = (-pi, +pi) ) 

###########################
### 1st step: build PDF ###
###########################
from P2VV.Parameterizations.FullPDFs import PdfConfiguration
class Bs2JpsiPhiConfig( PdfConfiguration ) :
        def __init__( self, **kwargs ) :
            self['parNamePrefix']   = "FitConfig"
            from math import pi
            self["obsDict"] = dict(
                      time      = ( 'time'        , 'Decay time'       , 'ps', 1.,  0., 14. )
                    , cpsi      = ( 'helcosthetaK', 'cos(#theta_{K})'  ,  '' , 5., -1., +1. )   
                    , ctheta    = ( 'helcosthetaL', 'cos(#theta_{#mu})',  '' , 5., -1., +1. )
                    , phi       = ( 'helphi'      , '#phi_{h}'         ,'rad', 0., -pi, +pi ) 
                    )
pdfConfig = Bs2JpsiPhiConfig()

# Build PDF
from P2VV.Parameterizations.FullPDFs import Bs2JpsiPhiVerySimple_PdfBuilder as PdfBuilder
pdfBuild = PdfBuilder( **pdfConfig )
pdf = pdfBuild.pdf()

# Get observables and parameters in PDF
pdfObs  = [ time, cpsi, ctheta, phi ]
pdfPars_set = pdf.Parameters()

pdfPars = []
for pars in pdfPars_set:
    pdfPars.append(pars)

# Set val for delta Gamma
# pdfPars.find("FitConfig_dGamma").setVal(-0.08)
# Set val for Phi_s
print pdfPars[6]
# pdfPars[6].setVal(0.8) 
# Set phases AperpPhase
# pdfPars[2].setVal(-4.7)
# Set phases AparPhase
# pdfPars[3].setVal(-4.7)


# =============================================================================

###########################
### 2nd step: build Toy ###
###########################
if __name__ == '__main__':
    import cppyy
    Interpreter = cppyy.gbl.gInterpreter
    Interpreter.Load("libP2VVFoam.so")
    Interpreter.Declare('#include "P2VV/P2VVFoam.h"')
    
    obs = cppyy.gbl.std.list(str)()
    for _obs in pdfObs:
       obs.push_back(_obs.GetName())
    # Number of seeds is 1951
    generator = cppyy.gbl.P2VVFoam(ws, pdf._var, obs, 1951)
    generator.GenerateData(100000)
    toy = generator.GetDataSet()
    from ROOT import TFile, TObject
    foamFile  = TFile.Open("FoamDataSet.root", "RECREATE")
    toy_Clone = toy.Clone("toyDataSet")
    toy_Clone.Write("toyDataSet", TObject.kOverwrite)
    foamFile.Close()
