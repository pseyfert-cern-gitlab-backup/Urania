from ROOT import *

gROOT.ProcessLine(".L $URANIAROOT/src/RooAmorosoPdf.cxx++")


class LambdaDecay:
    def __init__(self, name = "Bkg"):

        self.theta = RooRealVar("theta","theta",-200, -1000,-1)
        self.alpha = RooRealVar("alpha","alpha",1, 0.1, 10)
        self.offset = RooRealVar("mean","mean", 5600, 5450, 8000)
        self.beta = RooRealVar("beta", "beta", 2,-7,7)
        self.mass_model = RooAmorosoPdf("testing", "testing" ,Mass, self.offset, self.theta, self.alpha, self.beta)


