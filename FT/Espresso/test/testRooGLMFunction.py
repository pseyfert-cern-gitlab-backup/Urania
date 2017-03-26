import ROOT
from ROOT import *
from ROOT import RooFit

import Espresso
from Espresso import *

eta = RooRealVar("eta","#eta",0.0,0.5)
calName = "OS_Combination_Calibration"
calFileName = "OS_Combination_Calibration.xml"

glm = ROOT.Espresso.GLMBuilder("OS","OS",eta,calName,calFileName)
coeffs = glm.coefficients()
deltacoeffs = glm.delta_coefficients()
constraint = glm.covariance_matrix()
eta_b = glm.b_mistag()
eta_bbar = glm.bbar_mistag()

f = eta.frame()
eta_b.plotOn(f)
eta_bbar.plotOn(f,RooFit.LineColor(kRed))
c = TCanvas("testRooGLMFunction","testRooGLMFunction",800,600)
c.cd()
f.Draw()
c.SaveAs("testRooGLMFunction.png","png")

