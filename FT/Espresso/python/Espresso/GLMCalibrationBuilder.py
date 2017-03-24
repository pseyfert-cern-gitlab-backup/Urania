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

class GLMBuilder:

    def __init__( self, name, title, eta, calName, calFileName ):
        glm = RooGLMFunction.createRooGLMCalibration(name,
                                                     title,
                                                     eta,
                                                     calName,
                                                     calFileName)

        self.glmlist = glm

    def glm_calibration( self ):
        return self.glmlist

    def coefficients( self ):
        return self.glmlist[0]

    def delta_coefficients( self ):
        return self.glmlist[1]

    def covariance_matrix( self ):
        return self.glmlist[2]

    def b_mistag( self ):
        return self.glmlist[3]

    def bbar_mistag( self ):
        return self.glmlist[4]
