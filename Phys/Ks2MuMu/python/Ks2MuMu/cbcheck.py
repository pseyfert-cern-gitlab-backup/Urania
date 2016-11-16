from ROOT import *
from SomeMassModels.FiterBasis import *
from fiducial import fiducial

#f = TFile("ks2mumumc11.root")#
f = TFile("kspipi1fbA.root")
t = f.Get("T")


def KsCB(fiter):
    """ models the signal as two peaks, each peak being a two-sided crystalball
    """
    
    fiter.mean = RooRealVar("mean1","mean1",490,510)#5168.)
    fiter.sigma = RooRealVar("sigma","sigma", 2,6)#20., 12.,40.)#35.)
    
    fiter.n = RooRealVar("exponent", "exponent",1.)#,  0., 12 )
    
    fiter.a = RooRealVar("transition","transition", 0.5, 3) ## Transition point, in sigmas
    fiter.sig  = RooCBShape("Sigmodel","Sigmodel", fiter.mass, fiter.mean, fiter.sigma, fiter.a, fiter.n) 
    return 1




class KsFit(FiterBasis):

    def __init__(self,tree, cuts="", var= "Bmass", shorTime = True, weight_var=0, fixing = {}):
        FiterBasis. __init__(self,tree, var,cuts, shorTime, weight_var, sigf = KsCB, bkgf = exp_bkg, fit_in_init = 0)#,fixing = fixing )#not fixtails)
        for x in fixing.keys():
            getattr(self,x).setVal(fixing[x])
            getattr(self,x).setConstant(kTRUE)
        self.fit()
            



import cPickle    
eps = cPickle.load(file("eff_BDT"))

op = KsFit(t,fiducial +  "&& L0Tis && Hlt1Tis && Hlt2Tis && BDTDA>0.2 && BDTDA < 0.24800563493660696 && Bmass>475 && Bmass<520", fixing ={"nbkg":0, "indx":0})
op2 = KsFit(t,fiducial +  "&& L0Tis && Hlt1Tis && Hlt2Tis && BDTDA>0.2 && BDTDA > 0.24800563493660696 && Bmass>475 && Bmass<520", fixing ={"nbkg":0, "indx":0})

from SomeUtils.alyabar import *

def get_pseudo_tis(t, a,b):
    ba = str(eps(1-a))
    bb = str(eps(1-b))
    print ba, bb
    cut = fiducial + "&& BDTDA>"+ba +"&&BDTDA<"+bb
    print t.GetEntries(cut)
    tos = cut +"&& L0Tos && Hlt1Tos &&Hlt2Tos"
    tis = cut +"&& L0Tis && Hlt1Tis &&Hlt2Tis"
    TISTOS = t.GetEntries(tos + "&& L0 Tis && Hlt1Tis && Hlt2Tis")
    TOS = t.GetEntries(tos)
    TIS = t.GetEntries(tis)
    print TIS,TOS, TISTOS
    print nonIndepErrors(TISTOS,TOS)
    print nonIndepErrors(TISTOS,TIS)
