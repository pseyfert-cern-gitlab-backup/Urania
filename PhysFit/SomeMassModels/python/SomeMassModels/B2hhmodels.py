from FiterBasis import *
#from BsMuMuPy.pyAna.FiterBasis import RooFit

from ROOT import *

IncFit01, IncFit02 = {}, {}
IncFit01["Bmass"] = {'f1': 0.0678, 'n': 1.0, 'a3': 1.38, 'a2': -1.19,  'n2': 9.28, 'd1': 72.4}
IncFit01["B_mass"] = IncFit01["Bmass"]
IncFit01["Mpipi"] = {'f1': 0.0707, 'n': 1.0, 'a3': 1.41, 'a2': -1.25,  'n2': 8.53, 'd1': 72.3}
IncFit01["MpiK"]  = {'f1': 0.833,  'n': 1.0, 'a3': 1.35, 'a2': -0.718, 'n2': 4.33, 'd1': 54.0}
IncFit01["MKpi"]  = {'f1': 0.855,  'n': 1.0, 'a3': 1.46, 'a2': -0.758, 'n2': 4.08, 'd1': 59.0}
IncFit01["MKK"]   = {'f1': 0.687,  'n': 1.0, 'a3': 2.33, 'a2': -0.5,   'n2': 4.85, 'd1': 50.4}

IncFit02["Bmass"] = {'rad_slope': 1.10383e-02, 'ftail': 1.97263e-01 , 'fgauss': 8.83655e-01}# 'sigma2': 7.78384e+01}
IncFit02["Mpipi"] = {'rad_slope': 1.42961e-02, 'ftail': 2.26093e-01 , 'fgauss': 8.75905e-01}# 'sigma2':  7.39784e+01}
IncFit01["B_s0_MM"] = IncFit01["Bmass"]
IncFit02["B_s0_MM"] = IncFit02["Bmass"]


class InclusiveFiter01(FiterBasis):

    def __init__(self,tree, var,cuts="", shorTime = True, weight_var=0, fixtails = 1):
        FiterBasis. __init__(self,tree, var,cuts, shorTime = True, weight_var=0, sigf = two_double_cb, bkgf = bkg_with_gauss_shoulder, fit_in_init = not fixtails)

        if fixtails:
            for key in IncFit01[var].keys():
                getattr(self, key).setVal(IncFit01[var][key])
                getattr(self, key).setConstant(kTRUE)
            FiterBasis.fit(self)
            

    def plot(self, bins = 100):
        """Plots the data and the models
        """
        fr = self.mass.frame()
        self.data.plotOn(fr, RooFit.Binning(bins))
        self.model.plotOn(fr)
        self.model.plotOn(fr,RooFit.Components("MS2"), RooFit.LineStyle(kDashed), RooFit.LineColor(kGreen))
        self.model.plotOn(fr,RooFit.Components("MS1"), RooFit.LineStyle(kDashed), RooFit.LineColor(kRed))
        self.model.plotOn(fr,RooFit.Components("bkg"), RooFit.LineStyle(kDashed), RooFit.LineColor(kBlue))
        self.model.plotOn(fr,RooFit.Components("shoulder"), RooFit.LineStyle(kDashed), RooFit.LineColor(kCyan))
        self.model.plotOn(fr,RooFit.Components("Sigmodel"), RooFit.LineColor(kRed))
        self.model.plotOn(fr,RooFit.Components("lambda"), RooFit.LineStyle(kDashed), RooFit.LineColor(kMagenta))
        fr.Draw()
        return(fr)

class InclusiveFiter01b(FiterBasis):

    def __init__(self,tree, var,cuts="", shorTime = True, weight_var=0, fixtails = 1):
        FiterBasis. __init__(self,tree, var,cuts, shorTime = True, weight_var=0, sigf = two_double_cb, bkgf = bkg_with_Pshoulder, fit_in_init = not fixtails)
        
        if fixtails:
            for key in IncFit01[var].keys():
                getattr(self, key).setVal(IncFit01[var][key])
                getattr(self, key).setConstant(kTRUE)
            FiterBasis.fit(self)
            
    def plot(self, bins = 100):
        """Plots the data and the models
        """
        fr = self.mass.frame()
        self.data.plotOn(fr, RooFit.Binning(bins))
        self.model.plotOn(fr)
        self.model.plotOn(fr,RooFit.Components("MS2"), RooFit.LineStyle(kDashed), RooFit.LineColor(kGreen))
        self.model.plotOn(fr,RooFit.Components("MS1"), RooFit.LineStyle(kDashed), RooFit.LineColor(kRed))
        self.model.plotOn(fr,RooFit.Components("bkg"), RooFit.LineStyle(kDashed), RooFit.LineColor(kBlue))
        self.model.plotOn(fr,RooFit.Components("shoulder"), RooFit.LineStyle(kDashed), RooFit.LineColor(kCyan))
        self.model.plotOn(fr,RooFit.Components("Sigmodel"), RooFit.LineColor(kRed))
        self.model.plotOn(fr,RooFit.Components("lambda"), RooFit.LineStyle(kDashed), RooFit.LineColor(kMagenta))
        fr.Draw()
        return(fr)

class InclusiveFiter01A(FiterBasis):

    def __init__(self,tree, var,cuts="", shorTime = True, weight_var=0, fixtails = 1, sigma =0):
        FiterBasis. __init__(self,tree, var,cuts, shorTime = True, weight_var=0, sigf = two_double_cb, bkgf = bkg_with_RooPhysBkg, fit_in_init =not (fixtails or sigma))
        
        if fixtails or sigma:
            for key in IncFit01[var].keys():
                getattr(self, key).setVal(IncFit01[var][key])
                getattr(self, key).setConstant(kTRUE)
            if sigma:
                self.sigma.setVal(sigma)
                self.sigma.setConstant(kTRUE)
        
            FiterBasis.fit(self)
        
            
    def plot(self, bins = 100):
        """Plots the data and the models
        """
        fr = self.mass.frame()
        self.data.plotOn(fr, RooFit.Binning(bins))
        self.model.plotOn(fr)
        self.model.plotOn(fr,RooFit.Components("MS2"), RooFit.LineStyle(kDashed), RooFit.LineColor(kGreen))
        self.model.plotOn(fr,RooFit.Components("MS1"), RooFit.LineStyle(kDashed), RooFit.LineColor(kRed))
        self.model.plotOn(fr,RooFit.Components("bkg"), RooFit.LineStyle(kDashed), RooFit.LineColor(kBlue))
        self.model.plotOn(fr,RooFit.Components("shoulder"), RooFit.LineStyle(kDashed), RooFit.LineColor(kCyan))
        self.model.plotOn(fr,RooFit.Components("Sigmodel"), RooFit.LineColor(kRed))
        self.model.plotOn(fr,RooFit.Components("lambda"), RooFit.LineStyle(kDashed), RooFit.LineColor(kMagenta))
        fr.Draw()
        return(fr)
    

class InclusiveFiter02(FiterBasis):

    def __init__(self,tree, var,cuts="", shorTime = True, weight_var=0, fixtails = 1):
        FiterBasis. __init__(self,tree, var,cuts, shorTime = True, weight_var=0, sigf = sig_with_erf, bkgf = bkg_with_gauss_shoulder, fit_in_init = not fixtails)
        for key in IncFit02[var].keys():
            getattr(self, key).setVal(IncFit02[var][key])
            getattr(self, key).setConstant(kTRUE)
        FiterBasis.fit(self)
            

    def plot(self, bins = 100):
        """Plots the data and the models
        """
        fr = self.mass.frame()
        self.data.plotOn(fr, RooFit.Binning(bins))
        self.model.plotOn(fr)
        self.model.plotOn(fr,RooFit.Components("dgaus"), RooFit.LineStyle(kDashed), RooFit.LineColor(kGreen))
        self.model.plotOn(fr,RooFit.Components("dtail"), RooFit.LineStyle(kDashed), RooFit.LineColor(kRed))
        self.model.plotOn(fr,RooFit.Components("bkg"), RooFit.LineStyle(kDashed), RooFit.LineColor(kBlue))
        self.model.plotOn(fr,RooFit.Components("shoulder"), RooFit.LineStyle(kDashed), RooFit.LineColor(kCyan))
        self.model.plotOn(fr,RooFit.Components("Sigmodel"), RooFit.LineColor(kRed))
        self.model.plotOn(fr,RooFit.Components("lambda"), RooFit.LineStyle(kDashed), RooFit.LineColor(kMagenta))
        fr.Draw()
        return(fr)

class InclusiveFiter02b(FiterBasis):   ### Used the shoulder a la B+->JpsiK+

    def __init__(self,tree, var,cuts="", shorTime = True, weight_var=0, fixtails = 1):
        FiterBasis. __init__(self,tree, var,cuts, shorTime = True, weight_var=0, sigf = sig_with_erf, bkgf = bkg_with_Pshoulder, fit_in_init = not fixtails)
        for key in IncFit02[var].keys():
            getattr(self, key).setVal(IncFit02[var][key])
            getattr(self, key).setConstant(kTRUE)
        FiterBasis.fit(self)
            

    def plot(self, bins = 100):
        """Plots the data and the models
        """
        fr = self.mass.frame()
        self.data.plotOn(fr, RooFit.Binning(bins))
        self.model.plotOn(fr)
        self.model.plotOn(fr,RooFit.Components("dgaus"), RooFit.LineStyle(kDashed), RooFit.LineColor(kGreen))
        self.model.plotOn(fr,RooFit.Components("dtail"), RooFit.LineStyle(kDashed), RooFit.LineColor(kRed))
        self.model.plotOn(fr,RooFit.Components("bkg"), RooFit.LineStyle(kDashed), RooFit.LineColor(kBlue))
        self.model.plotOn(fr,RooFit.Components("shoulder"), RooFit.LineStyle(kDashed), RooFit.LineColor(kCyan))
        self.model.plotOn(fr,RooFit.Components("Sigmodel"), RooFit.LineColor(kRed))
        self.model.plotOn(fr,RooFit.Components("lambda"), RooFit.LineStyle(kDashed), RooFit.LineColor(kMagenta))
        fr.Draw()
        return(fr)

class InclusiveFiter02A(FiterBasis):   ### Used the shoulder a la B+->JpsiK+

    def __init__(self,tree, var,cuts="", shorTime = True, weight_var=0, fixtails = 1):
        FiterBasis. __init__(self,tree, var,cuts, shorTime = True, weight_var=0, sigf = sig_with_erf, bkgf = bkg_with_RooPhysBkg, fit_in_init = not fixtails)
        for key in IncFit02[var].keys():
            getattr(self, key).setVal(IncFit02[var][key])
            getattr(self, key).setConstant(kTRUE)
        FiterBasis.fit(self)
            

    def plot(self, bins = 100):
        """Plots the data and the models
        """
        fr = self.mass.frame()
        self.data.plotOn(fr, RooFit.Binning(bins))
        self.model.plotOn(fr)
        self.model.plotOn(fr,RooFit.Components("dgaus"), RooFit.LineStyle(kDashed), RooFit.LineColor(kGreen))
        self.model.plotOn(fr,RooFit.Components("dtail"), RooFit.LineStyle(kDashed), RooFit.LineColor(kRed))
        self.model.plotOn(fr,RooFit.Components("bkg"), RooFit.LineStyle(kDashed), RooFit.LineColor(kBlue))
        self.model.plotOn(fr,RooFit.Components("shoulder"), RooFit.LineStyle(kDashed), RooFit.LineColor(kCyan))
        self.model.plotOn(fr,RooFit.Components("Sigmodel"), RooFit.LineColor(kRed))
        self.model.plotOn(fr,RooFit.Components("lambda"), RooFit.LineStyle(kDashed), RooFit.LineColor(kMagenta))
        fr.Draw()
        return(fr)

class SigGaussFiter(FiterBasis):
    """signal modeled as a gaussian
    wide range for mean, not very good for exclusive modes,is meant as a crosscheck for inclusive fitters. For exclusive try SigGausExFiter instead
    """

    def __init__(self,tree, var,cuts="", shorTime = True, weight_var=0):
        FiterBasis. __init__(self,tree, var,cuts, shorTime = True, weight_var=0, sigf = gaussian_signal, bkgf = bkg_with_gauss_shoulder)

class TwoGaussPhysBkg(FiterBasis):
    """signal modeled as a gaussian
    wide range for mean, not very good for exclusive modes,is meant as a crosscheck for inclusive fitters. For exclusive try SigGausExFiter instead
    """

    def __init__(self,tree, var,cuts="", shorTime = True, weight_var=0):
        FiterBasis. __init__(self,tree, var,cuts, shorTime = True, weight_var=0, sigf = double_gaussian, bkgf = bkg_with_RooPhysBkg, fit_in_init = 0)
        self.mean1.setMin(5270)
        self.mean1.setMax(5400)
        self.sigma1.setMin(6.)
        self.fit()

        
class SigGaussFiterSC(FiterBasis):
    """signal modeled as a gaussian
    wide range for mean, not very good for exclusive modes,is meant as a crosscheck for inclusive fitters. For exclusive try SigGausExFiter instead
    """

    def __init__(self,tree, var,cuts="", shorTime = True, weight_var=0):
        FiterBasis. __init__(self,tree, var,cuts, shorTime = True, weight_var=0, sigf = gaussian_signal, bkgf = bkg_with_gauss_shoulder, fit_in_init = 0)
        self.sigma.setVal(38.7)
        self.sigma.setConstant(kTRUE)
        FiterBasis.fit(self)

    
        

class SigGaussExFiter(FiterBasis):
    """signal modeled as a gaussian
    mean restricte to 5260 - 5400
    """

    def __init__(self,tree, var,cuts="", shorTime = True, weight_var=0):
        FiterBasis. __init__(self,tree, var,cuts, shorTime = True, weight_var=0, sigf = gaussian_signal, bkgf = bkg_with_gauss_shoulder, fit_in_init=0)
        self.mean.setMin(5260)
        self.mean.setMax(5400)
        FiterBasis.fit(self)

        
        
class SigCBFiter(FiterBasis):
    """Crystalball for single exclusive channel, optional use of Lambda_b background
    """
    def __init__(self,tree, var,cuts="", shorTime = True, weight_var=0, add_lambda = False, transition = 0.):
        if add_lambda:  FiterBasis. __init__(self,tree, var,cuts, shorTime = True, weight_var=0, sigf = CB_signal, bkgf = bkg_with_gauss_shoulder_and_L, fit_in_init=0)
        else: FiterBasis. __init__(self,tree, var,cuts, shorTime = True, weight_var=0, sigf = CB_signal, bkgf = bkg_with_gauss_shoulder, fit_in_init=0)
        self.mean.setMin(5260)
        self.mean.setMax(5400)
        if transition:
            self.a.setVal(transition)
            self.a.setConstant(kTRUE)
        FiterBasis.fit(self)

class TwoCBpeakFiter(FiterBasis):
    """Crystalballs for two exclusives channel, optional use of Lambda_b background
    """
    def __init__(self,tree, var,cuts="", shorTime = True, weight_var=0, add_lambda = False, transition = 0., d1 =5366.3 -5279.5):
        if add_lambda:  FiterBasis. __init__(self,tree, var,cuts, shorTime = True, weight_var=0, sigf = two_cb, bkgf = bkg_with_gauss_shoulder_and_L, fit_in_init=0)
        else: FiterBasis. __init__(self,tree, var,cuts, shorTime = True, weight_var=0, sigf = two_cb, bkgf = bkg_with_gauss_shoulder, fit_in_init=0)
        
        if transition:
            self.a.setVal(transition)
            self.a.setConstant(kTRUE)
        if d1:
            self.d1.setVal(d1)
            self.d1.setConstant(kTRUE)
        FiterBasis.fit(self)
        
    def plot(self, bins = 100):
        """Plots the data and the models
        """
        fr = self.mass.frame()
        self.data.plotOn(fr, RooFit.Binning(bins))
        self.model.plotOn(fr)
        self.model.plotOn(fr,RooFit.Components("Bs peak"), RooFit.LineStyle(kDashed), RooFit.LineColor(kGreen))
        self.model.plotOn(fr,RooFit.Components("Bd peak"), RooFit.LineStyle(kDashed), RooFit.LineColor(kRed))
        self.model.plotOn(fr,RooFit.Components("bkg"), RooFit.LineStyle(kDashed), RooFit.LineColor(kBlue))
        self.model.plotOn(fr,RooFit.Components("shoulder"), RooFit.LineStyle(kDashed), RooFit.LineColor(kCyan))
        self.model.plotOn(fr,RooFit.Components("Sigmodel"), RooFit.LineColor(kRed))
        self.model.plotOn(fr,RooFit.Components("lambda"), RooFit.LineStyle(kDashed), RooFit.LineColor(kMagenta))
        fr.Draw()
        return(fr)
    

