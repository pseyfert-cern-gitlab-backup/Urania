from ROOT import *
from FiterBasis import *

#from BsMuMuPy.pyAna.FiterBasis import RooExponential

class SigGaussFiter(FiterBasis):

    def __init__(self,tree, var,cuts="", shorTime = True, weight_var=0):
        FiterBasis. __init__(self,tree, var,cuts, shorTime, weight_var, sigf = gaussian_signal, bkgf = exp_bkg, fit_in_init=False)
        self.mean.setMin(1650)
        self.mean.setMax(2100)
        self.sigma.setMin(3.)
        self.fit()
        
class SigCBFiter(FiterBasis):

    def __init__(self,tree, var,cuts="", shorTime = True, weight_var=0):
        FiterBasis. __init__(self,tree, var,cuts, shorTime, weight_var, sigf = CB_signal, bkgf = bkg_with_Pshoulder)
        self.mean.setMin(1850)
        self.mean.setMax(2100)

class DoubleGaussian(FiterBasis):

    def __init__(self,tree, var,cuts="", shorTime = True, weight_var=0, fit1peak = True, fixBs = False, single = 0, fit_in_init = False):
        FiterBasis. __init__(self,tree, var,cuts, shorTime , weight_var, sigf = double_gaussian, bkgf = exp_bkg, fit_in_init=fit_in_init)
            
        #self.sh_trans.setRange( 5050.,5250.)
        self.mean1.setRange(1850,2100)
        self.sigma1 = RooRealVar("sigma1","sigma1", 3.,15)

        if fit1peak:
            self.fB2.setVal(0)
            self.fB2.setConstant(kTRUE)
        if fixBs:
            self.mean1.setRange(1850,2100)
            self.delta_m.setVal(fixBs)
            self.delta_m.setConstant(kTRUE)
        if single:
            self.sigma1.setRange(3,20)
            self.f1.setVal(1)
            self.f1.setConstant(kTRUE)
            self.delta_s.setConstant(kTRUE)
            
        #self.mean.setMin(5270)
        #self.mean.setMax(5400)
        self.fit()

    def plot(self, bins = 100):
        """Plots the data and the models
        """
        fr = self.mass.frame()
        self.data.plotOn(fr, RooFit.Binning(bins))
        self.model.plotOn(fr)
        self.model.plotOn(fr,RooFit.Components("bkg"), RooFit.LineStyle(kDashed), RooFit.LineColor(kBlue))
        self.model.plotOn(fr,RooFit.Components("shoulder"), RooFit.LineStyle(kDashed), RooFit.LineColor(kCyan))
        self.model.plotOn(fr,RooFit.Components("Sigmodel"), RooFit.LineColor(kRed))
        self.model.plotOn(fr,RooFit.Components("phi"), RooFit.LineStyle(kDashed), RooFit.LineColor(kMagenta))
        
        self.model.plotOn(fr,RooFit.Components("Sigmodel"), RooFit.LineColor(kRed))
        
        fr.Draw()
        return(fr)

class CBplusGaussian(FiterBasis):

    def __init__(self,tree, var,cuts="", shorTime = True, weight_var=0, fit1peak = True, fit_in_init= True):
        FiterBasis. __init__(self,tree, var,cuts, shorTime, weight_var, sigf = CB_plus_gaussian, bkgf = bkg_with_Pshoulder, fit_in_init=fit_in_init)
        if fit1peak:
            self.fB2.setVal(0)
            self.fB2.setConstant(kTRUE)
        #self.mean.setMin(5270)
        #self.mean.setMax(5400)
        self.fit()

def bkg_with_gauss_shoulder(fiter):
    """ models the bkg as an exponential + a shoulder on the left described as a wide Gaussian. Optionally adds a Lambda_b component
    """

    
    ###bkg pdf
    fiter.bkg_indx = RooRealVar("indx", "indx", -0.001, -0.1, 0.)
    fiter.linbkg = RooExponential("expBkg", "Exponential background pdf", fiter.mass, fiter.bkg_indx)
   
    
    ###Shoulder
    fiter.sh_mean = RooRealVar("sh_mean", "sh_mean", 5279.5)
    fiter.sh_sigma = RooRealVar("sh_sigma", "sh_sigma", 20)
       
    #fiter.sh_trans.setConstant(kTRUE)
    #fiter.sh_sigma.setConstant(kTRUE)
    #fiter.sh_mean.setConstant(kTRUE)
       
    #fiter.shoulder = RooExpAndGauss("shoulder", "shoulder pdf", fiter.mass,fiter.sh_mean, fiter.sh_sigma, fiter.sh_trans)
    fiter.shoulder = RooGaussian("shoulder","shoulder pdf", fiter.mass, fiter.sh_mean, fiter.sh_sigma)
    #### model
   
    fiter.fsh = RooRealVar("fh", "shoulder fraction in background", 0.5,0.,1.)
    fiter.bkg = RooAddPdf("bkg", "background pdf", fiter.shoulder, fiter.linbkg, fiter.fsh)

    
    return 1




class BsJpsiKstarForced(FiterBasis):

    def __init__(self,tree, var,cuts="", shorTime = True, weight_var=0, fit_in_init = False):
        FiterBasis. __init__(self,tree, var,cuts, shorTime, weight_var, sigf = gaussian_signal, bkgf = bkg_with_gauss_shoulder, fit_in_init=fit_in_init)
        self.mean.setMin(5279 + 80)
        self.mean.setVal(5366.3)
        self.mean.setMax(5279 + 105)
        self.sigma.setMin(7)
        self.sigma.setVal(7.92)
        self.sigma.setMax(10)
        self.bkg_indx.setMin(-1e-01)
        #self.sigma.setConstant(kFALSE)
        self.sigma.setConstant(kTRUE)
        #self.mean.setConstant(kTRUE)
        self.fit()

## from ROOT import *
## f = TFile("/afs/cern.ch/project/lbcern/vol5/diegoms/NTuples/stp12_B2JPsiX_Bd_incompleto.root")
## t = f.Get("Bd2JPsiKstar")
#op = DoubleGaussian(t,"Bmass","Bmass>4900 && Bmass<5700 && Bdissig>20 && Bips<3 && mu1ips>6 && mu2ips>6 && k1ips>6 && p1ips>6 && Vchi2<15 && PIDk>1 && abs(KstMass-895.94)<100", fit1peak=False)

#op = BsJpsiKstarForced(t,"Bmass","Bmass>5320 && Bmass<5700 && Bdissig>15 && Bips<3 && Bip<0.05 && mu1ips>5 && mu2ips>5 && k1ips>5 && p1ips>5 && Vchi2<9 && PIDk>5 && abs(KstMass-895.94)<80")


## FCN=-3097.2 FROM MINOS     STATUS=PROBLEMS     2669 CALLS        5980 TOTAL
##                      EDM=6243.63    STRATEGY= 1      ERROR MATRIX ACCURATE 
##   EXT PARAMETER                  PARABOLIC         MINOS ERRORS        
##   NO.   NAME      VALUE            ERROR      NEGATIVE      POSITIVE   
##    1  Sigfraction   1.95759e+03   6.36244e+01                            
##    2  bkgfraction   1.46409e+02   4.74379e+01                            
##    3  fbkg         2.18707e-03   7.04572e-03                            
##    4  indx        -9.92636e-01   2.07847e-04                            
##    5  logvar       7.45500e+02   2.53845e-07                            
##    6  mean         8.95576e+02   7.47868e-01                 7.49315e-01
## ##    7  sigma        4.71082e+01   2.23018e+00 
## f=TFile("/afs/cern.ch/lhcb/group/physics/bsmumu/ntuples/2011/Blind_150pb/stp13_dms_pidWeights.root")
## t = f.Get("Bs2JPsiPhi")
## op = SigGaussFiter(t,"Bmass_JC", "Bmass_JC>5000 && Bmass_JC<5600 && PIDk1>0 && PIDk2<0",weight_var = "WeightB")
