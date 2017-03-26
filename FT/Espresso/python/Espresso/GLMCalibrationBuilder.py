#
# @file    GLMCalibrationBuilder.py
# @author  Vincenzo Battista
# @date    2017/03/24
#
# @brief   Python wrapper which allows to create
#          an Espresso calibration object
#          inside a python script

import Espresso
from Espresso import *

import ROOT
from ROOT import *
from ROOT import RooFit

from ROOT.Espresso import RooGLMFunction

class OldGLMBuilder:

    def __init__( self, name, title, eta, calName, calFileName ):
        coeffs, delta_coeffs, matrix, b_mis, bbar_mis = ROOT.Espresso.createRooGLMCalibration(name,
                                                    title,
                                                    eta,
                                                    calName,
                                                    calFileName)
        self.glmlist = glm
    
    #def glm_calibration( self ):
    #    return self.glmlist
    
    def coefficients( self ):
        return coeffs

    def delta_coefficients( self ):
        return delta_coeffs

    def covariance_matrix( self ):
        return matrix

    def b_mistag( self ):
        return b_mis

    def bbar_mistag( self ):
        return bbar_mis

